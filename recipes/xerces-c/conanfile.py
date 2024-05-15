from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import collect_libs, copy, get, patch
from conan.tools.scm import Version

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "xerces-c"
    version = "2.7.0"
    homepage = "http://xml.apache.org/xerces-c"
    description = "A validating XML parser written in a portable subset of C++"
    license = "Apache-2.0"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "CMakeLists.txt", "patches/*.patch"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        v = Version(self.version)
        get(self,
            url=f"https://archive.apache.org/dist/xml/xerces-c/Xerces-C_{v.major}_{v.minor}_{v.patch}/source/xerces-c-src_{v.major}_{v.minor}_{v.patch}.tar.gz",
            sha256="77fae8a1e7aa58007115c939aa68fd5028da79c481fc457dfce546b50c9dfda5",
            strip_root=True
        )
        patch(self, patch_file="patches/001-macos.patch")
        patch(self, patch_file="patches/002-windows_64bit.patch")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.cache_variables["CONAN_XERCES_VERSION"] = f"{self.version}"
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables['BUILD_SHARED_LIBS'] = True
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder=self.source_path.parent)
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_path, dst=self.package_path / "licenses")
        copy(self, "*.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False, excludes="*vc???.pdb")
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "XercesC")
        self.cpp_info.set_property("cmake_target_name", "XercesC::XercesC")
        self.cpp_info.set_property("display_name", "Xerces-C++")
        self.cpp_info.libs = collect_libs(self)
        self.cpp_info.frameworks.extend(["CoreFoundation", "CoreServices"])
        if self.settings.os == "Windows":
            self.cpp_info.system_libs.append("advapi32")
            self.cpp_info.system_libs.append("ws2_32")
