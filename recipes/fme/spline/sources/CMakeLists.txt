cmake_minimum_required(VERSION 3.27)
project(spline)
include(GenerateExportHeader)

add_library(spline spline.h spline.cpp)
generate_export_header(spline)
target_include_directories(spline PRIVATE "${CMAKE_BINARY_DIR}")

install(TARGETS spline RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(FILES spline.h ${PROJECT_BINARY_DIR}/spline_export.h DESTINATION include)
