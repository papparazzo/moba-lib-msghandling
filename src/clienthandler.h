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

#include <moba/version.h>
#include <memory>
#include <string>

#include "basemessage.h"

struct ClientVoid : public RecieveMessage, public DispatchMessage {
    virtual std::string getMessageName() const override {
        return "CLIENT_VOID";
    }
};

struct ClientEchoReq : public DispatchMessage {
    ClientEchoReq(const std::string &payload) : payload{payload} {
    }

    virtual std::string getMessageName() const override {
        return "CLIENT_ECHO_REQ";
    }

    virtual moba::JsonItemPtr getData() const override {
        return moba::toJsonStringPtr(payload);
    }

    std::string payload;
};

struct ClientEchoRes : public RecieveMessage {
    ClientEchoRes(moba::JsonItemPtr data) {
        payload = moba::castToString(data);
    }

    virtual std::string getMessageName() const override {
        return "CLIENT_ECHO_RES";
    }

    std::string payload;
};

struct ClientError : public RecieveMessage {
    ClientError(moba::JsonItemPtr data) {
        auto o = boost::dynamic_pointer_cast<moba::JsonObject>(data);
        errorId = moba::castToString(o->at("errorId"));
        additionalMsg = moba::castToString(o->at("additonalMsg"));
    }

    virtual std::string getMessageName() const override {
        return "CLIENT_ERROR";
    }

    std::string errorId;
    std::string additionalMsg;
};

struct ClientStart : public DispatchMessage {
    ClientStart(
        const std::string &appName, const moba::Version &version, moba::JsonArrayPtr groups
    ) : appName{appName}, version{version}, groups{groups} {
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

    std::string appName;
    moba::Version version;
    moba::JsonArrayPtr groups;
};

struct ClientConnected : public RecieveMessage {
    ClientConnected(moba::JsonItemPtr data) {
        appId = moba::castToInt(data);
    }

    virtual std::string getMessageName() const override {
        return "CLIENT_CONNECTED";
    }

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
