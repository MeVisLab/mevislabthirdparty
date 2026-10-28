import os
import shlex
from pathlib import Path
from types import SimpleNamespace
from conan import ConanFile
from conan.errors import ConanException
from conan.tools.env import Environment
from conan.tools.files import get, load, patch, copy, replace_in_file

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "grpcio"
    version = "1.84.0"
    homepage = "https://grpc.io"
    description = "HTTP/2-based RPC framework for Python"
    license = "Apache-2.0"
    python_requires = "python_package/[>=1.0.0]"
    python_requires_extend = "python_package.PythonPackageRecipe"
    exports_sources = "requirements.txt", "patches/*"
    package_type = "shared-library"

    @property
    def license_path(self):
        return "LICENSE"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def python_requirements(self):
        self.requires("grpc/[>=1.81.1]", visible=False)
        self.requires("abseil/[>=20230802.1]")
        self.requires("c-ares/[>=1.34]")
        self.requires("openssl/[>=3.5]")
        self.requires("re2/[>=20231101]")
        self.requires("zlib/[>=1.3]")

    def source(self):
        get(
            self,
            sha256="17a4d25717f4871eb71cfdf191f7491f66a59c8ebc782ab53d52fcbfc478959f",
            url=f"https://github.com/grpc/grpc/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )
        patch(
            self,
            patch_file="patches/001-system-dependencies.patch",
            patch_description="Allow grpcio to link against our dependencies",
        )
        patch(
            self,
            patch_file="patches/002-spawn-patch-for-setuptools-83.patch",
        )

        typing_imported = [
            py
            for py in Path(self.source_folder, "src", "python", "grpcio").rglob("*.py")
            if "from typing_extensions import" in load(self, py)
        ]
        if not typing_imported:
            raise ConanException(f"No typing_extensions imports found")
        for py in typing_imported:
            replace_in_file(self, py, "from typing_extensions import", "from typing import")

    def build(self):
        def _dep_info(dependency_name, component=None):
            dependency = self.dependencies[dependency_name].cpp_info
            if not component:
                includedirs = os.pathsep.join(dependency.aggregated_components().includedirs)
                libraries = os.pathsep.join(dependency.aggregated_components().libs)
            else:
                includedirs = os.pathsep.join(dependency.components[component].includedirs)
                libraries = os.pathsep.join(dependency.components[component].libs)
            return SimpleNamespace(includedirs=includedirs, libraries=libraries)

        env = Environment()
        env.define("GRPC_BUILD_WITH_BORING_SSL_ASM", "0")
        env.define("GRPC_PYTHON_BUILD_WITH_CYTHON", "1")
        env.define("GRPC_PYTHON_USE_PREBUILT_GRPC_CORE", "1")

        env.define("GRPC_PYTHON_BUILD_SYSTEM_ABSL", "1")
        env.define("GRPC_PYTHON_BUILD_SYSTEM_CARES", "1")
        env.define("GRPC_PYTHON_BUILD_SYSTEM_OPENSSL", "1")
        env.define("GRPC_PYTHON_BUILD_SYSTEM_RE2", "1")
        env.define("GRPC_PYTHON_BUILD_SYSTEM_ZLIB", "1")

        dep = _dep_info("abseil")
        env.define("GRPC_PYTHON_SYSTEM_ABSL_INCLUDE_DIRS", dep.includedirs)
        env.define("GRPC_PYTHON_SYSTEM_ABSL_LIBRARIES", dep.libraries)

        dep = _dep_info("c-ares")
        env.define("GRPC_PYTHON_SYSTEM_CARES_INCLUDE_DIRS", dep.includedirs)
        env.define("GRPC_PYTHON_SYSTEM_CARES_LIBRARIES", dep.libraries)

        dep = _dep_info("openssl")
        env.define("GRPC_PYTHON_SYSTEM_OPENSSL_INCLUDE_DIRS", dep.includedirs)
        env.define("GRPC_PYTHON_SYSTEM_OPENSSL_LIBRARIES", dep.libraries)

        dep = _dep_info("re2")
        env.define("GRPC_PYTHON_SYSTEM_RE2_INCLUDE_DIRS", dep.includedirs)
        env.define("GRPC_PYTHON_SYSTEM_RE2_LIBRARIES", dep.libraries)

        dep = _dep_info("zlib")
        env.define("GRPC_PYTHON_SYSTEM_ZLIB_INCLUDE_DIRS", dep.includedirs)
        env.define("GRPC_PYTHON_SYSTEM_ZLIB_LIBRARIES", dep.libraries)

        env.define("GRPC_PYTHON_PREBUILT_GRPC_CORE_LIBRARIES", _dep_info("grpc", "_grpc").libraries)

        lib_dir_flag = "/LIBPATH:" if self.settings.os == "Windows" else "-L"
        flags = []
        for dependency_name in ("grpc", "abseil", "c-ares", "openssl", "re2", "zlib"):
            for lib_dir in self.dependencies[dependency_name].cpp_info.aggregated_components().libdirs:
                flags.append(f"{lib_dir_flag}{lib_dir}")

        if self.settings.os == "Windows":
            runtime_flag = "/MDd" if self.settings.build_type == "Debug" else "/MD"
            env.define(
                "GRPC_PYTHON_CFLAGS",
                f"/std:c++20 /std:c11 {runtime_flag} /Zc:preprocessor"
                + (" /UNDEBUG" if self.settings.build_type == "Debug" else ""),
            )
        else:
            env.define(
                "GRPC_PYTHON_CFLAGS",
                "-std=c++20 -fvisibility=hidden -fno-wrapv -fno-exceptions"
                + (" -UNDEBUG" if self.settings.build_type == "Debug" else ""),
            )
            flags.extend(["-lpthread", "-static-libgcc"])

        if self.settings.os == "Windows":
            env.define("GRPC_PYTHON_LDFLAGS", " ".join(f'"{flag}"' for flag in flags))
        else:
            env.define("GRPC_PYTHON_LDFLAGS", " ".join(shlex.quote(flag) for flag in flags))

        with env.vars(self).apply():
            self.default_build(env="conanrun")

    def package(self):
        super().package()
        for bindir in self.dependencies["grpc"].cpp_info.bindirs:
            copy(
                self,
                pattern="grpc_python_plugin*",
                src=bindir,
                dst=os.path.join(self.package_folder, "bin"),
                keep_path=False,
            )

    def package_info(self):
        super().package_info()
        self.cpp_info.set_property("cpe", f"cpe:2.3:a:grpc:grpc:{self.version}:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/grpc/grpc@v{self.version}")
