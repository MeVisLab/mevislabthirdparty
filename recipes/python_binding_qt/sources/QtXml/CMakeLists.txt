find_package(Qt5 COMPONENTS Core Gui Xml REQUIRED)

add_library(QtXml "")
set_target_properties(QtXml PROPERTIES OUTPUT_NAME QtXml)

if(WIN32)
    set_target_properties(QtXml PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(QtXml PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(QtXml PRIVATE QtXml.cpp)
target_sources(QtXml PRIVATE
  ../generated_cpp/com_trolltech_qt_xml/com_trolltech_qt_xml0.h
  ../generated_cpp/com_trolltech_qt_xml/com_trolltech_qt_xml0.cpp
  ../generated_cpp/com_trolltech_qt_xml/com_trolltech_qt_xml1.h
  ../generated_cpp/com_trolltech_qt_xml/com_trolltech_qt_xml1.cpp
  ../generated_cpp/com_trolltech_qt_xml/com_trolltech_qt_xml_init.cpp
)

target_link_libraries(QtXml
  PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Xml
    Python3::Python
    Threads::Threads
    ${CONAN_LIBS}
)

install(TARGETS QtXml
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)
