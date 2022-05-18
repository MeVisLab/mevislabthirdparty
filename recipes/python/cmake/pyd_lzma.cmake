add_pyd(_lzma)
target_link_libraries(_lzma PRIVATE CONAN_PKG::xz-utils)

target_sources(_lzma PRIVATE
    sources/Modules/_lzmamodule.c
)
