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
#include <memory>
#include "message.h"
#include "shared.h"
#include "enumtogglestate.h"
#include "enumswitch.h"

struct EnvironmentMessage: Message {
    enum MessageName {
        ENVIRONMENT_GET_ENVIRONMENT     = 1,
        ENVIRONMENT_SET_ENVIRONMENT     = 2,
        ENVIRONMENT_SET_AMBIENCE        = 3,
        ENVIRONMENT_SET_AMBIENT_LIGHT   = 4
    };

    static constexpr std::uint32_t GROUP_ID = ENVIRONMENT;
};

struct EnvironmentGetEnvironment final : EnvironmentMessage {
    static constexpr std::uint32_t MESSAGE_ID = ENVIRONMENT_GET_ENVIRONMENT;
};

struct EnvironmentSetEnvironment final : EnvironmentMessage {
    static constexpr std::uint32_t MESSAGE_ID = ENVIRONMENT_SET_ENVIRONMENT;

    EnvironmentSetEnvironment(
        const Switch thunder,
        const Switch wind,
        const Switch rain,
        const Switch environmentSound,
        const Switch aux1,
        const Switch aux2,
        const Switch aux3
    ) : thunder{thunder}, wind{wind}, rain{rain}, environmentSound{environmentSound}, aux1{aux1}, aux2{aux2}, aux3{aux3} {
    }

    explicit EnvironmentSetEnvironment(const nlohmann::json &d) {
        thunder = stringToSwitchEnum(d["thunderStorm"].get<std::string>());
        wind = stringToSwitchEnum(d["wind"].get<std::string>());
        rain = stringToSwitchEnum(d["rain"].get<std::string>());
        environmentSound = stringToSwitchEnum(d["environmentSound"].get<std::string>());
        aux1 = stringToSwitchEnum(d["aux1"].get<std::string>());
        aux2 = stringToSwitchEnum(d["aux2"].get<std::string>());
        aux3 = stringToSwitchEnum(d["aux3"].get<std::string>());
    }


    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        nlohmann::json d;

        d["thunderStorm"] = switchEnumToString(thunder);
        d["wind"] = switchEnumToString(wind);
        d["rain"] = switchEnumToString(rain);
        d["environmentSound"] = switchEnumToString(environmentSound);
        d["aux01"] = switchEnumToString(aux1);
        d["aux02"] = switchEnumToString(aux2);
        d["aux03"] = switchEnumToString(aux3);

        return d;
    }

    Switch thunder;
    Switch wind;
    Switch rain;
    Switch environmentSound;
    Switch aux1;
    Switch aux2;
    Switch aux3;
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

struct EnvironmentSetAmbientLight final : EnvironmentMessage {
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
        d["blue"] =  blue;
        d["green"] =  green;
        d["white"] =  white;

        return d;
    }

    int red;
    int blue;
    int green;
    int white;
};