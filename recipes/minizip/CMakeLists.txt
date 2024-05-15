cmake_minimum_required(VERSION 3.27)
project(conan-minizip C)

find_package(ZLIB REQUIRED)
find_package(BZip2 REQUIRED)

if(MSVC)
  add_compile_options(/W3 /wd4005 /wd4996 /wd4018 -D_CRT_SECURE_NO_WARNINGS)
endif()

add_library(minizip "")
target_sources(minizip PRIVATE
    src/contrib/minizip/crypt.h
    src/contrib/minizip/ioapi.c
    src/contrib/minizip/ioapi.h
    src/contrib/minizip/mztools.c
    src/contrib/minizip/mztools.h
    src/contrib/minizip/unzip.c
    src/contrib/minizip/unzip.h
    src/contrib/minizip/zip.c
    src/contrib/minizip/zip.h
)

if(WIN32)
  target_sources(minizip PRIVATE
      src/contrib/minizip/iowin32.c
      src/contrib/minizip/iowin32.h
      minizip-win32.def
  )
endif()

# target_include_directories(minizip PRIVATE sources)
target_include_directories(minizip PRIVATE src/contrib/minizip)

target_link_libraries(minizip PUBLIC ZLIB::ZLIB)
target_compile_definitions(minizip PRIVATE -D_ZLIB_H)

target_link_libraries(minizip PUBLIC BZip2::BZip2)
target_compile_definitions(minizip PRIVATE -DHAVE_BZIP2=1)

# target_compile_definitions(minizip PRIVATE MINIZIP_BUILDING)
# target_compile_definitions(minizip PRIVATE MINIZIP_DLL)

install(TARGETS minizip ARCHIVE DESTINATION "lib" LIBRARY DESTINATION "lib" RUNTIME DESTINATION "bin")


# Don't install crypt.h which causing trouble for linking.
# See https://bugzilla.redhat.com/show_bug.cgi?id=1424609
#install(FILES src/contrib/minizip/crypt.h DESTINATION "include/minizip")
install(FILES src/contrib/minizip/ioapi.h DESTINATION "include/minizip")
install(FILES src/contrib/minizip/mztools.h DESTINATION "include/minizip")
install(FILES src/contrib/minizip/unzip.h DESTINATION "include/minizip")
install(FILES src/contrib/minizip/zip.h DESTINATION "include/minizip")

if(WIN32)
    install(FILES src/contrib/minizip/iowin32.h DESTINATION "include/minizip")
endif()
