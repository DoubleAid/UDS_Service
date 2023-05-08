project(UDS)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-std=c++14 -mavx2 -mno-avx512f -pipe -O2 -Wall -Wextra -fopenmp -fPIC -pthread")

set(PROJECT_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/..)

include_directories(${PROJECT_INCLUDE_DIRS})

add_library(uds
		doip/doip.cpp
		)

add_executable(server
		server.cpp
		)

add_executable(client
		client.cpp
		)

target_link_libraries(client

)