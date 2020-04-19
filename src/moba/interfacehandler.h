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
#include "basemessage.h"
#include "shared.h"

struct InterfaceMessage : public Message {
    enum MessageName {
        CONNECTIVITY_STATE_CHANGED = 1,
        CONTACT_TRIGGERED          = 2,
        SET_BRAKE_VECTOR           = 3,
        SET_LOC_SPEED              = 4
    };

    const static std::uint32_t GROUP_ID = INTERFACE;
};

struct InterfaceConnectivityStateChanged : public InterfaceMessage {
    const static std::uint32_t MESSAGE_ID = CONNECTIVITY_STATE_CHANGED;

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
/*
struct InterfaceContactTriggered :public InterfaceMessage {
    const static std::uint32_t MESSAGE_ID = CONTACT_TRIGGERED;

    InterfaceContactTriggered(const ContactTrigger &contactTrigger) : contactTrigger{contactTrigger} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetObject();

        d["modulAddr"] = moba::toJsonNumberPtr(contactTrigger.contact.modulAddr);
        d["contactNb"] = moba::toJsonNumberPtr(contactTrigger.contact.contactNb);
        moba::JsonObjectPtr o(new moba::JsonObject());

        (*o)["contact"] = c;
        (*o)["state"  ] = moba::toJsonBoolPtr(contactTrigger.state);
        (*o)["time"   ] = moba::toJsonNumberPtr(contactTrigger.time);
        return o;
    }

    ContactTrigger contactTrigger;
};

struct InterfaceSetBrakeVector : public RecieveMessage {
    InterfaceSetBrakeVector(moba::JsonItemPtr data) {
        auto a = std::dynamic_pointer_cast<moba::JsonArray>(data);
        for(auto iter : *a) {
            items.push_back(BrakeVectorContact{std::dynamic_pointer_cast<moba::JsonObject>(iter)});
        }
    }

    static std::string getMessageName() {
        return "SET_BRAKE_VECTOR";
    }

    std::vector<BrakeVectorContact> items;
};
*/