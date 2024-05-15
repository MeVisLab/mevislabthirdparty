add_library(InventorDetails "")
set_target_properties(InventorDetails PROPERTIES OUTPUT_NAME details)

if(WIN32)
    set_target_properties(InventorDetails PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(InventorDetails PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(InventorDetails PRIVATE
  InventorDetails.cpp
  ../generated_cpp/Inventor_details/Inventor_details0.h
  ../generated_cpp/Inventor_details/Inventor_details0.cpp
  ../generated_cpp/Inventor_details/Inventor_details_init.cpp
)

target_link_libraries(InventorDetails
  PRIVATE
    ${REQUIRED_LIBS}
)

install(TARGETS InventorDetails
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)