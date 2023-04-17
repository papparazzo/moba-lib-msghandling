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

#include "message.h"

struct SystemMessage: public Message {
    enum MessageName {
        SYSTEM_SET_AUTOMATIC_MODE      = 1,
        SYSTEM_TOGGLE_AUTOMATIC_MODE   = 2,
        SYSTEM_TRIGGER_EMERGENCY_STOP  = 3,
        SYSTEM_RELEASE_EMERGENCY_STOP  = 4,
        SYSTEM_SET_STANDBY_MODE        = 5,
        SYSTEM_TOGGLE_STANDBY_MODE     = 6,
        SYSTEM_GET_HARDWARE_STATE      = 7,
        SYSTEM_HARDWARE_STATE_CHANGED  = 8,
        SYSTEM_HARDWARE_SHUTDOWN       = 9,
        SYSTEM_HARDWARE_RESET          = 10
    };

    static constexpr std::uint32_t GROUP_ID = SYSTEM;
};

struct SystemSetAutomaticMode: public SystemMessage {
    static constexpr std::uint32_t MESSAGE_ID = SYSTEM_SET_AUTOMATIC_MODE;

    SystemSetAutomaticMode(const rapidjson::Document &d) {
        automaticActive = d.GetBool();
    }

    SystemSetAutomaticMode(bool automaticActive) : automaticActive{automaticActive} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetBool(automaticActive);
        return d;
    }

    bool automaticActive;
};

struct SystemToggleAutomaticMode: public SystemMessage {
    static constexpr std::uint32_t MESSAGE_ID = SYSTEM_TOGGLE_AUTOMATIC_MODE;
};

struct SystemTriggerEmergencyStop: public SystemMessage {
    static constexpr std::uint32_t MESSAGE_ID = SYSTEM_TRIGGER_EMERGENCY_STOP;

    enum class EmergencyTriggerReason {
        CENTRAL_STATION,
        EXTERN,
        SOFTWARE_MANUELL,
        SELF_ACTING_BY_EXTERN_SWITCHING
    };

    SystemTriggerEmergencyStop(
        EmergencyTriggerReason emergencyTriggerReason = EmergencyTriggerReason::SOFTWARE_MANUELL
    ) : emergencyTriggerReason{emergencyTriggerReason} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;

        switch(emergencyTriggerReason) {
            case EmergencyTriggerReason::CENTRAL_STATION:
                d.SetString("CENTRAL_STATION");
                break;

            case EmergencyTriggerReason::SOFTWARE_MANUELL:
                d.SetString("SOFTWARE_MANUELL");
                break;

            case EmergencyTriggerReason::SELF_ACTING_BY_EXTERN_SWITCHING:
                d.SetString("SELF_ACTING_BY_EXTERN_SWITCHING");
                break;

            default:
            case EmergencyTriggerReason::EXTERN:
                d.SetString("EXTERN");
                break;
        }
        return d;
    }
    EmergencyTriggerReason emergencyTriggerReason;
};

struct SystemReleaseEmergencyStop: public SystemMessage {
    static constexpr std::uint32_t MESSAGE_ID = SYSTEM_RELEASE_EMERGENCY_STOP;
};

struct SystemSetStandbyMode: public SystemMessage {
    static constexpr std::uint32_t MESSAGE_ID = SYSTEM_SET_STANDBY_MODE;

    SystemSetStandbyMode(bool standbyActive) : standbyActive{standbyActive} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetBool(standbyActive);
        return d;
    }
    bool standbyActive;
};

struct SystemToggleStandbyMode: public SystemMessage {
    static constexpr std::uint32_t MESSAGE_ID = SYSTEM_TOGGLE_STANDBY_MODE;
};

struct SystemGetHardwareState: public SystemMessage {
    static constexpr std::uint32_t MESSAGE_ID = SYSTEM_GET_HARDWARE_STATE;

    SystemGetHardwareState() {
    }
};

struct SystemHardwareStateChanged: public SystemMessage {
    static constexpr std::uint32_t MESSAGE_ID = SYSTEM_HARDWARE_STATE_CHANGED;

    enum class HardwareState {
        ERROR,
        STANDBY,
        EMERGENCY_STOP,
        MANUEL,
        AUTOMATIC
    };

    SystemHardwareStateChanged(const rapidjson::Document &d) {
        std::string status = d.GetString();
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

    HardwareState hardwareState;
};

struct SystemHardwareShutdown: public SystemMessage {
    static constexpr std::uint32_t MESSAGE_ID = SYSTEM_HARDWARE_SHUTDOWN;
};

struct SystemHardwareReset: public SystemMessage {
    static constexpr std::uint32_t MESSAGE_ID = SYSTEM_HARDWARE_RESET;
};
