cmake_minimum_required(VERSION 3.27)
project(test_package LANGUAGES C)

find_package(PCRE2 REQUIRED 8BIT)

add_executable(test_package test_package.c)
target_link_libraries(test_package PRIVATE PCRE2::8BIT)
