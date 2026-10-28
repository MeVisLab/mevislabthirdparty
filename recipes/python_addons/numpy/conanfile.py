import os
from pathlib import Path

from conan import ConanFile
from conan.errors import ConanException
from conan.tools.env import Environment
from conan.tools.files import get, copy, rmdir
from conan.tools.microsoft import MSBuildToolchain

required_conan_version = ">=2.32.0"

# FIXME numpy links to blas/lapack/openblas if found on the system.
# It's also recommended to use it, since it's way faster than the fallback implementation.
# Either way, we should prevent blas/lapack/openblas from being used or we provide it explicitly as a dependency.


class ConanRecipe(ConanFile):
    name = "numpy"
    mli_name = "Python3__NumPy"
    version = "2.5.3"
    homepage = "https://numpy.org"
    description = "NumPy is the fundamental package for scientific computing with Python"
    license = "BSD-3-Clause"
    python_requires = "python_package/[>=1.0.0]"
    python_requires_extend = "python_package.PythonPackageRecipe"
    exports_sources = "requirements.txt"
    package_type = "shared-library"

    mlab_hooks = {
        "dependencies.system_libs": ["libflexiblas.so.3", "libopenblas.so.0"],
    }

    @property
    def license_path(self):
        return "LICENSE.txt"

    def source(self):
        get(
            self,
            sha256="df2d5874ff183595a4ba404edd04f6bd9b5505c1d7708573f6a6c17489a67563",
            url=f"https://github.com/numpy/numpy/releases/download/v{self.version}/numpy-{self.version}.tar.gz",
            strip_root=True,
        )

    def generate(self):
        if self.settings.os == "Windows":
            tc = MSBuildToolchain(self)
            tc.generate()
        super().generate()

    def build(self):
        if self.settings.build_type == "Debug" and self.settings.os == "Windows":
            # convince Meson to do the right thing:
            env = Environment()
            # Meson tries to link python313_d.lib without providing a lib path
            # (this was caused by us linking against the Debug MSVC runtime, otherwise it links without problems)
            # the following seems to be the only way to provide the path:
            extra_libdirs = self.dependencies["python"].cpp_info.libdirs
            env.append("LDFLAGS", f'/LIBPATH:"{extra_libdirs[0]}"', separator=" ")
            with env.vars(self).apply():
                self.default_build(
                    # override default values:
                    config_settings=[
                        "setup-args=-Dbuildtype=debug",
                        "setup-args=-Db_vscrt=from_buildtype",
                    ]
                )
        else:
            self.default_build()

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
        self.cpp_info.set_property("cpe", f"cpe:2.3:a:numpy:numpy:{self.version}:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/numpy/numpy@v{self.version}")
        self.cpp_info.set_property("cmake_target_aliases", ["Python3::NumPy"])  # for use by Python3Config.cmake
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("pkg_config_name", "NumPy")
        self.cpp_info.includedirs = [self.relative_site_package_folder() + "/numpy/_core/include"]
