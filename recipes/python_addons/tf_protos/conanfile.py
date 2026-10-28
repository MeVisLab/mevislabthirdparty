import os
import re
from pathlib import Path
from conan import ConanFile
from conan.errors import ConanException
from conan.tools.files import copy, get, load, mkdir, replace_in_file, rmdir, save

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "tf_protos"
    version = "2.21.0"
    homepage = "https://www.tensorflow.org/serving"
    description = "Generated Python protobuf and gRPC modules for TensorFlow Serving"
    license = "Apache-2.0"
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
            sha256="ef3568bb4865d6c1b2564fb5689c19b6b9a5311572cd1f2ff9198636a8520921",
            url=f"https://github.com/tensorflow/tensorflow/archive/refs/tags/v{self.version}.tar.gz",
            destination="tensorflow_src",
            strip_root=True,
        )
        get(
            self,
            sha256="e24e076f9eec7e4892bc4fd30bc4094ec243128ecc7a37e0aab74e2970dd0c68",
            url=f"https://github.com/tensorflow/serving/archive/refs/tags/{self.version}.tar.gz",
            destination="tensorflow_serving_src",
            strip_root=True,
        )

    def build(self):
        out_dir = Path(self.build_folder) / self.relative_site_package_folder() / self.name
        mkdir(self, out_dir)
        save(self, out_dir / "__init__.py", f'__version__ = "{self.version}"\n')

        tensorflow_src = os.path.join(self.source_folder, "tensorflow_src")
        serving_src = os.path.join(self.source_folder, "tensorflow_serving_src")
        xla_src = os.path.join(tensorflow_src, "third_party", "xla")
        tsl_src = os.path.join(xla_src, "third_party", "tsl")
        import_roots = [tsl_src, xla_src, tensorflow_src, serving_src]
        service_proto_files = [
            os.path.join(serving_src, "tensorflow_serving", "apis", "model_service.proto"),
            os.path.join(serving_src, "tensorflow_serving", "apis", "prediction_service.proto"),
        ]
        proto_files = self._collect_proto_closure(service_proto_files, import_roots)
        self._run_protoc(proto_files, import_roots, out_dir, grpc=False)
        self._run_protoc(service_proto_files, import_roots, out_dir, grpc=True)

        for f in Path(out_dir).rglob("*_pb2*.py"):
            self._replace_in_file(f, "from tensorflow.", "from tf_protos.tensorflow.")
            self._replace_in_file(f, "import tensorflow.", "import tf_protos.tensorflow.")
            self._replace_in_file(f, "from tensorflow_serving.", "from tf_protos.tensorflow_serving.")
            self._replace_in_file(f, "import tensorflow_serving.", "import tf_protos.tensorflow_serving.")
            self._replace_in_file(f, "from xla.", "from tf_protos.xla.")
            self._replace_in_file(f, "import xla.", "import tf_protos.xla.")
            self._replace_in_file(f, "from tsl.", "from tf_protos.tsl.")
            self._replace_in_file(f, "import tsl.", "import tf_protos.tsl.")
            self._replace_in_file(f, "__module__ = 'tensorflow.", "__module__ = 'tf_protos.tensorflow.")
            self._replace_in_file(f, "__module__ = 'tensorflow_serving.", "__module__ = 'tf_protos.tensorflow_serving.")
            self._replace_in_file(f, "__module__ = 'xla.", "__module__ = 'tf_protos.xla.")
            self._replace_in_file(f, "__module__ = 'tsl.", "__module__ = 'tf_protos.tsl.")

        for directory in out_dir.rglob("*"):
            if directory.is_dir():
                save(self, directory / "__init__.py", "")

    def _collect_proto_closure(self, start_files, import_roots):
        result = []
        visited = set()

        def visit(proto_file):
            proto_path = Path(proto_file)
            key = str(proto_path)
            if key in visited:
                return
            visited.add(key)
            for imported in self._proto_imports(proto_path):
                dependency = self._resolve_proto_import(imported, import_roots)
                if dependency is not None:
                    visit(dependency)
            result.append(proto_path)

        for proto_file in start_files:
            visit(proto_file)
        return result

    def _proto_imports(self, proto_file):
        return re.findall(r'^\s*import\s+(?:public\s+|weak\s+)?"([^"]+)";', load(self, proto_file), re.MULTILINE)

    def _resolve_proto_import(self, imported, import_roots):
        if imported.startswith("google/protobuf/"):
            return None
        for import_root in import_roots:
            candidate = Path(import_root) / imported
            if candidate.exists():
                return candidate
        raise ConanException(f"Could not resolve proto import {imported!r}")

    def _run_protoc(self, proto_files, import_roots, out_dir, grpc):
        if not proto_files:
            return
        include_args = " ".join(f'-I "{path}"' for path in import_roots)
        output_args = f'--python_out="{out_dir}"'
        if grpc:
            grpc_plugin = self.dependencies["grpc"].buildenv_info.vars(self).get("MEVIS_GRPC_PYTHON_PLUGIN_CMD")
            output_args += f' --plugin=protoc-gen-grpc_python="{grpc_plugin}"' f' --grpc_python_out="{out_dir}"'
        files_arg = " ".join(f'"{path}"' for path in proto_files)
        protoc_cmd = self.dependencies["protobuf"].buildenv_info.vars(self).get("MEVIS_PROTOC_CMD")
        self.run(f'"{protoc_cmd}" {include_args} {output_args} {files_arg}', env="conanrun")

    def _replace_in_file(self, file_path, search, replace):
        if search in load(self, file_path):
            replace_in_file(self, file_path, search, replace)

    def package(self):
        copy(
            self,
            "tf_protos/*",
            src=Path(self.build_folder) / self.relative_site_package_folder(),
            dst=Path(self.package_folder) / self.relative_site_package_folder(),
        )
        copy(
            self,
            "LICENSE",
            src=Path(self.source_folder) / "tensorflow_serving_src",
            dst=Path(self.package_folder) / "licenses",
            keep_path=False,
        )
        rmdir(self, Path(self.package_folder) / self.relative_site_package_folder() / self.name / "__pycache__")

    def package_info(self):
        super().package_info()
        self.cpp_info.set_property("purl", f"pkg:github/tensorflow/serving@{self.version}")
