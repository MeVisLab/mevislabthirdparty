cmake_minimum_required(VERSION 3.27)
project(test_package LANGUAGES C)

find_package(LibXml2 REQUIRED)
find_package(LibXslt REQUIRED)

add_executable(test_package test_package.c)
target_link_libraries(test_package PRIVATE LibXml2::LibXml2 LibXslt::LibXslt)
