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
        groups = std::dynamic_pointer_cast<moba::JsonArray>(appData->at("msgGroups"));
    }

    std::string appName;
    moba::Version version;
    moba::JsonArrayPtr groups;
};

struct EndpointData {
    EndpointData(
        const AppData &appInfo, long appId, const std::string &startTime, const std::string &addr, long port
    ) : appInfo{appInfo}, appId{appId}, startTime{startTime}, addr{addr} {
    }

    EndpointData(moba::JsonObjectPtr appData) {
        appId = moba::castToInt(appData->at("appID"));
        addr = moba::castToString(appData->at("addr"));
        port = moba::castToInt(appData->at("port"));
        startTime = moba::castToString(appData->at("startTime"));

        auto oi = std::dynamic_pointer_cast<moba::JsonObject>(appData->at("appInfo"));
        appInfo = AppData{oi};
    }

    AppData     appInfo;
    long        appId;
    std::string startTime;
    std::string addr;
    long        port;
};

struct TrackLayoutData {
    TrackLayoutData(
        int id, const std::string &name, const std::string &description,
        const std::string &created, const std::string &modified, int locked
    ) : id{id}, name{name}, description{description}, created{created}, modified{modified}, locked{locked} {

    }

    TrackLayoutData(moba::JsonObjectPtr appData) {
        id = moba::castToInt(appData->at("id"));
        name = moba::castToString(appData->at("name"));
        description = moba::castToString(appData->at("description"));
        created = moba::castToString(appData->at("created"));
        modified = moba::castToString(appData->at("modified"));
        locked = moba::castToInt(appData->at("locked"));
    }

	int id;
    std::string name;
    std::string description;
    std::string created;
    std::string modified;
    int locked;
};

struct TrackLayoutSymbolData {
	int id;
    int xPos;
    int yPos;
	int symbol;
};

struct SpecificLayoutData {
    SpecificLayoutData(moba::JsonObjectPtr appData) {
        id = moba::castToInt(appData->at("id"));
        //groups = std::dynamic_pointer_cast<moba::JsonArray>(appData->at("msgGroups"));

    }

    int id;

    std::vector<TrackLayoutSymbolData> symbols;
};

struct Contact {
    Contact(int modulAddr = 0, int contactNb = 0) : modulAddr{modulAddr}, contactNb{contactNb} {
    }

    Contact(moba::JsonObjectPtr data) {
        modulAddr = moba::castToInt(data->at("modulAddr"));
        contactNb = moba::castToInt(data->at("contactNb"));
    }

    int modulAddr;
    int contactNb;
};

struct ContactTrigger {
    ContactTrigger(
        int modulAddr, int contactNb, bool state, int time
    ) : contact{modulAddr, contactNb}, state{state}, time{time} {

    }

    Contact contact;
	bool state;
	int time;
};

struct BrakeVectorContact {
    BrakeVectorContact(moba::JsonObjectPtr data) {
        auto oi = std::dynamic_pointer_cast<moba::JsonObject>(data->at("contact"));
        contact = Contact{oi};
        locId = moba::castToInt(data->at("locId"));
    }

    Contact contact;
    int locId;
};
