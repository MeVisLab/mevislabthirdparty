add_pyd(unicodedata)
target_compile_definitions(unicodedata PRIVATE MMAP_EXPORTS)

target_sources(unicodedata PRIVATE
    ${SRC}/Modules/unicodedata.c
)
