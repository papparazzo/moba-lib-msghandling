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


#include "basemessage.h"

const std::string BaseMessage::MSG_HEADER  = "msgType";
const std::string BaseMessage::DATA_HEADER = "msgData";

BaseMessage::BaseMessage(const BaseMessage& orig) {
}

BaseMessage::~BaseMessage() {
}

std::string BaseMessage::getRawMessage() {
    moba::JsonObject obj;

    obj["msgType"] = moba::toJsonStringPtr(this->getMessageName());
    obj["msgData"] = this->data;
    return obj.getJsonString();
}