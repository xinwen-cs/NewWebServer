//
// Created by root on 24-1-27.
//

#include "EventLoop.h"
#include "base/Logging.h"

#include <sys/epoll.h>
#include <sys/eventfd.h>

__thread EventLoop* t_loopInThisThread;

int createEventFd() {
    int event_fd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);

    if (event_fd < 0) {
        LOG << "Failed in eventfd";
        abort();
    }

    return event_fd;
}

EventLoop::EventLoop() :
    looping_(false),
    poller_(new Epoll()),
    wakeupFd_(createEventFd()),
    quit_(false),
    callingPendingFunctors_(false),
    threadId_(CurrentThread::tid()),
    wakeupChannel_(new Channel(wakeupFd_)) {
    if (t_loopInThisThread) {
         LOG << "Another EventLoop " << t_loopInThisThread << " exists in this thread " << threadId_;
    } else {
        t_loopInThisThread = this;
    }

    wakeupChannel_->setEvents(EPOLLIN | EPOLLET);
    wakeupChannel_->setReadHandler(std::bind(&EventLoop::handleRead, this));
    wakeupChannel_->setConnHandler(std::bind(&EventLoop::handleConn, this));
    poller_->epoll_add(wakeupChannel_, 0);
}

EventLoop::~EventLoop() {
    close(wakeupFd_);
    t_loopInThisThread = NULL;
}

void EventLoop::wakeup() {
    uint64_t one = 1;
    ssize_t n = writen(wakeupFd_, (char*)(&one), sizeof one);
    if (n != sizeof one) {
        LOG << "EventLoop::wakeup() writes " << n << " bytes instead of 8";
    }
}

void EventLoop::handleConn() {
    updatePoller(wakeupChannel_, 0);
}

void EventLoop::handleRead() {
    uint64_t one = 1;
    ssize_t n = readn(wakeupFd_, &one, sizeof one);
    if (n != sizeof one) {
        LOG << "EventLoop::handleRead() reads " << n << " bytes instead of 8";
    }
    wakeupChannel_->setEvents(EPOLLIN | EPOLLET);
}

void EventLoop::runInLoop(EventLoop::Functor &&cb) {
    if (isInLoopThread()) {
        cb();
    } else {
        queueInLoop(std::move(cb));
    }
}

void EventLoop::queueInLoop(EventLoop::Functor &&cb) {
    {
        MutexLockGuard lock(mutex_);
        pendingFunctors_.emplace_back(std::move(cb));
    }

    if (!isInLoopThread() || callingPendingFunctors_) {
        wakeup();
    }
}

void EventLoop::loop() {
    assert(!looping_);
    assert(isInLoopThread());

    looping_ = true;
    quit_ = false;

    std::vector<shared_channel_ptr> ret;

    while (!quit_) {
        ret.clear();
        ret = poller_->poll();
        for (auto& it : ret) {
            it->handleEvents();
        }
        doPendingFunctors();
        poller_->handleExpired();
    }
    looping_ = false;
}

void EventLoop::doPendingFunctors() {
    std::vector<Functor> functors;
    callingPendingFunctors_ = true;

    {
        MutexLockGuard lock(mutex_);
        functors.swap(pendingFunctors_);
    }

    for (size_t i = 0; i < functors.size(); ++i) {
        functors[i]();
    }

    callingPendingFunctors_ = false;
}

void EventLoop::quit() {
    quit_ = true;
    if (!isInLoopThread()) {
        wakeup();
    }
}
