# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import CMake
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None

    def system_requirements(self):
        installer = tools.SystemPackageTool()
        packages = []

        if tools.os_info.linux_distro in ["ubuntu", "debian"]:
            packages.append('libglu1-mesa-dev')

        if packages:
            installer.install_packages(packages)


    def _configure_cmake(self):
        if not self._cmake:
            self.create_cmake_wrapper(add_subdirectory="sources/build/cmake")
            self._cmake = CMake(self)
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.definitions["CMAKE_POSITION_INDEPENDENT_CODE"] = self.settings.os != "Windows"
            if self.settings.os == 'Windows':
                self._cmake.definitions["GLEW_STATIC"] = True
            self._cmake.configure()
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build(target='glew')
        if self.settings.build_type == 'Release':
            cmake.build(target='glewinfo')
            cmake.build(target='visualinfo')


    def package(self):
        self.copy("*.h", dst="include/GL", src="sources/include", keep_path=False)
        self.copy("*", src="bin", dst="bin", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False, symlinks=True)
        self.copy("*.lib", dst="lib", keep_path=False, symlinks=True)
        self.copy("*.dylib*", dst="lib", keep_path=False, symlinks=True)
        self.copy("*.so*", dst="lib", keep_path=False, symlinks=True)
        self.copy("*.pdb", src="bin", dst="bin")

        if os.path.exists(os.path.join(self.package_folder, 'lib', 'Makefile.solaris')):
            os.remove(os.path.join(self.package_folder, 'lib', 'Makefile.solaris'))
        if os.path.exists(os.path.join(self.package_folder, 'lib', 'Makefile.solaris-gcc')):
            os.remove(os.path.join(self.package_folder, 'lib', 'Makefile.solaris-gcc'))

        self.patch_binaries(executables=['visualinfo', 'glewinfo'] if self.settings.build_type == 'Release' else [])
        self.default_package()


    def package_info(self):
        self.default_package_info()

        if tools.os_info.is_macos:
            self.cpp_info.exelinkflags.append("-framework OpenGL")
        elif tools.os_info.is_windows:
            self.cpp_info.libs.append("opengl32")
        else:
            self.cpp_info.libs.append("GL")
