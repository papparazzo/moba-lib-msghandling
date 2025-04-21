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

#include "message.h"
#include "shared.h"

struct ServerMessage : Message {
    enum MessageName {
        SERVER_NEW_CLIENT_STARTED = 1,
        SERVER_CLIENT_CLOSED = 2,
        SERVER_RESET_CLIENT = 3,
        SERVER_INFO_REQ = 4,
        SERVER_INFO_RES = 5,
        SERVER_CON_CLIENTS_REQ = 6,
        SERVER_CON_CLIENTS_RES = 7,
        SERVER_SELF_TESTING_CLIENT = 8
    };

    static constexpr std::uint32_t GROUP_ID = SERVER;
};

struct ServerNewClientStarted final : ServerMessage {
    static constexpr std::uint32_t MESSAGE_ID = SERVER_NEW_CLIENT_STARTED;

    explicit ServerNewClientStarted(const nlohmann::json &d) : endpoint{d} {
    }

    EndpointData endpoint;
};

struct ServerClientClosed final : ServerMessage {
    static constexpr std::uint32_t MESSAGE_ID = SERVER_CLIENT_CLOSED;

    explicit ServerClientClosed(const nlohmann::json &d) {
        clientId = d.get<long>();
    }

    long clientId;
};

struct ServerResetClient final : ServerMessage {
    static constexpr std::uint32_t MESSAGE_ID = SERVER_RESET_CLIENT;

    explicit ServerResetClient(const long appId) : appId{appId} {
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        return appId;
    }

    long appId;
};

struct ServerInfoReq final : ServerMessage {
    static constexpr std::uint32_t MESSAGE_ID = SERVER_INFO_REQ;

    ServerInfoReq() = default;
};

struct ServerInfoRes final : ServerMessage {
    static constexpr std::uint32_t MESSAGE_ID = SERVER_INFO_RES;

    explicit ServerInfoRes(const nlohmann::json &d) {
        appName = d["appName"].get<std::string>();
        version = d["version"].get<std::string>();
        buildDate = d["buildDate"].get<std::string>();
        startTime = d["startTime"].get<std::string>();
        maxClients = d["maxClients"].get<int>();
        connectedClients = d["connectedClients"].get<int>();
        osArch = d["osArch"].get<std::string>();
        osName = d["osName"].get<std::string>();
        osVersion = d["osVersion"].get<std::string>();
        fwType = d["fwType"].get<std::string>();
        fwVersion = d["fwVersion"].get<std::string>();
    }

    std::string appName;
    moba::Version version;
    std::string buildDate;
    std::string startTime;
    int maxClients;
    int connectedClients;
    std::vector<std::string> supportedMessages;
    std::string osArch;
    std::string osName;
    std::string osVersion;
    std::string fwType;
    std::string fwVersion;

};

struct ServerConClientsReq final : ServerMessage {
    static constexpr std::uint32_t MESSAGE_ID = SERVER_CON_CLIENTS_REQ;

    ServerConClientsReq() = default;
};

struct ServerConClientsRes final : ServerMessage {
    static constexpr std::uint32_t MESSAGE_ID = SERVER_CON_CLIENTS_RES;

    explicit ServerConClientsRes(const nlohmann::json &d) {
        for (auto &iter: d) {
            endpoints.emplace_back(iter);
        }
    }

    std::vector<EndpointData> endpoints;
};

struct ServerSelfTestingClient final : ServerMessage {
    static constexpr std::uint32_t MESSAGE_ID = SERVER_SELF_TESTING_CLIENT;

    explicit ServerSelfTestingClient(const long appId) : appId{appId} {
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        return appId;
    }

    long appId;
};
