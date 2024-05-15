cmake_minimum_required(VERSION 3.27)
project(test_package LANGUAGES C)

find_package(ZLIB REQUIRED)

add_executable(test_package test_package.c)
target_link_libraries(test_package PRIVATE ZLIB::ZLIB)

# https://cmake.org/cmake/help/latest/module/FindZLIB.html
set(_result_vars
    ZLIB_INCLUDE_DIRS
    ZLIB_LIBRARIES
    ZLIB_LIBRARY
    ZLIB_FOUND
    ZLIB_VERSION

    # legacy
    ZLIB_VERSION_MAJOR
    ZLIB_VERSION_MINOR
    ZLIB_VERSION_PATCH
    ZLIB_VERSION_TWEAK
    ZLIB_VERSION_STRING
    ZLIB_MAJOR_VERSION
    ZLIB_MINOR_VERSION
    ZLIB_PATCH_VERSION
)

foreach(_var ${_result_vars})
  if(DEFINED ${_var})
    message(STATUS "${_var}: ${${_var}}")
  else()
    message(FATAL_ERROR "${_var} not defined")
  endif()
endforeach()
