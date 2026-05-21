cmake_minimum_required(VERSION 3.10)

project(cmake_smartphones)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

option(BUILD_SHARED_LIBS  "DYNAMIC" OFF)

# #define TEST_DEF 5
add_definitions(-DTEST_DEF=5)
set(SOURCES ${SOURCE_DIR}/smartphones.c)
add_library(UTIL_LIB STATIC ${SOURCES})

add_executable(main src/main.c)
target_link_libraries(main UTIL_LIB m)
