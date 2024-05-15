cmake_minimum_required(VERSION 3.27)
project(QHttpServer)

set(CMAKE_AUTOMOC ON)
find_package(Qt6 COMPONENTS Core Network REQUIRED)

add_library(QHttpServer)

include_directories(src/http-parser)

target_sources(QHttpServer PRIVATE
    src/http-parser/http_parser.h
    src/http-parser/http_parser.c
    src/src/qhttpconnection.cpp
    src/src/qhttpconnection.h
    src/src/qhttprequest.cpp
    src/src/qhttprequest.h
    src/src/qhttpresponse.cpp
    src/src/qhttpresponse.h
    src/src/qhttpserverapi.h
    src/src/qhttpserverfwd.h
    src/src/qhttpserver.cpp
    src/src/qhttpserver.h
)

target_include_directories(QHttpServer PRIVATE src src/http-parser)

target_link_libraries(QHttpServer PUBLIC Qt::Core Qt::Network)

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

install(
  FILES
    src/src/qhttpconnection.h
    src/src/qhttprequest.h
    src/src/qhttpresponse.h
    src/src/qhttpserverapi.h
    src/src/qhttpserverfwd.h
    src/src/qhttpserver.h
  DESTINATION
    include/QHttpServer
)

if(MSVC)
  install(FILES $<TARGET_PDB_FILE:QHttpServer> DESTINATION bin OPTIONAL)
endif()
