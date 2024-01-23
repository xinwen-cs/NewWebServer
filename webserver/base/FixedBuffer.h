//
// Created by root on 24-1-23.
//

#ifndef TINYWEBSERVER_FIXEDBUFFER_H
#define TINYWEBSERVER_FIXEDBUFFER_H

#include "noncopyable.h"
#include <cstdio>
#include <cstring>

// 4kb
const int kSmallBuffer = 4000;
// 4mb
const int kLargeBuffer = 4000 * 1000;

template <int SIZE>
class FixedBuffer : noncopyable {
public:
    FixedBuffer() : cur(data_) {};

    ~FixedBuffer() = default;

    void append(const char* buf, size_t len) {
        if (avail() > len) {
            memcpy(cur, buf, len);
            cur += len;
        }
    }

    const char* data() const { return data_; }

    size_t length() const {
        return cur - data_;
    }

    char* current() {
        return cur;
    }

    size_t avail() const {
        return end() - cur;
    }

    void add(size_t len) {
        cur += len;
    }

    void reset() {
        cur = data_;
    }

    void bzero() {
        memset(data_, 0, sizeof data_);
    }
private:
    const char* end() const {
        return data_ + sizeof data_;
    }

    char data_[SIZE];
    char* cur;
};

#endif //TINYWEBSERVER_FIXEDBUFFER_H
