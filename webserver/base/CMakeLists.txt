set(LIB_SRC
        noncopyable.h
        Thread.cpp Thread.h
        FileUtil.cpp FileUtil.h
        Mutex.h LogFile.cpp LogFile.h
        Condition.h
        CountDownLatch.cpp CountDownLatch.h
        CurrentThread.cpp CurrentThread.h
        AsyncLogging.cpp AsyncLogging.h
        FixedBuffer.h
        LogStream.cpp LogStream.h
        Logging.cpp Logging.h)

add_library(libserver_base ${LIB_SRC})
target_link_libraries(libserver_base pthread)

add_subdirectory(tests)
