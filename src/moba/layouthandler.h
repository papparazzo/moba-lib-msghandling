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

#include <string>
#include <vector>
#include <memory>

#include "message.h"
#include "shared.h"

struct LayoutMessage : public Message {
    enum MessageName {
        LAYOUT_GET_LAYOUTS_REQ          = 1,
        LAYOUT_GET_LAYOUTS_RES          = 2,
        LAYOUT_DELETE_LAYOUT            = 3,
        LAYOUT_LAYOUT_DELETED           = 4,
        LAYOUT_CREATE_LAYOUT            = 5,
        LAYOUT_LAYOUT_CREATED           = 6,
        LAYOUT_UPDATE_LAYOUT            = 7,
        LAYOUT_LAYOUT_UPDATED           = 8,
        LAYOUT_UNLOCK_LAYOUT            = 9,
        LAYOUT_LAYOUT_UNLOCKED          = 10,
        LAYOUT_LOCK_LAYOUT              = 11,
        LAYOUT_LAYOUT_LOCKED            = 12,
        LAYOUT_GET_LAYOUT_REQ           = 13,
        LAYOUT_GET_LAYOUT_READ_ONLY_REQ = 14,
        LAYOUT_GET_LAYOUT_RES           = 15,
        LAYOUT_SAVE_LAYOUT              = 16,
        LAYOUT_LAYOUT_CHANGED           = 17,
    };

    const static std::uint32_t GROUP_ID = LAYOUT;
};

struct LayoutGetLayoutsReq : public LayoutMessage {
    const static std::uint32_t MESSAGE_ID = LAYOUT_GET_LAYOUTS_REQ;
};

struct LayoutGetLayoutsRes : public LayoutMessage {
    const static std::uint32_t MESSAGE_ID = LAYOUT_GET_LAYOUTS_RES;

    LayoutGetLayoutsRes(const rapidjson::Document &d) {
        for(auto &iter : d.GetArray()) {
            layouts.push_back(iter);
        }
    }

    std::vector<TrackLayoutData> layouts;
};

struct LayoutDeleteLayout : public LayoutMessage {
    const static std::uint32_t MESSAGE_ID = LAYOUT_DELETE_LAYOUT;

    LayoutDeleteLayout(int layoutId) : layoutId{layoutId} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetInt(layoutId);
        return d;
    }

    int layoutId;
};

struct LayoutLayoutDeleted : public LayoutMessage {
    const static std::uint32_t MESSAGE_ID = LAYOUT_LAYOUT_DELETED;

    LayoutLayoutDeleted(const rapidjson::Document &d) {
        layoutId = d.GetInt();
    }

    int layoutId;
};

struct LayoutCreateLayout : public LayoutMessage {
    const static std::uint32_t MESSAGE_ID = LAYOUT_CREATE_LAYOUT;

    LayoutCreateLayout(const TrackLayoutData &tracklayout) : tracklayout{tracklayout} {
    }

    LayoutCreateLayout(const std::string &name, const std::string &description, bool active) : tracklayout{name, description, active} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetObject();

        d.AddMember("name", rapidjson::Value(tracklayout.name.c_str(), tracklayout.name.length(), d.GetAllocator()), d.GetAllocator());
        d.AddMember("description", rapidjson::Value(tracklayout.description.c_str(), tracklayout.description.length(), d.GetAllocator()), d.GetAllocator());
        d.AddMember("active", tracklayout.active, d.GetAllocator());
        return d;
    }

    TrackLayoutData tracklayout;
};

struct LayoutLayoutCreated : public LayoutMessage {
    const static std::uint32_t MESSAGE_ID = LAYOUT_LAYOUT_CREATED;

    LayoutLayoutCreated(const rapidjson::Document &d) : tracklayout{d} {
    }

    TrackLayoutData tracklayout;
};
/*
struct LayoutUpdateLayout : public LayoutMessage {
    const static std::uint32_t MESSAGE_ID = LAYOUT_UPDATE_LAYOUT;

    LayoutUpdateLayout(const TrackLayoutData &tracklayout) : tracklayout{tracklayout} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetObject();

        d.AddMember();

        moba::JsonObjectPtr obj(new moba::JsonObject());
        (*obj)["id"         ] = moba::toJsonNumberPtr(tracklayout.id);
        (*obj)["name"       ] = moba::toJsonStringPtr(tracklayout.name);
        (*obj)["description"] = moba::toJsonStringPtr(tracklayout.description);
        return obj;
    }

    TrackLayoutData tracklayout;
};

struct LayoutLayoutUpdated : public RecieveMessage {
    LayoutLayoutUpdated(moba::JsonItemPtr data) : tracklayout{std::dynamic_pointer_cast<moba::JsonObject>(data)} {
    }

    static std::string getMessageName() {
        return "LAYOUT_UPDATED";
    }

    TrackLayoutData tracklayout;
};

struct LayoutUnlockLayout : public DispatchMessageType<LayoutUnlockLayout> {
    LayoutUnlockLayout(int layoutId) : layoutId{layoutId} {
    }

    static std::string getMessageName() {
        return "UNLOCK_LAYOUT";
    }

    virtual moba::JsonItemPtr getData() const override {
        return moba::toJsonNumberPtr(layoutId);
    }

    int layoutId;
};

struct LayoutLayoutUnlocked : public RecieveMessage {
    LayoutLayoutUnlocked(moba::JsonItemPtr data) {
        layoutId = moba::castToInt(data);
    }

    static std::string getMessageName() {
        return "LAYOUT_UNLOCKED";
    }

    int layoutId;
};

struct LayoutLockLayout : public DispatchMessageType<LayoutLockLayout> {
    LayoutLockLayout(int layoutId) : layoutId{layoutId} {
    }

    static std::string getMessageName() {
        return "LOCK_LAYOUT";
    }

    virtual moba::JsonItemPtr getData() const override {
        return moba::toJsonNumberPtr(layoutId);
    }

    int layoutId;
};

struct LayoutLayoutLocked : public RecieveMessage {
    LayoutLayoutLocked(moba::JsonItemPtr data) {
        layoutId = moba::castToInt(data);
    }

    static std::string getMessageName() {
        return "LAYOUT_LOCKED";
    }

    int layoutId;
};
*/
struct LayoutGetLayoutReq : public LayoutMessage {
    const static std::uint32_t MESSAGE_ID = LAYOUT_GET_LAYOUT_REQ;

    LayoutGetLayoutReq(int layoutId) : layoutId{layoutId} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetInt(layoutId);
        return d;
    }

    int layoutId;
};

struct LayoutGetLayoutReadOnlyReq : public LayoutMessage {
    const static std::uint32_t MESSAGE_ID = LAYOUT_GET_LAYOUT_READ_ONLY_REQ;

    LayoutGetLayoutReadOnlyReq(int layoutId) : layoutId{layoutId} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetInt(layoutId);
        return d;
    }

    int layoutId;
};


/*
struct LayoutGetLayoutRes : public RecieveMessage {
    LayoutGetLayoutRes(moba::JsonItemPtr data) : data{data} {
    }

    static std::string getMessageName() {
        return "GET_LAYOUT_RES";
    }

    moba::JsonItemPtr data;
};

struct LayoutSaveLayout : public DispatchMessageType<LayoutSaveLayout> {
    LayoutSaveLayout(moba::JsonItemPtr data) : data{data} {
    }

    static std::string getMessageName() {
        return "SAVE_LAYOUT";
    }

    virtual moba::JsonItemPtr getData() const override {
        return data;
    }
    moba::JsonItemPtr data;
};
*/