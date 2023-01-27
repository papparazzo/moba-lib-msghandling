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
 *  along with this program. If not, see <http://www.gnu.org/licenses/agpl.txt>.
 *
 */

#pragma once

#include "message.h"
#include "shared.h"
#include "train.h"
#include <map>

struct ControlMessage: public Message {
    enum MessageName {
        CONTROL_GET_CONTACT_LIST_REQ      = 1,
        CONTROL_GET_CONTACT_LIST_RES      = 2,
        CONTROL_GET_SWITCH_STAND_LIST_REQ = 3,
        CONTROL_GET_SWITCH_STAND_LIST_RES = 4,
        CONTROL_GET_TRAIN_LIST_REQ        = 5,
        CONTROL_GET_TRAIN_LIST_RES        = 6,
        CONTROL_LOCK_BLOCK                = 7,
        CONTROL_LOCK_BLOCK_WAITING        = 8,
        CONTROL_BLOCK_LOCKED              = 9,
        CONTROL_BLOCK_LOCKING_FAILED      = 10,
        CONTROL_UNLOCK_BLOCK              = 11,
    };

    static constexpr std::uint32_t GROUP_ID = CONTROL;
};

struct ControlGetContactListReq: public ControlMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_GET_CONTACT_LIST_REQ;

    ControlGetContactListReq(int layoutId = 0): layoutId{layoutId} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        if(layoutId) {
            d.SetInt(layoutId);
        } else {
            d.SetNull();
        }
        return d;
    }

    int layoutId;
};

struct ControlGetSwitchStateListReq: public ControlMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_GET_SWITCH_STAND_LIST_REQ;

    ControlGetSwitchStateListReq(int layoutId = 0): layoutId{layoutId} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        if(layoutId) {
            d.SetInt(layoutId);
        } else {
            d.SetNull();
        }
        return d;
    }

    int layoutId;
};

struct ControlGetTrainListReq: public ControlMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_GET_TRAIN_LIST_REQ;

    ControlGetTrainListReq(int layoutId = 0): layoutId{layoutId} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        if(layoutId) {
            d.SetInt(layoutId);
        } else {
            d.SetNull();
        }
        return d;
    }

    int layoutId;
};

struct ControlGetTrainListRes: public ControlMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_GET_TRAIN_LIST_RES;

    ControlGetTrainListRes(const rapidjson::Document &d) {
        trainList = std::make_shared<std::map<int, std::shared_ptr<Train>>>();

        for(auto &iter : d.GetArray()) {
            (*trainList)[iter["blockId"].GetInt()] = std::make_shared<Train>(iter);
        }
    }

    TrainListPtr trainList;
};

struct ControlLock: public ControlMessage {
    ControlLock(std::uint32_t b1, std::uint32_t b2) {
        blockVec.push_back(b1);
        blockVec.push_back(b2);
    }

    ControlLock(const rapidjson::Document &d) {
        for(auto &iter : d.GetArray()) {
            blockVec.push_back(iter.GetUint());
        }
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;

        auto &allocator = d.GetAllocator();

        d.SetArray();
        d.Reserve(blockVec.size(), allocator);
        for(auto &iter : blockVec) {
            d.PushBack(iter, allocator);
        }
        return d;
    }

    std::vector<std::uint32_t> blockVec;
};

struct ControlLockBlock: public ControlLock {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_LOCK_BLOCK;
    using ControlLock::ControlLock;
};

struct ControlLockBlockWaiting: public ControlLock {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_LOCK_BLOCK_WAITING;
    using ControlLock::ControlLock;
};

struct ControlUnlockBlock: public ControlLock {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_UNLOCK_BLOCK;
    using ControlLock::ControlLock;
};

struct ControlBlockLocked: public ControlLock {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_BLOCK_LOCKED;
    using ControlLock::ControlLock;
};

struct ControlBlockLockingFailed: public ControlLock {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_BLOCK_LOCKING_FAILED;
    using ControlLock::ControlLock;
};

