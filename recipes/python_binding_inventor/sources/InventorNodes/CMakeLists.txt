add_library(InventorNodes "")
set_target_properties(InventorNodes PROPERTIES OUTPUT_NAME nodes)

if(WIN32)
    set_target_properties(InventorNodes PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(InventorNodes PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(InventorNodes PRIVATE
  InventorNodes.cpp
  ../generated_cpp/Inventor_nodes/Inventor_nodes0.h
  ../generated_cpp/Inventor_nodes/Inventor_nodes0.cpp
  ../generated_cpp/Inventor_nodes/Inventor_nodes1.h
  ../generated_cpp/Inventor_nodes/Inventor_nodes1.cpp
  ../generated_cpp/Inventor_nodes/Inventor_nodes2.h
  ../generated_cpp/Inventor_nodes/Inventor_nodes2.cpp
  ../generated_cpp/Inventor_nodes/Inventor_nodes3.h
  ../generated_cpp/Inventor_nodes/Inventor_nodes3.cpp
  ../generated_cpp/Inventor_nodes/Inventor_nodes_init.cpp
)

target_link_libraries(InventorNodes
  PRIVATE
    Qt5::Core
    Python3::Python
    Threads::Threads
    ${CONAN_LIBS}
)

install(TARGETS InventorNodes
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)