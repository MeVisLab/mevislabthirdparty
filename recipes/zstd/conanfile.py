import os
import textwrap

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import collect_libs
from conan.tools.files import get, copy, rmdir, save

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "zstd"
    version = "1.5.7"
    homepage = "https://facebook.github.io/zstd"
    description = "Zstandard - Fast real-time compression algorithm"
    license = "BSD-3-Clause"
    package_type = "static-library"
    settings = "os", "arch", "compiler", "build_type"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="7897bc5d620580d9b7cd3539c44b59d78f3657d33663fe97a145e07b4ebd69a4",
            url=f"https://github.com/facebook/zstd/archive/v{self.version}.zip",
            destination=self.source_folder,
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["BUILD_SHARED_LIBS"] = False
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = self.settings.compiler != "msvc"
        tc.variables["ZSTD_BUILD_PROGRAMS"] = False
        tc.variables["ZSTD_BUILD_STATIC"] = not tc.variables["BUILD_SHARED_LIBS"]
        tc.variables["ZSTD_BUILD_SHARED"] = tc.variables["BUILD_SHARED_LIBS"]
        tc.variables["ZSTD_LEGACY_SUPPORT"] = True
        tc.variables["ZSTD_MULTITHREAD_SUPPORT"] = True
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder=os.path.join(self.source_folder, "build", "cmake"))
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(self, "*.pdb", src=self.build_folder, dst=os.path.join(self.package_folder, "bin"), keep_path=False)
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        self._cmake_module_file_write()

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:facebook:zstandard:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/facebook/zstd@v{self.version}")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "zstd")
        self.cpp_info.set_property("cmake_target_name", "zstd::zstd")
        self.cpp_info.set_property("cmake_target_aliases", ["zstd::libzstd_static"])
        self.cpp_info.set_property("cmake_build_modules", [self._cmake_module_file])
        self.cpp_info.set_property("cmake_find_package", [self._cmake_module_file])
        self.cpp_info.set_property("pkg_config_name", "zstd")
        self.cpp_info.libs = collect_libs(self)
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.append("pthread")

    @property
    def _cmake_module_file(self):
        return os.path.join("lib", "cmake", f"{self.name}-variables.cmake")

    def _cmake_module_file_write(self):
        file = os.path.join(self.package_folder, self._cmake_module_file)
        content = textwrap.dedent(
            f"""\
            set(ZSTD_FOUND TRUE)
            set(ZSTD_LIBRARY ${{zstd_LIBRARIES}})
            set(ZSTD_LIBRARIES ${{zstd_LIBRARIES}})
            set(ZSTD_INCLUDE_DIR ${{zstd_INCLUDE_DIR}})
            set(ZSTD_INCLUDE_DIRS ${{zstd_INCLUDE_DIR}})
            """
        )
        save(self, file, content)
