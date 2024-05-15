cmake_minimum_required(VERSION 3.27)
project(test_package LANGUAGES CXX)

enable_testing()

find_package(Python3 REQUIRED)
find_package(PythonQt REQUIRED)
find_package(Qt6 COMPONENTS Core Network REQUIRED)

add_executable(test_package test_package.cpp)
target_link_libraries(test_package PRIVATE Qt6::Core PythonQt::PythonQt)

add_test(NAME test_package COMMAND test_package)
