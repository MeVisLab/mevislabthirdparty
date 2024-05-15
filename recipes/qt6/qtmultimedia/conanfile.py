from conan import ConanFile
from conan.tools.system import package_manager


required_conan_version = ">=2.2.2"

class ConanRecipe(ConanFile):
    python_requires = "qt_package/1.0.0"
    python_requires_extend = "qt_package.QtPackage"

    mlab_hooks = {
        'dependencies.system_libs': [
            'libasound.so.2',
            'libEGL.so.1',
            'libglib-2.0.so.0',
            'libgobject-2.0.so.0',
            'libgstallocators-1.0.so.0',
            'libgstapp-1.0.so.0',
            'libgstaudio-1.0.so.0',
            'libgstbase-1.0.so.0',
            'libgstgl-1.0.so.0',
            'libgstpbutils-1.0.so.0',
            'libgstphotography-1.0.so.0',
            'libgstreamer-1.0.so.0',
            'libgstvideo-1.0.so.0',
            'libgthread-2.0.so.0',
            'libxkbcommon.so.0',
        ]
    }

    qt_feature = {
        "alsa": False,
        "ffmpeg": False,
        "gstreamer": False,
        "linux_v4l": False,
        "pulseaudio": False,
        "vaapi": False
    }

    def configure(self):
        super().configure()
        if self.settings.os == 'Linux':
            self.qt_feature['alsa'] = True
            self.qt_feature['gstreamer'] = True
            self.qt_feature['linux_v4l'] = True

    def system_requirements(self):
        super().system_requirements()
        apt = package_manager.Apt(self)
        apt.install(["libgstreamer1.0-dev", "libgstreamer-plugins-base1.0-dev"], update=True)
