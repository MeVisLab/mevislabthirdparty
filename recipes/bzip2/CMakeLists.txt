cmake_minimum_required(VERSION 3.14)
project(bzip2 C)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# prevent CMake from complaining about this external unused variable.
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

if(MSVC OR MSVC90 OR MSVC10)
    set(MSVC ON)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

add_library(bz2 STATIC "")
target_sources(bz2 PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/blocksort.c
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/bzlib.c
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/compress.c
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/crctable.c
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/decompress.c
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/huffman.c
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/randtable.c
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/bzlib.h
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/bzlib_private.h
)
target_include_directories(bz2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/sources)

install(TARGETS bz2 RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/sources/bzlib.h DESTINATION include)
