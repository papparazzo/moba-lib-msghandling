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

#include "basemessage.h"
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

    ServerMessage(unsigned char msgId) : Message{SERVER, msgId} {
    }
};

struct ServerNewClientStarted : public ServerMessage {
    ServerNewClientStarted() : ServerMessage{SERVER_NEW_CLIENT_STARTED} {
    }


//    ServerNewClientStarted(moba::JsonItemPtr data) : endpoint{std::dynamic_pointer_cast<moba::JsonObject>(data)} {
//    }
//
//    EndpointData endpoint;

};

struct ServerClientClosed : public ServerMessage {
    ServerClientClosed() : ServerMessage{SERVER_CLIENT_CLOSED} {
    }

//    ServerClientClosed(moba::JsonItemPtr data) {
//        clientId = moba::castToInt(data);
//    }

    int clientId;
};

struct ServerResetClient : public ServerMessage {
    ServerResetClient(long appId) : ServerMessage{SERVER_RESET_CLIENT} {
        data.SetInt(appId);
    }
};

struct ServerInfoReq : public ServerMessage {
    ServerInfoReq() : ServerMessage{SERVER_INFO_REQ} {
    }
};

struct ServerInfoRes : public ServerMessage {

//    ServerInfoRes(moba::JsonItemPtr data) {
//        auto o = std::dynamic_pointer_cast<moba::JsonObject>(data);
//        appName = moba::castToString(o->at("appName"));
//        version = moba::Version{moba::castToString(o->at("version"))};
//        buildDate = moba::castToString(o->at("buildDate"));
//        startTime = moba::castToString(o->at("startTime"));
//        maxClients = moba::castToInt(o->at("maxClients"));
//        connectedClients = moba::castToInt(o->at("connectedClients"));
//        auto a = std::dynamic_pointer_cast<moba::JsonArray>(o->at("supportedMessages"));
//        for(auto iter : *a) {
//            supportedMessages.push_back(moba::castToString(iter));
//        }
//        osArch = moba::castToString(o->at("osArch"));
//        osName = moba::castToString(o->at("osName"));
//        osVersion = moba::castToString(o->at("osVersion"));
//        fwType = moba::castToString(o->at("fwType"));
//        fwVersion = moba::castToString(o->at("fwVersion"));
//    }
//
//    static std::string getMessageName() {
//        return "INFO_RES";
//    }
//
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
};

struct ServerConClientsRes : public ServerMessage {
//
//    ServerConClientsRes(moba::JsonItemPtr data) {
//        auto a = std::dynamic_pointer_cast<moba::JsonArray>(data);
//        for(auto iter : *a) {
//            endpoints.push_back(EndpointData{std::dynamic_pointer_cast<moba::JsonObject>(iter)});
//        }
//    }
//
//    std::vector<EndpointData> endpoints;
//
};

struct ServerSelfTestingClient : public ServerMessage {
    ServerSelfTestingClient(long appId) : ServerMessage{SERVER_SELF_TESTING_CLIENT} {
        data.SetInt(appId);
    }
};
