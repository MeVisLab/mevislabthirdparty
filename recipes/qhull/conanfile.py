from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout
from conan.tools.files import get, patch, replace_in_file, rmdir, copy, collect_libs
from conan.tools.microsoft import is_msvc

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "qhull"
    version = "8.0.2"
    homepage = "http://www.qhull.org"
    description = (
        "Qhull computes the convex hull, Delaunay triangulation, Voronoi diagram, "
        "halfspace intersection about a point, furthest-site Delaunay triangulation, "
        "and furthest-site Voronoi diagram"
    )
    license = "Qhull"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = ["patches/*"]

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="8774e9a12c70b0180b95d6b0b563c5aa4bea8d5960c15e18ae3b6d2521d64f8b",
            url=f"https://github.com/qhull/qhull/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )
        patch(self, patch_file="patches/001-add_missing_symbols.patch")
        patch(self, patch_file="patches/002-minimum_cmake_version.patch")
        patch(self, patch_file="patches/003-cpp20.patch")

        # we say we don't want static libs, but we need static qhullcpp (but only that)
        replace_in_file(
            self, self.source_path / "CMakeLists.txt", "set_target_properties(${qhull_CPP} PROPERTIES EXCLUDE_FROM_ALL TRUE)", ""
        )
        replace_in_file(
            self,
            self.source_path / "CMakeLists.txt",
            "list(APPEND qhull_TARGETS_INSTALL ${qhull_TARGETS_SHARED})",
            "list(APPEND qhull_TARGETS_INSTALL ${qhull_TARGETS_SHARED} ${qhull_CPP})",
        )

        replace_in_file(self, self.source_path / "CMakeLists.txt", "INSTALL_RPATH_USE_LINK_PATH TRUE", "INSTALL_RPATH_USE_LINK_PATH FALSE")

        replace_in_file(
            self, self.source_path / "CMakeLists.txt", 'INSTALL_RPATH "${LIB_INSTALL_DIR}"', 'INSTALL_RPATH "\$ORIGIN;\$ORIGIN/../lib"'
        )

        replace_in_file(self, self.source_path / "CMakeLists.txt", "$<$<CONFIG:Debug>:d>", "$<$<CONFIG:Debug>:_d>")

    def generate(self):
        tc = CMakeToolchain(self)
        # qhull adds d postfix itself, no need for CMAKE_DEBUG_POSTFIX
        # tc.variables["CMAKE_DEBUG_POSTFIX"] = "d"
        tc.variables["BUILD_STATIC_LIBS"] = False
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.cache_variables["CMAKE_POLICY_DEFAULT_CMP0091"] = "NEW"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

        copy(self, "*/qhull_rd.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False)
        copy(self, "COPYING.txt", src=self.source_path, dst=self.package_path / "licenses")

        rmdir(self, self.package_path / "lib" / "cmake")
        rmdir(self, self.package_path / "lib" / "pkgconfig")
        rmdir(self, self.package_path / "share")

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/qhull/qhull@v{self.version}")
        self.cpp_info.set_property("cmake_file_name", "Qhull")
        self.cpp_info.set_property("cmake_target_name", "Qhull::Qhull")
        self.cpp_info.set_property("pkg_config_name", "qhull_r")
        self.cpp_info.libs = collect_libs(self)

        if self.settings.os == "Linux":
            self.cpp_info.system_libs.append("m")

        if is_msvc(self):
            self.cpp_info.defines.append("qh_dllimport")
