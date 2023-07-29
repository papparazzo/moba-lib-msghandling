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
 *  along with this program. If not, see <http://www.gnu.org/licenses/agpl.txt>.
 *
 */

#include "socket.h"
#include <cstring>

#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

Socket::Socket(const std::string &host, int port): socket{-1} {
    if(host == "" || port > 64738 || port < 1024) {
        throw SocketException{"either host or port is invalid!"};
    }
    this->host = host;
    this->port = port;
}

Socket::~Socket() noexcept {
    if(socket != -1) {
        close(socket);
    }
}

void Socket::init() {
    if(socket != -1) {
        close(socket);
    }

    struct in6_addr serverAddr;
    struct addrinfo hints;
    struct addrinfo *result = nullptr;

    memset(&hints, 0x00, sizeof(hints));
    hints.ai_flags    = AI_NUMERICSERV;
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if(inet_pton(AF_INET, host.c_str(), &serverAddr) == 1) {
        hints.ai_family = AF_INET;
        hints.ai_flags |= AI_NUMERICHOST;
    } else if(inet_pton(AF_INET6, host.c_str(), &serverAddr) == 1) {
        hints.ai_family = AF_INET6;
        hints.ai_flags |= AI_NUMERICHOST;
    }

    if(getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &result) != 0) {
        throw SocketException{"resolving url failed"};
    }

    socket = ::socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if(socket == -1) {
        freeaddrinfo(result);
        throw SocketException{"socket creation failed"};
    }

    if(::connect(socket, result->ai_addr, result->ai_addrlen) == -1) {
        freeaddrinfo(result);
        throw SocketException{"connection to host failed"};
    }
    freeaddrinfo(result);
}
