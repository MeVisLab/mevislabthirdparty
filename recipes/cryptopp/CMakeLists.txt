cmake_minimum_required(VERSION 3.14)
project(conan-wrapper)

set(_unused ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY} ${CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(sources)
