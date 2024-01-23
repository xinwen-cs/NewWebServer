//
// Created by henrywen on 2024/1/23.
//

#ifndef TINYWEBSERVER_MUTEX_H
#define TINYWEBSERVER_MUTEX_H

#include <pthread.h>
#include "noncopyable.h"

class MutexLock : noncopyable {
public:
    MutexLock() {
        pthread_mutex_init(&mutex, nullptr);
    }

    ~MutexLock() {
        pthread_mutex_lock(&mutex);
        pthread_mutex_destroy(&mutex);
    }

    void lock() {
        pthread_mutex_lock(&mutex);
    }

    void unlock() {
        pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_t* get() {
        return &mutex;
    }

private:
    pthread_mutex_t mutex;

private:
    friend class Condition;
};

class MutexGuard : noncopyable {
public:
    explicit MutexGuard(MutexLock& mutex) : mutex(mutex) {
        mutex.lock();
    }

    ~MutexGuard() {
        mutex.unlock();
    }

private:
    MutexLock& mutex;
};

#endif //TINYWEBSERVER_MUTEX_H
