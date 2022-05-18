cmake_minimum_required(VERSION 3.17)
project(PythonBindingInventor LANGUAGES CXX)

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
    ${CMAKE_INSTALL_SBINDIR})

find_package(GLEW REQUIRED)
find_package(OpenGL 2.1 REQUIRED)
find_library(Python3_LIBRARY NAMES ${CONAN_LIBS_PYTHON} PATHS ${CONAN_LIB_DIRS_PYTHON})
if(WIN32)
    find_library(Python3_LIBRARY_RELEASE NAMES python${python_VERSION_MAJOR}${python_VERSION_MINOR} PATHS ${CONAN_LIB_DIRS_PYTHON})
    find_library(Python3_LIBRARY_DEBUG NAMES python${python_VERSION_MAJOR}${python_VERSION_MINOR}_d PATHS ${CONAN_LIB_DIRS_PYTHON})
else()
    find_library(Python3_LIBRARY_RELEASE NAMES python${python_VERSION_MAJOR}.${python_VERSION_MINOR}m python${python_VERSION_MAJOR}.${python_VERSION_MINOR} PATHS ${CONAN_LIB_DIRS_PYTHON})
    find_library(Python3_LIBRARY_DEBUG NAMES python${python_VERSION_MAJOR}.${python_VERSION_MINOR}m python${python_VERSION_MAJOR}.${python_VERSION_MINOR} PATHS ${CONAN_LIB_DIRS_PYTHON})
endif()

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Threads REQUIRED)

add_library(Python3::Python INTERFACE IMPORTED)
set_property(TARGET Python3::Python PROPERTY INTERFACE_LINK_LIBRARIES $<IF:$<CONFIG:Debug>,${Python3_LIBRARY_DEBUG},${Python3_LIBRARY_RELEASE}>)
set_property(TARGET Python3::Python PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_PYTHON})

set(SITE_PACKAGE_TARGET_DIR "${MEVIS_PYTHON_SITE_PACKAGES_FOLDER}")

set(TARGET_RUNTIME_OUTPUT_DIRECTORY "${SITE_PACKAGE_TARGET_DIR}/Inventor")

set(CMAKE_AUTOMOC ON)

set(_UNUSED ${CMAKE_DEBUG_POSTFIX} ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY} ${CMAKE_INSTALL_BINDIR} ${CMAKE_INSTALL_DATAROOTDIR} ${CMAKE_INSTALL_INCLUDEDIR} ${CMAKE_INSTALL_LIBDIR} ${CMAKE_INSTALL_LIBEXECDIR} ${CMAKE_INSTALL_OLDINCLUDEDIR} ${CMAKE_INSTALL_SBINDIR})

add_subdirectory(InventorActions)
add_subdirectory(InventorBase)
add_subdirectory(InventorDetails)
add_subdirectory(InventorDraggers)
add_subdirectory(InventorElements)
add_subdirectory(InventorEngines)
add_subdirectory(InventorEvents)
add_subdirectory(InventorFields)
add_subdirectory(InventorManips)
add_subdirectory(InventorNodekits)
add_subdirectory(InventorNodes)
add_subdirectory(InventorProjectors)
add_subdirectory(InventorSensors)