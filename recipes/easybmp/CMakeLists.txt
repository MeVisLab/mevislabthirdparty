cmake_minimum_required(VERSION 3.27)
project(EasyBMP VERSION 1.06)

add_library(easybmp "")
target_sources(easybmp PRIVATE EasyBMP.cpp)

target_include_directories(easybmp PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS easybmp
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

install(FILES
    EasyBMP.h
    EasyBMP_BMP.h
    EasyBMP_VariousBMPutilities.h
    EasyBMP_DataStructures.h
  DESTINATION include
)

install(FILES "BSD_(revised)_license.txt" DESTINATION licenses RENAME LICENSE)
