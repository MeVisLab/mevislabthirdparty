cmake_minimum_required(VERSION 3.20)
project(test_package LANGUAGES CXX)

enable_testing()

find_package(Qt6 COMPONENTS Core Network Widgets REQUIRED)
qt_standard_project_setup()

find_package(SingleApplication REQUIRED)

qt_add_executable(test_package test_package.cpp)

if (NOT WIN32)
  # fixes a linker problem with the order of static lib and dynamic libs on the command line
  set_target_properties(Qt6::Widgets PROPERTIES INTERFACE_LINK_LIBRARIES Qt6::Network)
  set_target_properties(Qt6::Network PROPERTIES INTERFACE_LINK_LIBRARIES Qt6::Widgets)
endif()

target_link_libraries(test_package PRIVATE SingleApplication::SingleApplication Qt6::Network Qt6::Widgets Qt::Core)

add_test(NAME test_package COMMAND test_package)
