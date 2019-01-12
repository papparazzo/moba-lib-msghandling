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

#include "socket.h"

#include <moba/version.h>
#include <moba/jsonabstractitem.h>
#include <moba/message.h>

class Endpoint {
    public:
        Endpoint(SocketPtr socket);
        virtual ~Endpoint();

        long connect();

        long connect(const std::string &appName, moba::Version version, const moba::JsonArrayPtr &groups);

        long getAppId() {return appId;}

        auto recieveMsg(time_t timeoutSec) -> moba::MessagePtr;

        // ---- message transmission ----
        void sendMsg(const std::string &msgType, const moba::JsonItemPtr &msgData);

        void sendMsg(const std::string &msgType, const std::string &msgData);

        void sendMsg(const std::string &msgType);

        void sendMsg(const moba::JsonObject &obj);

    protected:
        SocketPtr socket;

        long appId;

        std::string appName;
        moba::Version version;
        moba::JsonArrayPtr groups;

        static const int MSG_HANDLER_TIME_OUT_SEC = 2;
        static const int MSG_HANDLER_TIME_OUT_USEC = 0;

        long registerApp();
        void init();
};
