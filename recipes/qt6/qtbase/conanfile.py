import sys

from conan import ConanFile
from conan.tools.system import package_manager
from conan.tools.files import rmdir

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    python_requires = "qt_package/1.0.0"
    python_requires_extend = "qt_package.QtPackage"

    qt_feature = {
        "androiddeployqt": False,
        "gif": True,
        "ico": True,
        "jpeg": True,
        "png": True,
        "zstd": True,

        "accessibility": True,
        "concurrent": True,
        "printsupport": True,
        "sql": True,
        "testlib": True,
        "widgets": True,
        "xml": True,

        "sql_db2": False,
        "sql_ibase": False,
        "sql_mysql": False,
        "sql_oci": False,
        "sql_odbc": sys.platform == "win32",
        "sql_psql": True,
        "sql_sqlite": True,

        "system_doubleconversion": True,
        # "system_freetype": True,
        "system_harfbuzz": True,
        "system_jpeg": True,
        "system_libb2": False,
        "system_pcre2": True,
        "system_png": True,
        "system_proxies": True,
        "system_sqlite": True,
        "system_textmarkdownreader": True,
        "system_xcb_xinput": True,
        "system_zlib": True,
    }

    mlab_hooks = {
        'dependencies.system_libs': [
            'libxcb*.so.*',
            'libxkbcommon*.so.*',
            'libatk-1.0.so.0',
            'libcairo-gobject.so.2',
            'libcairo.so.2',
            'libcups.so.2',
            'libdbus-1.so.3',
            'libdrm.so.2',
            'libEGL.so.1',
            'libfontconfig.so.1',
            'libfreetype.so.6',
            'libgbm.so.1',
            'libgdk_pixbuf-2.0.so.0',
            'libgdk-3.so.0',
            'libgio-2.0.so.0',
            'libglib-2.0.so.0',
            'libgobject-2.0.so.0',
            'libgssapi_krb5.so.2',
            'libgthread-2.0.so.0',
            'libgtk-3.so.0',
            'libinput.so.10',
            'libmtdev.so.1',
            'libpango-1.0.so.0',
            'libpangocairo-1.0.so.0',
            'libresolv.so.2',
            'libudev.so.1',
            'libX11-xcb.so.1',
        ],
    }

    def system_requirements(self):
        apt = package_manager.Apt(self)
        apt.install(['libcups2-dev'], update=True)

    def requirements(self):
        super().requirements()
        # self.requires(f"assimp/[>=5.0.0]")
        self.requires("brotli/[>=1.0.9]")
        self.requires("double-conversion/[>=3.1.5]")
        if self.settings.os == 'Windows':
            self.requires("freetype/[>=2.13.0]")
            self.qt_feature['system_freetype'] = True
        self.requires("harfbuzz/[>=7.3.0]")
        self.requires("icu/[>=56.1]")
        self.requires("libjpeg-turbo/[>=2.1.0]")
        self.requires("libpng/[>=1.6.37]")
        self.requires("libpq/[>=14.0]")
        self.requires("libwebp/[>=1.1.0]")
        self.requires("libxslt/[>=1.1.3]")
        self.requires("md4c/[>=0.4.8]")
        if self.settings.os != 'Macos':
            self.requires("openssl/[>=3.0.9]")
        self.requires("pcre2/[>=10.34]")
        self.requires("re2/[>=20231101]")
        self.requires("sqlite3/[>=3.33.0]")
        self.requires("tiff/[>=4.1.0]")
        self.requires("zlib/[>=1.2.11]")
        self.requires("zstd/[>=1.5.0]")

    def package(self):
        super().package()
        if self.settings.os == "Windows":
            # In Qt6.6.1 we found a directory objects-Debug/Release in lib that clearly
            # doesn't belong there - seems to be a bug in the CMake files:
            rmdir(self, self.package_path / "lib" / f"objects-{self.settings.build_type}")
        