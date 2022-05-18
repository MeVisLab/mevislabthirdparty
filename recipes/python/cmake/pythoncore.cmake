add_library(pythoncore)
set_target_properties(pythoncore PROPERTIES OUTPUT_NAME "python${CMAKE_PROJECT_VERSION_MAJOR}${CMAKE_PROJECT_VERSION_MINOR}")

target_link_libraries(pythoncore PRIVATE Advapi32.lib shell32.lib User32.lib ws2_32.lib shlwapi.lib version.lib)

target_include_directories(pythoncore PRIVATE sources/Python sources/Modules/zlib sources/PC)
target_include_directories(pythoncore PUBLIC sources/Include)

target_link_directories(pythoncore PRIVATE sources/PC/external/v141/amd64)


target_compile_definitions(pythoncore PRIVATE _USRDLL)
target_compile_definitions(pythoncore PRIVATE Py_BUILD_CORE)
target_compile_definitions(pythoncore PRIVATE Py_BUILD_CORE_BUILTIN)
target_compile_definitions(pythoncore PRIVATE Py_ENABLE_SHARED)
target_compile_definitions(pythoncore PRIVATE NDEBUG)
target_compile_definitions(pythoncore PRIVATE _WIN64)
target_compile_definitions(pythoncore PRIVATE _M_X64)
target_compile_definitions(pythoncore PRIVATE _WINDLL)
target_compile_definitions(pythoncore PRIVATE MS_DLL_ID=\"${CMAKE_PROJECT_VERSION}\")
target_compile_definitions(pythoncore PRIVATE PY3_DLLNAME=L\"python3${CMAKE_DEBUG_POSTFIX}\")
message(PY3_DLLNAME=python3${CMAKE_DEBUG_POSTFIX})


target_sources(pythoncore PRIVATE
    sources/Modules/_bisectmodule.c
    sources/Modules/_blake2/blake2b_impl.c
    sources/Modules/_blake2/blake2module.c
    sources/Modules/_blake2/blake2s_impl.c
    sources/Modules/_codecsmodule.c
    sources/Modules/_collectionsmodule.c
    sources/Modules/_csv.c
    sources/Modules/_datetimemodule.c
    sources/Modules/_functoolsmodule.c
    sources/Modules/_heapqmodule.c
    sources/Modules/_io/_iomodule.c
    sources/Modules/_io/bufferedio.c
    sources/Modules/_io/bytesio.c
    sources/Modules/_io/fileio.c
    sources/Modules/_io/iobase.c
    sources/Modules/_io/stringio.c
    sources/Modules/_io/textio.c
    sources/Modules/_io/winconsoleio.c
    sources/Modules/_json.c
    sources/Modules/_localemodule.c
    sources/Modules/_lsprof.c
    sources/Modules/_math.c
    sources/Modules/_opcode.c
    sources/Modules/_operator.c
    sources/Modules/_pickle.c
    sources/Modules/_randommodule.c
    sources/Modules/_sha3/sha3module.c
    sources/Modules/_sre.c
    sources/Modules/_stat.c
    sources/Modules/_struct.c
    sources/Modules/_threadmodule.c
    sources/Modules/_tracemalloc.c
    sources/Modules/_weakref.c
    sources/Modules/_winapi.c
    sources/Modules/arraymodule.c
    sources/Modules/atexitmodule.c
    sources/Modules/audioop.c
    sources/Modules/binascii.c
    sources/Modules/cjkcodecs/_codecs_cn.c
    sources/Modules/cjkcodecs/_codecs_hk.c
    sources/Modules/cjkcodecs/_codecs_iso2022.c
    sources/Modules/cjkcodecs/_codecs_jp.c
    sources/Modules/cjkcodecs/_codecs_kr.c
    sources/Modules/cjkcodecs/_codecs_tw.c
    sources/Modules/cjkcodecs/multibytecodec.c
    sources/Modules/cmathmodule.c
    sources/Modules/errnomodule.c
    sources/Modules/faulthandler.c
    sources/Modules/gcmodule.c
    sources/Modules/getbuildinfo.c
    sources/Modules/itertoolsmodule.c
    sources/Modules/main.c
    sources/Modules/mathmodule.c
    sources/Modules/md5module.c
    sources/Modules/mmapmodule.c
    sources/Modules/parsermodule.c
    sources/Modules/posixmodule.c
    sources/Modules/rotatingtree.c
    sources/Modules/sha1module.c
    sources/Modules/sha256module.c
    sources/Modules/sha512module.c
    sources/Modules/signalmodule.c
    sources/Modules/symtablemodule.c
    sources/Modules/timemodule.c
    sources/Modules/xxsubtype.c
    sources/Modules/zlibmodule.c
    sources/Objects/abstract.c
    sources/Objects/accu.c
    sources/Objects/boolobject.c
    sources/Objects/bytearrayobject.c
    sources/Objects/bytes_methods.c
    sources/Objects/bytesobject.c
    sources/Objects/capsule.c
    sources/Objects/cellobject.c
    sources/Objects/classobject.c
    sources/Objects/codeobject.c
    sources/Objects/complexobject.c
    sources/Objects/descrobject.c
    sources/Objects/dictobject.c
    sources/Objects/enumobject.c
    sources/Objects/exceptions.c
    sources/Objects/fileobject.c
    sources/Objects/floatobject.c
    sources/Objects/frameobject.c
    sources/Objects/funcobject.c
    sources/Objects/genobject.c
    sources/Objects/iterobject.c
    sources/Objects/listobject.c
    sources/Objects/longobject.c
    sources/Objects/memoryobject.c
    sources/Objects/methodobject.c
    sources/Objects/moduleobject.c
    sources/Objects/namespaceobject.c
    sources/Objects/object.c
    sources/Objects/obmalloc.c
    sources/Objects/odictobject.c
    sources/Objects/rangeobject.c
    sources/Objects/setobject.c
    sources/Objects/sliceobject.c
    sources/Objects/structseq.c
    sources/Objects/tupleobject.c
    sources/Objects/typeobject.c
    sources/Objects/unicodectype.c
    sources/Objects/unicodeobject.c
    sources/Objects/weakrefobject.c
    sources/PC/config.c
    sources/PC/dl_nt.c
    sources/PC/getpathp.c
    sources/PC/invalid_parameter_handler.c
    sources/PC/msvcrtmodule.c
    sources/PC/winreg.c
    sources/Parser/acceler.c
    sources/Parser/grammar1.c
    sources/Parser/listnode.c
    sources/Parser/myreadline.c
    sources/Parser/node.c
    sources/Parser/parser.c
    sources/Parser/parsetok.c
    sources/Parser/tokenizer.c
    sources/Python/Python-ast.c
    sources/Python/_warnings.c
    sources/Python/asdl.c
    sources/Python/ast.c
    sources/Python/bltinmodule.c
    sources/Python/ceval.c
    sources/Python/codecs.c
    sources/Python/compile.c
    sources/Python/dtoa.c
    sources/Python/dynamic_annotations.c
    sources/Python/dynload_win.c
    sources/Python/errors.c
    sources/Python/fileutils.c
    sources/Python/formatter_unicode.c
    sources/Python/frozen.c
    sources/Python/future.c
    sources/Python/getargs.c
    sources/Python/getcompiler.c
    sources/Python/getcopyright.c
    sources/Python/getopt.c
    sources/Python/getplatform.c
    sources/Python/getversion.c
    sources/Python/graminit.c
    sources/Python/import.c
    sources/Python/importdl.c
    sources/Python/marshal.c
    sources/Python/modsupport.c
    sources/Python/mysnprintf.c
    sources/Python/mystrtoul.c
    sources/Python/peephole.c
    sources/Python/pyarena.c
    sources/Python/pyctype.c
    sources/Python/pyfpe.c
    sources/Python/pyhash.c
    sources/Python/pylifecycle.c
    sources/Python/pymath.c
    sources/Python/pystate.c
    sources/Python/pystrcmp.c
    sources/Python/pystrhex.c
    sources/Python/pystrtod.c
    sources/Python/pythonrun.c
    sources/Python/pytime.c
    sources/Python/structmember.c
    sources/Python/symtable.c
    sources/Python/sysmodule.c
    sources/Python/thread.c
    sources/Python/traceback.c
)

if(CMAKE_PROJECT_VERSION VERSION_GREATER_EQUAL 3.9)
    target_link_libraries(pythoncore PRIVATE CONAN_PKG::ZLIB)
    target_compile_definitions(pythoncore PRIVATE _Py_HAVE_ZLIB)
    target_link_libraries(pythoncore PRIVATE pathcch.lib)
    target_include_directories(pythoncore PUBLIC sources/Include/internal)
    target_sources(pythoncore PRIVATE
        sources/Modules/_abc.c
        sources/Modules/_contextvarsmodule.c
        sources/Modules/_functoolsmodule.c
        sources/Modules/_peg_parser.c
        sources/Modules/_statisticsmodule.c
        sources/Modules/_xxsubinterpretersmodule.c
        sources/Objects/call.c
        sources/Objects/genericaliasobject.c
        sources/Objects/interpreteridobject.c
        sources/Objects/picklebufobject.c
        sources/Parser/token.c
        sources/Parser/pegen/pegen.c
        sources/Parser/pegen/parse.c
        sources/Parser/pegen/parse_string.c
        sources/Parser/pegen/peg_api.c
        sources/Python/ast_opt.c
        sources/Python/ast_unparse.c
        sources/Python/bootstrap_hash.c
        sources/Python/context.c
        sources/Python/hamt.c
        sources/Python/hashtable.c
        sources/Python/initconfig.c
        sources/Python/pathconfig.c
        sources/Python/preconfig.c

    )
else()
    target_sources(pythoncore PRIVATE
        sources/Modules/_asynciomodule.c
        sources/Modules/hashtable.c
        sources/Modules/zipimport.c
        sources/Modules/zlib/adler32.c
        sources/Modules/zlib/compress.c
        sources/Modules/zlib/crc32.c
        sources/Modules/zlib/deflate.c
        sources/Modules/zlib/infback.c
        sources/Modules/zlib/inffast.c
        sources/Modules/zlib/inflate.c
        sources/Modules/zlib/inftrees.c
        sources/Modules/zlib/trees.c
        sources/Modules/zlib/uncompr.c
        sources/Modules/zlib/zutil.c
        sources/PC/_findvs.cpp
        sources/Parser/bitset.c
        sources/Parser/firstsets.c
        sources/Parser/grammar.c
        sources/Parser/metagrammar.c
        sources/Python/random.c
    )
endif()

install(TARGETS pythoncore RUNTIME DESTINATION .)
install(TARGETS pythoncore ARCHIVE DESTINATION libs)
install(DIRECTORY sources/Include/ DESTINATION Include)
install(DIRECTORY sources/Lib/ DESTINATION Lib)
install(FILES sources/PC/pyconfig.h DESTINATION Include/)
