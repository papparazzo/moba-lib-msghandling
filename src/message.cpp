/*
 *  Project:    moba-common
 *
 *  Copyright (C) 2016 Stefan Paproth <pappi-@gmx.de>
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

#include "message.h"

const std::string Message::MSG_HEADER  = "msgType";
const std::string Message::DATA_HEADER = "msgData";

Message::Message(MessageType msgType) {
    this->msgType = msgType;
}

Message::Message(MessageType msgType, JsonItemPtr data) {
    this->msgType = msgType;
    this->data = data;
}

Message::~Message() {
}

Message::MessageType Message::convertToMsgType(const std::string &msgName) {
    int size =
        sizeof(__msgEnumClearTextStruct) / sizeof(__msgEnumClearTextStruct[0]);

    for(int i = 0; i < size; ++i) {
        if(msgName == __msgEnumClearTextStruct[i].msg) {
            return __msgEnumClearTextStruct[i].type;
        }
    }
    return MT_UNKNOWN;
}

JsonStringPtr Message::convertToString(Message::MessageType mt) {
    int size =
        sizeof(__msgEnumClearTextStruct) / sizeof(__msgEnumClearTextStruct[0]);

    for(int i = 0; i < size; ++i) {
        if(__msgEnumClearTextStruct[i].type == mt) {
            return JsonStringPtr(
                new JsonString(__msgEnumClearTextStruct[i].msg)
            );
        }
    }

    return JsonStringPtr(new JsonString("UNKNOWN"));
}

std::string Message::getRawMessage() const {
    JsonObject obj;
    obj["msgType"] = Message::convertToString(this->msgType);
    obj["msgData"] = this->data;
    return obj.getJsonString();
}

std::string Message::msgTypeAsString() const {
    int size =
        sizeof(__msgEnumClearTextStruct) / sizeof(__msgEnumClearTextStruct[0]);

    for(int i = 0; i < size; ++i) {
        if(__msgEnumClearTextStruct[i].type == this->msgType) {
            return __msgEnumClearTextStruct[i].msg;
        }
    }
    return "UNKNOWN";
}

