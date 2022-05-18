# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools
from conans.errors import ConanException
import shutil
import glob
import os


cmake_header='''project(WebKit)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_path(ZLIB_INCLUDE_DIR NAMES zlib.h PATHS ${CONAN_INCLUDE_DIRS_ZLIB})
find_library(ZLIB_LIBRARY NAMES ${CONAN_LIBS_ZLIB} PATHS ${CONAN_LIB_DIRS_ZLIB})
set(ZLIB_FOUND TRUE)
set(ZLIB_INCLUDE_DIRS ${ZLIB_INCLUDE_DIR})
set(ZLIB_LIBRARIES ${ZLIB_LIBRARY})
mark_as_advanced(ZLIB_LIBRARY ZLIB_INCLUDE_DIR)

find_path(PNG_INCLUDE_DIR NAMES png.h PATHS ${CONAN_INCLUDE_DIRS_PNG})
find_library(PNG_LIBRARY NAMES ${CONAN_LIBS_PNG} PATHS ${CONAN_LIB_DIRS_PNG})
set(PNG_FOUND TRUE)
set(PNG_INCLUDE_DIRS ${PNG_INCLUDE_DIR})
set(PNG_LIBRARIES ${PNG_LIBRARY})
mark_as_advanced(PNG_LIBRARY PNG_INCLUDE_DIR)

find_path(ICU_INCLUDE_DIRS NAMES unicode/utypes.h PATHS ${CONAN_INCLUDE_DIRS_ICU})
set(ICU_FOUND TRUE)
set(ICU_I18N_FOUND TRUE)
set(ICU_INCLUDE_DIRS ${ICU_INCLUDE_DIR})
set(ICU_LIBRARIES ${CONAN_LIBS_ICU})
set(ICU_I18N_LIBRARIES ${CONAN_LIBS_ICU})
mark_as_advanced(ICU_LIBRARY ICU_INCLUDE_DIR)

set(_UNUSED ${CMAKE_DISABLE_FIND_PACKAGE_Fontconfig} ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY} ${CMAKE_INSTALL_OLDINCLUDEDIR})

add_compile_definitions(_ENABLE_EXTENDED_ALIGNED_STORAGE)

if(APPLE)
    # tell ranlib to ignore empty compilation units
    set(CMAKE_C_ARCHIVE_FINISH   "<CMAKE_RANLIB> -no_warning_for_no_symbols <TARGET>")
    set(CMAKE_CXX_ARCHIVE_FINISH "<CMAKE_RANLIB> -no_warning_for_no_symbols <TARGET>")

    # prevents ar from invoking ranlib, let CMake do it
    set(CMAKE_C_ARCHIVE_CREATE   "<CMAKE_AR> qc -S <TARGET> <LINK_FLAGS> <OBJECTS>")
    set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> qc -S <TARGET> <LINK_FLAGS> <OBJECTS>")
endif()
'''


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    short_paths = True
    _cmake = None


    def system_requirements(self):
        installer = tools.SystemPackageTool()
        packages = []

        if tools.os_info.linux_distro in ["ubuntu", "debian"]:
            packages.append('libxcomposite-dev')
            packages.append('libgl1-mesa-dev')
            packages.append('libxrender-dev')
            packages.append('libdrm-dev')
            packages.append('python2.7')
            packages.append('ruby')
            packages.append('bison')
            packages.append('flex')

        if packages:
            installer.install_packages(packages)


    def build_requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        if self.settings.os == "Windows":
            self.build_requires("winflexbison_installer/[>=2.5.18]" + channel)
            self.build_requires("gperf_installer/[>=3.1]" + channel)
            self.build_requires("ruby_installer/[>=2.7.0]" + channel)
            self.build_requires("python2_installer/[>=2.7.17]" + channel)
            self.build_requires("strawberryperl_installer/[>=5.30]" + channel)


    def requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        self.requires("qt5/[>=5.12.7]" + channel)
        self.requires("libjpeg/9e" + channel)
        self.requires("libpng/[>=1.6.37]" + channel)
        self.requires("libxml2/[>=2.9.9]" + channel)
        self.requires("kf5-extra-cmake-modules/[>=5.75.0]" + channel)
        self.requires("zlib/[>=1.2.11]" + channel)
        self.requires("icu/[>=56.1]" + channel)


    def source(self):
        self.default_source()

        shutil.copy2('sources/LICENSE.LGPLv21', 'sources/LICENSE')

        # insert conan project setup
        tools.replace_in_file(os.path.join('sources', 'CMakeLists.txt'), 'project(WebKit)', cmake_header)

        # # no WebKit2 please...
        shutil.rmtree(os.path.join('sources', 'Source', 'WebKit2'))

        # # fix some (not all ;-)) issues in QtWebKit
        file = os.path.join('sources', 'Source', 'cmake', 'OptionsQt.cmake')
        tools.replace_in_file(file, 'find_package(ZLIB REQUIRED)', 'set(ZLIB_FOUND 1)')
        tools.replace_in_file(file, 'find_package(PNG REQUIRED)', 'set(PNG_FOUND 1)')
        tools.replace_in_file(file, 'find_package(ICU REQUIRED)', 'set(ICU_FOUND 1)')

        tools.replace_in_file(file, 'CHECK_QT5_PRIVATE_INCLUDE_DIRS(Gui private/qhexstring_p.h)', '#CHECK_QT5_PRIVATE_INCLUDE_DIRS(Gui private/qhexstring_p.h)')
        tools.replace_in_file(file, 'CHECK_QT5_PRIVATE_INCLUDE_DIRS(Network private/http2protocol_p.h)', '#CHECK_QT5_PRIVATE_INCLUDE_DIRS(Network private/http2protocol_p.h)')
        tools.replace_in_file(file, 'CHECK_QT5_PRIVATE_INCLUDE_DIRS(Quick private/qsgrendernode_p.h)', '#CHECK_QT5_PRIVATE_INCLUDE_DIRS(Quick private/qsgrendernode_p.h)')

        tools.replace_in_file(file, 'set(ECM_MODULE_DIR ${CMAKE_MODULE_PATH})', 'set(ECM_MODULE_DIR "${CMAKE_SOURCE_DIR}/Source/cmake")')

        tools.replace_in_file(os.path.join('sources', 'Source', 'cmake', 'FindSqlite.cmake'), 'find_library(SQLITE_LIBRARIES NAMES sqlite3', 'find_library(SQLITE_LIBRARIES NAMES sqlite3 sqlite3d')
        tools.replace_in_file(os.path.join('sources', 'CMakeLists.txt'), 'set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Source/cmake")', 'set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Source/cmake" ${CMAKE_MODULE_PATH})')
        tools.replace_in_file(os.path.join('sources', 'Source', 'PlatformQt.cmake'), 'target_compile_options(WebKit2', '#target_compile_options(WebKit2')

        tools.replace_in_file(os.path.join('sources', 'Source', 'cmake', 'WebKitMacros.cmake'), 'if (APPLE AND NOT PORT STREQUAL "GTK" AND', 'if (APPLE AND MACOS_BUILD_FRAMEWORKS AND NOT PORT STREQUAL "GTK" AND')

        tools.replace_in_file(os.path.join('sources', 'Source', 'cmake', 'OptionsQt.cmake'),
            'set(ICU_LIBRARIES ${ICU_LIBRARY_PREFIX}icuuc${CMAKE_DEBUG_POSTFIX} ${ICU_LIBRARY_PREFIX}icuin${CMAKE_DEBUG_POSTFIX} ${ICU_LIBRARY_PREFIX}icudt${CMAKE_DEBUG_POSTFIX})',
            'set(ICU_LIBRARIES ${ICU_LIBRARY_PREFIX}icuuc${CMAKE_DEBUG_POSTFIX} ${ICU_LIBRARY_PREFIX}icuin${CMAKE_DEBUG_POSTFIX} ${ICU_LIBRARY_PREFIX}icudt)')


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)

            self._cmake.definitions["CMAKE_VS_PLATFORM_TOOLSET_HOST_ARCHITECTURE"] = "x64"

            self._cmake.definitions['PORT'] = 'Qt'

            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d" if self.settings.build_type == "Debug" else '' # WebKit is horrible broken!

            self._cmake.definitions['MACOS_BUILD_FRAMEWORKS'] = False

            self._cmake.definitions['USE_SYSTEM_MALLOC'] = True
            self._cmake.definitions['USE_MINIMAL_DEBUG_INFO'] = True
            self._cmake.definitions['USE_MINIMAL_DEBUG_INFO_MSVC'] = True

            self._cmake.definitions['USE_WOFF2'] = False
            self._cmake.definitions['ENABLE_WEBKIT'] = True
            self._cmake.definitions['ENABLE_WEBKIT2'] = False
            self._cmake.definitions['ENABLE_API_TESTS'] = False
            self._cmake.definitions['ENABLE_TOOLS'] = False
            self._cmake.definitions['USE_GSTREAMER'] = False
            self._cmake.definitions['USE_LIBHYPHEN'] = False
            self._cmake.definitions['ENABLE_JIT'] = True
            self._cmake.definitions['USE_QT_MULTIMEDIA'] = False
            self._cmake.definitions['ENABLE_NETSCAPE_PLUGIN_API'] = False
            self._cmake.definitions['ENABLE_OPENGL'] = False
            self._cmake.definitions['ENABLE_PRINT_SUPPORT'] = False
            self._cmake.definitions['ENABLE_DEVICE_ORIENTATION'] = False
            self._cmake.definitions['ENABLE_BATTERY_STATUS'] = False
            self._cmake.definitions['ENABLE_GEOLOCATION'] = False
            self._cmake.definitions['ENABLE_PROXIMITY_EVENTS'] = False
            self._cmake.definitions['ENABLE_VIBRATION'] = False
            self._cmake.definitions['ENABLE_QT_WEBCHANNEL'] = False
            self._cmake.definitions['ENABLE_XSLT'] = False
            self._cmake.definitions['ENABLE_VIDEO'] = False
            self._cmake.definitions['ENABLE_SPELLCHECK'] = False

            self._cmake.definitions['CMAKE_DISABLE_FIND_PACKAGE_Fontconfig'] = True

            self._cmake.configure(source_folder='sources')
        return self._cmake


    def build(self):
        with tools.environment_append({"LC_ALL": "C", "LANG": "C"}):
            cmake = self._configure_cmake()
            cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        tools.rmdir(os.path.join(self.package_folder, "mkspecs"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "cmake"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        super().package_info()
        self.cpp_info.includedirs = ["include", "include/QtWebKit", "include/QtWebKitWidgets"]
