// Tencent is pleased to support the open source community by making RapidJSON available.
//
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip. All rights reserved.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_FILEREADSTREAM_H_
#define RAPIDJSON_FILEREADSTREAM_H_

#include "stream.h"
#include <cstdio>
#include <memory>
#include "socket.h"

#ifdef __clang__
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(padded)
RAPIDJSON_DIAG_OFF(unreachable-code)
RAPIDJSON_DIAG_OFF(missing-noreturn)
#endif

RAPIDJSON_NAMESPACE_BEGIN

class SocketReadStream {
public:
    typedef char Ch;    //!< Character type (byte).

    SocketReadStream(int socket, size_t msgSize) : socket_{socket}, bufferLast_{0}, current_{buffer_}, readCount_{0}, count_{0}, msgSize_{msgSize}, eof_{false} {
        RAPIDJSON_ASSERT(socket_ != 0);
        Read();
    }

    Ch Peek() const { return *current_; }
    Ch Take() { Ch c = *current_; Read(); return c; }
    size_t Tell() const { return count_ + static_cast<size_t>(current_ - buffer_); }

    // Not implemented
    void Put(Ch) { RAPIDJSON_ASSERT(false); }
    void Flush() { RAPIDJSON_ASSERT(false); }
    Ch* PutBegin() { RAPIDJSON_ASSERT(false); return 0; }
    size_t PutEnd(Ch*) { RAPIDJSON_ASSERT(false); return 0; }

    // For encoding detection only.
    const Ch* Peek4() const {
        return (current_ + 4 - !eof_ <= bufferLast_) ? current_ : 0;
    }

private:
    void Read() {
        if (current_ < bufferLast_) {
            ++current_;
            return;
        }

        if (eof_) {
            return;
        }
        count_ += readCount_;

        size_t bufferSize = BUFFER_SIZE;
        if(count_ + BUFFER_SIZE > msgSize_) {
            bufferSize = msgSize_ - count_;
        }

        if(count_ == msgSize_) {
            readCount_ = 0;
        } else {
            readCount_ = ::recv(socket_, buffer_, bufferSize, MSG_WAITALL);

            if(readCount_ == -1) {
                throw SocketException{"reading failed"};
            }
        }

        bufferLast_ = buffer_ + readCount_ - 1;
        current_ = buffer_;

        if (static_cast<size_t>(readCount_) < BUFFER_SIZE) {
            buffer_[readCount_] = '\0';
            ++bufferLast_;
            eof_ = true;
        }
    }

    static const size_t BUFFER_SIZE = 4096;

    int     socket_;
    Ch      buffer_[BUFFER_SIZE];
    Ch     *bufferLast_;
    Ch     *current_;
    ssize_t readCount_;
    size_t  count_;  //!< Number of characters read
    size_t  msgSize_;
    bool    eof_;
};

RAPIDJSON_NAMESPACE_END

#ifdef __clang__
RAPIDJSON_DIAG_POP
#endif

#endif // RAPIDJSON_FILESTREAM_H_
