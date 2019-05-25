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
#include "shared.h"

struct ClientVoid : public RecieveMessage, public DispatchMessageType<ClientVoid> {
    static std::string getMessageName() {
        return "VOID";
    }
};

struct ClientEchoReq : public DispatchMessageType<ClientEchoReq> {
    ClientEchoReq(const std::string &payload) : payload{payload} {
    }

    static std::string getMessageName() {
        return "ECHO_REQ";
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

    static std::string getMessageName() {
        return "ECHO_RES";
    }

    std::string payload;
};

struct ClientError : public RecieveMessage {
    ClientError(moba::JsonItemPtr data) {
        auto o = std::dynamic_pointer_cast<moba::JsonObject>(data);
        errorId = moba::castToString(o->at("errorId"));
        additionalMsg = moba::castToString(o->at("additonalMsg"));
    }

    static std::string getMessageName() {
        return "ERROR";
    }

    std::string errorId;
    std::string additionalMsg;
};

struct ClientStart : public DispatchMessageType<ClientStart> {
    ClientStart(const AppData &appData) : appData{appData} {
    }

    static std::string getMessageName() {
        return "START";
    }

    virtual moba::JsonItemPtr getData() const override {
        moba::JsonObjectPtr obj(new moba::JsonObject());
        (*obj)["appName"  ] = moba::toJsonStringPtr(appData.appName);
        (*obj)["version"  ] = appData.version.toJsonPtr();
        (*obj)["msgGroups"] = appData.groups;
        return obj;
    }

    AppData appData;
};

struct ClientConnected : public RecieveMessage {
    ClientConnected(moba::JsonItemPtr data) {
        appId = moba::castToInt(data);
    }

    static std::string getMessageName() {
        return "CONNECTED";
    }

    long appId;
};

struct ClientClose : public DispatchMessageType<ClientClose> {
    static std::string getMessageName() {
        return "CLOSE";
    }
};

struct ClientShutdown : public RecieveMessage {
    static std::string getMessageName() {
        return "SHUTDOWN";
    }
};

struct ClientReset : public RecieveMessage {
    static std::string getMessageName() {
        return "RESET";
    }
};

struct ClientSelfTesting : public RecieveMessage {
    static std::string getMessageName() {
        return "SELF_TESTING";
    }
};
