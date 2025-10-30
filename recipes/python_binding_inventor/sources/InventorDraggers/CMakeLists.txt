add_library(InventorDraggers "")
set_target_properties(InventorDraggers PROPERTIES OUTPUT_NAME draggers)

if(WIN32)
    set_target_properties(InventorDraggers PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(InventorDraggers PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(InventorDraggers PRIVATE
  InventorDraggers.h
  InventorDraggers.cpp
  ../generated_cpp/inventor_draggers/inventor_draggers0.h
  ../generated_cpp/inventor_draggers/inventor_draggers0.cpp
  ../generated_cpp/inventor_draggers/inventor_draggers_init.cpp
)

target_link_libraries(InventorDraggers
  PRIVATE
    ${REQUIRED_LIBS}
)

install(TARGETS InventorDraggers
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)