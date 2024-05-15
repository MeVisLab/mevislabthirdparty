add_library(InventorActions "")
set_target_properties(InventorActions PROPERTIES OUTPUT_NAME actions)

if(WIN32)
    set_target_properties(InventorActions PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(InventorActions PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(InventorActions PRIVATE
  InventorActions.cpp
  ../generated_cpp/Inventor_actions/Inventor_actions0.h
  ../generated_cpp/Inventor_actions/Inventor_actions0.cpp
  ../generated_cpp/Inventor_actions/Inventor_actions_init.cpp
)

target_link_libraries(InventorActions
  PRIVATE
    ${REQUIRED_LIBS}
)

install(TARGETS InventorActions
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)