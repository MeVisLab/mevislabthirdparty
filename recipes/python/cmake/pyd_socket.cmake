add_pyd(_socket)

target_sources(_socket PRIVATE
    sources/Modules/socketmodule.c
)

target_link_libraries(_socket PRIVATE Ws2_32.lib)
target_link_libraries(_socket PRIVATE iphlpapi.lib)
