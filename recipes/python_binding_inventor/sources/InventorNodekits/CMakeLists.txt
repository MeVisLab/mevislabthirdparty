add_library(InventorNodekits "")
set_target_properties(InventorNodekits PROPERTIES OUTPUT_NAME nodekits)

if(WIN32)
    set_target_properties(InventorNodekits PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(InventorNodekits PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(InventorNodekits PRIVATE
  InventorNodekits.cpp
  ../generated_cpp/Inventor_nodekits/Inventor_nodekits0.h
  ../generated_cpp/Inventor_nodekits/Inventor_nodekits0.cpp
  ../generated_cpp/Inventor_nodekits/Inventor_nodekits_init.cpp
)

target_link_libraries(InventorNodekits
  PRIVATE
    ${REQUIRED_LIBS}
)

install(TARGETS InventorNodekits
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)