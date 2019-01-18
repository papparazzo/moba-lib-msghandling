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

struct Message {

    std::string getMessageName() {
        return Message::MESSAGE_NAME;
    }

    protected:
        static const std::string MESSAGE_NAME;
};

struct MessageVoid : public Message {

};

struct MessageEchoReq : public Message {

};

const std::string Message::MESSAGE_NAME = "VOID";
//const std::string Message::MESSAGE_NAME = "ECHO_REQ"

/*


ECHO_RES
ERROR
CLIENT_START
CLIENT_CONNECTED
CLIENT_CLOSE
CLIENT_SHUTDOWN
CLIENT_RESET
CLIENT_SELF_TESTING
*/


class Registry {
    public:
        Registry();
        Registry(const Registry& orig);
        virtual ~Registry();

        template<typename T>
        void registerHandler(int i, std::function<void(const T&)> cb) {
            //auto x = [cb](const std::string input) {
            //    cb(convert(input));
            //}
            //handlers[i] = x;
        }

        void handleMsg() {


        }

    protected:
        std::unordered_map<std::string, int> handlers;
};


/*
void handlerForMessageA(const MessageA &);
void handlerForMessageB(const MessageB &);


Registry reg;

reg.register(1, handlerForMessageA);


template <typename T>
T convert(const std::string &input) {
    return reinpret_cast<T> (input);
}
*/