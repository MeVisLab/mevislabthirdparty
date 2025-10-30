cmake_minimum_required(VERSION 3.27)
project(test_package CXX)

include(CTest)
enable_testing()

find_package(Qt6 REQUIRED COMPONENTS Positioning REQUIRED)
qt_standard_project_setup()

qt_add_executable(test_package test_package.cpp)
target_link_libraries(test_package PRIVATE Qt6::Positioning)
add_test(NAME tst_package COMMAND test_package)
