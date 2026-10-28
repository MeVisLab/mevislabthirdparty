cmake_minimum_required(VERSION 3.31)
project(test_package LANGUAGES C CXX)

find_package(protobuf REQUIRED)
find_package(ONNX REQUIRED)

add_executable(test_package test_package.cpp)
target_link_libraries(test_package PRIVATE protobuf::libprotobuf onnx)
