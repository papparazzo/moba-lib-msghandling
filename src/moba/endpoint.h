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

#include <iostream>
#include <moba-common/version.h>
#include <memory>
#include <mutex>

#include "rawmessage.h"
#include "socket.h"
#include "shared.h"

#include "nlohmann/json.hpp"

class Endpoint final {
public:
    Endpoint(const SocketPtr &socket, const std::string &appName, const moba::Version &version, const MessageGroups &groups);

    Endpoint(const SocketPtr &socket, const std::string &appName, const moba::Version &version);

    ~Endpoint() noexcept = default;
    
    long connect();

    [[nodiscard]] long getAppId() const;

    auto receiveMsg(time_t timeoutSec = 0) const -> RawMessage;
    auto waitForNewMsg() const -> RawMessage;
    std::string waitForNewMsgAsString() const;

    template<typename T>
    void sendMsg(const T &msg) {
        sendMsg(T::GROUP_ID, T::MESSAGE_ID, msg.getJsonDocument());
    }

    void sendMsg(std::uint32_t grpId, std::uint32_t msgId, const nlohmann::json &data);

    void sendMsg(std::uint32_t grpId, std::uint32_t msgId, const std::string &data);

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
