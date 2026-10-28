import os
import re

from conan import ConanFile
from conan.errors import ConanException
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import replace_in_file, copy, get, load, rmdir

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "grpc"
    version = "1.84.0"
    homepage = "https://grpc.io"
    description = "A high performance, open source universal RPC framework"
    license = "Apache-2.0"
    package_type = "static-library"
    exports_sources = "patches/*.patch"
    settings = "os", "arch", "compiler", "build_type"

    mlab_hooks = {"folders.exclude": ["res"]}

    def layout(self):
        cmake_layout(self, src_folder="src", generator="Ninja")

    def requirements(self):
        self.requires("abseil/[>=20230802.1]", transitive_libs=True, transitive_headers=True)
        self.requires("c-ares/[>=1.34]")
        self.requires("openssl/[>=3.5]")
        self.requires("protobuf/[>=35.0]", transitive_headers=True)
        self.requires("re2/[>=20231101]")
        self.requires("zlib/[>=1.3]")

    def source(self):
        get(
            self,
            sha256="17a4d25717f4871eb71cfdf191f7491f66a59c8ebc782ab53d52fcbfc478959f",
            url=f"https://github.com/grpc/grpc/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )
        # third_party/grpc-proto is a submodule missing from the source archive
        grpc_deps = load(self, os.path.join(self.source_folder, "bazel", "grpc_deps.bzl"))
        grpc_proto = re.search(
            r'name = "grpc_proto",\s*sha256 = "(\w+)",\s*strip_prefix = "grpc-proto-(\w+)"', grpc_deps
        )
        if not grpc_proto:
            raise ConanException("Could not read the grpc-proto revision from bazel/grpc_deps.bzl")
        get(
            self,
            sha256=grpc_proto.group(1),
            url=f"https://github.com/grpc/grpc-proto/archive/{grpc_proto.group(2)}.tar.gz",
            destination=os.path.join(self.source_folder, "third_party", "grpc-proto"),
            strip_root=True,
        )

        replace_in_file(
            self, os.path.join(self.source_folder, "CMakeLists.txt"), "include(cmake/msvc_static_runtime.cmake)", ""
        )

        # remove unused thirdparty directories
        rmdir(self, os.path.join(self.source_folder, "third_party", "abseil-cpp"))
        rmdir(self, os.path.join(self.source_folder, "third_party", "benchmark"))
        rmdir(self, os.path.join(self.source_folder, "third_party", "bloaty"))
        rmdir(self, os.path.join(self.source_folder, "third_party", "boringssl-with-bazel"))
        rmdir(self, os.path.join(self.source_folder, "third_party", "cares"))
        rmdir(self, os.path.join(self.source_folder, "third_party", "cares/cares"))
        rmdir(self, os.path.join(self.source_folder, "third_party", "cel-spec"))
        rmdir(self, os.path.join(self.source_folder, "third_party", "dock"))
        rmdir(self, os.path.join(self.source_folder, "third_party", "envoy-api"))
        rmdir(self, os.path.join(self.source_folder, "third_party", "googleapis"))
        rmdir(self, os.path.join(self.source_folder, "third_party", "googletest"))
        rmdir(self, os.path.join(self.source_folder, "third_party", "objective_c"))
        rmdir(self, os.path.join(self.source_folder, "third_party", "opencensus-proto"))
        rmdir(self, os.path.join(self.source_folder, "third_party", "opentelemetry-cpp"))
        rmdir(self, os.path.join(self.source_folder, "third_party", "opentelemetry"))
        rmdir(self, os.path.join(self.source_folder, "third_party", "protobuf"))
        rmdir(self, os.path.join(self.source_folder, "third_party", "protoc-gen-validate"))
        rmdir(self, os.path.join(self.source_folder, "third_party", "re2"))
        rmdir(self, os.path.join(self.source_folder, "third_party", "toolchains"))
        rmdir(self, os.path.join(self.source_folder, "third_party", "xds"))
        rmdir(self, os.path.join(self.source_folder, "third_party", "zlib"))

    def generate(self):
        cd = CMakeDeps(self)
        cd.generate()

        tc = CMakeToolchain(self, generator="Ninja")
        tc.cache_variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.cache_variables["BUILD_SHARED_LIBS"] = False
        tc.cache_variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True

        tc.cache_variables["gRPC_BUILD_CODEGEN"] = True
        tc.cache_variables["gRPC_BUILD_TESTS"] = "OFF"
        tc.cache_variables["gRPC_INSTALL"] = True
        tc.cache_variables["gRPC_INSTALL_SHAREDIR"] = "res/grpc"

        tc.cache_variables["gRPC_DOWNLOAD_ARCHIVES"] = False
        tc.cache_variables["gRPC_USE_SYSTEMD"] = False

        tc.cache_variables["gRPC_BUILD_GRPC_CSHARP_PLUGIN"] = False
        tc.cache_variables["gRPC_BUILD_GRPC_NODE_PLUGIN"] = False
        tc.cache_variables["gRPC_BUILD_GRPC_OBJECTIVE_C_PLUGIN"] = False
        tc.cache_variables["gRPC_BUILD_GRPC_PHP_PLUGIN"] = False
        tc.cache_variables["gRPC_BUILD_GRPC_PYTHON_PLUGIN"] = True
        tc.cache_variables["gRPC_BUILD_GRPC_RUBY_PLUGIN"] = False
        tc.cache_variables["gRPC_BUILD_GRPCPP_OTEL_PLUGIN"] = False

        # use the find_package versions
        tc.cache_variables["gRPC_ZLIB_PROVIDER"] = "package"
        tc.cache_variables["gRPC_CARES_PROVIDER"] = "package"
        tc.cache_variables["gRPC_RE2_PROVIDER"] = "package"
        tc.cache_variables["gRPC_SSL_PROVIDER"] = "package"
        tc.cache_variables["gRPC_PROTOBUF_PROVIDER"] = "package"
        tc.cache_variables["gRPC_BENCHMARK_PROVIDER"] = "none"
        tc.cache_variables["gRPC_ABSL_PROVIDER"] = "package"
        tc.cache_variables["gRPC_OPENTELEMETRY_PROVIDER"] = "package"

        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "share"))

    def package_info(self):
        self.cpp_info.set_property("cpe", f"cpe:2.3:a:grpc:grpc:{self.version}:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/grpc/grpc@v{self.version}")

        self.cpp_info.set_property("cmake_file_name", "gRPC")
        self.cpp_info.resdirs = ["res"]

        e = ".exe" if self.settings.os == "Windows" else ""
        d = os.path.join(self.package_folder, "bin")
        self.buildenv_info.define_path("MEVIS_GRPC_PYTHON_PLUGIN_CMD", os.path.join(d, f"grpc_python_plugin{e}"))
        self.runenv_info.define_path("MEVIS_GRPC_PYTHON_PLUGIN_CMD", os.path.join(d, f"grpc_python_plugin{e}"))
        self.buildenv_info.define_path("MEVIS_GRPC_CPP_PLUGIN_CMD", os.path.join(d, f"grpc_cpp_plugin{e}"))
        self.runenv_info.define_path("MEVIS_GRPC_CPP_PLUGIN_CMD", os.path.join(d, f"grpc_cpp_plugin{e}"))

        ssl_roots_file_path = os.path.join(self.package_folder, "res", "grpc", "roots.pem")
        self.runenv_info.define_path("GRPC_DEFAULT_SSL_ROOTS_FILE_PATH", ssl_roots_file_path)

        debug_suffix = "_d" if self.settings.build_type == "Debug" else ""
        system_libs = ["crypt32", "ws2_32", "wsock32"] if self.settings.os == "Windows" else ["m", "pthread"]
        common_requires = [
            "zlib::zlib",
            "re2::re2",
            "c-ares::c-ares",
            "abseil::absl_base",
            "abseil::absl_config",
            "abseil::absl_core_headers",
            "abseil::absl_log_severity",
            "abseil::absl_cleanup",
            "abseil::absl_flags",
            "abseil::absl_flags_marshalling",
            "abseil::absl_any_invocable",
            "abseil::absl_bind_front",
            "abseil::absl_check",
            "abseil::absl_log_globals",
            "abseil::absl_log",
            "abseil::absl_memory",
            "abseil::absl_bits",
            "abseil::absl_random_random",
            "abseil::absl_status",
            "abseil::absl_statusor",
            "abseil::absl_cord",
            "abseil::absl_str_format",
            "abseil::absl_strings",
            "abseil::absl_synchronization",
            "abseil::absl_time",
            "abseil::absl_optional",
            "abseil::absl_algorithm_container",
            "abseil::absl_no_destructor",
            "abseil::absl_btree",
            "abseil::absl_flat_hash_map",
            "abseil::absl_flat_hash_set",
            "abseil::absl_inlined_vector",
            "abseil::absl_node_hash_map",
            "abseil::absl_function_ref",
            "abseil::absl_hash",
            "abseil::absl_type_traits",
            "abseil::absl_random_bit_gen_ref",
            "abseil::absl_random_distributions",
            "abseil::absl_string_view",
            "abseil::absl_span",
            "abseil::absl_utility",
            "abseil::absl_dynamic_annotations",
            "abseil::absl_prefetch",
            "abseil::absl_layout",
            "abseil::absl_absl_check",
            "abseil::absl_absl_log",
            "abseil::absl_strings_internal",
        ]

        component = self.cpp_info.components["_grpc"]
        component.set_property("cmake_target_name", "gRPC::grpc")
        component.set_property("pkg_config_name", "grpc")
        component.libs = [
            f"grpc{debug_suffix}",
            f"gpr{debug_suffix}",
            f"address_sorting{debug_suffix}",
            f"upb_json_lib{debug_suffix}",
            f"upb_textformat_lib{debug_suffix}",
            f"upb_reflection_lib{debug_suffix}",
            f"upb_mini_descriptor_lib{debug_suffix}",
            f"upb_descriptor_lib{debug_suffix}",
            f"upb_wire_lib{debug_suffix}",
            f"upb_message_lib{debug_suffix}",
            f"upb_mini_table_lib{debug_suffix}",
            f"upb_hash_lib{debug_suffix}",
            f"upb_base_lib{debug_suffix}",
            f"upb_mem_lib{debug_suffix}",
            f"upb_lex_lib{debug_suffix}",
            f"utf8_range_lib{debug_suffix}",
        ]
        component.requires = common_requires + ["openssl::ssl", "openssl::crypto"]
        component.system_libs = system_libs

        component = self.cpp_info.components["grpc++"]
        component.set_property("cmake_target_name", "gRPC::grpc++")
        component.set_property("pkg_config_name", "grpc++")
        component.libs = [f"grpc++{debug_suffix}"]
        component.requires = ["_grpc", "protobuf::libprotobuf"]
        component.system_libs = system_libs

        component = self.cpp_info.components["grpc_unsecure"]
        component.set_property("cmake_target_name", "gRPC::grpc_unsecure")
        component.set_property("pkg_config_name", "grpc_unsecure")
        component.libs = [
            f"grpc_unsecure{debug_suffix}",
            f"gpr{debug_suffix}",
            f"address_sorting{debug_suffix}",
            f"upb_textformat_lib{debug_suffix}",
            f"upb_reflection_lib{debug_suffix}",
            f"upb_mini_descriptor_lib{debug_suffix}",
            f"upb_descriptor_lib{debug_suffix}",
            f"upb_wire_lib{debug_suffix}",
            f"upb_message_lib{debug_suffix}",
            f"upb_mini_table_lib{debug_suffix}",
            f"upb_hash_lib{debug_suffix}",
            f"upb_base_lib{debug_suffix}",
            f"upb_mem_lib{debug_suffix}",
            f"upb_lex_lib{debug_suffix}",
            f"utf8_range_lib{debug_suffix}",
        ]
        component.requires = common_requires
        component.system_libs = system_libs

        component = self.cpp_info.components["grpc++_unsecure"]
        component.set_property("cmake_target_name", "gRPC::grpc++_unsecure")
        component.set_property("pkg_config_name", "grpc++_unsecure")
        component.libs = [f"grpc++_unsecure{debug_suffix}"]
        component.requires = ["grpc_unsecure", "protobuf::libprotobuf"]
        component.system_libs = system_libs

        component = self.cpp_info.components["grpc++_reflection"]
        component.set_property("cmake_target_name", "gRPC::grpc++_reflection")
        component.set_property("pkg_config_name", "grpc++_reflection")
        component.libs = [f"grpc++_reflection{debug_suffix}"]
        component.requires = ["grpc++"]
        component.system_libs = system_libs

        component = self.cpp_info.components["grpc_plugin_support"]
        component.set_property("cmake_target_name", "gRPC::grpc_plugin_support")
        component.set_property("pkg_config_name", "grpc_plugin_support")
        component.libs = [f"grpc_plugin_support{debug_suffix}"]
        component.requires = ["grpc++", "protobuf::libprotobuf", "protobuf::libprotoc"]
        component.system_libs = system_libs
