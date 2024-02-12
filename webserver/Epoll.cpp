//
// Created by henrywen on 2024/1/23.
//

#include "Epoll.h"

#include <sys/epoll.h>
#include <cassert>

#include "base/Logging.h"

const int EVENTSNUM = 4096;
const int EPOLLWAIT_TIME = 10000;

Epoll::Epoll() : epollFd_(epoll_create1(EPOLL_CLOEXEC)), events_(EVENTSNUM) {
    assert(epollFd_ > 0);
}

void Epoll::epoll_add(shared_channel_ptr request, int timeout) {
    int fd = request->getFd();

    if (timeout > 0) {
        add_timer(request, timeout);
        fd2http_[fd] = request->getHolder();
    }

    struct epoll_event event;
    event.data.fd = fd;
    event.events = request->getEvents();

    request->EqualAndUpdateLastEvents();

    fd2chan_[fd] = request;

    if (epoll_ctl(epollFd_, EPOLL_CTL_ADD, fd, &event) < 0) {
        perror("epoll_add error");
        fd2chan_[fd].reset();
    }
}

void Epoll::epoll_mod(shared_channel_ptr request, int timeout) {
    int fd = request->getFd();

    if (timeout > 0) {
        add_timer(request, timeout);
    }

    if (!request->EqualAndUpdateLastEvents()) {
        struct epoll_event event;
        event.data.fd = fd;
        event.events = request->getEvents();
        if (epoll_ctl(epollFd_, EPOLL_CTL_MOD, fd, &event) < 0) {
            perror("epoll_mod error");
            fd2chan_[fd].reset();
        }
    }
}

void Epoll::epoll_del(shared_channel_ptr request) {
    int fd = request->getFd();
    struct epoll_event event;
    event.data.fd = fd;
    event.events = request->getLastEvents();

    if (epoll_ctl(epollFd_, EPOLL_CTL_DEL, fd, &event) < 0) {
        perror("epoll_del error");
    }
    fd2chan_[fd].reset();
    fd2http_[fd].reset();
}

void Epoll::handleExpired() {
    timerManager_.handleExpiredEvent();
}

std::vector<shared_channel_ptr> Epoll::poll() {
    while (true) {
        int event_count =
                epoll_wait(epollFd_, &*events_.begin(), events_.size(), EPOLLWAIT_TIME);
        if (event_count < 0) {
            perror("epoll wait error");
        }
        std::vector<shared_channel_ptr> req_data = getEventsRequest(event_count);
        if (!req_data.empty()) {
            return req_data;
        }
    }
}

std::vector<shared_channel_ptr> Epoll::getEventsRequest(int events_num) {
    std::vector<shared_channel_ptr> req_data;
    for (int i = 0; i < events_num; ++i) {
        int fd = events_[i].data.fd;

        shared_channel_ptr cur_req = fd2chan_[fd];

        if (cur_req) {
            cur_req->setRevents(events_[i].events);
            cur_req->setEvents(0);
            req_data.push_back(cur_req);
        } else {
            LOG << "Channel cur_req is invalid";
        }
    }
    return req_data;
}

void Epoll::add_timer(shared_channel_ptr request_data, int timeout) {
    std::shared_ptr<HttpData> t = request_data->getHolder();
    if (t) {
        timerManager_.addTimer(t, timeout);
    } else {
        LOG << "Add timer fail";
    }
}
