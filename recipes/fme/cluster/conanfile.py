from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMakeToolchain, CMake
from conan.tools.files import copy, collect_libs

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "cluster"
    version = "1.59"  # ???
    homepage = "http://bonsai.hgc.jp/~mdehoon/software/cluster/software.htm"  # ???
    description = "the C Clustering Library"  # ???
    license = "MIT"
    package_type = "static-library"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "static-library"
    exports_sources = ["sources/*"]

    # FIXME!
    # The version from FME we build here is quite different from the above original code.

    def layout(self):
        cmake_layout(self, src_folder="sources")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = False
        tc.variables['CMAKE_POSITION_INDEPENDENT_CODE'] = True
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_path, dst=self.package_path / "licenses")
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "Cluster")
        self.cpp_info.set_property("cmake_target_name", "Cluster::Cluster")
        self.cpp_info.set_property("pkg_config_name", "Cluster")
        self.cpp_info.set_property("mevislab_prosdk_exclude", True)
        self.cpp_info.libs = collect_libs(self)
