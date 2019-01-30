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

class ServerMaxClientCount : public RecieveMessage {
    public:
        ServerMaxClientCount(moba::JsonItemPtr data) {
            maxClientCount = moba::castToInt(data);
        }

        virtual std::string getMessageName() const override {
            return "SERVER_MAX_CLIENT_COUNT";
        }

        std::string getMaxClientCount() {
            return maxClientCount;
        }

    protected:
        int maxClientCount;
};

class ServerNewClientStarted : public RecieveMessage {
    public:
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

    protected:
        int appId;
        int port;

        std::string addr;
        std::string upTime;

        std::string appName;
        std::string version;
};

class ServerClientClosed : public RecieveMessage {
    public:
        ServerClientClosed(moba::JsonItemPtr data) {
            clientId = moba::castToInt(data);
        }

        virtual std::string getMessageName() const override {
            return "SERVER_CLIENT_CLOSED";
        }

        int getClientId() {
            return clientId;
        }

    protected:
        int clientId;
};

class ServerResetClient : public DispatchMessage {
    public:
        ServerResetClient(long appId) : appId{appId} {
        }

        virtual std::string getMessageName() const override {
            return "SERVER_RESET_CLIENT";
        }

        virtual moba::JsonItemPtr getData() const override {
            return moba::toJsonNumberPtr(appId);
        }

    protected:
        long appId;
};

class ServerInfoReq : public DispatchMessage {
    public:
        virtual std::string getMessageName() const override {
            return "SERVER_INFO_REQ";
        }
};



/*


SERVER_INFO_RES
SERVER_CON_CLIENTS_REQ
SERVER_CON_CLIENTS_RES
SERVER_SELF_TESTING_CLIENT



            void sendSelfTestingClient(long id) {msgep->sendMsg(Message::MT_SELF_TESTING_CLIENT, toJsonNumberPtr(id));}

            void sendServerInfoReq() {msgep->sendMsg(Message::MT_SERVER_INFO_REQ);}

            void sendConClientsReq() {msgep->sendMsg(Message::MT_CON_CLIENTS_REQ);}

*/