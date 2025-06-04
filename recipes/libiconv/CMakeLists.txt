cmake_minimum_required(VERSION 3.27)
project(libiconv C)

set(_unused
    ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY}
    ${CMAKE_INSTALL_BINDIR}
    ${CMAKE_INSTALL_DATAROOTDIR}
    ${CMAKE_INSTALL_INCLUDEDIR}
    ${CMAKE_INSTALL_LIBDIR}
    ${CMAKE_INSTALL_LIBEXECDIR}
    ${CMAKE_INSTALL_OLDINCLUDEDIR}
    ${CMAKE_INSTALL_SBINDIR}
)

include(${CMAKE_TOOLCHAIN_FILE})

set(LIBICONV_DYNAMIC "1")

if(WIN32)
  set(HAVE_WCHAR_T "1 /*HAVE_WCHAR_T*/")
  set(USE_MBSTATE_T "0 /*USE_MBSTATE_T*/")
  set(BROKEN_WCHAR_H "0 /*BROKEN_WCHAR_H*/")
  set(HAVE_VISIBILITY "0 /*HAVE_VISIBILITY*/")

  configure_file(src/config.h.in config.h)
  file(READ "${CMAKE_CURRENT_BINARY_DIR}/config.h" _contents)
  string(REPLACE "#undef HAVE_WORKING_O_NOFOLLOW" "#define HAVE_WORKING_O_NOFOLLOW 0" _contents "${_contents}")
  string(REPLACE "#undef HAVE_MBRTOWC" "#define HAVE_MBRTOWC 1" _contents "${_contents}")
  string(REPLACE "#undef HAVE_MBSINIT" "#define HAVE_MBSINIT 1" _contents "${_contents}")
  string(REPLACE "#undef HAVE_WCRTOMB" "#define HAVE_WCRTOMB 1" _contents "${_contents}")
  string(REPLACE "#undef ICONV_CONST" "#define ICONV_CONST const" _contents "${_contents}")
  string(REPLACE "#undef EILSEQ" "" _contents "${_contents}")
  string(REPLACE "#undef HAVE_STDBOOL_H" "#define HAVE_STDBOOL_H 1" _contents "${_contents}")
  string(REPLACE "#undef WORDS_LITTLEENDIAN" "#define WORDS_LITTLEENDIAN 1" _contents "${_contents}")
  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/config.h" "${_contents}")

  configure_file(src/libcharset/include/localcharset.h.build.in localcharset.h)
  configure_file(src/include/iconv.h.build.in iconv.h)
else()
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/autoconf)
  execute_process(
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/src/configure --enable-relocatable --enable-shared --disable-static --without-libiconv-prefix --without-libintl-prefix
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/autoconf
  )

  configure_file(${CMAKE_CURRENT_BINARY_DIR}/autoconf/config.h config.h @ONLY)
  configure_file(${CMAKE_CURRENT_BINARY_DIR}/autoconf/include/iconv.h iconv.h @ONLY)
  configure_file(${CMAKE_CURRENT_BINARY_DIR}/autoconf/libcharset/include/localcharset.h localcharset.h @ONLY)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_definitions(-DLIBDIR -D_CRT_SECURE_NO_WARNINGS)

add_library(libcharset SHARED src/libcharset/lib/localcharset.c)
target_include_directories(libcharset PUBLIC $<INSTALL_INTERFACE:src/include>)

add_library(libiconv SHARED src/lib/iconv.c)
target_link_libraries(libiconv PRIVATE libcharset)
target_include_directories(libiconv PUBLIC $<INSTALL_INTERFACE:src/include>)

install(TARGETS libcharset libiconv
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/iconv.h
  ${CMAKE_CURRENT_BINARY_DIR}/localcharset.h
  DESTINATION include
)

if(MSVC)
  install(FILES $<TARGET_PDB_FILE:libcharset> DESTINATION bin OPTIONAL)
  install(FILES $<TARGET_PDB_FILE:libiconv>   DESTINATION bin OPTIONAL)
endif()
