cmake_minimum_required(VERSION 3.31)
project(test_package LANGUAGES CXX)

find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(SoQtMeVis REQUIRED)

add_executable(test_package test_package.cpp)
target_link_libraries(test_package SoQtMeVis::SoQtMeVis Qt6::Core)
