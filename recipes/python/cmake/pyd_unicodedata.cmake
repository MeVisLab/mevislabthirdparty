add_pyd(unicodedata)
target_compile_definitions(unicodedata PRIVATE MMAP_EXPORTS)

target_sources(unicodedata PRIVATE
    sources/Modules/unicodedata.c
)
