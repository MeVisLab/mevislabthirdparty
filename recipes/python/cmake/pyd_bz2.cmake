add_pyd(_bz2)

find_package(BZip2 REQUIRED)

target_link_libraries(_bz2 PRIVATE BZip2::BZip2)

target_compile_definitions(_bz2 PRIVATE _FILE_OFFSET_BITS=64)

target_sources(_bz2 PRIVATE
    ${SRC}/Modules/_bz2module.c
)
