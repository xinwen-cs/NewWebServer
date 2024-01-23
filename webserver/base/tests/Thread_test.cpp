//
// Created by henrywen on 2024/1/23.
//

#include "../base/Thread.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <memory>

void func() {
    std::cout << "hello world\n";
}

int main() {
    Thread thread0(func, "");
    Thread thread1(func, "");
    Thread thread2(func, "");

    std::cout << thread0.started() << "\n";
    std::cout << thread1.started() << "\n";
    std::cout << thread2.started() << "\n";

    thread0.start();
    thread1.start();
    thread2.start();

    std::cout << thread0.name() << "\n";
    std::cout << thread0.tid() << "\n";
    std::cout << thread0.started() << "\n";

    std::cout << thread1.name() << "\n";
    std::cout << thread1.tid() << "\n";
    std::cout << thread1.started() << "\n";

    std::cout << thread2.name() << "\n";
    std::cout << thread2.tid() << "\n";
    std::cout << thread2.started() << "\n";

    thread0.join();
    thread1.join();
    thread2.join();

    std::vector<std::unique_ptr<Thread>> threads;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10; ++i) {
        threads.push_back(std::make_unique<Thread>(func, ""));
    }
    auto end = std::chrono::high_resolution_clock::now();

    // 计算耗时
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // 输出结果
    std::cout << "Function took " << duration.count() << " milliseconds to complete." << std::endl;

    for (auto& thread : threads) {
        thread->start();
        std::cout << thread->tid() << "\n";
        std::cout << thread->name() << "\n";
    }

    for (auto& thread : threads) {
        thread->join();
    }
}