find_package(Qt5 COMPONENTS Core Gui PrintSupport Multimedia MultimediaWidgets Widgets REQUIRED)

add_library(QtMultimedia "")
set_target_properties(QtMultimedia PROPERTIES OUTPUT_NAME QtMultimedia)

if(WIN32)
    set_target_properties(QtMultimedia PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(QtMultimedia PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(QtMultimedia PRIVATE QtMultimedia.cpp)
target_sources(QtMultimedia PRIVATE
  ../generated_cpp/com_trolltech_qt_multimedia/com_trolltech_qt_multimedia0.cpp
  ../generated_cpp/com_trolltech_qt_multimedia/com_trolltech_qt_multimedia0.h
  ../generated_cpp/com_trolltech_qt_multimedia/com_trolltech_qt_multimedia1.cpp
  ../generated_cpp/com_trolltech_qt_multimedia/com_trolltech_qt_multimedia1.h
  ../generated_cpp/com_trolltech_qt_multimedia/com_trolltech_qt_multimedia2.cpp
  ../generated_cpp/com_trolltech_qt_multimedia/com_trolltech_qt_multimedia2.h
  ../generated_cpp/com_trolltech_qt_multimedia/com_trolltech_qt_multimedia3.cpp
  ../generated_cpp/com_trolltech_qt_multimedia/com_trolltech_qt_multimedia3.h
  ../generated_cpp/com_trolltech_qt_multimedia/com_trolltech_qt_multimedia_init.cpp
)

target_link_libraries(QtMultimedia
  PRIVATE
    Qt5::Core 
    Qt5::Gui 
    Qt5::Multimedia 
    Qt5::MultimediaWidgets
    Qt5::PrintSupport
    Qt5::Widgets 
    Python3::Python
    Threads::Threads
    ${CONAN_LIBS}
)

install(TARGETS QtMultimedia
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)
