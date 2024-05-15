add_library(QtGui "")
set_target_properties(QtGui PROPERTIES OUTPUT_NAME QtGui)

if(WIN32)
    set_target_properties(QtGui PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(QtGui PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(QtGui PRIVATE QtGui.cpp)
target_sources(QtGui PRIVATE
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui0.cpp
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui0.h
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui_init.cpp
)

target_link_libraries(QtGui
  PRIVATE
    ${REQUIRED_LIBS}
    Qt6::Gui
    Qt6::PrintSupport
    Qt6::Widgets
)

install(TARGETS QtGui
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)
