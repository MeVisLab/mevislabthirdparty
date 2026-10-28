cmake_minimum_required(VERSION 3.31)
project(test_package LANGUAGES CXX)

find_package(Python3 REQUIRED)
find_package(PythonQt REQUIRED)
find_package(PythonBindingQt REQUIRED)
find_package(Qt6 COMPONENTS Core Network REQUIRED)

add_executable(test_package test_package.cpp)
target_link_libraries(test_package PRIVATE Qt6::Core PythonQt::PythonQt PythonBindingQt::PythonBindingQt)
