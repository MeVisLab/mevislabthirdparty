import re
import textwrap

from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, CMakeDeps, cmake_layout
from conan.tools.env import VirtualRunEnv, Environment
from conan.tools.files import get, rmdir, rm, replace_in_file, copy, collect_libs, save
from conan.tools.microsoft import is_msvc
from conan.tools.system import package_manager

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "opencv"
    version = "4.10.0"
    homepage = "https://opencv.org"
    description = "OpenCV is an open source computer vision and machine learning software library"
    license = "Apache-2.0"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"

    mlab_hooks = {
        "dependencies.system_libs": [
            "libgobject-2.0.so.0",
            "libgstreamer-1.0.so.0",
            "libgstaudio-1.0.so.0",
            "libgstapp-1.0.so.0",
            "libgstriff-1.0.so.0",
            "libgstvideo-1.0.so.0",
            "libgstbase-1.0.so.0",
            "libgstpbutils-1.0.so.0",
            "libglib-2.0.so.0",
        ]
    }

    def system_requirements(self):
        apt = package_manager.Apt(self)
        apt.install(["libgstreamer1.0-dev", "libgstreamer-plugins-base1.0-dev"], update=True)

    def requirements(self):
        self.requires("zlib/[>=1.2.11]")
        self.requires("eigen/[>=3.3.8]")
        self.requires("libpng/[>=1.6.37]")
        self.requires("tiff/[>=4.0.9]")
        self.requires("libwebp/[>=1.1.0]")
        self.requires("numpy/[>=1.17.5]")
        self.requires("protobuf/[>=21.9]", visible=False)
        # self.requires("openexr/[>=2.5.3]")
        # self.requires("openjpeg/[>=2.4.0]")
        self.requires("python/[>=3.9.7]")
        self.requires("qtbase/[>=6.5]")
        self.requires("libjpeg-turbo/[>=2.1.5]")
        # self.build_requires("pcre2/[>=10.34]")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="b2171af5be6b26f7a06b1229948bbb2bdaa74fcf5cd097e0af6378fce50a6eb9",
            url=f"https://github.com/opencv/opencv/archive/{self.version}.tar.gz",
            strip_root=True,
        )

        [rmdir(self, d) for d in (self.source_path / "3rdparty").iterdir() if d.is_dir() and d.name != "flatbuffers"]

        replace_in_file(
            self, self.source_path / "CMakeLists.txt", 'if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")', "if(false)"
        )

        save(
            self,
            self.source_path / "cmake" / "OpenCVFindWebP.cmake",
            textwrap.dedent(
                """
            find_package(WebP CONFIG REQUIRED)
            set(WEBP_FOUND TRUE)
            set(WEBP_INCLUDE_DIR ${WebP_INCLUDE_DIR})
            set(WEBP_INCLUDE_DIRS ${WebP_INCLUDE_DIRS})
            set(WEBP_LIBRARIES ${WebP_LIBRARIES})
            set(WEBP_LIBRARY ${WebP_LIBRARIES})
            include(FindPackageHandleStandardArgs)
            find_package_handle_standard_args(WebP DEFAULT_MSG WEBP_LIBRARY WEBP_LIBRARIES WEBP_INCLUDE_DIR WEBP_INCLUDE_DIRS)
        """
            ),
        )

        replace_in_file(
            self,
            self.source_path / "cmake" / "OpenCVDetectOpenCL.cmake",
            'ocv_install_3rdparty_licenses(opencl-headers "${OpenCV_SOURCE_DIR}' '/3rdparty/include/opencl/LICENSE.txt")',
            "",
        )
        replace_in_file(
            self,
            self.source_path / "cmake" / "OpenCVInstallLayout.cmake",
            'ocv_update(OPENCV_INSTALL_BINARIES_PREFIX "${OpenCV_ARCH}/${OpenCV_RUNTIME}/")',
            'ocv_update(OPENCV_INSTALL_BINARIES_PREFIX "")',
        )
        replace_in_file(
            self,
            self.source_path / "cmake" / "OpenCVInstallLayout.cmake",
            "set(CMAKE_INSTALL_RPATH_USE_LINK_PATH",
            "#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH",
        )

        # It is necessary to remove the global configured Debug postfix for the Python binding library,
        # otherwise there would be two postfixes
        replace_in_file(self, self.source_path / "modules" / "python" / "common.cmake", 'PREFIX ""', 'PREFIX "" DEBUG_POSTFIX ""')

        # Without this patch, the debug Python binding library would not be installed
        replace_in_file(
            self,
            self.source_path / "modules" / "python" / "common.cmake",
            "set(PYTHON_INSTALL_CONFIGURATIONS CONFIGURATIONS Release)",
            'set(PYTHON_INSTALL_CONFIGURATIONS "")',
        )

        # allow to find conan-supplied OpenEXR
        find_openexr = self.source_path / "cmake" / "OpenCVFindOpenEXR.cmake"
        replace_in_file(self, find_openexr, r'SET(OPENEXR_ROOT "C:/Deploy" CACHE STRING "Path to the OpenEXR \"Deploy\" folder")', "")
        replace_in_file(self, find_openexr, "SET(OPENEXR_LIBSEARCH_SUFFIXES x64/Release x64 x64/Debug)", "")
        replace_in_file(self, find_openexr, "SET(OPENEXR_LIBSEARCH_SUFFIXES Win32/Release Win32 Win32/Debug)", "")

    def generate(self):
        env = VirtualRunEnv(self)
        env.generate(scope="build")

        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        tc.variables["OpenGL_GL_PREFERENCE"] = "LEGACY"

        tc.variables["OPENCV_ENABLE_NONFREE"] = False
        tc.variables["OPENCV_FORCE_3RDPARTY_BUILD"] = False

        tc.variables["INSTALL_TO_MANGLED_PATHS"] = False
        tc.variables["INSTALL_TESTS"] = False
        tc.variables["INSTALL_C_EXAMPLES"] = False
        tc.variables["INSTALL_PYTHON_EXAMPLES"] = False

        tc.variables["ENABLE_PROFILING"] = False
        tc.variables["ENABLE_COVERAGE"] = False

        tc.variables["BUILD_EXAMPLES"] = False
        tc.variables["BUILD_DOCS"] = False
        tc.variables["BUILD_TESTS"] = False
        tc.variables["BUILD_PACKAGE"] = False
        tc.variables["BUILD_PERF_TESTS"] = False

        if is_msvc(self):
            tc.variables["BUILD_WITH_STATIC_CRT"] = "MT" in str(self.settings.compiler.runtime)

        # disable builds for all 3rd-party components, use conan libraries only
        tc.variables["BUILD_ZLIB"] = False
        tc.variables["BUILD_TIFF"] = False
        tc.variables["BUILD_OPENJPEG"] = False
        tc.variables["BUILD_JASPER"] = False
        tc.variables["BUILD_JPEG"] = False
        tc.variables["BUILD_PNG"] = False
        tc.variables["BUILD_OPENEXR"] = False
        tc.variables["BUILD_WEBP"] = False
        tc.variables["BUILD_TBB"] = False
        tc.variables["BUILD_IPP_IW"] = False
        tc.variables["BUILD_ITT"] = False
        tc.variables["BUILD_JPEG_TURBO_DISABLE"] = True
        tc.variables["BUILD_PROTOBUF"] = False

        tc.variables["BUILD_opencv_apps"] = False
        tc.variables["BUILD_opencv_java"] = False
        tc.variables["BUILD_opencv_python"] = False
        tc.variables["BUILD_opencv_python2"] = False
        tc.variables["BUILD_opencv_python3"] = True
        tc.variables["BUILD_opencv_python_bindings_generator"] = True
        tc.variables["BUILD_opencv_js"] = False
        tc.variables["BUILD_opencv_java_bindings_generator"] = False

        tc.variables["WITH_1394"] = False
        tc.variables["WITH_ANDROID_MEDIANDK"] = False
        tc.variables["WITH_ARAVIS"] = False
        tc.variables["WITH_CAROTENE"] = False
        tc.variables["WITH_CLP"] = False
        tc.variables["WITH_CUBLAS"] = False
        tc.variables["WITH_CUDA"] = False
        tc.variables["WITH_CUDNN"] = False
        tc.variables["WITH_CUFFT"] = False
        tc.variables["WITH_DIRECTX"] = self.settings.os == "Windows"
        tc.variables["WITH_DSHOW"] = False
        tc.variables["WITH_EIGEN"] = True
        tc.variables["WITH_FFMPEG"] = False
        tc.variables["WITH_GDAL"] = False
        tc.variables["WITH_GDCM"] = False
        tc.variables["WITH_GPHOTO2"] = False
        tc.variables["WITH_GSTREAMER"] = self.settings.os == "Linux"
        tc.variables["WITH_GTK"] = False
        tc.variables["WITH_GTK_2_X"] = False
        tc.variables["WITH_HALIDE"] = False
        tc.variables["WITH_HPX"] = False
        tc.variables["WITH_IMGCODEC_HDR"] = True
        tc.variables["WITH_IMGCODEC_PFM"] = True
        tc.variables["WITH_IMGCODEC_PXM"] = True
        tc.variables["WITH_IMGCODEC_SUNRASTER"] = True
        tc.variables["WITH_INF_ENGINE"] = False
        tc.variables["WITH_IPP"] = False
        tc.variables["WITH_ITT"] = False
        tc.variables["WITH_JASPER"] = False
        tc.variables["WITH_JPEG"] = True
        tc.variables["WITH_LAPACK"] = False
        tc.variables["WITH_LIBREALSENSE"] = False
        tc.variables["WITH_MFX"] = False
        tc.variables["WITH_MSMF"] = self.settings.os == "Windows"
        tc.variables["WITH_MSMF_DXVA"] = False
        tc.variables["WITH_NGRAPH"] = False
        tc.variables["WITH_ONNX"] = False
        tc.variables["WITH_OPENCL"] = False
        tc.variables["WITH_OPENCL_D3D11_NV"] = self.settings.os == "Windows"
        tc.variables["WITH_OPENCL_SVM"] = False
        tc.variables["WITH_OPENCLAMDBLAS"] = True
        tc.variables["WITH_OPENCLAMDFFT"] = True
        tc.variables["WITH_OPENEXR"] = False
        tc.variables["WITH_OPENGL"] = False
        tc.variables["WITH_OPENJPEG"] = False
        tc.variables["WITH_OPENMP"] = False
        tc.variables["WITH_OPENNI"] = False
        tc.variables["WITH_OPENNI2"] = False
        tc.variables["WITH_OPENVX"] = False
        tc.variables["WITH_PNG"] = True
        tc.variables["WITH_PROTOBUF"] = True
        tc.variables["WITH_PVAPI"] = False
        tc.variables["WITH_QT"] = True
        tc.variables["WITH_QUIRC"] = False
        tc.variables["WITH_TBB"] = False
        tc.variables["WITH_TENGINE"] = False
        tc.variables["WITH_TIFF"] = True
        tc.variables["WITH_UEYE"] = False
        tc.variables["WITH_V4L"] = self.settings.os == "Linux"
        tc.variables["WITH_VA"] = False
        tc.variables["WITH_VA_INTEL"] = False
        tc.variables["WITH_VTK"] = False
        tc.variables["WITH_VULKAN"] = False
        tc.variables["WITH_WEBP"] = True
        tc.variables["WITH_WIN32UI"] = self.settings.os == "Windows"
        tc.variables["WITH_XIMEA"] = False
        tc.variables["WITH_XINE"] = False

        tc.variables["PROTOBUF_UPDATE_FILES"] = True
        tc.variables["Protobuf_USE_STATIC_LIBS"] = True
        tc.variables["protobuf_MODULE_COMPATIBLE"] = True

        # Avoid link dependency on gstreamer:
        tc.variables["VIDEOIO_PLUGIN_LIST"] = "ffmpeg;gstreamer"  # could also be "all"
        tc.variables["OPENCV_GAPI_GSTREAMER"] = False  # because this is currently not a plugin

        python_package = self.dependencies["python"]
        py = python_package.buildenv_info.vars(self).get("MEVIS_PYTHON_CMD")
        home = python_package.buildenv_info.vars(self).get("PYTHONHOME").replace("\\", "/")

        if self.settings.os == "Windows":
            tc.variables["PYTHON3_EXECUTABLE"] = f"{home}/{py}"
        else:
            tc.variables["PYTHON3_EXECUTABLE"] = f"{home}/bin/{py}"
        tc.variables["PYTHON3_INCLUDE_DIR"] = python_package.cpp_info.includedirs[0].replace("\\", "/")
        version = python_package.ref.version
        if self.settings.os == "Windows":
            debug_ext = "_d" if self.settings.build_type == "Debug" else ""
            tc.variables["PYTHON3_LIBRARY"] = f"{home}/libs/python{version.major}{version.minor}{debug_ext}.lib"
        else:
            tc.variables["PYTHON3_LIBRARY"] = f"{home}/lib/libpython{version.major}.so"

        site_pkg_folder = python_package.buildenv_info.vars(self).get("MEVIS_PYTHON_SITE_PACKAGES_FOLDER")
        tc.variables["PYTHON3_PACKAGES_PATH"] = f"{home}/{site_pkg_folder}"
        numpy_include_folders = self.dependencies["numpy"].cpp_info.includedirs
        tc.variables["PYTHON3_NUMPY_INCLUDE_DIRS"] = ";".join(numpy_include_folders).replace("\\", "/")
        opencv_folder = self.package_folder.replace("\\", "/")
        tc.variables["OPENCV_PYTHON_INSTALL_PATH"] = f"{opencv_folder}/{site_pkg_folder}"
        tc.generate()

        cd = CMakeDeps(self)
        cd.generate()

    def build(self):
        # These config files must be patched, because they contain the conan package dir as library path for the library
        template_path = self.source_path / "modules" / "python" / "package" / "template"
        version = self.dependencies["python"].ref.version
        replace_in_file(
            self,
            template_path / "config-x.y.py.in",
            "@CMAKE_PYTHON_EXTENSION_PATH@",
            f"os.path.join(os.path.dirname(os.path.abspath(os.path.realpath(__file__)))," f" 'python-{version.major}.{version.minor}')",
        )
        replace_in_file(
            self,
            template_path / "config.py.in",
            "@CMAKE_PYTHON_BINARIES_PATH@",
            f"os.path.join(os.path.dirname(os.path.abspath(os.path.realpath(__file__)))," f" 'python-{version.major}.{version.minor}')",
        )

        # try to fix download problem
        env = Environment()
        env.append("CMAKE_TLS_VERIFY", "0")
        with env.vars(self).apply():
            cmake = CMake(self)
            cmake.configure()
            cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(self, "LICENSE", src=self.source_path, dst=self.package_path / "licenses")
        copy(self, "*.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False, excludes="*vc???.pdb")

        if self.settings.os == "Windows":
            # cleanup package root on Windows
            rm(self, pattern="LICENSE", folder=self.package_path)
            rm(self, pattern="setup_vars_opencv4.cmd", folder=self.package_path)
            rm(self, pattern="OpenCVConfig*.cmake", folder=self.package_path)
            rm(self, pattern="OpenCVConfig*.cmake", folder=self.package_path / "lib")

        if self.settings.os != "Windows":
            rmdir(self, self.package_path / "bin")
        rmdir(self, self.package_path / "etc")
        rmdir(self, self.package_path / "share")
        rmdir(self, self.package_path / "lib" / "cmake")

        for cmakefile in (self.package_path / "lib").glob("*.cmake"):
            cmakefile.unlink()
        for cmakefile in self.package_path.glob("*.cmake"):
            cmakefile.unlink()
        setup_vars_path = self.package_path / "setup_vars_opencv4.cmd"
        if setup_vars_path.exists():
            setup_vars_path.unlink()

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:opencv:opencv:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("base_purl", "github/opencv/opencv")
        self.cpp_info.set_property("cmake_file_name", "OpenCV")
        self.cpp_info.set_property("cmake_target_name", "OpenCV::OpenCV")

        # list dependencies of the components
        comp_dependencies = {
            "core": [],
            "flann": [],
            "imgproc": [],
            "ml": [],
            "photo": ["imgproc"],
            "dnn": ["imgproc"],
            "features2d": ["flann", "imgproc"],
            "imgcodecs": ["imgproc", "libpng::libpng", "libjpeg-turbo::jpeg", "tiff::tiff", "libwebp::webp", "zlib::zlib"],
            "videoio": ["imgproc", "imgcodecs"],
            "calib3d": ["flann", "imgproc", "features2d"],
            "objdetect": ["flann", "imgproc", "features2d", "calib3d"],
            "highgui": ["imgproc", "imgcodecs", "videoio", "qtbase::qtbase"],
            "stitching": ["flann", "imgproc", "features2d", "calib3d"],
            "video": ["flann", "imgproc", "features2d", "calib3d"],
            "gapi": ["imgproc", "calib3d", "video"],
        }

        prefix = "opencv_"
        full_core = prefix + "core"
        version = "".join(self.version.split(".")) if self.settings.os == "Windows" else ""
        debug_suffix = "_d" if self.settings.build_type == "Debug" else ""
        # keep track of existing libs that don"t belong to an explicit component:
        unassigned_libs = collect_libs(self)
        # filter out (potential) plugins:
        plugin_re = re.compile(".*(ffmpeg|gstreamer).*")
        unassigned_libs = [name for name in unassigned_libs if not plugin_re.match(name)]
        for comp in comp_dependencies:
            full_comp = prefix + comp
            self.cpp_info.components[full_comp].set_property("cmake_target_name", f"OpenCV::{full_comp}")
            # prefix local components with "opencv_":
            requirements = [r if "::" in r else prefix + r for r in comp_dependencies[comp]]
            if comp != "core":
                # everything depends on opencv_core (except opencv_core itself):
                requirements += [full_core]
            # everything depends on eigen:
            requirements += ["eigen::eigen"]
            self.cpp_info.components[full_comp].requires = requirements
            # set library name of this component
            lib_name = f"{full_comp}{version}{debug_suffix}"
            self.cpp_info.components[full_comp].libs = [lib_name]
            try:
                unassigned_libs.remove(lib_name)
            except ValueError:
                self.output.warning(f"{lib_name} not found in list of unassigned libs: {unassigned_libs}")

            if self.settings.os == "Linux":
                self.cpp_info.components[full_comp].system_libs.extend(["pthread", "m", "dl"])
            if self.settings.os != "Windows":
                self.cpp_info.components[full_comp].includedirs = ["include", "include/opencv4"]

        if self.settings.os == "Windows":
            self.cpp_info.components["opencv_highgui"].system_libs = ["Vfw32"]

        # create a dummy component for compatibility with our old one-component CMake file:
        self.cpp_info.components["OpenCV"].requires = [prefix + comp for comp in comp_dependencies]
        # Conan demands that all project requirements are used:
        self.cpp_info.components["OpenCV"].requires += ["python::python", "numpy::numpy"]
        # Put all unused libs in this dummy component:
        if unassigned_libs:
            self.output.warning(f'Adding the following libs to the dummy "OpenCV" component: {unassigned_libs}')
            self.cpp_info.components["OpenCV"].libs += unassigned_libs
