add_pyd(_elementtree)
target_include_directories(_elementtree PRIVATE ${SRC}/Modules/expat)
target_compile_definitions(_elementtree PRIVATE HAVE_EXPAT_H XML_NS XML_DTD)
target_compile_definitions(_elementtree PRIVATE BYTEORDER=1234 XML_CONTEXT_BYTES=1024)
target_compile_definitions(_elementtree PRIVATE XML_STATIC HAVE_MEMMOVE)

target_sources(_elementtree PRIVATE
    ${SRC}/Modules/_elementtree.c
    ${SRC}/Modules/expat/xmlparse.c
    ${SRC}/Modules/expat/xmlrole.c
    ${SRC}/Modules/expat/xmltok.c
)
