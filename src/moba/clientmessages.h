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

    explicit ClientEchoReq(std::string payload): payload{std::move(payload)} {
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        return nlohmann::json{payload};
    }

    std::string payload;
};

struct ClientEchoRes: public ClientMessage {
    static constexpr std::uint32_t MESSAGE_ID = CLIENT_ECHO_RES;

    explicit ClientEchoRes(const nlohmann::json &d) {
        payload = d.get<std::string>();
    }

    std::string payload;
};

struct ClientError: public ClientMessage {
    static constexpr std::uint32_t MESSAGE_ID = CLIENT_ERROR;
   
    ClientError(ErrorId errorId, std::string additionalMsg):
    errorId{errorId}, additionalMsg{std::move(additionalMsg)}
    {
    }

    explicit ClientError(const nlohmann::json &d) {
        auto s = d["errorId"].get<std::string>();
        errorId = stringToErrorIdEnum(s);
        additionalMsg = d["additionalMsg"].get<std::string>();
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        return {
            {"errorId", errorIdEnumToString(errorId)},
            {"additonalMsg", additionalMsg},
        };
    }
    
    ErrorId errorId;
    std::string additionalMsg;
};

struct ClientStart: public ClientMessage {
    static constexpr std::uint32_t MESSAGE_ID = CLIENT_START;

    explicit ClientStart(AppData appData): appData{std::move(appData)} {
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        nlohmann::json d;

        d["appName"] = appData.appName;
        d["version"] = appData.version.getString();
        d["msgGroups"] = appData.groups;
        return d;
    }

    AppData appData;
};

struct ClientConnected: public ClientMessage {
    static constexpr std::uint32_t MESSAGE_ID = CLIENT_CONNECTED;

    explicit ClientConnected(const nlohmann::json &d) {
        appId = d.get<int>();
    }

    long appId;
};

struct ClientClose: public ClientMessage {
    static constexpr std::uint32_t MESSAGE_ID = CLIENT_CLOSE;
};

struct ClientShutdown: public ClientMessage {

    explicit ClientShutdown(const nlohmann::json &) {
    }
    static constexpr std::uint32_t MESSAGE_ID = CLIENT_SHUTDOWN;
};

struct ClientReset: public ClientMessage {
    static constexpr std::uint32_t MESSAGE_ID = CLIENT_RESET;
};

struct ClientSelfTesting: public ClientMessage {
    static constexpr std::uint32_t MESSAGE_ID = CLIENT_SELF_TESTING;
};

