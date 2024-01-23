//
// Created by henrywen on 2024/1/23.
//

#include "CountDownLatch.h"

CountDownLatch::CountDownLatch(int count) : mutex(), condition(mutex), count(count) {}

void CountDownLatch::wait() {
    MutexLockGuard lock(mutex);
    while (count > 0) {
        condition.wait();
    }
}

void CountDownLatch::countDown() {
    MutexLockGuard lock(mutex);
    --count;
    if (count == 0) {
        condition.notifyAll();
    }
}
