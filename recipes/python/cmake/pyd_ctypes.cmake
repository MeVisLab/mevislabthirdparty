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

target_compile_definitions(_ctypes PRIVATE FFI_BUILDING)
target_link_libraries(_ctypes PRIVATE CONAN_PKG::libffi)
