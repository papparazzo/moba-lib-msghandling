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

enum class ThreeState {
    ON,
    OFF,
    AUTO,
    UNSET
};

inline ThreeState stringToThreeStateEnum(const std::string &s) {
    if(s == "ON") {
        return ThreeState::ON;
    }
    if(s == "OFF") {
        return ThreeState::OFF;
    }
    if(s == "AUTO") {
        return ThreeState::AUTO;
    }
    if(s == "UNSET") {
        return ThreeState::UNSET;
    }
    throw moba::UnsupportedOperationException{"ThreeState: invalid value <" + s + "> given"};
}

inline std::string threeStateEnumToString(ThreeState s) {
    switch(s) {
        case ThreeState::ON:
            return "ON";

        case ThreeState::OFF:
            return "OFF";

        case ThreeState::AUTO:
            return "AUTO";

        case ThreeState::UNSET:
            return "UNSET";

        default:
            throw moba::UnsupportedOperationException{"ThreeState: invalid value given"};
    }
}
