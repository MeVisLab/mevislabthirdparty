from conan import ConanFile


required_conan_version = ">=2.2.2"

class ConanRecipe(ConanFile):
    python_requires = "qt_package/1.0.0"
    python_requires_extend = "qt_package.QtPackage"

    mlab_hooks = {
        'dependencies.system_libs': [
            'libxkbcommon.so.0',
        ]
    }

    def requirements(self):
        super().requirements()
        self.requires(f"zlib/[>=1.2.11]")   # TODO stb: an attempt to fix the Windows build. But this is not the right solution!
