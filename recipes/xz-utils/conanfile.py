import os
import textwrap
from conan import ConanFile
from conan.tools.scm import Version
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import get, copy, rmdir, save, collect_libs

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "xz-utils"
    version = "5.6.3"
    homepage = "https://tukaani.org/xz"
    description = "XZ Utils is free general-purpose data compression software with a high compression ratio"
    license = "Unlicense"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch"

    def configure(self):
        self.settings.rm_safe("compiler.cppstd")
        self.settings.rm_safe("compiler.libcxx")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="a95a49147b2dbb5487517acc0adcd77f9c2032cf00664eeae352405357d14a6c",
            url=f"https://github.com/tukaani-project/xz/releases/download/v{self.version}/xz-{self.version}.tar.bz2",
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

        rmdir(self, self.package_path / "lib" / "cmake")
        rmdir(self, self.package_path / "lib" / "pkgconfig")
        rmdir(self, self.package_path / "share")

        copy(self, "COPYING", src=self.source_path, dst=self.package_path / "licenses")

        content = textwrap.dedent(
            f"""\
            if (NOT TARGET LibLZMA::LibLZMA)
                message(FATAL_ERROR "Target LibZMA missing")
            endif()

            set(LIBLZMA_FOUND TRUE)
            # include(CheckLibraryExists)
            set(CMAKE_REQUIRED_QUIET_SAVE ${{CMAKE_REQUIRED_QUIET}})
            set(CMAKE_REQUIRED_QUIET ${{LIBLZMA_FIND_QUIETLY}})
            # CHECK_LIBRARY_EXISTS(LibLZMA::LibLZMA lzma_auto_decoder "" LIBLZMA_HAS_AUTO_DECODER)
            # CHECK_LIBRARY_EXISTS(LibLZMA::LibLZMA lzma_easy_encoder "" LIBLZMA_HAS_EASY_ENCODER)
            # CHECK_LIBRARY_EXISTS(LibLZMA::LibLZMA lzma_lzma_preset "" LIBLZMA_HAS_LZMA_PRESET)
            unset(LIBLZMA_LIBRARY_check)
            set(CMAKE_REQUIRED_QUIET ${{CMAKE_REQUIRED_QUIET_SAVE}})

            set(LIBLZMA_VERSION {self.version})
            set(LIBLZMA_INCLUDE_DIRS ${{LibLZMA_INCLUDE_DIRS}})
            set(LIBLZMA_LIBRARIES ${{LibLZMA_LIBRARIES}})

            set(LIBLZMA_VERSION_MAJOR {Version(self.version).major})
            set(LIBLZMA_VERSION_MINOR {Version(self.version).minor})
            set(LIBLZMA_VERSION_PATCH {Version(self.version).patch})
            set(LIBLZMA_VERSION_STRING "{self.version}")
        """
        )
        save(self, self.package_path / self._module_file_rel_path, content)

    @property
    def _module_file_rel_path(self):
        return os.path.join("lib", "cmake", "liblzma-variables.cmake")

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:tukaani:xz:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("base_purl", "github/tukaani-project/xz")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "LibLZMA")
        self.cpp_info.set_property("cmake_target_name", "LibLZMA::LibLZMA")
        self.cpp_info.set_property("cmake_target_aliases", ["liblzma::liblzma"])
        self.cpp_info.set_property("cmake_build_modules", [self._module_file_rel_path])
        self.cpp_info.set_property("display_name", "xz-utils")
        self.cpp_info.set_property("pkg_config_name", "liblzma")
        self.cpp_info.libs = collect_libs(self)
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.append("pthread")
