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

    LayoutGetLayoutsRes(const nlohmann::json &d) {
        for(auto &iter: d) {
            layouts.push_back(iter);
        }
    }

    std::vector<TrackLayoutData> layouts;
};

struct LayoutDeleteLayout: public LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_DELETE_LAYOUT;

    LayoutDeleteLayout(int layoutId): layoutId{layoutId} {
    }

    LayoutDeleteLayout(const nlohmann::json &d) {
        layoutId = d.get<int>();
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        nlohmann::json d;
        d = layoutId;
        return d;
    }

    int layoutId;
};

struct LayoutCreateLayout: public LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_CREATE_LAYOUT;

    LayoutCreateLayout(const TrackLayoutData &tracklayout): tracklayout{tracklayout} {
    }

    LayoutCreateLayout(const std::string &name, const std::string &description, bool active):
    tracklayout{name, description, active} {
    }

    LayoutCreateLayout(const nlohmann::json &d): tracklayout{d} {
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        nlohmann::json d;

        d["name"] = tracklayout.name;
        d["description"] = tracklayout.description;
        d["active"] = tracklayout.active;
        return d;
    }

    TrackLayoutData tracklayout;
};

struct LayoutUpdateLayout: public LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_UPDATE_LAYOUT;

    LayoutUpdateLayout(const TrackLayoutData &tracklayout): tracklayout{tracklayout} {
    }

    LayoutUpdateLayout(const nlohmann::json &d): tracklayout{d} {
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        nlohmann::json d;

        d["id"] = tracklayout.id;
        d["name"] = tracklayout.name;
        d["description"] = tracklayout.description;
        return d;
    }

    TrackLayoutData tracklayout;
};

struct LayoutUnlockLayout: public LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_UNLOCK_LAYOUT;

    LayoutUnlockLayout(int layoutId): layoutId{layoutId} {
    }

    LayoutUnlockLayout(const nlohmann::json &d) {
        layoutId = d.get<int>();
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        nlohmann::json d;
        d = layoutId;
        return d;
    }

    int layoutId;
};

struct LayoutLockLayout: public LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_LOCK_LAYOUT;

    LayoutLockLayout(int layoutId): layoutId{layoutId} {
    }

    LayoutLockLayout(const nlohmann::json &d) {
        layoutId = d.get<int>();
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        nlohmann::json d;
        d = layoutId;
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

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        nlohmann::json d;
        if(layoutId) {
            d = *layoutId;
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

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        nlohmann::json d;
        if(layoutId) {
            d = *layoutId;
        }
        return d;
    }

    std::optional<int> layoutId;
};

struct LayoutGetLayoutRes: public LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_GET_LAYOUT_RES;

    LayoutGetLayoutRes(const nlohmann::json &d): specificLayoutData{d} {
    }

    SpecificLayoutData specificLayoutData;
};

struct LayoutSaveLayout: public LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_SAVE_LAYOUT;

    LayoutSaveLayout() {
        specificLayoutData.id = 4;
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        nlohmann::json d;
        auto a = nlohmann::json::array();

        for(auto &iter : *specificLayoutData.symbols) {
            nlohmann::json s;
            if(iter.second.id == 0) {
                s["id"] = nullptr;
            } else {
                s["id"] = iter.second.id;
            }
            s["xPos"] = iter.first.first;
            s["yPos"] = iter.first.second;
            s["symbol"] = iter.second.symbol;

            a.push_back(s);
        }

        d["id"] = specificLayoutData.id;
        d["symbols"] = a;

        return d;
    }

    SpecificLayoutData specificLayoutData;
};

struct LayoutDefaultLayoutChanged: public LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_DEFAULT_LAYOUT_CHANGED;

    LayoutDefaultLayoutChanged(const nlohmann::json &d) {
        layoutId = d.get<int>();
    }

    int layoutId;
};