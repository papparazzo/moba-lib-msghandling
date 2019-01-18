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
#include <moba/jsonabstractitem.h>

class BaseMessage {
    public:
        static const std::string MSG_HEADER;
        static const std::string DATA_HEADER;

        //BaseMessage::BaseMessage() {
        //}

        BaseMessage(moba::JsonItemPtr data) : data{data} {
        }
        BaseMessage(const BaseMessage& orig);
        virtual ~BaseMessage();

        virtual std::string getMessageName() = 0;

        moba::JsonItemPtr getData() const {
            return this->data;
        }

        std::string getRawMessage();

    protected:
        moba::JsonItemPtr data;

    private:
};


