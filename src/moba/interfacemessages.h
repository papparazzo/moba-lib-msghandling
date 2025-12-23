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

struct InterfaceMessage: Message {
    enum MessageName {
        CONNECTED           = 1,
        CONNECTION_LOST     = 2,
        SET_ACTION_LIST     = 3,
        REPLACE_ACTION_LIST = 4,
        DELETE_ACTION_LIST  = 5,
        ROUTE_SWITCHED      = 6,
        ROUTE_RELEASED      = 7,
        BLOCK_RELEASED      = 8,
        PUSH_TRAIN          = 9
    };

    static constexpr std::uint32_t GROUP_ID = INTERFACE;
};

struct InterfaceConnected final: InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONNECTED;

    explicit InterfaceConnected(const bool onInitialize): onInitialize {onInitialize} {
    }

    [[nodiscard]]
    nlohmann::json getJsonDocument() const override {
        return onInitialize;
    }

    bool onInitialize;
};

struct InterfaceConnectionLost final: InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONNECTION_LOST;
};

struct InterfacePushTrain final: InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = PUSH_TRAIN;

    InterfacePushTrain(const unsigned long trainId, const unsigned long toBlockId): trainId{trainId}, blockId {toBlockId} {}

    [[nodiscard]]
    nlohmann::json getJsonDocument() const override {
        nlohmann::json d;

        d["trainId"] = trainId;
        d["blockId"] = blockId;

        return d;
    }

    unsigned long trainId;
    unsigned long blockId;
};

struct InterfaceRouteSwitched final: InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = ROUTE_SWITCHED;

    explicit InterfaceRouteSwitched(const unsigned long id): id{id} {
    }

    [[nodiscard]]
    nlohmann::json getJsonDocument() const override {
        return id;
    }

    unsigned long id;
};

struct InterfaceRouteReleased final: InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = ROUTE_RELEASED;

    explicit InterfaceRouteReleased(const unsigned long id): id{id} {
    }

    [[nodiscard]]
    nlohmann::json getJsonDocument() const override {
        return id;
    }

    unsigned long id;
};

struct InterfaceBlockReleased final: InterfaceMessage {
    static constexpr std::uint32_t MESSAGE_ID = BLOCK_RELEASED;

    explicit InterfaceBlockReleased(const unsigned long id): id{id} {
    }

    [[nodiscard]]
    nlohmann::json getJsonDocument() const override {
        return id;
    }

    unsigned long id;
};
