//
// Created by henrywen on 2024/1/23.
//

#ifndef TINYWEBSERVER_CURRENTTHREAD_H
#define TINYWEBSERVER_CURRENTTHREAD_H

#include <unistd.h>
#include <cstdio>
#include <sys/syscall.h>


namespace CurrentThread {
    extern __thread int t_cachedTid;
    extern __thread char t_tidString[32];
    extern __thread int t_tidStringLength;
    extern __thread const char* t_threadName;

    void cacheTid();

    inline int tid() {
        if (__builtin_expect(t_cachedTid == 0, 0)) {
            cacheTid();
        }
        return t_cachedTid;
    }
}

#endif //TINYWEBSERVER_CURRENTTHREAD_H
