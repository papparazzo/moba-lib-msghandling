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

#include "message.h"
#include "shared.h"

struct InterfaceMessage : public Message {
    enum MessageName {
        CONNECTIVITY_STATE_CHANGED = 1,
        CONTACT_TRIGGERED          = 2,
        SET_BRAKE_VECTOR           = 3,
        SET_LOC_SPEED              = 4
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

    InterfaceContactTriggered(const ContactTrigger &contactTrigger) : contactTrigger{contactTrigger} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetObject();
        d.AddMember("modulAddr", contactTrigger.contact.modulAddr, d.GetAllocator());
        d.AddMember("contactNb", contactTrigger.contact.contactNb, d.GetAllocator());

        rapidjson::Value v;
        v.SetObject();
        v.AddMember("state", contactTrigger.state, d.GetAllocator());
        v.AddMember("time", contactTrigger.time, d.GetAllocator());
        d.AddMember("contact", v, d.GetAllocator());
        return d;
    }

    ContactTrigger contactTrigger;
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