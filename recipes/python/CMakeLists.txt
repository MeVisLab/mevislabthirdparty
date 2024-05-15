cmake_minimum_required(VERSION 3.27)
project(Dummy) # trigger reading the toolchain file
project(Python VERSION ${PYTHON_VERSION} LANGUAGES C CXX ASM)
enable_language(ASM_MASM)

set(CMAKE_DEBUG_POSTFIX _d)

set(SRC src)

function(add_pyd libname)
    add_library(${libname})
    set_target_properties(${libname} PROPERTIES SUFFIX ".pyd")

    target_link_libraries(${libname} PRIVATE pythoncore)
    target_compile_definitions(${libname} PRIVATE Py_BUILD_CORE_MODULE)
    target_include_directories(${libname} PRIVATE ${SRC}/PC)

    install(TARGETS ${libname} RUNTIME DESTINATION DLLs LIBRARY DESTINATION DLLs)
endfunction()

# Core:
include(cmake/_freeze_module.cmake)
include(cmake/pythoncore.cmake)
include(cmake/python3dll.cmake)
include(cmake/MeVisPython.cmake)

# Python modules:
include(cmake/pyd_bz2.cmake)
include(cmake/pyd_ctypes.cmake)
include(cmake/pyd_decimal.cmake)
include(cmake/pyd_elementtree.cmake)
include(cmake/pyd_hashlib.cmake)
include(cmake/pyd_lzma.cmake)
include(cmake/pyd_multiprocessing.cmake)
include(cmake/pyd_overlapped.cmake)
include(cmake/pyd_pyexpat.cmake)
include(cmake/pyd_select.cmake)
include(cmake/pyd_socket.cmake)
include(cmake/pyd_sqlite3.cmake)
include(cmake/pyd_ssl.cmake)
include(cmake/pyd_unicodedata.cmake)
include(cmake/pyd_winsound.cmake)
include(cmake/pyd_queue.cmake)
include(cmake/pyd_uuid.cmake)
include(cmake/pyd_zoneinfo.cmake)
