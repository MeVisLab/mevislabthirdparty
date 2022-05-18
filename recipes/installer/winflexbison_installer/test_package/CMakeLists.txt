cmake_minimum_required(VERSION 3.10)
project(test_package)

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

enable_testing()

set(CMAKE_CXX_STANDARD 11)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(NO_OUTPUT_DIRS)

message(STATUS "Configuring Flex test package targets")
set(FLEX_TARGET_COMPILE_FLAGS "")
if(MSVC)
    set(FLEX_TARGET_COMPILE_FLAGS "--wincompat")
endif()

find_package(FLEX)
flex_target(TestParser basic_nr.l "${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp" COMPILE_FLAGS "${FLEX_TARGET_COMPILE_FLAGS}")
add_executable(flex_test_package ${FLEX_TestParser_OUTPUTS})
add_test(TestLexer flex_test_package "${CMAKE_CURRENT_LIST_DIR}/basic_nr.txt")


message(STATUS "Configuring Bison test package targets")
find_package(BISON)
bison_target(bison_parser_target mc_parser.yy "${CMAKE_CURRENT_BINARY_DIR}/mc_parser.cpp")

add_executable(bison_test_package
  "${CMAKE_CURRENT_BINARY_DIR}/mc_parser.cpp"
  dummy_lex.cpp
)
target_include_directories(bison_test_package  PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
add_test(TestBison bison_test_package)
