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
 *  along with this program. If not, see <https://www.gnu.org/licenses/agpl.txt>.
 *
 */

#pragma once

#include "message.h"

struct SystemMessage: Message {
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

struct SystemSetAutomaticMode final: SystemMessage {
    static constexpr std::uint32_t MESSAGE_ID = SYSTEM_SET_AUTOMATIC_MODE;

    explicit SystemSetAutomaticMode(const nlohmann::json &d) {
        automaticActive = d.get<bool>();
    }

    explicit SystemSetAutomaticMode(const bool automaticActive) : automaticActive{automaticActive} {
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        return automaticActive;
    }

    bool automaticActive;
};

struct SystemToggleAutomaticMode final: SystemMessage {
    static constexpr std::uint32_t MESSAGE_ID = SYSTEM_TOGGLE_AUTOMATIC_MODE;
};

struct SystemTriggerEmergencyStop final: SystemMessage {
    static constexpr std::uint32_t MESSAGE_ID = SYSTEM_TRIGGER_EMERGENCY_STOP;

    enum class EmergencyTriggerReason {
        CENTRAL_STATION,
        EXTERN,
        SOFTWARE_ERROR,
        SOFTWARE_MANUAL,
        SELF_ACTING_BY_EXTERN_SWITCHING
    };

    explicit SystemTriggerEmergencyStop(
        const EmergencyTriggerReason emergencyTriggerReason = EmergencyTriggerReason::SOFTWARE_MANUAL
    ) : emergencyTriggerReason{emergencyTriggerReason} {
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        switch(emergencyTriggerReason) {
            case EmergencyTriggerReason::CENTRAL_STATION:
                return "CENTRAL_STATION";

            case EmergencyTriggerReason::SOFTWARE_ERROR:
                return "SOFTWARE_ERROR";

            case EmergencyTriggerReason::SOFTWARE_MANUAL:
                return "SOFTWARE_MANUAL";

            case EmergencyTriggerReason::SELF_ACTING_BY_EXTERN_SWITCHING:
                return "SELF_ACTING_BY_EXTERN_SWITCHING";

            default:
            case EmergencyTriggerReason::EXTERN:
                return "EXTERN";
        }
    }

    EmergencyTriggerReason emergencyTriggerReason;
};

struct SystemReleaseEmergencyStop final: SystemMessage {
    static constexpr std::uint32_t MESSAGE_ID = SYSTEM_RELEASE_EMERGENCY_STOP;
};

struct SystemSetStandbyMode final: SystemMessage {
    static constexpr std::uint32_t MESSAGE_ID = SYSTEM_SET_STANDBY_MODE;

    explicit SystemSetStandbyMode(const bool standbyActive) : standbyActive{standbyActive} {
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        return standbyActive;
    }
    bool standbyActive;
};

struct SystemToggleStandbyMode final: SystemMessage {
    static constexpr std::uint32_t MESSAGE_ID = SYSTEM_TOGGLE_STANDBY_MODE;
};

struct SystemGetHardwareState final: SystemMessage {
    static constexpr std::uint32_t MESSAGE_ID = SYSTEM_GET_HARDWARE_STATE;

    SystemGetHardwareState() = default;
};

struct SystemHardwareStateChanged final: SystemMessage {
    static constexpr std::uint32_t MESSAGE_ID = SYSTEM_HARDWARE_STATE_CHANGED;

    enum class HardwareState {
        ERROR,
        STANDBY,
        EMERGENCY_STOP,
        MANUEL,
        AUTOMATIC
    };

    explicit SystemHardwareStateChanged(const nlohmann::json &d) {
        if(const auto status = d.get<std::string>(); status == "ERROR") {
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

struct SystemHardwareShutdown final: SystemMessage {
    static constexpr std::uint32_t MESSAGE_ID = SYSTEM_HARDWARE_SHUTDOWN;
};

struct SystemHardwareReset final: SystemMessage {
    static constexpr std::uint32_t MESSAGE_ID = SYSTEM_HARDWARE_RESET;
};
