from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import get, load, save, copy, collect_libs
from conan.tools.scm import Version
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "sqlite3"
    version = "3.49.2"
    description = "Self-contained, serverless, in-process SQL database engine."
    license = "Unlicense"
    homepage = "https://www.sqlite.org"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "CMakeLists.txt"

    def configure(self):
        self.settings.rm_safe("compiler.cppstd")
        self.settings.rm_safe("compiler.libcxx")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def build_requirements(self):
        self.build_requires("zlib/[>=1.2.11]")

    def source(self):
        v = Version(self.version)
        get(
            self,
            sha256="921fc725517a694df7df38a2a3dfede6684024b5788d9de464187c612afb5918",
            url=f"https://www.sqlite.org/2025/sqlite-amalgamation-{v.major}{str(v.minor).zfill(2)}{str(v.patch).zfill(2)}00.zip",
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["HAVE_LOCALTIME_R"] = self.settings.os != "Windows"
        tc.variables["HAVE_POSIX_FALLOCATE"] = self.settings.os == "Linux"
        tc.variables["SQLITE3_SRC_DIR"] = self.source_folder.replace("\\", "/")
        tc.variables["SQLITE3_VERSION"] = self.version
        tc.variables["SQLITE3_BUILD_EXECUTABLE"] = False
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder=os.path.join(self.source_folder, ".."))
        cmake.build()

    def _extract_license(self):
        header = load(self, os.path.join(self.source_folder, "sqlite3.h"))
        license_content = header[3 : header.find("***", 1)]
        return license_content

    def package(self):
        save(self, self.package_path / "licenses" / "LICENSE", self._extract_license())
        copy(self, "*.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False, excludes="*vc???.pdb")
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:sqlite:sqlite:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/sqlite/sqlite@version-{self.version}")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "SQLite3")
        self.cpp_info.set_property("cmake_module_file_name", "sqlite3")
        self.cpp_info.set_property("cmake_target_name", "SQLite::SQLite3")
        self.cpp_info.set_property("cmake_module_target_name", "sqlite3::sqlite3")
        self.cpp_info.set_property("cmake_target_aliases", ["sqlite3::sqlite3"])
        self.cpp_info.set_property("pkg_config_name", "sqlite3")
        self.cpp_info.libs = collect_libs(self)

        if self.settings.os == "Linux":
            self.cpp_info.system_libs.extend(["m", "dl", "pthread"])
