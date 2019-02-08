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

#include <unordered_map>
#include <string>
#include <functional>
#include <memory>

#include "basemessage.h"
#include <moba/jsonabstractitem.h>

#include <iostream>

class Registry {
    public:
        using HandlerFnWrapper = std::function<void(const std::string&, moba::JsonItemPtr)>;

        Registry() {
        }

        Registry(const Registry& orig) = delete;
        virtual ~Registry() noexcept {
        }

        template<typename T>
        void registerHandler(std::function<void(const T&)> fn) {
            handlers[T::getMessageName()] = [fn](moba::JsonItemPtr data) {
                T m{data};
                fn(m);
            };
        }

        void registerDefaultHandler(HandlerFnWrapper fn) {
            defHandler = fn;
        }

        auto handleMsg(moba::JsonItemPtr data) -> bool {
            auto o = boost::dynamic_pointer_cast<moba::JsonObject>(data);
            if(!o) {
                return false;
            }

            auto msgKey = moba::castToString(o->at(BaseMessage::MSG_HEADER_NAME));
            auto msgData = o->at(BaseMessage::MSG_HEADER_DATA);

            auto iter = handlers.find(msgKey);
            if(iter != handlers.end()) {
                iter->second(msgData);
                return true;
            }

            if(defHandler) {
                defHandler(msgKey, msgData);
            }
            return false;
        }

    protected:
        using HandlerMap = std::unordered_map<std::string, std::function<void(moba::JsonItemPtr)>>;

        HandlerMap       handlers;
        HandlerFnWrapper defHandler;
};

