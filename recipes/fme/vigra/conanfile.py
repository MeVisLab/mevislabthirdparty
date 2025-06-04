from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout
from conan.tools.files import get, patch, copy, rmdir, collect_libs
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "vigra"
    version = "1.12.2"
    homepage = "https://ukoethe.github.io/vigra"
    description = "a generic C++ library for image analysis"
    license = "MIT"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "shared-library"
    exports_sources = ["patches/*"]

    def requirements(self):
        self.requires("boost/[>=1.75.0]")
        self.requires("hdf5/[>=1.14.2]", transitive_headers=True, transitive_libs=True)
        self.requires("libpng/[>=1.6.37]")
        self.requires("tiff/[>=4.1.0]")
        self.requires("zlib/[>=1.2.11]")
        self.requires("libjpeg-turbo/[>=2.1.5]")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="e927477a8a0bcdabcaab914e425782f7eba82711dbaca02538dfda79476f6b7e",
            url=f"https://github.com/ukoethe/vigra/archive/refs/tags/Version-{self.version.replace('.', '-')}.tar.gz",
            strip_root=True,
        )

        patch(self, patch_file="patches/001-cpp17.patch")
        patch(
            self,
            patch_file="patches/003-namespace.patch",
            patch_description="Temporary fix for MSVC compiler bug, see "
            "https://developercommunity.visualstudio.com/"
            "t/VS-17111:-Compiler-fails-to-match-defi/10728187",
        )

        # rather use conan version of this file:
        os.remove(os.path.join(self.source_folder, "config", "FindHDF5.cmake"))

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["BUILD_TESTS"] = False
        tc.variables["CREATE_CTEST_TARGETS"] = False
        tc.variables["WITH_VIGRANUMPY"] = False
        tc.variables["CMAKE_DISABLE_FIND_PACKAGE_FFTW3"] = True
        tc.variables["CMAKE_DISABLE_FIND_PACKAGE_FFTW3F"] = True
        tc.variables["CMAKE_DISABLE_FIND_PACKAGE_Doxygen"] = True
        tc.variables["CMAKE_DISABLE_FIND_PACKAGE_Python"] = True
        tc.generate()

        cd = CMakeDeps(self)
        cd.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

        copy(self, "*.pdb", src=self.source_folder, dst=os.path.join(self.package_folder, "bin"), keep_path=False, excludes="*vc???.pdb")
        copy(self, "LICENSE.txt", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        rmdir(self, os.path.join(self.package_folder, "doc"))
        rmdir(self, os.path.join(self.package_folder, "lib", "vigra"))

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/ukoethe/vigra@Version-{self.version.replace('.', '-')}")
        self.cpp_info.set_property("display_name", "VIGRA Computer Vision Library")
        self.cpp_info.set_property("mevislab_prosdk_exclude", True)
        self.cpp_info.defines += ["HasHDF5"]
        self.cpp_info.libs = collect_libs(self)
