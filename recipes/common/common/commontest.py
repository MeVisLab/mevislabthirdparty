# -*- coding: utf-8 -*-

from conans import ConanFile
from conans import CMake
from conans import tools
from conans.errors import ConanException
import platform
import sys
import os


class CommonTest(object):
    settings = "os", "compiler", "arch", "build_type"
    generators = "cmake"
    default_user = "mevislab"
    default_channel = "stable"

    test_license = True
    test_command = os.path.join("bin", "test_package")
    test_allow_fail = False
    test_args = None
    test_with_environment = True


    def build(self):
        self.default_build()


    def default_build(self):
        if os.path.isfile(os.path.join(self.source_folder, 'CMakeLists.txt')):
            cmake = CMake(self)
            cmake.configure()
            cmake.build()
        else:
            self.output.info("skip build step, because no CMakeLists.txt was found")


    def imports(self):
        self.default_imports()


    def default_imports(self):
        self.copy("license*", dst="licenses", folder=True, keep_path=False, ignore_case=True)
        self.copy("metadata.json", dst="licenses", folder=True, keep_path=False, ignore_case=True)

        # import shared libraries
        self.copy("*.dll", dst="bin", src="bin")    # TODO fix all packages and remove this 2 line (dlls are libs)
        self.copy("*.lib", dst="bin", src="bin")

        self.copy("*.dll", dst="bin", src="lib")
        self.copy("*.lib", dst="bin", src="lib")

        self.copy("*.dylib*", dst="bin", src="lib")
        self.copy("*.so*", dst="bin", src="lib")


    def check_license(self):
        dirs = list(filter(lambda x: os.path.isdir(os.path.join("licenses", x)), os.listdir("licenses")))
        if not dirs:
            raise ConanException('No license information found')

        for dir in dirs:
            licence_found = os.path.isfile(os.path.join("licenses", dir, "LICENSE"))
            metadata_found = os.path.isfile(os.path.join("licenses", dir, "metadata.json"))
            if licence_found and metadata_found:
                self.output.success("LICENSE file and meta information found for package '%s'"  % dir)
            elif not self.test_license:
                self.output.info("LICENSE file check disabled")
                self.output.success("License meta information found for package '%s'"  % dir)
            else:
                raise ConanException("License information not found for package '%s'" % dir)


    def test(self):
        self.default_test()


    def default_test(self):
        self.check_license()

        if not self.test_command is None:
            cmd = self.test_command + (".exe" if self.settings.os == 'Windows' else '')
            if self.test_args is not None:
                if isinstance(self.test_args, str):
                    cmd += ' %s' % self.test_args
                elif all(isinstance(item, str) for item in self.test_args):
                    cmd += ' %s' % (' '.join(self.test_args))
                else:
                    raise ConanException("Invalid test_args")

            self.output.info("Executing '%s' (using run environment: %s)" % (cmd, "yes" if self.test_with_environment else "no"))
            try:
                self.run(cmd, run_environment=self.test_with_environment)
            except Exception as e:
                if self.test_allow_fail:
                    self.output.warn("Test program failed (but it was allowed to do): " + str(e))
                else:
                    self.output.error("Test program failed: " + str(e))
                    sys.exit(1)
