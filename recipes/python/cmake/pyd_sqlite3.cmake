add_pyd(_sqlite3)

target_link_libraries(_sqlite3 PRIVATE CONAN_PKG::sqlite3)

target_compile_definitions(_sqlite3 PRIVATE _USRDLL _SQLITE3_EXPORTS MODULE_NAME="\\\"sqlite3\\\"")

target_sources(_sqlite3 PRIVATE
    sources/Modules/_sqlite/cache.h
    sources/Modules/_sqlite/connection.h
    sources/Modules/_sqlite/cursor.h
    sources/Modules/_sqlite/microprotocols.h
    sources/Modules/_sqlite/module.h
    sources/Modules/_sqlite/prepare_protocol.h
    sources/Modules/_sqlite/row.h
    sources/Modules/_sqlite/statement.h
    sources/Modules/_sqlite/util.h
    sources/Modules/_sqlite/cache.c
    sources/Modules/_sqlite/connection.c
    sources/Modules/_sqlite/cursor.c
    sources/Modules/_sqlite/microprotocols.c
    sources/Modules/_sqlite/module.c
    sources/Modules/_sqlite/prepare_protocol.c
    sources/Modules/_sqlite/row.c
    sources/Modules/_sqlite/statement.c
    sources/Modules/_sqlite/util.c
)
