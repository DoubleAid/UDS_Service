cmake_minimum_required(VERSION 3.5)
project(uds_server)

set(TARGET_PLATFORM "x86" CACHE STRING "Target platform (x86, aarch64)")

if (TARGET_PLATFORM STREQUAL "x86")
    message("---- build for x86 ----")
    set(CMAKE_CXX_COMPILE g++)
    set(CMAKE_C_COMPILE gcc)
    set(CMAKE_CXX_FLAGS "-std=c++20 -mavx2 -mno-avx512f -pipe -O2 -Wall -Wextra -fopenmp -fPIC -pthread")
elseif (TARGET_PLATFORM STREQUAL "aarch64")
    message("---- build for x86 ----")
    set(CMAKE_CXX_COMPILE aarch64-linux-gnu-g++)
    set(CMAKE_C_COMPILE aarch64-linux-gnu-gcc)
    set(CMAKE_CXX_FLAGS "-std=c++20 -pipe -O2 -Wall -Wextra -fopenmp -fPIC -pthread")
    set(CMAKE_EXE_LINKER_FLAGS "-static")
else()
    message(FATAL_ERROR "Unknown target platform: ${TARGET_PLATFORM}")
endif ()

set(PROJECT_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR}/..)

include_directories(${PROJECT_INCLUDE_DIRS})

add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(client)