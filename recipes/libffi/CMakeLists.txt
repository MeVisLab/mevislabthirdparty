cmake_minimum_required(VERSION 3.19)
project(libffi VERSION ${VERSION} LANGUAGES C ASM)

set(_unused
  ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY}
  ${CMAKE_DEBUG_POSTFIX}
  ${CMAKE_INSTALL_BINDIR}
  ${CMAKE_INSTALL_DATAROOTDIR}
  ${CMAKE_INSTALL_INCLUDEDIR}
  ${CMAKE_INSTALL_LIBDIR}
  ${CMAKE_INSTALL_LIBEXECDIR}
  ${CMAKE_INSTALL_OLDINCLUDEDIR}
  ${CMAKE_INSTALL_SBINDIR}
)

include(conanbuildinfo.cmake)
conan_basic_setup()

set(HAVE_LONG_DOUBLE 0)
if(WIN32)
    set(TARGET X86_WIN64)
elseif(APPLE)
    if("${ARCH}" STREQUAL "armv8")
        set(TARGET ARM64)
        set(HAVE_LONG_DOUBLE 1)
    else()
        set(TARGET X86_DARWIN)
        set(HAVE_LONG_DOUBLE 1)
    endif()
else()
    set(TARGET X86_64)
    set(HAVE_LONG_DOUBLE 1)
endif()

message(STATUS "Target platform: ${TARGET}")

set(FFI_CLOSURES 1)
set(FFI_GO_CLOSURES 1)
set(FFI_DEBUG off)
set(FFI_EXEC_TRAMPOLINE_TABLE 0)
set(FFI_MMAP_EXEC_WRIT 0)

# mimic layout of original buildsystem
configure_file(sources/include/ffi.h.in ${CMAKE_BINARY_DIR}/include/ffi.h)

configure_file(files/fficonfig.h.in ${CMAKE_BINARY_DIR}/fficonfig.h @ONLY)

if("${ARCH}" STREQUAL "armv8")
file(COPY sources/src/aarch64/ffitarget.h DESTINATION ${CMAKE_BINARY_DIR}/include)
else()
    file(COPY sources/src/x86/ffitarget.h DESTINATION ${CMAKE_BINARY_DIR}/include)
endif()

include_directories(${CMAKE_BINARY_DIR}/include)
include_directories(${CMAKE_BINARY_DIR})
include_directories(sources/include)

add_library(ffi "")

if(BUILD_SHARED_LIBS)
    message(STATUS "Building shared library")
    target_compile_definitions(ffi PRIVATE -DFFI_BUILDING_DLL)
else()
    target_compile_definitions(ffi PRIVATE -DFFI_BUILDING)
    message(STATUS "Building static library")
endif()

target_sources(ffi PRIVATE
    sources/src/closures.c
    sources/src/prep_cif.c
    sources/src/types.c
    sources/src/java_raw_api.c
    sources/src/raw_api.c
    sources/src/tramp.c
)

if(WIN32)
    enable_language(ASM_MASM)

    target_sources(ffi PRIVATE sources/src/x86/ffiw64.c)

    execute_process(
        COMMAND ${CMAKE_C_COMPILER} /nologo /EP
            /I${CMAKE_SOURCE_DIR}/sources
            /I${CMAKE_SOURCE_DIR}/sources/include
            /I${CMAKE_BINARY_DIR}
            /I${CMAKE_BINARY_DIR}/include
          ${CMAKE_SOURCE_DIR}/sources/src/x86/win64_intel.S
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        OUTPUT_FILE ${CMAKE_BINARY_DIR}/win64_intel.asm
        COMMAND_ERROR_IS_FATAL ANY
    )

    target_sources(ffi PRIVATE ${CMAKE_BINARY_DIR}/win64_intel.asm)
    set_source_files_properties(${CMAKE_BINARY_DIR}/win64_intel.asm PROPERTIES GENERATED TRUE LANGUAGE ASM_MASM)
elseif("${ARCH}" STREQUAL "armv8")
    target_sources(ffi PRIVATE 
        sources/src/aarch64/ffi.c
        sources/src/aarch64/ffitarget.h
        sources/src/aarch64/internal.h
        sources/src/aarch64/sysv.S
    )
elseif("${ARCH}" STREQUAL "x86_64")
    target_sources(ffi PRIVATE 
        sources/src/x86/unix64.S 
        sources/src/x86/win64.S
        sources/src/x86/ffi64.c
        sources/src/x86/ffiw64.c
    )
else()
    message(FATAL_ERROR "Unknown arch '${ARCH}'")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_sources(ffi PRIVATE sources/src/debug.c)
    add_definitions(-DFFI_DEBUG)
endif()

install(TARGETS ffi RUNTIME DESTINATION bin ARCHIVE DESTINATION lib LIBRARY DESTINATION lib)
install(FILES ${CMAKE_BINARY_DIR}/include/ffi.h ${CMAKE_BINARY_DIR}/include/ffitarget.h DESTINATION include)
