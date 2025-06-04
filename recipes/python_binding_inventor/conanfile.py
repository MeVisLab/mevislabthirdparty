from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout
from conan.tools.env import VirtualRunEnv
from conan.tools.files import copy, collect_libs

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "python_binding_inventor"
    version = "2024.12.27"
    homepage = "https://mevislab.de"
    description = "Python binding into Inventor"
    license = "LGPL-2.1-only"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "shared-library"
    exports_sources = "sources/*", "LICENSE"

    mlab_hooks = {
        "test_package.skip": True,
    }

    def requirements(self):
        self.requires("glew/[>=2.0.0]")
        self.requires("numpy/[>=1.17.5]")
        self.requires("openinventor/[>=2.5.1]")
        self.requires("qtbase/[>=6.5]")
        self.build_requires("pcre2/[>=10.34]")
        self.requires("python/[>=3.11]")
        self.requires("pythonqt/[>=3.4.2]")

    def layout(self):
        cmake_layout(self, src_folder="sources")

    def generate(self):
        env = VirtualRunEnv(self)
        env.generate(scope="build")

        tc = CMakeToolchain(self)
        version = self.dependencies['python'].ref.version

        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["python_VERSION_MAJOR"] = version.major
        tc.variables["python_VERSION_MINOR"] = version.minor
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../../../../lib/"
        tc.generate()
        cd = CMakeDeps(self)
        cd.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(self, "LICENSE", src=self.source_path.parent, dst=self.package_path / "licenses")

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "PythonBindingInventor")
        self.cpp_info.set_property("cmake_target_name", "PythonBindingInventor::PythonBindingInventor")
        self.cpp_info.set_property("cmake_config_version_compat", "AnyNewerVersion")
        self.cpp_info.set_property("pkg_config_name", "PythonBindingInventor")
        self.cpp_info.libs = collect_libs(self)
        self.cpp_info.includedirs.clear()
