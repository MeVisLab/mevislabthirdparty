add_pyd(_lzma)

find_package(LibLZMA REQUIRED)

target_link_libraries(_lzma PRIVATE LibLZMA::LibLZMA)

target_sources(_lzma PRIVATE
    ${SRC}/Modules/_lzmamodule.c
)
