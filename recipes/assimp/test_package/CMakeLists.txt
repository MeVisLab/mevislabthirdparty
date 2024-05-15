cmake_minimum_required(VERSION 3.27)
project(test_package LANGUAGES C CXX)

find_package(assimp REQUIRED)

add_executable(test_package test_package.cpp)
target_link_libraries(test_package PRIVATE assimp::assimp)

add_executable(test_package_c test_package.c)
target_link_libraries(test_package_c PRIVATE assimp::assimp)
