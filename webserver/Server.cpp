//
// Created by root on 24-1-27.
//

#include "Server.h"
#include "Util.h"
#include "base/Logging.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "HttpData.h"


Server::Server(EventLoop *loop, int threadNum, int port)
        : loop_(loop),
          threadNum_(threadNum),
          eventLoopThreadPool_(new EventLoopThreadPool(loop_, threadNum)),
          started_(false),
          port_(port),
          listenFd_(socket_bind_listen(port_)),
          acceptChannel_(new Channel(listenFd_)) {
    handle_for_sigpipe();
    if (setSocketNonBlocking(listenFd_) < 0) {
        perror("set socket non block failed");
        abort();
    }
}


void Server::start() {
    eventLoopThreadPool_->start();
    acceptChannel_->setEvents(EPOLLIN | EPOLLET);
    acceptChannel_->setReadHandler(std::bind(&Server::handNewConn, this));
    acceptChannel_->setConnHandler(std::bind(&Server::handThisConn, this));
    loop_->addToPoller(acceptChannel_, 0);
    started_ = true;
}

void Server::handThisConn() {
    loop_->updatePoller(acceptChannel_);
}

void Server::handNewConn() {
    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    socklen_t client_addr_len = sizeof(client_addr);

    int accept_fd = 0;

    while ((accept_fd = accept(listenFd_, (struct sockaddr *) &client_addr, &client_addr_len)) > 0) {
        LOG << "New connection from " << inet_ntoa(client_addr.sin_addr) << ": " << ntohs(client_addr.sin_port);

        if (accept_fd >= MAXFDS) {
            close(accept_fd);
            continue;
        }

        if (setSocketNonBlocking(accept_fd) < 0) {
            LOG << "Set non block failed!";
            return;
        }

        setSocketNoDelay(accept_fd);

        EventLoop* loop = eventLoopThreadPool_->getNextLoop();

        std::shared_ptr<HttpData> req_info(new HttpData(loop, accept_fd));
        req_info->getChannel()->setHolder(req_info);
        loop->queueInLoop(std::bind(&HttpData::newEvent, req_info));
    }
    acceptChannel_->setEvents(EPOLLIN | EPOLLET);
}
