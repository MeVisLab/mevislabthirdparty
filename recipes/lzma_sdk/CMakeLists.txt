cmake_minimum_required(VERSION 3.27)
project(LZMA VERSION ${CONAN_LZMA_VERISON} LANGUAGES C)

add_library(lzma_sdk)
set_target_properties(lzma_sdk PROPERTIES VERSION "${PROJECT_VERSION}" SOVERSION "${PROJECT_VERSION_MAJOR}")

set(_HEADERS
  src/C/Alloc.h
  src/C/7zTypes.h
  src/C/Bra.h
  src/C/CpuArch.h
  src/C/LzFindMt.h
  src/C/LzFind.h
  src/C/LzHash.h
  src/C/Lzma86.h
  src/C/LzmaDec.h
  src/C/LzmaEnc.h
  src/C/RotateDefs.h
  src/C/Threads.h
  )

target_sources(lzma_sdk PRIVATE
  src/C/Alloc.c
  src/C/Bra.c
  src/C/Bra86.c
  src/C/CpuArch.c
  src/C/LzFind.c
  src/C/Lzma86Dec.c
  src/C/Lzma86Enc.c
  src/C/LzmaDec.c
  src/C/LzmaEnc.c
  ${_HEADERS}
)

# On Windows we can use a multi threading implementation of LzFind
# On other platforms, we have to disabled it
if (WIN32)
  target_sources(lzma_sdk PRIVATE
    src/C/LzFindMt.c
    src/C/Threads.c
  )
else()
  target_compile_definitions(lzma_sdk PRIVATE _7ZIP_ST)
endif()

target_include_directories(lzma_sdk PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/C>)

install(TARGETS lzma_sdk RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(FILES ${_HEADERS} DESTINATION "include/C")
