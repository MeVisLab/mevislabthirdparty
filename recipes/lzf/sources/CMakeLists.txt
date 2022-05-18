cmake_minimum_required(VERSION 3.14)
project(LZF VERSION 3.5.0)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

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

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(LZF STATIC "")
add_library(LZF::LZF ALIAS LZF)
target_sources(LZF PRIVATE
    config.h
    crc32.h
    lzf_c.cpp
    lzf_d.cpp
    lzf.h
    lzfP.h
    )

install(TARGETS LZF LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(FILES "lzf.h" DESTINATION include)