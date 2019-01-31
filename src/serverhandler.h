/*
 *  Project:    moba-common
 *
 *  Copyright (C) 2016 Stefan Paproth <pappi-@gmx.de>
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

    virtual std::string getMessageName() const override {
        return "SERVER_MAX_CLIENT_COUNT";
    }

    int maxClientCount;
};

struct ServerNewClientStarted : public RecieveMessage {
    ServerNewClientStarted(moba::JsonItemPtr data) {
        auto o = std::dynamic_pointer_cast<moba::JsonObject>(data);
        appId = moba::castToInt(o->at("appID"));
        addr = moba::castToString(o->at("addr"));
        port = moba::castToInt(o->at("port"));
        upTime = moba::castToString(o->at("upTime"));

        auto oi = std::dynamic_pointer_cast<moba::JsonObject>(o->at("appInfo"));
        appName = moba::castToString(oi->at("appName"));
        version = moba::castToString(oi->at("version"));
    }

    virtual std::string getMessageName() const override {
        return "SERVER_NEW_CLIENT_STARTED";
    }

    int appId;
    int port;

    std::string addr;
    std::string upTime;

    std::string appName;
    std::string version;
};

struct ServerClientClosed : public RecieveMessage {
    ServerClientClosed(moba::JsonItemPtr data) {
        clientId = moba::castToInt(data);
    }

    virtual std::string getMessageName() const override {
        return "SERVER_CLIENT_CLOSED";
    }

    int clientId;
};

struct ServerResetClient : public DispatchMessage {
    ServerResetClient(long appId) : appId{appId} {
    }

    virtual std::string getMessageName() const override {
        return "SERVER_RESET_CLIENT";
    }

    virtual moba::JsonItemPtr getData() const override {
        return moba::toJsonNumberPtr(appId);
    }

    long appId;
};

struct ServerInfoReq : public DispatchMessage {
    virtual std::string getMessageName() const override {
        return "SERVER_INFO_REQ";
    }
};

struct ServerInfoRes : public RecieveMessage {
    ServerInfoRes(moba::JsonItemPtr data) {
        auto o = std::dynamic_pointer_cast<moba::JsonObject>(data);
        appName = moba::castToString(o->at("appName"));
        version = moba::Version{moba::castToString(o->at("version"))};
        buildDate = moba::castToString(o->at("buildDate"));
        startTime = moba::castToString(o->at("startTime"));
        upTime = moba::castToString(o->at("upTime"));
        maxClients = moba::castToInt(o->at("maxClients"));
        connectedClients = moba::castToInt(o->at("connectedClients"));
        supportedMessages = moba::castToString(o->at("supportedMessages"));
        osArch = moba::castToString(o->at("osArch"));
        osName = moba::castToString(o->at("osName"));
        osVersion = moba::castToString(o->at("osVersion"));
        fwType = moba::castToString(o->at("fwType"));
        fwVersion = moba::castToString(o->at("fwVersion"));
    }

    virtual std::string getMessageName() const override {
        return "SERVER_INFO_RES";
    }

    std::string appName;
    moba::Version version;
    std::string buildDate;
    std::string startTime;
    std::string upTime;
    int maxClients;
    int connectedClients;
    std::string supportedMessages;
    std::string osArch;
    std::string osName;
    std::string osVersion;
    std::string fwType;
    std::string fwVersion;
};

struct ServerConClientsReq : public DispatchMessage {
    virtual std::string getMessageName() const override {
        return "SERVER_CON_CLIENTS_REQ";
    }
};

struct ServerConClientsRes : public RecieveMessage {
    ServerClientClosed(moba::JsonItemPtr data) {
        clientId = moba::castToInt(data);
    }

    virtual std::string getMessageName() const override {
        return "SERVER_CON_CLIENTS_RES";
    }

    int clientId;
};

struct ServerResetClient : public DispatchMessage {
    ServerResetClient(long appId) : appId{appId} {
    }

    virtual std::string getMessageName() const override {
        return "SERVER_SELF_TESTING_CLIENT";
    }

    virtual moba::JsonItemPtr getData() const override {
        return moba::toJsonNumberPtr(appId);
    }

    long appId;
};
