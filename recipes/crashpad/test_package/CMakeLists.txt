cmake_minimum_required(VERSION 3.31)
project(test_package LANGUAGES CXX)

find_package(CrashPad REQUIRED)

add_executable(test_package test_package.cpp)
target_compile_features(test_package PRIVATE cxx_std_20)
target_compile_definitions(test_package PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN UNICODE _UNICODE)
target_link_libraries(test_package PRIVATE CrashPad::CrashPad advapi32 powrprof rpcrt4 user32 version winhttp)
