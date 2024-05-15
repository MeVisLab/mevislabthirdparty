cmake_minimum_required(VERSION 3.20)
project(test_package LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(SoQtMeVis REQUIRED)

add_executable(test_package test_package.cpp)
target_link_libraries(test_package SoQtMeVis::SoQtMeVis Qt6::Core)
