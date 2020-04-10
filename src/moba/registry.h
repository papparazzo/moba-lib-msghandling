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
#include "rapidjson/document.h"

class Registry {
    public:
       /*
        using HandlerFnWrapper = std::function<void(int, const rapidjson::Document &data)
        using HandlerDefFnWrapper = std::function<void(int, int, const rapidjson::Document &data);

        Registry() {
        }

        Registry(const Registry& orig) = delete;

        virtual ~Registry() noexcept {
        }

        void registerHandler(int groupId, HandlerFnWrapper fn) {
            handlers[groupId] = fn;
        }

        void registerDefaultHandler(HandlerDefFnWrapper fn) {
            defHandler = fn;
        }

        auto handleMsg(int grpId, int msgId, const rapidjson::Document &msgData) -> bool {
            auto iter = handlers.find(grpId);
            if(iter != handlers.end()) {
                iter->second(msgId, msgData);
                return true;
            }

            if(defHandler) {
                defHandler(grpId, msgId, msgData);
            }
            return false;
        }

    protected:
        using HandlerMap = std::unordered_map<int, HandlerFnWrapper>>;

        HandlerMap       handlers;
        HandlerFnWrapper defHandler;
        HandlerFnWrapper auxHandler;
        */
};

