/*
 *  Project:    moba-lib-msghandling
 *
 *  Copyright (C) 2019 Stefan Paproth <pappi-@gmx.de>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program. If not, see <https://www.gnu.org/licenses/agpl.txt>.
 *
 */

#include "socket.h"
#include <cstring>

#include <sys/socket.h>

#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <cerrno>

Socket::Socket(const std::string_view host, const int port): socket{-1} {
    if(host == "" || port > 64738 || port < 1024) {
        throw SocketException{"either host or port is invalid!"};
    }
    this->host = host;
    this->port = port;
}

Socket::~Socket() noexcept {
    close();
}

void Socket::init() {
    close();

    addrinfo hints{};
    addrinfo *res = nullptr;
    const addrinfo *rp = nullptr;

    hints.ai_flags    = AI_NUMERICSERV;
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if(
        const int result = getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &res);
        result != 0
    ) {
        throw SocketException{std::string{"Resolving host failed: "} + gai_strerror(result)};
    }

    std::unique_ptr<addrinfo, decltype(&freeaddrinfo)> res_guard(res, freeaddrinfo);

    for(rp = res; rp != nullptr; rp = rp->ai_next) {
        if((socket = ::socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)) == -1) {
            continue;
        }

        timeval timeout{.tv_sec = 10, .tv_usec = 0};
        setsockopt(socket, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));

        if(connect(socket, rp->ai_addr, rp->ai_addrlen) == 0 || errno == EINPROGRESS) {
            return;
        }
    }

    throw SocketException{std::string{"Socket creation failed: "} + strerror(errno)};
}

void Socket::close() {
    if(socket == -1) {
        return;
    }

    ::close(socket);
    socket = -1;
}
