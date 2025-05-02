/*
 *  Project:    moba-blocksystem
 *
 *  Copyright (C) 2020 Stefan Paproth <pappi-@gmx.de>
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
#include "train.h"

#include <moba-common/drivingdirection.h>
#include <map>

struct ControlMessage: Message {
    enum MessageName {
        CONTROL_GET_BLOCK_LIST_REQ        = 1,
        CONTROL_GET_BLOCK_LIST_RES        = 2,
        CONTROL_SAVE_BLOCK_LIST           = 3,
        CONTROL_GET_SWITCH_STAND_LIST_REQ = 4,
        CONTROL_GET_SWITCH_STAND_LIST_RES = 5,
        CONTROL_SAVE_SWITCH_STAND_LIST    = 6,
        CONTROL_GET_TRAIN_LIST_REQ        = 7,
        CONTROL_GET_TRAIN_LIST_RES        = 8,
        CONTROL_SAVE_TRAIN_LIST           = 9,
        CONTROL_LOCK_BLOCK                = 10,
        CONTROL_LOCK_BLOCK_WAITING        = 11,
        CONTROL_BLOCK_LOCKED              = 12,
        CONTROL_BLOCK_LOCKING_FAILED      = 13,
        CONTROL_UNLOCK_BLOCK              = 14,
        CONTROL_PUSH_TRAIN                = 15
    };

    static constexpr std::uint32_t GROUP_ID = CONTROL;
};

struct ControlGetBlockListReq final : ControlMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_GET_BLOCK_LIST_REQ;

    explicit ControlGetBlockListReq(const int layoutId = 0): layoutId{layoutId} {
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        if(layoutId == 0) {
            return nlohmann::json{};
        }
        return layoutId;
    }

    int layoutId;
};

struct ControlGetSwitchStateListReq final : ControlMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_GET_SWITCH_STAND_LIST_REQ;

    explicit ControlGetSwitchStateListReq(const int layoutId = 0): layoutId{layoutId} {
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        if(layoutId == 0) {
            return nlohmann::json{};
        }
        return layoutId;
    }

    int layoutId;
};

struct ControlGetTrainListReq final : ControlMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_GET_TRAIN_LIST_REQ;

    explicit ControlGetTrainListReq(const int layoutId = 0): layoutId{layoutId} {
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        if(layoutId == 0) {
            return nlohmann::json{};
        }
        return layoutId;
    }

    int layoutId;
};

struct ControlGetTrainListRes final : ControlMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_GET_TRAIN_LIST_RES;

    explicit ControlGetTrainListRes(const nlohmann::json &d) {
        trainList = std::make_shared<std::map<int, std::shared_ptr<Train>>>();

        for(auto &iter: d) {
            (*trainList)[iter["id"].get<int>()] = std::make_shared<Train>(iter);
        }
    }

    TrainListPtr trainList;
};

struct ControlLock: ControlMessage {
    ControlLock(const std::uint32_t b1, const std::uint32_t b2) {
        blockVec.push_back(b1);
        blockVec.push_back(b2);
    }

    explicit ControlLock(const nlohmann::json &d) {
        for(auto &iter: d){
            blockVec.push_back(iter.get<unsigned int>());
        }
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        return blockVec;
    }

    std::vector<std::uint32_t> blockVec;
};

struct ControlLockBlock final : ControlLock {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_LOCK_BLOCK;
    using ControlLock::ControlLock;
};

struct ControlLockBlockWaiting final : ControlLock {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_LOCK_BLOCK_WAITING;
    using ControlLock::ControlLock;
};

struct ControlUnlockBlock final : ControlLock {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_UNLOCK_BLOCK;
    using ControlLock::ControlLock;
};

struct ControlBlockLocked final : ControlLock {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_BLOCK_LOCKED;
    using ControlLock::ControlLock;
};

struct ControlBlockLockingFailed final : ControlLock {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_BLOCK_LOCKING_FAILED;
    using ControlLock::ControlLock;
};

struct ControlPushTrain final : ControlMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_PUSH_TRAIN;

    ControlPushTrain(
        const std::uint32_t trainId,
        const std::uint32_t fromBlock,
        const std::uint32_t toBlock,
        const moba::DrivingDirection direction
    ): trainId{trainId}, fromBlock{fromBlock}, toBlock{toBlock}, direction{direction} {
    }

    explicit ControlPushTrain(const nlohmann::json &d) {
        trainId = d["trainId"].get<unsigned int>();
        fromBlock = d["fromBlock"].get<unsigned int>();
        toBlock = d["toBlock"].get<unsigned int>();
        direction.setDrivingDirection(d["direction"].get<std::string>());
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        nlohmann::json d;

        d["trainId"] = trainId;
        d["direction"] = direction.getDrivingDirection();
        d["fromBlock"] = fromBlock;
        d["toBlock"] = toBlock;

        return d;
    }

    std::uint32_t trainId;
    std::uint32_t fromBlock;
    std::uint32_t toBlock;

    moba::DrivingDirection direction;
};
