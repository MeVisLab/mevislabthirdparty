from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import collect_libs
from conan.tools.files import copy, get, patch

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "easybmp"
    version = "1.06"
    homepage = "https://easybmp.sourceforge.net"
    description = "Cross-Platform Windows Bitmap Library"
    license = "BSD-3-Clause"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "static-library"
    exports_sources = "patches/*.patch", "CMakeLists.txt"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(self,
            url=f"https://sourceforge.net/projects/easybmp/files/easybmp/EasyBMP Library Files Version {self.version}/EasyBMP_{self.version}.zip/download",
            sha256="1ef19cc92b18a8ab272bf68a4ce8ce862d08208d4e675560c33fbd04d997c469",
            strip_root=False)
        patch(self, patch_file="patches/001-mevis.patch")
        copy(self, "CMakeLists.txt", src=self.source_path.parent, dst=self.source_path)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS"] = True
        tc.variables["BUILD_SHARED_LIBS"] = False
        tc.variables['CMAKE_POSITION_INDEPENDENT_CODE'] = True
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "*.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False)
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE?
        # self.cpp_info.set_property("purl", "")  # Real source is at sourceforge - "sourceforge/easybmp"?
        self.cpp_info.set_property("cmake_file_name", "easybmp")
        self.cpp_info.set_property("cmake_target_name", "EasyBMP::EasyBMP")
        self.cpp_info.libs = collect_libs(self)


