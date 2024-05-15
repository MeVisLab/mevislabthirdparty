import os
import textwrap

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import get, copy, rmdir, save, collect_libs

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "lz4"
    version = "1.9.4"
    homepage = "https://lz4.github.io/lz4"
    description = "Extremely fast compression algorithm"
    license = "BSD-3-Clause"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "static-library"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(self,
            url=f"https://github.com/lz4/lz4/archive/v{self.version}.tar.gz",
            sha256="0b0e3aa07c8c063ddf40b082bdf7e37a1562bda40a0ff5272957f3e987e0e54b",
            destination=self.source_folder,
            strip_root=True)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.variables["BUILD_SHARED_LIBS"] = False
        tc.variables["LZ4_BUILD_CLI"] = False
        tc.variables["LZ4_BUILD_LEGACY_LZ4C"] = False
        tc.variables["LZ4_BUNDLED_MODE"] = False
        tc.variables["LZ4_POSITION_INDEPENDENT_LIB"] = True
        # Generate a relocatable shared lib on Macos
        tc.cache_variables["CMAKE_POLICY_DEFAULT_CMP0042"] = "NEW"
        # Honor BUILD_SHARED_LIBS (see https://github.com/conan-io/conan/issues/11840)
        tc.cache_variables["CMAKE_POLICY_DEFAULT_CMP0077"] = "NEW"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder=self.source_path / "build" / "cmake")
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(self, "LICENSE", src=self.source_path, dst=self.package_path / "licenses")
        copy(self, "*.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False)
        rmdir(self, self.package_path / "lib" / "cmake")
        rmdir(self, self.package_path / "lib" / "pkgconfig")
        rmdir(self, self.package_path / "share")
        self._cmake_module_file_write()

    def package_info(self):
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "LZ4")
        self.cpp_info.set_property("cmake_target_name", "lz4::lz4")
        self.cpp_info.set_property("pkg_config_name", "liblz4")
        self.cpp_info.set_property("cmake_build_modules", [self._cmake_module_file])
        self.cpp_info.libs = collect_libs(self)

    @property
    def _cmake_module_file(self):
        return os.path.join("lib", "cmake", f"{self.name}-variables.cmake")

    def _cmake_module_file_write(self):
        file = self.package_path / self._cmake_module_file
        content = textwrap.dedent("""\
            set(LZ4_LIBRARY ${LZ4_LIBRARIES})
            set(LZ4_LINK_LIBRARIES ${LZ4_LIBRARIES})
            """)
        save(self, file, content)
