add_pyd(_ctypes)
target_link_libraries(_ctypes PRIVATE Ole32.lib Oleaut32.lib)

find_package(libffi REQUIRED)

target_sources(_ctypes PRIVATE
    ${SRC}/Modules/_ctypes/_ctypes.c
    ${SRC}/Modules/_ctypes/callbacks.c
    ${SRC}/Modules/_ctypes/callproc.c
    ${SRC}/Modules/_ctypes/cfield.c
    ${SRC}/Modules/_ctypes/malloc_closure.c
    ${SRC}/Modules/_ctypes/stgdict.c
)

target_compile_definitions(_ctypes PRIVATE USING_MALLOC_CLOSURE_DOT_C)
target_link_libraries(_ctypes PRIVATE libffi::libffi)
