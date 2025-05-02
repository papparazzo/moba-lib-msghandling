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
 *  along with this program. If not, see <https://www.gnu.org/licenses/agpl.txt>.
 * 
 */
 
#pragma once

#include <moba-common/exception.h>

enum class ToggleState {
    ON,
    OFF,
    UNSET
};

inline ToggleState stringToToggleStateEnum(const std::string &s) {
    if(s == "ON") {
        return ToggleState::ON;
    }
    if(s == "OFF") {
        return ToggleState::OFF;
    }
    if(s == "UNSET") {
        return ToggleState::UNSET;
    }
    throw moba::UnsupportedOperationException{"ToggleState: invalid value given"};
}

inline std::string toggleStateEnumToString(ToggleState s) {
    switch(s) {
        case ToggleState::ON:
            return "ON";

        case ToggleState::OFF:
            return "OFF";

        case ToggleState::UNSET:
            return "UNSET";

        default:
            throw moba::UnsupportedOperationException{"ToggleState: invalid value given"};
    }
}
