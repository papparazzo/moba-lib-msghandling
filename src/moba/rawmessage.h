/*
 *  Project:    moba-systemmanager
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

#include "nlohmann/json.hpp"

struct RawMessage final {

    // Avoid using {} in data(std::move(data). Further information can be found here:
    // https://json.nlohmann.me/home/faq/#brace-initialization-yields-arrays
    RawMessage(
        const std::uint32_t grpId,
        const std::uint32_t msgId,
        nlohmann::json data
    ) : groupId{grpId}, messageId{msgId}, data(std::move(data)) {
    }

    explicit RawMessage(
        const std::uint32_t grpId = 0,
        const std::uint32_t msgId = 0
    ) : groupId{grpId}, messageId{msgId} {
    }

    ~RawMessage() noexcept = default;

    bool operator!() const {
        if(groupId && messageId) {
            return false;
        }
        return true;
    }

    std::uint32_t  groupId;
    std::uint32_t  messageId;
    nlohmann::json data;
};
