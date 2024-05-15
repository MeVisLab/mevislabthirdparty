add_library(QtQuick "")
set_target_properties(QtQuick PROPERTIES OUTPUT_NAME QtQuick)

if(WIN32)
    set_target_properties(QtQuick PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(QtQuick PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(QtQuick PRIVATE QtQuick.cpp)
target_sources(QtQuick PRIVATE
  ../generated_cpp/com_trolltech_qt_quick/com_trolltech_qt_quick0.h
  ../generated_cpp/com_trolltech_qt_quick/com_trolltech_qt_quick0.cpp
#   ../generated_cpp/com_trolltech_qt_quick/com_trolltech_qt_quick1.h
#   ../generated_cpp/com_trolltech_qt_quick/com_trolltech_qt_quick1.cpp
  ../generated_cpp/com_trolltech_qt_quick/com_trolltech_qt_quick_init.cpp
)

target_link_libraries(QtQuick
  PRIVATE
    ${REQUIRED_LIBS}
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickWidgets
)

install(TARGETS QtQuick
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)
