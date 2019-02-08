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
#include <moba/jsonabstractitem.h>

struct InterfaceSetConnectivity : public DispatchMessageType<InterfaceSetConnectivity> {
    enum Connectivity {
        CO_CONNECTED,
        CO_ERROR
    };

    InterfaceSetConnectivity(Connectivity connectivity) : connectivity{connectivity} {
    }

    static std::string getMessageName() const {
        return "INTERFACE_SET_CONNECTIVITY";
    }

    virtual moba::JsonItemPtr getData() const override {
        switch(connectivity) {
            case CO_CONNECTED:
                return moba::toJsonStringPtr("CONNECTED");

            case CO_ERROR:
                return moba::toJsonStringPtr("ERROR");
        }
    }

    Connectivity connectivity;
};
