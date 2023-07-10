cmake_minimum_required(VERSION 3.17)
project(PythonQt LANGUAGES CXX)

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

find_library(Python3_LIBRARY NAMES ${CONAN_LIBS_PYTHON} PATHS ${CONAN_LIB_DIRS_PYTHON})
if(WIN32)
    find_library(Python3_LIBRARY_RELEASE NAMES python${python_VERSION_MAJOR}${python_VERSION_MINOR} PATHS ${CONAN_LIB_DIRS_PYTHON})
    find_library(Python3_LIBRARY_DEBUG NAMES python${python_VERSION_MAJOR}${python_VERSION_MINOR}_d PATHS ${CONAN_LIB_DIRS_PYTHON})
else()
    find_library(Python3_LIBRARY_RELEASE NAMES python${python_VERSION_MAJOR}.${python_VERSION_MINOR}m python${python_VERSION_MAJOR}.${python_VERSION_MINOR} PATHS ${CONAN_LIB_DIRS_PYTHON})
    find_library(Python3_LIBRARY_DEBUG NAMES python${python_VERSION_MAJOR}.${python_VERSION_MINOR}m python${python_VERSION_MAJOR}.${python_VERSION_MINOR} PATHS ${CONAN_LIB_DIRS_PYTHON})
endif()

add_library(Python3::Python INTERFACE IMPORTED)
set_property(TARGET Python3::Python PROPERTY INTERFACE_LINK_LIBRARIES $<IF:$<CONFIG:Debug>,${Python3_LIBRARY_DEBUG},${Python3_LIBRARY_RELEASE}>)
set_property(TARGET Python3::Python PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_PYTHON})

if(WIN32)
    set_property(TARGET Python3::Python PROPERTY INTERFACE_LINK_OPTIONS /STACK:3000000)
    target_compile_definitions(Python3::Python INTERFACE NT_THREADS)
else()
    target_compile_definitions(Python3::Python INTERFACE _POSIX_THREADS)
endif()


find_package(Qt5 COMPONENTS Core Gui Widgets Network REQUIRED)
find_package(Threads REQUIRED)

set(CMAKE_AUTOMOC ON)

add_library(PythonQt "")
add_library(PythonQt::PythonQt ALIAS PythonQt)
set_target_properties(PythonQt PROPERTIES OUTPUT_NAME PythonQt)

add_subdirectory(src)
add_subdirectory(generated_cpp)

target_compile_definitions(PythonQt PRIVATE MEVIS_TARGET=PythonQt)
target_compile_definitions(PythonQt PRIVATE PYTHONQT_EXPORTS)
target_compile_definitions(PythonQt PUBLIC PYTHONQT_SUPPORT_NAME_PROPERTY)
target_compile_definitions(PythonQt PUBLIC PYTHONQT_SUPPORT_ML_TYPES)

target_include_directories(PythonQt
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:${MEVISLAB_INSTALL_INCLUDEDIR}>
  PRIVATE
    ${Qt5Core_PRIVATE_INCLUDE_DIRS}
)

target_link_libraries(PythonQt
  PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Network
    Python3::Python
    Threads::Threads
)

# MVL-11: TODO We have to fix the code generator!
# The code in generated_cpp uses many deprecated Qt function.
# Therefore I just remove QT_DISABLE_DEPRECATED_BEFORE=xxx and enable QT_NO_DEPRECATED_WARNINGS.
get_directory_property(defs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} COMPILE_DEFINITIONS)
if("${defs}" MATCHES ".*QT_DISABLE_DEPRECATED_BEFORE=0x[0-9]+")
    remove_definitions("-D${CMAKE_MATCH_0}")
endif()
remove_definitions("-DQT_DEPRECATED_WARNINGS")
target_compile_definitions(PythonQt PRIVATE QT_NO_DEPRECATED_WARNINGS) # since Qt 5.13

install(TARGETS PythonQt RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

if(WIN32)
    install(FILES $<TARGET_PDB_FILE:PythonQt> DESTINATION bin OPTIONAL)
endif()

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/" DESTINATION include FILES_MATCHING PATTERN "*.h")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/gui" DESTINATION include FILES_MATCHING PATTERN "*.h")

#file(RELATIVE_PATH REL ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
#install(FILES COPYING README DESTINATION ${REL})
