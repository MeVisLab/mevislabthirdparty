from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps, cmake_layout
from conan.tools.env import VirtualRunEnv
from conan.tools.files import get, patch, copy, rm, rmdir, collect_libs, replace_in_file

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    short_paths = True
    name = "itk"
    version = "5.3.0"
    homepage = "https://www.itk.org"
    description = ("An open-source, cross-platform library that provides developers "
                   "with an extensive suite of software tools for image analysis")
    license = "MPL-2.0"
    settings = "os", "compiler", "arch", "build_type"
    package_type = "shared-library"
    exports_sources = ["patches/*"]

    def requirements(self):
        self.requires("dcmtk/[>=3.6.5]")
        self.requires("double-conversion/[>=3.1.5]")
        self.requires("hdf5/[>=1.14.2]")
        self.requires("libjpeg-turbo/[>=2.1.5]")
        self.requires("libpng/[>=1.6.37]")
        self.requires("tiff/[>=4.1.0]")
        self.requires("xz-utils/[>=5.2.6]")
        self.requires("zlib/[>=1.2.11]")
        self.requires("eigen/[>=3.4.0]")
        self.requires("expat/[>=2.5.0]")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(self,
            url=f"https://github.com/InsightSoftwareConsortium/ITK/archive/v{self.version}.tar.gz",
            sha256="64e7e8094a5023c8f68ee042459d6319581fadb35e2fe90a4ae230ce36369db1",
            strip_root=True)
        patch(self, patch_file="patches/001-double_conversion.patch")
        patch(self, patch_file="patches/002-ignore_cmake_policy.patch")
        patch(self, patch_file="patches/003-conan_dependencies.patch")
        patch(self, patch_file="patches/004-issue_4358_itkShapedNeighborhoodIterator.patch")
        patch(self, patch_file="patches/005-add_using_in_class_namespace.patch")

        # see https://github.com/InsightSoftwareConsortium/ITK/pull/4066/,
        # will be obsolete in itk 5.4.0
        replace_in_file(self, self.source_path / "Modules" / "Filtering" / "MathematicalMorphology" / "src" /
            "itkMathematicalMorphologyEnums.cxx",
            '#include "itkMathematicalMorphologyEnums.h"',
            '#include "itkIntTypes.h"\n#include "itkMathematicalMorphologyEnums.h"'
        )
        # stop libminc from forcing an absolute RPATH
        replace_in_file(self, self.source_path / "Modules" / "ThirdParty" / "MINC" / "src" / "libminc" / "CMakeLists.txt",
            'SET(CMAKE_INSTALL_RPATH',
            '#SET(CMAKE_INSTALL_RPATH'
        )
        rm(self, "*.cmake", self.source_path / "Modules" / "Compatibility" / "Deprecated")

    def generate(self):
        # need the run environment to set LD_LIBRARYPPATH while building the test kernel
        env = VirtualRunEnv(self)
        env.generate(scope="build")

        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        tc.variables["BUILD_EXAMPLES"] = False
        tc.variables["BUILD_TESTING"] = False

        tc.variables["ITK_WRAPPING"] = False
        tc.variables["ITK_WRAP_PYTHON"] = False
        tc.variables["ITK_BUILD_DEFAULT_MODULES"] = True

        tc.variables["Module_ITKTestKernel"] = True
        tc.variables["Module_ITKDeprecated"] = False
        tc.variables["Module_ITKFEMRegistration"] = True

        tc.variables["ITK_USE_GPU"] = False  # requires OpenCL on all platforms

        tc.variables["ITK_USE_CONCEPT_CHECKING"] = False
        tc.variables["ITK_USE_SYSTEM_ZLIB"] = True
        tc.variables["ITK_USE_SYSTEM_DOUBLECONVERSION"] = True
        tc.variables["ITK_USE_SYSTEM_HDF5"] = True
        tc.variables["ITK_USE_SYSTEM_DCMTK"] = True
        tc.variables["ITK_USE_SYSTEM_JPEG"] = True
        tc.variables["ITK_USE_SYSTEM_PNG"] = True
        tc.variables["ITK_USE_SYSTEM_EIGEN"] = True
        tc.variables["ITK_USE_SYSTEM_TIFF"] = True
        tc.variables["ITK_USE_SYSTEM_EXPAT"] = True
        tc.variables["ITK_SKIP_PATH_LENGTH_CHECKS"] = True
        tc.variables["ITK_LEGACY_REMOVE"] = True

        tc.cache_variables["CMAKE_POLICY_DEFAULT_CMP0091"] = "NEW"
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

        bin_path = self.package_path / "bin"
        if self.settings.os == "Windows":
            copy(self, "*.pdb", src=self.build_path, dst=bin_path, keep_path=False, excludes="*/vc???.pdb")
            copy(self, "*.dll", src=self.build_path, dst=bin_path, keep_path=False, excludes="*/vc???.dll")
            copy(self, "*.exe", src=self.build_path, dst=bin_path, keep_path=False)
        else:
            rmdir(self, bin_path)
        copy(self, "LICENSE", src=self.source_path, dst=self.package_path / "licenses")
        rmdir(self, self.package_path / 'lib' / 'pkgconfig')
        (self.package_path / 'lib' / 'gdcmopenjpeg-2.3' / 'OpenJPEGConfig.cmake').unlink()

        rmdir(self, self.package_path / "share")
        rmdir(self, self.package_path / "lib" / "cmake")

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "ITK")
        self.cpp_info.set_property("cmake_target_name", "ITK::ITK")
        self.cpp_info.set_property("display_name", "Insight Toolkit(ITK)")
        major, minor, _ = self.version.split('.')
        self.cpp_info.includedirs = ["include", f"include/ITK-{major}.{minor}"]
        self.cpp_info.libs = collect_libs(self)

