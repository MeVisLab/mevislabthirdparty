find_package(Qt5 COMPONENTS Core Gui Widgets Network PrintSupport REQUIRED)

add_library(QtWebKit "")
set_target_properties(QtWebKit PROPERTIES OUTPUT_NAME QtWebKit)

if(WIN32)
    set_target_properties(QtWebKit PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(QtWebKit PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(QtWebKit PRIVATE QtWebKit.cpp)
target_sources(QtWebKit PRIVATE
  ../generated_cpp/com_trolltech_qt_webkit/com_trolltech_qt_webkit0.h
  ../generated_cpp/com_trolltech_qt_webkit/com_trolltech_qt_webkit0.cpp
  ../generated_cpp/com_trolltech_qt_webkit/com_trolltech_qt_webkit_init.cpp
)

target_link_libraries(QtWebKit
  PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Network
    Qt5::PrintSupport
    Python3::Python
    Threads::Threads
    ${CONAN_LIBS}
)

install(TARGETS QtWebKit
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)
