add_library(InventorBase "")
set_target_properties(InventorBase PROPERTIES OUTPUT_NAME base)

if(WIN32)
    set_target_properties(InventorBase PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(InventorBase PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(InventorBase PRIVATE
  InventorBase.h
  InventorBase.cpp
  ../generated_cpp/inventor_base/inventor_base0.h
  ../generated_cpp/inventor_base/inventor_base0.cpp
  ../generated_cpp/inventor_base/inventor_base_init.cpp
)

target_link_libraries(InventorBase
  PRIVATE
    ${REQUIRED_LIBS}
    Python3::NumPy
)

install(TARGETS InventorBase
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)

install(FILES "__init__.py.in" DESTINATION "${SITE_PACKAGE_TARGET_DIR}/Inventor/" RENAME "__init__.py")
