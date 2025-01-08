from shutil import which

from conan import ConanFile
from conan.errors import ConanException
from conan.tools.env import Environment
from conan.tools.files import get, patch, replace_in_file

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "pyzmq"
    version = "25.1.2"
    homepage = "https://zguide.zeromq.org/"
    description = "Lightweight and super-fast messaging library built on top of the ZeroMQ library"
    license = ["BSD-3-Clause", "LGPL-3.0"]
    python_requires = "python_package/[>=1.0.0]"
    python_requires_extend = "python_package.PythonPackageRecipe"
    exports_sources = "requirements.txt", "patches/*"
    package_type = "application"
    # parallel make causes trouble on Windows in the Debug build,
    # where several process try to write to vc140.pdb at the same time
    parallel_make = False

    def python_requirements(self):
        self.requires(f"libzmq/[>=4.3.2]")

    @property
    def license_path(self):
        return "LICENSE.*"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def source(self):
        get(self,
            sha256="4df6361aa20dad1572ef83b441d0ef43125e86e139b30e215cad95883166ee4d",
            url=f"https://github.com/zeromq/pyzmq/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True
        )
        patch(self, patch_file="patches/001-windows_libzmq_library_path.patch")

    def build(self):
        env = Environment()
        libzmq_dep = self.dependencies["libzmq"]
        env.append("ZMQ_PREFIX", libzmq_dep.package_folder)
        with env.vars(self).apply():
            if self.settings.build_type == "Debug":
                # Let setup.py link the debug variant of zmq
                replace_in_file(self, self.source_path / "setup.py",
                                "settings['libraries'].append('zmq')",
                                "settings['libraries'].append('zmq_d')")
            self.default_build(env="conanrun")

    def package(self):
        self.default_package()
        if self.settings.os == "Linux":
            patchelf = which("patchelf")
            if not patchelf:
                raise ConanException("patchelf could not be found")
            for sofile in self.package_path.rglob('*.so'):
                self.run(f"{patchelf} --set-rpath '$ORIGIN/../lib' {sofile}")

    def package_info(self):
        super().package_info()
        # self.cpp_info.set_property("cpe", "")  # No own CPE, see libzmq
        self.cpp_info.set_property("base_purl", "github/zeromq/pyzmq")
