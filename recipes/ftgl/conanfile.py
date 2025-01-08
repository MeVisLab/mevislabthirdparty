import os
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps, cmake_layout
from conan.tools.files import copy, get, patch, collect_libs

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "ftgl"
    version = "2.1.2"
    homepage = "https://sourceforge.net/projects/ftgl/"
    description = "library to use arbitrary fonts in OpenGL applications"
    license = "MIT"
    settings = "os", "compiler", "arch", "build_type"
    package_type = "shared-library"
    exports_sources = ["patches/*", "CMakeLists.txt"]

    mlab_hooks = {
        "dependencies.system_libs": ["libfreetype.so.6", "libGLU.so.1"],
    }

    def layout(self):
        cmake_layout(self)

    def source(self):
        get(
            self,
            url=f"https://sourceforge.net/projects/ftgl/files/FTGL Source/{self.version}/ftgl-{self.version}.tar.gz",
            sha256="2759cbd5fac0b631e8b012923cd0d2add320f6e541b399a7cda37163ad034075",
            destination="src",
            strip_root=True,
        )
        patch(self, base_path="src", patch_file="patches/001-mevis.patch")

    def requirements(self):
        if self.settings.os != "Linux":
            self.requires("freetype/[>=2.10.4]", transitive_headers=True)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        tc.variables["CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS"] = True
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
        copy(self, "*.pdb", src=self.build_folder, dst=os.path.join(self.package_folder, "bin"), keep_path=False, excludes="*vc???.pdb")
        copy(self, "license.txt", src=os.path.join(self.source_folder, "src"), dst=os.path.join(self.package_folder, "licenses"))

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE yet?
        # self.cpp_info.set_property("base_purl", "")  # Official source a sourceforge - "sourceforge/ftgl"?
        self.cpp_info.includedirs.append("include/FTGL")
        self.cpp_info.set_property("cmake_file_name", "FTGL")
        self.cpp_info.set_property("cmake_target_name", "FTGL::FTGL")
        self.cpp_info.libs = collect_libs(self)
