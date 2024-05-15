cmake_minimum_required(VERSION 3.27)
project(hunspell VERSION "${CONAN_PROJECT_VERSION}" LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-fvisibility=hidden HAVE_VISIBILITY)
configure_file(src/src/hunspell/hunvisapi.h.in hunvisapi.h @ONLY)

add_library(hunspell)

target_sources(hunspell PRIVATE
    src/src/hunspell/affentry.cxx
    src/src/hunspell/affixmgr.cxx
    src/src/hunspell/csutil.cxx
    src/src/hunspell/filemgr.cxx
    src/src/hunspell/hashmgr.cxx
    src/src/hunspell/hunspell.cxx
    src/src/hunspell/hunzip.cxx
    src/src/hunspell/phonet.cxx
    src/src/hunspell/replist.cxx
    src/src/hunspell/suggestmgr.cxx
)

if(MSVC)
  target_compile_options(hunspell PRIVATE /wd4267 /wd4996)
endif()

target_compile_definitions(hunspell PRIVATE BUILDING_LIBHUNSPELL)
set_target_properties(hunspell PROPERTIES CXX_VISIBILITY_PRESET hidden)
set_target_properties(hunspell PROPERTIES VISIBILITY_INLINES_HIDDEN YES)
set_target_properties(hunspell PROPERTIES VERSION "${PROJECT_VERSION}" SOVERSION "${PROJECT_VERSION_MAJOR}")

include(GNUInstallDirs)
install(TARGETS hunspell
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(FILES
    src/src/hunspell/hunspell.hxx
    src/src/hunspell/hunspell.h
    src/src/hunspell/w_char.hxx
    src/src/hunspell/atypes.hxx

    ${PROJECT_BINARY_DIR}/hunvisapi.h
  DESTINATION
    ${CMAKE_INSTALL_INCLUDEDIR}/hunspell
)

install(FILES
    src/COPYING
    src/COPYING.MPL
    src/COPYING.LESSER
  DESTINATION
    licenses
)

install(FILES src/license.hunspell RENAME LICENSE DESTINATION licenses)
