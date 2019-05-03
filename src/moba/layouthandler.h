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

#include "basemessage.h"
#include <moba/jsonabstractitem.h>
#include "shared.h"

struct LayoutGetLayoutsReq : public DispatchMessageType<LayoutGetLayoutsReq> {
    static std::string getMessageName() {
        return "LAYOUT_GET_LAYOUTS_REQ";
    }
};

struct LayoutGetLayoutsRes : public RecieveMessage {
    LayoutGetLayoutsRes(moba::JsonItemPtr data) {
        auto a = std::dynamic_pointer_cast<moba::JsonArray>(data);
        for(auto iter : *a) {
            layouts.push_back(TrackLayoutData{std::dynamic_pointer_cast<moba::JsonObject>(iter)});
        }
    }

    static std::string getMessageName() {
        return "LAYOUT_GET_LAYOUTS_RES";
    }

    std::vector<TrackLayoutData> layouts;
};

struct LayoutDeleteLayout : public DispatchMessageType<LayoutDeleteLayout> {
    LayoutDeleteLayout(int layoutId) : layoutId{layoutId} {
    }

    static std::string getMessageName() {
        return "LAYOUT_DELETE_LAYOUT";
    }

    virtual moba::JsonItemPtr getData() const override {
        return moba::toJsonNumberPtr(layoutId);
    }

    int layoutId;
};

struct LayoutLayoutDeleted : public RecieveMessage {
    LayoutLayoutDeleted(moba::JsonItemPtr data) {
        layoutId = moba::castToInt(data);
    }

    static std::string getMessageName() {
        return "LAYOUT_LAYOUT_DELETED";
    }

    int layoutId;
};

struct LayoutCreateLayoutReq : public DispatchMessageType<LayoutCreateLayoutReq> {
    LayoutCreateLayoutReq(const TrackLayoutData &tracklayout) : tracklayout{tracklayout} {
    }

    static std::string getMessageName() {
        return "LAYOUT_CREATE_LAYOUT_REQ";
    }

    virtual moba::JsonItemPtr getData() const override {
        moba::JsonObjectPtr obj(new moba::JsonObject());
        (*obj)["name"       ] = moba::toJsonStringPtr(tracklayout.name);
        (*obj)["description"] = moba::toJsonStringPtr(tracklayout.description);
        return obj;
    }

    TrackLayoutData tracklayout;
};

struct LayoutCreateLayoutRes : public RecieveMessage {
    LayoutCreateLayoutRes(moba::JsonItemPtr data) {
        layoutId = moba::castToInt(data);
    }

    static std::string getMessageName() {
        return "LAYOUT_CREATE_LAYOUT_RES";
    }

    int layoutId;
};

struct LayoutLayoutCreated : public RecieveMessage {
    LayoutLayoutCreated(moba::JsonItemPtr data) : tracklayout{std::dynamic_pointer_cast<moba::JsonObject>(data)} {
    }

    static std::string getMessageName() {
        return "LAYOUT_LAYOUT_CREATED";
    }

    TrackLayoutData tracklayout;
};

struct LayoutUpdateLayout : public DispatchMessageType<LayoutUpdateLayout> {
    LayoutUpdateLayout(const TrackLayoutData &tracklayout) : tracklayout{tracklayout} {
    }

    static std::string getMessageName() {
        return "LAYOUT_UPDATE_LAYOUT";
    }

    virtual moba::JsonItemPtr getData() const override {
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
        return "LAYOUT_LAYOUT_UPDATED";
    }

    TrackLayoutData tracklayout;
};

struct LayoutUnlockLayout : public DispatchMessageType<LayoutUnlockLayout> {
    LayoutUnlockLayout(int layoutId) : layoutId{layoutId} {
    }

    static std::string getMessageName() {
        return "LAYOUT_UNLOCK_LAYOUT";
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
        return "LAYOUT_LAYOUT_UNLOCKED";
    }

    int layoutId;
};

struct LayoutLockLayout : public DispatchMessageType<LayoutLockLayout> {
    LayoutLockLayout(int layoutId) : layoutId{layoutId} {
    }

    static std::string getMessageName() {
        return "LAYOUT_LOCK_LAYOUT";
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
        return "LAYOUT_LAYOUT_LOCKED";
    }

    int layoutId;
};

struct LayoutGetLayoutReq : public DispatchMessageType<LayoutGetLayoutReq> {
    LayoutGetLayoutReq(int layoutId) : layoutId{layoutId} {
    }

    static std::string getMessageName() {
        return "LAYOUT_GET_LAYOUT_REQ";
    }

    virtual moba::JsonItemPtr getData() const override {
        return moba::toJsonNumberPtr(layoutId);
    }

    int layoutId;
};

struct LayoutGetLayoutReadOnlyReq : public DispatchMessageType<LayoutGetLayoutReadOnlyReq> {
    LayoutGetLayoutReadOnlyReq(int layoutId) : layoutId{layoutId} {
    }

    static std::string getMessageName() {
        return "LAYOUT_GET_LAYOUT_READ_ONLY_REQ";
    }

    virtual moba::JsonItemPtr getData() const override {
        return moba::toJsonNumberPtr(layoutId);
    }

    int layoutId;
};

struct LayoutGetLayoutRes : public RecieveMessage {
    LayoutGetLayoutRes(moba::JsonItemPtr data) : layoutData{std::dynamic_pointer_cast<moba::JsonObject>(data)} {
    }

    static std::string getMessageName() {
        return "LAYOUT_GET_LAYOUT_RES";
    }

    SpecificLayoutData layoutData;
};
