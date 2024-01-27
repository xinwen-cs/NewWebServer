//
// Created by root on 24-1-27.
//

#ifndef TINYWEBSERVER_EVENTLOOPTHREADPOOL_H
#define TINYWEBSERVER_EVENTLOOPTHREADPOOL_H

#include "base/noncopyable.h"
#include "EventLoopThread.h"

#include <vector>
#include <memory>


class EventLoopThreadPool : noncopyable {
public:
    EventLoopThreadPool(EventLoop* baseLoop, int numThreads);

    ~EventLoopThreadPool() = default;

    void start();

    EventLoop* getNextLoop();

private:
    EventLoop* baseLoop_;
    bool started_;
    int numThreads_;
    int next_;
    std::vector<std::shared_ptr<EventLoopThread>> threads_;
    std::vector<EventLoop*> loops_;
};


#endif //TINYWEBSERVER_EVENTLOOPTHREADPOOL_H
