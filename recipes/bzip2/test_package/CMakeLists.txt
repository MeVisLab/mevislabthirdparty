cmake_minimum_required(VERSION 3.27)
project(test_package LANGUAGES C)

find_package(BZip2 REQUIRED)

add_executable(test_package test_package.c)
target_link_libraries(test_package PRIVATE BZip2::BZip2)

# Test whether variables from https://cmake.org/cmake/help/latest/module/FindBZip2.html are properly defined
set(vars
    BZIP2_FOUND
    BZIP2_INCLUDE_DIRS
    BZIP2_LIBRARIES
    BZIP2_NEED_PREFIX
    BZIP2_VERSION
    BZIP2_INCLUDE_DIR
    BZIP2_VERSION_STRING
)

foreach(var ${vars})
    if(DEFINED ${var})
        message(STATUS "${var}: ${${var}}")
    else()
        message(FATAL_ERROR "${var} not defined")
    endif()
endforeach()
