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

struct ControlMessage : public Message {
    enum MessageName {
        CONTROL_GET_CONTACT_LIST_REQ      = 1,
        CONTROL_GET_CONTACT_LIST_RES      = 2,
        CONTROL_GET_SWITCH_STAND_LIST_REQ = 3,
        CONTROL_GET_SWITCH_STAND_LIST_RES = 4,
        CONTROL_GET_TRAIN_LIST_REQ        = 5,
        CONTROL_GET_TRAIN_LIST_RES        = 6,
        CONTROL_UNLOCK_BLOCK              = 7,
        CONTROL_BLOCK_UNLOCKED            = 8,
        CONTROL_LOCK_BLOCK                = 9,
        CONTROL_BLOCK_LOCKED              = 10,
    };

    static constexpr std::uint32_t GROUP_ID = CONTROL;
};

struct ControlGetContactListReq : public ControlMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_GET_CONTACT_LIST_REQ;

    ControlGetContactListReq(int layoutId = 0) : layoutId{layoutId} {
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

struct ControlGetSwitchStateListReq : public ControlMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_GET_SWITCH_STAND_LIST_REQ;

    ControlGetSwitchStateListReq(int layoutId = 0) : layoutId{layoutId} {
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

struct ControlGetTrainListReq : public ControlMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_GET_TRAIN_LIST_REQ;

    ControlGetTrainListReq(int layoutId = 0) : layoutId{layoutId} {
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

struct ControlGetTrainListRes : public ControlMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_GET_TRAIN_LIST_RES;

    ControlGetTrainListRes(const rapidjson::Document &d) {
        trainList = std::make_shared<std::map<int, std::shared_ptr<Train>>>();

        for(auto &iter : d.GetArray()) {
            (*trainList)[iter["id"].GetInt()] = std::make_shared<Train>(iter);
        }
    }

    using TrainListPtr = std::shared_ptr<std::map<int, std::shared_ptr<Train>>>;

    TrainListPtr trainList;
};

struct ControlUnlockBlock : public ControlMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_UNLOCK_BLOCK;

    ControlUnlockBlock(int id = 0) : id{id} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetInt(id);
        return d;
    }

    int id;
};

struct ControlBlockUnlocked : public ControlMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_BLOCK_UNLOCKED;

    ControlBlockUnlocked(const rapidjson::Document &d) {
        id = d.GetInt();
    }

    int id;
};

struct ControlLockBlock : public ControlMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_LOCK_BLOCK;

    ControlLockBlock(int id = 0) : id{id} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetInt(id);
        return d;
    }

    int id;
};

struct ControlBlockLocked : public ControlMessage {
    static constexpr std::uint32_t MESSAGE_ID = CONTROL_BLOCK_LOCKED;

    ControlBlockLocked(int id = 0) : id{id} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetInt(id);
        return d;
    }

    int id;
};


