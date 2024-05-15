cmake_minimum_required(VERSION 3.27)
project(PythonBindingQt LANGUAGES CXX)

find_package(Python3 REQUIRED)
find_package(PythonQt REQUIRED)
find_package(Threads REQUIRED)
find_package(Qt6 COMPONENTS
             Core Gui Widgets PrintSupport Network
             OpenGL OpenGLWidgets
             Qml Quick QuickWidgets
             Sql Svg SvgWidgets
             Multimedia MultimediaWidgets
             WebEngineWidgets
             Xml
             REQUIRED)

set(REQUIRED_LIBS
  Python3::Python PythonQt::PythonQt
  Qt6::Core Qt6::Gui
  Qt6::OpenGL Qt6::OpenGLWidgets
  Qt6::Svg Qt6::SvgWidgets
  Qt6::Xml Qt6::Sql Qt6::Multimedia Qt6::Qml Qt6::Quick
  Qt6::WebEngineWidgets
)

set(SITE_PACKAGE_TARGET_DIR "$ENV{MEVIS_PYTHON_SITE_PACKAGES_FOLDER}")

set(TARGET_LIBRARY_OUTPUT_DIRECTORY "${SITE_PACKAGE_TARGET_DIR}/../")
set(TARGET_RUNTIME_OUTPUT_DIRECTORY "${SITE_PACKAGE_TARGET_DIR}/PythonQt")

set(CMAKE_AUTOMOC ON)
if(WIN32)
    add_definitions(/bigobj)
endif()

add_subdirectory(Qt)
add_subdirectory(QtCore)
add_subdirectory(QtGui)
add_subdirectory(QtMultimedia)
add_subdirectory(QtNetwork)
add_subdirectory(QtQml)
add_subdirectory(QtQuick)
add_subdirectory(QtSql)
add_subdirectory(QtSvg)
add_subdirectory(QtWebEngineWidgets)
add_subdirectory(QtXml)
