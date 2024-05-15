cmake_minimum_required(VERSION 3.27)
project(QtService)

set(CMAKE_AUTOMOC ON)

add_library(QtService "")

add_definitions(-DUNICODE -D_UNICODE)

target_sources(QtService PRIVATE
    src/qtservice/src/qtservice.cpp
    src/qtservice/src/qtservice.h
    src/qtservice/src/qtservice_p.h
)

if(WIN32)
  target_sources(QtService PRIVATE src/qtservice/src/qtservice_win.cpp)
else()
  target_sources(QtService PRIVATE
      src/qtservice/src/qtservice_unix.cpp
      src/qtservice/src/qtunixserversocket.cpp
      src/qtservice/src/qtunixserversocket.h
      src/qtservice/src/qtunixsocket.cpp
      src/qtservice/src/qtunixsocket.h
  )
endif()

find_package(Qt6 COMPONENTS Core Network REQUIRED)
target_link_libraries(QtService PUBLIC Qt6::Core Qt6::Network)

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
    src/qtservice/src/QtService
    src/qtservice/src/QtServiceBase
    src/qtservice/src/QtServiceController
    src/qtservice/src/qtservice.h
  DESTINATION include/QtService
)

if(MSVC)
  install(FILES $<TARGET_PDB_FILE:QtService> DESTINATION bin OPTIONAL)
endif()
