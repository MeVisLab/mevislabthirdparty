cmake_minimum_required(VERSION 3.17)
project(PythonBindingQt LANGUAGES CXX)

option(BUILD_WEBKIT_BINDING "Build QtWebKit bindings" ON)

message(STATUS "BUILD_WEBKIT_BINDING: ${BUILD_WEBKIT_BINDING}")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(_UNUSED
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

find_library(Python3_LIBRARY NAMES ${CONAN_LIBS_PYTHON} PATHS ${CONAN_LIB_DIRS_PYTHON})
if(WIN32)
    find_library(Python3_LIBRARY_RELEASE NAMES python${python_VERSION_MAJOR}${python_VERSION_MINOR} PATHS ${CONAN_LIB_DIRS_PYTHON})
    find_library(Python3_LIBRARY_DEBUG NAMES python${python_VERSION_MAJOR}${python_VERSION_MINOR}_d PATHS ${CONAN_LIB_DIRS_PYTHON})
else()
    find_library(Python3_LIBRARY_RELEASE NAMES python${python_VERSION_MAJOR}.${python_VERSION_MINOR}m python${python_VERSION_MAJOR}.${python_VERSION_MINOR} PATHS ${CONAN_LIB_DIRS_PYTHON})
    find_library(Python3_LIBRARY_DEBUG NAMES python${python_VERSION_MAJOR}.${python_VERSION_MINOR}m python${python_VERSION_MAJOR}.${python_VERSION_MINOR} PATHS ${CONAN_LIB_DIRS_PYTHON})
endif()

find_package(Threads REQUIRED)

add_library(Python3::Python INTERFACE IMPORTED)
set_property(TARGET Python3::Python PROPERTY INTERFACE_LINK_LIBRARIES $<IF:$<CONFIG:Debug>,${Python3_LIBRARY_DEBUG},${Python3_LIBRARY_RELEASE}>)
set_property(TARGET Python3::Python PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_PYTHON})

set(SITE_PACKAGE_TARGET_DIR "${MEVIS_PYTHON_SITE_PACKAGES_FOLDER}")

set(TARGET_LIBRARY_OUTPUT_DIRECTORY "${SITE_PACKAGE_TARGET_DIR}/../")
set(TARGET_RUNTIME_OUTPUT_DIRECTORY "${SITE_PACKAGE_TARGET_DIR}/PythonQt")

set(CMAKE_AUTOMOC ON)

set(_UNUSED ${CMAKE_DEBUG_POSTFIX} ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY} ${CMAKE_INSTALL_BINDIR} ${CMAKE_INSTALL_DATAROOTDIR} ${CMAKE_INSTALL_INCLUDEDIR} ${CMAKE_INSTALL_LIBDIR} ${CMAKE_INSTALL_LIBEXECDIR} ${CMAKE_INSTALL_OLDINCLUDEDIR} ${CMAKE_INSTALL_SBINDIR})

add_subdirectory(Qt)
add_subdirectory(QtCore)
add_subdirectory(QtGui)
add_subdirectory(QtMultimedia)
add_subdirectory(QtNetwork)
add_subdirectory(QtOpenGL)
add_subdirectory(QtQml)
add_subdirectory(QtQuick)
add_subdirectory(QtSql)
add_subdirectory(QtSvg)
add_subdirectory(QtWebEngineWidgets)
add_subdirectory(QtXml)
add_subdirectory(QtXmlPatterns)

if(BUILD_WEBKIT_BINDING)
    add_subdirectory(QtWebKit)
endif()
