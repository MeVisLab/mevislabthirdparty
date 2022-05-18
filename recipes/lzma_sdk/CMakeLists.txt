cmake_minimum_required(VERSION 3.17)
project(LZMA LANGUAGES C)

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

add_library(lzma_sdk STATIC "")
add_library(lzma_sdk::lzma_sdk ALIAS lzma_sdk)

set(_HEADERS
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/C/Alloc.h
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/C/7zTypes.h
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/C/Bra.h
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/C/CpuArch.h
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/C/LzFindMt.h
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/C/LzFind.h
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/C/LzHash.h
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/C/Lzma86.h
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/C/LzmaDec.h
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/C/LzmaEnc.h
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/C/RotateDefs.h
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/C/Threads.h
  )

target_sources(lzma_sdk PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/C/Alloc.c
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/C/Bra.c
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/C/Bra86.c
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/C/CpuArch.c
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/C/LzFind.c
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/C/Lzma86Dec.c
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/C/Lzma86Enc.c
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/C/LzmaDec.c
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/C/LzmaEnc.c
  ${_HEADERS}
)

# On Windows we can use a multi threading implementation of LzFind
# On other platforms, we have to disabled it
if (WIN32)
  target_sources(lzma_sdk PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/C/LzFindMt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/C/Threads.c
  )
else()
  target_compile_definitions(lzma_sdk PRIVATE _7ZIP_ST)
endif()

target_include_directories(lzma_sdk PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sources/C>
)

install(TARGETS lzma_sdk RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(FILES ${_HEADERS} DESTINATION "include/C")
