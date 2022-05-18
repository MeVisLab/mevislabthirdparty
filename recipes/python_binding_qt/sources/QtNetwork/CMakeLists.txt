find_package(Qt5 COMPONENTS Core Gui Network REQUIRED)

add_library(QtNetwork "")
set_target_properties(QtNetwork PROPERTIES OUTPUT_NAME QtNetwork)

if(WIN32)
    set_target_properties(QtNetwork PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(QtNetwork PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(QtNetwork PRIVATE QtNetwork.cpp)
target_sources(QtNetwork PRIVATE
  ../generated_cpp/com_trolltech_qt_network/com_trolltech_qt_network0.h
  ../generated_cpp/com_trolltech_qt_network/com_trolltech_qt_network0.cpp
  ../generated_cpp/com_trolltech_qt_network/com_trolltech_qt_network1.h
  ../generated_cpp/com_trolltech_qt_network/com_trolltech_qt_network1.cpp
  ../generated_cpp/com_trolltech_qt_network/com_trolltech_qt_network_init.cpp
)

target_link_libraries(QtNetwork
  PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Network
    Python3::Python
    Threads::Threads
    ${CONAN_LIBS}
)

install(TARGETS QtNetwork
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)
