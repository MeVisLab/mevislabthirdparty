cmake_minimum_required(VERSION 3.27)
project(test_package CXX)

find_package(vigra REQUIRED)

add_executable(test_package test_package.cpp)
target_link_libraries(test_package vigra::vigra)
