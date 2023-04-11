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

enum class ErrorId {
    UNKNOWN_ERROR,
    UNKNOWN_GROUP_ID,
    UNKNOWN_MESSAGE_ID,

    DATABASE_ERROR,

    DATASET_NOT_LOCKED,
    DATASET_LOCKED,
    DATASET_MISSING,

    FAULTY_MESSAGE,

    INVALID_APP_ID,
    INVALID_DATA_SEND,
    INVALID_STATUS_CHANGE,

    NO_DEFAULT_GIVEN,

    SAME_ORIGIN_NEEDED,

    SETTING_NOT_ALLOWED,
    INVALID_VALUE_GIVEN,
};

inline ErrorId stringToErrorIdEnum(const std::string &s) {
    if(s == "UNKNOWN_ERROR") {
        return ErrorId::UNKNOWN_ERROR;
    }
    if(s == "UNKNOWN_GROUP_ID") {
        return ErrorId::UNKNOWN_GROUP_ID;
    }
    if(s == "UNKNOWN_MESSAGE_ID") {
        return ErrorId::UNKNOWN_MESSAGE_ID;
    }
    if(s == "DATABASE_ERROR") {
        return ErrorId::DATABASE_ERROR;
    }
    if(s == "DATASET_NOT_LOCKED") {
        return ErrorId::DATASET_NOT_LOCKED;
    }
    if(s == "DATASET_LOCKED") {
        return ErrorId::DATASET_LOCKED;
    }
    if(s == "DATASET_MISSING") {
        return ErrorId::DATASET_MISSING;
    }
    if(s == "FAULTY_MESSAGE") {
        return ErrorId::FAULTY_MESSAGE;
    }
    if(s == "INVALID_APP_ID") {
        return ErrorId::INVALID_APP_ID;
    }
    if(s == "INVALID_DATA_SEND") {
        return ErrorId::INVALID_DATA_SEND;
    }
    if(s == "INVALID_STATUS_CHANGE") {
        return ErrorId::INVALID_STATUS_CHANGE;
    }
    if(s == "NO_DEFAULT_GIVEN") {
        return ErrorId::NO_DEFAULT_GIVEN;
    }
    if(s == "SAME_ORIGIN_NEEDED") {
        return ErrorId::SAME_ORIGIN_NEEDED;
    }
    if(s == "SETTING_NOT_ALLOWED") {
        return ErrorId::SETTING_NOT_ALLOWED;
    }
    if(s == "INVALID_VALUE_GIVEN") {
        return ErrorId::INVALID_VALUE_GIVEN;
    }
    throw moba::UnsupportedOperationException{"ErrorId: invalid value given"};
}

inline std::string errorIdEnumToString(ErrorId s) {
    switch(s) {
        case ErrorId::UNKNOWN_ERROR:
            return "UNKNOWN_ERROR";

        case ErrorId::UNKNOWN_GROUP_ID:
            return "UNKNOWN_GROUP_ID";

        case ErrorId::UNKNOWN_MESSAGE_ID:
            return "UNKNOWN_MESSAGE_ID";

        case ErrorId::DATABASE_ERROR:
            return "DATABASE_ERROR";

        case ErrorId::DATASET_NOT_LOCKED:
            return "DATASET_NOT_LOCKED";

        case ErrorId::DATASET_LOCKED:
            return "DATASET_LOCKED";

        case ErrorId::DATASET_MISSING:
            return "DATASET_MISSING";

        case ErrorId::FAULTY_MESSAGE:
            return "FAULTY_MESSAGE";

        case ErrorId::INVALID_APP_ID:
            return "INVALID_APP_ID";

        case ErrorId::INVALID_DATA_SEND:
            return "INVALID_DATA_SEND";

        case ErrorId::INVALID_STATUS_CHANGE:
            return "INVALID_STATUS_CHANGE";

        case ErrorId::NO_DEFAULT_GIVEN:
            return "NO_DEFAULT_GIVEN";

        case ErrorId::SAME_ORIGIN_NEEDED:
            return "SAME_ORIGIN_NEEDED";

        case ErrorId::SETTING_NOT_ALLOWED:
            return "SETTING_NOT_ALLOWED";

        case ErrorId::INVALID_VALUE_GIVEN:
            return "INVALID_VALUE_GIVEN";

        default:
            throw moba::UnsupportedOperationException{"ErrorId: invalid value given"};
    }
}
