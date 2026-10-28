cmake_minimum_required(VERSION 3.31)
project(test_package)

find_package(HDF5 REQUIRED)
add_executable(test_package test_package.cpp)
target_link_libraries(test_package PRIVATE hdf5::hdf5 hdf5::hdf5_cpp hdf5::hdf5_hl)
