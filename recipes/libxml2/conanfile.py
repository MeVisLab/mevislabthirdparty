import os
import textwrap
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import collect_libs
from conan.tools.files import get, copy, rmdir, patch, save
from conan.tools.scm import Version

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "libxml2"
    version = "2.13.5"
    homepage = "http://xmlsoft.org"
    description = "XML C parser and toolkit"
    license = "MIT"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("zlib/[>=1.2.11]")
        self.requires("icu/[>=68.2]")

    def source(self):
        v = Version(self.version)
        get(
            self,
            sha256="74fc163217a3964257d3be39af943e08861263c4231f9ef5b496b6f6d4c7b2b6",
            url=f"https://download.gnome.org/sources/libxml2/{v.major}.{v.minor}/libxml2-{self.version}.tar.xz",
            strip_root=True,
        )
        patch(self, patch_file="patches/001-debug_postfix.patch")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        tc.variables["LIBXML2_WITH_ICONV"] = False
        tc.variables["LIBXML2_WITH_ICU"] = True
        tc.variables["LIBXML2_WITH_LZMA"] = False
        tc.variables["LIBXML2_WITH_ZLIB"] = True
        tc.variables["LIBXML2_WITH_PROGRAMS"] = False
        tc.variables["LIBXML2_WITH_PYTHON"] = False
        tc.variables["LIBXML2_WITH_TESTS"] = False
        tc.generate()
        tc = CMakeDeps(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(self, "Copyright", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        rmdir(self, os.path.join(self.package_folder, "share"))
        self._cmake_module_file_write()

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:xmlsoft:libxml2:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("base_purl", "github/GNOME/libxml2")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "LibXml2")
        self.cpp_info.set_property("cmake_target_name", "LibXml2::LibXml2")
        self.cpp_info.set_property("pkg_config_name", "libxml-2.0")
        self.cpp_info.libs = collect_libs(self)
        self.cpp_info.includedirs.append("include/libxml2")

        self.cpp_info.set_property("cmake_build_modules", [self._cmake_module_file])
        self.cpp_info.set_property("cmake_find_package", [self._cmake_module_file])

        if self.settings.os == "Linux":
            self.cpp_info.system_libs.extend(["m", "pthread"])
        elif self.settings.os == "Windows":
            self.cpp_info.system_libs.extend(["ws2_32", "wsock32"])

    @property
    def _cmake_module_file(self):
        return os.path.join("lib", "cmake", f"{self.name}-variables.cmake")

    def _cmake_module_file_write(self):
        file = os.path.join(self.package_folder, self._cmake_module_file)
        content = textwrap.dedent(
            f"""\
            set(LIBXML2_FOUND TRUE)
            set(LIBXML2_INCLUDE_DIR ${{LibXml2_INCLUDE_DIR}})
            set(LIBXML2_INCLUDE_DIRS ${{LibXml2_INCLUDE_DIRS}})
            set(LIBXML2_LIBRARIES ${{LibXml2_LIBRARIES}})
            set(LIBXML2_VERSION_STRING ${{LibXml2_VERSION_STRING}})
            """
        )
        save(self, file, content)
