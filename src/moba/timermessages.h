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

struct TimerMessage : public Message {
    enum MessageName {
        TIMER_GLOBAL_TIMER_EVENT = 1,
        TIMER_GET_GLOBAL_TIMER   = 2,
        TIMER_SET_GLOBAL_TIMER   = 3,
        TIMER_GET_COLOR_THEME    = 4,
        TIMER_SET_COLOR_THEME    = 5,
        TIMER_COLOR_THEME_EVENT  = 6
    };

    static constexpr std::uint32_t GROUP_ID = TIMER;
};

struct TimerGlobalTimerEvent : public TimerMessage {
    static constexpr std::uint32_t MESSAGE_ID = TIMER_GLOBAL_TIMER_EVENT;

    TimerGlobalTimerEvent(const rapidjson::Document &d) {
        curModelDay = stringToDayEnum(d["curModelDay"].GetString());
        auto tmp = d["curModelTime"].GetString();
        if(tmp.size() != 5) {
            throw moba::common::UnsupportedOperationException{"invalid time given"};
        }
        hours = std::stoi(tmp.substr(0, 2));
        minutes = std::stoi(tmp.substr(3, 2));
        multiplicator = d["multiplicator"].GetInt();
    }

    unsigned int minutes;
    unsigned int hours;

    Day curModelDay;
    unsigned int multiplicator;
};

struct TimerGetGlobalTimer : public TimerMessage {
    static constexpr std::uint32_t MESSAGE_ID = TIMER_GET_GLOBAL_TIMER;
};

struct TimerSetGlobalTimer : public TimerMessage {
    static constexpr std::uint32_t MESSAGE_ID = TIMER_SET_GLOBAL_TIMER;

    TimerSetGlobalTimer(Day curModelTime, const std::string &curModelTime, unsigned int multiplicator) :
    curModelDay{curModelDay}, curModelTime{curModelTime}, multiplicator{multiplicator} {
    }

    TimerSetGlobalTimer(const rapidjson::Document &d) {
        curModelDay = stringToDayEnum(d["curModelDay"].GetString());
        curModelTime = d["curModelTime"].GetString();
        multiplicator = d["multiplicator"].GetInt();
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetObject();
        d.AddMember()
        auto tmp = dayEnumToString(curModelDay);

        d.AddMember("curModelDay", rapidjson::Value(tmp.c_str(), tmp.length(), d.GetAllocator()), d.GetAllocator());
        d.AddMember("curModelTime", rapidjson::Value(curModelTime.c_str(), curModelTime.length(), d.GetAllocator()), d.GetAllocator());
        d.AddMember("multiplicator", multiplicator, d.GetAllocator());
        return d;
    }

    Day curModelDay;
    std::string curModelTime;
    unsigned int multiplicator;
};

struct TimerGetColorTheme : public TimerMessage {
    static constexpr std::uint32_t MESSAGE_ID = TIMER_GET_COLOR_THEME;
};

struct TimerSetColorTheme : public TimerMessage {
    static constexpr std::uint32_t MESSAGE_ID = TIMER_SET_COLOR_THEME;

    TimerSetColorTheme(const std::string &dimTime, const std::string &brightTime, ThreeState condition) :
    dimTime{dimTime}, brightTime{brightTime}, condition{condition} {
    }

    TimerSetColorTheme(const rapidjson::Document &d) {
        dimTime = d["dimTime"].GetString();
        brightTime = d["brightTime"].GetInt();
        condition = stringToThreeStateEnum(d["condition"].GetString());
    }

    rapidjson::Document getJsonDocument() const override {
        rapidjson::Document d;
        d.SetObject();

        auto conditionStr = threeStateEnumToString(condition);
        d.AddMember("dimTime", rapidjson::Value(dimTime.c_str(), dimTime.length(), d.GetAllocator()), d.GetAllocator());
        d.AddMember("brightTime", rapidjson::Value(brightTime.c_str(), brightTime.length(), d.GetAllocator()), d.GetAllocator());
        d.AddMember("condition", rapidjson::Value(conditionStr.c_str(), conditionStr.length(), d.GetAllocator()), d.GetAllocator());
        return d;
    }

    std::string dimTime;
    std::string brightTime;
    ThreeState condition;
};

struct TimerColorThemeEvent : public TimerMessage {
    static constexpr std::uint32_t MESSAGE_ID = TIMER_COLOR_THEME_EVENT;

    enum class ColorTheme {
		BRIGHT,
		DIM
    };

    TimerColorThemeEvent(const rapidjson::Document &d) {
        std::string status = d["dimTime"].GetString();
        if(status == "BRIGHT") {
            colorTheme = ColorTheme::BRIGHT;
        } else if(status == "DIM") {
            colorTheme = ColorTheme::DIM;
        } else {
            throw moba::common::UnsupportedOperationException{"invalid value given"};
        }
    }

    ColorTheme colorTheme;
};
