import json
import os

from conan import ConanFile
from conan.tools.cmake import CMakeDeps
from conan.tools.files import get, replace_in_file

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "ml_dtypes"
    version = "0.6.0"
    homepage = "https://github.com/jax-ml/ml_dtypes"
    description = "stand-alone implementation of several NumPy dtype extensions used in machine learning"
    license = "Apache-2.0"
    python_requires = "python_package/[>=1.0.0]"
    python_requires_extend = "python_package.PythonPackageRecipe"
    exports_sources = "requirements.txt"
    package_type = "shared-library"

    @property
    def license_path(self):
        return "LICENSE"

    def python_requirements(self):
        self.requires("eigen/[>=3.4.0]")
        self.requires("numpy/[>=2.1.0]")

    def source(self):
        get(
            self,
            sha256="8459353101f8c90c17e2167e2c283d78f1e60f325c4bc1e1e851d799969b7614",
            url=f"https://github.com/jax-ml/ml_dtypes/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )
        replace_in_file(
            self,
            os.path.join(self.source_folder, "CMakeLists.txt"),
            "add_subdirectory(third_party/eigen EXCLUDE_FROM_ALL)",
            "find_package(Eigen3 REQUIRED CONFIG)",
        )

    def generate(self):
        super().generate()
        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        generators_folder = self.generators_folder.replace("\\", "/")
        cmake_args = [f"-DCMAKE_PREFIX_PATH={generators_folder}"]
        replace_in_file(
            self,
            os.path.join(self.source_folder, "pyproject.toml"),
            'wheel.packages = ["ml_dtypes"]',
            f'cmake.build-type = "{self.settings.build_type}"\n'
            f"cmake.args = {json.dumps(cmake_args)}\n"
            'wheel.packages = ["ml_dtypes"]',
        )
        self.default_build()

    def package_info(self):
        super().package_info()
        self.cpp_info.set_property("cmake_find_mode", "config")
        self.cpp_info.set_property("purl", f"pkg:github/jax-ml/ml_dtypes@v{self.version}")
