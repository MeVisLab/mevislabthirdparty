cmake_minimum_required(VERSION 3.27)
project(test_package LANGUAGES C)

find_package(LibLZMA REQUIRED)

add_executable(test_package test_package.c)
target_link_libraries(test_package PRIVATE LibLZMA::LibLZMA)

# Test whether variables from https://cmake.org/cmake/help/latest/module/FindLibLZMA.html
# are properly defined in conan generators
set(_vars
    LIBLZMA_FOUND
    LIBLZMA_INCLUDE_DIRS
    LIBLZMA_LIBRARIES
    # LIBLZMA_HAS_AUTO_DECODER
    # LIBLZMA_HAS_EASY_ENCODER
    # LIBLZMA_HAS_LZMA_PRESET
    LIBLZMA_VERSION
    LIBLZMA_VERSION_MAJOR
    LIBLZMA_VERSION_MINOR
    LIBLZMA_VERSION_PATCH
    LIBLZMA_VERSION_STRING
)

foreach(var ${_vars})
    if(DEFINED ${var})
        message(STATUS "${var}: ${${var}}")
    else()
        message(FATAL_ERROR "${var} not defined")
    endif()
endforeach()
