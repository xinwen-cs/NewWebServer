//
// Created by root on 24-1-26.
//

#include "Channel.h"

Channel::Channel(EventLoop *loop)
        : loop(loop), fd(0), events_(0), lastEvents_(0) {}

Channel::Channel(EventLoop *loop, int fd)
        : loop(loop), fd(fd), events_(0), lastEvents_(0) {}

int Channel::getFd() {
    return fd;
}

void Channel::setFd(int fd) {
    this->fd = fd;
}

void Channel::handleRead() {
    if (readHandler) {
        readHandler();
    }
}

void Channel::handleWrite() {
    if (writeHandler) {
        writeHandler();
    }
}

void Channel::handleConn() {
    if (connHandler) {
        connHandler();
    }
}
