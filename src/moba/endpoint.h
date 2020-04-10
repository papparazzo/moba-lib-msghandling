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

#include <moba-common/version.h>
#include <memory>
#include <mutex>

#include "basemessage.h"
#include "socket.h"
#include "groups.h"

#include "rapidjson/document.h"

class Endpoint {
public:
    Endpoint(SocketPtr socket, const std::string &appName, moba::common::Version version, Groups groups);

    Endpoint(SocketPtr socket, const std::string &appName, moba::common::Version version);

    virtual ~Endpoint() noexcept;

    long connect();

    long getAppId() {return appId;}

    auto recieveMsg(time_t timeoutSec = 0) -> Message;

    auto waitForNewMsg() -> Message;

    void sendMsg(const Message &msg);

protected:
    SocketPtr socket;

    std::mutex m;

    long appId;

    std::string appName;
    moba::common::Version version;
    Groups groups;

    static const int MSG_HANDLER_TIME_OUT_SEC = 2;
    static const int MSG_HANDLER_TIME_OUT_USEC = 0;

    long registerApp();
};

using EndpointPtr = std::shared_ptr<Endpoint>;
