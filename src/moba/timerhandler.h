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

#include <moba/jsonabstractitem.h>

#include "basemessage.h"
#include "shared.h"

struct TimerGlobalTimerEvent  : public RecieveMessage {
    TimerGlobalTimerEvent(moba::JsonItemPtr data) {
        auto o = std::dynamic_pointer_cast<moba::JsonObject>(data);
        curModelTime = moba::castToString(o->at("curModelTime"));
        multiplicator = moba::castToInt(o->at("multiplicator"));
    }

    static std::string getMessageName() {
        return "GLOBAL_TIMER_EVENT";
    }

    std::string curModelTime;
    unsigned int multiplicator;
};

struct TimerGetGlobalTimer : public DispatchMessageType<TimerGetGlobalTimer> {
    static std::string getMessageName() {
        return "GET_GLOBAL_TIMER";
    }
};

struct TimerSetGlobalTimer : public RecieveMessage, public DispatchMessageType<TimerSetGlobalTimer> {
    TimerSetGlobalTimer(const std::string &curModelTime, unsigned int multiplicator) :
    curModelTime{curModelTime}, multiplicator{multiplicator} {
    }

    TimerSetGlobalTimer(moba::JsonItemPtr data) {
        auto o = std::dynamic_pointer_cast<moba::JsonObject>(data);
        curModelTime = moba::castToString(o->at("curModelTime"));
        multiplicator = moba::castToInt(o->at("multiplicator"));
    }

    static std::string getMessageName() {
        return "SET_GLOBAL_TIMER";
    }

    virtual moba::JsonItemPtr getData() const override {
        moba::JsonObjectPtr obj(new moba::JsonObject());
        (*obj)["curModelTime" ] = moba::toJsonStringPtr(curModelTime);
        (*obj)["multiplicator"] = moba::toJsonNumberPtr(multiplicator);
        return obj;
    }

    std::string curModelTime;
    unsigned int multiplicator;
};

struct TimerGetColorTheme : public DispatchMessageType<TimerGetColorTheme> {
    static std::string getMessageName() {
        return "GET_COLOR_THEME";
    }
};

struct TimerSetColorTheme : public RecieveMessage, public DispatchMessageType<TimerSetColorTheme> {
    TimerSetColorTheme(const std::string &dimTime, const std::string &brightTime, moba::JsonThreeState::ThreeState condition) :
    dimTime{dimTime}, brightTime{brightTime}, condition{condition} {
    }

    TimerSetColorTheme(moba::JsonItemPtr data) {
        auto o = std::dynamic_pointer_cast<moba::JsonObject>(data);
        dimTime = moba::castToString(o->at("dimTime"));
        brightTime = moba::castToString(o->at("brightTime"));
        condition = moba::castToThreeState(o->at("condition"));
    }

    static std::string getMessageName() {
        return "SET_COLOR_THEME";
    }

    virtual moba::JsonItemPtr getData() const override {
        moba::JsonObjectPtr obj(new moba::JsonObject());
        (*obj)["dimTime"   ] = moba::toJsonStringPtr(dimTime);
        (*obj)["brightTime"] = moba::toJsonStringPtr(brightTime);
        (*obj)["condition" ] = moba::toJsonThreeStatePtr(condition);
        return obj;
    }

    std::string dimTime;
    std::string brightTime;
    moba::JsonThreeState::ThreeState condition;
};

struct TimerColorThemeEvent  : public RecieveMessage {
    enum class ColorTheme {
		BRIGHT,
		DIM
    };

    TimerColorThemeEvent(moba::JsonItemPtr data) {
        std::string status = moba::castToString(data);
        if(status == "BRIGHT") {
            colorTheme = ColorTheme::BRIGHT;
        } else if(status == "DIM") {
            colorTheme = ColorTheme::DIM;
        }
    }

    static std::string getMessageName() {
        return "COLOR_THEME_EVENT";
    }

    ColorTheme colorTheme;
};