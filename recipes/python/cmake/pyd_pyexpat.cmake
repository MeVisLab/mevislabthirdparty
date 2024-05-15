add_pyd(pyexpat)
target_include_directories(pyexpat PRIVATE ${SRC}/Modules/expat)
target_compile_definitions(pyexpat PRIVATE XML_NS XML_DTD)
target_compile_definitions(pyexpat PRIVATE BYTEORDER=1234 XML_CONTEXT_BYTES=1024)
target_compile_definitions(pyexpat PRIVATE XML_STATIC HAVE_MEMMOVE)

target_sources(pyexpat PRIVATE
    ${SRC}/Modules/expat/xmlparse.c
    ${SRC}/Modules/expat/xmlrole.c
    ${SRC}/Modules/expat/xmltok.c
    ${SRC}/Modules/pyexpat.c
)
