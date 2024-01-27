//
// Created by root on 24-1-27.
//

#ifndef TINYWEBSERVER_EVENTLOOP_H
#define TINYWEBSERVER_EVENTLOOP_H

#include <functional>
#include <memory>
#include <cassert>

#include "Epoll.h"
#include "base/Thread.h"
#include "base/CurrentThread.h"
#include "Util.h"


class EventLoop {
    using Functor = std::function<void()>;

public:
    EventLoop();
    ~EventLoop();

    void loop();
    void quit();

    void runInLoop(Functor&& cb);
    void queueInLoop(Functor&& cb);

    bool isInLoopThread() const {
        return threadId_ == CurrentThread::tid();
    }

    void assertInLoopThread() { assert(isInLoopThread()); }

    void shutdown(std::shared_ptr<Channel> channel) {
        shutDownWR(channel->getFd());
    }

    void removeFromPoller(std::shared_ptr<Channel> channel) {
        poller_->epoll_del(channel);
    }

    void updatePoller(std::shared_ptr<Channel> channel, int timeout = 0) {
        poller_->epoll_mod(channel, timeout);
    }

    void addToPoller(std::shared_ptr<Channel> channel, int timeout = 0) {
        poller_->epoll_add(channel, timeout);
    }

private:
    bool looping_;
    std::shared_ptr<Epoll> poller_;
    int wakeupFd_;
    bool quit_;
    mutable MutexLock mutex_;
    std::vector<Functor> pendingFunctors_;
    bool callingPendingFunctors_;
    const pid_t threadId_;
    std::shared_ptr<Channel> pwakeupChannel_;

    void wakeup();
    void handleConn();
    void handleRead();
    void doPendingFunctors();
};


#endif //TINYWEBSERVER_EVENTLOOP_H
