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

#include "basemessage.h"
#include <moba/jsonabstractitem.h>

struct LayoutGetLayoutReq : public DispatchMessageType<LayoutGetLayoutReq> {

    LayoutGetLayoutReq(int layoutId) : layoutId{layoutId} {
    }

    static std::string getMessageName() {
        return "LAYOUT_GET_LAYOUT_REQ";
    }

    virtual moba::JsonItemPtr getData() const override {
        return moba::toJsonNumberPtr(layoutId);
    }

    int layoutId;
};

/*
struct LayoutGetLayoutRes : public RecieveMessage {

    ServerConClientsRes(moba::JsonItemPtr data) {
        auto a = boost::dynamic_pointer_cast<moba::JsonArray>(data);
        for(auto iter : *a) {
            endpoints.push_back(EndpointData{boost::dynamic_pointer_cast<moba::JsonObject>(iter)});
        }
    }

    static std::string getMessageName() {
        return "LAYOUT_GET_LAYOUT_RES";
    }

    std::vector<EndpointData> endpoints;
};
*/



