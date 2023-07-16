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
#include <utility>

#include "rawmessage.h"
#include "systemmessages.h"
#include "servermessages.h"

class Registry {
public:

    using HandlerMsgFnWrapper = std::function<void(const nlohmann::json &data)>;
    using HandlerDefFnWrapper = std::function<void(std::uint32_t, std::uint32_t, const nlohmann::json &data)>;

    Registry() {
    }

    Registry(const Registry& orig) = delete;

    virtual ~Registry() noexcept = default;

    // TODO: deprecated! remove this
    template<typename T>
    void registerHandler(std::function<void(const T&)> fn) {
        handlers[T::GROUP_ID][T::MESSAGE_ID] = [fn](const nlohmann::json &data) {
            T m{data};
            fn(m);
        };
    }
    
    template<typename T>
    void registerHandler(std::function<void(T&&)> fn) {
        handlers[T::GROUP_ID][T::MESSAGE_ID] = [fn](const nlohmann::json &data) {
            T m{data};
            fn(std::move(m));
        };
    }

    template<typename T>
    void registerHandler(std::function<void()> fn) {
        handlers[T::GROUP_ID][T::MESSAGE_ID] = [fn](const nlohmann::json &data) {
            fn();
        };
    }

    void registerDefaultHandler(HandlerDefFnWrapper fn) {
        defHandler = fn;
    }

    void registerAuxiliaryHandler(HandlerDefFnWrapper fn) {
        auxHandler = fn;
    }

    auto handleMsg(const RawMessage &msg) -> bool {
        if(!msg) {
            return true;
        }

        if(auxHandler) {
            auxHandler(msg.groupId, msg.messageId, msg.data);
        }

        auto iter = handlers.find(msg.groupId);

        if(iter != handlers.end()) {
            auto iter2 = iter->second.find(msg.messageId);
            if(iter2 != iter->second.end()) {
                iter2->second(msg.data);
                return true;
            }
        }

        if(defHandler) {
            defHandler(msg.groupId, msg.messageId, msg.data);
        }
        return false;
    }

protected:
    using HandlerMapG = std::unordered_map<std::uint32_t, HandlerMsgFnWrapper>;
    using HandlerMapF = std::unordered_map<std::uint32_t, HandlerMapG>;

    HandlerMapF         handlers;
    HandlerDefFnWrapper defHandler;
    HandlerDefFnWrapper auxHandler;
};
