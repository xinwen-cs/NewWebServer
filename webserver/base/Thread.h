//
// Created by henrywen on 2024/1/23.
//

#ifndef TINYWEBSERVER_THREAD_H
#define TINYWEBSERVER_THREAD_H

#include "noncopyable.h"
#include "CountDownLatch.h"
#include <string>
#include <functional>
#include <atomic>

class Thread : noncopyable {
public:
    typedef std::function<void()> ThreadFunc;
    explicit Thread(const ThreadFunc&, const std::string& name = std::string());

    ~Thread();

    void start();
    int join();

    bool started() const {
        return started_;
    }

    pid_t tid() const { return tid_; }
    const std::string& name() const { return name_; }


private:
    void setDefaultName();
    bool started_;
    bool joined_;
    pthread_t pthreadId_;
    pid_t tid_;
    ThreadFunc func_;
    std::string name_;
    CountDownLatch latch_;

    static std::atomic_int numCreated;
};


#endif //TINYWEBSERVER_THREAD_H
