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

#include "rawmessage.h"
#include "socket.h"
#include "shared.h"

#include "rapidjson/document.h"

class Endpoint {
public:
    Endpoint(SocketPtr socket, const std::string &appName, moba::Version version, const MessageGroups &groups);

    Endpoint(SocketPtr socket, const std::string &appName, moba::Version version);

    virtual ~Endpoint() noexcept = default;
    
    long connect();

    long getAppId() const;

    auto recieveMsg(time_t timeoutSec = 0) -> RawMessage;

    auto waitForNewMsg() -> RawMessage;
    std::string waitForNewMsgAsString();

    template<typename T>
    void sendMsg(const T &msg) {
        sendMsg(T::GROUP_ID, T::MESSAGE_ID, msg.getJsonDocument());
    }

    void sendMsg(std::uint32_t grpId, std::uint32_t msgId, const rapidjson::Document &data);

    void sendMsg(std::uint32_t grpId, std::uint32_t msgId, const std::string &data) {
        sendMsg(grpId, msgId, data.c_str(), data.length());
    }

    void sendMsg(std::uint32_t grpId, std::uint32_t msgId, const char *buffer, std::size_t bufferSize);

protected:
    SocketPtr socket;

    std::mutex m;

    long appId{0};

    std::string appName;
    moba::Version version;
    MessageGroups groups;

    static constexpr int MSG_HANDLER_TIME_OUT_SEC = 2;
    static constexpr int MSG_HANDLER_TIME_OUT_USEC = 0;

    auto registerApp() -> long;
};

using EndpointPtr = std::shared_ptr<Endpoint>;
