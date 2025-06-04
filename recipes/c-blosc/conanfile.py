import os
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get, rmdir, collect_libs

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "c-blosc"
    version = "1.21.6"
    homepage = "https://www.blosc.org"
    description = "An extremely fast, multi-threaded, meta-compressor library"
    license = "BSD-3-Clause"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("lz4/[>=1.9.4]")
        #self.requires("snappy/[>=1.1.9]")
        self.requires("zlib/[>=1.2.13]")
        self.requires("zstd/[>=1.5.2]")

    def source(self):
        get(self,
            sha256="9fcd60301aae28f97f1301b735f966cc19e7c49b6b4321b839b4579a0c156f38",
            url=f"https://github.com/Blosc/c-blosc/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True
        )
        rmdir(self, self.source_path / "cmake")
        rmdir(self, self.source_path / "internal-complibs")

    def generate(self):
        tc = CMakeToolchain(self)

        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"

        tc.variables["BLOSC_INSTALL"] = True

        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        tc.variables["BUILD_STATIC"] = False
        tc.variables["BUILD_SHARED"] = True
        tc.variables["BUILD_TESTS"] = False
        tc.variables["BUILD_FUZZERS"] = False
        tc.variables["BUILD_BENCHMARKS"] = False

        tc.variables["PREFER_EXTERNAL_LZ4"] = True
        tc.variables["PREFER_EXTERNAL_Snappy"] = True
        tc.variables["PREFER_EXTERNAL_ZLIB"] = True
        tc.variables["PREFER_EXTERNAL_ZSTD"] = True

        tc.variables["CMAKE_REQUIRE_FIND_PACKAGE_LZ4"] = True
        tc.variables["CMAKE_REQUIRE_FIND_PACKAGE_Snappy"] = True
        tc.variables["CMAKE_REQUIRE_FIND_PACKAGE_ZLIB"] = True
        tc.variables["CMAKE_REQUIRE_FIND_PACKAGE_Zstd"] = True

        def _has_dependency(name):
            try:
                self.dependencies.get(name)
                return True
            except KeyError:
                return False

        tc.variables["DEACTIVATE_LZ4"] = not _has_dependency("lz4")
        tc.variables["DEACTIVATE_SNAPPY"] = not _has_dependency("snappy")
        tc.variables["DEACTIVATE_ZLIB"] = not _has_dependency("zlib")
        tc.variables["DEACTIVATE_ZSTD"] = not _has_dependency("zstd")

        tc.variables["CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP"] = True

        tc.cache_variables["CMAKE_POLICY_DEFAULT_CMP0042"] = "NEW"
        tc.generate()

        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE.txt", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(self, "*.pdb", src=self.build_folder, dst=os.path.join(self.package_folder, "bin"), keep_path=False, excludes="*vc???.pdb")
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE for c-blosc yet (there is one for c-blosc2)!
        self.cpp_info.set_property("purl", f"pkg:github/Blosc/c-blosc@v{self.version}")
        self.cpp_info.set_property("pkg_config_name", "blosc")
        self.cpp_info.libs = collect_libs(self)
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.extend(["m", "pthread"])
