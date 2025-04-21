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
#include <utility>
#include <vector>
#include <memory>
#include <optional>

#include "message.h"
#include "shared.h"

struct LayoutMessage: Message {
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

struct LayoutGetLayoutsReq final: LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_GET_LAYOUTS_REQ;
};

struct LayoutGetLayoutsRes final: LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_GET_LAYOUTS_RES;

    explicit LayoutGetLayoutsRes(const nlohmann::json &d) {
        for(auto &iter: d) {
            layouts.emplace_back(iter);
        }
    }

    std::vector<TrackLayoutData> layouts;
};

struct LayoutDeleteLayout final: LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_DELETE_LAYOUT;

    explicit LayoutDeleteLayout(const int layoutId): layoutId{layoutId} {
    }

    explicit LayoutDeleteLayout(const nlohmann::json &d) {
        layoutId = d.get<int>();
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        return layoutId;
    }

    int layoutId;
};

struct LayoutCreateLayout final: LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_CREATE_LAYOUT;

    explicit LayoutCreateLayout(TrackLayoutData trackLayout): trackLayout{std::move(trackLayout)} {
    }

    LayoutCreateLayout(const std::string &name, const std::string &description, const bool active):
            trackLayout{name, description, active} {
    }

    explicit LayoutCreateLayout(const nlohmann::json &d): trackLayout{d} {
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        nlohmann::json d;

        d["name"] = trackLayout.name;
        d["description"] = trackLayout.description;
        d["active"] = trackLayout.active;
        return d;
    }

    TrackLayoutData trackLayout;
};

struct LayoutUpdateLayout final: LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_UPDATE_LAYOUT;

    explicit LayoutUpdateLayout(TrackLayoutData trackLayout): trackLayout{std::move(trackLayout)} {
    }

    explicit LayoutUpdateLayout(const nlohmann::json &d): trackLayout{d} {
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        nlohmann::json d;

        d["id"] = trackLayout.id;
        d["name"] = trackLayout.name;
        d["description"] = trackLayout.description;
        return d;
    }

    TrackLayoutData trackLayout;
};

struct LayoutUnlockLayout final: LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_UNLOCK_LAYOUT;

    explicit LayoutUnlockLayout(const int layoutId): layoutId{layoutId} {
    }

    explicit LayoutUnlockLayout(const nlohmann::json &d) {
        layoutId = d.get<int>();
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        return layoutId;
    }

    int layoutId;
};

struct LayoutLockLayout final: LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_LOCK_LAYOUT;

    explicit LayoutLockLayout(const int layoutId): layoutId{layoutId} {
    }

    explicit LayoutLockLayout(const nlohmann::json &d) {
        layoutId = d.get<int>();
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        return layoutId;
    }

    int layoutId;
};

struct LayoutGetLayoutReq final: LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_GET_LAYOUT_REQ;

    LayoutGetLayoutReq() = default;

    explicit LayoutGetLayoutReq(int layoutId): layoutId{layoutId} {
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

struct LayoutGetLayoutReadOnlyReq final: LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_GET_LAYOUT_READ_ONLY_REQ;

    LayoutGetLayoutReadOnlyReq() = default;

    explicit LayoutGetLayoutReadOnlyReq(int layoutId): layoutId{layoutId} {
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

struct LayoutGetLayoutRes final: LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_GET_LAYOUT_RES;

    explicit LayoutGetLayoutRes(const nlohmann::json &d): specificLayoutData{d} {
    }

    SpecificLayoutData specificLayoutData;
};

struct LayoutSaveLayout final: LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_SAVE_LAYOUT;

    LayoutSaveLayout() {
        specificLayoutData.id = 4; // TODO: What's that?
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        nlohmann::json d;
        auto a = nlohmann::json::array();

        for(auto &[fst, snd] : *specificLayoutData.symbols) {
            nlohmann::json s;
            if(snd.id == 0) {
                s["id"] = nullptr;
            } else {
                s["id"] = snd.id;
            }
            s["xPos"] = fst.first;
            s["yPos"] = fst.second;
            s["symbol"] = snd.symbol;

            a.push_back(s);
        }

        d["id"] = specificLayoutData.id;
        d["symbols"] = a;

        return d;
    }

    SpecificLayoutData specificLayoutData;
};

struct LayoutDefaultLayoutChanged final: LayoutMessage {
    static constexpr std::uint32_t MESSAGE_ID = LAYOUT_DEFAULT_LAYOUT_CHANGED;

    explicit LayoutDefaultLayoutChanged(const nlohmann::json &d) {
        layoutId = d.get<int>();
    }

    int layoutId;
};