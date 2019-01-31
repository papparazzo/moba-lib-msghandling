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

#include <moba/jsonabstractitem.h>
#include <memory>

struct AppData {
    AppData(
        const std::string &appName, const moba::Version &version, moba::JsonArrayPtr groups
    ) : appName{appName}, version{version}, groups{groups} {
    }

    AppData(moba::JsonObjectPtr appData) {
        appName = moba::castToString(appData->at("appName"));
        version = moba::castToString(appData->at("version"));
        groups = std::dynamic_pointer_cast<moba::JsonArray>(appData->at("msgGroups"));
    }

    std::string appName;
    moba::Version version;
    moba::JsonArrayPtr groups;

};

struct EndpointData {

    AppData     appInfo;
    long        appID;
    std::string upTime;
    std::string addr;
    long        port;
};


/*
        ServerNewClientStarted(moba::JsonItemPtr data) {
            auto o = std::dynamic_pointer_cast<moba::JsonObject>(data);
            appId = moba::castToInt(o->at("appID"));
            addr = moba::castToString(o->at("addr"));
            port = moba::castToInt(o->at("port"));
            upTime = moba::castToString(o->at("upTime"));

 */