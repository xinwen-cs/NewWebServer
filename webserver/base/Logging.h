//
// Created by root on 24-1-23.
//

#ifndef TINYWEBSERVER_LOGGING_H
#define TINYWEBSERVER_LOGGING_H

#include "LogStream.h"
#include <cstdio>

class Logger {
public:
    Logger(const char* filename, size_t len);

    ~Logger();

    static void setLogFileName(std::string fileName) { logFileName_ = fileName; }
    static std::string getLogFileName() { return logFileName_; }

    LogStream& stream() {
        return impl_.stream_;
    }

private:
    class Impl {
    public:
        Impl(const char* filename, int line);
        void formatTime();

        LogStream stream_;
        int line_;
        std::string basename_;
    };
    Impl impl_;
    static std::string logFileName_;
};

#define LOG Logger(__FILE__, __LINE__).stream()

#endif //TINYWEBSERVER_LOGGING_H
