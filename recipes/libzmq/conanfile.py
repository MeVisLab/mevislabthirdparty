from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout, CMakeDeps
from conan.tools.files import get, patch, rmdir, copy, collect_libs, rm
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "libzmq"
    version = "4.3.5"
    homepage = "https://zeromq.org"
    description = "ZeroMQ core engine in C++, implements ZMTP/3.1"
    license = "MPL-2.0"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "shared-library"
    exports_sources = ["patches/*"]

    mlab_hooks = {"debug_suffix.exclude": ["libzmq-*-mt-gd-*.dll", "libzmq-*-mt-gd-*.lib"]}

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("libsodium/[>=1.0.18]")

    def source(self):
        get(
            self,
            sha256="6653ef5910f17954861fe72332e68b03ca6e4d9c7160eb3a8de5a5a913bfab43",
            url=f"https://github.com/zeromq/libzmq/releases/download/v{self.version}/zeromq-{self.version}.tar.gz",
            strip_root=True,
        )
        patch(self, patch_file="patches/001-minimum_cmake_version.patch")
        rm(self, "FindSodium.cmake", os.path.join(self.source_folder, "builds", "cmake", "Modules"))

    def generate(self):
        cd = CMakeDeps(self)
        cd.generate()

        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        tc.variables["ENABLE_CURVE"] = True
        tc.variables["ENABLE_CPACK"] = False
        tc.variables["ENABLE_DRAFTS"] = False
        tc.variables["ENABLE_WS"] = False
        tc.variables["WITH_NSS"] = False
        tc.variables["WITH_TLS"] = False
        tc.variables["ZMQ_BUILD_TESTS"] = False
        tc.variables["BUILD_SHARED"] = True
        tc.variables["BUILD_STATIC"] = False
        tc.variables["CMAKE_DISABLE_FIND_PACKAGE_AsciiDoc"] = True
        tc.variables["WITH_DOC"] = False
        tc.variables["WITH_LIBSODIUM"] = True
        tc.variables["WITH_LIBBSD"] = False
        tc.variables["WITH_PERF_TOOL"] = False

        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake4_compat = {"CMAKE_POLICY_VERSION_MINIMUM": "3.5"}  # FIXME required for compatibility with CMake 4.0+
        cmake.configure(variables=cmake4_compat)
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(self, "*.pdb", src=os.path.join(self.source_folder, "bin"), dst=os.path.join(self.package_folder, "bin"))

        rmdir(self, os.path.join(self.package_folder, "doc"))
        rmdir(self, os.path.join(self.package_folder, "share"))
        rmdir(self, os.path.join(self.package_folder, "CMake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:zeromq:libzmq:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/zeromq/libzmq@v{self.version}")
        self.cpp_info.set_property("cmake_find_mode", "both")
        # This is how libzmq itself generates the CMake files
        self.cpp_info.set_property("cmake_file_name", "ZeroMQ")
        self.cpp_info.set_property("cmake_target_name", "libzmq")
        # This is how we generated it with Conan 1:
        self.cpp_info.set_property("cmake_module_file_name", "libzmq")
        self.cpp_info.set_property("cmake_module_target_name", "libzmq::libzmq")
        self.cpp_info.set_property("pkg_config_name", "libzmq")
        self.cpp_info.libs = collect_libs(self)
