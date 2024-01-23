//
// Created by henrywen on 2024/1/23.
//

#ifndef TINYWEBSERVER_COUNTDOWNLATCH_H
#define TINYWEBSERVER_COUNTDOWNLATCH_H

#include "noncopyable.h"
#include "Mutex.h"
#include "Condition.h"

class CountDownLatch : noncopyable {
public:
    explicit CountDownLatch(int count);
    void wait();
    void countDown();

private:
    mutable MutexLock mutex;
    Condition condition;
    int count;
};


#endif //TINYWEBSERVER_COUNTDOWNLATCH_H
