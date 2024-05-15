cmake_minimum_required(VERSION 3.27)
project(test_package LANGUAGES C)

find_package(LZ4 REQUIRED)

add_executable(test_package test_package.c)
target_link_libraries(test_package lz4::lz4)

set(_result_vars
    LZ4_INCLUDE_DIR
    LZ4_INCLUDE_DIRS
    LZ4_LIBRARY
    LZ4_LIBRARIES
    LZ4_FOUND
)

foreach(_var ${_result_vars})
  if(DEFINED ${_var})
    message(STATUS "${_var}: ${${_var}}")
  else()
    message(FATAL_ERROR "${_var} not defined")
  endif()
endforeach()
