# -*- coding: utf-8 -*-
from conans import ConanFile
from conans.errors import ConanException
from conans import tools
import pathlib


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.PythonPackageRecipe'
    parallel_make = False  # parallel make causes trouble on Windows in the Debug build, where several process try to write to vc140.pdb at the same time

    def requirements(self):
        self.default_requirements()

        self.requires(f"cython/[>=0.29.24]@{self.user}/{self.channel}")
        self.requires(f"libzmq/[>=4.3.2]@{self.user}/{self.channel}")
        self.requires(f"packaging/[>=21.3]@{self.user}/{self.channel}")

    def build(self):
        if self.settings.build_type == "Debug":
            # Let setup.py link the debug variant of zmq
            tools.replace_in_file("sources/setup.py", "settings['libraries'].append('zmq')",
                                  "settings['libraries'].append('zmqd')")
        args = ['--zmq="%s"' % self.deps_cpp_info["libzmq"].rootpath]
        if tools.os_info.is_windows:
            args.append('--libzmq="%s"' % self.deps_cpp_info["libzmq"].libs[0])

        self.default_build(args=args)

    def package_info(self):
        super().package_info()

        if tools.os_info.is_linux:
            patchelf = tools.which("patchelf")
            if not patchelf:
                raise ConanException("patchelf could not be found")

            for sofile in pathlib.Path(self.package_folder).rglob('*.so'):
                self.output.info(f"patching RPATH in file: {sofile}")
                self.run(f"{patchelf} --set-rpath '$ORIGIN/../lib' {sofile}")

    @property
    def prefer_setup_py(self):
        # workaround: if using pyproject it currently does not find libzmq
        return True
