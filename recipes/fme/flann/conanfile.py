from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMakeToolchain, CMake, CMakeDeps
from conan.tools.files import get, patch, rmdir, copy, collect_libs

required_conan_version = ">=2.2.2"

class ConanRecipe(ConanFile):
    name = "flann"
    version = "1.9.2"
    homepage = "https://github.com/flann-lib/flann"
    description = "FLANN - Fast Library for Approximate Nearest Neighbors"
    license = "BSD-3-Clause"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = ["patches/*"]

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("lz4/[>=1.9.3]", transitive_headers=True, transitive_libs=True)
        self.requires("hdf5/[>=1.14.2]", transitive_headers=True, transitive_libs=True)

    def source(self):
        get(self,
            sha256="e26829bb0017f317d9cc45ab83ddcb8b16d75ada1ae07157006c1e7d601c8824",
            url=f"https://github.com/flann-lib/flann/archive/refs/tags/{self.version}.tar.gz",
            strip_root=True
            )
        patch(self, patch_file="patches/001-export_symbols.patch")
        patch(self, patch_file="patches/002-arm_neon_include.patch")
        patch(self, patch_file="patches/003-conan_lz4.patch")
        # remove embedded lz4
        rmdir(self, self.source_path / "src" / "cpp" / "flann" / "ext")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = False
        tc.variables['CMAKE_POSITION_INDEPENDENT_CODE'] = True
        tc.variables["USE_OPENMP"] = False
        tc.variables["BUILD_C_BINDINGS"] = True
        tc.variables["BUILD_DOC"] = False
        tc.variables["BUILD_EXAMPLES"] = False
        tc.variables["BUILD_TESTS"] = False
        tc.variables["BUILD_MATLAB_BINDINGS"] = False
        tc.variables["BUILD_PYTHON_BINDINGS"] = False
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

        copy(self, "*.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False, excludes="*vc???.pdb")
        copy(self, "COPYING", src=self.source_path, dst=self.package_path / "licenses")

        rmdir(self, self.package_path / "lib" / "cmake")
        rmdir(self, self.package_path / "lib" / "pkgconfig")

        # Remove MS runtime files
        for pattern in ["concrt*.dll", "msvcp*.dll", "vcruntime*.dll"]:
            for lib in (self.package_path / "bin").glob(pattern):
                lib.unlink()

        # Remove static libraries
        static_libs = ["*flann_cpp_s.*", "*flann_cpp_sd.*", "*flann_s.*", "*flann_sd.*"]
        for pattern in static_libs:
            for lib in (self.package_path / "lib").glob(pattern):
                lib.unlink()

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("base_purl", "github/flann-lib/flann")
        self.cpp_info.set_property("cmake_file_name", "FLANN")
        self.cpp_info.set_property("cmake_target_name", "FLANN::FLANN")
        self.cpp_info.set_property("pkg_config_name", "FLANN")
        self.cpp_info.set_property("mevislab_prosdk_exclude", True)
        self.cpp_info.libs = collect_libs(self)
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.append("m")
