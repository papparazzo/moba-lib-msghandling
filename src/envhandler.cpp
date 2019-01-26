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

#include "envhandler.h"

SetEnvironment::SetEnvironment(
    moba::JsonSwitch::Switch thunder, moba::JsonSwitch::Switch wind, moba::JsonSwitch::Switch rain,
    moba::JsonSwitch::Switch environmentSound, moba::JsonSwitch::Switch aux1, moba::JsonSwitch::Switch aux2,
    moba::JsonSwitch::Switch aux3
) : thunder{thunder}, wind{wind}, rain{rain}, environmentSound{environmentSound}, aux1{aux1}, aux2{aux2}, aux3{aux3} {
}

moba::JsonItemPtr SetEnvironment::getData() const {
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