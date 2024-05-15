cmake_minimum_required(VERSION 3.27)
project(test_package C)

find_package(LibXml2 REQUIRED)

# https://cmake.org/cmake/help/latest/module/FindLibXml2.html
set(_result_vars
    LibXml2_FOUND
    LIBXML2_FOUND
    LIBXML2_INCLUDE_DIR
    LIBXML2_INCLUDE_DIRS
    LIBXML2_LIBRARIES
    LIBXML2_VERSION_STRING
)

foreach(_var ${_result_vars})
  if(DEFINED ${_var})
    message(STATUS "${_var}: ${${_var}}")
  else()
    message(FATAL_ERROR "${_var} not defined")
  endif()
endforeach()


add_executable(test_package test_package.c)
target_link_libraries(test_package LibXml2::LibXml2)
