find_package(Qt5 COMPONENTS Core Gui Xml XmlPatterns REQUIRED)

add_library(QtXmlPatterns "")
set_target_properties(QtXmlPatterns PROPERTIES OUTPUT_NAME QtXmlPatterns)

if(WIN32)
    set_target_properties(QtXmlPatterns PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(QtXmlPatterns PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(QtXmlPatterns PRIVATE QtXmlPatterns.cpp)
target_sources(QtXmlPatterns PRIVATE
  ../generated_cpp/com_trolltech_qt_xmlpatterns/com_trolltech_qt_xmlpatterns0.h
  ../generated_cpp/com_trolltech_qt_xmlpatterns/com_trolltech_qt_xmlpatterns0.cpp
  ../generated_cpp/com_trolltech_qt_xmlpatterns/com_trolltech_qt_xmlpatterns_init.cpp
)

target_link_libraries(QtXmlPatterns
  PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Xml
    Qt5::XmlPatterns
    Python3::Python
    Threads::Threads
    ${CONAN_LIBS}
)

install(TARGETS QtXmlPatterns
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)
