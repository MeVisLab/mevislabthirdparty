add_pyd(_overlapped)
target_link_libraries(_overlapped PRIVATE ws2_32.lib)

target_sources(_overlapped PRIVATE
    ${SRC}/Modules/overlapped.c
)
