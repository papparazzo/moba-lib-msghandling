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

#include <memory>
#include "message.h"
#include "shared.h"

struct EnvironmentMessage: Message {
    enum MessageName {
        ENVIRONMENT_GET_FUNCTION_LIST      = 1,
        ENVIRONMENT_SET_FUNCTION_LIST      = 2,
        ENVIRONMENT_SET_FUNCTIONS          = 3,
        ENVIRONMENT_FUNCTION_STATE_CHANGED = 4
    };

    static constexpr std::uint32_t GROUP_ID = ENVIRONMENT;
};

struct EnvironmentGetEnvironment final: EnvironmentMessage {
    static constexpr std::uint32_t MESSAGE_ID = ENVIRONMENT_GET_FUNCTION_LIST;
};

struct EnvironmentSetFunctions final: EnvironmentMessage {
    static constexpr std::uint32_t MESSAGE_ID = ENVIRONMENT_SET_FUNCTIONS;

    EnvironmentSetFunctions() = default;

    explicit EnvironmentSetFunctions(const nlohmann::json &d) {
        for(auto &iter: d) {
            functions.emplace_back(iter);
        }
    }
    std::vector<FunctionStateData> functions;
};


/*
struct EnvironmentSetAmbientLight final: EnvironmentMessage {
    static constexpr std::uint32_t MESSAGE_ID = ENVIRONMENT_SET_AMBIENT_LIGHT;

    EnvironmentSetAmbientLight(const int red, const int blue, const int green, const int white):
    red{red}, blue{blue}, green{green}, white{white} {
    }

    explicit EnvironmentSetAmbientLight(const nlohmann::json &d) {
        red = d["red"].get<int>();
        blue = d["blue"].get<int>();
        green = d["green"].get<int>();
        white = d["white"].get<int>();
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        nlohmann::json d;

        d["red"] = red;
        d["blue"] = blue;
        d["green"] = green;
        d["white"] = white;

        return d;
    }

    int red;
    int blue;
    int green;
    int white;
};
*/