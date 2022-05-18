cmake_minimum_required(VERSION 3.14)
project(EasyBMP VERSION 1.06)

set(_unused
    ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY}
    ${CMAKE_INSTALL_BINDIR}
    ${CMAKE_INSTALL_DATAROOTDIR}
    ${CMAKE_INSTALL_INCLUDEDIR}
    ${CMAKE_INSTALL_LIBDIR}
    ${CMAKE_INSTALL_LIBEXECDIR}
    ${CMAKE_INSTALL_OLDINCLUDEDIR}
    ${CMAKE_INSTALL_SBINDIR}
    ${CMAKE_DEBUG_POSTFIX}
)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(easybmp "")
target_sources(easybmp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/sources/EasyBMP.cpp)

target_include_directories(easybmp PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sources>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS easybmp
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

install(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/EasyBMP.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/EasyBMP_BMP.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/EasyBMP_VariousBMPutilities.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/EasyBMP_DataStructures.h
  DESTINATION include
)
