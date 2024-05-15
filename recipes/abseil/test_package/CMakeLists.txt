cmake_minimum_required(VERSION 3.27)
project(test_package LANGUAGES CXX)

find_package(absl REQUIRED)

add_executable(test_package test_package.cpp)

target_link_libraries(test_package PRIVATE absl::strings absl::flat_hash_map absl::flat_hash_set absl::int128 absl::time)
