/*
 *  Project:    moba-common
 *
 *  Copyright (C) 2016 Stefan Paproth <pappi-@gmx.de>
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
#include <memory>

#include <moba-common/exception.h>

#include "message.h"
#include "shared.h"
#include "day.h"
#include "timestruct.h"

struct TimerMessage: public Message {
    enum MessageName {
        TIMER_GLOBAL_TIMER_EVENT = 1,
        TIMER_GET_GLOBAL_TIMER   = 2,
        TIMER_SET_GLOBAL_TIMER   = 3
    };

    static constexpr std::uint32_t GROUP_ID = TIMER;
};

struct TimerGlobalTimerEvent: public TimerMessage {
    static constexpr std::uint32_t MESSAGE_ID = TIMER_GLOBAL_TIMER_EVENT;

    TimerGlobalTimerEvent(const nlohmann::json &d) {
        curModelDay = stringToDayEnum(d["day"].get<std::string>());
        time = Time{d["time"].get<unsigned int>()};
    }

    Time time;
    Day curModelDay;
};

struct TimerGetGlobalTimer: public TimerMessage {
    static constexpr std::uint32_t MESSAGE_ID = TIMER_GET_GLOBAL_TIMER;
};

struct TimerSetGlobalTimer: public TimerMessage {
    static constexpr std::uint32_t MESSAGE_ID = TIMER_SET_GLOBAL_TIMER;

    TimerSetGlobalTimer(
        Day curModelDay, Time curModelTime, unsigned int multiplicator,
        Time sunriseStartTime, Time dayStartTime, Time sunsetStartTime, Time nightStartTime
    ):
        curModelDay{curModelDay}, curModelTime{curModelTime}, multiplicator{multiplicator},
        nightStartTime{nightStartTime}, sunriseStartTime{sunriseStartTime}, dayStartTime{dayStartTime},
        sunsetStartTime{sunsetStartTime}
    {
    }

    TimerSetGlobalTimer(const nlohmann::json &d) {
        auto modelTime = d["modelTime"];
        curModelDay = stringToDayEnum(modelTime["day"].get<std::string>());
        curModelTime = Time{modelTime["time"].get<unsigned int>()};
        multiplicator = d["multiplicator"].get<int>();

        nightStartTime = Time{d["nightStartTime"].get<unsigned int>()};
        sunriseStartTime = Time{d["sunriseStartTime"].get<unsigned int>()};
        dayStartTime = Time{d["dayStartTime"].get<unsigned int>()};
        sunsetStartTime = Time{d["sunsetStartTime"].get<unsigned int>()};
    }

    [[nodiscard]] nlohmann::json getJsonDocument() const override {
        nlohmann::json v;
        v["day"] = dayEnumToString(curModelDay);
        v["time"] = curModelTime.getTime();

        nlohmann::json d;
        d["modelTime"] = v;
        d["multiplicator"] = multiplicator;
        d["nightStartTime"] = nightStartTime.getTime();
        d["sunriseStartTime"] = sunriseStartTime.getTime();
        d["dayStartTime"] = dayStartTime.getTime();
        d["sunsetStartTime"] = sunsetStartTime.getTime();
        return d;
    }

    Day curModelDay;
    Time curModelTime;
    unsigned int multiplicator;
    Time nightStartTime;
    Time sunriseStartTime;
    Time dayStartTime;
    Time sunsetStartTime;
};
