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
#include <boost/any.hpp>

#include "jsonabstractitem.h"


class Message {

    public:
        Message(MessageType msgType = MT_VOID);
        Message(MessageType msgType, JsonItemPtr data);

        virtual ~Message();

        static const std::string MSG_HEADER;
        static const std::string DATA_HEADER;

        static JsonStringPtr convertToString(MessageType mt);
        static MessageType convertToMsgType(const std::string &msgName);

        MessageType getMsgType() const {
            return this->msgType;
        }

        JsonItemPtr getData() const {
            return this->data;
        }

        std::string getRawMessage() const;

        std::string msgTypeAsString() const;

        template<typename charT, typename traits>
        friend std::basic_ostream<charT, traits> &
        operator<< (std::basic_ostream<charT, traits> &lhs, Message const &rhs) {
            return lhs << rhs.msgTypeAsString();
        }

    protected:
        MessageType msgType;
        JsonItemPtr data;
};

using MessagePtr = std::shared_ptr<Message>;
