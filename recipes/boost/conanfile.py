# -*- coding: utf-8 -*-
from conans import ConanFile
from conans.client.build.cppstd_flags import cppstd_flag
from conans.model.version import Version
from conans import tools
import os

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

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
        #"python",          # TODO enable boost python
    ]


    # TODO fix requirements
    def requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
    #    self.requires("BZip2/[>=1.0.6]" + channel)
    #    self.requires("LZMA/[>=5.2.3]" + channel)
    #    self.requires("SQLite3/[>=3.27.0]" + channel)
    #    self.requires("ZLIB/[>=1.2.11]" + channel)
    #    self.requires("ZStd/[>=1.4.0]" + channel)

        # self.requires('python/3.9.7' + channel)


    def source(self):
        self.default_source()
        os.rename(os.path.join("sources", "LICENSE_1_0.txt"), os.path.join("sources", "LICENSE"))

        # change rpath on macOS
        tools.replace_in_file('sources/tools/build/src/tools/clang-darwin.jam', '-install_name "@rpath/$(<[1]:D=)" "$(>)"', '-install_name "$(<[1]:D=)" "$(>)"')


    def build(self):
        self._bootstrap()

        flags = self._get_build_flags()
        b2dir = os.path.join(self.source_folder, "sources", "tools", "build")
        b2 = os.path.join(b2dir, ("b2.exe" if tools.os_info.is_windows else "b2"))
        b2 += " %s" % (" ".join(flags))
        b2 += " -j%s" % tools.cpu_count()
        b2 += " --abbreviate-paths"
        b2 += " --debug-configuration"
        b2 += " --disable-icu"
        b2 += ' --build-dir="%s"' % self.build_folder

        with tools.vcvars(self.settings) if self.settings.compiler == "Visual Studio" else tools.no_op():
            with tools.chdir(os.path.join(self.source_folder, "sources")):
                # to locate user config jam (BOOST_BUILD_PATH)
                with tools.environment_append({"BOOST_BUILD_PATH": os.path.join(self.source_folder, "sources", "tools", "build")}):
                    self.run(b2,run_environment=True)


    def package(self):
        self.copy(pattern="*", dst="include/boost", src="sources/boost", excludes="*/CMakeLists.txt")

        out_lib_dir = os.path.join("sources", "stage", "lib")
        self.copy(pattern="*.a",        dst="lib", src=out_lib_dir, keep_path=False)
        self.copy(pattern="*.so",       dst="lib", src=out_lib_dir, keep_path=False, symlinks=True)
        self.copy(pattern="*.so.*",     dst="lib", src=out_lib_dir, keep_path=False, symlinks=True)
        self.copy(pattern="*.dylib*",   dst="lib", src=out_lib_dir, keep_path=False)
        self.copy(pattern="*.lib",      dst="lib", src=out_lib_dir, keep_path=False)
        self.copy(pattern="*.dll",      dst="bin", src=out_lib_dir, keep_path=False)
        self.copy(pattern="boost*.pdb", dst="bin", src=out_lib_dir, keep_path=False)

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.cpp_info.name = "Boost"
        self.cpp_info.names["pkg_config"] = "boost"

        self.env_info.BOOST_ROOT = self.package_folder

        self.cpp_info.components["headers"].libs = []
        self.cpp_info.components["headers"].defines.append("BOOST_ALL_DYN_LINK")
        self.cpp_info.components["headers"].defines.append("BOOST_SYSTEM_NO_DEPRECATED")

        if self.settings.compiler == "Visual Studio":
            # Avoid WINAPI mismatch in boost::log:
            self.cpp_info.components["headers"].defines.append("BOOST_USE_WINAPI_VERSION=0x600")

            self.cpp_info.components["headers"].defines.append("BOOST_ALL_NO_LIB")

        # TODO PCL 1.12.0 uses deprecated filesystem and asio API's.
        #      Check again with newer PCL version when available.
        #self.cpp_info.components["headers"].defines.append("BOOST_ASIO_NO_DEPRECATED")
        #self.cpp_info.components["headers"].defines.append("BOOST_FILESYSTEM_NO_DEPRECATED")

        # Boost::boost is an alias of Boost::headers
        self.cpp_info.components["_boost_cmake"].requires = ["headers"]
        self.cpp_info.components["_boost_cmake"].names["cmake_find_package"] = "boost"
        self.cpp_info.components["_boost_cmake"].names["cmake_find_package_multi"] = "boost"

        self.cpp_info.components["diagnostic_definitions"].libs = []
        self.cpp_info.components["diagnostic_definitions"].defines = ["BOOST_LIB_DIAGNOSTIC"]

        # A target defined by CMake's original Boost find package and used by openvdb
        self.cpp_info.components["disable_autolinking"].libs = []
        self.cpp_info.components['disable_autolinking'].defines = ["BOOST_ALL_NO_LIB"]

        for lib in tools.collect_libs(self):
            # remove boost_ prefix and any suffix
            comp = lib[len("boost_"):].split('-')[0]

            self.output.info(f"creating component {comp}")

            self.cpp_info.components[comp].requires = ["headers"]
            self.cpp_info.components[comp].libs = [lib]
            self.cpp_info.components[comp].bindirs = "lib"

            if comp == "thread" and self.settings.os == "Linux":
                self.cpp_info.components[comp].libs.append("pthread")


    def _bootstrap(self):
        folder = os.path.join(self.source_folder, "sources", "tools", "build")
        try:
            bootstrap = "bootstrap.bat" if tools.os_info.is_windows else "sh bootstrap.sh"
            with tools.vcvars(self.settings) if self.settings.compiler == "Visual Studio" else tools.no_op():
                with tools.chdir(folder):
                    option = "" if tools.os_info.is_windows else "-with-toolset="
                    cmd = "%s --without-icu %s%s" % (bootstrap, option, self._boostrap_toolset())
                    self.output.info(cmd)
                    self.run(cmd)
        except Exception as ex:
            self.output.warn(str(ex))
            if os.path.exists(os.path.join(folder, "bootstrap.log")):
                self.output.warn(tools.load(os.path.join(folder, "bootstrap.log")))
            raise

        self.output.info("boost bootstrap done")


    def _boostrap_toolset(self):
        if self.settings.compiler == "Visual Studio":
            comp_ver = self.settings.compiler.version
            return "vc%s" % ("141" if Version(str(comp_ver)) >= "15" else comp_ver)

        with_toolset = {"apple-clang": "clang"}.get(str(self.settings.compiler), str(self.settings.compiler))
        # fallback for the case when no unversioned gcc/clang is available
        if with_toolset in ["gcc", "clang"] and not tools.which(with_toolset):
            with_toolset = "cc"
        return with_toolset


    def _b2_os(self):
        return {
            "Windows": "windows",
            "Linux": "linux",
            "Android": "android",
            "Macos": "darwin",
            "iOS": "iphone"
        }.get(str(self.settings.os))


    def _b2_address_model(self):
        if str(self.settings.arch) in ["x86_64", "armv8"]:
            return "64"
        return "32"


    def _b2_binary_format(self):
        return {
            "Windows": "pe",
            "Linux": "elf",
            "Android": "elf",
            "Macos": "mach-o",
            "iOS": "mach-o"
        }.get(str(self.settings.os))


    def _b2_architecture(self):
        if str(self.settings.arch).startswith('x86'):
            return 'x86'
        elif str(self.settings.arch).startswith('arm'):
            return 'arm'
        return None


    def _b2_abi(self):
        if str(self.settings.arch).startswith('x86'):
            return "ms" if self.settings.os == "Windows" else "sysv"
        elif str(self.settings.arch).startswith('arm'):
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
        flags.append("-sBOOST_BUILD_PATH=%s" % os.path.join(self.source_folder, "sources", "tools", "build"))

        # TODO fix requirements
        flags.append("-sNO_ZLIB=1")
        flags.append("-sNO_BZIP2=1")
        flags.append("-sNO_LZMA=1")
        flags.append("-sNO_ZSTD=1")
        
        if self.settings.compiler == "Visual Studio":
            # Avoid WINAPI mismatch in boost::log:
            flags.append("define=BOOST_USE_WINAPI_VERSION=0x600")

            flags.append("runtime-link=shared")

        flags.append("threading=multi")
        flags.append("link=shared")
        flags.append("variant=%s" % ("debug" if self.settings.build_type == "Debug" else "release"))

        flags.extend([ "--with-" + c for c in self.boost_components ])

        toolset, version, _ = self._get_toolset_version_and_exe()
        if tools.os_info.is_windows:
            flags.append("toolset=%s-%s" % (toolset,version) )
        else:
            flags.append("toolset=%s" % toolset)

        if self.settings.get_safe("compiler.cppstd"):
            flags.append("cxxflags=%s" % cppstd_flag(
                self.settings.get_safe("compiler"),
                self.settings.get_safe("compiler.version"),
                self.settings.get_safe("compiler.cppstd")
            ))

        cxx_flags = []
        if self.settings.os != "Windows":
            cxx_flags.append("-fPIC")

        if self.settings.os != "Android":
            try:
                if str(self.settings.compiler.libcxx) == "libstdc++":
                    flags.append("define=_GLIBCXX_USE_CXX11_ABI=0")
                elif str(self.settings.compiler.libcxx) == "libstdc++11":
                    flags.append("define=_GLIBCXX_USE_CXX11_ABI=1")
                if "clang" in str(self.settings.compiler):
                    if str(self.settings.compiler.libcxx) == "libc++":
                        cxx_flags.append("-stdlib=libc++")
                        flags.append('linkflags="-stdlib=libc++"')
                    else:
                        cxx_flags.append("-stdlib=libstdc++")
            except:
                pass

        if tools.is_apple_os(self.settings.os):
            if self.settings.get_safe("os.version"):
                cxx_flags.append(tools.apple_deployment_target_flag(self.settings.os, self.settings.os.version))

        cxx_flags = 'cxxflags="%s"' % " ".join(cxx_flags) if cxx_flags else ""
        flags.append(cxx_flags)
        return flags


    def _get_toolset_version_and_exe(self):
        compiler_version = str(self.settings.compiler.version)
        compiler = str(self.settings.compiler)

        if compiler == "gcc":
            return compiler, compiler_version[0], ""
        elif self.settings.compiler == "clang":
            return compiler, compiler_version, ""
        elif self.settings.compiler == "apple-clang":
            return "clang", compiler_version, tools.XCRun(self.settings).cxx
        elif self.settings.os == "Android" and self.settings.compiler == "clang":
            return "clang-linux", compiler_version, ""
        elif self.settings.compiler == "Visual Studio":
            cversion = self.settings.compiler.version
            _msvc_version = "14.1" if Version(str(cversion)) >= "15" else "%s.0" % cversion
            return "msvc", _msvc_version, ""

        return compiler, compiler_version, ""
