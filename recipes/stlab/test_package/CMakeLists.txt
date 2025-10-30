cmake_minimum_required(VERSION 3.27)
project(test_package CXX)

find_package(stlab REQUIRED)

add_executable(test_package test_package.cpp)
target_link_libraries(test_package stlab::stlab)

if(MSVC)
    target_compile_options(test_package PUBLIC "/Zc:__cplusplus")
endif()

if (WIN32)
  target_compile_definitions(test_package PRIVATE
    -DNOMINMAX
    -D_SILENCE_CXX17_RESULT_OF_DEPRECATION_WARNING
  )
endif()
