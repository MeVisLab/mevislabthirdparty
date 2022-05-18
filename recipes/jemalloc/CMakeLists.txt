cmake_minimum_required(VERSION 3.14)
project(conan-wrapper C)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

set(_UNUSED
  ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY}
  ${CMAKE_INSTALL_BINDIR}
  ${CMAKE_INSTALL_DATAROOTDIR}
  ${CMAKE_INSTALL_INCLUDEDIR}
  ${CMAKE_INSTALL_LIBDIR}
  ${CMAKE_INSTALL_LIBEXECDIR}
  ${CMAKE_INSTALL_OLDINCLUDEDIR}
  ${CMAKE_INSTALL_SBINDIR}
  ${CONAN_COMPILER}
  ${CONAN_COMPILER_VERSION}
  ${CONAN_EXPORTED}
  ${CONAN_IN_LOCAL_CACHE}
  ${CONAN_LINK_RUNTIME}
)

add_library(jemalloc)

target_include_directories(jemalloc PUBLIC sources/include sources/include/msvc_compat)
target_compile_definitions(jemalloc PUBLIC _REENTRANT DLLEXPORT)
target_compile_definitions(jemalloc PUBLIC $<$<CONFIG:DEBUG>:JEMALLOC_DEBUG>)
target_compile_definitions(jemalloc PUBLIC $<$<CONFIG:DEBUG>:_DEBUG>)
target_compile_definitions(jemalloc PUBLIC $<$<CONFIG:RELEASE>:NDEBUG>)

target_sources(jemalloc PUBLIC
    sources/src/arena.c
    sources/src/atomic.c
    sources/src/base.c
    sources/src/bitmap.c
    sources/src/chunk.c
    sources/src/chunk_dss.c
    sources/src/chunk_mmap.c
    sources/src/ckh.c
    sources/src/ctl.c
    sources/src/extent.c
    sources/src/hash.c
    sources/src/huge.c
    sources/src/jemalloc.c
    sources/src/mb.c
    sources/src/mutex.c
    sources/src/nstime.c
    sources/src/pages.c
    sources/src/prng.c
    sources/src/prof.c
    sources/src/quarantine.c
    sources/src/rtree.c
    sources/src/spin.c
    sources/src/stats.c
    sources/src/tcache.c
    sources/src/ticker.c
    sources/src/tsd.c
    sources/src/util.c
    sources/src/witness.c
)


install(TARGETS jemalloc RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(FILES sources/include/msvc_compat/windows_extra.h sources/include/msvc_compat/strings.h DESTINATION include/jemalloc/msvc_compat)
install(FILES sources/include/jemalloc/jemalloc.h DESTINATION include/jemalloc)

if(MSVC)
    install(FILES $<TARGET_PDB_FILE:jemalloc> DESTINATION bin OPTIONAL)
endif()
