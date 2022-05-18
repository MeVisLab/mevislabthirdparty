cmake_minimum_required(VERSION 3.10)
project(QtService)

include(conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_AUTOMOC ON)

set(_UNUSED ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY} ${CMAKE_INSTALL_BINDIR} ${CMAKE_INSTALL_DATAROOTDIR} ${CMAKE_INSTALL_INCLUDEDIR} ${CMAKE_INSTALL_LIBDIR} ${CMAKE_INSTALL_LIBEXECDIR} ${CMAKE_INSTALL_OLDINCLUDEDIR} ${CMAKE_INSTALL_SBINDIR})

add_library(QtService "")

add_definitions(-DUNICODE -D_UNICODE)

target_sources(QtService PRIVATE
    sources/src/qtservice.cpp
    sources/src/qtservice.h
    sources/src/qtservice_p.h
)

if(WIN32)
  target_sources(QtService PRIVATE sources/src/qtservice_win.cpp)
else()
  target_sources(QtService PRIVATE
      sources/src/qtservice_unix.cpp
      sources/src/qtunixserversocket.cpp
      sources/src/qtunixserversocket.h
      sources/src/qtunixsocket.cpp
      sources/src/qtunixsocket.h
  )
endif()

find_package(Qt5 COMPONENTS Core Network REQUIRED)
target_link_libraries(QtService PUBLIC Qt5::Core Qt5::Network)

if(WIN32)
  target_compile_definitions(QtService PRIVATE $<BUILD_INTERFACE:QT_QTSERVICE_EXPORT>)
else()
  set_target_properties(QtService PROPERTIES C_VISIBILITY_PRESET default)
  set_target_properties(QtService PROPERTIES CXX_VISIBILITY_PRESET default)
endif()

install(TARGETS QtService
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

install(FILES
    sources/src/QtService
    sources/src/QtServiceBase
    sources/src/QtServiceController
    sources/src/qtservice.h
  DESTINATION include/QtService
)

if(MSVC)
  install(FILES $<TARGET_PDB_FILE:QtService> DESTINATION bin OPTIONAL)
endif()
