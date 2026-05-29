cmake_minimum_required(VERSION 3.10)

project(brainfuck_interpreter C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)

add_library(brainfuck_core
    src/brainfuck.c
    src/config.c
    src/logger.c
)

add_executable(brainfuck
    src/main.c
)

target_link_libraries(brainfuck brainfuck_core)

enable_testing()

add_executable(test_brainfuck
    tests/test_brainfuck.c
)

target_link_libraries(test_brainfuck brainfuck_core cmocka)

add_test(NAME BrainfuckUnitTests COMMAND test_brainfuck)