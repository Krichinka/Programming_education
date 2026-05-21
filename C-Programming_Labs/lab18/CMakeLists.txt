cmake_minimum_required(VERSION 3.10)

project(lab18 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

enable_testing()

add_library(task5 src/task5.c)

add_executable(task5_test tests/task5_test.c)

target_link_libraries(task5_test task5 cmocka)

add_test(NAME Task5UnitTests COMMAND task5_test)