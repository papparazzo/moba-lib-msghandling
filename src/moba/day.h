/*
 *  Project:    moba-tester
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

enum class Day {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY,
};

inline Day stringToDayEnum(const std::string &s) {
    if(s == "MONDAY") {
        return Day::MONDAY;
    } else if(s == "TUESDAY") {
        return Day::TUESDAY;
    } else if(s == "WEDNESDAY") {
        return Day::WEDNESDAY;
    } else if(s == "THURSDAY") {
        return Day::THURSDAY;
    } else if(s == "FRIDAY") {
        return Day::FRIDAY;
    } else if(s == "SATURDAY") {
        return Day::SATURDAY;
    } else if(s == "SUNDAY") {
        return Day::SUNDAY;
    } else {
        throw moba::common::UnsupportedOperationException{"Day: invalid value given"};
    }
}

inline std::string dayEnumToString(Day s) {
    switch(s) {
        case Day::MONDAY:
            return "MONDAY";
        case Day::TUESDAY:
            return "TUESDAY";
        case Day::WEDNESDAY:
            return "WEDNESDAY";
        case Day::THURSDAY:
            return "THURSDAY";
        case Day::FRIDAY:
            return "FRIDAY";
        case Day::SATURDAY:
            return "SATURDAY";
        case Day::SUNDAY:
            return "SUNDAY";
        default:
            throw moba::common::UnsupportedOperationException{"Day: invalid value given"};
    }
}

