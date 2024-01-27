//
// Created by root on 24-1-26.
//

#ifndef TINYWEBSERVER_CHANNEL_H
#define TINYWEBSERVER_CHANNEL_H

#include <sys/epoll.h>
#include <memory>
#include <functional>

class EventLoop;
class HttpData;

class Channel {
    using Callback = std::function<void()>;

public:
    explicit Channel(EventLoop* loop);
    Channel(EventLoop* loop, int fd);

    ~Channel() = default;

    int getFd();
    void setFd(int fd);

    void setHolder(std::shared_ptr<HttpData> holder) {
        this->holder = holder;
    }

    std::shared_ptr<HttpData> getHolder() {
        return std::shared_ptr<HttpData>(holder.lock());
    }

    void setReadHandler(Callback&& readHandler) {
        this->readHandler = readHandler;
    }

    void setWriteHandler(Callback&& writeHandler) {
        this->writeHandler = writeHandler;
    }

    void setConnHandler(Callback&& connHandler) {
        this->connHandler = connHandler;
    }

    void handleRead();
    void handleWrite();
    void handleConn();

    void handleEvents() {
        events_ = 0;

        if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN)) {
            events_ = 0;
            return;
        }

        if (revents_ & EPOLLERR) {
            if (errorHandler) {
                errorHandler();
            }
            events_ = 0;
            return;
        }

        if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)) {
            handleRead();
        }

        if (revents_ & EPOLLOUT) {
            handleWrite();
        }

        handleConn();
    }

    void setRevents(__uint32_t ev) { revents_ = ev; }

    void setEvents(__uint32_t ev) { events_ = ev; }
    __uint32_t &getEvents() { return events_; }

    bool EqualAndUpdateLastEvents() {
        bool ret = (lastEvents_ == events_);
        lastEvents_ = events_;
        return ret;
    }

    __uint32_t getLastEvents() { return lastEvents_; }

private:
    Callback readHandler;
    Callback writeHandler;
    Callback errorHandler;
    Callback connHandler;

    // FIXME
    EventLoop* loop;

    int fd;

    __uint32_t events_;
    __uint32_t revents_;
    __uint32_t lastEvents_;

    std::weak_ptr<HttpData> holder;
};

using shared_channel_ptr = std::shared_ptr<Channel>;

#endif //TINYWEBSERVER_CHANNEL_H
