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

#include <moba/jsondecoder.h>
#include <moba/jsonstreamreadersocket.h>

#include "registry.h"
#include "clienthandler.h"
#include "endpoint.h"

Endpoint::Endpoint(SocketPtr socket) : socket{socket} {
}

Endpoint::~Endpoint() {
    ClientClose msg;
    sendMsg(msg);
}

long Endpoint::connect(const std::string &appName, moba::Version version, const moba::JsonArrayPtr &groups) {
    this->appName = appName;
    this->version = version;
    this->groups = groups;
    connect();
}

long Endpoint::connect() {
    return registerApp();
}

long Endpoint::registerApp() {
    moba::JsonObjectPtr obj{new moba::JsonObject{}};

    ClientStart msg{AppData{appName, version, groups}};

    sendMsg(msg);
    auto data = recieveMsg(Endpoint::MSG_HANDLER_TIME_OUT_SEC);
    auto o = boost::dynamic_pointer_cast<moba::JsonObject>(data);
    auto msgKey = moba::castToString(o->at(BaseMessage::MSG_HEADER_NAME));
    auto msgData = o->at(BaseMessage::MSG_HEADER_DATA);

    ClientConnected mptr{msgData};

    if(msgKey != mptr.getMessageName()) {
        throw SocketException{"did not recieve CLIENT_CONNECTED"};
    }
    return appId = mptr.appId;
}

moba::JsonItemPtr Endpoint::recieveMsg(time_t timeoutSec) {
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
        return moba::toJsonNULLPtr();
    }

    moba::JsonStreamReaderSocketPtr reader{new moba::JsonStreamReaderSocket{sd}};
    moba::JsonDecoder decoder(reader);
    return decoder.decode();
}

void Endpoint::sendMsg(const DispatchMessage &msg) {
    std::string s = msg.getRawMessage();
    ssize_t c = ::send(socket->getSocket(), s.c_str(), s.length(), 0);
    if(c == -1 || c != s.length()) {
        throw SocketException{"sending <" + s + "> failed"};
    }
}
