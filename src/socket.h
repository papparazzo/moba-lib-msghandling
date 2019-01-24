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

#include <exception>
#include <string>
#include <memory>

class SocketException : public std::exception {

    public:
        virtual ~SocketException() noexcept {

        }

        SocketException(const std::string &what) {
            this->what__ = what;
        }

        virtual const char* what() const noexcept {
            return this->what__.c_str();
        }

    private:
        std::string what__;
};

class Socket {
    public:
        Socket(const std::string &host, int port);
        virtual ~Socket() noexcept;

        int getSocket() const {
            return socket;
        }

    protected:
        int socket;
        std::string host;
        int port;

        void init();
};

using SocketPtr = std::shared_ptr<Socket>;

