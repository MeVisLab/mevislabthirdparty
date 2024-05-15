add_library(QtWebEngineWidgets "")
set_target_properties(QtWebEngineWidgets PROPERTIES OUTPUT_NAME QtWebEngineWidgets)

if(WIN32)
    set_target_properties(QtWebEngineWidgets PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(QtWebEngineWidgets PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(QtWebEngineWidgets PRIVATE QtWebEngineWidgets.cpp)
target_sources(QtWebEngineWidgets PRIVATE
  ../generated_cpp/com_trolltech_qt_webenginewidgets/com_trolltech_qt_webenginewidgets0.h
  ../generated_cpp/com_trolltech_qt_webenginewidgets/com_trolltech_qt_webenginewidgets0.cpp
  ../generated_cpp/com_trolltech_qt_webenginewidgets/com_trolltech_qt_webenginewidgets_init.cpp
)

target_link_libraries(QtWebEngineWidgets
  PRIVATE
    ${REQUIRED_LIBS}
    Qt6::Widgets
    Qt6::WebEngineWidgets
)

install(TARGETS QtWebEngineWidgets
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)
