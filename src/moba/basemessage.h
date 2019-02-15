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
        static const std::string MSG_HEADER_NAME;
        static const std::string MSG_HEADER_DATA;

        virtual ~BaseMessage() noexcept {
        }

    protected:
        BaseMessage() {
        }
};

class RecieveMessage : public BaseMessage {
};

class DispatchMessage : public BaseMessage {
    public:
        virtual std::string getRawMessage() const = 0;
};

class DispatchGenericMessage : public DispatchMessage {
    public:
        DispatchGenericMessage(const std::string msgName, moba::JsonItemPtr data) : msgName{msgName}, data{data} {
        }

        DispatchGenericMessage(const std::string msgName) : msgName{msgName}, data{moba::toJsonNULLPtr()} {
        }

        virtual std::string getRawMessage() const {
            moba::JsonObject obj;

            obj[BaseMessage::MSG_HEADER_NAME] = moba::toJsonStringPtr(msgName);
            obj[BaseMessage::MSG_HEADER_DATA] = data;
            return obj.getJsonString();
        };

    protected:
        std::string msgName;
        moba::JsonItemPtr data;
};

template<typename T = int>
class DispatchMessageType : public DispatchMessage {
    public:
        virtual std::string getRawMessage() const {
            moba::JsonObject obj;

            obj[BaseMessage::MSG_HEADER_NAME] = moba::toJsonStringPtr(T::getMessageName());
            obj[BaseMessage::MSG_HEADER_DATA] = getData();
            return obj.getJsonString();
        }

        virtual moba::JsonItemPtr getData() const {
            return moba::toJsonNULLPtr();
        }
};
