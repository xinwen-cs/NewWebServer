//
// Created by root on 24-1-27.
//

#ifndef TINYWEBSERVER_SERVER_H
#define TINYWEBSERVER_SERVER_H

#include "EventLoopThreadPool.h"

class Server {
public:
    Server(EventLoop* loop, int threadNum, int port);
    ~Server() = default;

    EventLoop* getLoop() const {
        return loop_;
    }

    void start();
    void handNewConn();
    void handThisConn();

private:
    EventLoop* loop_;
    int threadNum_;

    std::unique_ptr<EventLoopThreadPool> eventLoopThreadPool_;

    bool started_;

    std::shared_ptr<Channel> acceptChannel_;

    int port_;
    int listenFd_;

    static const int MAXFDS = 100000;
};


#endif //TINYWEBSERVER_SERVER_H
