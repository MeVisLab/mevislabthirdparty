import os
from pathlib import Path
from typing import Iterable

from conan import ConanFile
from conan.tools.files import copy, get, load, mkdir, replace_in_file, rmdir, save

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "triton_protos"
    version = "26.08"
    homepage = "https://github.com/triton-inference-server/common"
    description = "Generated Python protobuf and gRPC modules for Triton Inference Server"
    license = "BSD-3-Clause"
    python_requires = "python_package/[>=1.0.0]"
    python_requires_extend = "python_package.PythonPackageRecipe"
    package_type = "application"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def python_requirements(self):
        self.requires("protobuf/[>=35.0]", run=True)
        self.requires("grpc/[>=1.81.1]", visible=False)
        self.requires("grpcio/[>=1.81.1]")

    @property
    def license_path(self):
        return "LICENSE"

    def source(self):
        get(
            self,
            sha256="690d52c3a813af519edee573e277ea1f375db3fb1180ddf28b6ef0b009f5dca1",
            url=f"https://github.com/triton-inference-server/common/archive/refs/heads/r{self.version}.tar.gz",
            strip_root=True,
        )

    def build(self):
        out_dir = os.path.join(self.build_folder, self.relative_site_package_folder(), self.name)
        mkdir(self, out_dir)
        save(self, os.path.join(out_dir, "__init__.py"), f'__version__ = "{self.version}"\n')

        proto_root = os.path.join(self.source_folder, "protobuf")
        proto_files = Path(proto_root).rglob("*.proto")
        self._run_protoc(proto_files, [proto_root], out_dir)
        for file in Path(out_dir).rglob("*_pb2*.py"):
            self._replace_in_file(file, "__module__ = '", "__module__ = 'triton_protos.")
            self._replace_in_file(file, "import model_config_pb2", "from triton_protos import model_config_pb2")
            self._replace_in_file(file, "import grpc_service_pb2", "from triton_protos import grpc_service_pb2")

    def _run_protoc(self, proto_files: Iterable[str], import_roots: Iterable[str], out_dir: str):
        grpc_plugin = self.dependencies["grpc"].buildenv_info.vars(self).get("MEVIS_GRPC_PYTHON_PLUGIN_CMD")
        include_args = " ".join(f'-I "{path}"' for path in import_roots)
        output_args = (
            f'--python_out="{out_dir}"'
            f' --plugin=protoc-gen-grpc_python="{grpc_plugin}"'
            f' --grpc_python_out="{out_dir}"'
        )
        files_arg = " ".join(f'"{path}"' for path in proto_files)
        protoc_cmd = self.dependencies["protobuf"].buildenv_info.vars(self).get("MEVIS_PROTOC_CMD")
        self.run(f'"{protoc_cmd}" {include_args} {output_args} {files_arg}', env="conanrun")

    def _replace_in_file(self, file_path: str, search: str, replace: str):
        if search in load(self, file_path):
            replace_in_file(self, file_path, search, replace)

    def package(self):
        copy(
            self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"), keep_path=False
        )
        copy(
            self,
            "triton_protos/*",
            src=os.path.join(self.build_folder, self.relative_site_package_folder()),
            dst=os.path.join(self.package_folder, self.relative_site_package_folder()),
        )
        rmdir(self, os.path.join(self.package_folder, self.relative_site_package_folder(), self.name, "__pycache__"))

    def package_info(self):
        super().package_info()
        self.cpp_info.set_property("purl", f"pkg:github/triton-inference-server/server@v{self.version}")
