//
// Created by henrywen on 2024/1/23.
//

#ifndef TINYWEBSERVER_EPOLL_H
#define TINYWEBSERVER_EPOLL_H

#include <vector>
#include <memory>

#include "Channel.h"
#include "Timer.h"


class Epoll {
public:
    Epoll();
    ~Epoll() = default;

    void epoll_add(shared_channel_ptr request, int timeout);
    void epoll_mod(shared_channel_ptr request, int timeout);
    void epoll_del(shared_channel_ptr);

    std::vector<std::shared_ptr<Channel>> poll();
    std::vector<std::shared_ptr<Channel>> getEventsRequest(int events_num);

    void handleExpired();
    void add_timer(std::shared_ptr<Channel> request_data, int timeout);

private:
    static const int MAXFDS = 100000;

    int epollFd_;
    std::vector<epoll_event> events_;
    std::shared_ptr<Channel> fd2chan_[MAXFDS];
    std::shared_ptr<HttpData> fd2http_[MAXFDS];
    TimerManager timerManager_;
};


#endif //TINYWEBSERVER_EPOLL_H
