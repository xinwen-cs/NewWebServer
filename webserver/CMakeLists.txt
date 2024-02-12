set(SRCS
        main.cpp
        Epoll.cpp Epoll.h
        Util.cpp Util.h
        Channel.cpp Channel.h
        EventLoop.cpp EventLoop.h
        EventLoopThread.cpp EventLoopThread.h
        EventLoopThreadPool.cpp EventLoopThreadPool.h
        Server.cpp Server.h
        HttpData.cpp HttpData.h
        Timer.cpp Timer.h)
include_directories(${PROJECT_SOURCE_DIR}/base)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
endif()

add_executable(tinywebserver ${SRCS})
target_link_libraries(tinywebserver libserver_base)

add_subdirectory(base)

