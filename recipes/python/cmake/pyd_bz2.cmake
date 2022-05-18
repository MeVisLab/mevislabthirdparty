add_pyd(_bz2)
target_link_libraries(_bz2 PRIVATE CONAN_PKG::BZip2)

target_compile_definitions(_bz2 PRIVATE _FILE_OFFSET_BITS=64)

target_sources(_bz2 PRIVATE
    sources/Modules/_bz2module.c
)
