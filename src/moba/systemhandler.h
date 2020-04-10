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

#include "basemessage.h"

struct SystemMessage : public Message {
    enum MessageName {
        SET_AUTOMATIC_MODE      = 1,
        SET_EMERGENCY_STOP      = 2,
        SET_STANDBY_MODE        = 3,
        GET_HARDWARE_STATE      = 4,
        HARDWARE_STATE_CHANGED  = 5,
        HARDWARE_SHUTDOWN       = 6,
        HARDWARE_RESET          = 7
    };

    SystemMessage(unsigned char msgId) : Message{SYSTEM, msgId} {
    }
};

struct SystemSetAutomaticMode : public SystemMessage {
    SystemSetAutomaticMode(bool automaticActive) : SystemMessage{SET_AUTOMATIC_MODE} {
        data.SetBool(automaticActive);
    }
};

struct SystemSetEmergencyStop : public SystemMessage {
    SystemSetEmergencyStop(bool emergencyStopActive) : SystemMessage{SET_EMERGENCY_STOP} {
        data.SetBool(emergencyStopActive);
    }
};



/*


struct SystemSetStandbyMode : public DispatchMessageType<SystemSetStandbyMode> {
    SystemSetStandbyMode(bool standbyActive) : standbyActive{standbyActive} {
    }

    static std::string getMessageName() {
        return "SET_STANDBY_MODE";
    }

    virtual moba::JsonItemPtr getData() const override {
        return moba::toJsonBoolPtr(standbyActive);
    }

    bool standbyActive;
};
*/
struct SystemGetHardwareState : public SystemMessage {
    SystemGetHardwareState() : SystemMessage{GET_HARDWARE_STATE} {
    }
};
/*
struct SystemHardwareStateChanged : public RecieveMessage {
    enum class HardwareState {
        ERROR,
        STANDBY,
        EMERGENCY_STOP,
        MANUEL,
        AUTOMATIC
    };

    SystemHardwareStateChanged(moba::JsonItemPtr data) {
        std::string status = moba::castToString(data);
        if(status == "ERROR") {
            hardwareState = HardwareState::ERROR;
        } else if(status == "EMERGENCY_STOP") {
            hardwareState = HardwareState::EMERGENCY_STOP;
        } else if(status == "STANDBY") {
            hardwareState = HardwareState::STANDBY;
        } else if(status == "MANUEL") {
            hardwareState = HardwareState::MANUEL;
        } else if(status == "AUTOMATIC") {
            hardwareState = HardwareState::AUTOMATIC;
        }
    }

    static std::string getMessageName() {
        return "HARDWARE_STATE_CHANGED";
    }

    HardwareState hardwareState;
};

struct SystemHardwareShutdown : public DispatchMessageType<SystemHardwareShutdown> {
    static std::string getMessageName() {
        return "HARDWARE_SHUTDOWN";
    }
};

struct SystemHardwareReset : public DispatchMessageType<SystemHardwareReset> {
    static std::string getMessageName() {
        return "HARDWARE_RESET";
    }
};
*/