# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'
    generators = "cmake_find_package"

    def source(self):
        self.default_source()
        tools.replace_in_file('sources/stlab/CMakeLists.txt',
          'concurrency/channel.hpp', 
          '    pre_exit.hpp\n'\
          '    concurrency/channel.hpp\n'\
          '    concurrency/await.hpp\n'\
          '    concurrency/concurrency.hpp\n'\
          '    concurrency/ready_future.hpp\n'\
          '    concurrency/serial_queue.hpp\n'\
          '    concurrency/set_current_thread_name.hpp')


    def layout(self):
        cmake_layout(self)

    def generate(self):
        toolchain = CMakeToolchain(self)
        toolchain.variables["CMAKE_CXX_STANDARD"] = "17"
        toolchain.variables["BUILD_TESTING"] = "OFF"

        toolchain.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder="sources", )
        #cmake.build()


    def package(self):
        cmake = CMake(self)
        cmake.install()

        tools.rmdir(os.path.join(self.package_folder, 'share'))
        tools.rmdir(os.path.join(self.package_folder, 'bin'))

        self.default_package()


    def package_info(self):
        self.default_package_info()
        if self.settings.os == "Linux":
            self.cpp_info.libs.extend(["pthread"])
