import pathlib
import glob
import os
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.env import VirtualRunEnv
from conan.tools.files import collect_libs, copy, get, rmdir, chdir, rename, patch
from conan.tools.scm import Version

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "vtk"
    version = "9.7.1"
    homepage = "https://www.vtk.org"
    description = (
        "The Visualization Toolkit (VTK) is open source software for manipulating and displaying scientific data"
    )
    license = "MPL-2.0"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch", "CMakeLists.txt"

    mlab_hooks = {
        "dependencies.system_libs": [
            "libfreetype.so.6",
            "libXcursor.so.1",
            "libXfixes.so.3",
            "libXrender.so.1",
        ]
    }

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("boost/[>=1.74.0]")
        self.requires("eigen/[>=3.3.9]")
        self.requires("expat/[>=2.5.0]")
        self.requires("hdf5/[>=1.14.2]")
        self.requires("libjpeg-turbo/[>=2.1.0]")
        self.requires("libpng/[>=1.6.37]")
        self.requires("libxml2/[>=2.9.12]")
        self.requires("lz4/[>=1.9.3]")
        self.requires("nlohmann_json/[>=3.11.3]", transitive_headers=True)
        self.requires("python/[>=3.6.4]")
        self.requires("qtbase/[>=6.5]")
        self.requires("qtdeclarative/[>=6.5]")
        self.requires("sqlite3/[>=3.36.0]")
        self.requires("tiff/[>=4.3.0]")
        self.requires("xz-utils/[>=5.2.6]")
        self.requires("zlib/[>=1.2.12]")

        if self.settings.os != "Linux":
            self.requires("freetype/[>=2.10.4]")

    def source(self):
        major_minor = ".".join(str(self.version).split(".")[0:2])
        get(
            self,
            sha256="cae04fd355004cb916a409db79d53a208f1221e975aeacc7540ee67b148ee91a",
            url=f"https://www.vtk.org/files/release/{major_minor}/VTK-{self.version}.tar.gz",
            strip_root=True,
        )
        patch(
            self,
            patch_file="patches/001-vtk_msvc_bug_19533.patch",
            patch_type="compatibility",
            patch_description="workaround a msvc compile error, see https://gitlab.kitware.com/vtk/vtk/-/issues/19533",
        )
        patch(
            self,
            patch_file="patches/003-vtk_equal_op.patch",
            patch_type="compatibility",
            patch_description="fix equal operator for check existence of attributes",
        )
        patch(
            self,
            patch_file="patches/004-vtk_disable-hook.patch",
            patch_type="compatibility",
            patch_description="Disable VTKMetaHook while importing vtkmodules due to conflicting debug/release python.dll",
        )

    def generate(self):
        # run environment is needed to be able to run sqlite and other executables during build
        env = VirtualRunEnv(self)
        env.generate(scope="build")

        cd = CMakeDeps(self)
        cd.generate()

        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d" if self.settings.build_type == "Debug" else ""
        tc.variables["VTK_WINDOWS_PYTHON_DEBUGGABLE"] = self.settings.build_type == "Debug"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        tc.variables["BUILD_TESTING"] = False
        tc.variables["VTK_ENABLE_REMOTE_MODULES"] = False
        tc.variables["VTK_FORBID_DOWNLOADS"] = True
        tc.variables["VTK_USE_FUTURE_BOOL"] = True

        python_dependency = self.dependencies["python"]
        py_version = python_dependency.ref.version

        if self.settings.os == "Windows":
            build_suffix = "_d" if self.settings.build_type == "Debug" else ""
            tc.variables["PYTHON_LIBRARY"] = (
                python_dependency.cpp_info.libdirs[0].replace("\\", "/")
                + f"/python{py_version.major}{py_version.minor}{build_suffix}.lib"
            )
            tc.variables["PYTHON_INCLUDE_DIR"] = python_dependency.cpp_info.includedirs[0].replace("\\", "/")
            tc.variables["VTK_PYTHON_SITE_PACKAGES_SUFFIX"] = "Lib/site-packages"
            tc.variables["PYTHON_EXECUTABLE"] = (
                python_dependency.package_folder.replace("\\", "/") + f"/python3{build_suffix}.exe"
            )
        else:
            tc.variables["PYTHON_EXECUTABLE"] = python_dependency.package_folder + "/bin/python3"

        tc.variables["VTK_QT_VERSION"] = 6
        tc.variables["VTK_DISPATCH_AOS_ARRAYS"] = True

        tc.variables["VTK_GROUP_ENABLE_Imaging"] = "YES"
        tc.variables["VTK_GROUP_ENABLE_Qt"] = "YES"
        tc.variables["VTK_GROUP_ENABLE_Rendering"] = "YES"
        tc.variables["VTK_GROUP_ENABLE_StandAlone"] = "YES"
        tc.variables["VTK_GROUP_ENABLE_Views"] = "YES"

        tc.variables["VTK_WRAP_PYTHON"] = True
        tc.variables["VTK_WRAP_JAVA"] = False
        tc.variables["VTK_USE_TK"] = False

        tc.variables["VTK_MODULE_USE_EXTERNAL_VTK_eigen"] = True
        tc.variables["VTK_MODULE_USE_EXTERNAL_VTK_expat"] = True
        tc.variables["VTK_MODULE_USE_EXTERNAL_VTK_hdf5"] = True
        tc.variables["VTK_MODULE_USE_EXTERNAL_VTK_freetype"] = True
        tc.variables["VTK_MODULE_USE_EXTERNAL_VTK_libxml2"] = True
        tc.variables["VTK_MODULE_USE_EXTERNAL_VTK_lzma"] = True
        tc.variables["VTK_MODULE_USE_EXTERNAL_VTK_nlohmannjson"] = True
        tc.variables["VTK_MODULE_USE_EXTERNAL_VTK_jpeg"] = True
        tc.variables["VTK_MODULE_USE_EXTERNAL_VTK_png"] = True
        tc.variables["VTK_MODULE_USE_EXTERNAL_VTK_tiff"] = True
        tc.variables["VTK_MODULE_USE_EXTERNAL_VTK_sqlite"] = True
        tc.variables["VTK_MODULE_USE_EXTERNAL_VTK_lz4"] = True
        tc.variables["VTK_MODULE_USE_EXTERNAL_VTK_zlib"] = True

        tc.variables["VTK_MODULE_ENABLE_VTK_FiltersReebGraph"] = "YES"
        tc.variables["VTK_MODULE_ENABLE_VTK_GUISupportQt"] = "YES"
        tc.variables["VTK_MODULE_ENABLE_VTK_GUISupportQtQuick"] = "YES"
        tc.variables["VTK_MODULE_ENABLE_VTK_InfovisBoost"] = "YES"
        tc.variables["VTK_MODULE_ENABLE_VTK_InfovisBoostGraphAlgorithms"] = "YES"
        tc.variables["VTK_MODULE_ENABLE_VTK_IOGeoJSON"] = "YES"
        tc.variables["VTK_MODULE_ENABLE_VTK_IOVPIC"] = "YES"
        tc.variables["VTK_MODULE_ENABLE_VTK_IOIOSS"] = (
            "NO"  # only needed for tests, compiler error with msbuild 17.6/17.7
        )
        tc.variables["VTK_MODULE_ENABLE_VTK_Python"] = "YES"
        tc.variables["VTK_MODULE_ENABLE_VTK_RenderingExternal"] = "YES"
        tc.variables["VTK_MODULE_ENABLE_VTK_RenderingQt"] = "YES"
        tc.variables["VTK_MODULE_ENABLE_VTK_RenderingSceneGraph"] = "YES"
        tc.variables["VTK_MODULE_ENABLE_VTK_ViewsQt"] = "YES"
        tc.variables["VTK_MODULE_ENABLE_VTK_WrappingTools"] = "YES"
        tc.variables["HDF5_IS_PARALLEL"] = False
        # make sure libGL is preferred to libOpenGL
        tc.variables["OpenGL_GL_PREFERENCE"] = "LEGACY"

        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder=os.path.join(self.source_folder, ".."))
        cmake.build()

    def package(self):
        copy(self, "Copyright.txt", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        cmake = CMake(self)
        cmake.install()

        if self.settings.build_type == "Debug":
            # remove one "_d" too many: (FIXME!)
            if self.settings.os == "Windows":
                with chdir(self, os.path.join(self.package_folder, "Lib/site-packages/vtkmodules")):
                    for entry in glob.glob("*_d_d.pyd"):
                        rename(self, entry, entry[:-8] + "_d.pyd")
            if self.settings.os == "Linux":
                python_dependency = self.dependencies["python"]
                py_version = python_dependency.ref.version
                py_version_str = f"{py_version.major}.{py_version.minor}"
                with chdir(
                    self, os.path.join(self.package_folder, f"lib/python{py_version_str}/site-packages/vtkmodules")
                ):
                    for entry in glob.glob("*_d.so"):
                        rename(self, entry, entry[:-5] + ".so")

        if self.settings.os == "Windows":
            for dll in pathlib.Path(os.path.join(self.package_folder, "bin")).glob("*.dll"):
                copy(
                    self,
                    f"*/{dll.stem}.pdb",
                    src=self.build_folder,
                    dst=os.path.join(self.package_folder, "bin"),
                    keep_path=False,
                )
            for exe in pathlib.Path(os.path.join(self.package_folder, "bin")).glob("*.exe"):
                copy(
                    self,
                    f"*/{exe.stem}.pdb",
                    src=self.build_folder,
                    dst=os.path.join(self.package_folder, "bin"),
                    keep_path=False,
                )

        rmdir(self, os.path.join(self.package_folder, "cmake"))
        rmdir(self, os.path.join(self.package_folder, "share"))
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        for pycache_path in pathlib.Path(os.path.join(self.package_folder, "lib")).rglob("__pycache__"):
            rmdir(self, pycache_path)

    def package_info(self):
        self.cpp_info.set_property("cpe", f"cpe:2.3:a:vtk:vtk:{self.version}:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/Kitware/VTK@v{self.version}")  # Official mirror
        self.cpp_info.set_property("cmake_file_name", "VTK")
        self.cpp_info.set_property("cmake_target_name", "VTK::VTK")
        self.cpp_info.set_property("pkg_config_name", "VTK")

        v = Version(self.version)
        self.cpp_info.includedirs = ["include", f"include/vtk-{v.major}.{v.minor}"]
        self.cpp_info.defines.append(
            "VTK_RENDERING_BACKEND_OPENGL" if self.settings.os == "Macos" else "VTK_RENDERING_BACKEND_OPENGL2"
        )
        # Remove all libs not prefixed with 'vtk' and not containing 'PythonXY'
        py_version = self.dependencies["python"].ref.version
        python_filter = f"Python{py_version.major}{py_version.minor}D"
        self.cpp_info.libs = list(filter(lambda x: python_filter not in x, collect_libs(self)))
