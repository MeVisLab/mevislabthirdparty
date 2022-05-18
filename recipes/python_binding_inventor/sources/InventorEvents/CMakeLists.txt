add_library(InventorEvents "")
set_target_properties(InventorEvents PROPERTIES OUTPUT_NAME events)

if(WIN32)
    set_target_properties(InventorEvents PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(InventorEvents PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(InventorEvents PRIVATE
  InventorEvents.cpp
  ../generated_cpp/Inventor_events/Inventor_events0.h
  ../generated_cpp/Inventor_events/Inventor_events0.cpp
  ../generated_cpp/Inventor_events/Inventor_events_init.cpp
)

target_link_libraries(InventorEvents
  PRIVATE
    Qt5::Core
    Python3::Python
    Threads::Threads
    ${CONAN_LIBS}
)

install(TARGETS InventorEvents
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)