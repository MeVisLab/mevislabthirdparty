cmake_minimum_required(VERSION 3.31)
project(test_package LANGUAGES CXX)

execute_process(
  COMMAND "${LLVM_CONFIG_EXECUTABLE}" --includedir
  OUTPUT_VARIABLE LLVM_INCLUDE_DIR
  OUTPUT_STRIP_TRAILING_WHITESPACE
  COMMAND_ERROR_IS_FATAL ANY
)
execute_process(
  COMMAND "${LLVM_CONFIG_EXECUTABLE}" --libfiles --system-libs core
  OUTPUT_VARIABLE LLVM_LINK_LIBRARIES
  OUTPUT_STRIP_TRAILING_WHITESPACE
  COMMAND_ERROR_IS_FATAL ANY
)
string(REPLACE "\n" " " LLVM_LINK_LIBRARIES "${LLVM_LINK_LIBRARIES}")
separate_arguments(LLVM_LINK_LIBRARIES NATIVE_COMMAND "${LLVM_LINK_LIBRARIES}")

add_executable(test_package test_package.cpp)
target_compile_features(test_package PRIVATE cxx_std_17)
target_include_directories(test_package PRIVATE "${LLVM_INCLUDE_DIR}")
target_link_libraries(test_package PRIVATE ${LLVM_LINK_LIBRARIES})
