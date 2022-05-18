# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import RunEnvironment
from conans import CMake
from conans import tools
from pathlib import Path

from conans.errors import ConanException

import shutil
import glob
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'
    generators = "cmake", "pkg_config"
    short_paths = True

    _cmake = None


    def system_requirements(self):
        installer = tools.SystemPackageTool()
        packages = []

        if tools.os_info.linux_distro in ["ubuntu", "debian"]:
            packages.append('libxt-dev')
            packages.append('pkg-config')

        if packages:
            installer.install_packages(packages)


    def requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)

        self.requires("boost/[>=1.74.0]" + channel)
        self.requires("glew/[>=2.2.0]" + channel)
        self.requires("libpng/[>=1.6.37]" + channel)
        self.requires("libxml2/[>=2.9.10]" + channel)
        self.requires("lz4/[>=1.9.2]" + channel)
        self.requires("python/[>=3.6.4]" + channel)
        self.requires("qt5/[>=5.12.9]" + channel)
        self.requires("tiff/[>=4.1.0]" + channel)
        self.requires("zlib/[>=1.2.11]" + channel)
        self.requires("libjpeg/9e" + channel)

        if not tools.os_info.is_linux:
            self.requires("freetype/[>=2.10.4]" + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self.create_cmake_wrapper()
            self._cmake = CMake(self)

            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d" if self.settings.build_type == "Debug" else ""
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.definitions["BUILD_TESTING"] = False

            py_major, py_minor, _ = self.deps_cpp_info["python"].version.split('.', 3)
            self._cmake.definitions["VTK_PYTHON_VERSION"] = f"{py_major}.{py_minor}"
            self._cmake.definitions["Python_ADDITIONAL_VERSIONS"] = f"{py_major}.{py_minor}"
            self._cmake.definitions["PythonInterp_ROOT"] = self.deps_cpp_info['python'].rootpath

            if tools.os_info.is_windows:
                self._cmake.definitions["PYTHON_LIBRARY"] = self.deps_cpp_info['python'].rootpath + f"/libs/python{py_major}{py_minor}" + ("_d.lib" if self.settings.build_type == "Debug" else ".lib")
                self._cmake.definitions["PYTHON_INCLUDE_DIR"] = self.deps_cpp_info['python'].rootpath + "/Include"
                self._cmake.definitions["VTK_INSTALL_PYTHON_MODULE_DIR"] = "Lib/site-packages"

            self._cmake.definitions["USE_COMPILER_HIDDEN_VISIBILITY"] = True

            self._cmake.definitions["VTK_USE_CXX11_FEATURES"] = True

            self._cmake.definitions["VTK_QT_VERSION"] = 5
            self._cmake.definitions["VTK_BUILD_QT_DESIGNER_PLUGIN"] = False

            self._cmake.definitions["VTK_DISPATCH_AOS_ARRAYS"] = True

            self._cmake.definitions["VTK_Group_Imaging"] = True
            self._cmake.definitions["VTK_Group_Qt"] = True
            self._cmake.definitions["VTK_Group_Rendering"] = True
            self._cmake.definitions["VTK_Group_StandAlone"] = True
            self._cmake.definitions["VTK_Group_Views"] = True

            self._cmake.definitions["VTK_REPORT_OPENGL_ERRORS"] = True
            self._cmake.definitions["VTK_USE_64BIT_IDS"] = True

            self._cmake.definitions["VTK_USE_QVTK"] = True
            self._cmake.definitions["VTK_USE_QVTK_QTOPENGL"] = True

            self._cmake.definitions["VTK_USE_RENDERING"] = True
            self._cmake.definitions["VTK_USE_PATENTED"] = False
            self._cmake.definitions["VTK_USE_PARALLEL"] = True
            self._cmake.definitions["VTK_USE_HYBRID"] = True
            self._cmake.definitions["VTK_USE_BOOST"] = True

            self._cmake.definitions["VTK_WRAP_PYTHON"] = True
            self._cmake.definitions["VTK_WRAP_JAVA"] = False
            self._cmake.definitions["VTK_WRAP_TCL"] = False
            self._cmake.definitions["VTK_USE_TK"] = False

            if tools.os_info.is_macos:
                self._cmake.definitions["VTK_USE_COCOA"] = True
                self._cmake.definitions["VTK_USE_X"] = False

                self._cmake.definitions["VTK_RENDERING_BACKEND"] = "OpenGL"
                self._cmake.definitions["Module_vtkIOExportOpenGL"] = True
            else:
                self._cmake.definitions["Module_vtkIOExportOpenGL2"] = True

            self._cmake.definitions["Module_vtkAddon"] = False
            self._cmake.definitions["Module_vtkDICOM"] = False
            self._cmake.definitions["Module_vtkFiltersReebGraph"] = True
            self._cmake.definitions["Module_vtkGUISupportQt"] = True
            self._cmake.definitions["Module_vtkGUISupportQtOpenGL"] = True
            self._cmake.definitions["Module_vtkGUISupportQtWebkit"] = False
            self._cmake.definitions["Module_vtkIOGeoJSON"] = True
            self._cmake.definitions["Module_vtkIOVPIC"] = True
            self._cmake.definitions["Module_vtkInfovisBoost"] = True
            self._cmake.definitions["Module_vtkInfovisBoostGraphAlgorithms"] = True
            self._cmake.definitions["Module_vtkParseOGLExt"] = True
            self._cmake.definitions["Module_vtkPython"] = True
            self._cmake.definitions["Module_vtkRenderingExternal"] = True
            self._cmake.definitions["Module_vtkRenderingQt"] = True
            self._cmake.definitions["Module_vtkRenderingSceneGraph"] = True
            self._cmake.definitions["Module_vtkVPIC"] = True
            self._cmake.definitions["Module_vtkViewsGeovis"] = True
            self._cmake.definitions["Module_vtkViewsQt"] = True
            self._cmake.definitions["Module_vtkWrappingTools"] = True

            self._cmake.definitions["ZLIB_USE_EXTERNAL"] = True
            self._cmake.definitions["VTK_USE_SYSTEM_JPEG"] = True
            self._cmake.definitions["VTK_USE_SYSTEM_PNG"] = True
            self._cmake.definitions["VTK_USE_SYSTEM_TIFF"] = True
            self._cmake.definitions["VTK_USE_SYSTEM_ZLIB"] = True
            self._cmake.definitions["VTK_USE_SYSTEM_LIBXML2"] = True
            self._cmake.definitions["VTK_USE_SYSTEM_FREETYPE"] = True
            self._cmake.definitions["VTK_USE_SYSTEM_GLEW"] = True

            self._cmake.definitions["VTK_USE_SYSTEM_EXPAT"] = False
            self._cmake.definitions["VTK_USE_SYSTEM_HDF5"] = False
            self._cmake.definitions["VTK_USE_SYSTEM_NETCDF"] = False
            self._cmake.definitions["VTK_USE_SYSTEM_DIY2"] = False
            self._cmake.definitions["VTK_USE_SYSTEM_GL2PS"] = False
            self._cmake.definitions["VTK_USE_SYSTEM_JSONCPP"] = False
            self._cmake.definitions["VTK_USE_SYSTEM_LIBPROJ4"] = False
            self._cmake.definitions["VTK_USE_SYSTEM_MPI4PY"] = False
            self._cmake.definitions["VTK_USE_SYSTEM_OGGTHEORA"] = False
            self._cmake.definitions["VTK_USE_SYSTEM_XDMF2"] = False
            self._cmake.definitions["VTK_USE_SYSTEM_XDMF3"] = False

            self._cmake.configure()
        return self._cmake


    def build(self):
        if tools.os_info.is_windows or tools.os_info.is_macos:
            for dependency in self.deps_cpp_info.deps:
                if dependency in ['python', 'openssl', 'sqlite3']:
                    imported_libs = os.listdir(self.deps_cpp_info[dependency].lib_paths[0])
                    for imported_lib in imported_libs:
                        if os.path.isfile(self.deps_cpp_info[dependency].lib_paths[0] + '/' + imported_lib):
                            shutil.copy(self.deps_cpp_info[dependency].lib_paths[0] + '/' + imported_lib, self.build_folder)


        with tools.environment_append(RunEnvironment(self).vars):
            cmake = self._configure_cmake()
            cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        # It is necessary that the Python debug dlls in windows have suffix _d
        if tools.os_info.is_windows and self.settings.build_type == 'Debug':
            with tools.chdir(self.package_folder + "/Lib/site-packages/vtk"):
                for entry in glob.glob('*.pyd'):
                    tools.rename(entry, entry[:-5]+'_d.pyd')

        # copy PDB's for dll and exe files
        for dll in glob.glob(self.package_folder + "/bin/*.dll"):
            self.copy(Path(dll).stem + ".pdb", src="bin", dst="bin")

        for exe in glob.glob(self.package_folder + "/bin/*.exe"):
            self.copy(Path(exe).stem + ".pdb", src="bin", dst="bin")

        tools.rmdir(os.path.join(self.package_folder, "cmake"))
        tools.rmdir(os.path.join(self.package_folder, "share"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "cmake"))

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.default_package_info()

        self.cpp_info.includedirs = ['include', 'include/vtk-7.1']
        self.cpp_info.defines = ['VTK_RENDERING_BACKEND_OPENGL' if tools.os_info.is_macos else 'VTK_RENDERING_BACKEND_OPENGL2']

        # Remove all libs not prefixed with 'vtk' and not containing 'PythonXY'
        py_major, py_minor, _ = self.deps_cpp_info["python"].version.split('.', 3)
        self.cpp_info.libs = list(filter(lambda x: f"Python{py_major}{py_minor}D" not in x, self.cpp_info.libs))
