cmake_minimum_required(VERSION 3.14)
project(conan-wrapper)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# prevent CMake from complaining about this external unused variable.
set(_UNUSED
  ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY}
  ${CMAKE_INSTALL_BINDIR}
  ${CMAKE_INSTALL_DATAROOTDIR}
  ${CMAKE_INSTALL_INCLUDEDIR}
  ${CMAKE_INSTALL_LIBDIR}
  ${CMAKE_INSTALL_LIBEXECDIR}
  ${CMAKE_INSTALL_OLDINCLUDEDIR}
  ${CMAKE_INSTALL_SBINDIR}
)

if(TARGET CONAN_PKG::ZLIB)
    set(ZLIB_FOUND TRUE)
endif()

if(TARGET CONAN_PKG::BZIP2)
    set(BZIP2_FOUND TRUE)
endif()

if(TARGET CONAN_PKG::PNG)
    set(PNG_FOUND TRUE)
endif()

add_subdirectory(sources)
