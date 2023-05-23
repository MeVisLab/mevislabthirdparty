# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import CMake
from conans import RunEnvironment
from conans import AutoToolsBuildEnvironment
from conans.errors import ConanException
import subprocess
import shutil
import os
import glob


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'
    generators = "cmake", "pkg_config"

    exports_sources = ["CMakeLists.txt", "cmake/*", "patches/*", "sources/*", "LICENSE"]

    _autotools = None
    _cmake = None


    def requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        self.requires("zlib/[>=1.2.11]" + channel)
        self.requires("sqlite3/[>=3.33.0]" + channel)
        self.requires("bzip2/[>=1.0.8]" + channel)
        self.requires("xz-utils/[>=5.2.5]" + channel)
        self.requires("libffi/[>=3.3]" + channel)
        self.requires("openssl/1.1.1t" + channel)


    def _unix_build(self):
        # copy dependencies
        deps = ['zlib'] if tools.os_info.is_linux else ['zlib', 'openssl', 'sqlite3', 'bzip2', 'xz-utils']
        for dependency in self.deps_cpp_info.deps:
            if dependency in deps:
                imported_libs = os.listdir(self.deps_cpp_info[dependency].lib_paths[0])

                for imported_lib in imported_libs:
                    if os.path.isfile(self.deps_cpp_info[dependency].lib_paths[0] + '/' + imported_lib):
                        shutil.copy(self.deps_cpp_info[dependency].lib_paths[0] + '/' + imported_lib, self.build_folder)
                        shutil.copy(self.deps_cpp_info[dependency].lib_paths[0] + '/' + imported_lib, self.build_folder)

        with tools.environment_append(RunEnvironment(self).vars):
            tk_headers = None
            if tools.os_info.is_macos:
                result = subprocess.run(['xcode-select', '-p'], stdout=subprocess.PIPE)
                tk_headers = os.path.join(result.stdout.decode(), "/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/Tk.framework/Versions/8.5/Headers")

            with tools.environment_append({'CFLAGS': f'-I{tk_headers}'}) if tk_headers else tools.no_op():
                args=[
                    '--enable-shared',
                    '--with-computed-gotos',
                    '--with-ensurepip=yes',
                ]
                self._autotools = AutoToolsBuildEnvironment(self, win_bash=tools.os_info.is_windows)
                # Do not add libs from dependencies, they are only used for Python extensions and detected in setup.py:
                self._autotools.libs = []
                self._autotools.configure(configure_dir='sources', args=args)
                self._autotools.make()


    def generate_symbol_export(self):
        version = ''.join(self.version.split('.')[0:2])
        sourceDef = self.source_folder + "/sources/PC/python3.def"
        targetDef = "python3.def"
        targetStubDef = "python3stub.def"

        lines = open(sourceDef,"r").readlines()
        stub = ["EXPORTS"]
        for l in lines:
            idx = l.find("=")
            if idx > 0:
                stub.append(l[:idx].strip())

        with open(targetStubDef,"w") as o:
            o.write("\n".join(stub))

        if self.settings.build_type == "Release":
            with open(targetDef,"w") as o:
                o.write("".join(lines))
        else:
            debugDef = []
            for l in lines:
                l = l.replace("\"python3\"","\"python3_d\"")
                l = l.replace("python%s" % version,"python%s_d" % version)
                debugDef.append(l)

            with open(targetDef,"w") as o:
                o.write("".join(debugDef))


    def _windows_build(self):
        self._cmake = CMake(self)
        self._cmake.definitions["PYTHON_VERSION"] = self.version
        self._cmake.definitions["BUILD_SHARED_LIBS"] = True
        self._cmake.configure()
        self._cmake.build()


    def build(self):
        if self.settings.build_type == "Debug":
            # Let setup.py look for the debug variant of the libraries
            tools.replace_in_file("sources/setup.py", "'z'", "'zd'")
            tools.replace_in_file("sources/setup.py", "'bz2'", "'bz2d'")
            tools.replace_in_file("sources/setup.py", "'lzma'", "'lzmad'")
            tools.replace_in_file("sources/setup.py", "'ffi'", "'ffid'")
            tools.replace_in_file("sources/setup.py", "libraries=[\"sqlite3\",]", "libraries=[\"sqlite3d\",]")
            tools.replace_in_file("sources/setup.py", "sqlite_dirs_to_check + self.lib_dirs, 'sqlite3')", "sqlite_dirs_to_check + self.lib_dirs, 'sqlite3d')")

        tools.replace_in_file("sources/setup.py", "        depends = ['_ctypes/ctypes.h']\n", f"        depends = ['_ctypes/ctypes.h']\n        extra_link_args.append(\"-L{self.deps_cpp_info['libffi'].rootpath}/lib\")")

        if self.settings.os == "Windows":
            self.generate_symbol_export()
            self._windows_build()
        else:
            self._unix_build()


    def package(self):
        if self._autotools:
            with tools.environment_append({
                "LD_LIBRARY_PATH": os.path.join(self.package_folder, "lib"),
                "DYLD_LIBRARY_PATH": os.path.join(self.package_folder, "lib")
            }):
                self._autotools.install()

            tools.rmdir(os.path.join(self.package_folder, "share"))
            tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))

            mm_version = '.'.join(self.version.split('.')[0:2])

            # remove test directory
            tools.rmdir(os.path.join(self.package_folder, "lib", f"python{mm_version}", "test"))

            if self.settings.build_type == "Debug":
                # FIXME python3 -> python3_d
                mevis_python = os.path.join(self.package_folder, "bin", "MeVisPython_d")
                os.symlink(f"python{mm_version}", mevis_python)
            else:
                mevis_python = os.path.join(self.package_folder, "bin", "MeVisPython")
                os.symlink(f"python{mm_version}", mevis_python)

            if tools.os_info.is_macos:
                install_name_tool = tools.which("install_name_tool")
                if not install_name_tool:
                    raise ConanException("install_name_tool could not be found")
                self.run(f'{install_name_tool} -change libpython{mm_version}.dylib "@rpath/libpython{mm_version}.dylib" ' + os.path.join(self.package_folder, 'bin', f'python{mm_version}'))
                self.run(f'{install_name_tool} -add_rpath "@executable_path/../lib" ' + os.path.join(self.package_folder, 'bin', f'python{mm_version}'))
            elif tools.os_info.is_linux:
                patchelf = tools.which("patchelf")
                if not patchelf:
                    raise ConanException("patchelf could not be found")
                self.run("%s --set-rpath '$ORIGIN/../lib' %s" % (patchelf, os.path.join(self.package_folder, 'bin', f'python{mm_version}')))
        else:
            self._cmake.install()

            self.copy("*.pdb", src="bin", dst="bin")

            if self.settings.build_type == "Debug":
                mevis_python = os.path.join(self.package_folder, "MeVisPython_d.exe")
                shutil.copyfile(mevis_python, os.path.join(self.package_folder, "python3_d.exe"))
                shutil.copyfile(mevis_python, os.path.join(self.package_folder, "python.exe"))
                shutil.copyfile(mevis_python, os.path.join(self.package_folder, "python3.exe"))

                mevis_python_w = os.path.join(self.package_folder, "MeVisPythonW_d.exe")
                shutil.copyfile(mevis_python_w, os.path.join(self.package_folder, "python3w_d.exe"))
                shutil.copyfile(mevis_python_w, os.path.join(self.package_folder, "python3w.exe"))
                shutil.copyfile(mevis_python_w, os.path.join(self.package_folder, "pythonw.exe"))
            else:
                mevis_python = os.path.join(self.package_folder, "MeVisPython.exe")
                shutil.copyfile(mevis_python, os.path.join(self.package_folder, "python3.exe"))
                shutil.copyfile(mevis_python, os.path.join(self.package_folder, "python.exe"))

                mevis_python_w = os.path.join(self.package_folder, "MeVisPythonW.exe")
                shutil.copyfile(mevis_python_w, os.path.join(self.package_folder, "python3w.exe"))
                shutil.copyfile(mevis_python_w, os.path.join(self.package_folder, "pythonw.exe"))

            # remove test directory
            tools.rmdir(os.path.join(self.package_folder, "Lib", "test"))

        with tools.chdir(self.package_folder):
            self.run("%s -m ensurepip --verbose --altinstall" % mevis_python, run_environment=True)

        self.patch_binaries()
        self.default_package()


        # Hack for a shortcoming of building pyproject.toml projects through pip install:
        # It is not possible to pass on a flag to build in debug mode, which let's the linker fail on Windows in Debug mode
        # (and man, I almost despaired when trying to work out how the compiler is called)
        # We take a shortcut and set the flag where it is needed through an environment variable.
        build_exts = glob.glob(self.package_folder + "/**/*distutils/command/build_ext.py",
                              recursive=True)
        if build_exts:
            for build_ext in build_exts:
                tools.replace_in_file(build_ext,
                                      "self.debug = None",
                                      "self.debug = bool(int(os.environ.get('SETUPTOOLS_BUILD_DEBUG'))) if 'SETUPTOOLS_BUILD_DEBUG' in os.environ else None   # MeVis hack")
        else:
            print("Did not find 'command/build_ext.py'")

    def package_info(self):
        self.default_package_info()

        version = tools.Version(self.version)
        self.cpp_info.includedirs = ['include', f'include/python{version.major}.{version.minor}']

        # MEVIS_PYTHON_CMD, the name of the mevislab python executable
        if tools.os_info.is_windows:
            self.cpp_info.libdirs = ['libs']
            self.env_info.PATH.append(self.package_folder)

            mevis_python = "MeVisPython_d.exe" if self.settings.build_type == "Debug" else "MeVisPython.exe"
        else:
            self.env_info.PATH.append(os.path.join(self.package_folder, 'bin'))
            mevis_python = "MeVisPython_d" if self.settings.build_type == "Debug" else "MeVisPython"

        self.output.info('Creating MEVIS_PYTHON_CMD environment variable: %s' % mevis_python)
        self.env_info.MEVIS_PYTHON_CMD = mevis_python

        # PYTHONHOME
        self.output.info('Creating PYTHONHOME environment variable: %s' % self.package_folder)
        self.env_info.PYTHONHOME = self.package_folder

        # used by cmake's standard FindPython3.cmake
        self.output.info('Creating Python3_ROOT_DIR environment variable: %s' % self.package_folder)
        self.env_info.Python3_ROOT_DIR = self.package_folder

        # relative site-packages directory
        if tools.os_info.is_windows:
            sp = "Lib/site-packages"
        else:
            sp = f"lib/python{version.major}.{version.minor}/site-packages"

        self.output.info('Creating MEVIS_PYTHON_SITE_PACKAGES_FOLDER environment variable: %s' % sp)
        self.env_info.MEVIS_PYTHON_SITE_PACKAGES_FOLDER = sp
