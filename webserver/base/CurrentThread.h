//
// Created by henrywen on 2024/1/23.
//

#ifndef TINYWEBSERVER_CURRENTTHREAD_H
#define TINYWEBSERVER_CURRENTTHREAD_H

#include <unistd.h>
#include <cstdio>
#include <sys/syscall.h>


namespace CurrentThread {
    __thread int t_cachedTid = 0;
    __thread char t_tidString[32];
    __thread int t_tidStringLength = 6;
    __thread const char* t_threadName = "default";

    pid_t gettid() {
        return static_cast<pid_t>(::syscall(SYS_gettid));
    }

    void cacheTid() {
        if (t_cachedTid == 0) {
            t_cachedTid = gettid();
            t_tidStringLength =
                    snprintf(t_tidString, sizeof t_tidString, "%5d ", t_cachedTid);
        }
    }

    inline int tid() {
        if (__builtin_expect(t_cachedTid == 0, 0)) {
            cacheTid();
        }
        return t_cachedTid;
    }
}

#endif //TINYWEBSERVER_CURRENTTHREAD_H
