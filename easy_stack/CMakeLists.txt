cmake_minimum_required(VERSION 2.8.3)
project(Task)
set(CMAKE_BUILD_TYPE "debug")

include_directories(
    ./include
)

aux_source_directory(
    ./src SRC
)

add_executable(Task test.c
    ${SRC}
)