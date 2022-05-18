cmake_minimum_required(VERSION 3.14)
project(conan-wrapper)

set(UNUSED ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_subdirectory(sources/cmake)
