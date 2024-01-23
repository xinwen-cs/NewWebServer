//
// Created by root on 24-1-23.
//

#ifndef TINYWEBSERVER_LOGSTREAM_H
#define TINYWEBSERVER_LOGSTREAM_H

#include <string>
#include "noncopyable.h"
#include "FixedBuffer.h"

class LogStream : noncopyable {
public:
    using Buffer = FixedBuffer<kSmallBuffer>;

    LogStream& operator<<(bool v) {
        buffer_.append(v ? "1" : "0", 1);
        return *this;
    }

    LogStream& operator<<(short);
    LogStream& operator<<(unsigned short);
    LogStream& operator<<(int);
    LogStream& operator<<(unsigned int);
    LogStream& operator<<(long);
    LogStream& operator<<(unsigned long);
    LogStream& operator<<(long long);
    LogStream& operator<<(unsigned long long);


    LogStream& operator<<(double v);
    LogStream& operator<<(long double);
    LogStream& operator<<(float v) {
        *this << static_cast<double>(v);
        return *this;
    }

    LogStream& operator<<(char v) {
        buffer_.append(&v, 1);
        return *this;
    }

    LogStream& operator<<(const char* str) {
        if (str) {
            buffer_.append(str, strlen(str));
        } else {
            buffer_.append("(null)", 6);
        }
        return *this;
    }

    LogStream& operator<<(const std::string& v) {
        buffer_.append(v.c_str(), v.size());
        return *this;
    }

    const Buffer& buffer() {
        return buffer_;
    }
private:
    template <typename T>
    void formatInteger(T v);

    Buffer buffer_;
    static const int kMaxNumericSize = 32;
};


#endif //TINYWEBSERVER_LOGSTREAM_H
