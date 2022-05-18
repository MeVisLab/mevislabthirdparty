cmake_minimum_required(VERSION 3.10)
project(conan-wrapper)

set(_unused
    ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY}
    ${CMAKE_INSTALL_BINDIR}
    ${CMAKE_INSTALL_DATAROOTDIR}
    ${CMAKE_INSTALL_INCLUDEDIR}
    ${CMAKE_INSTALL_LIBDIR}
    ${CMAKE_INSTALL_LIBEXECDIR}
    ${CMAKE_INSTALL_OLDINCLUDEDIR}
    ${CMAKE_INSTALL_SBINDIR}
)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(sources)
