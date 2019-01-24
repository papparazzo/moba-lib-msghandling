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

#include "basemessage.h"
#include <moba/version.h>

class ClientVoid : public RecieveMessage, public DispatchMessage {
    public:
        virtual std::string getMessageName() const override {
            return "CLIENT_VOID";
        }
};

class ClientEchoReq : public DispatchMessage {
    public:
        ClientEchoReq(const std::string &payload) : payload{payload} {
        }

        virtual std::string getMessageName() const override {
            return "CLIENT_ECHO_REQ";
        }

        virtual moba::JsonItemPtr getData() const override {
            return moba::toJsonStringPtr(payload);
        }

    protected:
        std::string payload;
};

class ClientEchoRes : public RecieveMessage {
    public:
        ClientEchoRes(moba::JsonItemPtr data) {
            payload = moba::castToString(data);
        }

        virtual std::string getMessageName() const override {
            return "CLIENT_ECHO_RES";
        }

        std::string getPayload() {
            return payload;
        }

    protected:
        std::string payload;
};

class ClientError : public RecieveMessage {
    public:
        ClientError(moba::JsonItemPtr data) {
            moba::JsonObjectPtr o = boost::dynamic_pointer_cast<moba::JsonObject>(data);
            errorId = moba::castToString(o->at("errorId"));
            additionalMsg = moba::castToString(o->at("additonalMsg"));
        }

        virtual std::string getMessageName() const override {
            return "CLIENT_ERROR";
        }

        std::string getErrorId() {
            return errorId;
        }

        std::string getAdditionalMsg() {
            return additionalMsg;
        }

    protected:
        std::string errorId;
        std::string additionalMsg;
};

class ClientStart : public DispatchMessage {
    public:
        ClientStart(const std::string &appName, const moba::Version &version, moba::JsonArrayPtr groups) :
        appName{appName}, version{version}, groups{groups} {
        }

        virtual std::string getMessageName() const override {
            return "CLIENT_START";
        }

        virtual moba::JsonItemPtr getData() const override {
            moba::JsonObjectPtr obj(new moba::JsonObject());
            (*obj)["appName"  ] = moba::toJsonStringPtr(appName);
            (*obj)["version"  ] = version.toJsonPtr();
            (*obj)["msgGroups"] = groups;
            return obj;
        }

    protected:
        std::string appName;
        moba::Version version;
        moba::JsonArrayPtr groups;
};

class ClientConnected : public RecieveMessage {
    public:
        ClientConnected(moba::JsonItemPtr data) {
            appId = moba::castToInt(data);
        }

        virtual std::string getMessageName() const override {
            return "CLIENT_CONNECTED";
        }

        long getAppId() {
            return appId;
        }

    protected:
        long appId;
};

struct ClientClose : public DispatchMessage {
    virtual std::string getMessageName() const override {
        return "CLIENT_CLOSE";
    }
};

struct ClientShutdown : public RecieveMessage {
    virtual std::string getMessageName() {
        return "CLIENT_SHUTDOWN";
    }
};

struct ClientReset : public RecieveMessage {
    virtual std::string getMessageName() {
        return "CLIENT_RESET";
    }
};

struct ClientSelfTesting : public RecieveMessage {
    virtual std::string getMessageName() {
        return "CLIENT_SELF_TESTING";
    }
};
