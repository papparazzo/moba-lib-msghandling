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

#include <string>
#include <vector>
#include <moba-common/exception.h>

#include "message.h"
#include "shared.h"
#include "enumfunction.h"

struct InterfaceMessage: Message {
    enum MessageName {
        CONNECTIVITY_STATE_CHANGED         = 1,
        CONTACT_TRIGGERED                  = 2,
        SET_BRAKE_VECTOR                   = 3,
        RESET_BRAKE_VECTOR                 = 4,
        SET_LOCO_SPEED                     = 5,
        SET_LOCO_DIRECTION                 = 6,
        SET_LOCO_FUNCTION                  = 7,
        SWITCH_ACCESSORY_DECODERS          = 8,
        SWITCH_ACCESSORY_DECODERS_COMPLETE = 9
    };

    static constexpr std::uint32_t GROUP_ID = INTERFACE;
};

struct InterfaceConnectivityStateChanged final: InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONNECTIVITY_STATE_CHANGED;

    enum class Connectivity {
        CONNECTED,
        ERROR
    };

    explicit InterfaceConnectivityStateChanged(const Connectivity connectivity): connectivity{connectivity} {
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        switch(connectivity) {
            case Connectivity::CONNECTED:
                return "CONNECTED";

            case Connectivity::ERROR:
            default:
                return "ERROR";
        }
    }

    Connectivity connectivity;
};

struct InterfaceContactTriggered final: InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONTACT_TRIGGERED;

    explicit InterfaceContactTriggered(const nlohmann::json &d): contactTrigger{d} {
    }

    explicit InterfaceContactTriggered(const ContactTriggerData &contactTrigger): contactTrigger{contactTrigger} {
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        nlohmann::json d;

        d["state"] = contactTrigger.state;
        d["time"] = contactTrigger.time;

        nlohmann::json v;

        v["moduleAddr"] = contactTrigger.contactData.moduleAddr;
        v["contactNb"] = contactTrigger.contactData.contactNb;

        d["contact"] = v;
        return d;
    }

    ContactTriggerData contactTrigger;
};

struct InterfaceSetBrakeVector final: InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = SET_BRAKE_VECTOR;

    explicit InterfaceSetBrakeVector(const nlohmann::json &d) {
        for(auto &iter: d) {
            items.push_back(BrakeVectorContact{iter});
        }
    }

    std::vector<BrakeVectorContact> items;
};

struct InterfaceResetBrakeVector final: InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = RESET_BRAKE_VECTOR;

    explicit InterfaceResetBrakeVector(const nlohmann::json &d) {
        for(auto &iter: d) {
            items.push_back(BrakeVectorContact{iter});
        }
    }

    std::vector<BrakeVectorContact> items;
};

struct InterfaceSetLocoSpeed final: InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = SET_LOCO_SPEED;

    InterfaceSetLocoSpeed(const std::uint32_t localId, const std::uint16_t speed): localId{localId}, speed{speed} {
    }

    explicit InterfaceSetLocoSpeed(const nlohmann::json &d) {
        localId = d["localId"].get<int>();
        speed = d["speed"].get<int>();
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        nlohmann::json d;

        d["localId"] = localId;
        d["speed"] = speed;
        return d;
    }

    std::uint32_t localId;
    std::uint16_t speed;
};

struct InterfaceSetLocoDirection final: InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = SET_LOCO_DIRECTION;

    enum class DrivingDirection	{
        RETAIN   = 0,
        FORWARD  = 1,
        BACKWARD = 2,
        TOGGLE   = 3,
    };

    InterfaceSetLocoDirection(const std::uint32_t localId, const DrivingDirection direction):
    localId{localId}, direction{direction} {
    }

    InterfaceSetLocoDirection(const std::uint32_t localId, std::uint8_t drivingDirection): localId{localId} {
         direction = static_cast<DrivingDirection>(drivingDirection);
    }

    explicit InterfaceSetLocoDirection(const nlohmann::json &d) {
        localId = d["localId"].get<int>();
        const auto s = d["direction"].get<std::string>();
        direction = getDirectionFromString(s);
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        nlohmann::json d;

        d["localId"] = localId;
        switch(direction) {
            case DrivingDirection::FORWARD:
                d["direction"] = "FORWARD";
                break;

            case DrivingDirection::BACKWARD:
                d["direction"] = "BACKWARD";
                break;

            case DrivingDirection::TOGGLE:
                d["direction"] = "TOGGLE";
                break;

            case DrivingDirection::RETAIN:
            default:
                d["direction"] = "RETAIN";
                break;
        }
        return d;
    }

    std::uint32_t localId;
    DrivingDirection direction;

protected:
    static DrivingDirection getDirectionFromString(const std::string &s) {
        if(s == "RETAIN") {
            return DrivingDirection::RETAIN;
        }
        if(s == "FORWARD") {
            return DrivingDirection::FORWARD;
        }
        if(s == "BACKWARD") {
            return DrivingDirection::BACKWARD;
        }
        if(s == "TOGGLE") {
            return DrivingDirection::TOGGLE;
        }
        throw moba::UnsupportedOperationException{"invalid value given"};
    }
};

struct InterfaceSetLocoFunction final: InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = SET_LOCO_FUNCTION;

    InterfaceSetLocoFunction(const std::uint32_t localId, const Function function, const bool active):
    localId{localId}, function{function}, active{active} {
    }

    explicit InterfaceSetLocoFunction(const nlohmann::json &d) {
        localId = d["localId"].get<int>();
        const auto s = d["function"].get<std::string>();
        function = stringToControllableFunctionEnum(s);
        active = d["active"].get<bool>();
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        nlohmann::json d;

        d["localId"] = localId;
        d["function"] = controllableFunctionEnumToString(function);

        return d;
    }

    std::uint32_t localId;
    Function function;
    bool active;
};

struct InterfaceSwitchAccessoryDecoders final: InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = SWITCH_ACCESSORY_DECODERS;

    explicit InterfaceSwitchAccessoryDecoders(const nlohmann::json &d) {
        for(auto &iter: d) {
            switchingOutputs.emplace_back(iter);
        }
    }
    SwitchingOutputs switchingOutputs;
};

struct InterfaceSwitchAccessoryDecodersComplete final: InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = SWITCH_ACCESSORY_DECODERS_COMPLETE;

    explicit InterfaceSwitchAccessoryDecodersComplete(const nlohmann::json &d) {
        id = d.get<int>();
    }

    int id;
};
