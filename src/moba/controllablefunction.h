/*
 *  Project:    moba-connector
 *
 *  Copyright (C) 2022 Stefan Paproth <pappi-@gmx.de>
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

#include <moba-common/exception.h>

enum class ControllableFunction {
    HEADLIGHTS       = 1,
    OPERATING_SOUNDS = 23,
};

inline ControllableFunction stringToControllableFunctionEnum(const std::string &s) {
    if(s == "HEADLIGHTS") {
        return ControllableFunction::HEADLIGHTS;
    } else if(s == "OPERATING_SOUNDS") {
        return ControllableFunction::OPERATING_SOUNDS;
    } else {
        throw moba::common::UnsupportedOperationException{"ControllableFunction: invalid value given"};
    }
}

inline std::string controllableFunctionEnumToString(ControllableFunction s) {
    switch(s) {
        case ControllableFunction::HEADLIGHTS:
            return "HEADLIGHTS";

        case ControllableFunction::OPERATING_SOUNDS:
            return "OPERATING_SOUNDS";

        default:
            throw moba::common::UnsupportedOperationException{"ControllableFunction: invalid value given"};
    }
}
