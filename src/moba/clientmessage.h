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

    const static std::uint32_t GROUP_ID = CLIENT;
};

struct ClientVoid : public ClientMessage {
    const static std::uint32_t MESSAGE_ID = CLIENT_VOID;
};

struct ClientEchoReq : public ClientMessage {
    const static std::uint32_t MESSAGE_ID = CLIENT_ECHO_REQ;

    ClientEchoReq(const std::string &payload) : payload{payload} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetString(payload.c_str(), payload.length(), d.GetAllocator());
        return d;
    }

    std::string payload;
};

struct ClientEchoRes : public ClientMessage {
    const static std::uint32_t MESSAGE_ID = CLIENT_ECHO_RES;

    ClientEchoRes(const rapidjson::Document &d) {
        payload = d.GetString();
    }

    std::string payload;
};

struct ClientError : public ClientMessage {
    const static std::uint32_t MESSAGE_ID = CLIENT_ERROR;

    ClientError(const rapidjson::Document &d) {
        errorId = d["errorId"].GetString();
        additionalMsg = d["additonalMsg"].GetString();
    }

    std::string errorId;
    std::string additionalMsg;
};

struct ClientStart : public ClientMessage {
    const static std::uint32_t MESSAGE_ID = CLIENT_START;

    ClientStart(const AppData &appData) : appData{appData} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        std::string version = appData.version.getString();
        d.SetObject();
        d.AddMember("appName", rapidjson::Value(appData.appName.c_str(), appData.appName.length(), d.GetAllocator()), d.GetAllocator());
        d.AddMember("version", rapidjson::Value(version.c_str(), version.length(), d.GetAllocator()), d.GetAllocator());
        d.AddMember("msgGroups", convertIntoGroupArray(appData.groups), d.GetAllocator());
        return d;
    }

    AppData appData;
};

struct ClientConnected : public ClientMessage {
    const static std::uint32_t MESSAGE_ID = CLIENT_CONNECTED;

    ClientConnected(const rapidjson::Document &d) {
        appId = d.GetInt();
    }

    long appId;
};

struct ClientClose : public ClientMessage {
    const static std::uint32_t MESSAGE_ID = CLIENT_CLOSE;
};

struct ClientShutdown : public ClientMessage {
    const static std::uint32_t MESSAGE_ID = CLIENT_SHUTDOWN;
};

struct ClientReset : public ClientMessage {
    const static std::uint32_t MESSAGE_ID = CLIENT_RESET;
};

struct ClientSelfTesting : public ClientMessage {
    const static std::uint32_t MESSAGE_ID = CLIENT_SELF_TESTING;
};

