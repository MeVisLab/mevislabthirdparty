from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import patch, collect_libs, copy, get, rmdir
from conan.tools.microsoft import is_msvc
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "assimp"
    version = "5.4.3"
    homepage = "https://www.assimp.org"
    description = "library to import and export various 3d-model-formats including scene-post-processing to generate missing render data"
    license = "BSD-3-Clause"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("zlib/[>=1.2.13]")

    def source(self):
        get(
            self,
            sha256="795c29716f4ac123b403e53b677e9f32a8605c4a7b2d9904bfaae3f4053b506d",
            url=f"https://github.com/assimp/assimp/archive/v{self.version}.zip",
            strip_root=True,
        )
        patch(self, patch_file="patches/001-no_pkgconfig_minizip.patch")
        patch(self, patch_file="patches/002-zlib_names.patch")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["ASSIMP_WARNINGS_AS_ERRORS"] = False
        tc.variables["ASSIMP_DOUBLE_PRECISION"] = False
        tc.variables["ASSIMP_BUILD_ASSIMP_TOOLS"] = False
        tc.variables["ASSIMP_BUILD_TESTS"] = False
        tc.variables["ASSIMP_BUILD_SAMPLES"] = False
        tc.variables["ASSIMP_BUILD_MINIZIP"] = False
        tc.variables["ASSIMP_INSTALL_PDB"] = False
        tc.variables["ASSIMP_IGNORE_GIT_HASH"] = True
        tc.variables["ASSIMP_BUILD_ZLIB"] = False

        # disable Collada module, see CVE-2022-45748 / https://github.com/assimp/assimp/issues/4286
        tc.variables["ASSIMP_BUILD_COLLADA_IMPORTER"] = False
        tc.variables["ASSIMP_BUILD_COLLADA_EXPORTER"] = False

        if self.settings.os == "Windows":
            tc.preprocessor_definitions["NOMINMAX"] = 1
        tc.cache_variables["CMAKE_POLICY_DEFAULT_CMP0077"] = "NEW"  # to avoid warnings

        tc.generate()

        cd = CMakeDeps(self)
        cd.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(self, "*.pdb", src=os.path.join(self.build_folder, "bin"), dst=os.path.join(self.package_folder, "bin"), keep_path=False)
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:assimp:assimp:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("base_purl", "github/assimp/assimp")
        self.cpp_info.set_property("cmake_file_name", "assimp")
        self.cpp_info.set_property("cmake_target_name", "assimp::assimp")
        self.cpp_info.set_property("pkg_config_name", "assimp")
        self.cpp_info.libs = collect_libs(self)
        if is_msvc(self):
            self.cpp_info.defines.append("ASSIMP_DLL")
        if self.settings.os == "Linux":
            self.cpp_info.system_libs = ["rt", "m", "pthread"]
