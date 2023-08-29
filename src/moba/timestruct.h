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
 *  along with this program. If not, see <http://www.gnu.org/licenses/agpl.txt>.
 *
 */

#pragma once

#include <string>

struct Time final {
    Time();
    Time(unsigned int hours, unsigned int minutes);
    explicit Time(unsigned int time);
    explicit Time(const std::string &time);
    Time(const Time& t) = default;

    virtual ~Time() noexcept = default;

    [[nodiscard]] unsigned int getHours() const;
    [[nodiscard]] unsigned int getMinutes() const;
    [[nodiscard]] unsigned int getTime() const;
    [[nodiscard]] std::string getTimeAsString() const;

    friend bool operator== (const Time& t1, const Time& t2);
    friend bool operator!= (const Time& t1, const Time& t2);

    friend bool operator< (const Time& t1, const Time& t2);
    friend bool operator> (const Time& t1, const Time& t2);

    friend bool operator<= (const Time& t1, const Time& t2);
    friend bool operator>= (const Time& t1, const Time& t2);

private:
    unsigned int time;

};
