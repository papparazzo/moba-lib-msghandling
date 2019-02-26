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
#include <moba/jsonabstractitem.h>

#include "basemessage.h"

struct GuiSystemNotice : public RecieveMessage {
    enum class NoticeType {
        INFO,
        WARNING,
        ERROR
    };

    GuiSystemNotice(moba::JsonItemPtr data) {
        moba::JsonObjectPtr o = std::dynamic_pointer_cast<moba::JsonObject>(data);
        std::string type = moba::castToString(o->at("type"));
        caption = moba::castToString(o->at("caption"));
        text = moba::castToString(o->at("text"));

        if(type == "INFO") {
            noticeType = NoticeType::INFO;
        } else if(type == "WARNING") {
            noticeType = NoticeType::WARNING;
        } else if(type == "ERROR") {
            noticeType = NoticeType::ERROR;
        }
    }

    static std::string getMessageName() {
        return "GUI_SYSTEM_NOTICE";
    }

    NoticeType  noticeType;
    std::string caption;
    std::string text;
};



