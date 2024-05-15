import io

from conan import ConanFile
from conan.tools.cmake import cmake_layout


class TestPackage(ConanFile):
    settings = "os", "arch", "compiler", "build_type"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires(self.tested_reference_str)

    def test(self):
        out = io.StringIO()
        exit_code = self.run("PythonQtGenerator --help", stdout=out, env="conanrun")
        assert exit_code == 0
        assert "generator [options] header-file typesystem-file" in out.getvalue()
