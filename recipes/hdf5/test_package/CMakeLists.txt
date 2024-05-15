cmake_minimum_required(VERSION 3.27)
project(test_package)

find_package(HDF5 REQUIRED)
add_executable(test_package test_package.cpp)
target_link_libraries(test_package PRIVATE HDF5::HDF5)
