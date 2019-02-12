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

#include <moba/jsonabstractitem.h>

#include "basemessage.h"
#include "shared.h"

struct ServerMaxClientCount : public RecieveMessage {
    ServerMaxClientCount(moba::JsonItemPtr data) {
        maxClientCount = moba::castToInt(data);
    }

    static std::string getMessageName() {
        return "SERVER_MAX_CLIENT_COUNT";
    }

    int maxClientCount;
};

struct ServerNewClientStarted : public RecieveMessage {
    ServerNewClientStarted(moba::JsonItemPtr data) : endpoint{boost::dynamic_pointer_cast<moba::JsonObject>(data)} {
    }

    static std::string getMessageName() {
        return "SERVER_NEW_CLIENT_STARTED";
    }

    EndpointData endpoint;
};

struct ServerClientClosed : public RecieveMessage {
    ServerClientClosed(moba::JsonItemPtr data) {
        clientId = moba::castToInt(data);
    }

    static std::string getMessageName() {
        return "SERVER_CLIENT_CLOSED";
    }

    int clientId;
};

struct ServerResetClient : public DispatchMessageType<ServerResetClient> {
    ServerResetClient(long appId) : appId{appId} {
    }

    static std::string getMessageName() {
        return "SERVER_RESET_CLIENT";
    }

    virtual moba::JsonItemPtr getData() const override {
        return moba::toJsonNumberPtr(appId);
    }

    long appId;
};

struct ServerInfoReq : public DispatchMessageType<ServerInfoReq> {
    static std::string getMessageName() {
        return "SERVER_INFO_REQ";
    }
};

struct ServerInfoRes : public RecieveMessage {
    ServerInfoRes(moba::JsonItemPtr data) {
        auto o = boost::dynamic_pointer_cast<moba::JsonObject>(data);
        appName = moba::castToString(o->at("appName"));
        version = moba::Version{moba::castToString(o->at("version"))};
        buildDate = moba::castToString(o->at("buildDate"));
        startTime = moba::castToString(o->at("startTime"));
        upTime = moba::castToString(o->at("upTime"));
        maxClients = moba::castToInt(o->at("maxClients"));
        connectedClients = moba::castToInt(o->at("connectedClients"));
        auto a = boost::dynamic_pointer_cast<moba::JsonArray>(o->at("supportedMessages"));
        for(auto iter : *a) {
            supportedMessages.push_back(moba::castToString(iter));
        }
        osArch = moba::castToString(o->at("osArch"));
        osName = moba::castToString(o->at("osName"));
        osVersion = moba::castToString(o->at("osVersion"));
        fwType = moba::castToString(o->at("fwType"));
        fwVersion = moba::castToString(o->at("fwVersion"));
    }

    static std::string getMessageName() {
        return "SERVER_INFO_RES";
    }

    std::string appName;
    moba::Version version;
    std::string buildDate;
    std::string startTime;
    std::string upTime;
    int maxClients;
    int connectedClients;
    std::vector<std::string> supportedMessages;
    std::string osArch;
    std::string osName;
    std::string osVersion;
    std::string fwType;
    std::string fwVersion;
};

struct ServerConClientsReq : public DispatchMessageType<ServerConClientsReq> {
    static std::string getMessageName() {
        return "SERVER_CON_CLIENTS_REQ";
    }
};

struct ServerConClientsRes : public RecieveMessage {
    ServerConClientsRes(moba::JsonItemPtr data) {
        auto a = boost::dynamic_pointer_cast<moba::JsonArray>(data);
        for(auto iter : *a) {
            endpoints.push_back(EndpointData{boost::dynamic_pointer_cast<moba::JsonObject>(iter)});
        }
    }

    static std::string getMessageName() {
        return "SERVER_CON_CLIENTS_RES";
    }

    std::vector<EndpointData> endpoints;
};

struct ServerSelfTestingClient : public DispatchMessageType<ServerSelfTestingClient> {
    ServerSelfTestingClient(long appId) : appId{appId} {
    }

    static std::string getMessageName() {
        return "SERVER_SELF_TESTING_CLIENT";
    }

    virtual moba::JsonItemPtr getData() const override {
        return moba::toJsonNumberPtr(appId);
    }

    long appId;
};
