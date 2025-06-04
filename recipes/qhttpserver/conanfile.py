from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import patch, collect_libs, copy, get
from conan.tools.env import VirtualRunEnv

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "qhttpserver"
    version = "2020.12.29"
    homepage = "https://github.com/nikhilm/qhttpserver"
    description = "Qt based HTTP Server based on Joyent's HTTP Parser library"
    license = "MIT"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch", "CMakeLists.txt"

    def layout(self):
        cmake_layout(self)

    def requirements(self):
        self.requires("qtbase/[>=6.6]")

    def source(self):
        get(self,
            sha256="49628e859a6aea81ada25b9b51630808cb6d7e9042b017b6514cdfd9dabb65dd",
            url=f"https://github.com/nikhilm/qhttpserver/archive/30ac5715d123030b01bbac7383fb73d1d00d932b.tar.gz",
            destination="src",
            strip_root=True,
        )
        patch(self, base_path="src", patch_file="patches/001-allow_set_qtcpserver.patch")
        patch(self, base_path="src", patch_file="patches/002-qt6.patch")

    def generate(self):
        env = VirtualRunEnv(self)
        env.generate(scope="build")
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.variables["CMAKE_CXX_VISIBILITY_PRESET"] = "default" #fixme
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_path / "src", dst=self.package_path / "licenses")
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/nikhilm/qhttpserver@30ac5715d123030b01bbac7383fb73d1d00d932b")
        self.cpp_info.set_property("cmake_file_name", "QHttpServer")
        self.cpp_info.set_property("cmake_target_name", "QHttpServer::QHttpServer")
        self.cpp_info.set_property("cmake_config_version_compat", "AnyNewerVersion")
        self.cpp_info.set_property("pkg_config_name", "QHttpServer")
        self.cpp_info.includedirs = ["include", "include/QHttpServer"]
        self.cpp_info.libs = collect_libs(self)
