cmake_minimum_required(VERSION 3.27)
project(libffi VERSION ${CONAN_LIBFFI_VERSION} LANGUAGES C ASM)

set(HAVE_LONG_DOUBLE 0)
if(WIN32)
    set(TARGET X86_WIN64)
elseif(APPLE)
    if("${CONAN_LIBFFI_ARCH}" STREQUAL "armv8")
        set(TARGET ARM64)
        set(HAVE_LONG_DOUBLE 1)
    else()
        set(TARGET X86_DARWIN)
        set(HAVE_LONG_DOUBLE 1)
    endif()
else()
    if("${CONAN_LIBFFI_ARCH}" STREQUAL "armv8")
        set(TARGET ARM64)
        set(HAVE_LONG_DOUBLE 1)
    else()
        set(TARGET X86_64)
        set(HAVE_LONG_DOUBLE 1)
    endif()
endif()

message(STATUS "Target platform: ${TARGET}")

set(FFI_CLOSURES 1)
set(FFI_GO_CLOSURES 1)
set(FFI_DEBUG off)
set(FFI_EXEC_TRAMPOLINE_TABLE 0)
set(FFI_MMAP_EXEC_WRIT 0)

# mimic layout of original buildsystem
configure_file(src/include/ffi.h.in ${CMAKE_BINARY_DIR}/include/ffi.h)
configure_file(files/fficonfig.h.in ${CMAKE_BINARY_DIR}/fficonfig.h @ONLY)

if("${CONAN_LIBFFI_ARCH}" STREQUAL "armv8")
    file(COPY src/src/aarch64/ffitarget.h DESTINATION ${CMAKE_BINARY_DIR}/include)
else()
    file(COPY src/src/x86/ffitarget.h DESTINATION ${CMAKE_BINARY_DIR}/include)
endif()

include_directories(${CMAKE_BINARY_DIR}/include)
include_directories(${CMAKE_BINARY_DIR})
include_directories(src/include)

add_library(ffi "")

if(BUILD_SHARED_LIBS)
    message(STATUS "Building shared library")
    target_compile_definitions(ffi PRIVATE -DFFI_BUILDING_DLL)
else()
    target_compile_definitions(ffi PRIVATE -DFFI_BUILDING)
    target_compile_definitions(ffi PRIVATE -DFFI_STATIC_BUILD)
    message(STATUS "Building static library")
endif()

target_sources(ffi PRIVATE
    src/src/closures.c
    src/src/prep_cif.c
    src/src/types.c
    src/src/java_raw_api.c
    src/src/raw_api.c
    src/src/tramp.c
)

if(WIN32)
    enable_language(ASM_MASM)

    target_sources(ffi PRIVATE src/src/x86/ffiw64.c)

    execute_process(
        COMMAND ${CMAKE_C_COMPILER} /nologo /EP
            /I${CMAKE_SOURCE_DIR}/src
            /I${CMAKE_SOURCE_DIR}/src/include
            /I${CMAKE_BINARY_DIR}
            /I${CMAKE_BINARY_DIR}/include
          ${CMAKE_SOURCE_DIR}/src/src/x86/win64_intel.S
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        OUTPUT_FILE ${CMAKE_BINARY_DIR}/win64_intel.asm
        COMMAND_ERROR_IS_FATAL ANY
    )

    target_sources(ffi PRIVATE ${CMAKE_BINARY_DIR}/win64_intel.asm)
    set_source_files_properties(${CMAKE_BINARY_DIR}/win64_intel.asm PROPERTIES GENERATED TRUE LANGUAGE ASM_MASM)
elseif("${CONAN_LIBFFI_ARCH}" STREQUAL "armv8")
    target_sources(ffi PRIVATE
        src/src/aarch64/ffi.c
        src/src/aarch64/ffitarget.h
        src/src/aarch64/internal.h
        src/src/aarch64/sysv.S
    )
elseif("${CONAN_LIBFFI_ARCH}" STREQUAL "x86_64")
    target_sources(ffi PRIVATE
        src/src/x86/unix64.S
        src/src/x86/win64.S
        src/src/x86/ffi64.c
        src/src/x86/ffiw64.c
    )
else()
    message(FATAL_ERROR "Unknown arch '${CONAN_LIBFFI_ARCH}'")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_sources(ffi PRIVATE src/src/debug.c)
    add_definitions(-DFFI_DEBUG)
endif()

install(TARGETS ffi RUNTIME DESTINATION bin ARCHIVE DESTINATION lib LIBRARY DESTINATION lib)
install(FILES ${CMAKE_BINARY_DIR}/include/ffi.h ${CMAKE_BINARY_DIR}/include/ffitarget.h DESTINATION include)
