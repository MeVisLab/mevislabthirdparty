add_library(InventorFields "")
set_target_properties(InventorFields PROPERTIES OUTPUT_NAME fields)

if(WIN32)
    set_target_properties(InventorFields PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(InventorFields PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(InventorFields PRIVATE
  InventorFields.cpp
  ../generated_cpp/Inventor_fields/Inventor_fields0.h
  ../generated_cpp/Inventor_fields/Inventor_fields0.cpp
  ../generated_cpp/Inventor_fields/Inventor_fields1.h
  ../generated_cpp/Inventor_fields/Inventor_fields1.cpp
  ../generated_cpp/Inventor_fields/Inventor_fields2.h
  ../generated_cpp/Inventor_fields/Inventor_fields2.cpp
  ../generated_cpp/Inventor_fields/Inventor_fields_init.cpp
)

target_link_libraries(InventorFields
  PRIVATE
    ${REQUIRED_LIBS}
)

install(TARGETS InventorFields
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)