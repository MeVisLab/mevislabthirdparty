import os

from conan import ConanFile
from conan.tools.env import Environment


class TestPackage(ConanFile):
    python_requires = "qt_package/1.0.0"
    python_requires_extend = "qt_package.QtTestPackage"

    def generate(self):
        super().generate()
        package_folder = self.dependencies["qtwebengine"].package_folder
        process_name = "QtWebEngineProcess_d" if self.settings.build_type == "Debug" else "QtWebEngineProcess"
        if self.settings.os == "Windows":
            process_path = os.path.join(package_folder, "bin", f"{process_name}.exe")
        else:
            process_path = os.path.join(package_folder, "libexec", process_name)
        env = Environment()
        env.define_path("QTWEBENGINEPROCESS_PATH", process_path)
        env.define_path("QTWEBENGINE_RESOURCES_PATH", os.path.join(package_folder, "resources"))
        env.define_path("QTWEBENGINE_LOCALES_PATH", os.path.join(package_folder, "translations", "qtwebengine_locales"))
        env.vars(self, scope="build").save_script("qtwebengine_env")

    def test(self):
        if self.settings.os != "Windows":
            super().test()
