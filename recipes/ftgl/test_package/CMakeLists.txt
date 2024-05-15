cmake_minimum_required(VERSION 3.27)
project(test_package LANGUAGES CXX)

find_package(FTGL REQUIRED)
find_package(Freetype REQUIRED)
find_package(OpenGL REQUIRED)

# create the test application
add_executable(test_package test_package.cpp)
target_link_libraries(test_package PRIVATE FTGL::FTGL Freetype::Freetype)
