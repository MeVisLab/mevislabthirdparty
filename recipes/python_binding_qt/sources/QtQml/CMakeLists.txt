add_library(QtQml "")
set_target_properties(QtQml PROPERTIES OUTPUT_NAME QtQml)

if(WIN32)
    set_target_properties(QtQml PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(QtQml PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(QtQml PRIVATE QtQml.cpp)
target_sources(QtQml PRIVATE
   ../generated_cpp/com_trolltech_qt_qml/com_trolltech_qt_qml0.h
   ../generated_cpp/com_trolltech_qt_qml/com_trolltech_qt_qml0.cpp
   ../generated_cpp/com_trolltech_qt_qml/com_trolltech_qt_qml_init.cpp
)

target_link_libraries(QtQml
  PRIVATE
    ${REQUIRED_LIBS}
    Qt6::Gui
    Qt6::Qml
)

install(TARGETS QtQml
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)
