add_pyd(_elementtree)
target_include_directories(_elementtree PRIVATE sources/Modules/expat)
target_compile_definitions(_elementtree PRIVATE HAVE_EXPAT_H XML_NS XML_DTD)
target_compile_definitions(_elementtree PRIVATE BYTEORDER=1234 XML_CONTEXT_BYTES=1024)
target_compile_definitions(_elementtree PRIVATE USE_PYEXPAT_CAPI XML_STATIC HAVE_MEMMOVE)

target_sources(_elementtree PRIVATE
    sources/Modules/_elementtree.c
    sources/Modules/expat/xmlparse.c
    sources/Modules/expat/xmlrole.c
    sources/Modules/expat/xmltok.c
)

if(CMAKE_PROJECT_VERSION VERSION_LESS 3.9)
    target_sources(_elementtree PRIVATE
        sources/Modules/expat/loadlibrary.c
    )
endif()
