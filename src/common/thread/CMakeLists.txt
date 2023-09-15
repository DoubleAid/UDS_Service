add_library(common_thread
    thread_pool.cpp
    threadsafe_queue.h
)

add_executable(thread_test thread_test_main.cpp)

target_link_libraries(thread_test
    common_thread
)