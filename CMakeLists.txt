cmake_minimum_required(VERSION 3.20)
project(tinywebserver)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CMAKE_CXX_STANDARD 17)

set(CXX_FLAGS
        -g
        -Wall
        -std=c++11
        -D_PTHREADS
        )

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    # Linux-specific includes or actions
    add_definitions(-DLINUX)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    # macOS-specific includes or actions
    add_definitions(-DMACOS)
endif()

add_subdirectory(webserver)

