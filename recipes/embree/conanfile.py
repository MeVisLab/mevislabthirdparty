from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import collect_libs, copy, get, rmdir, rm, replace_in_file
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "embree"
    version = "4.4.0"
    homepage = "https://github.com/embree/embree"
    description = "Embree is a high-performance ray tracing library"
    license = "Apache-2.0"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "shared-library"
    exports_sources = "patches/*.patch"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="acb517b0ea0f4b442235d5331b69f96192c28da6aca5d5dde0cbe40799638d5c",
            url=f"https://github.com/RenderKit/embree/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )
        replace_in_file(
            self,
            os.path.join(self.source_folder, "common", "cmake", "package.cmake"),
            "INSTALL(FILES ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS}",
            "#INSTALL(FILES ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS}",
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["EMBREE_TUTORIALS"] = False
        tc.variables["EMBREE_ISPC_SUPPORT"] = False
        tc.variables["EMBREE_TASKING_SYSTEM"] = "INTERNAL"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE.txt", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(
            self, "*/embree4*.pdb", src=self.build_folder, dst=os.path.join(self.package_folder, "bin"), keep_path=False
        )
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "bin", "models"))
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "share"))
        rm(self, folder=self.package_folder, pattern="embree-vars.*")

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/embree/embree@v{self.version}")
        self.cpp_info.set_property("cmake_file_name", "Embree")
        self.cpp_info.set_property("cmake_target_name", "Embree::Embree")
        self.cpp_info.libs = collect_libs(self)
