project(spline)
include(GenerateExportHeader)

add_library(spline spline.h spline.cpp)
generate_export_header(spline)

install(TARGETS spline RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(FILES spline.h ${PROJECT_BINARY_DIR}/spline_export.h DESTINATION include)
