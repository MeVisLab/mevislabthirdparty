cmake_minimum_required(VERSION 3.27)
project(test_package CXX)

find_package(VTK REQUIRED)

# create the test application
add_executable(test_package test_package.cpp)
target_link_libraries(test_package VTK::VTK)
