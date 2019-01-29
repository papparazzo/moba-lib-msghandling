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



/*
    void MsgEnvHandler::sendSetAmbience(
        JsonToggleState::ToggleState curtainUp, JsonToggleState::ToggleState mainLightOn
    ) {
        JsonObjectPtr obj(new JsonObject());
        (*obj)["curtainUp"   ] = toJsonToggleStatePtr(curtainUp);
        (*obj)["mainLightOn" ] = toJsonToggleStatePtr(mainLightOn);
        msgep->sendMsg(Message(Message::MT_SET_AMBIENCE, obj));
    }

    void MsgEnvHandler::sendSetAmbientLight(const MsgEnvHandler::AmbientLightData &ald) {
        JsonObjectPtr obj(new JsonObject());
        (*obj)["red"  ] = toJsonNumberPtr(ald.red);
        (*obj)["blue" ] = toJsonNumberPtr(ald.blue);
        (*obj)["green"] = toJsonNumberPtr(ald.blue);
        (*obj)["white"] = toJsonNumberPtr(ald.white);
        msgep->sendMsg(Message(Message::MT_SET_AMBIENT_LIGHT, obj));
    }
}
 * */



/*
namespace moba {

    class MsgEnvHandler {
        public:

            void sendGetAmbience() {msgep->sendMsg(Message::MT_GET_AMBIENCE);}

            void sendSetAmbience(JsonToggleState::ToggleState curtainUp, JsonToggleState::ToggleState mainLightOn);

            void sendGetAmbientLight() {msgep->sendMsg(Message::MT_GET_AMBIENT_LIGHT);}

            struct AmbientLightData {
                AmbientLightData() {};
                AmbientLightData(int red, int blue, int green, int white) {
                    this->red = red;
                    this->blue = blue;
                    this->green = green;
                    this->white = white;
                }
                int red;
                int blue;
                int green;
                int white;
            };

            void sendSetAmbientLight(const AmbientLightData &ald);

        protected:
            MsgEndpointPtr msgep;

    };
}
*/
