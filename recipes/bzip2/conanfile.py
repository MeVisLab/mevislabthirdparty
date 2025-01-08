import os
import textwrap

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get, save, collect_libs
from conan.tools.microsoft import is_msvc
from conan.tools.scm import Version

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "bzip2"
    version = "1.0.8"
    license = "bzip2-1.0.6"
    homepage = "http://www.bzip.org"
    description = "bzip2 is a free and open-source file compression program that uses the Burrows-Wheeler algorithm"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "static-library"
    exports_sources = ["CMakeLists.txt"]

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(self,
            url=f"https://sourceware.org/pub/bzip2/bzip2-{self.version}.tar.gz",
            sha256="ab5a03176ee106d3f0fa90e381da478ddae405918153cca248e682cd0c4a2269",
            strip_root=True)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables['BUILD_SHARED_LIBS'] = False
        tc.variables['CMAKE_POSITION_INDEPENDENT_CODE'] = not is_msvc(self)
        tc.variables["BZ2_SRC_DIR"] = self.source_folder.replace("\\", "/")
        tc.variables["BZ2_VERSION_MAJOR"] = Version(self.version).major
        tc.variables["BZ2_VERSION_STRING"] = self.version
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder=self.source_path.parent)
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_path, dst=self.package_path / "licenses")
        copy(self, "*.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False)
        cmake = CMake(self)
        cmake.install()
        self._create_cmake_module_variables(self.package_path / self._module_file_rel_path)

    def _create_cmake_module_variables(self, module_file):
        content = textwrap.dedent(f"""\
            set(BZIP2_FOUND TRUE)
            set(BZIP2_INCLUDE_DIRS ${{BZip2_INCLUDE_DIR}})
            set(BZIP2_LIBRARIES ${{BZip2_LIBRARIES}})
            set(BZIP2_NEED_PREFIX TRUE)
            set(BZIP2_VERSION "{self.version}")
            set(BZIP2_INCLUDE_DIR ${{BZip2_INCLUDE_DIR}})
            set(BZIP2_VERSION_STRING "{self.version}")
        """)
        save(self, module_file, content)

    @property
    def _module_file_rel_path(self):
        return os.path.join("lib", "cmake", f"{self.name}-variables.cmake")

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:bzip:bzip2:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("base_purl", "github/libarchive/bzip2")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "BZip2")
        self.cpp_info.set_property("cmake_target_name", "BZip2::BZip2")
        self.cpp_info.set_property("cmake_build_modules", [self._module_file_rel_path])
        self.cpp_info.libs = collect_libs(self)
