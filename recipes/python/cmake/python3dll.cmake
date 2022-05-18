add_library(python3)

add_custom_command(TARGET python3 PRE_LINK COMMAND lib /nologo /def:python3stub.def /out:"lib\\python3stub.lib" /MACHINE:X64)

target_sources(python3 PRIVATE
    python3.def
    sources/PC/python3dll.c
)

target_link_libraries(python3 PRIVATE lib/python3stub)

install(TARGETS python3 RUNTIME DESTINATION .)
install(TARGETS python3 ARCHIVE DESTINATION libs)

