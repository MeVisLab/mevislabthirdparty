import textwrap
import os

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import get, collect_libs, copy, rmdir, save

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "libaec"
    version = "1.1.4"
    homepage = "https://gitlab.dkrz.de/k202009/libaec"
    description = "Adaptive Entropy Coding library"
    license = "BSD-2-Clause"
    package_type = "shared-library"
    settings = "os", "compiler", "build_type", "arch"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="b910e47d526ecbfb802ba6cdc6d262420f6ca436e87edfb57a32966f5148f762",
            url=f"https://gitlab.dkrz.de/k202009/libaec/-/archive/v{self.version}/libaec-v{self.version}.tar.gz",
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.cache_variables["CMAKE_POLICY_DEFAULT_CMP0077"] = "NEW"

        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_TESTING"] = False
        tc.variables["BUILD_STATIC_LIBS"] = False
        tc.variables["CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS"] = True
        tc.variables["CMAKE_C_VISIBILITY_PRESET"] = "default"
        tc.variables["CMAKE_CXX_VISIBILITY_PRESET"] = "default"
        tc.variables["CMAKE_VISIBILITY_INLINES_HIDDEN"] = False
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"

        tc.variables["SKIP_INSTALL_ALL"] = False
        tc.variables["SKIP_INSTALL_LIBRARIES"] = False
        tc.variables["SKIP_INSTALL_HEADERS"] = False
        tc.variables["SKIP_INSTALL_FILES"] = True

        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, pattern="LICENSE.txt", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(
            self,
            "*.pdb",
            src=self.build_folder,
            dst=os.path.join(self.package_folder, "bin"),
            keep_path=False,
            excludes="*vc???.pdb",
        )
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake", "libaec"))
        rmdir(self, os.path.join(self.package_folder, "share"))
        self._cmake_module_file_write()

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/MathisRosenhauer/libaec@v{self.version}")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "libaec")
        self.cpp_info.set_property("cmake_target_name", "libaec::libaec")
        self.cpp_info.set_property("cmake_build_modules", [self._cmake_module_file])
        for lib in collect_libs(self):
            comp = lib.removesuffix("_d")
            comp = "sz" if comp == "szip" else comp
            self.cpp_info.components[comp].libs = [lib]
            self.cpp_info.components[comp].set_property("cmake_target_name", f"libaec::{comp}")

    @property
    def _cmake_module_file(self):
        return os.path.join("lib", "cmake", f"{self.name}-variables.cmake")

    def _cmake_module_file_write(self):
        file = os.path.join(self.package_folder, self._cmake_module_file)
        content = textwrap.dedent(
            f"""\
            set(libaec_FOUND TRUE)
            set(SZIP_FOUND TRUE)
            set(libaec_VERSION "{self.version}")
            set(SZIP_VERSION "{self.version}")
            set(SZIP_LIBRARIES "libaec::libaec")
            """
        )
        save(self, file, content)
