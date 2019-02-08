/*
 *  Project:    moba-common
 *
 *  Copyright (C) 2016 Stefan Paproth <pappi-@gmx.de>
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
#include "basemessage.h"
#include <moba/jsonabstractitem.h>

struct EnvGetEnvironment : public DispatchMessageType<EnvGetEnvironment> {
    static std::string getMessageName() {
        return "ENV_GET_ENVIRONMENT";
    }
};

struct EnvSetEnvironment : public RecieveMessage, public DispatchMessageType<EnvSetEnvironment> {
    EnvSetEnvironment(
        moba::JsonSwitch::Switch thunder,
        moba::JsonSwitch::Switch wind,
        moba::JsonSwitch::Switch rain,
        moba::JsonSwitch::Switch environmentSound,
        moba::JsonSwitch::Switch aux1,
        moba::JsonSwitch::Switch aux2,
        moba::JsonSwitch::Switch aux3
    ) : thunder{thunder}, wind{wind}, rain{rain}, environmentSound{environmentSound}, aux1{aux1}, aux2{aux2}, aux3{aux3} {
    }

    EnvSetEnvironment(moba::JsonItemPtr data) {
        auto o = boost::dynamic_pointer_cast<moba::JsonObject>(data);
        thunder = moba::castToSwitch(o->at("thunderStorm"));
        wind = moba::castToSwitch(o->at("wind"));
        rain = moba::castToSwitch(o->at("rain"));
        environmentSound = moba::castToSwitch(o->at("environmentSound"));
        aux01 = moba::castToSwitch(o->at("aux1"));
        aux02 = moba::castToSwitch(o->at("aux2"));
        aux03 = moba::castToSwitch(o->at("aux3"));
    }

    static std::string getMessageName() {
        return "ENV_SET_ENVIRONMENT";
    }

    virtual moba::JsonItemPtr getData() const override {
        moba::JsonObjectPtr obj(new moba::JsonObject());
        (*obj)["thunderStorm"      ] = moba::toJsonSwitchPtr(thunder);
        (*obj)["wind"              ] = moba::toJsonSwitchPtr(wind);
        (*obj)["rain"              ] = moba::toJsonSwitchPtr(rain);
        (*obj)["environmentSound"  ] = moba::toJsonSwitchPtr(environmentSound);
        (*obj)["aux01"             ] = moba::toJsonSwitchPtr(aux1);
        (*obj)["aux02"             ] = moba::toJsonSwitchPtr(aux2);
        (*obj)["aux03"             ] = moba::toJsonSwitchPtr(aux3);
        return obj;
    }

    moba::JsonSwitch::Switch thunder;
    moba::JsonSwitch::Switch wind;
    moba::JsonSwitch::Switch rain;
    moba::JsonSwitch::Switch environmentSound;
    moba::JsonSwitch::Switch aux1;
    moba::JsonSwitch::Switch aux2;
    moba::JsonSwitch::Switch aux3;
};

struct EnvGetAmbience : public DispatchMessageType<EnvGetAmbience> {
    static std::string getMessageName() {
        return "ENV_GET_AMBIENCE";
    }
};

struct EnvSetAmbience : public RecieveMessage, public DispatchMessageType<EnvSetAmbience> {
    EnvSetAmbience(
        moba::JsonToggleState::ToggleState curtainUp,
        moba::JsonToggleState::ToggleState mainLightOn
    ) : curtainUp{curtainUp}, mainLightOn{mainLightOn} {
    }

    EnvSetAmbience(moba::JsonItemPtr data) {
        auto o = boost::dynamic_pointer_cast<moba::JsonObject>(data);
        curtainUp = moba::castToJsonToggleState(o->at("curtainUp"));
        mainLightOn = moba::castToJsonToggleState(o->at("mainLightOn"));
    }

    static std::string getMessageName() {
        return "ENV_SET_AMBIENCE";
    }

    virtual moba::JsonItemPtr getData() const override {
        moba::JsonObjectPtr obj(new moba::JsonObject());
        (*obj)["curtainUp"  ] = moba::toJsonToggleStatePtr(curtainUp);
        (*obj)["mainLightOn"] = moba::toJsonToggleStatePtr(mainLightOn);
        return obj;
    }

    moba::JsonToggleState::ToggleState curtainUp,
    moba::JsonToggleState::ToggleState mainLightOn
};

struct EnvGetAmbientLight : public DispatchMessageType<EnvGetAmbientLight> {
    static std::string getMessageName() {
        return "ENV_GET_AMBIENT_LIGHT";
    }
};

struct EnvSetAmbientLight : public RecieveMessage, public DispatchMessageType<EnvSetAmbientLight> {

    EnvSetAmbientLight(
        int red, int blue, int green, int white
    ) : red{red}, blue{blue}, green{green}, white{white} {
    }

    EnvSetAmbience(moba::JsonItemPtr data) {
        auto o = boost::dynamic_pointer_cast<moba::JsonObject>(data);
        red = moba::castToInt(o->at("red"));
        blue = moba::castToInt(o->at("blue"));
        green = moba::castToInt(o->at("green"));
        white = moba::castToInt(o->at("white"));
    }

    static std::string getMessageName() {
        return "ENV_SET_AMBIENT_LIGHT";
    }

    virtual moba::JsonItemPtr getData() const override {
        moba::JsonObjectPtr obj(new moba::JsonObject());
        (*obj)["red"  ] = moba::toJsonNumberPtr(red);
        (*obj)["blue" ] = moba::toJsonNumberPtr(blue);
        (*obj)["green"] = moba::toJsonNumberPtr(green);
        (*obj)["white"] = moba::toJsonNumberPtr(white);
        return obj;
    }

    int red;
    int blue;
    int green;
    int white;
};
