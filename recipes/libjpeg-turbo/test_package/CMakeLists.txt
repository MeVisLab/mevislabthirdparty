cmake_minimum_required(VERSION 3.27)
project(test_package LANGUAGES C)

find_package(libjpeg-turbo REQUIRED)
add_executable(test_package1 test_package.c)
target_link_libraries(test_package1 PRIVATE libjpeg-turbo::jpeg)

find_package(JPEG REQUIRED)
add_executable(test_package2 test_package.c)
target_link_libraries(test_package2 PRIVATE JPEG::JPEG)
