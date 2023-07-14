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
#include "message.h"
#include "shared.h"
#include "enumerrorid.h"

struct ClientMessage: public Message {
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

    static constexpr std::uint32_t GROUP_ID = CLIENT;
};

struct ClientVoid: public ClientMessage {
    static constexpr std::uint32_t MESSAGE_ID = CLIENT_VOID;
};

struct ClientEchoReq: public ClientMessage {
    static constexpr std::uint32_t MESSAGE_ID = CLIENT_ECHO_REQ;

    ClientEchoReq(const std::string &payload): payload{payload} {
    }

    nlohmann::json getJsonDocument() const override {
        return nlohmann::json{payload};
    }

    std::string payload;
};

struct ClientEchoRes: public ClientMessage {
    static constexpr std::uint32_t MESSAGE_ID = CLIENT_ECHO_RES;

    ClientEchoRes(const nlohmann::json &d) {
        payload = d.get<std::string>();
    }

    std::string payload;
};

struct ClientError: public ClientMessage {
    static constexpr std::uint32_t MESSAGE_ID = CLIENT_ERROR;
   
    ClientError(ErrorId errorId, const std::string &additionalMsg): 
        errorId{errorId}, additionalMsg{additionalMsg} 
    {
    }

    ClientError(const nlohmann::json &d) {
        auto s = d["errorId"].get<std::string>();
        errorId = stringToErrorIdEnum(s);
        additionalMsg = d["additonalMsg"].get<std::string>();
    }

    nlohmann::json getJsonDocument() const override {
        nlohmann::json d;
        /*
        d.SetObject();
        auto cf = errorIdEnumToString(errorId);
        d.AddMember("errorId", rapidjson::Value(cf.c_str(), cf.length(), d.GetAllocator()), d.GetAllocator());
        d.AddMember("additonalMsg", rapidjson::Value(additionalMsg.c_str(), additionalMsg.length(), d.GetAllocator()), d.GetAllocator());
        */
        return d;
    }
    
    ErrorId errorId;
    std::string additionalMsg;
};

struct ClientStart: public ClientMessage {
    static constexpr std::uint32_t MESSAGE_ID = CLIENT_START;

    ClientStart(const AppData &appData): appData{appData} {
    }
/*
    nlohmann::json getJsonDocument() const override {
        nlohmann::json d;
        std::string version = appData.version.get<std::string>();
        d.SetObject();
        d.AddMember("appName", rapidjson::Value(appData.appName.c_str(), appData.appName.length(), d.GetAllocator()), d.GetAllocator());
        d.AddMember("version", rapidjson::Value(version.c_str(), version.length(), d.GetAllocator()), d.GetAllocator());

        rapidjson::Value g(rapidjson::kArrayType);

        for(auto &v : appData.groups) {
            g.PushBack(v, d.GetAllocator());
        }
        d.AddMember("msgGroups", g, d.GetAllocator());
        return d;
    }
*/

    AppData appData;
};

struct ClientConnected: public ClientMessage {
    static constexpr std::uint32_t MESSAGE_ID = CLIENT_CONNECTED;
  
    ClientConnected(const nlohmann::json &d) {
        appId = d.get<int>();
    }

    long appId;
};

struct ClientClose: public ClientMessage {
    static constexpr std::uint32_t MESSAGE_ID = CLIENT_CLOSE;
};

struct ClientShutdown: public ClientMessage {

    ClientShutdown(const nlohmann::json &d) {
    }
    static constexpr std::uint32_t MESSAGE_ID = CLIENT_SHUTDOWN;
};

struct ClientReset: public ClientMessage {
    static constexpr std::uint32_t MESSAGE_ID = CLIENT_RESET;
};

struct ClientSelfTesting: public ClientMessage {
    static constexpr std::uint32_t MESSAGE_ID = CLIENT_SELF_TESTING;
};

