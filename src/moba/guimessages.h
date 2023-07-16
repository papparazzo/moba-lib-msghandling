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
#include <memory>

#include "message.h"

struct GuiMessage: public Message {
    enum MessageName {
        GUI_SYSTEM_NOTICE = 1,
    };

    static constexpr std::uint32_t GROUP_ID = GUI;
};

struct GuiSystemNotice: public GuiMessage {
    static constexpr std::uint32_t MESSAGE_ID = GUI_SYSTEM_NOTICE;

    enum class NoticeType {
        INFO,
        WARNING,
        ERROR
    };

    GuiSystemNotice(const nlohmann::json &d) {
        std::string type = d["type"].get<std::string>();
        caption = d["caption"].get<std::string>();
        text = d["text"].get<std::string>();

        if(type == "INFO") {
            noticeType = NoticeType::INFO;
        } else if(type == "WARNING") {
            noticeType = NoticeType::WARNING;
        } else if(type == "ERROR") {
            noticeType = NoticeType::ERROR;
        }
    }

    NoticeType  noticeType;
    std::string caption;
    std::string text;
};
