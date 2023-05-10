project(UDS)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-std=c++14 -mavx2 -mno-avx512f -pipe -O2 -Wall -Wextra -fopenmp -fPIC -pthread")

set(PROJECT_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/..)

#add_definitions(-DTEST_RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/conf/")

include_directories(${PROJECT_INCLUDE_DIRS})

#catkin_package(INCLUDE_DIRS ${PROJECT_INCLUDE_DIRS}
#		LIBRARIES
#		map_common
#		map_hdmap
#		map_client_v1
#		router_v2
#		map_core
#		map_refline
#		map_refline_v2
#		map_processor
#		map_view
#		)

#link_directories(${CATKIN_DEVEL_PREFIX}/lib)

#enable_testing()
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})

#add_library(uds
#		doip/doip.cpp
#		)
#
#add_executable(server
#		server/server.cpp
#		)
#
#add_executable(client
#		client/client.cpp
#		)
#
#target_link_libraries(client
#
#)

#install(DIRECTORY ${PROJECT_INCLUDE_DIRS}
#		DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#		FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
#)

add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(client)