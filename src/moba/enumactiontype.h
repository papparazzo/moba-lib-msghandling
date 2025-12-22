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

enum class ActionType {
    DELAY,

    LOCO_HALT,
    LOCO_SPEED,
    LOCO_DIRECTION,

    LOCO_FUNCTION,
    LOCO_FUNCTION_TRIGGER,
    SWITCHING,

    //SEND_PUSH_TRAIN,
    SEND_ROUTE_SWITCHED,
    SEND_ROUTE_RELEASED,
    SEND_BLOCK_RELEASED
};

inline ActionType stringToActionTypeEnum(const std::string &s) {
    if(s == "DELAY") {
        return ActionType::DELAY;
    }
    if(s == "LOCO_HALT") {
        return ActionType::LOCO_HALT;
    }
    if(s == "LOCO_SPEED") {
        return ActionType::LOCO_SPEED;
    }
    if(s == "LOCO_DIRECTION") {
        return ActionType::LOCO_DIRECTION;
    }
    if(s == "LOCO_FUNCTION") {
        return ActionType::LOCO_FUNCTION;
    }
    if(s == "LOCO_FUNCTION_TRIGGER") {
        return ActionType::LOCO_FUNCTION_TRIGGER;
    }
    if(s == "SWITCHING") {
        return ActionType::SWITCHING;
    }
    if(s == "SEND_ROUTE_SWITCHED") {
        return ActionType::SEND_ROUTE_SWITCHED;
    }
    if(s == "SEND_ROUTE_RELEASED") {
        return ActionType::SEND_ROUTE_RELEASED;
    }
    if(s == "SEND_BLOCK_RELEASED") {
        return ActionType::SEND_BLOCK_RELEASED;
    }
    throw moba::UnsupportedOperationException{"ActionType: invalid value <" + s + "> given"};
}

inline std::string actionTypeEnumToString(ActionType s) {
    switch(s) {
        case ActionType::DELAY:
            return "DELAY";

        case ActionType::LOCO_HALT:
            return "LOCO_HALT";

        case ActionType::LOCO_SPEED:
            return "LOCO_SPEED";

        case ActionType::LOCO_DIRECTION:
            return "LOCO_DIRECTION";

        case ActionType::LOCO_FUNCTION:
            return "LOCO_FUNCTION";

        case ActionType::SWITCHING:
            return "SWITCHING";

        case ActionType::SEND_ROUTE_SWITCHED:
            return "SEND_ROUTE_SWITCHED";

        case ActionType::SEND_ROUTE_RELEASED:
            return "SEND_ROUTE_RELEASED";

        case ActionType::SEND_BLOCK_RELEASED:
            return "SEND_BLOCK_RELEASED";

        default:
            throw moba::UnsupportedOperationException{"ActionType: invalid value given"};
    }
}
