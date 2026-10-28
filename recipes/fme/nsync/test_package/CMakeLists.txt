cmake_minimum_required(VERSION 3.31)
project(test_package LANGUAGES C CXX)

find_package(nsync REQUIRED CONFIG)

add_executable(test_package test_package.c)
target_link_libraries(test_package nsync::nsync_c)

add_executable(test_package_cpp test_package.cpp)
target_link_libraries(test_package_cpp nsync::nsync_cpp)
