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
 *  along with this program. If not, see <https://www.gnu.org/licenses/agpl.txt>.
 *
 */

#pragma once

#include <string>
#include <chrono>
#include <ctime>
#include <utility>

#include "enumincidentlevel.h"
#include "enumincidenttype.h"
#include "shared.h"

struct IncidentData final {
    IncidentData(
        IncidentLevel level, 
        IncidentType type, 
        std::string  caption,
        std::string  message,
        std::string  source
    ) : level{level}, type{type}, caption{std::move(caption)}, message{std::move(message)}, source{std::move(source)} {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&time);

        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
        timeStamp = buffer;
    }

    explicit IncidentData(const nlohmann::json &d): origin{d["origin"]} {
        level = stringToIncidentLevelEnum(d["level"].get<std::string>());
        type = stringToIncidentTypeEnum(d["type"].get<std::string>());
        caption = d["caption"].get<std::string>();
        source = d["source"].get<std::string>();
        message = d["message"].get<std::string>();
        timeStamp = d["timeStamp"].get<std::string>();
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const {
        nlohmann::json d;

        d["caption"] = caption;
        d["level"] = incidentLevelEnumToString(level);
        d["type"] = incidentTypeEnumToString(type);
        d["message"] = message;
        d["source"] = source;
        d["origin"] = origin.getJsonDocument();    // origin wird nur vom moba-server gesetzt!
        d["timeStamp"] = timeStamp;
        return d;
    }

    IncidentLevel level;
    IncidentType type;
    std::string	caption;
    std::string	message;
    std::string	source;
    EndpointData origin;
    std::string	timeStamp;
};
