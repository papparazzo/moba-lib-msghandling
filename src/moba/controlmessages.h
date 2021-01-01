/*
 *  Project:    moba-blocksystem
 *
 *  Copyright (C) 2020 Stefan Paproth <pappi-@gmx.de>
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

#include "message.h"
#include "shared.h"

struct ControlMessage : public Message {
    enum MessageName {
        CONTROL_GET_CONTACT_LIST_REQ = 1,
        CONTROL_GET_CONTACT_LIST_RES = 2,
    };

    static constexpr std::uint32_t GROUP_ID = CONTROL;
};

struct ControlGetContactListReq : public ControlMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_GET_CONTACT_LIST_REQ;

    ControlGetContactListReq(int layoutId = 0) : layoutId{layoutId} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        if(layoutId) {
            d.SetInt(layoutId);
        } else {
            d.SetNull();
        }
        return d;
    }

    int layoutId;
};

/*
struct ControlGetContactListRes : public ControlMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_GET_CONTACT_LIST_RES;

    ControlGetContactListRes(const rapidjson::Document &d) {
        blockContacts = std::make_shared<BlockContacts>();

        for(auto &iter : d.GetArray()) {
            (*blockContacts)[{iter["xPos"].GetInt(), iter["yPos"].GetInt()}] = BlockContactData(iter);
        }
    }

    BlockContactsPtr blockContacts;
};
 */