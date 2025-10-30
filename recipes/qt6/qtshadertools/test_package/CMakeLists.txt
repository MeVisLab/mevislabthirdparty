cmake_minimum_required(VERSION 3.27)
project(test_package CXX)

include(CTest)
enable_testing()

find_package(Qt6 REQUIRED COMPONENTS ShaderTools REQUIRED)
qt_standard_project_setup()

qt_add_executable(test_package test_package.cpp)
qt6_add_shaders(test_package "test_package" PREFIX "/" FILES "wobble.frag")
target_link_libraries(test_package PRIVATE Qt6::ShaderTools)
add_test(NAME tst_package COMMAND test_package)
