cmake_minimum_required(VERSION 3.31)
project(test_package CXX)

include(CTest)
enable_testing()

find_package(Qt6 REQUIRED COMPONENTS Widgets UiTools Help LinguistTools REQUIRED)
qt_standard_project_setup()

qt_add_executable(test_package test_package.cpp)
target_link_libraries(test_package PRIVATE Qt6::Widgets Qt6::UiTools Qt6::Help)
add_test(NAME tst_package COMMAND test_package)
add_test(NAME tst_lrelease COMMAND Qt6::lrelease -version)
add_test(NAME tst_lupdate COMMAND Qt6::lupdate -version)
