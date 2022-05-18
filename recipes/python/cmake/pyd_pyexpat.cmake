add_pyd(pyexpat)
target_include_directories(pyexpat PRIVATE sources/Modules/expat)
target_compile_definitions(pyexpat PRIVATE HAVE_EXPAT_H XML_NS XML_DTD)
target_compile_definitions(pyexpat PRIVATE BYTEORDER=1234 XML_CONTEXT_BYTES=1024)
target_compile_definitions(pyexpat PRIVATE XML_STATIC HAVE_MEMMOVE)

target_sources(pyexpat PRIVATE
    sources/Modules/pyexpat.c
    sources/Modules/expat/xmlparse.c
    sources/Modules/expat/xmlrole.c
    sources/Modules/expat/xmltok.c
)

if(CMAKE_PROJECT_VERSION VERSION_LESS 3.9)
    target_sources(pyexpat PRIVATE
        sources/Modules/expat/loadlibrary.c
    )
endif()