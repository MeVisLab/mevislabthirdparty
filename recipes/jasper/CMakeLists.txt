cmake_minimum_required(VERSION 3.14)
project(conan-wrapper)

set(_unused ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/sources/build/cmake/modules/")

add_subdirectory(sources)
