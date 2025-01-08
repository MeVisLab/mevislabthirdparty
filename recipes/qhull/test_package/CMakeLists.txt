cmake_minimum_required(VERSION 3.27)

project(test_package LANGUAGES CXX)

find_package(Qhull REQUIRED)

add_executable(test_package test_package.cpp)
target_link_libraries(test_package Qhull::Qhull)
