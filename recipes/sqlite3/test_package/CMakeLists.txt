cmake_minimum_required(VERSION 3.27)
project(test_package LANGUAGES C)

find_package(SQLite3 REQUIRED)

add_executable(${PROJECT_NAME} test_package.c)
target_link_libraries(${PROJECT_NAME} PRIVATE SQLite::SQLite3)
target_compile_definitions(test_package PRIVATE EXPECTED_SQLITE3_VERSION="${EXPECTED_SQLITE3_VERSION}")
