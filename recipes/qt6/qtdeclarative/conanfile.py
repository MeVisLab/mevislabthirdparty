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
        "opengl": True,
        "sql": True,
        "widgets": True,
    }
