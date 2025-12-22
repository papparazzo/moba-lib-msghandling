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
#include "enumtogglestate.h"

struct EnvironmentMessage: Message {
    enum MessageName {
        ENVIRONMENT_GET_FUNCTION_LIST      = 1,
        ENVIRONMENT_SET_FUNCTION_LIST      = 2,
        ENVIRONMENT_SET_FUNCTIONS          = 3,
        ENVIRONMENT_FUNCTION_STATE_CHANGED = 4,
        ENVIRONMENT_SET_AMBIENCE           = 5
    };

    static constexpr std::uint32_t GROUP_ID = ENVIRONMENT;
};

struct EnvironmentGetEnvironment final: EnvironmentMessage {
    static constexpr std::uint32_t MESSAGE_ID = ENVIRONMENT_GET_FUNCTION_LIST;
};

struct EnvironmentSetFunctions final: EnvironmentMessage {
    static constexpr std::uint32_t MESSAGE_ID = ENVIRONMENT_SET_FUNCTIONS;

    EnvironmentSetFunctions() = default;

    explicit EnvironmentSetFunctions(FunctionStateData function) {
        functions.emplace_back(function);
    }

    explicit EnvironmentSetFunctions(const nlohmann::json &d) {
        for(auto &iter: d) {
            functions.emplace_back(iter);
        }
    }
    std::vector<FunctionStateData> functions;
};

struct EnvironmentSetAmbience final : EnvironmentMessage {
    static constexpr std::uint32_t MESSAGE_ID = ENVIRONMENT_SET_AMBIENCE;

    EnvironmentSetAmbience(const ToggleState curtainUp, const ToggleState mainLightOn):
    curtainUp{curtainUp}, mainLightOn{mainLightOn} {
    }

    explicit EnvironmentSetAmbience(const nlohmann::json &d) {
        curtainUp = stringToToggleStateEnum(d["curtainUp"].get<std::string>());
        mainLightOn = stringToToggleStateEnum(d["mainLightOn"].get<std::string>());
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        nlohmann::json d;

        d["curtainUp"] = toggleStateEnumToString(curtainUp);
        d["mainLightOn"] = toggleStateEnumToString(mainLightOn);

        return d;
    }

    ToggleState curtainUp;
    ToggleState mainLightOn;
};
