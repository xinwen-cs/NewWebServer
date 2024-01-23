//
// Created by henrywen on 2024/1/23.
//

#include "../base/Thread.h"

#include <iostream>

int main() {
    Thread thread(nullptr, "");
    Thread thread1(nullptr, "");
    Thread thread2(nullptr, "");

    thread.start();
    thread1.start();
    thread2.start();

    std::cout << thread.name() << "\n";
    std::cout << thread.tid() << "\n";

    std::cout << thread1.name() << "\n";
    std::cout << thread1.tid() << "\n";

    std::cout << thread2.name() << "\n";
    std::cout << thread2.tid() << "\n";

    thread.join();
    thread1.join();
    thread2.join();
}