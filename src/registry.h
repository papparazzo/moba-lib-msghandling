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

#include "basemessage.h"
#include <moba/jsonabstractitem.h>

template <typename T>
T convert(const std::string &input) {
    return reinterpret_cast<T> (input);
}

//void handlerForMessageA(const MessageA &);
//void handlerForMessageB(const MessageB &);


class Registry {
    public:
        using DefHandler = std::function<void(moba::JsonItemPtr)>;

        Registry();
        Registry(const Registry& orig);
        virtual ~Registry();

        template<typename T>
        void registerHandler(std::function<void(const T&)> fn) {
            T msg;
            handlers[msg.MESSAGE_NAME] = [fn](const std::string &input) {
                //convert(input);
                //fn(convert(input));
            };
        }

        void registerDefaultHandler(DefHandler fn) {
            defHandler = fn;
        }

        bool handleMsg() {
            std::string msgKey = "";

            auto iter = handlers.find(msgKey);
            if(iter != handlers.end()) {
                iter->second("bal");
                return true;
            }

            if(defHandler) {
               // defHandler();
            }

        }

    protected:
        using HandlerFnWrapper = std::function<void(const std::string&)>;
        using HandlerMap = std::unordered_map<std::string, HandlerFnWrapper>;

        HandlerMap handlers;
        DefHandler defHandler;
};

