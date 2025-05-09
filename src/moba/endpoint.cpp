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

#include <string>
#include <sstream>
#include <memory>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "clientmessages.h"
#include "endpoint.h"

#include "shared.h"

Endpoint::Endpoint(
    const SocketPtr &socket, const std::string &appName, const moba::Version &version, const MessageGroups &groups
) : socket{socket}, appName{appName}, version{version}, groups{groups} {
}

Endpoint::Endpoint(
    const SocketPtr &socket, const std::string &appName, const moba::Version &version
) : socket{socket}, appName{appName}, version{version} {
}

long Endpoint::connect() {
    socket->init();
    return registerApp();
}

long Endpoint::getAppId() const {
    return appId;
}

long Endpoint::registerApp() {
    sendMsg(ClientStart{AppData{appName, version, groups}});

    const auto msg = receiveMsg(Endpoint::MSG_HANDLER_TIME_OUT_SEC);

    if(!msg.data.is_number()) {
        throw SocketException{"msg data is not an int"};
    }

    if(msg.groupId != Message::CLIENT || msg.messageId != ClientMessage::CLIENT_CONNECTED) {
        throw SocketException{"did not receive CLIENT_CONNECTED"};
    }

    return appId = msg.data.get<int>();
}

RawMessage Endpoint::receiveMsg(const time_t timeoutSec) const {
    timeval timeout{};
    fd_set  read_sock;

    const int sd = socket->getSocket();

    FD_ZERO(&read_sock);
    FD_SET(sd, &read_sock);

    timeout.tv_sec = timeoutSec;
    timeout.tv_usec = MSG_HANDLER_TIME_OUT_USEC;

    if(::select(sd + 1, &read_sock, nullptr, nullptr, &timeout) == -1) {
        throw SocketException{"select-error occurred!"};
    }

    if(!FD_ISSET(sd, &read_sock)) {
        return RawMessage{};
    }
    return waitForNewMsg();
}

RawMessage Endpoint::waitForNewMsg() const {
    std::uint32_t d[3];

    ssize_t rev;
    // Try again on the interrupted function call
    while((rev = recv(socket->getSocket(), d, sizeof(d), MSG_WAITALL)) == -1) {
        if(errno != EINTR) {
            throw SocketException{std::strerror(errno)};
        }
    }

    if(rev < static_cast<ssize_t>(sizeof(d))) {
        throw SocketException{"receive header failed"};
    }

    for(unsigned int &i : d) {
        i = ntohl(i);
    }

    std::string output;
    output.resize(d[2]);

    if(
        const auto bytes_received = recv(socket->getSocket(), &output[0], d[2], MSG_WAITALL);
        bytes_received < 0
    ) {
        return RawMessage{};
    }

    return RawMessage{d[0], d[1], nlohmann::json::parse(output)};
}

std::string Endpoint::waitForNewMsgAsString() const {
    std::uint32_t d[3];

    if(recv(socket->getSocket(), d, sizeof(d), MSG_WAITALL) < static_cast<ssize_t>(sizeof(d))) {
        throw SocketException{"recv header failed"};
    }

    for(int i = 0; i < 3; ++i) {
        d[i] = ntohl(d[i]);
    }

    std::string output;
    output.resize(d[2]);

    if(
        auto bytes_received = ::recv(socket->getSocket(), &output[0], d[2], MSG_WAITALL);
        bytes_received < 0
    ) {
        return "";
    }

    std::stringstream ss;
    ss << "{\"groupId\":" << d[0] << ", \"messageId\":" << d[1] << ", \"data\":" << output << "}";

    return ss.str();
}

void Endpoint::sendMsg(const std::uint32_t grpId, const std::uint32_t msgId, const nlohmann::json &data) {
    std::lock_guard l{m};
    sendMsg(grpId, msgId, data.dump());
}

void Endpoint::sendMsg(const std::uint32_t grpId, const std::uint32_t msgId, const std::string &data) {
    const auto bufferSize = data.length();

    std::uint32_t d[] = {
        htonl(grpId),
        htonl(msgId),
        htonl(bufferSize)
    };

    if(send(socket->getSocket(), d, sizeof(d), MSG_NOSIGNAL) < static_cast<ssize_t>(sizeof(d))) {
        throw SocketException{"sending header failed"};
    }

    if(send(socket->getSocket(), data.c_str(), bufferSize, MSG_NOSIGNAL) < static_cast<ssize_t>(bufferSize)) {
        throw SocketException{"sending body failed"};
    }
}
