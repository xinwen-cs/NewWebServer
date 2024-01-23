//
// Created by root on 24-1-23.
//

#ifndef TINYWEBSERVER_ASYNCLOGGING_H
#define TINYWEBSERVER_ASYNCLOGGING_H

#include "noncopyable.h"
#include <string>
#include <vector>
#include <memory>
#include "Thread.h"
#include "FixedBuffer.h"


class AsyncLogging : noncopyable {
public:
    AsyncLogging(const std::string basename, int flushInterval = 2);
    ~AsyncLogging() {
        if (running_) {
            stop();
        }
    }

    void append(const char* logline, size_t len);

    void start() {
        running_ = true;
        thread_.start();
        latch_.wait();
    }

    void stop() {
        running_ = false;
        cond_.notify();
        thread_.join();
    }

private:
    void threadFunc();
    using Buffer = FixedBuffer<kLargeBuffer>;
    using BufferVector = std::vector<std::shared_ptr<Buffer>>;
    using BufferPtr = std::shared_ptr<Buffer>;

    const int flushInterval_;

    bool running_;

    std::string basename_;

    Thread thread_;
    MutexLock mutex_;
    Condition cond_;
    CountDownLatch latch_;

    BufferPtr currentBuffer_;
    BufferPtr nextBuffer_;

    BufferVector buffers_;
};


#endif //TINYWEBSERVER_ASYNCLOGGING_H
