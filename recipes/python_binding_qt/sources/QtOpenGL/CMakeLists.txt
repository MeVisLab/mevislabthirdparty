find_package(Qt5 COMPONENTS Core OpenGL REQUIRED)

add_library(QtOpenGL "")
set_target_properties(QtOpenGL PROPERTIES OUTPUT_NAME QtOpenGL)

if(WIN32)
    set_target_properties(QtOpenGL PROPERTIES PREFIX "" SUFFIX ".pyd")
else()
    set_target_properties(QtOpenGL PROPERTIES DEBUG_POSTFIX "" PREFIX "" SUFFIX ".so")
endif()

target_sources(QtOpenGL PRIVATE QtOpenGL.cpp)
target_sources(QtOpenGL PRIVATE
  ../generated_cpp/com_trolltech_qt_opengl/com_trolltech_qt_opengl0.h
  ../generated_cpp/com_trolltech_qt_opengl/com_trolltech_qt_opengl0.cpp
  ../generated_cpp/com_trolltech_qt_opengl/com_trolltech_qt_opengl_init.cpp
)

target_link_libraries(QtOpenGL
  PRIVATE
    Qt5::Core 
    Qt5::Gui
    Qt5::OpenGL
    Python3::Python
    Threads::Threads
    ${CONAN_LIBS}
)

install(TARGETS QtOpenGL
    RUNTIME DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY DESTINATION "${TARGET_RUNTIME_OUTPUT_DIRECTORY}"
)
