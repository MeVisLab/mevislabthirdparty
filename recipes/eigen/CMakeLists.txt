cmake_minimum_required(VERSION 3.14)
project(conan-wrapper)

include(${CMAKE_BINARY_DIR}/../conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(sources)
