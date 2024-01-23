//
// Created by henrywen on 2024/1/23.
//

#ifndef TINYWEBSERVER_LOGFILE_H
#define TINYWEBSERVER_LOGFILE_H

#include "FileUtil.h"
#include "Mutex.h"

#include <string>


class LogFile : noncopyable {
public:
    LogFile(const std::string& basename, int flushFreq = 1-24);

    ~LogFile();

    void append(const char* logline, size_t len);

    void flush();

private:
    void append_unlocked(const char* logline, size_t len);

    const std::string basename_;
    const int flushFreq_;

    int count_;

    std::unique_ptr<MutexLock> mutex_;
    std::unique_ptr<AppendFile> file_;
};


#endif //TINYWEBSERVER_LOGFILE_H
