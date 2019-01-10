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

#include "sender.h"
#include <string>
#include <memory>

#include <sys/types.h>
#include <sys/socket.h>

#include <moba/jsondecoder.h>
#include <moba/jsonmsgdecoder.h>
#include <moba/jsonstreamreadersocket.h>

Sender::Sender(SocketPtr socket) : socket{socket} {
}

Sender::~Sender() {
    //sendMsg(Message::MT_CLIENT_CLOSE);
}

long Sender::connect(const std::string &appName, moba::Version version, const moba::JsonArrayPtr &groups) {
    this->appName = appName;
    this->version = version;
    this->groups = groups;
    connect();
}

long Sender::connect() {
    init();
    return registerApp();
}

long Sender::registerApp() {
    moba::JsonObjectPtr obj{new moba::JsonObject{}};

    (*obj)["appName"  ] = moba::toJsonStringPtr(appName);
    (*obj)["version"  ] = version.toJsonPtr();
    (*obj)["msgGroups"] = groups;
/*
    Message msg{Message::MT_CLIENT_START, obj};
    sendMsg(msg);
    auto mptr = recieveMsg();
    if(!mptr || mptr->getMsgType() != Message::MT_CLIENT_CONNECTED) {
        throw SocketException{"did not recieve CLIENT_CONNECTED"};
    }

    auto item = mptr->getData();

    std::shared_ptr<moba::JsonNumber<long int>> o = std::dynamic_pointer_cast<moba::JsonNumber<long int>>(item);
    return appId = o->getVal();
 */
}

moba::MessagePtr Sender::recieveMsg() {
    struct timeval timeout;
    fd_set         read_sock;

    int sd = socket->getSocket();

    FD_ZERO(&read_sock);
    FD_SET(sd, &read_sock);

    timeout.tv_sec = MSG_HANDLER_TIME_OUT_SEC;
    timeout.tv_usec = MSG_HANDLER_TIME_OUT_USEC;

    if(::select(sd + 1, &read_sock, NULL, NULL, &timeout) == -1) {
        throw SocketException{"select-error occured!"};
    }

    if(!FD_ISSET(sd, &read_sock)) {
        return moba::MessagePtr{};
    }

    moba::JsonStreamReaderSocketPtr reader{new moba::JsonStreamReaderSocket(sd)};
    moba::JsonMsgDecoder decoder(reader);
    return decoder.decodeMsg();
}

void Sender::sendMsg(const std::string &msgType, const moba::JsonItemPtr &msgData) {
    moba::JsonObject obj;
    obj["msgType"] = moba::toJsonStringPtr(msgType);
    obj["msgData"] = msgData;
    sendMsg(obj);
}

void Sender::sendMsg(const std::string &msgType, const std::string &msgData) {
    moba::JsonObject obj;
    obj["msgType"] = moba::toJsonStringPtr(msgType);
    obj["msgData"] = moba::toJsonStringPtr(msgData);
    sendMsg(obj);
}

void Sender::sendMsg(const std::string &msgType) {
    moba::JsonObject obj;
    obj["msgType"] = moba::toJsonStringPtr(msgType);
    obj["msgData"] = moba::toJsonNULLPtr();
    sendMsg(obj);
}
/*
    void MsgEndpoint::sendMsg(const Message &msg) {
        JsonObject obj;
        obj["msgType"] = Message::convertToString(msg.getMsgType());
        obj["msgData"] = msg.getData();
        sendMsg(obj);
    }
*/

void Sender::sendMsg(const moba::JsonObject &obj) {
    std::string s = obj.getJsonString();
    ssize_t c = ::send(socket->getSocket(), s.c_str(), s.length(), 0);
    if(c == -1 || c != s.length()) {
        throw SocketException{"sending <" + s + "> failed"};
    }
}
