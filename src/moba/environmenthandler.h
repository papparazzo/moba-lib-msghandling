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
#include <memory>
#include "message.h"
#include "shared.h"

struct EnvironmentMessage : public Message {
    enum MessageName {
        ENVIRONMENT_GET_ENVIRONMENT     = 1,
        ENVIRONMENT_SET_ENVIRONMENT     = 2,
        ENVIRONMENT_GET_AMBIENCE        = 3,
        ENVIRONMENT_SET_AMBIENCE        = 4,
        ENVIRONMENT_GET_AMBIENT_LIGHT   = 5,
        ENVIRONMENT_SET_AMBIENT_LIGHT   = 6
    };

    static constexpr std::uint32_t GROUP_ID = ENVIRONMENT;
};

struct EnvGetEnvironment : public EnvironmentMessage {
    static constexpr std::uint32_t MESSAGE_ID = ENVIRONMENT_GET_ENVIRONMENT;
};

struct EnvSetEnvironment : public EnvironmentMessage {
    static constexpr std::uint32_t MESSAGE_ID = ENVIRONMENT_SET_ENVIRONMENT;

    EnvSetEnvironment(
        Switch thunder,
        Switch wind,
        Switch rain,
        Switch environmentSound,
        Switch aux1,
        Switch aux2,
        Switch aux3
    ) : thunder{thunder}, wind{wind}, rain{rain}, environmentSound{environmentSound}, aux1{aux1}, aux2{aux2}, aux3{aux3} {
    }

    EnvSetEnvironment(const rapidjson::Document &d) {
        thunder = stringToSwitchEnum(d["thunderStorm"].GetString());
        wind = stringToSwitchEnum(d["wind"].GetString());
        rain = stringToSwitchEnum(d["rain"].GetString());
        environmentSound = stringToSwitchEnum(d["environmentSound"].GetString());
        aux1 = stringToSwitchEnum(d["aux1"].GetString());
        aux2 = stringToSwitchEnum(d["aux2"].GetString());
        aux3 = stringToSwitchEnum(d["aux3"].GetString());
    }


    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;

        d.AddMember("thunderStorm", getJsonValue(d, thunder), d.GetAllocator());
        d.AddMember("wind", getJsonValue(d, wind), d.GetAllocator());
        d.AddMember("rain", getJsonValue(d, rain), d.GetAllocator());
        d.AddMember("environmentSound", getJsonValue(d, environmentSound), d.GetAllocator());
        d.AddMember("aux01", getJsonValue(d, aux1), d.GetAllocator());
        d.AddMember("aux02", getJsonValue(d, aux2), d.GetAllocator());
        d.AddMember("aux03", getJsonValue(d, aux3), d.GetAllocator());

        return d;
    }

    Switch thunder;
    Switch wind;
    Switch rain;
    Switch environmentSound;
    Switch aux1;
    Switch aux2;
    Switch aux3;

protected:
    rapidjson::Value getJsonValue(rapidjson::Document &d, Switch c) const {
        auto v = switchEnumToString(c);
        return rapidjson::Value(v.c_str(), v.length(), d.GetAllocator());
    }
};

struct EnvGetAmbience : public EnvironmentMessage {
    static constexpr std::uint32_t MESSAGE_ID = ENVIRONMENT_GET_AMBIENCE;
};


struct EnvSetAmbience : public EnvironmentMessage {
    static constexpr std::uint32_t MESSAGE_ID = ENVIRONMENT_SET_AMBIENCE;

    EnvSetAmbience(
        ToggleState curtainUp, ToggleState mainLightOn
    ) : curtainUp{curtainUp}, mainLightOn{mainLightOn} {
    }

    EnvSetAmbience(const rapidjson::Document &d) {
        curtainUp = stringToToggleStateEnum(d["curtainUp"].GetString());
        mainLightOn = stringToToggleStateEnum(d["mainLightOn"].GetString());
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;

        d.AddMember("curtainUp", getJsonValue(d, curtainUp), d.GetAllocator());
        d.AddMember("mainLightOn", getJsonValue(d, mainLightOn), d.GetAllocator());
        return d;
    }

    ToggleState curtainUp;
    ToggleState mainLightOn;

protected:
    rapidjson::Value getJsonValue(rapidjson::Document &d, ToggleState c) const {
        auto v = toggleStateEnumToString(c);
        return rapidjson::Value(v.c_str(), v.length(), d.GetAllocator());
    }
};

struct EnvGetAmbientLight : public EnvironmentMessage {
    static constexpr std::uint32_t MESSAGE_ID = ENVIRONMENT_GET_AMBIENT_LIGHT;
};

struct EnvSetAmbientLight : public EnvironmentMessage {
    static constexpr std::uint32_t MESSAGE_ID = ENVIRONMENT_SET_AMBIENT_LIGHT;

    EnvSetAmbientLight(
        int red, int blue, int green, int white
    ) : red{red}, blue{blue}, green{green}, white{white} {
    }

    EnvSetAmbientLight(const rapidjson::Document &d) {
        red = d["red"].GetInt();
        blue = d["blue"].GetInt();
        green = d["green"].GetInt();
        white = d["white"].GetInt();
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.AddMember("red", red, d.GetAllocator());
        d.AddMember("blue", blue, d.GetAllocator());
        d.AddMember("green", green, d.GetAllocator());
        d.AddMember("white", white, d.GetAllocator());

        return d;
    }

    int red;
    int blue;
    int green;
    int white;
};