cmake_minimum_required(VERSION 3.10)
project(test_package CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(_IGNORE ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY})

find_package(Qt5 COMPONENTS Core Gui Widgets Network REQUIRED)

add_executable(test_package test_package.cpp)
target_link_libraries(test_package Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network ${CONAN_LIBS})
