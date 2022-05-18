add_library(InventorManips "")
set_target_properties(InventorManips PROPERTIES OUTPUT_NAME manips)

if(WIN32)
    set_target_properties(InventorManips PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(InventorManips PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(InventorManips PRIVATE
  InventorManips.cpp
  ../generated_cpp/Inventor_manips/Inventor_manips0.h
  ../generated_cpp/Inventor_manips/Inventor_manips0.cpp
  ../generated_cpp/Inventor_manips/Inventor_manips_init.cpp
)

target_link_libraries(InventorManips
  PRIVATE
    Qt5::Core
    Python3::Python
    Threads::Threads
    ${CONAN_LIBS}
)

install(TARGETS InventorManips
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)