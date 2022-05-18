add_library(InventorEngines "")
set_target_properties(InventorEngines PROPERTIES OUTPUT_NAME engines)

if(WIN32)
    set_target_properties(InventorEngines PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(InventorEngines PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(InventorEngines PRIVATE
  InventorEngines.cpp
  ../generated_cpp/Inventor_engines/Inventor_engines0.h
  ../generated_cpp/Inventor_engines/Inventor_engines0.cpp
  ../generated_cpp/Inventor_engines/Inventor_engines1.h
  ../generated_cpp/Inventor_engines/Inventor_engines1.cpp
  ../generated_cpp/Inventor_engines/Inventor_engines_init.cpp
)

target_link_libraries(InventorEngines
  PRIVATE
    Qt5::Core
    Python3::Python
    Threads::Threads
    ${CONAN_LIBS}
)

install(TARGETS InventorEngines
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)