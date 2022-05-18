cmake_minimum_required(VERSION 3.10)
project(test_package CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# prevent CMake from complaining about this external unused variable.
set(_UNUSED
  ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY}
  ${CMAKE_INSTALL_BINDIR}
  ${CMAKE_INSTALL_DATAROOTDIR}
  ${CMAKE_INSTALL_INCLUDEDIR}
  ${CMAKE_INSTALL_LIBDIR}
  ${CMAKE_INSTALL_LIBEXECDIR}
  ${CMAKE_INSTALL_OLDINCLUDEDIR}
  ${CMAKE_INSTALL_SBINDIR}
)

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
include(ECMGenerateHeaders)

add_library(MyLib INTERFACE)
target_include_directories(MyLib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}")
ecm_generate_headers(
    MyLib_FORWARDING_HEADERS
    HEADER_NAMES MLFoo
    REQUIRED_HEADERS MyLib_HEADERS
)

add_executable(test_package test_package.cpp)
target_link_libraries(test_package MyLib)
