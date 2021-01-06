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

#include "moba/driving_direction.h"

struct Train {

    Train(int localId, int speed, DrivingDirection direction) : localId {localId}, speed{speed}, direction{direction} {
    }

    template <typename T>
    Train(const T &d) {
        localId = d["localId"].GetInt();
        speed   = d["speed"].GetInt();
        std::string s  = d["direction"].GetString();

        if(s == "FORWARD") {
            direction = DrivingDirection::FORWARD;
        } else if(s == "BACKWARD") {
            direction = DrivingDirection::BACKWARD;
        } else {
            throw moba::common::UnsupportedOperationException{"invalid value given"};
        }
    }

    virtual ~Train() {
    }

    void switchDirection() {
        direction = DrivingDirection::flip(direction);
    }

    int localId;
    int speed;

    DrivingDirection direction;
};

using TrainPtr = std::shared_ptr<Train>;
