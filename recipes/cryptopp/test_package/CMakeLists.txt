cmake_minimum_required(VERSION 3.27)
project(test_package LANGUAGES CXX)

find_package(CryptoPP REQUIRED CONFIG)

add_executable(${PROJECT_NAME} test_package.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE CryptoPP::CryptoPP)
