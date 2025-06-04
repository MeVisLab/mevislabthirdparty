import os
import textwrap

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import copy, collect_libs, get, patch, rmdir, rm, replace_in_file, save
from conan.tools.gnu import Autotools, AutotoolsToolchain
from conan.tools.layout import basic_layout
from conan.tools.microsoft import is_msvc

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "libiconv"
    version = "1.18"
    homepage = "https://www.gnu.org/software/libiconv"
    description = "Internationalization support library"
    license = "LGPL-2.1-or-later"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch", "CMakeLists.txt"

    mlab_hooks = {"debug_suffix.exclude": ["libiconv*.so.*", "libcharset*.so.*"]}

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def layout(self):
        if is_msvc(self):
            cmake_layout(self, src_folder="src")
        else:
            basic_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="3b08f5f4f9b4eb82f151a7040bfd6fe6c6fb922efe4b1659c66ea933276965e8",
            url=f"https://ftp.gnu.org/pub/gnu/libiconv/libiconv-{self.version}.tar.gz",
            strip_root=True,
        )
        patch(self, patch_file="patches/001-libcharset-fix-linkage.patch")

    def generate(self):
        if is_msvc(self):
            tc = CMakeToolchain(self)
            tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
            tc.variables["CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS"] = True
            tc.generate()
        else:
            tc = AutotoolsToolchain(self)
            tc.fpic = True
            tc.configure_args.append("--enable-static=no")
            tc.configure_args.append("--enable-shared=yes")
            tc.configure_args.append("--enable-relocatable=yes")
            tc.generate()

    def build(self):
        if is_msvc(self):
            cmake = CMake(self)
            cmake.configure(build_script_folder=os.path.join(self.source_folder, os.pardir))
            cmake.build()
        else:
            if self.settings.build_type == "Debug":
                replace_in_file(self, self.source_path / "lib" / "Makefile.in", "libiconv.la", "libiconvd.la")
                replace_in_file(self, self.source_path / "src" / "Makefile.in", "libiconv.la", "libiconvd.la")
                replace_in_file(self, self.source_path / "libcharset" / "lib" / "Makefile.in", "libcharset.la", "libcharsetd.la")
            autotools = Autotools(self)
            autotools.configure()
            autotools.make()

    def package(self):
        copy(self, "COPYING.LIB", src=self.source_path, dst=self.package_path / "licenses")
        if is_msvc(self):
            cmake = CMake(self)
            cmake.install()
        else:
            autotools = Autotools(self)
            autotools.install()
        self._cmake_module_file_write()
        rmdir(self, self.package_path / "share")
        rm(self, pattern="*.la", folder=self.package_path / "lib")

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE yet?
        self.cpp_info.set_property(
            "purl", f"pkg:github/roboticslibrary/libiconv@v{self.version}"
        )  # Official repository at https://ftp.gnu.org/gnu/libiconv
        self.cpp_info.set_property("display_name", "libiconv")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "Iconv")
        self.cpp_info.set_property("cmake_target_name", "Iconv::Iconv")
        self.cpp_info.set_property("cmake_target_aliases", ["libiconv::libiconv"])
        self.cpp_info.set_property("cmake_build_modules", [self._cmake_module_file])
        self.cpp_info.set_property("cmake_find_package", [self._cmake_module_file])
        self.cpp_info.libs = collect_libs(self)

    @property
    def _cmake_module_file(self):
        return os.path.join("lib", "cmake", f"{self.name}-variables.cmake")

    def _cmake_module_file_write(self):
        file = self.package_path / self._cmake_module_file
        content = textwrap.dedent(
            """\
            set(Iconv_IS_BUILT_IN FALSE)

            set(LIBICONV_FOUND TRUE)
            set(LIBICONV_INCLUDE_DIR ${Iconv_INCLUDE_DIRS})
            set(LIBICONV_INCLUDE_DIRS ${Iconv_INCLUDE_DIRS})
            set(LIBICONV_LIBRARY ${Iconv_LIBRARIES})
            set(LIBICONV_LIBRARIES ${Iconv_LIBRARIES})

            set(LIBCHARSET_FOUND TRUE)
            set(LIBCHARSET_LIBRARY ${Iconv_LIBRARIES})
            set(LIBCHARSET_LIBRARIES ${Iconv_LIBRARIES})
            set(LIBCHARSET_INCLUDE_DIR ${Iconv_INCLUDE_DIR})
            set(LIBCHARSET_INCLUDE_DIRS ${Iconv_INCLUDE_DIR})
            """
        )
        save(self, file, content)
