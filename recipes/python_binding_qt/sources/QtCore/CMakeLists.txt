
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
)

target_link_libraries(QtCore
  PRIVATE
    ${REQUIRED_LIBS}
    Qt6::Gui Qt6::Widgets
)

install(TARGETS QtCore
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)
