//
// Created by henrywen on 2024/1/23.
//

#include "../base/Mutex.h"

#include <cstdio>

int main() {
    printf("sizeof pthread_mutex_t: %zd\n", sizeof(pthread_mutex_t));
    printf("sizeof Mutex: %zd\n", sizeof(MutexLock));
    printf("sizeof Mutex: %zd\n", sizeof(MutexGuard));
    MutexLock mutexLock;
    MutexGuard mutexGuard(mutexLock);
    return 0;
}
