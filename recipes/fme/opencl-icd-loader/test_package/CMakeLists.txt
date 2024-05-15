cmake_minimum_required(VERSION 3.27)
project(test_package C)

find_package(OpenCLICDLoader REQUIRED)
find_package(OpenCL REQUIRED)

add_executable(test_package test_package.c)
target_link_libraries(test_package PRIVATE OpenCLICDLoader::OpenCLICDLoader)
