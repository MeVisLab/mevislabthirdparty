"""
Parts of the recipe are taken from the Conan Center Index (https://github.com/conan-io/conan-center-index),
licensed under the MIT License.
"""

import os
from shutil import which

from conan import ConanFile
from conan.tools.build.flags import cppstd_flag
from conan.tools.env import Environment
from conan.tools.files import get, copy, collect_libs, files
from conan.tools.microsoft import is_msvc
from conan.tools.layout import basic_layout
from conan.tools.microsoft.visual import msvc_version_to_toolset_version

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "boost"
    display_name = "Boost"
    mli_name = "None"
    version = "1.89.0"
    homepage = "https://www.boost.org"
    description = "Boost provides free peer-reviewed portable C++ source libraries"
    license = "BSL-1.0"
    settings = "os", "compiler", "arch", "build_type"
    package_type = "shared-library"
    exports_sources = ["patches/*"]

    mlab_hooks = {
        "debug_suffix.exclude": [
            "libboost_exception-mt-d-x64.a",
            "libboost_exception-mt-gd-x64.lib",
            "libboost_*-mt-d-x64.*",
            "boost_*-mt-gd-x64.*",
        ],
    }

    boost_components = [
        "atomic",
        "chrono",
        "container",
        "date_time",
        "exception",
        "filesystem",
        "headers",
        "iostreams",
        "json",
        "locale",
        "log",
        "math",
        "program_options",
        "random",
        "regex",
        "serialization",
        "system",
        "thread",
        "timer",
        "type_erasure",
    ]

    def requirements(self):
        self.requires("zlib/[>=1.2.11]")

    def layout(self):
        basic_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="85a33fa22621b4f314f8e85e1a5e2a9363d22e4f4992925d4bb3bc631b5a0c7a",
            url=f"https://archives.boost.io/release/{self.version}/source/boost_{self.version.replace('.','_')}.tar.bz2",
            strip_root=True,
        )

    def build(self):
        self._bootstrap()

        flags = self._get_build_flags()
        b2dir = os.path.join(self.source_folder, "tools", "build")
        b2exe = os.path.join(b2dir, ("b2.exe" if self.settings.os == "Windows" else "b2"))
        b2 = (
            f'{b2exe} {" ".join(flags)} '
            f"-j{os.cpu_count()} "
            f"--abbreviate-paths "
            f"--debug-configuration "
            f"--disable-icu "
            f'--build-dir="{self.build_folder}"'
        )

        # to locate user config jam (BOOST_BUILD_PATH)
        with files.chdir(self, self.source_folder):
            env = Environment()
            env.append_path("BOOST_BUILD_PATH", str(b2dir))
            with env.vars(self).apply():
                self.run(b2)

    def package(self):
        copy(
            self,
            pattern="*",
            src=os.path.join(self.source_folder, "boost"),
            dst=os.path.join(self.package_folder, "include", "boost"),
            excludes="*/CMakeLists.txt",
        )
        copy(self, "LICENSE_1_0.txt", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))

        out_lib_dir = os.path.join(self.source_folder, "stage", "lib")
        copy(self, pattern="*.a", dst=os.path.join(self.package_folder, "lib"), src=out_lib_dir, keep_path=False)
        copy(self, pattern="*.so", dst=os.path.join(self.package_folder, "lib"), src=out_lib_dir, keep_path=False)
        copy(self, pattern="*.so.*", dst=os.path.join(self.package_folder, "lib"), src=out_lib_dir, keep_path=False)
        copy(self, pattern="*.dylib*", dst=os.path.join(self.package_folder, "lib"), src=out_lib_dir, keep_path=False)
        copy(self, pattern="*.lib", dst=os.path.join(self.package_folder, "lib"), src=out_lib_dir, keep_path=False)
        copy(self, pattern="*.dll", dst=os.path.join(self.package_folder, "bin"), src=out_lib_dir, keep_path=False)
        copy(self, pattern="boost*.pdb", dst=os.path.join(self.package_folder, "bin"), src=out_lib_dir, keep_path=False)

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:boost:boost:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/boostorg/boost@boost-{self.version}")
        self.cpp_info.set_property("cmake_file_name", "Boost")
        self.cpp_info.set_property("cmake_target_name", "Boost::boost")

        self.cpp_info.components["headers"].libs = []
        self.cpp_info.components["headers"].set_property("cmake_target_name", "Boost::headers")
        self.cpp_info.components["headers"].defines.append("BOOST_ALL_DYN_LINK")

        if is_msvc(self):
            # Avoid WINAPI mismatch in boost::log:
            self.cpp_info.components["headers"].defines.append("BOOST_ALL_NO_LIB")

        # Boost::boost is an alias of Boost::headers
        self.cpp_info.components["_boost_cmake"].requires = ["headers"]

        self.cpp_info.components["diagnostic_definitions"].libs = []
        self.cpp_info.components["diagnostic_definitions"].defines = ["BOOST_LIB_DIAGNOSTIC"]
        self.cpp_info.components["diagnostic_definitions"].set_property(
            "cmake_target_name", f"Boost::diagnostic_definitions"
        )

        # A target defined by CMake's original Boost find package and used by openvdb
        self.cpp_info.components["disable_autolinking"].libs = []
        self.cpp_info.components["disable_autolinking"].defines = ["BOOST_ALL_NO_LIB"]
        self.cpp_info.components["disable_autolinking"].set_property("cmake_target_name", f"Boost::disable_autolinking")

        for lib in collect_libs(self):
            # remove boost_ prefix and any suffix
            comp = lib[lib.index("_") + 1 :].split("-")[0]

            self.output.info(f"creating component {comp}")

            self.cpp_info.components[comp].requires = ["headers"]
            self.cpp_info.components[comp].libs = [lib]
            self.cpp_info.components[comp].bindirs = ["lib"]
            self.cpp_info.components[comp].set_property("cmake_target_name", f"Boost::{comp}")

        if self.settings.os == "Linux":
            self.cpp_info.components["thread"].system_libs.extend(["m", "pthread"])

    def _bootstrap(self):
        folder = os.path.join(self.source_folder, "tools", "build")
        try:
            bootstrap = "bootstrap.bat" if self.settings.os == "Windows" else "sh bootstrap.sh"
            with files.chdir(self, folder):
                option = "" if self.settings.os == "Windows" else "-with-toolset="
                cmd = f"{bootstrap} --without-icu {option}{self._boostrap_toolset()}"
                self.output.info(cmd)
                self.run(cmd)
        except Exception as ex:
            self.output.warning(str(ex))
            log_path = os.path.join(folder, "bootstrap.log")
            if os.path.exists(log_path):
                self.output.warning(files.load(self, log_path))
            raise
        self.output.info("boost bootstrap done")

    def _boostrap_toolset(self):
        if is_msvc(self):
            vc_version = msvc_version_to_toolset_version(self.settings.compiler.version)[1:]
            return f"vc{vc_version}"

        with_toolset = {"apple-clang": "clang"}.get(str(self.settings.compiler), str(self.settings.compiler))
        # fallback for the case when no unversioned gcc/clang is available
        if with_toolset in ["gcc", "clang"] and not which(with_toolset):
            with_toolset = "cc"
        return with_toolset

    def _b2_os(self):
        return {
            "Windows": "windows",
            "Linux": "linux",
            "Macos": "darwin",
        }.get(str(self.settings.os))

    def _b2_address_model(self):
        if str(self.settings.arch) in ["x86_64", "armv8"]:
            return "64"
        return "32"

    def _b2_binary_format(self):
        return {
            "Windows": "pe",
            "Linux": "elf",
            "Macos": "mach-o",
        }.get(str(self.settings.os))

    def _b2_architecture(self):
        for arch in ("x86", "arm"):
            if str(self.settings.arch).startswith(arch):
                return arch

    def _b2_abi(self):
        if str(self.settings.arch).startswith("x86"):
            return "ms" if self.settings.os == "Windows" else "sysv"
        elif str(self.settings.arch).startswith("arm"):
            return "aapcs"
        return None

    def _get_build_flags(self):
        flags = []

        # https://www.boost.org/doc/libs/1_70_0/libs/context/doc/html/context/architectures.html
        if self._b2_os():
            flags.append("target-os=%s" % self._b2_os())
        if self._b2_architecture():
            flags.append("architecture=%s" % self._b2_architecture())
        if self._b2_address_model():
            flags.append("address-model=%s" % self._b2_address_model())
        if self._b2_binary_format():
            flags.append("binary-format=%s" % self._b2_binary_format())
        if self._b2_abi():
            flags.append("abi=%s" % self._b2_abi())

        flags.append("--layout=tagged")
        flags.append(f"-sBOOST_BUILD_PATH={os.path.join(self.source_folder, 'sources', 'tools', 'build')}")

        # TODO fix requirements
        flags.append("-sNO_BZIP2=1")
        flags.append("-sNO_ZLIB=0")
        flags.append("-sNO_LZMA=1")
        flags.append("-sNO_ZSTD=1")

        zlib_info = self.dependencies["zlib"].cpp_info
        zlib_name = "zlib" if self.settings.os == "Windows" else "z"
        debug_suffix = "_d" if self.settings.build_type == "Debug" else ""
        flags.append('-sZLIB_INCLUDE="%s"' % zlib_info.includedirs[0].replace("\\", "/"))
        flags.append('-sZLIB_LIBPATH="%s"' % zlib_info.libdirs[0].replace("\\", "/"))
        flags.append(f"-sZLIB_BINARY={zlib_name}{debug_suffix}")

        flags.append("boost.locale.iconv=on")
        flags.append("boost.locale.icu=off")

        if is_msvc(self):
            # Avoid WINAPI mismatch in boost::log:
            flags.append("runtime-link=shared")

        flags.append("threading=multi")
        flags.append("link=shared")
        flags.append("variant=%s" % ("debug" if self.settings.build_type == "Debug" else "release"))
        flags.extend(["--with-" + c for c in self.boost_components])
        flags.append(self._get_toolset_flag())

        if self.settings.get_safe("compiler.cppstd"):
            flags.append(f"cxxflags={cppstd_flag(self)}")

        cxx_flags = []
        if self.settings.os != "Windows":
            cxx_flags.append("-fPIC")

        if self.settings.get_safe("compiler.libcxx") == "libstdc++":
            flags.append("define=_GLIBCXX_USE_CXX11_ABI=0")
        elif self.settings.get_safe("compiler.libcxx") == "libstdc++11":
            flags.append("define=_GLIBCXX_USE_CXX11_ABI=1")
        if "clang" in str(self.settings.compiler):
            if self.settings.get_safe("compiler.libcxx") == "libc++":
                cxx_flags.append("-stdlib=libc++")
                flags.append('linkflags="-stdlib=libc++"')
            else:
                cxx_flags.append("-stdlib=libstdc++")
        if cxx_flags:
            flags.append(f'cxxflags="{" ".join(cxx_flags)}"')
        return flags

    def _get_toolset_flag(self):
        toolset = str(self.settings.compiler)
        if is_msvc(self):
            vc_version = msvc_version_to_toolset_version(self.settings.compiler.version)[1:]
            toolset = f"msvc-{vc_version[:2]}.{vc_version[2]}"
        return f"toolset={toolset}"
