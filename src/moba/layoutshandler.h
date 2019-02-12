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

#include <moba/jsonabstractitem.h>
#include "shared.h"

struct LayoutsGetLayoutsReq : public DispatchMessageType<LayoutsGetLayoutsReq> {
    static std::string getMessageName() {
        return "LAYOUTS_GET_LAYOUTS_REQ";
    }
};

struct LayoutsGetLayoutsRes : public RecieveMessage {
    LayoutsGetLayoutsRes(moba::JsonItemPtr data) {
        auto a = boost::dynamic_pointer_cast<moba::JsonArray>(data);
        for(auto iter : *a) {
            layouts.push_back(TrackLayoutData{boost::dynamic_pointer_cast<moba::JsonObject>(iter)});
        }
    }

    static std::string getMessageName() {
        return "LAYOUTS_GET_LAYOUTS_RES";
    }

    std::vector<TrackLayoutData> layouts;
};

struct LayoutsDeleteLayout : public DispatchMessageType<LayoutsDeleteLayout> {
    LayoutsDeleteLayout(int layoutId) : layoutId{layoutId} {
    }

    static std::string getMessageName() {
        return "LAYOUTS_DELETE_LAYOUT";
    }

    virtual moba::JsonItemPtr getData() const override {
        return moba::toJsonNumberPtr(layoutId);
    }

    int layoutId;
};

struct LayoutsLayoutDeleted : public RecieveMessage {
    LayoutsLayoutDeleted(moba::JsonItemPtr data) {
        layoutId = moba::castToInt(data);
    }

    static std::string getMessageName() {
        return "LAYOUTS_LAYOUT_DELETED";
    }

    int layoutId;
};

struct LayoutsCreateLayoutReq : public DispatchMessageType<LayoutsCreateLayoutReq> {
    LayoutsCreateLayoutReq(const TrackLayoutData &tracklayout) : tracklayout{tracklayout} {
    }

    static std::string getMessageName() {
        return "LAYOUTS_CREATE_LAYOUT_REQ";
    }

    virtual moba::JsonItemPtr getData() const override {
        moba::JsonObjectPtr obj(new moba::JsonObject());
        (*obj)["name"       ] = moba::toJsonStringPtr(tracklayout.name);
        (*obj)["description"] = moba::toJsonStringPtr(tracklayout.description);
        return obj;
    }

    TrackLayoutData tracklayout;
};

struct LayoutsCreateLayoutRes : public RecieveMessage {
    LayoutsCreateLayoutRes(moba::JsonItemPtr data) {
        layoutId = moba::castToInt(data);
    }

    static std::string getMessageName() {
        return "LAYOUTS_CREATE_LAYOUT_RES";
    }

    int layoutId;
};

struct LayoutsLayoutCreated : public RecieveMessage {
    LayoutsLayoutCreated(moba::JsonItemPtr data) : tracklayout{boost::dynamic_pointer_cast<moba::JsonObject>(data)} {
    }

    static std::string getMessageName() {
        return "LAYOUTS_LAYOUT_CREATED";
    }

    TrackLayoutData tracklayout;
};

struct LayoutsUpdateLayout : public DispatchMessageType<LayoutsUpdateLayout> {
    LayoutsUpdateLayout(const TrackLayoutData &tracklayout) : tracklayout{tracklayout} {
    }

    static std::string getMessageName() {
        return "LAYOUTS_UPDATE_LAYOUT";
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

struct LayoutsLayoutUpdated : public RecieveMessage {
    LayoutsLayoutUpdated(moba::JsonItemPtr data) : tracklayout{boost::dynamic_pointer_cast<moba::JsonObject>(data)} {
    }

    static std::string getMessageName() {
        return "LAYOUTS_LAYOUT_UPDATED";
    }

    TrackLayoutData tracklayout;
};

struct LayoutsUnlockLayout : public DispatchMessageType<LayoutsUnlockLayout> {
    LayoutsUnlockLayout(int layoutId) : layoutId{layoutId} {
    }

    static std::string getMessageName() {
        return "LAYOUTS_UNLOCK_LAYOUT";
    }

    virtual moba::JsonItemPtr getData() const override {
        return moba::toJsonNumberPtr(layoutId);
    }

    int layoutId;
};

struct LayoutsLayoutUnlocked : public RecieveMessage {
    LayoutsLayoutUnlocked(moba::JsonItemPtr data) {
        layoutId = moba::castToInt(data);
    }

    static std::string getMessageName() {
        return "LAYOUTS_LAYOUT_UNLOCKED";
    }

    int layoutId;
};
