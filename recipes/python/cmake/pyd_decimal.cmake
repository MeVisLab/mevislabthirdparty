add_pyd(_decimal)
target_include_directories(_decimal PRIVATE ${SRC}/Modules/_decimal ${SRC}/Modules/_decimal/libmpdec)
target_compile_definitions(_decimal PRIVATE D_CRT_SECURE_NO_WARNINGS CONFIG_64)
if(NOT ARM AND NOT ARM64)
    target_compile_definitions(_decimal PRIVATE MASM)
endif()

target_sources(_decimal PRIVATE
    ${SRC}/Modules/_decimal/_decimal.c
    ${SRC}/Modules/_decimal/docstrings.h
    ${SRC}/Modules/_decimal/libmpdec/basearith.c
    ${SRC}/Modules/_decimal/libmpdec/basearith.h
    ${SRC}/Modules/_decimal/libmpdec/bits.h
    ${SRC}/Modules/_decimal/libmpdec/constants.c
    ${SRC}/Modules/_decimal/libmpdec/constants.h
    ${SRC}/Modules/_decimal/libmpdec/context.c
    ${SRC}/Modules/_decimal/libmpdec/convolute.c
    ${SRC}/Modules/_decimal/libmpdec/convolute.h
    ${SRC}/Modules/_decimal/libmpdec/crt.c
    ${SRC}/Modules/_decimal/libmpdec/crt.h
    ${SRC}/Modules/_decimal/libmpdec/difradix2.c
    ${SRC}/Modules/_decimal/libmpdec/difradix2.h
    ${SRC}/Modules/_decimal/libmpdec/fnt.c
    ${SRC}/Modules/_decimal/libmpdec/fnt.h
    ${SRC}/Modules/_decimal/libmpdec/fourstep.c
    ${SRC}/Modules/_decimal/libmpdec/fourstep.h
    ${SRC}/Modules/_decimal/libmpdec/io.c
    ${SRC}/Modules/_decimal/libmpdec/mpalloc.c
    ${SRC}/Modules/_decimal/libmpdec/mpdecimal.c
    ${SRC}/Modules/_decimal/libmpdec/mpdecimal.h
    ${SRC}/Modules/_decimal/libmpdec/numbertheory.c
    ${SRC}/Modules/_decimal/libmpdec/numbertheory.h
    ${SRC}/Modules/_decimal/libmpdec/sixstep.c
    ${SRC}/Modules/_decimal/libmpdec/sixstep.h
    ${SRC}/Modules/_decimal/libmpdec/transpose.c
    ${SRC}/Modules/_decimal/libmpdec/transpose.h
    ${SRC}/Modules/_decimal/libmpdec/typearith.h
    ${SRC}/Modules/_decimal/libmpdec/umodarith.h
    ${SRC}/Modules/_decimal/libmpdec/vcdiv64.asm
)
