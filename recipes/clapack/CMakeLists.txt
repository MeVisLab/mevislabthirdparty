cmake_minimum_required(VERSION 3.14)
project(conan-wrapper LANGUAGES C)

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

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

if(MSVC)
  # This is a third party project. So we don't want to patch the code as far
  # as avoidable. However, this project generates a large number of
  # compiler warnings, making the output difficult to read.
  # Therefore we disable some warnings.

  # disable C4244 (implicit integer truncation)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4244")
  set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} /wd4244")

  # disable C4554 (check operator precedence for possible error; use parentheses to clarify precedence)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4554")
  set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} /wd4554")

  # disable C4996 (the compiler encountered a deprecated declaration)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4996")
  set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} /wd4996")

  # disable C4267 (conversion from 'size_t' to 'type', possible loss of data)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4267")
  set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} /wd4267")
endif()

add_compile_definitions("BUILD_CLAPACK")

add_subdirectory(sources)
