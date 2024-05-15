cmake_minimum_required(VERSION 3.27)
project(test_package LANGUAGES C)

find_package(c-blosc REQUIRED)

add_executable(${PROJECT_NAME} test_package.c)
target_link_libraries(${PROJECT_NAME} PRIVATE c-blosc::c-blosc)
