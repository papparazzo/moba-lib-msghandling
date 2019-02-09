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

#pragma once

#include <string>

#include "jsonabstractitem.h"


/*

            void sendGetLayoutsRequest() {msgep->sendMsg(Message::MT_GET_LAYOUTS_REQ);}

            void sendDeleteLayout(long id) {msgep->sendMsg(Message::MT_DEL_LAYOUT, toJsonNumberPtr(id));}

            void sendCreateLayout(const std::string &name, const std::string &description);

            void sendUpdateLayout(long id, const std::string &name, const std::string &description);

            void sendUnlockLayout(long id) {msgep->sendMsg(Message::MT_UNLOCK_LAYOUT, toJsonNumberPtr(id));}

            void sendGetLayoutRequest(long id) {msgep->sendMsg(Message::MT_GET_LAYOUT_REQ, toJsonNumberPtr(id));}



    void MsgLayoutsHandler::sendCreateLayout(const std::string &name, const std::string &description) {
        JsonObjectPtr obj(new JsonObject());
        (*obj)["name"       ] = toJsonStringPtr(name);
        (*obj)["description"] = toJsonStringPtr(description);
        msgep->sendMsg(Message(Message::MT_CREATE_LAYOUT_REQ, obj));
    }

    void MsgLayoutsHandler::sendUpdateLayout(long id, const std::string &name, const std::string &description) {
        JsonObjectPtr obj(new JsonObject());
        (*obj)["id"         ] = toJsonNumberPtr(id);
        (*obj)["name"       ] = toJsonStringPtr(name);
        (*obj)["description"] = toJsonStringPtr(description);
        msgep->sendMsg(Message(Message::MT_UPDATE_LAYOUT, obj));
    }
*/