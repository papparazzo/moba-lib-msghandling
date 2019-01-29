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

class EnvGetEnvironment : public DispatchMessage {
    public:
        virtual std::string getMessageName() const override {
            return "ENV_GET_ENVIRONMENT";
        }
};

class EnvSetEnvironment : public RecieveMessage, public DispatchMessage {
    public:
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

        virtual std::string getMessageName() const override {
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

        moba::JsonSwitch::Switch getThunder() const {
            return thunder;
        }

        moba::JsonSwitch::Switch getWind() const {
            return wind;
        }

        moba::JsonSwitch::Switch getRain() const {
            return rain;
        }

        moba::JsonSwitch::Switch getEnvironmentSound() const {
            return environmentSound;
        }

        moba::JsonSwitch::Switch getAux1() const {
            return aux1;
        }

        moba::JsonSwitch::Switch getAux2() const {
            return aux2;
        }

        moba::JsonSwitch::Switch getAux3() const {
            return aux3;
        }

    protected:
        moba::JsonSwitch::Switch thunder;
        moba::JsonSwitch::Switch wind;
        moba::JsonSwitch::Switch rain;
        moba::JsonSwitch::Switch environmentSound;
        moba::JsonSwitch::Switch aux1;
        moba::JsonSwitch::Switch aux2;
        moba::JsonSwitch::Switch aux3;
};

class EnvGetAmbience : public DispatchMessage {
    public:
        virtual std::string getMessageName() const override {
            return "ENV_GET_AMBIENCE";
        }
};

class EnvSetAmbience : public RecieveMessage, public DispatchMessage {
    public:
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

        virtual std::string getMessageName() const override {
            return "ENV_SET_AMBIENCE";
        }

        virtual moba::JsonItemPtr getData() const override {
            moba::JsonObjectPtr obj(new moba::JsonObject());
            (*obj)["curtainUp"  ] = moba::toJsonToggleStatePtr(curtainUp);
            (*obj)["mainLightOn"] = moba::toJsonToggleStatePtr(mainLightOn);
            return obj;
        }

        moba::JsonSwitch::Switch getCurtainUp() const {
            return curtainUp;
        }

        moba::JsonSwitch::Switch getMainLightOn() const {
            return mainLightOn;
        }

    protected:
        moba::JsonToggleState::ToggleState curtainUp,
        moba::JsonToggleState::ToggleState mainLightOn
};

class EnvGetAmbientLight : public DispatchMessage {
    public:
        virtual std::string getMessageName() const override {
            return "ENV_GET_AMBIENT_LIGHT";
        }
};

class EnvSetAmbientLight : public RecieveMessage, public DispatchMessage {
    public:
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

        virtual std::string getMessageName() const override {
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

        int getRed() const {
            return red;
        }

        int getBlue() const {
            return blue;
        }

        int getGreen() const {
            return green;
        }

        int getWhite() const {
            return white;
        }

    protected:
        int red;
        int blue;
        int green;
        int white;
};
