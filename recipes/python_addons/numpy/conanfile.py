import os
from pathlib import Path

from conan import ConanFile
from conan.errors import ConanException
from conan.tools.files import get, copy, rmdir
from conan.tools.microsoft import MSBuildToolchain

required_conan_version = ">=2.2.2"

# FIXME numpy links to blas/lapack/openblas if found on the system.
# It's also recommended to use it, since it's way faster than the fallback implementation.
# Either way, we should prevent blas/lapack/openblas from being used or we provide it explicitly as a dependency.


class ConanRecipe(ConanFile):
    name = "numpy"
    mli_name = "Python3__NumPy"
    version = "2.3.2"
    homepage = "https://numpy.org"
    description = "NumPy is the fundamental package for scientific computing with Python"
    license = "BSD-3-Clause"
    python_requires = "python_package/[>=1.0.0]"
    python_requires_extend = "python_package.PythonPackageRecipe"
    exports_sources = "requirements.txt"
    package_type = "shared-library"

    @property
    def license_path(self):
        return "LICENSE.txt"

    def source(self):
        get(
            self,
            sha256="e0486a11ec30cdecb53f184d496d1c6a20786c81e55e41640270130056f8ee48",
            url=f"https://github.com/numpy/numpy/releases/download/v{self.version}/numpy-{self.version}.tar.gz",
            strip_root=True,
        )

    def generate(self):
        if self.settings.os == "Windows":
            tc = MSBuildToolchain(self)
            tc.generate()
        super().generate()

    def package(self):
        self.default_package()
        numpy_config = next(Path(self.build_folder).rglob("**/numpy/_core/include/numpy/_numpyconfig.h"), None)
        if numpy_config is None:
            self.output.error("Expected Numpy include directory not found")
            raise ConanException("Expected Numpy include directory not found")
        src_dir = numpy_config.parent
        dst_dir = os.path.join(
            self.package_folder, self.relative_site_package_folder(), "numpy", "_core", "include", "numpy"
        )
        copy(self, "_numpyconfig.h", src=src_dir, dst=dst_dir)
        copy(self, "__ufunc_api.h", src=src_dir, dst=dst_dir)
        copy(self, "__multiarray_api.h", src=src_dir, dst=dst_dir)
        rmdir(
            self,
            os.path.join(
                self.package_folder, self.relative_site_package_folder(), "numpy", "_core", "lib", "pkgconfig"
            ),
        )

    def package_info(self):
        super().package_info()
        self.cpp_info.set_property("cpe", "cpe:2.3:a:numpy:numpy:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/numpy/numpy@v{self.version}")
        self.cpp_info.set_property("cmake_target_aliases", ["Python3::NumPy"])  # for use by Python3Config.cmake
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("pkg_config_name", "NumPy")
        self.cpp_info.includedirs = [self.relative_site_package_folder() + "/numpy/_core/include"]
