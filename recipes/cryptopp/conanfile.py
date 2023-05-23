# -*- coding: utf-8 -*-
from conans import ConanFile
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import export_conandata_patches, get
import shutil
import os

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'
    generators = "cmake_find_package"

    def export_sources(self):
        export_conandata_patches(self)

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(self, **self.conan_data["sources"]["source"], strip_root=True)
        get(self, **self.conan_data["sources"]["cmake"], destination=os.path.join(self.source_folder, "cryptopp-cmake"), strip_root=True)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.cache_variables["CRYPTOPP_SOURCES"] = self.source_folder.replace("\\", "/")
        tc.cache_variables["CRYPTOPP_BUILD_TESTING"] = False
        tc.cache_variables["CRYPTOPP_BUILD_DOCUMENTATION"] = False
        tc.cache_variables["CRYPTOPP_USE_INTERMEDIATE_OBJECTS_TARGET"] = False
        tc.cache_variables["CMAKE_DEBUG_POSTFIX"] = "d"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder="cryptopp-cmake")
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        shutil.rmtree(os.path.join(self.package_folder, "share"))
        self.default_package()
