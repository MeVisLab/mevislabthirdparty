cmake_minimum_required(VERSION 3.14)
project(sqlite3 C)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(_UNUSED ${CMAKE_DEBUG_POSTFIX} ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY} ${CMAKE_INSTALL_BINDIR} ${CMAKE_INSTALL_DATAROOTDIR} ${CMAKE_INSTALL_INCLUDEDIR} ${CMAKE_INSTALL_LIBDIR} ${CMAKE_INSTALL_LIBEXECDIR} ${CMAKE_INSTALL_OLDINCLUDEDIR} ${CMAKE_INSTALL_SBINDIR})

add_library(sqlite3 SHARED sources/sqlite3.c sources/sqlite3.h sources/sqlite3ext.h)

if (WIN32 AND MSVC)
  set_target_properties(sqlite3 PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
endif(MSVC)

target_compile_definitions(sqlite3 PRIVATE HAVE_FDATASYNC)
target_compile_definitions(sqlite3 PRIVATE HAVE_GMTIME_R)
target_compile_definitions(sqlite3 PRIVATE HAVE_STRERROR_R)
target_compile_definitions(sqlite3 PRIVATE HAVE_USLEEP)

if(HAVE_LOCALTIME_R)
  target_compile_definitions(sqlite3 PRIVATE HAVE_LOCALTIME_R)
endif()

if(HAVE_POSIX_FALLOCATE)
  target_compile_definitions(sqlite3 PRIVATE HAVE_POSIX_FALLOCATE)
endif()


# Support multithreaded environment.
# https://www.sqlite.org/compile.html#threadsafe
target_compile_definitions(sqlite3 PRIVATE SQLITE_THREADSAFE=1)

# Support detection of misuse of SQLite API.
# https://sqlite.org/compile.html#enable_api_armor
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_API_ARMOR)

# Support column metadata functions.
# https://sqlite.org/c3ref/column_database_name.html
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_COLUMN_METADATA)

# Support sqlite_dbpage virtual table.
# https://sqlite.org/compile.html#enable_dbpage_vtab
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_DBPAGE_VTAB)

# Support dbstat virtual table.
# https://sqlite.org/dbstat.html
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_DBSTAT_VTAB)

# Support sqlite3_serialize() and sqlite3_deserialize() functions.
# https://sqlite.org/compile.html#enable_deserialize
# https://sqlite.org/c3ref/serialize.html
# https://sqlite.org/c3ref/deserialize.html
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_DESERIALIZE)

# Support comments in output of EXPLAIN.
# https://sqlite.org/compile.html#enable_explain_comments
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_EXPLAIN_COMMENTS)


# Support Full-Text Search versions 3, 4 and 5.
# https://sqlite.org/fts3.html
# https://sqlite.org/fts5.html
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_FTS3)
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_FTS3_PARENTHESIS)
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_FTS4)
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_FTS5)

# Support hidden columns.
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_HIDDEN_COLUMNS)

# Support JSON1 extension.
# https://sqlite.org/json1.html
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_JSON1)

# Support memsys5 memory allocator.
# https://sqlite.org/malloc.html#memsys5
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_MEMSYS5)

# Support sqlite3_normalized_sql() function.
# https://sqlite.org/c3ref/expanded_sql.html
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_NORMALIZE)

# Support sqlite_offset() function.
# https://sqlite.org/lang_corefunc.html#sqlite_offset
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_OFFSET_SQL_FUNC)

# Support pre-update hook functions.
# https://sqlite.org/c3ref/preupdate_count.html
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_PREUPDATE_HOOK)

# Support Resumable Bulk Update extension.
# https://sqlite.org/rbu.html
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_RBU)

# Support R*Trees.
# https://sqlite.org/rtree.html
# https://sqlite.org/geopoly.html
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_RTREE)
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_GEOPOLY)

# Support scan status functions.
# https://sqlite.org/c3ref/stmt_scanstatus.html
# https://sqlite.org/c3ref/stmt_scanstatus_reset.html
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_STMT_SCANSTATUS)

# Support sqlite_stmt virtual table.
# https://sqlite.org/stmt.html
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_STMTVTAB)

# Support Session extension.
# https://sqlite.org/sessionintro.html
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_SESSION)

# Support unlock notification.
# https://sqlite.org/unlock_notify.html
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_UNLOCK_NOTIFY)

# Support LIMIT and ORDER BY clauses on DELETE and UPDATE statements.
# https://sqlite.org/compile.html#enable_update_delete_limit
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_UPDATE_DELETE_LIMIT)

# Support PRAGMA function_list, PRAGMA module_list and PRAGMA pragma_list statements.
# https://sqlite.org/pragma.html#pragma_function_list
# https://sqlite.org/pragma.html#pragma_module_list
# https://sqlite.org/pragma.html#pragma_pragma_list
target_compile_definitions(sqlite3 PRIVATE SQLITE_INTROSPECTION_PRAGMAS)

# Support soundex() function.
# https://sqlite.org/lang_corefunc.html#soundex
target_compile_definitions(sqlite3 PRIVATE SQLITE_SOUNDEX)

# Support URI filenames.
# https://sqlite.org/uri.html
target_compile_definitions(sqlite3 PRIVATE SQLITE_USE_URI)


install(TARGETS sqlite3 RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(DIRECTORY sources/ DESTINATION include FILES_MATCHING PATTERN "*.h")
