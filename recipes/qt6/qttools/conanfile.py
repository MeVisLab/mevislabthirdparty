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

    qt_feature = {
        "assistant": True,
        "commandlineparser": True,
        "designer": True,
        "distancefieldgenerator": True,
        "linguist": True,
        "pixeltool": True,
        "qtattributionsscanner": True,
        "qdbus": True,
        "qdoc": False, "clangcpp": False,  # these two belong together - Clang not available
        "qtdiag": True,
        "qtplugininfo": True,
        "thread": True
    }

    def requirements(self):
        super().requirements()
        self.requires(f"zstd/[>=1.5.0]")
