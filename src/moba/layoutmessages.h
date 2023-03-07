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
#include <optional>

#include "message.h"
#include "shared.h"

struct LayoutMessage: public Message {
    enum MessageName {
        LAYOUT_GET_LAYOUTS_REQ          = 1,
        LAYOUT_GET_LAYOUTS_RES          = 2,
        LAYOUT_DELETE_LAYOUT            = 3,
        LAYOUT_CREATE_LAYOUT            = 4,
        LAYOUT_UPDATE_LAYOUT            = 5,
        LAYOUT_UNLOCK_LAYOUT            = 6,
        LAYOUT_LOCK_LAYOUT              = 7,
        LAYOUT_GET_LAYOUT_REQ           = 8,
        LAYOUT_GET_LAYOUT_READ_ONLY_REQ = 9,
        LAYOUT_GET_LAYOUT_RES           = 10,
        LAYOUT_SAVE_LAYOUT              = 11,
        LAYOUT_LAYOUT_CHANGED           = 12,
        LAYOUT_DEFAULT_LAYOUT_CHANGED   = 13
    };

    static constexpr std::uint32_t GROUP_ID = LAYOUT;
};

struct LayoutGetLayoutsReq: public LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_GET_LAYOUTS_REQ;
};

struct LayoutGetLayoutsRes: public LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_GET_LAYOUTS_RES;

    LayoutGetLayoutsRes(const rapidjson::Document &d) {
        for(auto &iter : d.GetArray()) {
            layouts.push_back(iter);
        }
    }

    std::vector<TrackLayoutData> layouts;
};

struct LayoutDeleteLayout: public LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_DELETE_LAYOUT;

    LayoutDeleteLayout(int layoutId): layoutId{layoutId} {
    }

    LayoutDeleteLayout(const rapidjson::Document &d) {
        layoutId = d.GetInt();
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetInt(layoutId);
        return d;
    }

    int layoutId;
};

struct LayoutCreateLayout: public LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_CREATE_LAYOUT;

    LayoutCreateLayout(const TrackLayoutData &tracklayout): tracklayout{tracklayout} {
    }

    LayoutCreateLayout(const std::string &name, const std::string &description, bool active) : tracklayout{name, description, active} {
    }

    LayoutCreateLayout(const rapidjson::Document &d): tracklayout{d} {
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

struct LayoutUpdateLayout: public LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_UPDATE_LAYOUT;

    LayoutUpdateLayout(const TrackLayoutData &tracklayout): tracklayout{tracklayout} {
    }

    LayoutUpdateLayout(const rapidjson::Document &d): tracklayout{d} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetObject();

        d.AddMember("id", tracklayout.id, d.GetAllocator());
        d.AddMember("name", rapidjson::Value(tracklayout.name.c_str(), tracklayout.name.length(), d.GetAllocator()), d.GetAllocator());
        d.AddMember("description", rapidjson::Value(tracklayout.description.c_str(), tracklayout.description.length(), d.GetAllocator()), d.GetAllocator());
        return d;
    }

    TrackLayoutData tracklayout;
};

struct LayoutUnlockLayout: public LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_UNLOCK_LAYOUT;

    LayoutUnlockLayout(int layoutId): layoutId{layoutId} {
    }

    LayoutUnlockLayout(const rapidjson::Document &d) {
        layoutId = d.GetInt();
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetInt(layoutId);
        return d;
    }

    int layoutId;
};

struct LayoutLockLayout: public LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_LOCK_LAYOUT;

    LayoutLockLayout(int layoutId): layoutId{layoutId} {
    }

    LayoutLockLayout(const rapidjson::Document &d) {
        layoutId = d.GetInt();
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetInt(layoutId);
        return d;
    }

    int layoutId;
};

struct LayoutGetLayoutReq: public LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_GET_LAYOUT_REQ;

    LayoutGetLayoutReq(): layoutId{} {
    }

    LayoutGetLayoutReq(int layoutId): layoutId{layoutId} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        if(layoutId) {
            d.SetInt(*layoutId);
        }
        return d;
    }

    std::optional<int> layoutId;
};

struct LayoutGetLayoutReadOnlyReq : public LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_GET_LAYOUT_READ_ONLY_REQ;

    LayoutGetLayoutReadOnlyReq(): layoutId{} {
    }
    LayoutGetLayoutReadOnlyReq(int layoutId): layoutId{layoutId} {
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        if(layoutId) {
            d.SetInt(*layoutId);
        }
        return d;
    }

    std::optional<int> layoutId;
};

struct LayoutGetLayoutRes: public LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_GET_LAYOUT_RES;

    LayoutGetLayoutRes(const rapidjson::Document &d): specificLayoutData{d} {
    }

    SpecificLayoutData specificLayoutData;
};

struct LayoutSaveLayout: public LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_SAVE_LAYOUT;

    LayoutSaveLayout() {
        specificLayoutData.id = 4;
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        rapidjson::Value a(rapidjson::kArrayType);

        for(auto &iter : *specificLayoutData.symbols) {
            rapidjson::Value s(rapidjson::kObjectType);
            if(iter.second.id == 0) {
                s.AddMember("id", rapidjson::kNullType, d.GetAllocator());
            } else {
                s.AddMember("id", iter.second.id, d.GetAllocator());
            }
            s.AddMember("xPos", iter.first.first, d.GetAllocator());
            s.AddMember("yPos", iter.first.second, d.GetAllocator());
            s.AddMember("symbol", iter.second.symbol, d.GetAllocator());

            a.PushBack(s, d.GetAllocator());
        }

        d.SetObject();
        d.AddMember("id", specificLayoutData.id, d.GetAllocator());
        d.AddMember("symbols", a, d.GetAllocator());

        return d;
    }

    SpecificLayoutData specificLayoutData;
};

struct LayoutDefaultLayoutChanged: public LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_DEFAULT_LAYOUT_CHANGED;

    LayoutDefaultLayoutChanged(const rapidjson::Document &d) {
        layoutId = d.GetInt();
    }

    int layoutId;
};