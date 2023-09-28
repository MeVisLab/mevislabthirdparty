# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conan.tools.scm import Git
import itertools
import shutil
import glob
import re
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    short_paths = True
    generators = "pkg_config"

    sanitizer = { 'cmake': False, 'binaries': False }

    _qt5_libmap = []


    def system_requirements(self):
        installer = tools.SystemPackageTool()
        packages = []

        if tools.os_info.linux_distro in ["ubuntu", "debian"]:
            packages.append('libxtst-dev')
            packages.append('libxrandr-dev')
            packages.append('libxkbcommon-x11-dev')
            packages.append('libxkbcommon-dev')
            packages.append('libxshmfence-dev')
            packages.append('libxkbfile-dev')
            packages.append('libxi-dev')
            packages.append('libxfixes-dev')
            packages.append('libxext-dev')
            packages.append('libxdamage-dev')
            packages.append('libxcursor-dev')
            packages.append('libxcomposite-dev')
            packages.append('libx11-xcb-dev')
            packages.append('libpci-dev')
            packages.append('libglu1-mesa-dev')
            packages.append('libglib2.0-dev')
            packages.append('libgl1-mesa-dev')
            packages.append('libegl1-mesa-dev')
            packages.append('libdrm-dev')
            packages.append('libdbus-1-dev')
            packages.append('libcups2-dev')
            packages.append('libatspi2.0-dev')
            packages.append('^libxcb.*-dev')
            packages.append('libfontconfig-dev')
            packages.append('libfreetype6-dev')
            packages.append('fontconfig')
            packages.append('python2')

        if packages:
            installer.install_packages(packages)


    def build_requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        if tools.os_info.is_windows:
            self.tool_requires("gperf_installer/[>=3.1]" + channel)
            self.tool_requires("jom_installer/[>=1.1.3]" + channel)
            self.tool_requires("python2_installer/[>=2.7.17]" + channel)
            self.tool_requires("strawberryperl_installer/[>=5.30]" + channel)
            self.tool_requires("winflexbison_installer/[>=2.5.18]" + channel)


    def requirements(self):
        # small helper method
        def _add_dependency(requirement, libdir_prefix=None, private=False, supported_os=None):
            if supported_os is None or str(self.settings.os) in supported_os:
                channel = "@{0}/{1}".format(self.user, self.channel)
                self.requires(requirement + ('' if '@' in requirement else channel), private=private)
                if libdir_prefix is not None:
                    self._qt5_libmap.append((requirement.split('/', 1)[0], libdir_prefix))

        _add_dependency("zlib/[>=1.2.11]", "ZLIB")
        _add_dependency("libjpeg/9e", "LIBJPEG")
        _add_dependency("tiff/[>=4.1.0]", "TIFF")
        _add_dependency("libpng/[>=1.6.37]", "LIBPNG")
        _add_dependency("webp/[>=1.1.0]", "WEBP")
        _add_dependency("pcre2/[>=10.34]", "PCRE2")
        #_add_dependency("re2/[>=2021.02.02]")
        _add_dependency("double-conversion/[>=3.1.5]", "DOUBLECONVERSION")
        _add_dependency("icu/[>=56.1]", "ICU")
        _add_dependency("sqlite3/[>=3.33.0]", "SQLITE")
        _add_dependency("assimp/[>=5.0.0]", "ASSIMP", private=True)
        _add_dependency("libpq/[>=10.4]", "PSQL")
        _add_dependency("libxslt/[>=1.1.3]")
        _add_dependency("libalsa/[>=1.1.9]", "ALSA", supported_os="Linux")

        # on macOS we want to use SecureTransport instead of OpenSSL
        _add_dependency("openssl/[>=3.0]", "OPENSSL", supported_os=["Linux", "Windows"])

        # AAT is supported only with -qt-harfbuzz on macOS
        #_add_dependency("harfbuzz/[>=2.6.5]", "HARFBUZZ", supported_os=["Linux", "Windows"])

        #TODO other possible requirements
        # jasper
        # harfbuzz
        # sdl2
        # odbc
        # opus
        # ffmpeg
        # libvpx
        # snappy
        # libevent
        # jsoncpp
        # protobuf
        # lcms2


    def source(self):
        self.default_source(apply_patches=False)

        # copy the relevant license file
        shutil.copy2("sources/LICENSE.LGPLv3", "sources/LICENSE")

        # remove GPL only modules
        for dir in [os.path.join('sources', d) for d in os.listdir('sources') if os.path.isdir(os.path.join('sources', d))]:
            if os.path.isfile(os.path.join(dir, 'LICENSE.LGPL3')):
                continue

            if os.path.isfile(os.path.join(dir, 'LICENSE.LGPLv3')):
                continue

            if os.path.isfile(os.path.join(dir, 'LICENSE.GPL3-EXCEPT')):
                continue

            self.output.warn(f"Removing GPL only module '{dir}'")
            shutil.rmtree(dir)

        # remove deprecated modules
        shutil.rmtree("sources/qtquickcontrols")
        shutil.rmtree("sources/qtscript")

        # remove some other modules we do not need/want
        shutil.rmtree("sources/qtpurchasing")      # only for iOS, Android and macOS
        shutil.rmtree("sources/qtsensors")         # only for iOS, Android and WinRT
        shutil.rmtree("sources/qtwayland")         # we do not support wayland yet
        shutil.rmtree("sources/qtandroidextras")   # we do not support Android yet

        # replace qtwebengine
        shutil.rmtree("sources/qtwebengine")
        git = Git(self, self.source_folder)
        clone_args = ['--recurse-submodules', '--depth', '1', '--branch', self.conan_data.get('sources').get(self.version)['qtwebengine']]
        git.clone("https://code.qt.io/qt/qtwebengine.git", "sources/qtwebengine", clone_args)

        # finally, apply all patches
        self.apply_patches()


    def build(self):
        tools.mkdir("build")

        # Qt creates tools that link to QtCore. To execute this
        # tools during build we have different options:
        # 1. set *LD_LIBRARY_PATH (works on Linux but does not work on Windows or macOS 10.11 with SIP)
        # 2. copying dll's / dylib's to the build directory (fortunately works on Windows and macOS)
        # 3. set rpath (dangerous)
        if tools.os_info.is_windows or tools.os_info.is_macos:
            # copy qtcore dependencies to build/qtbase/lib
            qtcore_deps = ['double-conversion', 'icu', 'pcre2', 'zlib', 'bzip2']
            for dependency in self.deps_cpp_info.deps:
                if dependency in qtcore_deps:
                    imported_libs = os.listdir(self.deps_cpp_info[dependency].lib_paths[0])

                    target_lib_dir = os.path.join(self.build_folder, "build", "qtbase", "lib")
                    if not os.path.exists(target_lib_dir):
                        os.makedirs(target_lib_dir)

                    target_bin_dir = os.path.join(self.build_folder, "build", "qtbase", "bin")
                    if not os.path.exists(target_bin_dir):
                        os.makedirs(target_bin_dir)

                    for imported_lib in imported_libs:
                        if os.path.isfile(self.deps_cpp_info[dependency].lib_paths[0] + '/' + imported_lib):
                            shutil.copy(self.deps_cpp_info[dependency].lib_paths[0] + '/' + imported_lib, target_lib_dir)
                            shutil.copy(self.deps_cpp_info[dependency].lib_paths[0] + '/' + imported_lib, target_bin_dir)

        # try to find a better and faster alternative to nmake on Windows
        windows = tools.os_info.is_windows
        make = tools.which("jom")
        if make is None:
            make = "nmake" if windows else "make"
            self.output.info("Using make tool: %s" % make)
        else:
            self.output.info("Using make tool: jom")

        with tools.vcvars(self.settings) if windows else tools.no_op():
            extra_env = { "PKG_CONFIG_PATH": os.getcwd() }

            cpucount = tools.cpu_count()
            self.output.info("Number of parallel make jobs set to: %d" % cpucount)
            extra_env["MAKEFLAGS"] = "j%d" % cpucount
            extra_env["MAKEOPTS"] = "j%d" % cpucount

            if not windows:
                extra_env["QMAKE_PYTHON2"] = tools.which("python2")

            if self.settings.compiler in ['gcc', 'clang']:
                i_path = []
                l_path = []
                for p in ['libalsa', 'zlib']:
                    if p in self.deps_cpp_info.deps:
                        i_path.extend(self._gather_include_paths(p))
                        l_path.extend(self._gather_lib_paths(p))
                extra_env['C_INCLUDE_PATH'] = os.pathsep.join(i_path)
                extra_env['CPLUS_INCLUDE_PATH'] = os.pathsep.join(i_path)
                extra_env['LIBRARY_PATH'] = os.pathsep.join(l_path)

            with tools.environment_append(extra_env) if extra_env else tools.no_op():
                with tools.chdir("build"):
                    self.run(os.path.join(self.source_folder, 'sources', 'configure') + (" %s" % (" ".join(self._qt5_configure_args()))))
                    ib = None #tools.which("BuildConsole") # FIXME
                    if ib:
                        self.run('BuildConsole /COMMAND="jom -j 200"', run_environment=True)
                        self.run("nmake install", run_environment=True)
                    else:
                        self.run(make, run_environment=True)
                        self.run("%s install" % make, run_environment=True)

        with open('build/qtbase/bin/qt.conf', 'w') as f:
            f.write('[Paths]\nPrefix = ..')


    def package(self):
        # FIXME: qmake just exit with 0, even when the configuration is invalid.
        #        Implement a check that we really have a build (look for so/dlls or so)
        self.copy(os.path.join("bin", "qt.conf"), src="build/qtbase")
        shutil.rmtree(os.path.join(self.package_folder, "doc"), ignore_errors=True)
        shutil.rmtree(os.path.join(self.package_folder, "lib", "pkgconfig"), ignore_errors=True)

        # QtWebEngine's CMake files search dependencies (QtCore etc.) in the same version as QtWebEngine itself.
        qtwebengine_hdr = tools.load(os.path.join(self.package_folder, "include", "QtWebEngineCore", "qtwebenginecoreversion.h"))
        qtwebengine_version = re.search('#define QTWEBENGINECORE_VERSION_STR "([0-9]\.[0-9]+\.[0-9]+)', qtwebengine_hdr).group(1)
        for module in ['Qt5WebEngineCore', 'Qt5WebEngineWidgets', 'Qt5WebEngine']:
            module_file = os.path.join(self.package_folder, "lib", "cmake", module, f"{module}Config.cmake")
            tools.replace_in_file(module_file, f"{qtwebengine_version} ${{_{module}_FIND_VERSION_EXACT}}", f"{self.version} ${{_{module}_FIND_VERSION_EXACT}}")

        # remove pkg-config la files
        laFileList = glob.glob(os.path.join(self.package_folder, "lib", "*.la"))
        for laFile in laFileList:
            os.remove(laFile)

        if tools.os_info.is_linux:
            # set rpath for .so files:
            self.patch_binaries()
            for p in self._all_libraries(folder='plugins'):
                file = os.path.join(p.parent, p.name)
                self.patch_elf_file_rpath(file, add_paths=["$ORIGIN/../.."])
        self.default_package(split_debug=False)


    def sanitize_package_adhere_license(self):
        pass


    def package_info(self):
        self.default_package_info()

        # Do not collect libraries. Otherwise, all dependent packages would
        # always link against the entire Qt.
        self.cpp_info.libs = []
        self.cpp_info.includedirs = ['include']
        self.env_info.PATH.append(os.path.join(self.package_folder, "bin"))


    def _qt5_configure_args(self):
        args = []
        args.append('-silent')
        args.append("-prefix %s" % self.package_folder)
        args.append('-shared')

        # precompiled headers cause errors on Windows and can cause problems on hardened Linux
        args.append('-no-pch')

        # link-time code generation is not working on Windows/Visual Studio 2019 > 16.3
        # error is: "fatal error C1001: Internal compiler error."
        # see: https://developercommunity.visualstudio.com/content/problem/859109/internal-compiler-error-when-building-qt-5126.html
        # TODO revisted and try again
        args.append('-no-ltcg')

        # force fontconfig on Linux
        if tools.os_info.is_linux:
            args.append('-fontconfig')

        # Older gold linker (<=2.31.0?) seems to have some problems with
        # optimizations done by newer gcc/clang versions. For example on CentOS.
        # Retry using the gold linker at some point! ;)
        #
        # See also https://bugreports.qt.io/browse/QTBUG-66571
        if self.settings.os == 'Linux':
            args.append("-no-use-gold-linker")

        # license stuff
        args.append('-confirm-license')
        args.append('-opensource')

        # Enable OpenGL
        args.append('-opengl desktop')

        # no need to forcefully build host tools in optimized mode,
        # just follow the overall debug/release build settings
        args.append('-no-optimized-tools')

        # Enforce accessibility to be enabled.
        # Disabling accessibility is not recommended by Qt, as
        # it will break QStyle and may break other internal parts of Qt.
        # Worse than that, many users could no longer use our software.
        args.append('-accessibility')

        # no need to build examples and test
        args.append('-nomake examples')
        args.append('-nomake tests')
        args.append('-no-compile-examples')

        # map the build type to the Qt configure option
        if self.settings.build_type == "Debug":
            args.append("-debug")
            args.append("-separate-debug-info")
        elif self.settings.build_type == "Release" or self.settings.build_type == "RelWithDebInfo":
            args.append("-release")
            args.append("-force-debug-info")
            args.append("-separate-debug-info")
        elif self.settings.build_type == "MinSizeRel":
            args.append("-release")
            args.append("-optimize-size")

        # use pkg-config to detect include and library paths
        if self.settings.os != 'Windows':
            args.append('-pkg-config')

        # use 'system' libraries here
        args.append('-system-zlib' if "zlib" in self.deps_cpp_info.deps else '-qt-zlib')
        args.append('-system-pcre' if "pcre2" in self.deps_cpp_info.deps else '-qt-pcre')
        args.append('-system-doubleconversion' if "double-conversion" in self.deps_cpp_info.deps else '-no-doubleconversion')
        args.append("-system-sqlite" if "sqlite3" in self.deps_cpp_info.deps else '-no-sqlite')
        args.append("-icu" if "icu" in self.deps_cpp_info.deps else '-no-icu')

        if tools.os_info.is_linux:
            args.append("-system-freetype")

        if self.settings.os == 'Macos':
            args.append("-qt-harfbuzz")
        else:
            args.append("-system-harfbuzz" if "harfbuzz" in self.deps_cpp_info.deps else "-no-harfbuzz")

        # image formats (also qtimageformats)
        args.append('-system-jasper' if 'jasper' in self.deps_cpp_info.deps else '-no-jasper')
        args.append('-system-mng' if 'mng' in self.deps_cpp_info.deps else '-no-mng')
        args.append('-system-webp' if 'webp' in self.deps_cpp_info.deps else '-no-webp')
        args.append('-system-tiff' if 'tiff' in self.deps_cpp_info.deps else '-no-tiff')
        args.append('-system-libjpeg' if 'libjpeg' in self.deps_cpp_info.deps else '-no-libjpeg')
        args.append('-system-libpng' if 'libpng' in self.deps_cpp_info.deps else '-no-libpng')
        args.append('-system-assimp' if 'assimp' in self.deps_cpp_info.deps else '-no-assimp')

        # use SecureTransport on macOS, otherwise use OpenSSL
        args.append("-securetransport" if self.settings.os == 'Macos' else "-openssl-runtime")

        # enable print support using CUPS
        args.append("-cups" if self.settings.os != 'Windows' else '-no-cups')

        if self.settings.os == 'Linux':
            args.append('-glib')                # enable glib event loop support on Linux (TODO add dependency)
            #args.append('-qt-xcb')
        else:
            args.append('-no-dbus')             # since dbus could be installed on macOS as well

        if self.settings.os == "Windows":
            args.append("-mp")                  # use multiple processors for compilation
            if tools.which("jom"):
                args.append("-make-tool jom")   # use jom on Windows

        if self.settings.os == "Macos":
            args.append("-no-framework")

        # disable everything that may lead to automagic deps
        args.append('-no-journald')
        args.append('-no-syslog')
        args.append('-no-libproxy')
        #args.append('-no-evdev')
        args.append('-no-tslib')
        args.append('-no-eglfs')
        args.append('-no-egl')
        args.append('-no-kms')
        args.append('-no-gbm')
        args.append('-no-iconv')
        args.append('-no-directfb')
        args.append('-no-linuxfb')
        args.append('-no-gtk')
        #args.append('-no-mirclient')
        args.append("-no-gstreamer")
        args.append("-no-pulseaudio")

        # disable all unwanted SQL drivers explicit
        args.append('-no-sql-db2')
        args.append('-no-sql-ibase')
        args.append('-no-sql-mysql')
        args.append('-no-sql-oci')
        args.append('-no-sql-sqlite2')
        args.append('-no-sql-tds')

        # enable wanted SQL drivers
        args.append('-sql-odbc' if ("odbc" in self.deps_cpp_info.deps) or tools.os_info.is_windows else '-no-sql-odbc')
        args.append('-sql-psql' if "libpq" in self.deps_cpp_info.deps else '-no-sql-psql')
        args.append('-sql-sqlite' if "sqlite3" in self.deps_cpp_info.deps else '-no-sql-sqlite')

        # qtquickcontrols2 styles
        args.append('-style-fusion')
        args.append('-style-imagine')
        args.append('-style-material')
        args.append('-style-universal')

        # qtwebengine
        if not tools.os_info.is_windows:
            #args.append('-feature-webengine-system-re2' if 're2' in self.deps_cpp_info.deps else '-no-feature-webengine-system-re2')
            args.append('-feature-webengine-system-icu' if 'icu' in self.deps_cpp_info.deps else '-no-feature-webengine-system-icu')
            args.append('-feature-webengine-system-libwebp' if 'webp' in self.deps_cpp_info.deps else '-no-feature-webengine-system-libwebp')
            args.append('-feature-webengine-system-opus' if 'opus' in self.deps_cpp_info.deps else '-no-feature-webengine-system-opus')
            args.append('-feature-webengine-system-ffmpeg' if 'ffmpeg' in self.deps_cpp_info.deps else '-no-feature-webengine-system-ffmpeg')
            args.append('-feature-webengine-system-libvpx' if 'libvpx' in self.deps_cpp_info.deps else '-no-feature-webengine-system-libvpx')
            args.append('-feature-webengine-system-snappy' if 'snappy' in self.deps_cpp_info.deps else '-no-feature-webengine-system-snappy')
            args.append('-feature-webengine-system-libevent' if 'libevent' in self.deps_cpp_info.deps else '-no-feature-webengine-system-libevent')
            #args.append('-feature-webengine-system-jsoncpp' if 'jsoncpp' in self.deps_cpp_info.deps else '-no-feature-webengine-system-jsoncpp')
            #args.append('-feature-webengine-system-protobuf' if 'protobuf' in self.deps_cpp_info.deps else '-no-feature-webengine-system-protobuf')
            args.append('-feature-webengine-system-libxml2' if 'libxml2' in self.deps_cpp_info.deps else '-no-feature-webengine-system-libxml2')
            args.append('-feature-webengine-system-lcms2' if 'lcms2' in self.deps_cpp_info.deps else '-no-feature-webengine-system-lcms2')
            args.append('-feature-webengine-system-png' if 'libpng' in self.deps_cpp_info.deps else '-no-feature-webengine-system-png')
            # chromium expects a jpeg-turbo compatible jpeg, so this doesn't work
            #args.append('-feature-webengine-system-jpeg' if 'libjpeg' in self.deps_cpp_info.deps else '-no-feature-webengine-system-jpeg')
            args.append('-no-feature-webengine-system-jpeg')

            args.append('-feature-webengine-system-harfbuzz' if 'harfbuzz' in self.deps_cpp_info.deps else '-no-feature-webengine-system-harfbuzz')

        if tools.os_info.is_linux:
            args.append('-feature-webengine-system-freetype')

        # TODO chromiums zlib/minizip isn't compatible so use the bundled one
        #args.append('-feature-webengine-system-zlib' if 'zlib' in self.deps_cpp_info.deps else '-no-feature-webengine-system-zlib')
        #args.append('-feature-webengine-system-minizip' if 'minizip' in self.deps_cpp_info.deps else '-no-feature-webengine-system-minizip')
        args.append('-no-feature-webengine-system-minizip')
        args.append('-no-feature-webengine-system-zlib')

        if self.settings.os == 'Linux':
            # always enable session management support. It doesn't need extra
            # dependencies at configure time and turing it off is dangerous.
            args.append('-sm')

        # typedef qreal to double explicit
        args.append('-qreal double')

        # respect system proxies by default
        args.append('-system-proxies')

        # do not build with -Werror
        args.append('-no-warnings-are-errors')

        # if tools.which("BuildConsole"):
        #     args.append('-incredibuild-xge')

        args.extend(self._qt5_modules())      # Qt modules setup
        args.extend(self._qt5_lib_args())     # add INCDIR and LIBDIR for the default dependencies
        args.extend(self._qt5_platform())     # add host platform argument
        args.extend(self._qt5_compiler_env()) # add compiler environment variables

        return args


    def _qt5_modules(self):
        args = []

        # explicit enable
        args.append('-gui')
        args.append('-widgets')

        # skip deprecated modules
        args.append("-skip qtquickcontrols")
        args.append("-skip qtscript")

        # skip GPL only modules
        args.append("-skip qtcharts")
        args.append("-skip qtdatavis3d")
        args.append("-skip qtnetworkauth")
        args.append("-skip qtvirtualkeyboard")
        args.append("-skip qtwebglplugin")
        args.append("-no-build-qtpdf")      # QtPDF is part of the QtWebEngine module but not LGPL

        # skip some other modules we do not need/want
        args.append("-skip qtdoc")           # do not build the Qt Reference Documentation
        args.append("-skip qtpurchasing")    # only for iOS, Android and macOS
        args.append("-skip qtsensors")       # only for iOS, Android and WinRT
        args.append("-skip qtwayland")       # we do not support wayland yet
        args.append("-skip qtandroidextras") # we do not support Android yet


        return args


    def _qt5_platform(self):
        def _gather_platform():
            if self.settings.os == "Linux":
                if self.settings.compiler == "gcc":
                    return {"x86": "linux-g++-32",
                            "armv6": "linux-arm-gnueabi-g++",
                            "armv7": "linux-arm-gnueabi-g++",
                            "armv7hf": "linux-arm-gnueabi-g++",
                            "armv8": "linux-aarch64-gnu-g++"}.get(str(self.settings.arch), "linux-g++")
                elif self.settings.compiler == "clang":
                    if self.settings.arch == "x86":
                        return "linux-clang-libc++-32" if self.settings.compiler.libcxx == "libc++" else "linux-clang-32"
                    elif self.settings.arch == "x86_64":
                        return "linux-clang-libc++" if self.settings.compiler.libcxx == "libc++" else "linux-clang"
            elif self.settings.os == "Macos":
                return "macx-clang"
            elif self.settings.os == "Windows":
                return "win32-msvc"
            return None

        platform_val = _gather_platform()
        if platform_val:
            return ["-platform %s" % platform_val]

        self.output.warn("host not supported: %s %s %s %s" % (self.settings.os, self.settings.compiler, self.settings.compiler.version, self.settings.arch))
        return []


    def _qt5_lib_args(self):
        args = []
        for package, var in self._qt5_libmap:
            if package in self.deps_cpp_info.deps:
                if self.deps_cpp_info[package].include_paths:
                    args.append("\"%s_INCDIR=%s\"" % (var, self.deps_cpp_info[package].include_paths[-1]))
                for lib_path in self.deps_cpp_info[package].lib_paths:
                    args.append("\"%s_LIBDIR=%s\"" % (var, lib_path))
                    break
                args += ["-D " + s for s in self.deps_cpp_info[package].defines]
                args.append("\"%s_LIBS=%s\"" % (var, " ".join(self._gather_libs(package))))
        return args


    def _qt5_compiler_env(self):
        args = []
        def _getenvpath(var):
            val = os.getenv(var)
            if val and tools.os_info.is_windows:
                val = val.replace("\\", "/")
                os.environ[var] = val
            return val

        value = _getenvpath('CC')
        if value:
            args += ['QMAKE_CC="' + value + '"', 'QMAKE_LINK_C="' + value + '"', 'QMAKE_LINK_C_SHLIB="' + value + '"']

        value = _getenvpath('CXX')
        if value:
            args += ['QMAKE_CXX="' + value + '"', 'QMAKE_LINK="' + value + '"', 'QMAKE_LINK_SHLIB="' + value + '"']

        if tools.os_info.is_linux and self.settings.compiler == "clang":
            # Set the limit for recursively nested template instantiations to
            # the recommended minimum limit of 1024. Some (older) linux
            # distributions have smaller limits than that by default.
            args += ['QMAKE_CXXFLAGS+="-ftemplate-depth=1024"']

        if tools.os_info.is_macos and self.settings.arch == "armv8":
            args.append('QMAKE_APPLE_DEVICE_ARCHS="arm64"')

        return args


    @staticmethod
    def _remove_duplicate(l):
        seen = set()
        seen_add = seen.add
        for element in itertools.filterfalse(seen.__contains__, l):
            seen_add(element)
            yield element


    def _gather_libs(self, p):
        libs = ["-l" + i for i in self.deps_cpp_info[p].libs + self.deps_cpp_info[p].system_libs]
        if tools.is_apple_os(self.settings.os):
            libs += ["-framework " + i for i in self.deps_cpp_info[p].frameworks]
        libs += self.deps_cpp_info[p].sharedlinkflags
        for dep in self.deps_cpp_info[p].public_deps:
            libs += ["-L" + lpath for lpath in self.deps_cpp_info[dep].lib_paths]
            libs += self._gather_libs(dep)
        return self._remove_duplicate(libs)


    def _gather_lib_paths(self, p):
        lib_paths = self.deps_cpp_info[p].lib_paths
        for dep in self.deps_cpp_info[p].public_deps:
            lib_paths += self._gather_lib_paths(dep)
        return self._remove_duplicate(lib_paths)


    def _gather_include_paths(self, p):
        include_paths = self.deps_cpp_info[p].include_paths
        for dep in self.deps_cpp_info[p].public_deps:
            include_paths += self._gather_include_paths(dep)
        return self._remove_duplicate(include_paths)
