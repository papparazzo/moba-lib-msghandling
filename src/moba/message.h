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
#include <cstddef>
#include <cstdint>
#include <iostream>

#include "nlohmann/json.hpp"

struct Message {
    enum MessageGroup {
        BASE        = 1,
        CLIENT      = 2,
        SERVER      = 3,
        TIMER       = 4,
        ENVIRONMENT = 5,
        INTERFACE   = 6,
        SYSTEM      = 7,
        LAYOUT      = 8,
        GUI         = 9,
        CONTROL     = 10,
    };

    virtual ~Message() noexcept = default;

    virtual nlohmann::json getJsonDocument() const {
        return nlohmann::json{};
    }
};

/* TODO ...
struct GetByOptionalId {
    GetByOptionalId(int id = 0) : id{id} {
    }

    rapidjson::Document getJsonDocument() const {
        rapidjson::Document d;
        if(id) {
            d.SetInt(id);
        } else {
            d.SetNull();
        }
        return d;
    }

    int id;
};

struct GetById {
    GetById(int id) : id{id} {
    }

    rapidjson::Document getJsonDocument() const {
        rapidjson::Document d;
        d.SetInt(id);
        return d;
    }

    int id;
};
*/