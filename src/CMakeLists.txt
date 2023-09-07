cmake_minimum_required(VERSION 3.5)
project(uds_server)

set(CMAKE_CXX_FLAGS "-std=c++14 -mavx2 -mno-avx512f -pipe -O2 -Wall -Wextra -fopenmp -fPIC -pthread")

set(PROJECT_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR}/..)

include_directories(${PROJECT_INCLUDE_DIRS})

add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(client)