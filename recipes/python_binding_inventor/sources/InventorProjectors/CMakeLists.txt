add_library(InventorProjectors "")
set_target_properties(InventorProjectors PROPERTIES OUTPUT_NAME projectors)

if(WIN32)
    set_target_properties(InventorProjectors PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(InventorProjectors PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(InventorProjectors PRIVATE
  InventorProjectors.cpp
  ../generated_cpp/Inventor_projectors/Inventor_projectors0.h
  ../generated_cpp/Inventor_projectors/Inventor_projectors0.cpp
  ../generated_cpp/Inventor_projectors/Inventor_projectors_init.cpp
)

target_link_libraries(InventorProjectors
  PRIVATE
    ${REQUIRED_LIBS}
)

install(TARGETS InventorProjectors
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)