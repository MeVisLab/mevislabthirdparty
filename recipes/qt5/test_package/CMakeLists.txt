cmake_minimum_required(VERSION 3.12)
project(test_package CXX)

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
  ${CONAN_COMPILER_VERSION}
  ${CONAN_COMPILER}
)

# enforce a current C++ standard without proprietary extensions.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# load and setup conan
set(CONAN_DISABLE_CHECK_COMPILER TRUE)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Qt5 COMPONENTS Core Gui Widgets WebEngineCore WebEngineWidgets REQUIRED)

# check that Qt uses different library names for DEBUG and RELEASE mode
function(assert_qt5_library_name expected location)
    cmake_path(GET location STEM libname)
    string(COMPARE NOTEQUAL "${expected}" "${libname}" not_equal)
    if(not_equal)
        cmake_path(GET location PARENT_PATH libpath)
        message(FATAL_ERROR "Unexpected Qt5::Core library name (expected: \"${expected}\", actual: \"${libname}\" found in \"${libpath}\")")
    endif()
endfunction()

get_target_property(location Qt5::Core IMPORTED_LOCATION)
get_target_property(location_rls Qt5::Core IMPORTED_LOCATION_RELEASE)
get_target_property(location_dbg Qt5::Core IMPORTED_LOCATION_DEBUG)

message(STATUS "IMPORTED_LOCATION: ${location}")
message(STATUS "IMPORTED_LOCATION_RELEASE: ${location_rls}")
message(STATUS "IMPORTED_LOCATION_DEBUG: ${location_dbg}")

if(NOT location_dbg AND NOT location_rls)
    message(FATAL_ERROR "Failed to get IMPORTED_LOCATION_RELEASE/IMPORTED_LOCATION_DEBUG for Qt5::Core")
endif()

set(_expected "")
set(_actual "")

if(location_dbg AND NOT location_rls)
    set(_actual "${location_dbg}")

    if(WIN32)
        set(_expected "Qt5Cored")
    elseif(APPLE)
        set(_expected "libQt5Core_debug")
    else()
        set(_expected "libQt5Cored")
    endif()
elseif(NOT location_dbg AND location_rls)
    set(_actual "${location_rls}")

    if(WIN32)
        set(_expected "Qt5Core")
    else()
        set(_expected "libQt5Core")
    endif()
else()
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        if(NOT location_dbg)
            message(FATAL_ERROR "Failed to get IMPORTED_LOCATION_DEBUG for Qt5::Core")
        endif()

        set(_actual "${location_dbg}")

        if(WIN32)
            set(_expected "Qt5Cored")
        elseif(APPLE)
            set(_expected "libQt5Core_debug")
        else()
            set(_expected "libQt5Cored")
        endif()
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        if(NOT location_rls)
            message(FATAL_ERROR "Failed to get IMPORTED_LOCATION_RELEASE for Qt5::Core")
        endif()

        set(_actual "${location_rls}")

        if(WIN32)
            set(_expected "Qt5Core")
        else()
            set(_expected "libQt5Core")
        endif()
    else()
        message(FATAL_ERROR "Failed to select CMAKE_BUILD_TYPE")
    endif()
endif()

assert_qt5_library_name("${_expected}" "${_actual}")
