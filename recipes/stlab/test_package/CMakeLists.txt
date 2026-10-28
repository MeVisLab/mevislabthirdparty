cmake_minimum_required(VERSION 3.31)
project(test_package CXX)

find_package(stlab REQUIRED)

if(MSVC)
    add_compile_options("/Zc:__cplusplus")
endif()

if (WIN32)
  add_compile_definitions(NOMINMAX _SILENCE_CXX17_RESULT_OF_DEPRECATION_WARNING)
endif()

add_executable(test_package test_package.cpp)
target_link_libraries(test_package stlab::stlab)

foreach(it IN ITEMS a b)
  set(test_target test_package_${it})
  add_library(${test_target} SHARED test_package_api.cpp)
  target_compile_definitions(${test_target} PRIVATE TEST_PACKAGE_NAMESPACE=${test_target})
  target_link_libraries(${test_target} PRIVATE stlab::stlab)
  set_target_properties(${test_target} PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
    WINDOWS_EXPORT_ALL_SYMBOLS ON)
  target_link_libraries(test_package ${test_target})
endforeach()
