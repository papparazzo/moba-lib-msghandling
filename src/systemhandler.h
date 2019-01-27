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

class SystemSetAutomaticMode : public DispatchMessage {
    public:
        SystemSetAutomaticMode(bool automaticActive) : automaticActive{automaticActive} {
        }

        virtual std::string getMessageName() const override {
            return "SYSTEM_SET_AUTOMATIC_MODE";
        }

        virtual moba::JsonItemPtr getData() const override {
            return moba::toJsonBoolPtr(automaticActive);
        }

    protected:
        bool automaticActive;
};

class SystemSetEmergencyStop : public DispatchMessage {
    public:
        SystemSetEmergencyStop(bool emergencyStopActive) : emergencyStopActive{emergencyStopActive} {
        }

        virtual std::string getMessageName() const override {
            return "SYSTEM_SET_EMERGENCY_STOP";
        }

        virtual moba::JsonItemPtr getData() const override {
            return moba::toJsonBoolPtr(emergencyStopActive);
        }

    protected:
        bool emergencyStopActive;
};

class SystemSetStandbyMode : public DispatchMessage {
    public:
        SystemSetStandbyMode(bool standbyActive) : standbyActive{standbyActive} {
        }

        virtual std::string getMessageName() const override {
            return "SYSTEM_SET_STANDBY_MODE";
        }

        virtual moba::JsonItemPtr getData() const override {
            return moba::toJsonBoolPtr(emergencyStopActive);
        }

    protected:
        bool standbyActive;
};

class SystemGetHardwareState : public DispatchMessage {
    public:
        virtual std::string getMessageName() const override {
            return "SYSTEM_SET_STANDBY_MODE";
        }
};





/*


SYSTEM_HARDWARE_STATE_CHANGED
SYSTEM_HARDWARE_SHUTDOWN
SYSTEM_HARDWARE_RESET

 */








            void sendSetAutomaticMode(bool on) {msgep->sendMsg(Message::MT_SET_AUTOMATIC_MODE, toJsonBoolPtr(on));}

            void sendSetEmergencyStop(bool on) {msgep->sendMsg(Message::MT_SET_EMERGENCY_STOP, toJsonBoolPtr(on));}

            void sendSetStandByMode(bool on) {msgep->sendMsg(Message::MT_SET_STANDBY_MODE, toJsonBoolPtr(on));}

            void sendGetHardwareState()  {msgep->sendMsg(Message::MT_GET_HARDWARE_STATE);}

            void sendHardwareShutdown() {msgep->sendMsg(Message::MT_HARDWARE_SHUTDOWN);}

            void sendHardwareReset() {msgep->sendMsg(Message::MT_HARDWARE_RESET);}

            enum NoticeType {
                NT_INFO,
                NT_WARNING,
                NT_ERROR
            };

            void sendSystemNotice(NoticeType type, const std::string &caption, const std::string &text);

        protected:
            MsgEndpointPtr msgep;
    };

