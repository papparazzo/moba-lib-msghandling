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

#include <moba/jsonabstractitem.h>
#include "basemessage.h"

struct SystemSetAutomaticMode : public DispatchMessageType<SystemSetAutomaticMode> {

    SystemSetAutomaticMode(bool automaticActive) : automaticActive{automaticActive} {
    }

    static std::string getMessageName() {
        return "SET_AUTOMATIC_MODE";
    }

    virtual moba::JsonItemPtr getData() const override {
        return moba::toJsonBoolPtr(automaticActive);
    }

    bool automaticActive;
};

struct SystemSetEmergencyStop : public DispatchMessageType<SystemSetEmergencyStop> {

    SystemSetEmergencyStop(bool emergencyStopActive) : emergencyStopActive{emergencyStopActive} {
    }

    static std::string getMessageName() {
        return "SET_EMERGENCY_STOP";
    }

    virtual moba::JsonItemPtr getData() const override {
        return moba::toJsonBoolPtr(emergencyStopActive);
    }

    bool emergencyStopActive;
};

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

struct SystemGetHardwareState : public DispatchMessageType<SystemGetHardwareState> {
    static std::string getMessageName() {
        return "GET_HARDWARE_STATE";
    }
};

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
