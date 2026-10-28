cmake_minimum_required(VERSION 3.31)
project(test_package CXX)

find_package(VTK REQUIRED)

# create the test application
add_executable(test_package test_package.cpp)
target_link_libraries(test_package VTK::VTK)
target_compile_definitions(test_package PRIVATE WITH_RENDERING)

add_executable(test_package_no_renderer test_package.cpp)
target_link_libraries(test_package_no_renderer VTK::VTK)
