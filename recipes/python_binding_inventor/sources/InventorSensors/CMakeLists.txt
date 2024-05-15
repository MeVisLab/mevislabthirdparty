add_library(InventorSensors "")
set_target_properties(InventorSensors PROPERTIES OUTPUT_NAME sensors)

if(WIN32)
    set_target_properties(InventorSensors PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(InventorSensors PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(InventorSensors PRIVATE
  InventorSensors.h
  InventorSensors.cpp
  ../generated_cpp/Inventor_sensors/Inventor_sensors0.h
  ../generated_cpp/Inventor_sensors/Inventor_sensors0.cpp
  ../generated_cpp/Inventor_sensors/Inventor_sensors_init.cpp
)

target_link_libraries(InventorSensors
  PRIVATE
    ${REQUIRED_LIBS}
)

install(TARGETS InventorSensors
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)