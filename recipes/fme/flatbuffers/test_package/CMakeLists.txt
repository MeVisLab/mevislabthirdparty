cmake_minimum_required(VERSION 3.31)
project(test_package LANGUAGES CXX)

find_package(FlatBuffers REQUIRED)

set(FLATBUFFERS_SCHEMA ${CMAKE_CURRENT_SOURCE_DIR}/monster.fbs)
set(FLATBUFFERS_GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR})

build_flatbuffers("${FLATBUFFERS_SCHEMA}" "" fbschemas "" "${FLATBUFFERS_GENERATED_DIR}" "" "")

add_library(FlatbuffersSchema INTERFACE)
target_include_directories(FlatbuffersSchema INTERFACE ${FLATBUFFERS_GENERATED_DIR})
add_dependencies(FlatbuffersSchema fbschemas)

add_executable(test_package test_package.cpp)
target_link_libraries(test_package PRIVATE flatbuffers::flatbuffers FlatbuffersSchema)
