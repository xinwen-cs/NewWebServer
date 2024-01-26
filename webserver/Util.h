//
// Created by root on 24-1-26.
//

#ifndef TINYWEBSERVER_UTIL_H
#define TINYWEBSERVER_UTIL_H

#include <cstdlib>
#include <string>


ssize_t readn(int fd, void *buff, size_t n);
ssize_t readn(int fd, std::string &inBuffer, bool &zero);

ssize_t writen(int fd, void *buff, size_t n);
ssize_t writen(int fd, std::string &sbuff);

void setSocketNoDelay(int fd);
int setSocketNonBlocking(int fd);

void handle_for_sigpipe();

int socket_bind_listen(int port);
void shutDownWR(int fd);


#endif //TINYWEBSERVER_UTIL_H
