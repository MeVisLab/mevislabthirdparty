cmake_minimum_required(VERSION 3.14)
project(conan-wrapper)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# fix for somewhat broken GCC9 and GCC10 on Ubuntu 20.04
if(WITH_MSHSTK)
    include(CheckCCompilerFlag)
    CHECK_C_COMPILER_FLAG(-mshstk COMPILER_SUPPORTS_MSHSTK)
    if(COMPILER_SUPPORTS_MSHSTK)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mshstk")
    endif()
endif()

set(_UNUSED
  ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY}
  ${CMAKE_INSTALL_BINDIR}
  ${CMAKE_INSTALL_DATAROOTDIR}
  ${CMAKE_INSTALL_INCLUDEDIR}
  ${CMAKE_INSTALL_LIBDIR}
  ${CMAKE_INSTALL_LIBEXECDIR}
  ${CMAKE_INSTALL_OLDINCLUDEDIR}
  ${CMAKE_INSTALL_SBINDIR})

add_subdirectory(sources)
