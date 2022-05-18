find_package(Qt5 COMPONENTS Core Svg REQUIRED)

add_library(QtSvg "")
set_target_properties(QtSvg PROPERTIES OUTPUT_NAME QtSvg)

if(WIN32)
    set_target_properties(QtSvg PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(QtSvg PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(QtSvg PRIVATE QtSvg.cpp)
target_sources(QtSvg PRIVATE
  ../generated_cpp/com_trolltech_qt_svg/com_trolltech_qt_svg0.h
  ../generated_cpp/com_trolltech_qt_svg/com_trolltech_qt_svg0.cpp
  ../generated_cpp/com_trolltech_qt_svg/com_trolltech_qt_svg_init.cpp
)

target_link_libraries(QtSvg
  PRIVATE
    Qt5::Core
    Qt5::Svg
    Python3::Python
    Threads::Threads
    ${CONAN_LIBS}
)

install(TARGETS QtSvg
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)
