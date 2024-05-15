cmake_minimum_required(VERSION 3.27)
project(test_package LANGUAGES CXX)

find_package(Iconv REQUIRED)

add_executable(test_package test_package.cpp)
target_link_libraries(test_package PRIVATE Iconv::Iconv)

# Test whether variables from https://cmake.org/cmake/help/latest/module/FindIconv.html
# are properly defined in conan generators
set(_vars
    Iconv_FOUND
    Iconv_INCLUDE_DIRS
    Iconv_LIBRARIES
    Iconv_VERSION
    Iconv_VERSION_MAJOR
    Iconv_VERSION_MINOR
    Iconv_IS_BUILT_IN

    LIBICONV_FOUND
    LIBICONV_INCLUDE_DIR
    LIBICONV_INCLUDE_DIRS
    LIBICONV_LIBRARY
    LIBICONV_LIBRARIES

    LIBCHARSET_FOUND
    LIBCHARSET_INCLUDE_DIR
    LIBCHARSET_INCLUDE_DIRS
    LIBCHARSET_LIBRARY
    LIBCHARSET_LIBRARIES
)

foreach(var ${_vars})
    if(DEFINED ${var})
        message(STATUS "${var}: ${${var}}")
    else()
        message(FATAL_ERROR "${var} not defined")
    endif()
endforeach()
