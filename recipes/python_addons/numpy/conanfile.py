from conan import ConanFile
from conan.errors import ConanException
from conan.tools.files import get, copy

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "numpy"
    mli_name = "Python3__NumPy"
    version = "1.26.4"
    homepage = "https://numpy.org"
    description = "NumPy is the fundamental package for scientific computing with Python"
    license = "BSD-3-Clause"
    python_requires = "python_package/[>=1.0.0]"
    python_requires_extend = "python_package.PythonPackageRecipe"
    exports_sources = "requirements.txt"
    package_type = "shared-library"
    parallel_make = False  # see https://github.com/numpy/numpy/issues/13080

    mlab_hooks = {
        "dependencies.system_libs": [
            "liblapack.so.3",  # FIXME MLAB-2790
            "libblas.so.3",  # FIXME MLAB-2790
            "libcblas.so.3",  # FIXME MLAB-2790
        ]
    }

    @property
    def license_path(self):
        return "LICENSE.txt"

    def source(self):
        get(
            self,
            sha256="2a02aba9ed12e4ac4eb3ea9421c420301a0c6460d9830d74a9df87efa4912010",
            url=f"https://github.com/numpy/numpy/releases/download/v{self.version}/numpy-{self.version}.tar.gz",
            strip_root=True,
        )

    def package(self):
        self.default_package()
        numpy_config = next(self.source_path.rglob("**/numpy/core/include/numpy/_numpyconfig.h"), None)
        if numpy_config is None:
            self.output.error("Expected Numpy include directory not found")
            raise ConanException("Expected Numpy include directory not found")
        src_dir = numpy_config.parent
        dst_dir = self.package_path / self.relative_site_package_folder() / "numpy" / "core" / "include" / "numpy"
        copy(self, "_numpyconfig.h", src=src_dir, dst=dst_dir)
        copy(self, "__ufunc_api.h", src=src_dir, dst=dst_dir)
        copy(self, "__multiarray_api.h", src=src_dir, dst=dst_dir)

    def package_info(self):
        super().package_info()
        self.cpp_info.set_property("cpe", "cpe:2.3:a:numpy:numpy:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("base_purl", "github/numpy/numpy")
        self.cpp_info.set_property("cmake_target_aliases", ["Python3::NumPy"])  # for use by Python3Config.cmake
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("pkg_config_name", "NumPy")
        self.cpp_info.includedirs = [self.relative_site_package_folder() + "/numpy/core/include"]

    @property
    def prefer_setup_py(self):
        # did not get to work it with pyproject.toml using the mesonpy build backend
        return True
