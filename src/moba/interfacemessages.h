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
#include "controllablefunction.h"

struct InterfaceMessage: public Message {
    enum MessageName {
        CONNECTIVITY_STATE_CHANGED = 1,
        CONTACT_TRIGGERED          = 2,
        SET_BRAKE_VECTOR           = 3,
        SET_LOCO_SPEED             = 4,
        SET_LOCO_DIRECTION         = 5,
        SET_LOCO_FUNCTION          = 6
    };

    static constexpr std::uint32_t GROUP_ID = INTERFACE;
};

struct InterfaceConnectivityStateChanged : public InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONNECTIVITY_STATE_CHANGED;

    enum class Connectivity {
        CONNECTED,
        ERROR
    };

    InterfaceConnectivityStateChanged(Connectivity connectivity) : connectivity{connectivity} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;

        switch(connectivity) {
            case Connectivity::CONNECTED:
                d.SetString("CONNECTED");
                break;

            case Connectivity::ERROR:
            default:
                d.SetString("ERROR");
                break;
        }
        return d;
    }

    Connectivity connectivity;
};

struct InterfaceContactTriggered : public InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONTACT_TRIGGERED;

    InterfaceContactTriggered(const rapidjson::Document &d): contactTrigger{d} {
    }

    InterfaceContactTriggered(const ContactTriggerData &contactTrigger) : contactTrigger{contactTrigger} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetObject();
        d.AddMember("state", contactTrigger.state, d.GetAllocator());
        d.AddMember("time", contactTrigger.time, d.GetAllocator());

        rapidjson::Value v;
        v.SetObject();
        v.AddMember("modulAddr", contactTrigger.contactData.modulAddr, d.GetAllocator());
        v.AddMember("contactNb", contactTrigger.contactData.contactNb, d.GetAllocator());

        d.AddMember("contact", v, d.GetAllocator());
        return d;
    }

    ContactTriggerData contactTrigger;
};

struct InterfaceSetBrakeVector : public InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = SET_BRAKE_VECTOR;

    InterfaceSetBrakeVector(const rapidjson::Document &d) {
        for(auto &iter : d.GetArray()) {
            items.push_back(BrakeVectorContact{iter});
        }
    }

    std::vector<BrakeVectorContact> items;
};

struct InterfaceSetLocoSpeed : public InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = SET_LOCO_SPEED;

    InterfaceSetLocoSpeed(std::uint32_t localId, std::uint16_t speed) : localId{localId}, speed{speed} {
    }

    InterfaceSetLocoSpeed(const rapidjson::Document &d) {
        localId = d["localId"].GetInt();
        speed = d["speed"].GetInt();
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetObject();

        d.AddMember("localId", localId, d.GetAllocator());
        d.AddMember("speed", speed, d.GetAllocator());
        return d;
    }

    std::uint32_t localId;
    std::uint16_t speed;
};

struct InterfaceSetLocoDirection : public InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = SET_LOCO_DIRECTION;

    enum class DrivingDirection	{
        RETAIN   = 0,
		FORWARD  = 1,
		BACKWARD = 2,
		TOGGLE   = 3,
    };

    InterfaceSetLocoDirection(std::uint32_t localId, DrivingDirection direction) : localId{localId}, direction{direction} {
    }

    InterfaceSetLocoDirection(std::uint32_t localId, std::uint8_t drivingDirection) : localId{localId} {
         direction = static_cast<DrivingDirection>(drivingDirection);
    }

    InterfaceSetLocoDirection(const rapidjson::Document &d) {
        localId = d["localId"].GetInt();
        auto s = d["direction"].GetString();
        direction = getDirectionFromString(s);
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetObject();

        d.AddMember("localId", localId, d.GetAllocator());
        switch(direction) {
            case DrivingDirection::FORWARD:
                d.AddMember("direction", rapidjson::Value("FORWARD", d.GetAllocator()), d.GetAllocator());
                break;

            case DrivingDirection::BACKWARD:
                d.AddMember("direction", rapidjson::Value("BACKWARD", d.GetAllocator()), d.GetAllocator());
                break;

            case DrivingDirection::TOGGLE:
                d.AddMember("direction", rapidjson::Value("TOGGLE", d.GetAllocator()), d.GetAllocator());
                break;

            case DrivingDirection::RETAIN:
            default:
                d.AddMember("direction", rapidjson::Value("RETAIN", d.GetAllocator()), d.GetAllocator());
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

struct InterfaceSetLocoFunction : public InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = SET_LOCO_FUNCTION;

    InterfaceSetLocoFunction(std::uint32_t localId, ControllableFunction function, bool active) : localId{localId}, function{function}, active{active} {
    }

    InterfaceSetLocoFunction(const rapidjson::Document &d) {
        localId = d["localId"].GetInt();
        auto s = d["function"].GetString();
        function = stringToControllableFunctionEnum(s);
        active = d["active"].GetBool();
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetObject();
        d.AddMember("localId", localId, d.GetAllocator());
        d.AddMember("function", rapidjson::Value(controllableFunctionEnumToString(function).c_str(), d.GetAllocator()), d.GetAllocator());
        d.AddMember("localId", localId, d.GetAllocator());
        return d;
    }

    std::uint32_t localId;
    ControllableFunction function;
    bool active;
};
