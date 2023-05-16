/*
 *  Project:    moba-blocksystem
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

#include <memory>
#include <map>

#include <moba-common/exception.h>
#include <moba-common/drivingdirection.h>

struct Train {

    Train(
    std::uint32_t id, std::uint32_t address, std::uint32_t speed, moba::DrivingDirection direction):
    id{id}, address {address}, speed{speed}, direction{direction} {
    }

    template <typename T>
    Train(const T &d) {
        address = d["address"].GetInt();
        speed   = d["speed"].GetInt();
        id      = d["id"].GetInt();
        direction.setDrivingDirection(d["drivingDirection"].GetString());
    }

    virtual ~Train() {
    }

    std::uint32_t id;
    std::uint32_t address;
    std::uint32_t speed;

    moba::DrivingDirection direction;
};

using TrainPtr = std::shared_ptr<Train>;
using TrainListPtr = std::shared_ptr<std::map<int, std::shared_ptr<Train>>>;
