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
 *  along with this program. If not, see <https://www.gnu.org/licenses/agpl.txt>.
 *
 */

#pragma once

#include <string>
#include <moba-common/exception.h>

enum class NotificationLevel {
    CRITICAL,
    NOTICE,
    WARNING,
    ERROR
};

inline NotificationLevel stringToNotificationLevelEnum(const std::string &s) {
    if(s == "CRITICAL") {
        return NotificationLevel::CRITICAL;
    }
    if(s == "NOTICE") {
        return NotificationLevel::NOTICE;
    }
    if(s == "WARNING") {
        return NotificationLevel::WARNING;
    }
    if(s == "ERROR") {
        return NotificationLevel::ERROR;
    }
    throw moba::UnsupportedOperationException{"NotificationLevel: invalid value <" + s + "> given"};
}

inline std::string incidentLevelEnumToString(const NotificationLevel s) {
    switch(s) {
        case NotificationLevel::CRITICAL:
            return "CRITICAL";

        case NotificationLevel::NOTICE:
            return "NOTICE";

        case NotificationLevel::WARNING:
            return "WARNING";

        case NotificationLevel::ERROR:
            return "ERROR";

        default:
            throw moba::UnsupportedOperationException{"NotificationLevel: invalid value given"};
    }
}
