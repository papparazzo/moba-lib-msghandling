/*
 *  Project:    moba-lib-msghandling
 * 
 *  Copyright (C) 2023 Stefan Paproth <pappi-@gmx.de>
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
#include <moba-common/exception.h>

enum class Switch {
    ON,
    AUTO,
    UNSET,
    TRIGGER,
    OFF
};

inline Switch stringToSwitchEnum(const std::string &s) {
    if(s == "ON") {
        return Switch::ON;
    }
    if(s == "AUTO") {
        return Switch::AUTO;
    }
    if(s == "UNSET") {
        return Switch::UNSET;
    }
    if(s == "TRIGGER") {
        return Switch::TRIGGER;
    }
    if(s == "OFF") {
        return Switch::OFF;
    }
    throw moba::UnsupportedOperationException{"invalid value given"};
}

inline std::string switchEnumToString(const Switch s) {
    switch(s) {
        case Switch::ON:
            return "ON";

        case Switch::OFF:
            return "OFF";

        case Switch::AUTO:
            return "AUTO";

        case Switch::UNSET:
            return "UNSET";

        case Switch::TRIGGER:
            return "TRIGGER";

        default:
            throw moba::UnsupportedOperationException{"invalid value given"};
    }
}
