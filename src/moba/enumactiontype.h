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
    VOID,
    DELAY,

    LOCO_EMERGENCY_STOP,
    LOCO_SPEED,
    LOCO_DIRECTION,
    LOCO_FUNCTION_ON,
    LOCO_FUNCTION_OFF,
    LOCO_FUNCTION_IMPULSE,

    SWITCHING_ON,
    SWITCHING_OFF,
    SWITCHING_IMPULSE,

    ROUTING_SWITCH_ROUTE,
    ROUTING_ROUTE_SWITCHED,
    ROUTING_CLEAR_ROUTE,

    BLOCK_CLEAR_BLOCK
};

inline ActionType stringToActionTypeEnum(const std::string &s) {
    if(s == "VOID") {
        return ActionType::VOID;
    }
    if(s == "DELAY") {
        return ActionType::DELAY;
    }
    if(s == "LOCO_EMERGENCY_STOP") {
        return ActionType::LOCO_EMERGENCY_STOP;
    }
    if(s == "LOCO_SPEED") {
        return ActionType::LOCO_SPEED;
    }
    if(s == "LOCO_DIRECTION") {
        return ActionType::LOCO_DIRECTION;
    }
    if(s == "LOCO_FUNCTION_ON") {
        return ActionType::LOCO_FUNCTION_ON;
    }
    if(s == "LOCO_FUNCTION_OFF") {
        return ActionType::LOCO_FUNCTION_OFF;
    }
    if(s == "LOCO_FUNCTION_IMPULSE") {
        return ActionType::LOCO_FUNCTION_IMPULSE;
    }
    if(s == "SWITCHING_ON") {
        return ActionType::SWITCHING_ON;
    }
    if(s == "SWITCHING_OFF") {
        return ActionType::SWITCHING_OFF;
    }
    if(s == "SWITCHING_IMPULSE") {
        return ActionType::SWITCHING_IMPULSE;
    }
    if(s == "ROUTING_SWITCH_ROUTE") {
        return ActionType::ROUTING_SWITCH_ROUTE;
    }
    if(s == "ROUTING_ROUTE_SWITCHED") {
        return ActionType::ROUTING_ROUTE_SWITCHED;
    }
    if(s == "ROUTING_CLEAR_ROUTE") {
        return ActionType::ROUTING_CLEAR_ROUTE;
    }
    if(s == "BLOCK_CLEAR_BLOCK") {
        return ActionType::BLOCK_CLEAR_BLOCK;
    }
    throw moba::UnsupportedOperationException{"ActionType: invalid value given"};
}

inline std::string actionTypeEnumToString(ActionType s) {
    switch(s) {
        case ActionType::VOID:
            return "VOID";

        case ActionType::DELAY:
            return "DELAY";

        case ActionType::LOCO_EMERGENCY_STOP:
            return "LOCO_EMERGENCY_STOP";

        case ActionType::LOCO_SPEED:
            return "LOCO_SPEED";

        case ActionType::LOCO_DIRECTION:
            return "LOCO_DIRECTION";

        case ActionType::LOCO_FUNCTION_ON:
            return "LOCO_FUNCTION_ON";

        case ActionType::LOCO_FUNCTION_OFF:
            return "LOCO_FUNCTION_OFF";

        case ActionType::LOCO_FUNCTION_IMPULSE:
            return "LOCO_FUNCTION_IMPULSE";

        case ActionType::SWITCHING_ON:
            return "SWITCHING_ON";

        case ActionType::SWITCHING_OFF:
            return "SWITCHING_OFF";

        case ActionType::SWITCHING_IMPULSE:
            return "SWITCHING_IMPULSE";

        case ActionType::ROUTING_SWITCH_ROUTE:
            return "ROUTING_SWITCH_ROUTE";

        case ActionType::ROUTING_ROUTE_SWITCHED:
            return "ROUTING_ROUTE_SWITCHED";

        case ActionType::ROUTING_CLEAR_ROUTE:
            return "ROUTING_CLEAR_ROUTE";

        case ActionType::BLOCK_CLEAR_BLOCK:
            return "BLOCK_CLEAR_BLOCK";

        default:
            throw moba::UnsupportedOperationException{"ActionType: invalid value given"};
    }
}
