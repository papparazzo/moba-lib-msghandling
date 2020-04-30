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

#include <string>
#include <memory>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <cstdint>

#include <moba-common/log.h>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"

#include "rapidjson/socketwritestream.h"
#include "rapidjson/socketreadstream.h"

#include "clientmessage.h"
#include "endpoint.h"
#include "shared.h"

Endpoint::Endpoint(
    SocketPtr socket, const std::string &appName, moba::common::Version version, Groups groups
) : socket{socket}, appName{appName}, version{version}, groups{groups} {
}

Endpoint::Endpoint(
    SocketPtr socket, const std::string &appName, moba::common::Version version
) : socket{socket}, appName{appName}, version{version}, groups{Groups::ALL} {
}

long Endpoint::connect() {
    socket->init();
    return registerApp();
}

long Endpoint::registerApp() {
    sendMsg(ClientStart{AppData{appName, version, groups}});

    auto msg = recieveMsg(Endpoint::MSG_HANDLER_TIME_OUT_SEC);

    if(!msg.data.IsInt()) {
        throw SocketException{"msg data is not an int"};
    }

    if(msg.groupId != Message::CLIENT || msg.messageId != ClientMessage::CLIENT_CONNECTED) {
        throw SocketException{"did not recieve CLIENT_CONNECTED"};
    }

    return appId = msg.data.GetInt();
}

RawMessage Endpoint::recieveMsg(time_t timeoutSec) {
    struct timeval timeout;
    fd_set         read_sock;

    int sd = socket->getSocket();

    FD_ZERO(&read_sock);
    FD_SET(sd, &read_sock);

    timeout.tv_sec = timeoutSec;
    timeout.tv_usec = MSG_HANDLER_TIME_OUT_USEC;

    if(::select(sd + 1, &read_sock, NULL, NULL, &timeout) == -1) {
        throw SocketException{"select-error occured!"};
    }

    if(!FD_ISSET(sd, &read_sock)) {
        return RawMessage{};
    }
    return waitForNewMsg();
}

RawMessage Endpoint::waitForNewMsg() {
    std::uint32_t d[3];

    if(::recv(socket->getSocket(), d, sizeof(d), MSG_WAITALL) < static_cast<ssize_t>(sizeof(d))) {
        throw SocketException{"recv header failed"};
    }

    for(int i = 0; i < 3; ++i) {
        d[i] = ::ntohl(d[i]);
    }
    LOG(moba::common::LogLevel::DEBUG) << "recieve message <" << d[0] << ":" << d[1] << "> {" << d[2] << "} bytes" << std::endl;
    rapidjson::SocketReadStream srs{socket->getSocket(), d[2]};
    return RawMessage{d[0], d[1], srs};
}

void Endpoint::sendMsg(std::uint32_t grpId, std::uint32_t msgId, const rapidjson::Document &data) {
    std::lock_guard<std::mutex> l{m};

    rapidjson::StringBuffer buffer;
    rapidjson::Writer writer{buffer};
    data.Accept(writer);

    size_t bufferSize = buffer.GetSize();

    std::uint32_t d[] = {
        ::htonl(grpId),
        ::htonl(msgId),
        ::htonl(bufferSize)
    };
    LOG(moba::common::LogLevel::DEBUG) << "try to send message <" << grpId << ":" << msgId << "> {" << bufferSize << "} bytes" << std::endl;

    if(::send(socket->getSocket(), d, sizeof(d), 0) < static_cast<ssize_t>(sizeof(d))) {
        throw SocketException{"sending header failed"};
    }

    if(::send(socket->getSocket(), buffer.GetString(), bufferSize, 0) < static_cast<ssize_t>(bufferSize)) {
        throw SocketException{"sending body failed"};
    }
}
