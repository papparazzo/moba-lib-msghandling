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
#include <memory>

#include "message.h"
#include "shared.h"

struct ServerMessage : public Message {
    enum MessageName {
        SERVER_NEW_CLIENT_STARTED  = 1,
        SERVER_CLIENT_CLOSED       = 2,
        SERVER_RESET_CLIENT        = 3,
        SERVER_INFO_REQ            = 4,
        SERVER_INFO_RES            = 5,
        SERVER_CON_CLIENTS_REQ     = 6,
        SERVER_CON_CLIENTS_RES     = 7,
        SERVER_SELF_TESTING_CLIENT = 8
    };

    const static std::uint32_t GROUP_ID = SERVER;
};

struct ServerNewClientStarted : public ServerMessage {
    const static std::uint32_t MESSAGE_ID = SERVER_NEW_CLIENT_STARTED;

    ServerNewClientStarted(const rapidjson::Document &d) : endpoint{d} {
    }
    EndpointData endpoint;
};

struct ServerClientClosed : public ServerMessage {
    const static std::uint32_t MESSAGE_ID = SERVER_CLIENT_CLOSED;

    ServerClientClosed(const rapidjson::Document &d) {
        clientId = d.GetInt64();
    }

    long clientId;
};

struct ServerResetClient : public ServerMessage {
    const static std::uint32_t MESSAGE_ID = SERVER_RESET_CLIENT;

    ServerResetClient(long appId) : appId{appId} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetInt64(appId);
        return d;
    }

    long appId;
};

struct ServerInfoReq : public ServerMessage {
    const static std::uint32_t MESSAGE_ID = SERVER_INFO_REQ;
    ServerInfoReq() {
    }
};


struct ServerInfoRes : public ServerMessage {
    const static std::uint32_t MESSAGE_ID = SERVER_INFO_RES;
    ServerInfoRes(const rapidjson::Document &d) {
        appName = d["appName"].GetString();
        version = d["version"].GetString();
        buildDate = d["buildDate"].GetString();
        startTime = d["startTime"].GetString();
        maxClients = d["maxClients"].GetInt();
        connectedClients = d["connectedClients"].GetInt();
        osArch = d["osArch"].GetString();
        osName = d["osName"].GetString();
        osVersion = d["osVersion"].GetString();
        fwType = d["fwType"].GetString();
        fwVersion = d["fwVersion"].GetString();
    }

    std::string appName;
    moba::common::Version version;
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

struct ServerConClientsReq : public ServerMessage {
    const static std::uint32_t MESSAGE_ID = SERVER_CON_CLIENTS_REQ;
    ServerConClientsReq() {
    }
};

struct ServerConClientsRes : public ServerMessage {
    const static std::uint32_t MESSAGE_ID = SERVER_CON_CLIENTS_RES;
    ServerConClientsRes(const rapidjson::Document &d) {
        for(auto &iter : d.GetArray()) {
            endpoints.push_back(EndpointData{iter});
        }
    }
    std::vector<EndpointData> endpoints;
};

struct ServerSelfTestingClient : public ServerMessage {
    const static std::uint32_t MESSAGE_ID = SERVER_SELF_TESTING_CLIENT;

    ServerSelfTestingClient(long appId) : appId{appId} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetInt(appId);
        return d;
    }

    long appId;
};
