from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import get, load, save, copy, collect_libs
from conan.tools.scm import Version
import os

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "sqlite3"
    version = "3.53.4"
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

    def source(self):
        v = Version(self.version)
        get(
            self,
            sha256="1e71ddf93849c6a6ecf58b827c0692073d2dd7ee40196158068f7b29f422e87d",
            url=f"https://www.sqlite.org/2026/sqlite-amalgamation-{v.major}{str(v.minor).zfill(2)}{str(v.patch).zfill(2)}00.zip",
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
        save(self, os.path.join(self.package_folder, "licenses", "LICENSE"), self._extract_license())
        copy(
            self,
            "*.pdb",
            src=self.build_folder,
            dst=os.path.join(self.package_folder, "bin"),
            keep_path=False,
            excludes="*vc???.pdb",
        )
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.set_property("cpe", f"cpe:2.3:a:sqlite:sqlite:{self.version}:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/sqlite/sqlite@version-{self.version}")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "SQLite3")
        self.cpp_info.set_property("cmake_module_file_name", "sqlite3")
        self.cpp_info.set_property("cmake_target_name", "SQLite3::SQLite3")
        self.cpp_info.set_property("cmake_module_target_name", "sqlite3::sqlite3")
        self.cpp_info.set_property("cmake_target_aliases", ["sqlite3::sqlite3", "SQLite::SQLite3"])
        self.cpp_info.set_property("pkg_config_name", "sqlite3")
        self.cpp_info.libs = collect_libs(self)

        library = os.path.join(
            self.package_folder,
            self.cpp_info.libdirs[-1],
            f"{self.cpp_info.libs[0]}.lib" if self.settings.os == "Windows" else f"lib{self.cpp_info.libs[0]}.so",
        ).replace("\\", "/")
        self.cpp_info.set_property("cmake_additional_variables_prefixes", ["SQLITE3"])
        self.cpp_info.set_property("cmake_extra_variables", {"SQLite3_LIBRARY": library, "SQLITE3_LIBRARY": library})

        if self.settings.os == "Linux":
            self.cpp_info.system_libs.extend(["m", "dl", "pthread"])
