find_package(Qt5 COMPONENTS Core Gui Qml Quick QuickWidgets REQUIRED)

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
  ../generated_cpp/com_trolltech_qt_quick/com_trolltech_qt_quick1.h
  ../generated_cpp/com_trolltech_qt_quick/com_trolltech_qt_quick1.cpp
  ../generated_cpp/com_trolltech_qt_quick/com_trolltech_qt_quick_init.cpp
)

target_link_libraries(QtQuick
  PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Qml 
    Qt5::Quick
    Qt5::QuickWidgets
    Python3::Python
    Threads::Threads
    ${CONAN_LIBS}
)

install(TARGETS QtQuick
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)
