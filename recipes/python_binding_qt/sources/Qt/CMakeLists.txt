add_library(Qt "")
set_target_properties(Qt PROPERTIES OUTPUT_NAME Qt)

if(WIN32)
    set_target_properties(Qt PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(Qt PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()


target_sources(Qt PRIVATE Qt.cpp)
target_link_libraries(Qt PRIVATE Python3::Python Threads::Threads ${CONAN_LIBS})

install(TARGETS Qt
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)


install(FILES "__init__.py.in" DESTINATION "${SITE_PACKAGE_TARGET_DIR}/PythonQt/" RENAME "__init__.py")
