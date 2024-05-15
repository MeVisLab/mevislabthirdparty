add_library(python3)

target_compile_definitions(python3 PRIVATE PYTHON_DLL_NAME="\\\"$<TARGET_FILE_BASE_NAME:pythoncore>\\\"")

target_sources(python3 PRIVATE
    ${SRC}/PC/python3dll.c
)

install(TARGETS python3 RUNTIME DESTINATION .)
install(TARGETS python3 ARCHIVE DESTINATION libs)
