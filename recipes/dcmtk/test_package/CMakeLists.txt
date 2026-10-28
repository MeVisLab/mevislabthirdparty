cmake_minimum_required(VERSION 3.31)

project(test_package LANGUAGES CXX)

find_package(DCMTK REQUIRED)

add_executable(test_package test_package.cpp)
target_link_libraries(
    test_package
    PRIVATE DCMTK::ofstd
            DCMTK::oflog
            DCMTK::dcmdata
            DCMTK::dcmimgle
            DCMTK::dcmimage
            DCMTK::dcmjpeg
            DCMTK::dcmsr
            DCMTK::dcmnet)

if(MSVC)
    target_compile_options(test_package PUBLIC "/Zc:__cplusplus")
endif()
