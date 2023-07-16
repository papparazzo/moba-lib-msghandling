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

#include <string>
#include <vector>
#include <cstdint>
#include <moba-common/exception.h>

#include "message.h"
#include "shared.h"
#include "enumfunction.h"

struct InterfaceMessage: public Message {
    enum MessageName {
        CONNECTIVITY_STATE_CHANGED = 1,
        CONTACT_TRIGGERED          = 2,
        SET_BRAKE_VECTOR           = 3,
        RESET_BRAKE_VECTOR         = 4,  
        SET_LOCO_SPEED             = 5,
        SET_LOCO_DIRECTION         = 6,
        SET_LOCO_FUNCTION          = 7,
        SWITCH_ACCESSORY_DECODERS  = 8
    };

    static constexpr std::uint32_t GROUP_ID = INTERFACE;
};

struct InterfaceConnectivityStateChanged: public InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONNECTIVITY_STATE_CHANGED;

    enum class Connectivity {
        CONNECTED,
        ERROR
    };

    InterfaceConnectivityStateChanged(Connectivity connectivity): connectivity{connectivity} {
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        nlohmann::json d;

        switch(connectivity) {
            case Connectivity::CONNECTED:
                d = "CONNECTED";
                break;

            case Connectivity::ERROR:
            default:
                d = "ERROR";
                break;
        }
        return d;
    }

    Connectivity connectivity;
};

struct InterfaceContactTriggered: public InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONTACT_TRIGGERED;

    InterfaceContactTriggered(const nlohmann::json &d): contactTrigger{d} {
    }

    InterfaceContactTriggered(const ContactTriggerData &contactTrigger): contactTrigger{contactTrigger} {
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        nlohmann::json d;

        d["state"] = contactTrigger.state;
        d["time"] = contactTrigger.time;

        nlohmann::json  v;

        v["modulAddr"] = contactTrigger.contactData.modulAddr;
        v["contactNb"] = contactTrigger.contactData.contactNb;

        d["contact"] = v;
        return d;
    }

    ContactTriggerData contactTrigger;
};

struct InterfaceSetBrakeVector: public InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = SET_BRAKE_VECTOR;

    InterfaceSetBrakeVector(const nlohmann::json &d) {
        for(auto &iter: d) {
            items.push_back(BrakeVectorContact{iter});
        }
    }

    std::vector<BrakeVectorContact> items;
};

struct InterfaceResetBrakeVector: public InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = RESET_BRAKE_VECTOR;

    InterfaceResetBrakeVector(const nlohmann::json &d) {
        for(auto &iter: d) {
            items.push_back(BrakeVectorContact{iter});
        }
    }

    std::vector<BrakeVectorContact> items;
};

struct InterfaceSetLocoSpeed: public InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = SET_LOCO_SPEED;

    InterfaceSetLocoSpeed(std::uint32_t localId, std::uint16_t speed): localId{localId}, speed{speed} {
    }

    InterfaceSetLocoSpeed(const nlohmann::json &d) {
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

struct InterfaceSetLocoDirection: public InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = SET_LOCO_DIRECTION;

    enum class DrivingDirection	{
        RETAIN   = 0,
        FORWARD  = 1,
        BACKWARD = 2,
        TOGGLE   = 3,
    };

    InterfaceSetLocoDirection(std::uint32_t localId, DrivingDirection direction): localId{localId}, direction{direction} {
    }

    InterfaceSetLocoDirection(std::uint32_t localId, std::uint8_t drivingDirection): localId{localId} {
         direction = static_cast<DrivingDirection>(drivingDirection);
    }

    InterfaceSetLocoDirection(const nlohmann::json &d) {
        localId = d["localId"].get<int>();
        auto s = d["direction"].get<std::string>();
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
    DrivingDirection getDirectionFromString(const std::string &s) {
        if(s == "RETAIN") {
            return DrivingDirection::RETAIN;
        } else if(s == "FORWARD") {
            return DrivingDirection::FORWARD;
        } else if(s == "BACKWARD") {
            return DrivingDirection::BACKWARD;
        } else if(s == "TOGGLE") {
            return DrivingDirection::TOGGLE;
        } else {
            throw moba::UnsupportedOperationException{"invalid value given"};
        }
    }
};

struct InterfaceSetLocoFunction: public InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = SET_LOCO_FUNCTION;

    InterfaceSetLocoFunction(std::uint32_t localId, Function function, bool active): localId{localId}, function{function}, active{active} {
    }

    InterfaceSetLocoFunction(const nlohmann::json &d) {
        localId = d["localId"].get<int>();
        auto s = d["function"].get<std::string>();
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

struct InterfaceSwitchAccessoryDecoders: public InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = SWITCH_ACCESSORY_DECODERS;

    InterfaceSwitchAccessoryDecoders(const nlohmann::json &d) {
        for(auto &iter: d) {
            switchingOutputs.push_back(iter);
        }
    }
    SwitchingOutputs switchingOutputs;
};
