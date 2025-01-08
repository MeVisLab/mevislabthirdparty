cmake_minimum_required(VERSION 3.20)
project(test_package LANGUAGES C CXX)

enable_testing()

find_package(mimalloc REQUIRED)

add_executable(test_override_c test_override.c)
target_link_libraries(test_override_c PRIVATE mimalloc::mimalloc)
target_compile_features(test_override_c PRIVATE c_std_17)
add_test(NAME test_override_c COMMAND test_override_c)

add_executable(test_override_cpp test_override.cpp)
target_link_libraries(test_override_cpp PRIVATE mimalloc::mimalloc)
target_compile_features(test_override_cpp PRIVATE cxx_std_20)
add_test(NAME test_override_cpp COMMAND test_override_cpp)


add_executable(test_api_c test_api.c)
target_link_libraries(test_api_c PRIVATE mimalloc::mimalloc)
target_compile_features(test_api_c PRIVATE c_std_17)
add_test(NAME test_api_c COMMAND test_api_c)

add_executable(test_api_cpp test_api.cpp)
target_link_libraries(test_api_cpp PRIVATE mimalloc::mimalloc)
target_compile_features(test_api_cpp PRIVATE cxx_std_20)
add_test(NAME test_api_cpp COMMAND test_api_cpp)
