//
// Created by root on 24-1-26.
//

#include "Channel.h"


Channel::Channel(int fd)
        : fd(fd), events_(0), lastEvents_(0) {}

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
