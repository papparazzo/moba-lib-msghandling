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

#include <moba-common/version.h>
#include "basemessage.h"
#include "shared.h"

struct ClientMessage : public Message {
    enum MessageName {
        CLIENT_VOID         = 1,
        CLIENT_ECHO_REQ     = 2,
        CLIENT_ECHO_RES     = 3,
        CLIENT_ERROR        = 4,
        CLIENT_START        = 5,
        CLIENT_CONNECTED    = 6,
        CLIENT_CLOSE        = 7,
        CLIENT_SHUTDOWN     = 8,
        CLIENT_RESET        = 9,
        CLIENT_SELF_TESTING = 10
    };

    ClientMessage(unsigned int msgId) : Message{CLIENT, msgId} {
    }
};

struct ClientVoid : public ClientMessage {
    ClientVoid() : ClientMessage{CLIENT_VOID} {
    }
};

struct ClientEchoReq : public ClientMessage {
    ClientEchoReq(long payload) : ClientMessage{CLIENT_ECHO_REQ} {
        data.SetInt(payload);
    }
};
/*
struct ClientEchoRes : public ClientMessage {
    ClientEchoRes(const rapidjson::Document &d) : SystemMessage{CLIENT_ECHO_RES} {
    }

    std::string payload;
};
*/
struct ClientStart : public ClientMessage {
    ClientStart(const AppData &appData) : ClientMessage{CLIENT_START}, appData{appData} {
        std::string version = appData.version.getString();

        data.SetObject();
        data.AddMember("appName", rapidjson::Value(appData.appName.c_str(), appData.appName.length(), data.GetAllocator()), data.GetAllocator());
        data.AddMember("version", rapidjson::Value(version.c_str(), version.length(), data.GetAllocator()), data.GetAllocator());
        data.AddMember("msgGroups", convertIntoGroupArray(appData.groups), data.GetAllocator());
    }

    AppData appData;
};

struct ClientClose : public ClientMessage {
    ClientClose() : ClientMessage{CLIENT_CLOSE} {
    }
};








/*




struct ClientError : public RecieveMessage {
    ClientError(moba::JsonItemPtr data) {
        auto o = std::dynamic_pointer_cast<moba::JsonObject>(data);
        errorId = moba::castToString(o->at("errorId"));
        additionalMsg = moba::castToString(o->at("additonalMsg"));
    }

    static std::string getMessageName() {
        return "ERROR";
    }

    std::string errorId;
    std::string additionalMsg;
};

struct ClientShutdown : public RecieveMessage {
    static std::string getMessageName() {
        return "SHUTDOWN";
    }
};

struct ClientReset : public RecieveMessage {
    static std::string getMessageName() {
        return "RESET";
    }
};

struct ClientSelfTesting : public RecieveMessage {
    static std::string getMessageName() {
        return "SELF_TESTING";
    }
};
*/
