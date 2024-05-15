cmake_minimum_required(VERSION 3.27)
project(test_package CXX)

find_package(stlab REQUIRED)

# enforce a current C++ standard without proprietary extensions.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(test_package test_package.cpp)
target_link_libraries(test_package stlab::stlab)

if (WIN32)
  target_compile_definitions(test_package PRIVATE
    -DNOMINMAX
    -D_SILENCE_CXX17_RESULT_OF_DEPRECATION_WARNING
  )
endif()
