from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import collect_libs, copy, get, rmdir
from conan.tools.scm import Version

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "openjpeg"
    version = "2.5.2"
    homepage = "https://www.openjpeg.org"
    description = "Open-source JPEG 2000 library"
    license = "BSD-2-Clause"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "cmake/openjp2Config.cmake"

    mlab_hooks = {"cmake_files.exclude": ["lib/cmake/openjp2Config.cmake"]}

    def configure(self):
        self.settings.rm_safe("compiler.cppstd")
        self.settings.rm_safe("compiler.libcxx")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="90e3896fed910c376aaf79cdd98bdfdaf98c6472efd8e1debf0a854938cbda6a",
            url=f"https://github.com/uclouvain/openjpeg/archive/v{self.version}.tar.gz",
            strip_root=True,
        )
        copy(self, self.exports_sources, self.export_sources_path, self.source_path)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP"] = True
        tc.variables["BUILD_DOC"] = False
        tc.variables["BUILD_STATIC_LIBS"] = False
        tc.variables["BUILD_LUTS_GENERATOR"] = False
        tc.variables["BUILD_CODEC"] = False
        tc.variables["BUILD_JPIP"] = False
        tc.variables["BUILD_VIEWER"] = False
        tc.variables["BUILD_JAVA"] = False
        tc.variables["BUILD_TESTING"] = False
        tc.variables["BUILD_PKGCONFIG_FILES"] = False
        tc.variables["OPJ_DISABLE_TPSOT_FIX"] = False
        tc.variables["OPJ_USE_THREAD"] = True
        tc.variables["BUILD_THIRDPARTY"] = False
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_path, dst=self.package_path / "licenses")
        copy(self, "*.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False, excludes="*vc???.pdb")
        cmake = CMake(self)
        cmake.install()
        v = Version(self.version)
        rmdir(self, self.package_path / "lib" / "cmake")
        rmdir(self, self.package_path / "lib" / "pkgconfig")
        rmdir(self, self.package_path / "lib" / f"openjpeg-{v.major}.{v.minor}")
        copy(self, self.exports_sources, self.source_path, self.package_path / "lib")

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:uclouvain:openjpeg:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("base_purl", "github/uclouvain/openjpeg")
        v = Version(self.version)
        self.cpp_info.set_property("cmake_file_name", "OpenJPEG")
        self.cpp_info.set_property("cmake_target_name", "openjp2")
        self.cpp_info.set_property("cmake_target_aliases", ["openjp2::openjp2"])
        self.cpp_info.set_property("pkg_config_name", "libopenjp2")
        self.cpp_info.includedirs.append(f"include/openjpeg-{v.major}.{v.minor}")
        self.cpp_info.libs = collect_libs(self)
        if self.settings.os == "Linux":
            self.cpp_info.system_libs = ["pthread", "m"]
