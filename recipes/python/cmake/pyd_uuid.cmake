add_pyd(_uuid)
target_link_libraries(_uuid PRIVATE rpcrt4.lib)

target_sources(_uuid PRIVATE
    ${SRC}/Modules/_uuidmodule.c
)
