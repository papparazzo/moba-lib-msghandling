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

class GetEnvironment : public DispatchMessage {
    public:
        virtual std::string getMessageName() const override {
            return "ENV_GET_ENVIRONMENT";
        }
};

class SetEnvironment : public RecieveMessage, public DispatchMessage {
    public:
        SetEnvironment(
            moba::JsonSwitch::Switch thunder,
            moba::JsonSwitch::Switch wind,
            moba::JsonSwitch::Switch rain,
            moba::JsonSwitch::Switch environmentSound,
            moba::JsonSwitch::Switch aux1,
            moba::JsonSwitch::Switch aux2,
            moba::JsonSwitch::Switch aux3
        );

        SetEnvironment(moba::JsonItemPtr data) {
            //payload = moba::castToString(data);
        }

        virtual std::string getMessageName() const override {
            return "ENV_SET_ENVIRONMENT";
        }

        virtual moba::JsonItemPtr getData() const override;

        moba::JsonSwitch::Switch getThunder() const {
            return thunder;
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
