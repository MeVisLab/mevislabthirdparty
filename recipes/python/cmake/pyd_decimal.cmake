add_pyd(_decimal)
target_include_directories(_decimal PRIVATE sources/Modules/_decimal sources/Modules/_decimal/libmpdec)
target_compile_definitions(_decimal PRIVATE D_CRT_SECURE_NO_WARNINGS MASM CONFIG_64)

target_sources(_decimal PRIVATE
    sources/Modules/_decimal/_decimal.c
    sources/Modules/_decimal/docstrings.h
    sources/Modules/_decimal/libmpdec/basearith.c
    sources/Modules/_decimal/libmpdec/basearith.h
    sources/Modules/_decimal/libmpdec/bits.h
    sources/Modules/_decimal/libmpdec/constants.c
    sources/Modules/_decimal/libmpdec/constants.h
    sources/Modules/_decimal/libmpdec/context.c
    sources/Modules/_decimal/libmpdec/convolute.c
    sources/Modules/_decimal/libmpdec/convolute.h
    sources/Modules/_decimal/libmpdec/crt.c
    sources/Modules/_decimal/libmpdec/crt.h
    sources/Modules/_decimal/libmpdec/difradix2.c
    sources/Modules/_decimal/libmpdec/difradix2.h
    sources/Modules/_decimal/libmpdec/fnt.c
    sources/Modules/_decimal/libmpdec/fnt.h
    sources/Modules/_decimal/libmpdec/fourstep.c
    sources/Modules/_decimal/libmpdec/fourstep.h
    sources/Modules/_decimal/libmpdec/io.c
    sources/Modules/_decimal/libmpdec/mpalloc.c
    sources/Modules/_decimal/libmpdec/mpdecimal.c
    sources/Modules/_decimal/libmpdec/mpdecimal.h
    sources/Modules/_decimal/libmpdec/numbertheory.c
    sources/Modules/_decimal/libmpdec/numbertheory.h
    sources/Modules/_decimal/libmpdec/sixstep.c
    sources/Modules/_decimal/libmpdec/sixstep.h
    sources/Modules/_decimal/libmpdec/transpose.c
    sources/Modules/_decimal/libmpdec/transpose.h
    sources/Modules/_decimal/libmpdec/typearith.h
    sources/Modules/_decimal/libmpdec/umodarith.h
    sources/Modules/_decimal/libmpdec/vccompat.h
    sources/Modules/_decimal/libmpdec/vcdiv64.asm
)
