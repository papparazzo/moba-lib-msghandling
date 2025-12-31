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

enum class NotificationType {
    EXCEPTION,
    STATUS_CHANGED,
    CLIENT_NOTICE,
    CLIENT_ERROR,
    SERVER_NOTICE
};

inline NotificationType stringToNotificationTypeEnum(const std::string &s) {
    if(s == "EXCEPTION") {
        return NotificationType::EXCEPTION;
    }
    if(s == "STATUS_CHANGED") {
        return NotificationType::STATUS_CHANGED;
    }
    if(s == "CLIENT_NOTICE") {
        return NotificationType::CLIENT_NOTICE;
    }
    if(s == "CLIENT_ERROR") {
        return NotificationType::CLIENT_ERROR;
    }
    if(s == "SERVER_NOTICE") {
        return NotificationType::SERVER_NOTICE;
    }
    throw moba::UnsupportedOperationException{"NotificationType: invalid value <" + s + "> given"};
}

inline std::string incidentTypeEnumToString(const NotificationType s) {
    switch(s) {
        case NotificationType::EXCEPTION:
            return "EXCEPTION";

        case NotificationType::STATUS_CHANGED:
            return "STATUS_CHANGED";

        case NotificationType::CLIENT_NOTICE:
            return "CLIENT_NOTICE";

        case NotificationType::CLIENT_ERROR:
            return "CLIENT_ERROR";

        case NotificationType::SERVER_NOTICE:
            return "SERVER_NOTICE";

        default:
            throw moba::UnsupportedOperationException{"NotificationType: invalid value given"};
    }
}
