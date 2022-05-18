add_pyd(select)
target_link_libraries(select PRIVATE wsock32.lib Ws2_32.lib)

target_sources(select PRIVATE
    sources/Modules/selectmodule.c
)
