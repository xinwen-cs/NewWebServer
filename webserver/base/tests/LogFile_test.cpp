//
// Created by henrywen on 2024/1/23.
//
#include "../base/LogFile.h"

#include <string>

int main() {
    std::string hello("hello\n");
    LogFile* logFile = new LogFile("/tmp/logfile", 1000);
    for (int i = 0; i < 100000; ++i) {
        logFile->append(hello.c_str(), hello.size());
    }
    return 0;
}
