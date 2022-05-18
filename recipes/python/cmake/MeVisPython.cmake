add_executable(MeVisPython)
set_target_properties(MeVisPython PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

target_sources(MeVisPython PRIVATE
    sources/Programs/python.c
    cmake/ManifestFragment.manifest
)

set_property(TARGET MeVisPython PROPERTY LINK_OPTIONS /STACK:3000000)
set_target_properties(MeVisPython PROPERTIES WIN32_EXECUTABLE FALSE)

target_include_directories(MeVisPython PRIVATE sources/Python sources/PC)
target_compile_definitions(MeVisPython PRIVATE Py_BUILD_CORE)
target_link_libraries(MeVisPython PRIVATE pythoncore)

install(TARGETS MeVisPython DESTINATION .)

# ----

if(WIN32)
    add_executable(MeVisPythonW)
    set_target_properties(MeVisPythonW PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

    target_sources(MeVisPythonW PRIVATE
        sources/PC/WinMain.c
        cmake/ManifestFragment.manifest
    )

    set_property(TARGET MeVisPythonW PROPERTY LINK_OPTIONS /STACK:3000000)
    set_target_properties(MeVisPythonW PROPERTIES WIN32_EXECUTABLE TRUE)

    target_include_directories(MeVisPythonW PRIVATE sources/Python sources/PC)
    target_compile_definitions(MeVisPythonW PRIVATE Py_BUILD_CORE)
    target_link_libraries(MeVisPythonW PRIVATE pythoncore)

    install(TARGETS MeVisPythonW DESTINATION .)
endif()
