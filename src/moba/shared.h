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
 *  along with this program. If not, see <https://www.gnu.org/licenses/agpl.txt>.
 *
 */

#pragma once

#include <memory>
#include <set>
#include <utility>
#include <map>
#include <moba-common/exception.h>
#include <moba-common/version.h>
#include <moba-common/enumswitchstand.h>

#include "nlohmann/json.hpp"
#include "message.h"
#include "enumfunctionstate.h"

using MessageGroups = std::set<Message::MessageGroup>;

struct AppData {

    AppData() = default;

    AppData(std::string name, std::string description, const moba::Version &version, MessageGroups groups) :
        name{std::move(name)}, description{std::move(description)}, version{version}, groups{std::move(groups)} {
    }

    explicit AppData(const nlohmann::json &d) {
        version = d["version"].get<std::string>();
        for (auto &v: d["msgGroups"]) {
            groups.insert(static_cast<Message::MessageGroup>(v.get<int>()));
        }
        description = d["description"].get<std::string>();
        name = d["name"].get<std::string>();
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const {
        nlohmann::json d;

        d["name"] = name;
        d["description"] = description;
        d["version"] = version.toString();

        nlohmann::json msgGroups = nlohmann::json::array();
        for(const auto& group : groups) {
            msgGroups.push_back(group);
        }
        d["msgGroups"] = msgGroups;

        return d;
    }

    std::string name;
    std::string description;
    moba::Version version;
    MessageGroups groups;
};

struct EndpointData {

    EndpointData() = default;

    EndpointData(
        AppData appData, const long appId, std::string startTime, std::string addr, const long port
    ) : appData{std::move(appData)}, appId{appId}, startTime{std::move(startTime)}, addr{std::move(addr)}, port{port} {
    }

    explicit EndpointData(const nlohmann::json &d) {
        if (d.is_null()) {
            return;
        }
        appId = d["appId"].get<int>();
        addr = d["socket"]["addr"].get<std::string>();
        port = d["socket"]["port"].get<int>();
        startTime = d["startTime"].get<std::string>();

        appData = AppData{d["appData"]};
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const {
        nlohmann::json d;

        if(appData.name.empty() && appId == 0 && port == 0) {
            return nullptr;
        }

        d["appId"] = appId;

        nlohmann::json s;
        s["addr"] = addr;
        s["port"] = port;

        d["socket"] = s;

        d["startTime"] = startTime;

        d["appData"] = appData.getJsonDocument();
        return d;
    }

    [[nodiscard]] std::string toString() const {
        if(appData.name.empty() && appId == 0 && port == 0) {
            return "null";
        }
        std::stringstream ss;
        ss << appData.name << "#" << appId << "@" << addr << ":" << port;
        return ss.str();
    }

    AppData appData;
    long appId{0};
    std::string startTime;
    std::string addr;
    long port{0};
};

struct TrackLayoutData {
    TrackLayoutData(
        const int id, std::string name, std::string description, std::string created, std::string modified,
        const bool active, const int locked
    ) : id{id}, name{std::move(name)}, description{std::move(description)}, created{std::move(created)},
        modified{std::move(modified)}, active{active}, locked{locked} {
    }

    TrackLayoutData(std::string name, std::string description, const bool active) :
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
        if (l.moduleAddr == r.moduleAddr && l.contactNb < r.contactNb) {
            return true;
        }
        return false;
    }

    explicit operator std::string() const {
        return std::to_string(moduleAddr) + ":" + std::to_string(contactNb);
    }

    friend std::ostream& operator<<(std::ostream& stream, const ContactData& contact) {
        stream << std::to_string(contact.moduleAddr) + ":" + std::to_string(contact.contactNb);
        return stream;
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
        brakeTriggerContact{d["brakeTriggerContact"]}, blockContact{d["blockContact"]}
    {
        if (!d["trainId"].is_null()) {
            trainId = d["trainId"].get<int>();
        }

        id = d["id"].get<int>();
    }

    ContactData brakeTriggerContact;
    ContactData blockContact;
    int trainId{0};

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

struct PortAddressData {
    PortAddressData() = default;
    PortAddressData(const std::uint16_t controller, const std::uint16_t port) : controller{controller}, port{port} {
    }

    explicit PortAddressData(const nlohmann::json &d) {
        controller = d["controller"].get<std::uint16_t>();
        port = d["port"].get<std::uint16_t>();
    }

    std::uint16_t controller{};
    std::uint16_t port{};
};

struct GlobalPortAddressData {
    GlobalPortAddressData() = default;
    GlobalPortAddressData(const std::uint16_t deviceId, const PortAddressData address) : deviceId{deviceId}, address{address} {}

    explicit GlobalPortAddressData(const nlohmann::json &d) {
        deviceId = d["deviceId"].get<int>();
        address = PortAddressData(d["address"]);
    }

    std::uint16_t   deviceId{};
    PortAddressData address{};
};

struct FunctionStateData {
    FunctionStateData() = default;
    FunctionStateData(const GlobalPortAddressData address, const FunctionState functionState): address{address}, functionState{functionState} {}

    explicit FunctionStateData(const nlohmann::json &d) {
        address = GlobalPortAddressData(d["address"]);
        functionState = stringToFunctionStateEnum(d["state"].get<std::string>());
    }

    GlobalPortAddressData address;
    FunctionState functionState{FunctionState::OFF};
};
