cmake_minimum_required(VERSION 3.14)
project(conan-wrapper)

set(CONAN_DISABLE_CHECK_COMPILER ON)
set(_unused ${CONAN_COMPILER_VERSION} ${CMAKE_DEBUG_POSTFIX} ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY})

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})

include(${CMAKE_BINARY_DIR}/../conanbuildinfo.cmake)
conan_basic_setup()

find_package(Boost COMPONENTS system REQUIRED)

add_subdirectory(sources)
