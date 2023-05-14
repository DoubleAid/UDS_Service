project(UDS)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-std=c++14 -mavx2 -mno-avx512f -pipe -O2 -Wall -Wextra -fopenmp -fPIC -pthread")
set(CMAKE_PREFIX_PATH "/usr/.local")
set(PROJECT_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_BINARY_DIR}/..)

#add_definitions(-DTEST_RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/conf/")

include_directories(${PROJECT_INCLUDE_DIRS})

# list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})

find_package(Threads)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindProtobuf.cmake)
# FILE(GLOB_RECURSE PROTOS_ALL ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR}/common/proto/.. *.proto)
# protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTOS_ALL})

# include_directories(${CMAKE_CURRENT_BINARY_DIR})

# add_executable(main main.cpp
#     ${PROTO_SRCS}
# )

# target_link_libraries(main
# 		common_thread
# 		common_proto
#         ${PROTO_HDRS}
# 		${PROTOBUF_LIBRARIES}
# 		protobuf::libprotobuf
# )

add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(client)