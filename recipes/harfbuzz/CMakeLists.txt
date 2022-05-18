cmake_minimum_required(VERSION 3.14)
project(conan-wrapper)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(_IGNORED ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/sources/build/cmake/modules/")

add_subdirectory(sources)
