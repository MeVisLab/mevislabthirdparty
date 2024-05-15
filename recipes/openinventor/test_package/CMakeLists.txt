cmake_minimum_required(VERSION 3.27)
project(test_package CXX)

# enforce a current C++ standard without proprietary extensions.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenInventor REQUIRED)

add_executable(test_package test_package.cpp)

target_link_libraries(test_package OpenInventor::OpenInventor)

