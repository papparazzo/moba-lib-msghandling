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
#include <moba-common/exception.h>

enum class IncidentLevel {
    CRITICAL,
    NOTICE,
    WARNING,
    ERROR
};

inline IncidentLevel stringToIncidentLevelEnum(const std::string &s) {
    if(s == "CRITICAL") {
        return IncidentLevel::CRITICAL;
    }
    if(s == "NOTICE") {
        return IncidentLevel::NOTICE;
    }
    if(s == "WARNING") {
        return IncidentLevel::WARNING;
    }
    if(s == "ERROR") {
        return IncidentLevel::ERROR;
    }
    throw moba::UnsupportedOperationException{"invalid value given"};
}

inline std::string incidentLevelEnumToString(const IncidentLevel s) {
    switch(s) {
        case IncidentLevel::CRITICAL:
            return "CRITICAL";

        case IncidentLevel::NOTICE:
            return "NOTICE";

        case IncidentLevel::WARNING:
            return "WARNING";

        case IncidentLevel::ERROR:
            return "ERROR";

        default:
            throw moba::UnsupportedOperationException{"invalid value given"};
    }
}
