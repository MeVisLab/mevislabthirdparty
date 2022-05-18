cmake_minimum_required(VERSION 3.14)
project(conan-minizip C)

set(_UNUSED ${CMAKE_DEBUG_POSTFIX} ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY} ${CMAKE_INSTALL_BINDIR} ${CMAKE_INSTALL_DATAROOTDIR} ${CMAKE_INSTALL_INCLUDEDIR} ${CMAKE_INSTALL_LIBDIR} ${CMAKE_INSTALL_LIBEXECDIR} ${CMAKE_INSTALL_OLDINCLUDEDIR} ${CMAKE_INSTALL_SBINDIR})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(minizip "")
target_sources(minizip PRIVATE
    sources/contrib/minizip/crypt.h
    sources/contrib/minizip/ioapi.c
    sources/contrib/minizip/ioapi.h
    sources/contrib/minizip/minizip_extern.h
    sources/contrib/minizip/mztools.c
    sources/contrib/minizip/mztools.h
    sources/contrib/minizip/unzip.c
    sources/contrib/minizip/unzip.h
    sources/contrib/minizip/zip.c
    sources/contrib/minizip/zip.h
)

if(WIN32)
  target_sources(minizip PRIVATE
      sources/contrib/minizip/iowin32.c
      sources/contrib/minizip/iowin32.h
      sources/contrib/minizip/minizip1.rc
  )
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

target_include_directories(minizip PRIVATE sources)
target_include_directories(minizip PRIVATE sources/contrib/minizip)

target_link_libraries(minizip PUBLIC ${CONAN_LIBS})
target_compile_definitions(minizip PRIVATE MINIZIP_BUILDING)
target_compile_definitions(minizip PRIVATE MINIZIP_DLL)

install(TARGETS minizip ARCHIVE DESTINATION "lib" LIBRARY DESTINATION "lib" RUNTIME DESTINATION "bin")
install(FILES sources/contrib/minizip/minizip_extern.h DESTINATION "include/minizip")
# Don't install crypt.h which causing trouble for linking.
# See https://bugzilla.redhat.com/show_bug.cgi?id=1424609
#install(FILES sources/contrib/minizip/crypt.h DESTINATION "include/minizip")
install(FILES sources/contrib/minizip/ioapi.h DESTINATION "include/minizip")
install(FILES sources/contrib/minizip/mztools.h DESTINATION "include/minizip")
install(FILES sources/contrib/minizip/unzip.h DESTINATION "include/minizip")
install(FILES sources/contrib/minizip/zip.h DESTINATION "include/minizip")

if(WIN32)
    install(FILES sources/contrib/minizip/iowin32.h DESTINATION "include/minizip")
endif()
