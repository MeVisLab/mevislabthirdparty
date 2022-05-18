add_pyd(winsound)
target_compile_definitions(winsound PRIVATE WINSOUND_EXPORTS)
target_link_libraries(winsound PRIVATE User32.lib winmm.lib)

target_sources(winsound PRIVATE
    sources/PC/winsound.c
)
