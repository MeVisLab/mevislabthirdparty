from conan import ConanFile
from conan.tools.system import package_manager


required_conan_version = ">=2.2.2"

class ConanRecipe(ConanFile):
    python_requires = "qt_package/1.0.0"
    python_requires_extend = "qt_package.QtPackage"

    mlab_hooks = {
        'package_size.skip': True,
        'dependencies.system_libs': [
            'libasound.so.2',           # alsa-lib
            'libdbus-1.so.3',           # dbus
            'libdrm.so.2',              # libdrm
            'libexpat.so.1',            # expat (FIXME MLAB-2790)
            'libfontconfig.so.1',       # fontconfig
            'libfreetype.so.6',         # freetype
            'libgbm.so.1',              # mesa
            'libnspr4.so',              # nspr
            'libnss3.so',               # nss
            'libnssutil3.so',           # nss
            'libplc4.so',               # nspr
            'libplds4.so',              # nspr
            'libresolv.so.2',           # glibc
            'libsmime3.so',             # nss
            'libxcb-dri3.so.0',         # libxcb
            'libxcb.so.1',              # libxcb
            'libXcomposite.so.1',
            'libXdamage.so.1',
            'libXfixes.so.3',
            'libXi.so.6',
            'libxkbcommon.so.0',
            'libxkbfile.so.1',
            'libXrandr.so.2',
            'libXrender.so.1',
            'libxshmfence.so.1',
            'libXtst.so.6',
            "libudev.so.1",
        ]
    }
    qt_feature = {
        "qtpdf_build": False,
        "qtpdf_quick_build": False,
        "qtpdf_widgets_build": False,
        "qtwebengine_build": True,
        "qtwebengine_quick_build": True,
        "qtwebengine_widgets_build": True,
        "ssl": True,
        "static": False,
        "system_zlib": True,
        "system_png": True,
        "system_jpeg": True,
        "system_freetype": True,
        "system_harfbuzz": True,
        "webengine_embedded_build": False,
        "webengine_extensions": True,
        "webengine_geolocation": False,
        "webengine_jumbo_build": True,
        "webengine_kerberos": False,
        "webengine_native_spellchecker": False,
        "webengine_ozone_x11": False,
        "webengine_pepper_plugins": True,
        "webengine_proprietary_codecs": False,
        "webengine_printing_and_pdf": True,
        "webengine_sanitizer": True,
        "webengine_spellchecker": True,
        "webengine_webchannel": True,
        "webengine_webrtc": True,                   # TODO MLAB-2790
        "webengine_webrtc_pipewire": False,
        "webengine_system_alsa": False,
        "webengine_system_ffmpeg": False,
        "webengine_system_icu": False,              # TODO MLAB-2790
        "webengine_system_lcms2": False,            # TODO MLAB-2790
        "webengine_system_libevent": False,
        "webengine_system_libopenjpeg2": False,     # TODO MLAB-2790
        "webengine_system_libpci": False,
        "webengine_system_libpng": True,
        "webengine_system_libtiff": False,          # TODO MLAB-2790
        "webengine_system_libwebp": True,
        "webengine_system_opus": False,             # TODO MLAB-2790
        "webengine_system_pulseaudio": False,
        "webengine_system_re2": False,              # TODO MLAB-2790
        "webengine_system_zlib": False,             # TODO MLAB-2790
    }

    def configure(self):
        super().configure()
        if self.settings.os == 'Linux':
            self.qt_feature["webengine_ozone_x11"] = True
            self.qt_feature["webengine_system_alsa"] = True

    def system_requirements(self):
        apt = package_manager.Apt(self)
        apt.install(['libcups2-dev', 'libudev-dev', 'libgbm-dev', 'libxshmfence-dev'], update=True)

    def requirements(self):
        super().requirements()
        self.requires("brotli/[>=1.0.9]")
        # self.requires("harfbuzz/[>=1.2.11]")  # TODO MLAB-2790
        # self.requires("icu/[>=56.1]")         # TODO MLAB-2790
        self.requires("libpng/[>=1.6.37]")
        self.requires("libwebp/[>=1.1.0]")
        self.requires("libxml2/[>=2.11.4]")
        self.requires("libxslt/[>=1.1.38]")
        # self.requires("minizip/[>=1.2.11]")   # TODO MLAB-2790
        # self.requires("re2/[>=20231101]")     # TODO MLAB-2790
        # self.requires("snappy/[>=1.1.10]")    # TODO MLAB-2790
        # self.requires("zlib/[>=1.2.11]")      # TODO MLAB-2790
