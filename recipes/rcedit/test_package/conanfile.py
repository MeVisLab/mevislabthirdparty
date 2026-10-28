from conan import ConanFile
from conan.tools.build import can_run
import os, shutil


class TestPackage(ConanFile):
    settings = "os", "arch", "compiler", "build_type"
    test_type = "explicit"

    def build_requirements(self):
        self.tool_requires(self.tested_reference_str)

    def test(self):
        if can_run(self):
            exe_path = os.path.join(self.recipe_folder, "MeVisLabApp.exe")
            exe_copy_path = os.path.join(self.recipe_folder, "MeVisLabAppCopy.exe")
            shutil.copy(exe_path, exe_copy_path)
            self.run(
                f"rcedit.exe {exe_copy_path} --set-version-string ProductName My_Product --set-version-string CompanyName My_Company"
            )
