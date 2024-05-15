cmake_minimum_required(VERSION 3.27)
project(test_package LANGUAGES CXX)

find_package(protobuf CONFIG REQUIRED)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(test_package test_package.cpp addressbook.proto)
target_link_libraries(test_package PRIVATE protobuf::libprotobuf)
protobuf_generate(TARGET test_package)
