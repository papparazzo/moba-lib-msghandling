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

#include <string>
#include <cstddef>
#include <cstdint>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"

#include <iostream>

struct Message {
    enum MessageGroup {
        BASE        = 1,
        CLIENT      = 2,
        SERVER      = 3,
        TIMER       = 4,
        ENVIRONMENT = 5,
        INTERFACE   = 6,
        SYSTEM      = 7,
        LAYOUT      = 8,
        GUI         = 9,
    };

    template<typename InputStream>
    Message(std::uint32_t grpId, std::uint32_t msgId, InputStream &s) : groupId{grpId}, messageId{msgId} {
        data.ParseStream(s);
    }

    Message(std::uint32_t grpId = 0, std::uint32_t msgId = 0) : groupId{grpId}, messageId{msgId} {
    }

    virtual ~Message() noexcept {
    }

    virtual std::uint32_t getGroupId() const {
        return groupId;
    }
    virtual std::uint32_t getMessageId() const {
        return messageId;
    }

    bool operator!() const {
        if(groupId && messageId) {
            return false;
        }
        return true;
    }

    template<typename OutputStream>
    void Accept(OutputStream &s) const {
        rapidjson::Writer<OutputStream> w{s};
        data.Accept(w);
    }

    rapidjson::Document data;

protected:
    std::uint32_t groupId;
    std::uint32_t messageId;
};
