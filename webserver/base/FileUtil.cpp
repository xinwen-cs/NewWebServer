//
// Created by henrywen on 2024/1/23.
//

#include <cstdio>
#include "FileUtil.h"

AppendFile::AppendFile(std::string filename) : fp_(fopen(filename.c_str(), "ae")) {
    setbuffer(fp_, buffer_, sizeof buffer_);
}

AppendFile::~AppendFile() {
    if (fp_) {
        fclose(fp_);
    }
}

void AppendFile::append(const char *logline, size_t len) {
    size_t n = this->write(logline, len);
    size_t remain = len - n;
    while (remain > 0) {
        size_t x = this->write(logline + n, remain);
        if (x == 0) {
            int err = ferror(fp_);
            if (err) fprintf(stderr, "AppendFile::append() failed !\n");
            break;
        }
        n += x;
        remain = len - n;
    }
}

void AppendFile::flush() {
    fflush(fp_);
}

size_t AppendFile::write(const char *logline, size_t len) {
#ifdef LINUX
    return fwrite_unlocked(logline, 1, len, fp_);
#endif

#ifdef MACOS
    return fwrite(logline, 1, len, fp_);
#endif
}
