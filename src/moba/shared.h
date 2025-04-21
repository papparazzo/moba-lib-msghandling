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
#include <utility>
#include <vector>
#include <map>
#include <utility>
#include <moba-common/exception.h>
#include <moba-common/version.h>
#include <moba-common/drivingdirection.h>
#include <moba-common/enumswitchstand.h>

#include "nlohmann/json.hpp"
#include "message.h"

using MessageGroups = std::set<Message::MessageGroup>;

struct AppData {

    AppData() = default;

    AppData(
            std::string appName, const moba::Version &version, MessageGroups groups
    ) : appName{std::move(appName)}, version{version}, groups{std::move(groups)} {
    }

    explicit AppData(const nlohmann::json &d) {
        version = d["version"].get<std::string>();
        for (auto &v: d["msgGroups"]) {
            groups.insert(static_cast<Message::MessageGroup>(v.get<int>()));
        }
        appName = d["appName"].get<std::string>();
    }

    std::string appName;
    moba::Version version;
    MessageGroups groups;
};

struct EndpointData {
    EndpointData(
        AppData appInfo, long appId, std::string startTime, std::string addr, long port
    ) : appInfo{std::move(appInfo)}, appId{appId}, startTime{std::move(startTime)}, addr{std::move(addr)}, port{port} {
    }

    explicit EndpointData(const nlohmann::json &d) {
        appId = d["appID"].get<int>();
        addr = d["addr"].get<std::string>();
        port = d["port"].get<int>();
        startTime = d["startTime"].get<std::string>();
        appInfo = AppData{d["appInfo"]};
    }

    AppData appInfo;
    long appId;
    std::string startTime;
    std::string addr;
    long port;
};

struct TrackLayoutData {
    TrackLayoutData(
        int id, std::string name, std::string description, std::string created, std::string modified, bool active,
        int locked
    )
        : id{id}, name{std::move(name)}, description{std::move(description)}, created{std::move(created)},
          modified{std::move(modified)}, active{active}, locked{locked} {

    }

    TrackLayoutData(std::string name, std::string description, bool active) :
    name{std::move(name)}, description{std::move(description)}, active{active} {

    }

    explicit TrackLayoutData(const nlohmann::json &d) {
        id = d["id"].get<int>();
        name = d["name"].get<std::string>();
        description = d["description"].get<std::string>();
        created = d["created"].get<std::string>();
        modified = d["modified"].get<std::string>();
        active = d["active"].get<bool>();
        locked = d["locked"].get<int>();
    }

    int id{};
    std::string name;
    std::string description;
    std::string created;
    std::string modified;
    bool active;
    int locked{};
};

struct TrackLayoutSymbol {
    TrackLayoutSymbol() = default;

    explicit TrackLayoutSymbol(const int symbol) : symbol{symbol} {
    }

    TrackLayoutSymbol(const int id, const int symbol) : id{id}, symbol{symbol} {
    }

    int id{};
    int symbol{};
};

// Thanks to https://stackoverflow.com/a/45395204
using IntPair = std::pair<int, int>;

using Symbols = std::map<IntPair, TrackLayoutSymbol>;
using SymbolsPtr = std::shared_ptr<Symbols>;

struct SpecificLayoutData {
    SpecificLayoutData() {
        symbols = std::make_shared<Symbols>();
    }

    explicit SpecificLayoutData(const nlohmann::json &d) {
        symbols = std::make_shared<Symbols>();
        id = d["id"].get<int>();

        for (auto &iter: d["symbols"]) {
            (*symbols)[{
                    iter["xPos"].get<int>(),
                    iter["yPos"].get<int>()
            }] = TrackLayoutSymbol(
                    iter["id"].get<int>(),
                    iter["symbol"].get<int>()
            );
        }
    }

    int id{};
    SymbolsPtr symbols;
};

struct ContactData {
    explicit ContactData(const std::uint16_t moduleAddr = 0, const std::uint16_t contactNb = 0) :
        moduleAddr{moduleAddr}, contactNb{contactNb} {
    }

    explicit ContactData(const nlohmann::json &d) {
        moduleAddr = d["moduleAddr"].get<int>();
        contactNb = d["contactNb"].get<int>();
    }

    friend bool operator<(const ContactData &l, const ContactData &r) {
        if (l.moduleAddr < r.moduleAddr) {
            return true;
        }
        if (l.moduleAddr == r.moduleAddr && l.moduleAddr < r.moduleAddr) {
            return true;
        }
        return false;
    }

    std::uint16_t moduleAddr;
    std::uint16_t contactNb;
};

struct ContactTriggerData {
    ContactTriggerData(
        const std::uint16_t moduleAddr, const std::uint16_t contactNb, const bool state, const int time
    ) : contactData{moduleAddr, contactNb}, state{state}, time{time} {

    }

    explicit ContactTriggerData(const nlohmann::json &d) : contactData{d["contact"]} {
        state = d["state"].get<bool>();
        time = d["time"].get<int>();
    }

    ContactData contactData;
    bool state;
    int time;
};

struct BlockContactData {

    explicit BlockContactData(const nlohmann::json &d) :
            brakeTriggerContact{d["brakeTriggerContact"]}, blockContact{d["blockContact"]} {
        if (!d["trainId"].is_null()) {
            trainId = d["trainId"].get<int>();
        }

        id = d["id"].get<int>();
    }

    ContactData brakeTriggerContact;
    ContactData blockContact;
    int trainId;

    // ToDo Consider to make trainId optional
    //std::optional<int> trainId;
    int id;
};

struct SwitchStandData {
    SwitchStandData() = default;

    explicit SwitchStandData(const nlohmann::json &d) {
        id = d["id"].get<int>();
        switchStand = moba::stringToSwitchStandEnum(d["switchStand"].get<std::string>());
    }

    moba::SwitchStand switchStand{};
    int id{};
};

struct BrakeVectorContact {
    explicit BrakeVectorContact(const ContactData contact, const int localId = 0) : contact{contact}, localId{localId} {
    }

    explicit BrakeVectorContact(const nlohmann::json &d) {
        contact = ContactData{d["contact"]};
        localId = d["localId"].get<int>();
    }

    ContactData contact;
    int localId;
};

struct SwitchingOutput {
    SwitchingOutput(const std::uint32_t localId, const bool differ) : localId{localId}, differ{differ} {
    }

    explicit SwitchingOutput(const nlohmann::json &d) {
        localId = d["localId"].get<int>();
        differ = d["differ"].get<bool>();
    }

    std::uint32_t localId;
    bool differ;
};

using SwitchingOutputs = std::vector<SwitchingOutput>;
