//
// Created by henrywen on 2024/1/23.
//

#ifndef TINYWEBSERVER_FILEUTIL_H
#define TINYWEBSERVER_FILEUTIL_H

#include "noncopyable.h"
#include <string>

class AppendFile : noncopyable {
public:
    explicit AppendFile(std::string filename);
    ~AppendFile();

    void append(const char* logline, size_t len);
    void flush();

private:
    size_t write(const char* logline, size_t len);
    FILE* fp_;
    char buffer_[64 * 1024];
};

#endif //TINYWEBSERVER_FILEUTIL_H
