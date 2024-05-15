from conan import ConanFile
from conan.tools.system import package_manager
from conan.errors import ConanInvalidConfiguration


required_conan_version = ">=2.2.2"

class ConanRecipe(ConanFile):
    python_requires = "qt_package/1.0.0"
    python_requires_extend = "qt_package.QtPackage"

    mlab_hooks = {
        'dependencies.system_libs': [
            'libdrm.so.2',
            'libEGL.so.1',
            'libwayland-client.so.0',
            'libwayland-cursor.so.0',
            'libwayland-egl.so.1',
            'libwayland-server.so.0',
            'libxkbcommon.so.0',
        ]
    }

    def configure(self):
        if self.settings.os != "Linux":
            raise ConanInvalidConfiguration(f"{self.name} is only supported on Linux")

    def validate(self):
        if self.settings.os != "Linux":
            raise ConanInvalidConfiguration(f"{self.name} is only supported on Linux")

    def system_requirements(self):
        super().system_requirements()
        apt = package_manager.Apt(self)
        apt.install(["libwayland-dev", "libwayland-client0", "libwayland-server0"], update=True)
