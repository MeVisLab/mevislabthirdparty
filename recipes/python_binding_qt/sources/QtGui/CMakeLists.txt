find_package(Qt5 COMPONENTS Core Gui Widgets PrintSupport REQUIRED)

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
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui1.cpp
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui1.h
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui2.cpp
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui2.h
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui3.cpp
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui3.h
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui4.cpp
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui4.h
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui5.cpp
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui5.h
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui6.cpp
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui6.h
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui7.cpp
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui7.h
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui8.cpp
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui8.h
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui9.cpp
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui9.h
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui10.cpp
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui10.h
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui11.cpp
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui11.h
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui12.cpp
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui12.h
  ../generated_cpp/com_trolltech_qt_gui/com_trolltech_qt_gui_init.cpp
)

target_link_libraries(QtGui
  PRIVATE
    Qt5::Core 
    Qt5::Gui 
    Qt5::PrintSupport
    Qt5::Widgets 
    Python3::Python
    Threads::Threads
    ${CONAN_LIBS}
)

install(TARGETS QtGui
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)
