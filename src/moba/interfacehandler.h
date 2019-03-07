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
#include <moba/jsonabstractitem.h>

struct InterfaceConnectivityStateChanged : public DispatchMessageType<InterfaceConnectivityStateChanged> {
    enum class Connectivity {
        CONNECTED,
        ERROR
    };

    InterfaceConnectivityStateChanged(Connectivity connectivity) : connectivity{connectivity} {
    }

    static std::string getMessageName() {
        return "INTERFACE_CONNECTIVITY_STATE_CHANGED";
    }

    virtual moba::JsonItemPtr getData() const override {
        switch(connectivity) {
            case Connectivity::CONNECTED:
                return moba::toJsonStringPtr("CONNECTED");

            case Connectivity::ERROR:
            default:
                return moba::toJsonStringPtr("ERROR");
        }
    }

    Connectivity connectivity;
};

struct Contact {
    Contact(int modulAddr, int contactNb) : modulAddr{modulAddr}, contactNb{contactNb} {
    }

    Contact(moba::JsonObjectPtr appData) {
        modulAddr = moba::castToInt(appData->at("modulAddr"));
        contactNb = moba::castToInt(appData->at("contactNb"));
    }

    int modulAddr;
    int contactNb;

struct InterfaceContactTriggered : public DispatchMessageType<InterfaceContactTriggered> {
    InterfaceContactTriggered(const ContactTrigger &contactTrigger) : contactTrigger{contactTrigger} {
    }

    static std::string getMessageName() {
        return "INTERFACE_CONTACT_TRIGGERED";
    }

    /*
    virtual moba::JsonItemPtr getData() const override {

        moba::JsonObjectPtr c(new moba::JsonObject());
        (*c)["modulAddr"] = moba::toJsonNumberPtr(contactTrigger.contact.modulAddr);
        (*c)["contactNb"] = moba::toJsonNumberPtr(contactTrigger.contact.contactNb);
        moba::JsonObjectPtr o(new moba::JsonObject());


        (*o)["contact"] = c;
        (*o)["state"  ] = moba::toJsonSwitchPtr(wind);
        (*o)["time"   ] = moba::toJsonSwitchPtr(rain);
        return o;

    ContactTrigger	contact
		Bool
		Integer

    }
     */
    ContactTrigger contactTrigger;

};

struct InterfaceSetBrakeVector : public RecieveMessage {
    InterfaceSetBrakeVector(moba::JsonItemPtr data) {
        auto a = std::dynamic_pointer_cast<moba::JsonArray>(data);
        for(auto iter : *a) {
            layouts.push_back(BrakeVectorContact{std::dynamic_pointer_cast<moba::JsonObject>(iter)});
        }
    }

    static std::string getMessageName() {
        return "INTERFACE_SET_BRAKE_VECTOR";
    }

    std::vector<BrakeVectorContact> layouts;
};
