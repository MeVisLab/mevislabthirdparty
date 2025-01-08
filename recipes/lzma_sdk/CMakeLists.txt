cmake_minimum_required(VERSION 3.27)
project(LZMA VERSION ${CONAN_LZMA_VERISON} LANGUAGES C)

add_library(lzma_sdk)
set_target_properties(lzma_sdk PROPERTIES VERSION "${PROJECT_VERSION}" SOVERSION "${PROJECT_VERSION_MAJOR}")

set(_HEADERS
  src/C/7zTypes.h
  src/C/7zWindows.h
  src/C/Alloc.h
  src/C/Bra.h
  src/C/CpuArch.h
  src/C/LzFind.h
  src/C/LzFindMt.h
  src/C/LzHash.h
  src/C/Lzma86.h
  src/C/LzmaDec.h
  src/C/LzmaEnc.h
  src/C/RotateDefs.h
  src/C/Threads.h
  src/C/Util/Lzma/Precomp.h
  src/C/Util/LzmaLib/Precomp.h
  )

target_sources(lzma_sdk PRIVATE
  src/C/Alloc.c
  src/C/Bra.c
  src/C/Bra86.c
  src/C/CpuArch.c
  src/C/LzFind.c
  src/C/LzFindMt.c
  src/C/LzFindOpt.c
  src/C/Lzma86Dec.c
  src/C/Lzma86Enc.c
  src/C/LzmaDec.c
  src/C/LzmaEnc.c
  src/C/Sha256Opt.c
  src/C/SwapBytes.c
  src/C/SwapBytes.h
  src/C/Threads.c
  src/C/Util/LzmaLib/Precomp.c
  ${_HEADERS}
)

target_include_directories(lzma_sdk PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/C>)

install(TARGETS lzma_sdk RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(FILES ${_HEADERS} DESTINATION "include/C")
