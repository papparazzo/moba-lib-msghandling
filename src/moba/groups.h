/*
 *  Project:    moba-edit
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

#include <type_traits>

enum class Groups {
    CLIENT      = 0x0001,
    SERVER      = 0x0002,
    TIMER       = 0x0004,
    ENVIRONMENT = 0x0008,
    INTERFACE   = 0x0010,
    SYSTEM      = 0x0020,
    LAYOUT      = 0x0040,
    CONTROL     = 0x0080,
    GUI         = 0x0100,
};

inline Groups operator |(Groups lhs, Groups rhs) {
    return static_cast<Groups> (
        static_cast<std::underlying_type<Groups>::type>(lhs) |
        static_cast<std::underlying_type<Groups>::type>(rhs)
    );
}

inline Groups operator &(Groups lhs, Groups rhs) {
    return static_cast<Groups> (
        static_cast<std::underlying_type<Groups>::type>(lhs) &
        static_cast<std::underlying_type<Groups>::type>(rhs)
    );
}