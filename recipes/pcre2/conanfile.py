from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get, rmdir, replace_in_file

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "pcre2"
    version = "10.45"
    homepage = "https://www.pcre.org"
    description = "Perl-compatible regular expression library"
    license = "BSD-3-Clause"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"

    def configure(self):
        self.settings.rm_safe("compiler.cppstd")
        self.settings.rm_safe("compiler.libcxx")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="21547f3516120c75597e5b30a992e27a592a31950b5140e7b8bfde3f192033c4",
            url=f"https://github.com/PCRE2Project/pcre2/releases/download/pcre2-{self.version}/pcre2-{self.version}.tar.bz2",
            strip_root=True,
        )
        replace_in_file(self, self.source_path / "CMakeLists.txt", 'set(CMAKE_DEBUG_POSTFIX "d")', '#set(CMAKE_DEBUG_POSTFIX "d")')

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["BUILD_STATIC_LIBS"] = False
        tc.variables["PCRE2_BUILD_TESTS"] = False
        tc.variables["PCRE2_BUILD_PCRE2GREP"] = False
        tc.variables["PCRE2_DEBUG"] = self.settings.build_type == "Debug"

        tc.variables["PCRE2_BUILD_PCRE2_8"] = True
        tc.variables["PCRE2_BUILD_PCRE2_16"] = True
        tc.variables["PCRE2_BUILD_PCRE2_32"] = True

        tc.variables["PCRE2_SUPPORT_LIBZ"] = False
        tc.variables["PCRE2_SUPPORT_LIBBZ2"] = False
        tc.variables["PCRE2_SUPPORT_LIBEDIT"] = False
        tc.variables["PCRE2_SUPPORT_LIBREADLINE"] = False
        tc.variables["PCRE2_SUPPORT_JIT"] = True
        tc.variables["PCRE2_SUPPORT_UNICODE"] = True
        tc.generate()

        cd = CMakeDeps(self)
        cd.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENCE.md", src=self.source_path, dst=self.package_path / "licenses")
        copy(self, "*.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False, excludes="*vc???.pdb")
        cmake = CMake(self)
        cmake.install()
        rmdir(self, self.package_path / "cmake")
        rmdir(self, self.package_path / "man")
        rmdir(self, self.package_path / "share")
        rmdir(self, self.package_path / "lib" / "pkgconfig")
        rmdir(self, self.package_path / "lib" / "cmake")

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:pcre:pcre2:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("base_purl", "github/PCRE2Project/pcre2")

        def lib_name(name):
            return f"{name}_d" if self.settings.build_type == "Debug" else name

        self.cpp_info.set_property("cmake_file_name", "PCRE2")
        self.cpp_info.set_property("pkg_config_name", "libpcre2")

        self.cpp_info.components["pcre2-8"].set_property("cmake_target_name", "PCRE2::8BIT")
        self.cpp_info.components["pcre2-8"].set_property("pkg_config_name", "libpcre2-8")
        self.cpp_info.components["pcre2-8"].libs = [lib_name("pcre2-8")]

        self.cpp_info.components["pcre2-posix"].set_property("cmake_target_name", "PCRE2::POSIX")
        self.cpp_info.components["pcre2-posix"].set_property("pkg_config_name", "libpcre2-posix")
        self.cpp_info.components["pcre2-posix"].libs = [lib_name("pcre2-posix")]
        self.cpp_info.components["pcre2-posix"].requires = ["pcre2-8"]

        self.cpp_info.components["pcre2-16"].set_property("cmake_target_name", "PCRE2::16BIT")
        self.cpp_info.components["pcre2-16"].set_property("pkg_config_name", "libpcre2-16")
        self.cpp_info.components["pcre2-16"].libs = [lib_name("pcre2-16")]

        self.cpp_info.components["pcre2-32"].set_property("cmake_target_name", "PCRE2::32BIT")
        self.cpp_info.components["pcre2-32"].set_property("pkg_config_name", "libpcre2-32")
        self.cpp_info.components["pcre2-32"].libs = [lib_name("pcre2-32")]
