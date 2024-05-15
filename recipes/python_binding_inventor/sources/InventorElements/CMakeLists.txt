add_library(InventorElements "")
set_target_properties(InventorElements PROPERTIES OUTPUT_NAME elements)

if(WIN32)
    set_target_properties(InventorElements PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(InventorElements PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(InventorElements PRIVATE
  InventorElements.cpp
  ../generated_cpp/Inventor_elements/Inventor_elements0.h
  ../generated_cpp/Inventor_elements/Inventor_elements0.cpp
  ../generated_cpp/Inventor_elements/Inventor_elements1.h
  ../generated_cpp/Inventor_elements/Inventor_elements1.cpp
  ../generated_cpp/Inventor_elements/Inventor_elements2.h
  ../generated_cpp/Inventor_elements/Inventor_elements2.cpp
  ../generated_cpp/Inventor_elements/Inventor_elements_init.cpp
)

target_link_libraries(InventorElements
  PRIVATE
    ${REQUIRED_LIBS}
)

install(TARGETS InventorElements
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)