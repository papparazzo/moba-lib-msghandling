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

#include <utility>

#include "incident.h"
#include "message.h"

struct MessagingMessages: Message {
    enum MessageName {
        GET_INCIDENT_LIST = 1,
        SET_INCIDENT_LIST = 2,
        NOTIFY_INCIDENT   = 3,
    };

    static constexpr std::uint32_t GROUP_ID = MESSAGING;
};

struct MessagingGetIncidentList final : MessagingMessages {
    static constexpr std::uint32_t MESSAGE_ID = GET_INCIDENT_LIST;

    MessagingGetIncidentList() = default;
};

struct MessagingSetIncidentList final : MessagingMessages {
    static constexpr std::uint32_t MESSAGE_ID = SET_INCIDENT_LIST;

    explicit MessagingSetIncidentList(const nlohmann::json &d) {
        for(auto &iter: d) {
            incidents.emplace_back(iter);
        }
    }
    std::vector<IncidentData> incidents;
};

struct MessagingNotifyIncident final : MessagingMessages {
    static constexpr std::uint32_t MESSAGE_ID = NOTIFY_INCIDENT;

    explicit MessagingNotifyIncident(IncidentData incident): incident{std::move(incident)} {}

    explicit MessagingNotifyIncident(const nlohmann::json &d): incident{d} {
    }
    IncidentData incident;
};

