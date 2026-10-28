from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps, cmake_layout
from conan.tools.env import VirtualRunEnv
from conan.tools.files import get, patch, copy, rm, rmdir, collect_libs
import os

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    short_paths = True
    name = "itk"
    version = "5.4.7"
    homepage = "https://www.itk.org"
    description = (
        "An open-source, cross-platform library that provides developers "
        "with an extensive suite of software tools for image analysis"
    )
    license = "Apache-2.0"
    settings = "os", "compiler", "arch", "build_type"
    package_type = "shared-library"
    exports_sources = ["patches/*"]

    def requirements(self):
        self.requires("dcmtk/[>=3.6.5]")
        self.requires("double-conversion/[>=3.1.5]")
        self.requires("eigen/[>=3.4.0]", transitive_headers=True)
        self.requires("expat/[>=2.5.0]")
        self.requires("gtest/[>=1.17.0]")
        self.requires("hdf5/[>=1.14.2]")
        self.requires("libjpeg-turbo/[>=2.1.5]")
        self.requires("libpng/[>=1.6.37]")
        self.requires("tiff/[>=4.1.0]")
        self.requires("xz-utils/[>=5.2.6]")
        self.requires("zlib/[>=1.2.11]")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="c953ad7957c481dbb17cfebf03fc61e5252b2be7ccf6757d1234b48ac99914f8",
            url=f"https://github.com/InsightSoftwareConsortium/ITK/archive/v{self.version}.tar.gz",
            strip_root=True,
        )
        patch(self, patch_file="patches/001-double_conversion.patch")
        patch(self, patch_file="patches/002-ignore_cmake_policy.patch")
        patch(self, patch_file="patches/003-conan_dependencies.patch")
        patch(self, patch_file="patches/004-add_using_in_class_namespace.patch")
        patch(self, patch_file="patches/005-libminic_no_abs_rpath.patch")
        patch(self, patch_file="patches/006-libminc_compile_fix.patch")
        patch(self, patch_file="patches/007-system_tiff.patch")
        patch(self, patch_file="patches/008-stderr_flush.patch")
        patch(self, patch_file="patches/009-remove_unnecessary_warning.patch")
        rm(self, "*.cmake", os.path.join(self.source_folder, "Modules", "Compatibility", "Deprecated"))

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

        tc.variables["ITK_LEGACY_REMOVE"] = True
        tc.variables["ITK_USE_GPU"] = False  # requires OpenCL on all platforms
        tc.variables["ITK_USE_CONCEPT_CHECKING"] = False
        tc.variables["ITK_SKIP_PATH_LENGTH_CHECKS"] = True
        tc.variables["ITK_USE_SYSTEM_LIBRARIES"] = True
        tc.variables["ITK_USE_SYSTEM_DCMTK"] = True
        tc.variables["ITK_USE_SYSTEM_DOUBLECONVERSION"] = True
        tc.variables["ITK_USE_SYSTEM_EIGEN"] = True
        tc.variables["ITK_USE_SYSTEM_EXPAT"] = True
        tc.variables["ITK_USE_SYSTEM_GDCM"] = False
        tc.variables["ITK_USE_SYSTEM_GOOGLETEST"] = True
        tc.variables["ITK_USE_SYSTEM_HDF5"] = True
        tc.variables["ITK_USE_SYSTEM_JPEG"] = True
        tc.variables["ITK_USE_SYSTEM_MINC"] = False
        tc.variables["ITK_USE_SYSTEM_PNG"] = True
        tc.variables["ITK_USE_SYSTEM_TIFF"] = True
        tc.variables["ITK_USE_SYSTEM_VXL"] = False
        tc.variables["ITK_USE_SYSTEM_ZLIB"] = True
        tc.variables["ITK_USE_SYSTEM_GDCM"] = False
        tc.variables["ITK_USE_SYSTEM_ICU"] = True
        tc.variables["ITK_USE_SYSTEM_LIBLBFGS"] = True
        tc.variables["ITK_USE_SYSTEM_LLVM"] = True
        tc.variables["ITK_USE_SYSTEM_SWIG"] = True

        tc.cache_variables["CMAKE_POLICY_DEFAULT_CMP0091"] = "NEW"
        tc.generate()

        cd = CMakeDeps(self)
        cd.generate()

    def build(self):
        cmake = CMake(self)
        cmake4_compat = {"CMAKE_POLICY_VERSION_MINIMUM": "3.5"}  # FIXME required for compatibility with CMake 4.0+
        cmake.configure(variables=cmake4_compat)
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

        bin_path = os.path.join(self.package_folder, "bin")
        if self.settings.os == "Windows":
            copy(self, "*.pdb", src=self.build_folder, dst=bin_path, keep_path=False, excludes="*/vc???.pdb")
            copy(self, "*.dll", src=self.build_folder, dst=bin_path, keep_path=False, excludes="*/vc???.dll")
            copy(self, "*.exe", src=self.build_folder, dst=bin_path, keep_path=False)
        else:
            rmdir(self, bin_path)
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        rm(self, "OpenJPEGConfig.cmake", os.path.join(self.package_folder, "lib", "gdcmopenjpeg-2.3"))

        rmdir(self, os.path.join(self.package_folder, "share"))
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # Not in CVE?
        self.cpp_info.set_property("purl", f"pkg:github/InsightSoftwareConsortium/ITK@v{self.version}")
        self.cpp_info.set_property("cmake_file_name", "ITK")
        self.cpp_info.set_property("cmake_target_name", "ITK::ITK")
        self.cpp_info.set_property("display_name", "Insight Toolkit(ITK)")
        major, minor, _ = self.version.split(".")
        self.cpp_info.includedirs = ["include", f"include/ITK-{major}.{minor}"]
        self.cpp_info.libs = collect_libs(self)
