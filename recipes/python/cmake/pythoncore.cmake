add_library(pythoncore)

find_package(ZLIB REQUIRED)

set_target_properties(pythoncore PROPERTIES OUTPUT_NAME "python${CMAKE_PROJECT_VERSION_MAJOR}${CMAKE_PROJECT_VERSION_MINOR}")

target_link_libraries(pythoncore PRIVATE Advapi32.lib shell32.lib User32.lib ws2_32.lib shlwapi.lib version.lib)

target_include_directories(pythoncore PRIVATE ${SRC}/Python ${SRC}/Modules/zlib ${SRC}/PC)
target_include_directories(pythoncore PUBLIC ${SRC}/Include)

target_link_directories(pythoncore PRIVATE ${SRC}/PC/external/v141/amd64)


target_compile_definitions(pythoncore PRIVATE _USRDLL)
target_compile_definitions(pythoncore PRIVATE Py_BUILD_CORE)
target_compile_definitions(pythoncore PRIVATE Py_BUILD_CORE_BUILTIN)
target_compile_definitions(pythoncore PRIVATE Py_ENABLE_SHARED)
target_compile_definitions(pythoncore PRIVATE NDEBUG)
target_compile_definitions(pythoncore PRIVATE _WIN64)
target_compile_definitions(pythoncore PRIVATE _M_X64)
target_compile_definitions(pythoncore PRIVATE _WINDLL)
target_compile_definitions(pythoncore PRIVATE VPATH=\"$(PyVPath)\")
target_compile_definitions(pythoncore PRIVATE MS_DLL_ID=\"${CMAKE_PROJECT_VERSION}\")
target_compile_definitions(pythoncore PRIVATE PY3_DLLNAME=L\"python3$<$<CONFIG:Debug>:${CMAKE_DEBUG_POSTFIX}>\")
message(PY3_DLLNAME=python3${CMAKE_DEBUG_POSTFIX})

target_sources(pythoncore PRIVATE
    ${SRC}/Modules/_abc.c
    ${SRC}/Modules/_bisectmodule.c
    ${SRC}/Modules/_blake2/blake2b_impl.c
    ${SRC}/Modules/_blake2/blake2module.c
    ${SRC}/Modules/_blake2/blake2s_impl.c
    ${SRC}/Modules/_codecsmodule.c
    ${SRC}/Modules/_collectionsmodule.c
    ${SRC}/Modules/_contextvarsmodule.c
    ${SRC}/Modules/_csv.c
    ${SRC}/Modules/_datetimemodule.c
    ${SRC}/Modules/_functoolsmodule.c
    ${SRC}/Modules/_functoolsmodule.c
    ${SRC}/Modules/_heapqmodule.c
    ${SRC}/Modules/_io/_iomodule.c
    ${SRC}/Modules/_io/bufferedio.c
    ${SRC}/Modules/_io/bytesio.c
    ${SRC}/Modules/_io/fileio.c
    ${SRC}/Modules/_io/iobase.c
    ${SRC}/Modules/_io/stringio.c
    ${SRC}/Modules/_io/textio.c
    ${SRC}/Modules/_io/winconsoleio.c
    ${SRC}/Modules/_json.c
    ${SRC}/Modules/_localemodule.c
    ${SRC}/Modules/_lsprof.c
    ${SRC}/Modules/_opcode.c
    ${SRC}/Modules/_operator.c
    ${SRC}/Modules/_pickle.c
    ${SRC}/Modules/_randommodule.c
    ${SRC}/Modules/_sha3/sha3module.c
    ${SRC}/Modules/_sre/sre.c
    ${SRC}/Modules/_stat.c
    ${SRC}/Modules/_statisticsmodule.c
    ${SRC}/Modules/_struct.c
    ${SRC}/Modules/_threadmodule.c
    ${SRC}/Modules/_tracemalloc.c
    ${SRC}/Modules/_typingmodule.c
    ${SRC}/Modules/_weakref.c
    ${SRC}/Modules/_winapi.c
    ${SRC}/Modules/_xxsubinterpretersmodule.c
    ${SRC}/Modules/arraymodule.c
    ${SRC}/Modules/atexitmodule.c
    ${SRC}/Modules/audioop.c
    ${SRC}/Modules/binascii.c
    ${SRC}/Modules/cjkcodecs/_codecs_cn.c
    ${SRC}/Modules/cjkcodecs/_codecs_hk.c
    ${SRC}/Modules/cjkcodecs/_codecs_iso2022.c
    ${SRC}/Modules/cjkcodecs/_codecs_jp.c
    ${SRC}/Modules/cjkcodecs/_codecs_kr.c
    ${SRC}/Modules/cjkcodecs/_codecs_tw.c
    ${SRC}/Modules/cjkcodecs/multibytecodec.c
    ${SRC}/Modules/cmathmodule.c
    ${SRC}/Modules/errnomodule.c
    ${SRC}/Modules/faulthandler.c
    ${SRC}/Modules/gcmodule.c
    ${SRC}/Modules/getpath.c  # generated
    ${SRC}/Modules/getbuildinfo.c
    ${SRC}/Modules/itertoolsmodule.c
    ${SRC}/Modules/main.c
    ${SRC}/Modules/mathmodule.c
    ${SRC}/Modules/md5module.c
    ${SRC}/Modules/mmapmodule.c
    ${SRC}/Modules/posixmodule.c
    ${SRC}/Modules/rotatingtree.c
    ${SRC}/Modules/sha1module.c
    ${SRC}/Modules/sha256module.c
    ${SRC}/Modules/sha512module.c
    ${SRC}/Modules/signalmodule.c
    ${SRC}/Modules/symtablemodule.c
    ${SRC}/Modules/timemodule.c
    ${SRC}/Modules/xxsubtype.c
    ${SRC}/Modules/zlibmodule.c
    ${SRC}/Objects/abstract.c
    ${SRC}/Objects/accu.c
    ${SRC}/Objects/boolobject.c
    ${SRC}/Objects/bytearrayobject.c
    ${SRC}/Objects/bytes_methods.c
    ${SRC}/Objects/bytesobject.c
    ${SRC}/Objects/call.c
    ${SRC}/Objects/capsule.c
    ${SRC}/Objects/cellobject.c
    ${SRC}/Objects/classobject.c
    ${SRC}/Objects/codeobject.c
    ${SRC}/Objects/complexobject.c
    ${SRC}/Objects/descrobject.c
    ${SRC}/Objects/dictobject.c
    ${SRC}/Objects/enumobject.c
    ${SRC}/Objects/exceptions.c
    ${SRC}/Objects/fileobject.c
    ${SRC}/Objects/floatobject.c
    ${SRC}/Objects/frameobject.c
    ${SRC}/Objects/funcobject.c
    ${SRC}/Objects/genericaliasobject.c
    ${SRC}/Objects/genobject.c
    ${SRC}/Objects/interpreteridobject.c
    ${SRC}/Objects/iterobject.c
    ${SRC}/Objects/listobject.c
    ${SRC}/Objects/longobject.c
    ${SRC}/Objects/memoryobject.c
    ${SRC}/Objects/methodobject.c
    ${SRC}/Objects/moduleobject.c
    ${SRC}/Objects/namespaceobject.c
    ${SRC}/Objects/object.c
    ${SRC}/Objects/obmalloc.c
    ${SRC}/Objects/odictobject.c
    ${SRC}/Objects/picklebufobject.c
    ${SRC}/Objects/rangeobject.c
    ${SRC}/Objects/setobject.c
    ${SRC}/Objects/sliceobject.c
    ${SRC}/Objects/structseq.c
    ${SRC}/Objects/tupleobject.c
    ${SRC}/Objects/typeobject.c
    ${SRC}/Objects/unicodectype.c
    ${SRC}/Objects/unicodeobject.c
    ${SRC}/Objects/unionobject.c
    ${SRC}/Objects/weakrefobject.c
    ${SRC}/Parser/action_helpers.c
    ${SRC}/Parser/myreadline.c
    ${SRC}/Parser/parser.c
    ${SRC}/Parser/peg_api.c
    ${SRC}/Parser/pegen.c
    ${SRC}/Parser/pegen_errors.c
    ${SRC}/Parser/string_parser.c
    ${SRC}/Parser/token.c
    ${SRC}/Parser/tokenizer.c
    ${SRC}/PC/config.c
    ${SRC}/PC/dl_nt.c
    ${SRC}/PC/invalid_parameter_handler.c
    ${SRC}/PC/msvcrtmodule.c
    ${SRC}/PC/winreg.c
    ${SRC}/Python/_warnings.c
    ${SRC}/Python/asdl.c
    ${SRC}/Python/ast_opt.c
    ${SRC}/Python/ast_unparse.c
    ${SRC}/Python/ast.c
    ${SRC}/Python/bltinmodule.c
    ${SRC}/Python/bootstrap_hash.c
    ${SRC}/Python/ceval.c
    ${SRC}/Python/codecs.c
    ${SRC}/Python/compile.c
    ${SRC}/Python/context.c
    ${SRC}/Python/deepfreeze/deepfreeze.c   # autogenerated
    ${SRC}/Python/dtoa.c
    ${SRC}/Python/dynamic_annotations.c
    ${SRC}/Python/dynload_win.c
    ${SRC}/Python/errors.c
    ${SRC}/Python/fileutils.c
    ${SRC}/Python/formatter_unicode.c
    ${SRC}/Python/frame.c
    ${SRC}/Python/frozen.c
    ${SRC}/Python/future.c
    ${SRC}/Python/getargs.c
    ${SRC}/Python/getcompiler.c
    ${SRC}/Python/getcopyright.c
    ${SRC}/Python/getopt.c
    ${SRC}/Python/getplatform.c
    ${SRC}/Python/getversion.c
    ${SRC}/Python/hamt.c
    ${SRC}/Python/hashtable.c
    ${SRC}/Python/import.c
    ${SRC}/Python/importdl.c
    ${SRC}/Python/initconfig.c
    ${SRC}/Python/marshal.c
    ${SRC}/Python/modsupport.c
    ${SRC}/Python/mysnprintf.c
    ${SRC}/Python/mystrtoul.c
    ${SRC}/Python/pathconfig.c
    ${SRC}/Python/preconfig.c
    ${SRC}/Python/pyarena.c
    ${SRC}/Python/pyctype.c
    ${SRC}/Python/pyfpe.c
    ${SRC}/Python/pyhash.c
    ${SRC}/Python/pylifecycle.c
    ${SRC}/Python/pymath.c
    ${SRC}/Python/pystate.c
    ${SRC}/Python/pystrcmp.c
    ${SRC}/Python/pystrhex.c
    ${SRC}/Python/pystrtod.c
    ${SRC}/Python/Python-ast.c
    ${SRC}/Python/Python-tokenize.c
    ${SRC}/Python/pythonrun.c
    ${SRC}/Python/pytime.c
    ${SRC}/Python/specialize.c
    ${SRC}/Python/structmember.c
    ${SRC}/Python/suggestions.c
    ${SRC}/Python/symtable.c
    ${SRC}/Python/sysmodule.c
    ${SRC}/Python/thread.c
    ${SRC}/Python/traceback.c
)

set_source_files_properties(${SRC}/Modules/binascii.c PROPERTIES COMPILE_DEFINITIONS USE_ZLIB_CRC32)
set_source_files_properties(${SRC}/Modules/getpath.c PROPERTIES COMPILE_DEFINITIONS "PREFIX=NULL;EXEC_PREFIX=NULL;VERSION=NULL;PYDEBUGEXT=\"${CMAKE_DEBUG_POSTFIX}\";PLATLIBDIR=\"DLLs\"")

target_link_libraries(pythoncore PRIVATE ZLIB::ZLIB)
target_compile_definitions(pythoncore PRIVATE _Py_HAVE_ZLIB)
target_link_libraries(pythoncore PRIVATE pathcch.lib bcrypt.lib)
target_include_directories(pythoncore PUBLIC ${SRC}/Include/internal)

install(TARGETS pythoncore RUNTIME DESTINATION .)
install(TARGETS pythoncore ARCHIVE DESTINATION libs)
install(DIRECTORY ${SRC}/Include/ DESTINATION Include)
install(DIRECTORY ${SRC}/Lib/ DESTINATION Lib)
install(FILES ${SRC}/PC/pyconfig.h DESTINATION Include/)
