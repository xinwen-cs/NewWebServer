#include <iostream>

#include "EventLoop.h"

int main() {
    EventLoop* loop = new EventLoop();
    loop->loop();
    return 0;
}
