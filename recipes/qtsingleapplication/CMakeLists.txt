cmake_minimum_required(VERSION 3.14)
project(QtSingleApplication)

include(conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_AUTOMOC ON)

set(_UNUSED ${CMAKE_DEBUG_POSTFIX} ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY} ${CMAKE_INSTALL_BINDIR} ${CMAKE_INSTALL_DATAROOTDIR} ${CMAKE_INSTALL_INCLUDEDIR} ${CMAKE_INSTALL_LIBDIR} ${CMAKE_INSTALL_LIBEXECDIR} ${CMAKE_INSTALL_OLDINCLUDEDIR} ${CMAKE_INSTALL_SBINDIR})

add_library(QtSingleApplication STATIC "")

add_definitions(-DUNICODE -D_UNICODE)

target_sources(QtSingleApplication PRIVATE
    sources/src/qtlocalpeer.h
    sources/src/qtlocalpeer.cpp
    sources/src/qtsinglecoreapplication.h
    sources/src/qtsinglecoreapplication.cpp
)

if(WITH_WIDGETS)
  find_package(Qt5 COMPONENTS Core Widgets Network REQUIRED)
  target_link_libraries(QtSingleApplication PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network)
  set_target_properties(QtSingleApplication PROPERTIES OUTPUT_NAME "QtSingleApplication")

  target_sources(QtSingleApplication PRIVATE
      sources/src/qtsingleapplication.h
      sources/src/qtsingleapplication.cpp
  )
else()
  find_package(Qt5 COMPONENTS Core Network REQUIRED)
  target_link_libraries(QtSingleApplication PUBLIC Qt5::Core Qt5::Network)
  set_target_properties(QtSingleApplication PROPERTIES OUTPUT_NAME "QtSingleCoreApplication")
endif()

if(WIN32)
  target_compile_definitions(QtSingleApplication PRIVATE $<BUILD_INTERFACE:QT_QTSINGLEAPPLICATION_EXPORT>)
  target_compile_definitions(QtSingleApplication PRIVATE QT_QTLOCKEDFILE_EXPORT)
else()
  set_target_properties(QtSingleApplication PROPERTIES C_VISIBILITY_PRESET default)
  set_target_properties(QtSingleApplication PROPERTIES CXX_VISIBILITY_PRESET default)
endif()

install(TARGETS QtSingleApplication
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

install(FILES
    sources/src/QtLockedFile
    sources/src/QtSingleCoreApplication

    sources/src/qtlocalpeer.h
    sources/src/qtlockedfile.h
    sources/src/qtsinglecoreapplication.h
  DESTINATION include/QtSolutions
)

if(WITH_WIDGETS)
  install(FILES
      sources/src/QtSingleApplication
      sources/src/qtsingleapplication.h
    DESTINATION include/QtSolutions
  )
endif()
