cmake_minimum_required(VERSION 3.27)
project(test_package C)

find_package(libdeflate REQUIRED)

add_executable(test_package test_package.c)
target_link_libraries(test_package libdeflate::libdeflate_shared)
