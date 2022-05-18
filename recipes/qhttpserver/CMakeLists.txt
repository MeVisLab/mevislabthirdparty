cmake_minimum_required(VERSION 3.14)
project(QHttpServer)

include(conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_AUTOMOC ON)

set(_UNUSED ${CMAKE_DEBUG_POSTFIX} ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY} ${CMAKE_INSTALL_BINDIR} ${CMAKE_INSTALL_DATAROOTDIR} ${CMAKE_INSTALL_INCLUDEDIR} ${CMAKE_INSTALL_LIBDIR} ${CMAKE_INSTALL_LIBEXECDIR} ${CMAKE_INSTALL_OLDINCLUDEDIR} ${CMAKE_INSTALL_SBINDIR})

add_library(QHttpServer "")

include_directories(
  sources
  sources/http-parser
)

target_sources(QHttpServer PRIVATE
    sources/http-parser/http_parser.h
    sources/http-parser/http_parser.c

    sources/src/qhttpconnection.cpp
    sources/src/qhttpconnection.h
    sources/src/qhttprequest.cpp
    sources/src/qhttprequest.h
    sources/src/qhttpresponse.cpp
    sources/src/qhttpresponse.h
    sources/src/qhttpserverapi.h
    sources/src/qhttpserverfwd.h
    sources/src/qhttpserver.cpp
    sources/src/qhttpserver.h
)

find_package(Qt5 COMPONENTS Core Network REQUIRED)
target_link_libraries(QHttpServer PUBLIC Qt5::Core Qt5::Network)

if(WIN32)
  target_compile_definitions(QHttpServer PRIVATE $<BUILD_INTERFACE:QHTTPSERVER_EXPORT>)
else()
  set_target_properties(QHttpServer PROPERTIES C_VISIBILITY_PRESET default)
  set_target_properties(QHttpServer PROPERTIES CXX_VISIBILITY_PRESET default)
endif()

install(TARGETS QHttpServer
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

install(FILES
    sources/src/qhttpconnection.h
    sources/src/qhttprequest.h
    sources/src/qhttpresponse.h
    sources/src/qhttpserverapi.h
    sources/src/qhttpserverfwd.h
    sources/src/qhttpserver.h
  DESTINATION include/QHttpServer
)

if(MSVC)
  install(FILES $<TARGET_PDB_FILE:QHttpServer> DESTINATION bin OPTIONAL)
endif()
