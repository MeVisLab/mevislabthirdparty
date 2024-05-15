cmake_minimum_required(VERSION 3.27)
project(test_package LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(FLANN REQUIRED)

add_executable(test_package test_package.cpp)
target_link_libraries(test_package PRIVATE FLANN::FLANN)
