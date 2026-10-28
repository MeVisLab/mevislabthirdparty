import os

from conan import ConanFile
from conan.tools.env import Environment


class TestPackage(ConanFile):
    python_requires = "qt_package/1.0.0"
    python_requires_extend = "qt_package.QtTestPackage"

    def generate(self):
        super().generate()
        env = Environment()
        env.prepend_path("QT_PLUGIN_PATH", os.path.join(self.dependencies["qtwebview"].package_folder, "plugins"))
        for dependency in ("qtwebview", "qtwebengine", "qtdeclarative"):
            env.append_path("QML_IMPORT_PATH", os.path.join(self.dependencies[dependency].package_folder, "qml"))
        env.vars(self, scope="build").save_script("qtwebview_env")
