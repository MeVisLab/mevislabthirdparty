from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout
from conan.tools.files import rmdir, collect_libs, copy, get, patch, replace_in_file
from pathlib import Path
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "pcl"
    version = "1.15.1"
    homepage = "https://pointclouds.org"
    description = (
        "The Point Cloud Library (PCL) is a standalone, large scale, "
        "open project for 2D/3D image and point cloud processing."
    )
    license = "BSD-3-Clause"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = ["patches/*", "CMakeLists.txt"]

    def requirements(self):
        self.requires("boost/[>=1.75.0]", transitive_headers=True)
        self.requires("eigen/[>=3.3.9]", transitive_headers=True)
        self.requires("flann/[>=1.9.1]")
        self.requires("glew/[>=2.0.0]")
        self.requires("libpng/[>=1.6.37]")
        self.requires("qhull/[>=8.0.2]")
        # self.requires("vtk/[>=7.1.1]")
        self.requires("zlib/[>=1.2.11]")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="f187b2646422ae6fb6daf7eec2d62c538ae7fe626397ed649c0e9b5a5b862b5a",
            url=f"https://github.com/PointCloudLibrary/pcl/releases/download/pcl-{self.version}/source.tar.gz",
            strip_root=True,
        )
        patch(self, patch_file="patches/001-boost_no_mpi.patch")
        replace_in_file(
            self,
            os.path.join(self.source_folder, "CMakeLists.txt"),
            "set(CMAKE_INSTALL_RPATH",
            "#set(CMAKE_INSTALL_RPATH",
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["PCL_SHARED_LIBS"] = True
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"

        tc.variables["BUILD_tools"] = False
        tc.variables["BUILD_CUDA"] = False

        tc.variables["CMAKE_DISABLE_FIND_PACKAGE_VTK"] = True
        tc.variables["PCL_ENABLE_MARCHNATIVE"] = False
        tc.variables["PCL_DISABLE_GPU_TESTS"] = False
        tc.variables["PCL_DISABLE_VISUALIZATION_TESTS"] = False
        tc.variables["PCL_BUILD_WITH_BOOST_DYNAMIC_LINKING_WIN32"] = True

        tc.variables["WITH_DOCS"] = False
        tc.variables["WITH_TUTORIALS"] = False
        tc.variables["WITH_OPENMP"] = False
        tc.variables["WITH_LIBUSB"] = False
        tc.variables["WITH_PNG"] = True
        tc.variables["WITH_QHULL"] = True
        tc.variables["WITH_CUDA"] = False
        tc.variables["WITH_VTK"] = True
        tc.variables["WITH_QT"] = False
        tc.variables["WITH_PCAP"] = False
        tc.variables["WITH_OPENGL"] = True

        tc.generate()

        cd = CMakeDeps(self)
        cd.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder=os.path.dirname(self.source_folder))
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

        copy(self, "LICENSE.txt", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(
            self,
            "*.pdb",
            src=self.build_folder,
            dst=os.path.join(self.package_folder, "bin"),
            keep_path=False,
            excludes="*/vc???.pdb",
        )
        rmdir(self, os.path.join(self.package_folder, "cmake"))
        rmdir(self, os.path.join(self.package_folder, "share"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))

        # Remove MS runtime files
        for pattern in ["concrt*.dll", "msvcp*.dll", "vcruntime*.dll"]:
            for lib in (Path(self.package_folder) / "bin").glob(pattern):
                lib.unlink()

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/PointCloudLibrary/pcl@pcl-{self.version}")
        self.cpp_info.set_property("cmake_file_name", "PCL")
        self.cpp_info.set_property("cmake_target_name", "PCL::PCL")
        self.cpp_info.set_property("display_name", "Point Cloud Library")
        self.cpp_info.set_property("mevislab_prosdk_exclude", True)
        self.cpp_info.libs = collect_libs(self)

        major, minor = self.version.split(".")[:2]
        self.cpp_info.includedirs.append(f"include/pcl-{major}.{minor}")
