cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(stack)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(ArrayStack)

add_subdirectory(LinkStack)