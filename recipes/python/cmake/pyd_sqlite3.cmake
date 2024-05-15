add_pyd(_sqlite3)

find_package(sqlite3 REQUIRED)

target_link_libraries(_sqlite3 PRIVATE sqlite3::sqlite3)

target_compile_definitions(_sqlite3 PRIVATE _USRDLL _SQLITE3_EXPORTS PY_SQLITE_HAVE_SERIALIZE PY_SQLITE_ENABLE_LOAD_EXTENSION MODULE_NAME="\\\"sqlite3\\\"")

target_sources(_sqlite3 PRIVATE
    ${SRC}/Modules/_sqlite/blob.c
    ${SRC}/Modules/_sqlite/blob.h
    ${SRC}/Modules/_sqlite/connection.c
    ${SRC}/Modules/_sqlite/connection.h
    ${SRC}/Modules/_sqlite/cursor.c
    ${SRC}/Modules/_sqlite/cursor.h
    ${SRC}/Modules/_sqlite/microprotocols.c
    ${SRC}/Modules/_sqlite/microprotocols.h
    ${SRC}/Modules/_sqlite/module.c
    ${SRC}/Modules/_sqlite/module.h
    ${SRC}/Modules/_sqlite/prepare_protocol.c
    ${SRC}/Modules/_sqlite/prepare_protocol.h
    ${SRC}/Modules/_sqlite/row.c
    ${SRC}/Modules/_sqlite/row.h
    ${SRC}/Modules/_sqlite/statement.c
    ${SRC}/Modules/_sqlite/statement.h
    ${SRC}/Modules/_sqlite/util.c
    ${SRC}/Modules/_sqlite/util.h
)
