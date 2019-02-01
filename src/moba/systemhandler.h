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

#include <moba/jsonabstractitem.h>
#include "basemessage.h"

struct SystemSetAutomaticMode : public DispatchMessage {

    SystemSetAutomaticMode(bool automaticActive) : automaticActive{automaticActive} {
    }

    virtual std::string getMessageName() const override {
        return "SYSTEM_SET_AUTOMATIC_MODE";
    }

    virtual moba::JsonItemPtr getData() const override {
        return moba::toJsonBoolPtr(automaticActive);
    }

    bool automaticActive;
};

struct SystemSetEmergencyStop : public DispatchMessage {

    SystemSetEmergencyStop(bool emergencyStopActive) : emergencyStopActive{emergencyStopActive} {
    }

    virtual std::string getMessageName() const override {
        return "SYSTEM_SET_EMERGENCY_STOP";
    }

    virtual moba::JsonItemPtr getData() const override {
        return moba::toJsonBoolPtr(emergencyStopActive);
    }

    bool emergencyStopActive;
};

struct SystemSetStandbyMode : public DispatchMessage {
    SystemSetStandbyMode(bool standbyActive) : standbyActive{standbyActive} {
    }

    virtual std::string getMessageName() const override {
        return "SYSTEM_SET_STANDBY_MODE";
    }

    virtual moba::JsonItemPtr getData() const override {
        return moba::toJsonBoolPtr(standbyActive);
    }

    bool standbyActive;
};

struct SystemGetHardwareState : public DispatchMessage {
    virtual std::string getMessageName() const override {
        return "SYSTEM_SET_STANDBY_MODE";
    }
};

struct SystemHardwareStateChanged : public RecieveMessage {
    enum HardwareState {
        ERROR,
        STANDBY,
        EMERGENCY_STOP,
        MANUEL,
        AUTOMATIC
    };

    SystemHardwareStateChanged(moba::JsonItemPtr data) {
        std::string status = moba::castToString(data);
        if(status == "ERROR") {
            hardwareState = ERROR;
        } else if(status == "EMERGENCY_STOP") {
            hardwareState = EMERGENCY_STOP;
        } else if(status == "STANDBY") {
            hardwareState = STANDBY;
        } else if(status == "MANUEL") {
            hardwareState = MANUEL;
        } else if(status == "AUTOMATIC") {
            hardwareState = AUTOMATIC;
        }
    }

    virtual std::string getMessageName() const override {
        return "SYSTEM_HARDWARE_STATE_CHANGED";
    }

    HardwareState hardwareState;
};

struct SystemHardwareShutdown : public DispatchMessage {
    virtual std::string getMessageName() const override {
        return "SYSTEM_HARDWARE_SHUTDOWN";
    }
};

struct SystemHardwareReset : public DispatchMessage {
    virtual std::string getMessageName() const override {
        return "SYSTEM_HARDWARE_RESET";
    }
};
