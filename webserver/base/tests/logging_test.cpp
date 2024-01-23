//
// Created by root on 24-1-23.
//

#include "../base/Logging.h"
#include "../base/Thread.h"

#include <unistd.h>
#include <iostream>
#include <memory>

void threadFunc() {
    for (int i = 0; i < 100000; ++i) {
        LOG << i;
    }
}

void typeTest() {
    std::cout << "----------type test-----------" << std::endl;
    LOG << 0;
    LOG << 1234567890123;
    LOG << 1.0f;
    LOG << 3.1415926;
    LOG << (short) 1;
    LOG << (long long) 1;
    LOG << (unsigned int) 1;
    LOG << (unsigned long) 1;
    LOG << (long double) 1.6555556;
    LOG << (unsigned long long) 1;
    LOG << 'c';
    LOG << "abcdefg";
    LOG << std::string("This is a string");
}

void stressing_single_thread() {
    // 100000 lines
    std::cout << "----------stressing test single thread-----------" << std::endl;
    for (int i = 0; i < 100000; ++i) {
        LOG << i;
    }
}

void other()
{
    // 1 line
    std::cout << "----------other test-----------" << std::endl;
    LOG << "fddsa" << 'c' << 0 << 3.666 << std::string("This is a string");
}


void stressing_multi_threads(int threadNum = 4) {
    // threadNum * 100000 lines
    std::cout << "----------stressing test multi thread-----------" << std::endl;
    std::vector<std::shared_ptr<Thread>> vsp;
    for (int i = 0; i < threadNum; ++i) {
        vsp.push_back(std::make_shared<Thread>(threadFunc, "testFunc"));
    }
    for (int i = 0; i < threadNum; ++i)
    {
        vsp[i]->start();
    }
    sleep(3);
}

int main() {
//     共500014行
    typeTest();
    sleep(3);

    stressing_single_thread();
    sleep(3);

    other();
    sleep(3);

    stressing_multi_threads();
    sleep(3);
    return 0;
}
