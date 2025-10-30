cmake_minimum_required(VERSION 3.27)

project(test_package LANGUAGES CXX)

find_package(DCMTK REQUIRED)

add_executable(test_package test_package.cpp)
target_link_libraries(test_package PRIVATE DCMTK::DCMTK)

if(MSVC)
    target_compile_options(test_package PUBLIC "/Zc:__cplusplus")
endif()
