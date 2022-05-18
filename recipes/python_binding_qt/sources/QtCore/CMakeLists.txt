find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(Threads REQUIRED)

add_library(QtCore "")
set_target_properties(QtCore PROPERTIES OUTPUT_NAME QtCore)

set(CMAKE_AUTOMOC ON)

if(WIN32)
    set_target_properties(QtCore PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(QtCore PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(QtCore PRIVATE QtCore.cpp)
target_sources(QtCore PRIVATE
  ../generated_cpp/com_trolltech_qt_core/com_trolltech_qt_core_init.cpp
  ../generated_cpp/com_trolltech_qt_core/com_trolltech_qt_core0.h
  ../generated_cpp/com_trolltech_qt_core/com_trolltech_qt_core0.cpp
  ../generated_cpp/com_trolltech_qt_core/com_trolltech_qt_core1.h
  ../generated_cpp/com_trolltech_qt_core/com_trolltech_qt_core1.cpp
  ../generated_cpp/com_trolltech_qt_core/com_trolltech_qt_core2.h
  ../generated_cpp/com_trolltech_qt_core/com_trolltech_qt_core2.cpp
  ../generated_cpp/com_trolltech_qt_core/com_trolltech_qt_core3.h
  ../generated_cpp/com_trolltech_qt_core/com_trolltech_qt_core3.cpp
)

target_link_libraries(QtCore 
  PRIVATE 
  Python3::Python 
  Qt5::Core
  Qt5::Gui
  Qt5::Widgets
  Threads::Threads 
  ${CONAN_LIBS})

install(TARGETS QtCore
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)
