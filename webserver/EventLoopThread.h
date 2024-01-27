//
// Created by root on 24-1-27.
//

#ifndef TINYWEBSERVER_EVENTLOOPTHREAD_H
#define TINYWEBSERVER_EVENTLOOPTHREAD_H

#include "EventLoop.h"
#include "base/noncopyable.h"

class EventLoopThread : noncopyable {
public:
    EventLoopThread();
    ~EventLoopThread();

    EventLoop* startLoop();

private:
    void threadFunc();
    EventLoop* loop_;

    Thread thread_;
    MutexLock mutex_;
    Condition cond_;
};


#endif //TINYWEBSERVER_EVENTLOOPTHREAD_H
