import glob
import os
import shutil
import textwrap

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.env import VirtualRunEnv
from conan.tools.files import get, copy, rmdir, chdir, save, replace_in_file, patch, collect_libs
from conan.tools.gnu import Autotools, AutotoolsToolchain, PkgConfigDeps
from conan.tools.layout import basic_layout
from conan.tools.microsoft import is_msvc
from conan.tools.scm import Version

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "python"
    version = "3.11.10"
    homepage = "https://www.python.org"
    description = "An interpreted, interactive, object-oriented programming language"
    license = "Python-2.0"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = ["CMakeLists.txt", "cmake/*", "patches/*.patch"]

    mlab_hooks = {
        "debug_suffix.skip": True,
        "folders.exclude": ["DLLs", "libs", "Scripts", "python*.dll", "python*.exe", "MeVisPython*.exe"],
        "dependencies.system_libs": [
            "libcrypt.so.*",  # required for python module _crypt
            "libb2.so.1",  # required for python module _blake2
            "libbsd.so.0",  # required for python module fcntl
            "libuuid.so.1",  # required for python module _uuid
        ],
    }

    def configure(self):
        self.settings.rm_safe("compiler.cppstd")
        self.settings.rm_safe("compiler.libcxx")

    def requirements(self):
        self.requires("zlib/[>=1.2.11]")
        self.requires("sqlite3/[>=3.33.0]")
        self.requires("bzip2/[>=1.0.8]")
        self.requires("xz-utils/[>=5.2.5]")
        self.requires("libffi/[>=3.3]")
        self.requires("openssl/[>=3.0]")

    def layout(self):
        if is_msvc(self):
            cmake_layout(self, src_folder="src")
        else:
            basic_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="92f2faf242681bfa406d53a51e17d42c5373affe23a130cd9697e132ef574706",
            url=f"https://www.python.org/ftp/python/{self.version}/Python-{self.version}.tgz",
            strip_root=True,
        )
        patch(self, patch_file="patches/001-macos_remove_rpath_prefix.patch")
        patch(
            self,
            patch_file="patches/002-win32_multiprocessing_pool_limit.patch",
            patch_type="bugfix",
            patch_description="short term fix for https://github.com/python/cpython/issues/89240",
        )
        patch(
            self,
            patch_file="patches/003-sysconfig_posix_prefix.patch",
            patch_description="replace build system prefix path in sysconfig with current python home",
        )
        patch(self, patch_file="patches/004-disable_modules_with_external_deps.patch")
        patch(self, patch_file="patches/005-configure_abort_on_failure.patch")
        patch(
            self,
            patch_file="patches/006-hide_own_importlib_frames.patch",
            patch_description="suppress frames from our own injected importlib code in ImportError stacktraces",
        )

    def generate(self):
        if is_msvc(self):
            tc = CMakeToolchain(self)
            tc.variables["PYTHON_VERSION"] = self.version
            tc.variables["BUILD_SHARED_LIBS"] = True
            tc.generate()
            cd = CMakeDeps(self)
            cd.generate()
        else:
            env = VirtualRunEnv(self)
            env.generate(scope="build")
            tc = AutotoolsToolchain(self, prefix=self.package_folder)
            tc.configure_args.append("--enable-shared")
            tc.configure_args.append("--with-computed-gotos")
            tc.configure_args.append("--with-ensurepip=yes")
            env = tc.environment()
            # for the build step:
            if self.settings.os == "Linux":
                libffi_info = self.dependencies["libffi"].cpp_info
                tc.extra_cflags = ["-I" + libffi_info.includedirs[0]]
                tc.extra_ldflags = ["-L" + libffi_info.libdirs[0]]
            # for the install step:
            env.define("LD_LIBRARY_PATH", os.path.join(self.package_folder, "lib"))
            env.define("DYLD_LIBRARY_PATH", os.path.join(self.package_folder, "lib"))
            tc.generate()
            pc = PkgConfigDeps(self)
            pc.generate()

    def build(self):
        configureFile = os.path.join(self.source_folder, "configure")
        if self.settings.build_type == "Debug":
            # Let configure use the debug variant of the libraries
            replace_in_file(self, configureFile, "-lz", "-lz_d")
            replace_in_file(self, configureFile, "-lbz2", "-lbz2_d")
            replace_in_file(self, configureFile, "-llzma", "-llzma_d")
            # replace_in_file(self, configureFile, "-lffi", "-lffid")  # not found
            replace_in_file(self, configureFile, "-lsqlite3", "-lsqlite3_d -lm")  # avoid "undefined reference to `log'" with -lm
            replace_in_file(
                self,
                os.path.join(self.source_folder, "setup.py"),
                "for lib_name in ('ffi', 'ffi_pic'):",
                "for lib_name in ('ffi_d', 'ffi_pic'):",
            )
        else:
            replace_in_file(self, configureFile, "-lsqlite3", "-lsqlite3 -lm")  # avoid "undefined reference to `log'" with -lm
        if is_msvc(self):
            cmake = CMake(self)
            cmake.configure(build_script_folder=os.path.join(self.source_folder, os.pardir))
            cmake.build()
        else:
            autotools = Autotools(self)
            autotools.configure()
            autotools.make()

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(self, "*.pdb", src=self.build_folder, dst=os.path.join(self.package_folder, "bin"), keep_path=False, excludes="*vc???.pdb")
        self._cmake_module_file_write()
        if is_msvc(self):
            cmake = CMake(self)
            cmake.install()

            if self.settings.build_type == "Debug":
                mevis_python = os.path.join(self.package_folder, "MeVisPython_d.exe")
                for name in ["python3_d", "python3", "python"]:
                    shutil.copy(src=mevis_python, dst=os.path.join(self.package_folder, f"{name}.exe"))

                mevis_python_w = os.path.join(self.package_folder, "MeVisPythonW_d.exe")
                for name in ["python3w_d", "python3w", "pythonw"]:
                    shutil.copy(src=mevis_python_w, dst=os.path.join(self.package_folder, f"{name}.exe"))
                v = Version(self.version)
                shutil.copy(
                    src=os.path.join(self.package_folder, "libs", f"python{v.major}{v.minor}_d.lib"),
                    dst=os.path.join(self.package_folder, "libs", f"python{v.major}{v.minor}.lib"),
                )
            else:
                mevis_python = os.path.join(self.package_folder, "MeVisPython.exe")
                for name in ["python3", "python"]:
                    shutil.copy(src=mevis_python, dst=os.path.join(self.package_folder, f"{name}.exe"))

                mevis_python_w = os.path.join(self.package_folder, "MeVisPythonW.exe")
                for name in ["python3w", "pythonw"]:
                    shutil.copy(src=mevis_python_w, dst=os.path.join(self.package_folder, f"{name}.exe"))

            # remove test directory
            rmdir(self, os.path.join(self.package_folder, "Lib", "test"))

        else:
            autotools = Autotools(self)
            autotools.make(target="install")  # instead of .install() to avoid setting DESTDIR
            rmdir(self, self.package_path / "share")
            rmdir(self, self.package_path / "lib" / "pkgconfig")

            mm_version = ".".join(self.version.split(".")[0:2])

            # remove test directory
            rmdir(self, self.package_path / "lib" / f"python{mm_version}" / "test")

            orig_python = f"./python{mm_version}"
            # FIXME python3 -> python3_d
            mevis_python = os.path.join(
                self.package_folder, "bin", "MeVisPython_d" if self.settings.build_type == "Debug" else "MeVisPython"
            )
            os.symlink(orig_python, mevis_python)

            if self.settings.os == "Macos":
                self.run(
                    f'install_name_tool -change libpython{mm_version}.dylib "@rpath/libpython{mm_version}.dylib" '
                    + os.path.join(self.package_folder, "bin", f"python{mm_version}")
                )
                self.run(
                    f'install_name_tool -add_rpath "@executable_path/../lib" '
                    + os.path.join(self.package_folder, "bin", f"python{mm_version}")
                )
            elif self.settings.os == "Linux":
                self.run("patchelf --set-rpath '$ORIGIN/../lib' " + os.path.join(self.package_folder, "bin", f"python{mm_version}"))
                dyn_modules = glob.glob(self.package_folder + "/**/lib-dynload/*.so", recursive=True)
                for so_file in dyn_modules:
                    # make the dynamically loaded modules work in an installed MeVisLab
                    self.run("patchelf --add-rpath '$ORIGIN/../../../../../lib' " + so_file)

        with chdir(self, self.package_folder):
            self.run(f"{mevis_python} -m ensurepip --verbose --altinstall", env="conanbuild")

        for pycache_path in (self.package_path / "lib").rglob("__pycache__"):
            rmdir(self, pycache_path)

        # fix bug in setuptools, see https://github.com/pypa/setuptools/issues/3591
        ccompiler = glob.glob(self.package_folder + "/**/site-packages/setuptools/_distutils/ccompiler.py", recursive=True)
        if ccompiler:
            replace_in_file(self, ccompiler[0], "include_dirs = self.include_dirs", "include_dirs = list(self.include_dirs)")
        else:
            print("Did not find 'ccompiler.py'")

        # Hack for a shortcoming of building pyproject.toml projects through pip install:
        # It is not possible to pass on a flag to build in debug mode, which let's the linker fail on Windows in Debug mode
        # (and man, I almost despaired when trying to work out how the compiler is called)
        # We take a shortcut and set the flag where it is needed through an environment variable.
        build_exts = glob.glob(self.package_folder + "/**/*distutils/command/build_ext.py", recursive=True)
        if build_exts:
            for build_ext in build_exts:
                replace_in_file(
                    self,
                    build_ext,
                    "self.debug = None",
                    "self.debug = bool(int(os.environ.get('SETUPTOOLS_BUILD_DEBUG'))) "
                    "if 'SETUPTOOLS_BUILD_DEBUG' in os.environ else None   # MeVis hack",
                )
        else:
            print("Did not find 'command/build_ext.py'")

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:python:python:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("base_purl", "github/python/cpython")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "Python3")
        self.cpp_info.set_property("cmake_target_name", "Python3::Python")
        self.cpp_info.set_property("cmake_target_aliases", ["Python3::Module"])
        self.cpp_info.set_property("cmake_build_modules", [self._cmake_module_file])
        self.cpp_info.set_property("pkg_config_name", "python")
        self.cpp_info.libs = collect_libs(self)
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.append("pthread")

        if self.settings.os == "Windows":
            self.cpp_info.defines.append("NT_THREADS")
        else:
            self.cpp_info.defines.append("_POSIX_THREADS")
            version = Version(self.version)
            self.cpp_info.includedirs = [f"include/python{version.major}.{version.minor}"]

        # MEVIS_PYTHON_CMD, the name of the mevislab python executable
        if self.settings.os == "Windows":
            self.cpp_info.libdirs = ["libs"]
            self.cpp_info.bindirs.append(self.package_folder)

            mevis_python = "MeVisPython_d.exe" if self.settings.build_type == "Debug" else "MeVisPython.exe"
        else:
            mevis_python = "MeVisPython_d" if self.settings.build_type == "Debug" else "MeVisPython"

        self.output.info("Creating MEVIS_PYTHON_CMD environment variable: %s" % mevis_python)
        self.buildenv_info.define("MEVIS_PYTHON_CMD", mevis_python)
        self.runenv_info.define("MEVIS_PYTHON_CMD", mevis_python)

        # PYTHONHOME
        self.output.info("Creating PYTHONHOME environment variable: %s" % self.package_folder)
        self.buildenv_info.define("PYTHONHOME", self.package_folder)
        self.runenv_info.define("PYTHONHOME", self.package_folder)

        # used by cmake's standard FindPython3.cmake
        self.output.info("Creating Python3_ROOT_DIR environment variable: %s" % self.package_folder)
        self.buildenv_info.define("Python3_ROOT_DIR", self.package_folder)
        self.runenv_info.define("Python3_ROOT_DIR", self.package_folder)

        # relative site-packages directory
        if self.settings.os == "Windows":
            sp = "Lib/site-packages"
        else:
            sp = f"lib/python{version.major}.{version.minor}/site-packages"

        self.output.info("Creating MEVIS_PYTHON_SITE_PACKAGES_FOLDER environment variable: %s" % sp)
        self.buildenv_info.define("MEVIS_PYTHON_SITE_PACKAGES_FOLDER", sp)
        self.runenv_info.define("MEVIS_PYTHON_SITE_PACKAGES_FOLDER", sp)

    @property
    def _cmake_module_file(self):
        return os.path.join("lib", "cmake", f"{self.name}-variables.cmake")

    def _cmake_module_file_write(self):
        v = Version(self.version)
        file = self.package_path / self._cmake_module_file
        content = textwrap.dedent(
            f"""\
            set(Python3_VERSION_VERSION {self.version})
            set(Python3_VERSION_MAJOR {v.major})
            set(Python3_VERSION_MINOR {v.minor})
            set(Python3_VERSION_PATCH {v.patch})
            set(Python3_VERSION_TWEAK 0)
            set(Python3_VERSION_COUNT 0)

            if(WIN32)
                set_property(TARGET Python3::Python PROPERTY INTERFACE_LINK_OPTIONS /STACK:3000000)
            endif()

            if(NumPy IN_LIST Python3_FIND_COMPONENTS)
                if(${{Python3_FIND_REQUIRED_NumPy}})
                    set(_numpy_find_package_Options ${{_numpy_find_package_Options}} REQUIRED)
                endif()
                if(${{Python3_FIND_QUIETLY}})
                    set(_numpy_find_package_Options ${{_numpy_find_package_Options}} QUIET)
                endif()
                find_package(numpy ${{_numpy_find_package_Options}})
            endif()
            """
        )
        save(self, file, content)
