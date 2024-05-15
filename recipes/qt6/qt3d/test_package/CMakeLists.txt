cmake_minimum_required(VERSION 3.27)
project(test_package CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS 3DCore 3DRender 3DInput 3DLogic 3DExtras 3DAnimation REQUIRED)
qt_standard_project_setup()

qt_add_executable(test_package test_package.cpp)
target_link_libraries(test_package PRIVATE Qt6::3DCore Qt6::3DRender Qt6::3DLogic Qt6::3DExtras Qt6::3DAnimation)
add_test(NAME tst_package COMMAND test_package)
