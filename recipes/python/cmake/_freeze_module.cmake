add_executable(_freeze_module)
target_include_directories(_freeze_module PRIVATE ${SRC}/Include ${SRC}/Include/internal ${SRC}/PC)
target_compile_definitions(_freeze_module PRIVATE Py_NO_ENABLE_SHARED Py_BUILD_CORE _CONSOLE)
target_compile_definitions(_freeze_module PRIVATE VPATH=\"$(PyVPath)\")
target_compile_definitions(_freeze_module PRIVATE PY3_DLLNAME=L\"python3$<$<CONFIG:Debug>:${CMAKE_DEBUG_POSTFIX}>\")
target_link_libraries(_freeze_module PRIVATE version.lib ws2_32.lib pathcch.lib bcrypt.lib)

target_sources(_freeze_module PRIVATE
    ${SRC}/Programs/_freeze_module.c
    ${SRC}/PC/config_minimal.c
    ${SRC}/Modules/atexitmodule.c
    ${SRC}/Modules/faulthandler.c
    ${SRC}/Modules/gcmodule.c
    ${SRC}/Modules/getbuildinfo.c
    ${SRC}/Modules/getpath_noop.c
    ${SRC}/Modules/posixmodule.c
    ${SRC}/Modules/signalmodule.c
    ${SRC}/Modules/_tracemalloc.c
    ${SRC}/Modules/_io/_iomodule.c
    ${SRC}/Modules/_io/bufferedio.c
    ${SRC}/Modules/_io/bytesio.c
    ${SRC}/Modules/_io/fileio.c
    ${SRC}/Modules/_io/iobase.c
    ${SRC}/Modules/_io/stringio.c
    ${SRC}/Modules/_io/textio.c
    ${SRC}/Modules/_io/winconsoleio.c
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
    ${SRC}/Parser/myreadline.c
    ${SRC}/Parser/parser.c
    ${SRC}/Parser/peg_api.c
    ${SRC}/Parser/pegen.c
    ${SRC}/Parser/pegen_errors.c
    ${SRC}/Parser/action_helpers.c
    ${SRC}/Parser/string_parser.c
    ${SRC}/Parser/token.c
    ${SRC}/Parser/tokenizer.c
    ${SRC}/PC/invalid_parameter_handler.c
    ${SRC}/PC/msvcrtmodule.c
    ${SRC}/PC/winreg.c
    ${SRC}/Python/_warnings.c
    ${SRC}/Python/asdl.c
    ${SRC}/Python/ast.c
    ${SRC}/Python/ast_opt.c
    ${SRC}/Python/ast_unparse.c
    ${SRC}/Python/bltinmodule.c
    ${SRC}/Python/bootstrap_hash.c
    ${SRC}/Python/ceval.c
    ${SRC}/Python/codecs.c
    ${SRC}/Python/compile.c
    ${SRC}/Python/context.c
    ${SRC}/Python/dtoa.c
    ${SRC}/Python/dynamic_annotations.c
    ${SRC}/Python/dynload_win.c
    ${SRC}/Python/errors.c
    ${SRC}/Python/fileutils.c
    ${SRC}/Python/formatter_unicode.c
    ${SRC}/Python/frame.c
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
    ${SRC}/Python/pythonrun.c
    ${SRC}/Python/Python-tokenize.c
    ${SRC}/Python/pytime.c
    ${SRC}/Python/specialize.c
    ${SRC}/Python/structmember.c
    ${SRC}/Python/suggestions.c
    ${SRC}/Python/symtable.c
    ${SRC}/Python/sysmodule.c
    ${SRC}/Python/thread.c
    ${SRC}/Python/traceback.c)

set(frozen_module_names
    importlib._bootstrap
    importlib._bootstrap_external
    zipimport
    abc
    codecs
    io
    _collections_abc
    _sitebuiltins
    genericpath
    ntpath
    posixpath
    os
    site
    stat
    importlib.util
    importlib.machinery
    runpy
    __hello__
    __phello__
    __phello__.ham
    __phello__.ham.eggs
    __phello__.spam
    frozen_only
    getpath)

set(frozen_module_paths
    ${SRC}/Lib/importlib/_bootstrap.py
    ${SRC}/Lib/importlib/_bootstrap_external.py
    ${SRC}/Lib/zipimport.py
    ${SRC}/Lib/abc.py
    ${SRC}/Lib/codecs.py
    ${SRC}/Lib/io.py
    ${SRC}/Lib/_collections_abc.py
    ${SRC}/Lib/_sitebuiltins.py
    ${SRC}/Lib/genericpath.py
    ${SRC}/Lib/ntpath.py
    ${SRC}/Lib/posixpath.py
    ${SRC}/Lib/os.py
    ${SRC}/Lib/site.py
    ${SRC}/Lib/stat.py
    ${SRC}/Lib/importlib/util.py
    ${SRC}/Lib/importlib/machinery.py
    ${SRC}/Lib/runpy.py
    ${SRC}/Lib/__hello__.py
    ${SRC}/Lib/__phello__/__init__.py
    ${SRC}/Lib/__phello__/ham/__init__.py
    ${SRC}/Lib/__phello__/ham/eggs.py
    ${SRC}/Lib/__phello__/spam.py
    ${SRC}/Tools/freeze/flag.py
    ${SRC}/Modules/getpath.py)

foreach (module_name module_path IN ZIP_LISTS frozen_module_names frozen_module_paths)
    set(out_file ${CMAKE_SOURCE_DIR}/${SRC}/Python/frozen_modules/${module_name}.h)
    add_custom_command(OUTPUT ${out_file}
        DEPENDS _freeze_module
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMAND _freeze_module ${module_name} ${module_path} ${SRC}/Python/frozen_modules/${module_name}.h)
    list(APPEND frozen_module_files ${out_file})
    list(APPEND frozen_module_args ${SRC}/Python/frozen_modules/${module_name}.h:${module_name})
endforeach ()

add_custom_command(
    OUTPUT ${CMAKE_SOURCE_DIR}/${SRC}/Python/deepfreeze/deepfreeze.c
    DEPENDS ${frozen_module_files}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND python ${SRC}/Tools/scripts/deepfreeze.py
    ${frozen_module_args}
    -o ${SRC}/Python/deepfreeze/deepfreeze.c
)
