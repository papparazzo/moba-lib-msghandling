/*
 *  Project:    moba-tester
 *
 *  Copyright (C) 2020 Stefan Paproth <pappi-@gmx.de>
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

#include "stream.h"
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include "socket.h"

#ifdef __clang__
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(unreachable-code)
#endif

RAPIDJSON_NAMESPACE_BEGIN

class SocketWriteStream {
public:
    typedef unsigned char Ch;    //!< Character type. Only support char.

    SocketWriteStream(int socket, unsigned char* buffer, size_t bufferSize) : socket{socket}, buffer{buffer}, bufferEnd{buffer + bufferSize}, current{buffer} {
        RAPIDJSON_ASSERT(socket != 0);
    }

    void Put(char c) {
        if(current >= bufferEnd) {
            Flush();
        }

        *current++ = c;
    }

    void PutN(char c, size_t n) {
        size_t avail = static_cast<size_t>(bufferEnd - current);
        while(n > avail) {
            std::memset(current, c, avail);
            current += avail;
            Flush();
            n -= avail;
            avail = static_cast<size_t>(bufferEnd - current);
        }

        if(n > 0) {
            std::memset(current, c, n);
            current += n;
        }
    }

    void Flush() {
        if(current == buffer) {
            return;
        }
        ssize_t res = ::send(socket, buffer, current - buffer, 0);
        if(static_cast<unsigned int>(res) < current - buffer) {
            throw SocketException{"sending failed"};
        }
        current = buffer;
    }

    // Not implemented
    char Peek() const { RAPIDJSON_ASSERT(false); return 0; }
    char Take() { RAPIDJSON_ASSERT(false); return 0; }
    size_t Tell() const { RAPIDJSON_ASSERT(false); return 0; }
    char* PutBegin() { RAPIDJSON_ASSERT(false); return 0; }
    size_t PutEnd(char*) { RAPIDJSON_ASSERT(false); return 0; }

private:
    // Prohibit copy constructor & assignment operator.
    SocketWriteStream(const SocketWriteStream&);
    SocketWriteStream& operator=(const SocketWriteStream&);

    int socket;
    Ch *buffer;
    Ch *bufferEnd;
    Ch *current;
};

//! Implement specialized version of PutN() with memset() for better performance.
template<>
inline void PutN(SocketWriteStream& stream, char c, size_t n) {
    stream.PutN(c, n);
}

RAPIDJSON_NAMESPACE_END

#ifdef __clang__
RAPIDJSON_DIAG_POP
#endif
