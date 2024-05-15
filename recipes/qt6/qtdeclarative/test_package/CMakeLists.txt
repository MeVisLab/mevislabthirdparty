cmake_minimum_required(VERSION 3.27)
project(test_package CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Qml QmlIntegration Quick QuickControls2 QuickTest REQUIRED)
qt_standard_project_setup()

qt_add_executable(test_package test_package.cpp)
target_link_libraries(test_package PRIVATE Qt6::Qml Qt6::QmlIntegration Qt6::Quick Qt6::QuickControls2 Qt6::QuickTest)
add_test(NAME tst_package COMMAND test_package)
