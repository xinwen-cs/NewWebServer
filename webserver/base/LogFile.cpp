//
// Created by henrywen on 2024/1/23.
//

#include "LogFile.h"

LogFile::LogFile(const std::string& basename, int flushFreq) :
    basename_(basename),
    flushFreq_(flushFreq),
    count_(0),
    mutex_(new MutexLock),
    file_(std::make_unique<AppendFile>(basename)){

}

LogFile::~LogFile() {}

void LogFile::append(const char* logline, size_t len) {
    MutexLockGuard lock(*mutex_);
    append_unlocked(logline, len);
}

void LogFile::flush() {
    MutexLockGuard lock(*mutex_);
    file_->flush();
}

void LogFile::append_unlocked(const char* logline, size_t len) {
    file_->append(logline, len);
    ++count_;
    if (count_ >= flushFreq_) {
        file_->flush();
    }
}
