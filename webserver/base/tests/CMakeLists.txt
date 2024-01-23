include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

add_executable(fileutil_test FileUtil_test.cpp)
target_link_libraries(fileutil_test libserver_base)

add_executable(mutex_test mutex_test.cpp)
target_link_libraries(mutex_test libserver_base)

add_executable(logfile_test LogFile_test.cpp)
target_link_libraries(logfile_test libserver_base)

add_executable(thread_test Thread_test.cpp)
target_link_libraries(thread_test libserver_base)

add_executable(logging_test logging_test.cpp)
target_link_libraries(logging_test libserver_base)
