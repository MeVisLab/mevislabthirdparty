# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import CMake


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None


    def _configure_cmake(self):
        if not self._cmake:
            if tools.Version(self.version).major != "2":
                self.create_cmake_wrapper()
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.configure()
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        if tools.Version(self.version).major != "2":
            cmake = self._configure_cmake()
            cmake.install()
        else:
            self.copy("*.h", dst="include/xercesc", src="sources/src/xercesc/", keep_path=True)
            self.copy("*.c", dst="include/xercesc", src="sources/src/xercesc/", keep_path=True)
            self.copy("*.hpp", dst="include/xercesc", src="sources/src/xercesc/", keep_path=True)
            self.copy("*.so*", dst="lib", keep_path=False)
            self.copy("*.dylib*", dst="lib", keep_path=False)
            self.copy("*.a", dst="lib", keep_path=False)
            self.copy("*.dll", dst="bin", keep_path=False)
            self.copy("*.pdb", dst="bin", keep_path=False, excludes="*vc*.pdb")
            self.copy("*.lib", dst="lib", keep_path=False)

        self.default_package()


    def package_info(self):
        self.default_package_info()

        self.cpp_info.frameworks.extend(["CoreFoundation", "CoreServices"])
        if self.settings.compiler == "Visual Studio":
            self.cpp_info.system_libs.append("advapi32")
            self.cpp_info.system_libs.append("ws2_32")
