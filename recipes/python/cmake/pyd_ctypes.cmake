add_pyd(_ctypes)
target_link_libraries(_ctypes PRIVATE Ole32.lib Oleaut32.lib)

target_sources(_ctypes PRIVATE
    sources/Modules/_ctypes/_ctypes.c
    sources/Modules/_ctypes/callbacks.c
    sources/Modules/_ctypes/callproc.c
    sources/Modules/_ctypes/cfield.c
    sources/Modules/_ctypes/malloc_closure.c
    sources/Modules/_ctypes/stgdict.c
)

if(CMAKE_PROJECT_VERSION VERSION_GREATER_EQUAL 3.9)
    target_compile_definitions(_ctypes PRIVATE FFI_BUILDING)
    target_link_libraries(_ctypes PRIVATE CONAN_PKG::libffi)
else()
    target_include_directories(_ctypes PRIVATE sources/Modules/_ctypes/libffi_msvc)
    target_sources(_ctypes PRIVATE
        sources/Modules/_ctypes/libffi_msvc/ffi.c
        sources/Modules/_ctypes/libffi_msvc/prep_cif.c
        sources/Modules/_ctypes/libffi_msvc/win64.asm
    )
endif()