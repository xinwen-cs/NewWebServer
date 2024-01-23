//
// Created by henrywen on 2024/1/23.
//

#ifndef TINYWEBSERVER_CONDITION_H
#define TINYWEBSERVER_CONDITION_H

#include "noncopyable.h"
#include "Mutex.h"

#include <cerrno>


class Condition : noncopyable {
public:
    explicit Condition(MutexLock& mutex) : mutex(mutex) {
        pthread_cond_init(&cond, nullptr);
    }

    ~Condition() {
        pthread_cond_destroy(&cond);
    }

    void wait() {
        pthread_cond_wait(&cond, mutex.get());
    }

    void notify() {
        pthread_cond_signal(&cond);
    }

    void notifyAll() {
        pthread_cond_broadcast(&cond);
    }

    bool waitForSecond(int seconds) {
        struct timespec abstime;
        clock_gettime(CLOCK_REALTIME, &abstime);
        abstime.tv_sec += static_cast<time_t>(seconds);
        return ETIMEDOUT == pthread_cond_timedwait(&cond, mutex.get(), &abstime);
    }

private:
    MutexLock& mutex;
    pthread_cond_t cond;
};

#endif //TINYWEBSERVER_CONDITION_H
