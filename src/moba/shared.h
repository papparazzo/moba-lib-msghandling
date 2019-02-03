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
    AppData() {
    }

    AppData(
        const std::string &appName, const moba::Version &version, moba::JsonArrayPtr groups
    ) : appName{appName}, version{version}, groups{groups} {
    }

    AppData(moba::JsonObjectPtr appData) {
        appName = moba::castToString(appData->at("appName"));
        version = moba::castToString(appData->at("version"));
        groups = boost::dynamic_pointer_cast<moba::JsonArray>(appData->at("msgGroups"));
    }

    std::string appName;
    moba::Version version;
    moba::JsonArrayPtr groups;

};

struct EndpointData {
    EndpointData(
        const AppData &appInfo, long appId, const std::string &upTime, const std::string &addr, long port
    ) : appInfo{appInfo}, appId{appId}, upTime{upTime}, addr{addr} {
    }

    EndpointData(moba::JsonObjectPtr appData) {
        appId = moba::castToInt(appData->at("appID"));
        addr = moba::castToString(appData->at("addr"));
        port = moba::castToInt(appData->at("port"));
        upTime = moba::castToString(appData->at("upTime"));

        auto oi = boost::dynamic_pointer_cast<moba::JsonObject>(appData->at("appInfo"));
        appInfo = AppData{oi};
    }

    AppData     appInfo;
    long        appId;
    std::string upTime;
    std::string addr;
    long        port;
};
