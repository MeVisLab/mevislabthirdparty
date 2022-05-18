cmake_minimum_required(VERSION 3.14)
project(conan-wrapper)

set(_unused
    ${CONAN_COMPILER_VERSION}
    ${CMAKE_DEBUG_POSTFIX}
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

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})

find_package(FLANN REQUIRED)
find_package(Boost COMPONENTS system serialization filesystem date_time iostreams REQUIRED)

find_package(Qhull REQUIRED)
set(QHULL_FOUND TRUE)
set(HAVE_QHULL TRUE)
add_library(QHULL::QHULL ALIAS Qhull::Qhull)

add_subdirectory(sources)
