cmake_minimum_required(VERSION 3.27)
project(test_package LANGUAGES C)

find_package(EXPAT REQUIRED)

add_executable(test_package ../test_package/test_package.c)
target_link_libraries(test_package PRIVATE EXPAT::EXPAT)

# Test whether variables from https://cmake.org/cmake/help/latest/module/FindEXPAT.html
# are properly defined in conan generators
set(_vars
    EXPAT_INCLUDE_DIRS
    EXPAT_LIBRARIES
    EXPAT_FOUND
)
foreach(_var ${_vars})
    if(DEFINED ${_var})
        message(STATUS "${_var}: ${${_var}}")
    else()
        message(FATAL_ERROR "${_var} not defined")
    endif()
endforeach()
