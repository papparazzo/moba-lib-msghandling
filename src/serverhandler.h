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
#include <moba/jsonabstractitem.h>
#include "basemessage.h"

class ServerMaxClientCount : public RecieveMessage {
    public:
        ServerMaxClientCount(moba::JsonItemPtr data) {
            maxClientCount = moba::castToInt(data);
        }

        virtual std::string getMessageName() const override {
            return "SERVER_MAX_CLIENT_COUNT";
        }

        std::string getMaxClientCount() {
            return maxClientCount;
        }

    protected:
        int maxClientCount;
};

class ServerNewClientStarted : public RecieveMessage {
    public:
        virtual std::string getMessageName() const override {
            return "SERVER_NEW_CLIENT_STARTED";
        }

        /*
         * appInfo	AppData
appID	Integer
upTime	Time
addr	IP4
port	Integer

         */
};

class ServerClientClosed : public RecieveMessage {
    public:
        ServerClientClosed(moba::JsonItemPtr data) {
            clientId = moba::castToInt(data);
        }

        virtual std::string getMessageName() const override {
            return "SERVER_CLIENT_CLOSED";
        }

        int getClientId() {
            return clientId;
        }

    protected:
        int clientId;
};




/*
SERVER_RESET_CLIENT
SERVER_INFO_REQ
SERVER_INFO_RES
SERVER_CON_CLIENTS_REQ
SERVER_CON_CLIENTS_RES
SERVER_SELF_TESTING_CLIENT
 * /




#include "msgendpoint.h"
#include "jsonabstractitem.h"
#include "message.h"

namespace moba {

    class MsgServerHandler {

        public:
            MsgServerHandler(MsgEndpointPtr msgep) : msgep(msgep) {
            }

            virtual ~MsgServerHandler() {
            }

            void sendResetClient(long id) {msgep->sendMsg(Message::MT_RESET_CLIENT, toJsonNumberPtr(id));}

            void sendSelfTestingClient(long id) {msgep->sendMsg(Message::MT_SELF_TESTING_CLIENT, toJsonNumberPtr(id));}

            void sendServerInfoReq() {msgep->sendMsg(Message::MT_SERVER_INFO_REQ);}

            void sendConClientsReq() {msgep->sendMsg(Message::MT_CON_CLIENTS_REQ);}

        protected:
            MsgEndpointPtr msgep;
    };
}
*/