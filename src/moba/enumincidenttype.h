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

enum class IncidentType {
    EXCEPTION,
    STATUS_CHANGED,
    NOTICE,
    CLIENT_ERROR,
    SERVER_NOTICE
};

inline IncidentType stringToIncidentTypeEnum(const std::string &s) {
    if(s == "EXCEPTION") {
        return IncidentType::EXCEPTION;
    }
    if(s == "STATUS_CHANGED") {
        return IncidentType::STATUS_CHANGED;
    }
    if(s == "NOTICE") {
        return IncidentType::NOTICE;
    }
    if(s == "CLIENT_ERROR") {
        return IncidentType::CLIENT_ERROR;
    }
    if(s == "SERVER_NOTICE") {
        return IncidentType::SERVER_NOTICE;
    }
    throw moba::UnsupportedOperationException{"invalid value given"};
}

inline std::string incidentTypeEnumToString(const IncidentType s) {
    switch(s) {
        case IncidentType::EXCEPTION:
            return "EXCEPTION";

        case IncidentType::STATUS_CHANGED:
            return "STATUS_CHANGED";

        case IncidentType::NOTICE:
            return "NOTICE";

        case IncidentType::CLIENT_ERROR:
            return "CLIENT_ERROR";

        case IncidentType::SERVER_NOTICE:
            return "SERVER_NOTICE";

        default:
            throw moba::UnsupportedOperationException{"invalid value given"};
    }
}
