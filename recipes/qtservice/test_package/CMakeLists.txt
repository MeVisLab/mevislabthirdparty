cmake_minimum_required(VERSION 3.27)
project(test_package LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core REQUIRED)
qt_standard_project_setup()

find_package(QtService REQUIRED)

qt_add_executable(test_package test_package.cpp)
target_link_libraries(test_package PRIVATE Qt6::Core QtService::QtService)

add_test(NAME test_package COMMAND test_package)
