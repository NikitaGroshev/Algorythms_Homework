cmake_minimum_required(VERSION 3.20)

project(seminar LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic)

set(TARGET "Homework_3")

add_executable(
    ${TARGET}
    src/task2.cpp
)