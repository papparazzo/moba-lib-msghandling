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

#include <memory>
#include <set>
#include <vector>
#include <map>
#include <utility>
#include <moba-common/exception.h>
#include <moba-common/version.h>
#include "message.h"
#include "driving_direction.h"

#include "rapidjson/document.h"
#include "enumswitchstand.h"

using MessageGroups = std::set<Message::MessageGroup>;

struct AppData {

    AppData() {
    }

    AppData(
        const std::string &appName, const moba::Version &version, const MessageGroups &groups
    ) : appName{appName}, version{version}, groups{groups} {
    }

    template <typename T>
    AppData(const rapidjson::GenericValue<T> &d) {
        appName = d["appName"].GetString();
        version = d["version"].GetString();
        for(auto &v : d["msgGroups"].GetArray()) {
            groups.insert(static_cast<Message::MessageGroup>(v.GetInt()));
        }
    }

    std::string appName;
    moba::Version version;
    MessageGroups groups;
};

struct EndpointData {
    EndpointData(
        const AppData &appInfo, long appId, const std::string &startTime, const std::string &addr, long port
    ) : appInfo{appInfo}, appId{appId}, startTime{startTime}, addr{addr} {
    }

    template <typename T>
    EndpointData(const rapidjson::GenericValue<T> &d) {
        appId = d["appID"].GetInt();
        addr = d["addr"].GetString();
        port = d["port"].GetInt();
        startTime = d["startTime"].GetString();
        appInfo = AppData{d["appInfo"]};
    }

    AppData     appInfo;
    long        appId;
    std::string startTime;
    std::string addr;
    long        port;
};

struct TrackLayoutData {
    TrackLayoutData(
        int id, const std::string &name, const std::string &description, const std::string &created, const std::string &modified, bool active, int locked
    ) : id{id}, name{name}, description{description}, created{created}, modified{modified}, active{active}, locked{locked} {

    }

    TrackLayoutData(
        const std::string &name, const std::string &description, bool active
    ) : name{name}, description{description}, active{active} {

    }

    template <typename T>
    TrackLayoutData(const rapidjson::GenericValue<T> &d) {
        id = d["id"].GetInt();
        name = d["name"].GetString();
        description = d["description"].GetString();
        created = d["created"].GetString();
        modified = d["modified"].GetString();
        active = d["active"].GetBool();
        locked = d["locked"].GetInt();
    }

	int id;
    std::string name;
    std::string description;
    std::string created;
    std::string modified;
    bool active;
    int locked;
};

struct TrackLayoutSymbol {
    TrackLayoutSymbol() {
    }
    TrackLayoutSymbol(int symbol): id{0}, symbol{symbol} {
    }
    TrackLayoutSymbol(int id, int symbol): id{id}, symbol{symbol} {
    }
    int id;
    int symbol;
};

// Thanks to https://stackoverflow.com/a/45395204
using IntPair = std::pair<int, int>;

using Symbols    = std::map<IntPair, TrackLayoutSymbol>;
using SymbolsPtr = std::shared_ptr<Symbols>;

struct SpecificLayoutData {
    SpecificLayoutData() {
        symbols = std::make_shared<Symbols>();
    }

    SpecificLayoutData(const rapidjson::Document &d) {
        symbols = std::make_shared<Symbols>();
        id = d["id"].GetInt();

        for(auto &iter : d["symbols"].GetArray()) {
            (*symbols)[{
                iter["xPos"].GetInt(),
                iter["yPos"].GetInt()
            }] = TrackLayoutSymbol(
                iter["id"].GetInt(),
                iter["symbol"].GetInt()
            );
        }
    }

    int id;
    SymbolsPtr symbols;
};

struct ContactData {
    ContactData(std::uint16_t modulAddr = 0, std::uint16_t contactNb = 0) : modulAddr{modulAddr}, contactNb{contactNb} {
    }

    template <typename T>
    ContactData(const rapidjson::GenericValue<T> &d) {
        modulAddr = d["modulAddr"].GetInt();
        contactNb = d["contactNb"].GetInt();
    }

    friend bool operator<(const ContactData &l, const ContactData &r) {
        if(l.modulAddr < r.modulAddr) {
            return true;
        }
        if(l.modulAddr == r.modulAddr && l.contactNb < r.contactNb) {
            return true;
        }
        return false;
    }

    std::uint16_t modulAddr;
    std::uint16_t contactNb;
};

struct ContactTriggerData {
    ContactTriggerData(
        std::uint16_t modulAddr, std::uint16_t contactNb, bool state, int time
    ) : contactData{modulAddr, contactNb}, state{state}, time{time} {

    }

    template <typename T>
    ContactTriggerData(const rapidjson::GenericValue<T> &d): contactData{d["contact"]} {
        state = d["state"].GetBool();
        time = d["time"].GetInt();
    }

    ContactData contactData;
	bool        state;
	int         time;
};

struct BlockContactData {
    template <typename T>
    BlockContactData(const rapidjson::GenericValue<T> &d): brakeTriggerContact{d["brakeTriggerContact"]}, blockContact{d["blockContact"]} {
        if(!d["trainId"].IsNull()) {
            trainId = d["trainId"].GetInt();
        }
        
        id = d["id"].GetInt();
    }

    ContactData brakeTriggerContact;
    ContactData blockContact;
    int trainId;
    
    // ToDo Consider to make trainId optional
    //std::optional<int> trainId;
    int id;
};

struct SwitchStandData {
    SwitchStandData() {
    }

    template <typename T>
    SwitchStandData(const rapidjson::GenericValue<T> &d) {
        id = d["id"].GetInt();
        switchStand = stringToSwitchStandEnum(d["switchStand"].GetString());
    }
    SwitchStand switchStand;
    int id;
};

struct BrakeVectorContact {
    BrakeVectorContact(ContactData contact, int localId = 0) : contact{contact}, localId{localId} {
    }

    template <typename T>
    BrakeVectorContact(const rapidjson::GenericValue<T> &d) {
        contact = ContactData{d["contact"]};
        localId = d["localId"].GetInt();
    }

    ContactData contact;
    int localId;
};

struct SwitchingOutput {
    SwitchingOutput(std::uint32_t localId, bool differ): localId{localId}, differ{differ} {
        
    }

    template <typename T>
    SwitchingOutput(const rapidjson::GenericValue<T> &d) {
        localId = d["localId"].GetInt();
        differ = d["differ"].GetBool();
    }
    
    std::uint32_t localId;
    bool differ;
};

using SwitchingOutputs = std::vector<SwitchingOutput>;
