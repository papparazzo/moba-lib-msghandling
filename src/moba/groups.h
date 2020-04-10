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
#include "rapidjson/document.h"
#include "basemessage.h"

enum class Groups {
    ALL         = 0x0000,
    CLIENT      = 0x0001,
    SERVER      = 0x0002,
    TIMER       = 0x0004,
    ENVIRONMENT = 0x0008,
    INTERFACE   = 0x0010,
    SYSTEM      = 0x0020,
    LAYOUT      = 0x0040,
    GUI         = 0x0080,
};

inline Groups operator |=(Groups lhs, Groups rhs) {
    return static_cast<Groups> (
        static_cast<std::underlying_type<Groups>::type>(lhs) |
        static_cast<std::underlying_type<Groups>::type>(rhs)
    );
}

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

inline rapidjson::Value convertIntoGroupArray(Groups groups) {
    rapidjson::Value g(rapidjson::kArrayType);
    rapidjson::Document document;
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    if(groups == Groups::ALL) {
        return g;
    }
    if((groups & Groups::CLIENT) == Groups::CLIENT) {
        g.PushBack(Message::CLIENT, allocator);
    }
    if((groups & Groups::SERVER) == Groups::SERVER) {
        g.PushBack(Message::SERVER, allocator);
    }
    if((groups & Groups::TIMER) == Groups::TIMER) {
        g.PushBack(Message::TIMER, allocator);
    }
    if((groups & Groups::ENVIRONMENT) == Groups::ENVIRONMENT) {
        g.PushBack(Message::ENVIRONMENT, allocator);
    }
    if((groups & Groups::INTERFACE) == Groups::INTERFACE) {
        g.PushBack(Message::INTERFACE, allocator);
    }
    if((groups & Groups::SYSTEM) == Groups::SYSTEM) {
        g.PushBack(Message::SYSTEM, allocator);
    }
    if((groups & Groups::LAYOUT) == Groups::LAYOUT) {
        g.PushBack(Message::LAYOUT, allocator);
    }
    if((groups & Groups::GUI) == Groups::GUI) {
        g.PushBack(Message::GUI, allocator);
    }
    return g;
}

inline Groups convertFromGroupArray(const rapidjson::Value &v) {
    Groups group;
    for(auto &i : v["msgGroups"].GetArray()) {
        switch(i.GetInt()) {
            case Message::CLIENT:
                group |= Groups::CLIENT;
                break;
            case Message::SERVER:
                group |= Groups::SERVER;
                break;
            case Message::TIMER:
                group |= Groups::TIMER;
                break;
            case Message::ENVIRONMENT:
                group |= Groups::ENVIRONMENT;
                break;
            case Message::INTERFACE:
                group |= Groups::INTERFACE;
                break;
            case Message::SYSTEM:
                group |= Groups::SYSTEM;
                break;
            case Message::LAYOUT:
                group |= Groups::LAYOUT;
                break;
            case Message::GUI:
                group |= Groups::GUI;
                break;
        }
    }
    return group;
}
