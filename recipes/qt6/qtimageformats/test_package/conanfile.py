import os
from conan import ConanFile
from conan.tools.env import Environment


class TestPackage(ConanFile):
    python_requires = "qt_package/1.0.0"
    python_requires_extend = "qt_package.QtTestPackage"

    def generate(self):
        self.python_requires["qt_package"].module.QtTestPackage.generate(self)
        env = Environment()
        env.prepend_path("QT_PLUGIN_PATH", os.path.join(self.dependencies["qtimageformats"].package_folder, "plugins"))
        env.vars(self, scope="build").save_script("qt_plugin_path")
