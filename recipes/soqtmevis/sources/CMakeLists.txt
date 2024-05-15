cmake_minimum_required(VERSION 3.27)
project(SoQtMeVis LANGUAGES CXX)

find_package(Qt6 COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenInventor REQUIRED)

if(UNIX AND NOT APPLE)
    find_package(Fontconfig REQUIRED)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_library(SoQtMeVis "")
add_library(SoQtMeVis::SoQtMeVis ALIAS SoQtMeVis)
set_target_properties(SoQtMeVis PROPERTIES OUTPUT_NAME SoQtMeVis)

target_sources(SoQtMeVis PRIVATE
  include/Inventor/Qt/devices/SoQtDevice.h
  include/Inventor/Qt/devices/SoQtSubDevice.h
  include/Inventor/Qt/SoQt.h
  include/Inventor/Qt/SoQtCameraController.h
  include/Inventor/Qt/SoQtDLLInit.h
  include/Inventor/Qt/SoQtGLWidget.h
  include/Inventor/Qt/SoQtIcons.h
  include/Inventor/Qt/SoQtRenderArea.h
  include/Inventor/Qt/SoQtSceneHandler.h
  include/Inventor/Qt/SoQtStandardEventTranslator.h
  include/Inventor/Qt/SoQtThumbWheel.h
  include/Inventor/Qt/viewers/SoQtConstrainedViewer.h
  include/Inventor/Qt/viewers/SoQtExaminerViewer.h
  include/Inventor/Qt/viewers/SoQtFlyViewer.h
  include/Inventor/Qt/viewers/SoQtFullViewer.h
  include/Inventor/Qt/viewers/SoQtViewer.h
  SoQtMeVis.qrc
  src/SoQt.cpp
  src/SoQtCameraController.cpp
  src/SoQtContextShareManager.cpp
  src/SoQtContextShareManager.h
  src/SoQtDevice.cpp
  src/SoQtGLWidget.cpp
  src/SoQtHeadlight.cpp
  src/SoQtHeadlight.h
  src/SoQtOffscreenGLWidget.cpp
  src/SoQtOffscreenGLWidget.h
  src/SoQtRealQOpenGLWidget.cpp
  src/SoQtRealQOpenGLWidget.h
  src/SoQtRenderArea.cpp
  src/SoQtSceneHandler.cpp
  src/SoQtStandardEventTranslator.cpp
  src/SoQtThumbWheel.cpp
  src/viewers/SoQtConstrainedViewer.cpp
  src/viewers/SoQtExaminerViewer.cpp
  src/viewers/SoQtFlyViewer.cpp
  src/viewers/SoQtFullViewer.cpp
  src/viewers/SoQtIcons.cpp
  src/viewers/SoQtViewer.cpp
)

target_include_directories(SoQtMeVis PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${MEVISLAB_INSTALL_INCLUDEDIR}>
)

target_compile_definitions(SoQtMeVis PRIVATE MEVIS_TARGET=SoQtMeVis)
target_compile_definitions(SoQtMeVis PRIVATE $<BUILD_INTERFACE:SOQT_MEVIS_EXPORTS>)

target_link_libraries(SoQtMeVis
  PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    OpenGL::GL
    OpenGL::GLU
    OpenInventor::OpenInventor
)

if(UNIX AND NOT APPLE)
    target_link_libraries(SoQtMeVis PUBLIC Fontconfig::Fontconfig)
endif()

install(TARGETS SoQtMeVis RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/" DESTINATION include FILES_MATCHING PATTERN "*.h")
# MVL-543: Where to install
# install(FILES Changes-Mevis.txt CHANGES.txt License.txt README.txt DESTINATION ${REL})

if(MSVC)
  install(FILES $<TARGET_PDB_FILE:SoQtMeVis> DESTINATION bin OPTIONAL)
endif()
