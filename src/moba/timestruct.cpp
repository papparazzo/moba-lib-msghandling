/*
 *  Project:    moba-systemmanager
 *
 *  Copyright (C) 2022 Stefan Paproth <pappi-@gmx.de>
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

#include "timestruct.h"
#include <sstream>

Time::Time(): time{0} {
}

Time::Time(const unsigned int hours, const unsigned int minutes) {
    time = hours * 60 + minutes;
}

Time::Time(const unsigned int time): time{time} {
}

Time::Time(const std::string &str) {
    if(str.length() != 5) {
        time = 0;
        return;
    }

    time = std::stoi(str.substr(0, 2)) * 60 + std::stoi(str.substr(3, 2));
}

unsigned int Time::getHours() const {
    return time / 60;
}

unsigned int Time::getMinutes() const {
    return time % 60;
}

unsigned int Time::getTime() const {
    return time;
}

std::string Time::getTimeAsString() const {

    const auto h = getHours();
    const auto m = getMinutes();

    std::stringstream ss;

    if(h < 10) {
        ss << "0";
    }
    ss << h << ":";

    if(m < 10) {
        ss << "0";
    }
    ss << m;
    return ss.str();
}

bool operator== (const Time& t1, const Time& t2) {
    return t1.time == t2.time;
}

bool operator!= (const Time& t1, const Time& t2) {
    return t1.time != t2.time;
}

bool operator< (const Time& t1, const Time& t2) {
    return t1.time < t2.time;
}

bool operator> (const Time& t1, const Time& t2) {
    return t1.time > t2.time;
}

bool operator<= (const Time& t1, const Time& t2) {
    return t1.time <= t2.time;
}

bool operator>= (const Time& t1, const Time& t2) {
    return t1.time >= t2.time;
}

