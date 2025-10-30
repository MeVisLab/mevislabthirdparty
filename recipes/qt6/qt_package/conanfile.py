import glob
import json
import os
from pathlib import Path
from conan import ConanFile
from conan.tools.build import check_min_cppstd, can_run
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.env import Environment, VirtualRunEnv
from conan.tools.files import load, save, copy, get, patch, rmdir

from conan.tools.gnu import PkgConfigDeps
from conan.tools.microsoft import is_msvc

required_conan_version = ">=2.2.2"


class QtTestPackage:
    settings = "os", "arch", "compiler", "build_type"

    def layout(self):
        cmake_layout(self)

    def package_id(self):
        self.info.python_requires.recipe_revision_mode()

    def system_requirements(self):
        pass

    def requirements(self):
        self.requires(self.tested_reference_str)

    def generate(self):
        env = VirtualRunEnv(self)
        env.generate(scope="build")
        tc = CMakeToolchain(self, generator="Ninja")
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self: ConanFile):
        if can_run(self):
            cmake = CMake(self)
            cmake.test()


class QtPackage:
    homepage = "https://www.qt.io"
    description = "cross-platform application development framework"
    license = "LGPL-3.0-only"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch"

    _qtdata = None
    qt_feature = None

    def init(self):
        data = load(self, os.path.join(self.python_requires["qt_package"].path, "qt.json"))
        self._qtdata = json.loads(data)

        self.name = f"{os.path.basename(self.recipe_folder)}"
        self.version = self._qtdata["version"]

    def package_id(self):
        self.info.python_requires.recipe_revision_mode()

    def validate(self):
        check_min_cppstd(self, "20")

    def configure(self):
        pass

    def layout(self):
        cmake_layout(self, src_folder="src")

    def system_requirements(self):
        pass

    def requirements(self):
        if self.name != "qtbase":
            self.requires(f"qtbase/{self.version}")

        for d in self._qtdata["modules"][self.name]["dependencies"]:
            if d != "qtbase":
                self.requires(f"{d}/{self.version}")

    def source(self: ConanFile):
        get(
            self,
            sha256=self._qtdata["modules"][self.name]["sha256"],
            url=self._qtdata["modules"][self.name]["url"],
            strip_root=True,
        )
        patchFolder = Path(self.export_sources_folder) / "patches"
        patches = patchFolder.glob("*.patch") if patchFolder.exists() else []
        for p in sorted(patches):
            self.output.info(f"Apply patch: {p}")
            patch(self, patch_file=p)
        if not patches:
            self.output.info("No patches found")

    def generate(self):
        env = VirtualRunEnv(self)
        env.generate(scope="build")

        env = Environment()
        env.prepend_path("PKG_CONFIG_PATH", self.generators_folder)
        env.vars(self).save_script("buildenv_pkg_config_path")

        tc = CMakeToolchain(self, generator="Ninja")
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["CMAKE_CXX_EXTENSIONS"] = True  # -std=c++NN instead of gnu++NN breaks <type_traits> on libstdc++

        tc.variables["BUILD_SHARED_LIBS"] = True

        tc.variables["OpenGL_GL_PREFERENCE"] = "LEGACY"

        tc.variables["FEATURE_separate_debug_info"] = self.settings.build_type == "Debug" and not is_msvc(self)
        tc.variables["FEATURE_cxx20"] = True
        tc.variables["FEATURE_c11"] = True

        tc.variables["QT_UNITY_BUILD"] = (
            False if self.settings.os == "Windows" else True
        )  # ~30% faster build (but build problems on windows with 6.8.0)
        tc.variables["QT_DISABLE_DEPRECATED_UP_TO"] = "0x051500"

        tc.variables["QT_BUILD_TESTS"] = False
        tc.variables["QT_BUILD_EXAMPLES"] = False
        tc.variables["QT_BUILD_BENCHMARKS"] = False
        tc.variables["QT_GENERATE_SBOM"] = False

        if self.qt_feature:
            for key, value in self.qt_feature.items():
                if isinstance(value, bool):
                    tc.variables[f"QT_FEATURE_{key}"] = "ON" if value else "OFF"
                else:
                    tc.variables[f"QT_FEATURE_{key}"] = str(value)

        if is_msvc(self):
            tc.cache_variables["CMAKE_INSTALL_LIBDIR"] = "lib"  # TODO stb: really needed?
            # TODO: needed until this is fixed: https://github.com/conan-io/conan/issues/12012
            tc.cache_variables["CMAKE_TRY_COMPILE_CONFIGURATION"] = str(self.settings.build_type)

        tc.generate()

        cd = CMakeDeps(self)
        cd.generate()

        for f in glob.glob("**/*.cmake", recursive=True):
            # like replace_in_file but without a warning
            content = load(self, f)
            if -1 == content.find(" IMPORTED)\n"):
                continue
            content = content.replace(" IMPORTED)\n", " IMPORTED GLOBAL)\n")
            save(self, f, content)

        pc = PkgConfigDeps(self)
        pc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(
            self,
            pattern="*.txt",
            src=os.path.join(self.source_folder, "LICENSES"),
            dst=os.path.join(self.package_folder, "licenses"),
        )
        if self.settings.os == "Windows":
            # In Qt6.6.1 we found a directory objects-Debug/Release in lib that clearly
            # doesn't belong there - seems to be a bug in the CMake files:
            rmdir(self, os.path.join(self.package_folder, "lib", f"objects-{self.settings.build_type}"))

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:qt:qt:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/qt/{self.name}@v{self.version}")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", f"Qt6{self.name}Dummy")
        self.cpp_info.set_property("cmake_target_name", f"Qt6{self.name}Dummy")
        self.cpp_info.libs.clear()
        self.cpp_info.builddirs.append(os.path.join("lib", "cmake"))
        self.buildenv_info.append_path("QT_ADDITIONAL_PACKAGES_PREFIX_PATH", self.package_folder)


class ConanRecipe(ConanFile):
    name = "qt_package"
    version = "1.0.0"
    url = "https://github.com/MeVisLab/mevislabthirdparty"
    license = "MIT"
    description = "Common recipes for Qt packages"
    settings = None
    exports = "qt.json"
    package_type = "python-require"
