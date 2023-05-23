# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools
import glob
import os
import re


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None

    def system_requirements(self):
        installer = tools.SystemPackageTool()
        packages = []

        if tools.os_info.linux_distro in ["ubuntu", "debian"]:
            packages.append('libglu1-mesa-dev')
            packages.append('libfreetype6-dev')

        if packages:
            installer.install_packages(packages)


    def requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        self.requires("eigen/[>=3.3.8]" + channel)
        self.requires("libpng/[>=1.6.37]" + channel)
        self.requires("tiff/[>=4.0.9]" + channel)
        self.requires("webp/[>=1.1.0]" + channel)
        self.requires("numpy/[>=1.17.5]" + channel)
        self.requires("protobuf/[>=21.9]" + channel)
        #self.requires("openexr/[>=2.5.3]" + channel)
        #self.requires("openjpeg/[>=2.4.0]" + channel)
        self.requires("python/[>=3.9.7]" + channel)
        self.requires("qt5/[>=5.12.11]" + channel)
        self.requires("libjpeg/9e" + channel)


    def source(self):
        self.default_source()

        tools.rmdir(os.path.join("sources", '3rdparty'))

        tools.replace_in_file(os.path.join('sources', 'CMakeLists.txt'), 'if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")', 'if(false)')
        tools.replace_in_file(os.path.join('sources', 'cmake', 'OpenCVFindWebP.cmake'), 'FIND_LIBRARY(WEBP_LIBRARY NAMES webp)', 'FIND_LIBRARY(WEBP_LIBRARY NAMES webp webpd libwebp libwebpd)')
        tools.replace_in_file(os.path.join('sources', 'cmake', 'OpenCVDetectOpenCL.cmake'), 'ocv_install_3rdparty_licenses(opencl-headers "${OpenCV_SOURCE_DIR}/3rdparty/include/opencl/LICENSE.txt")', '')
        tools.replace_in_file(os.path.join('sources', 'cmake', 'OpenCVInstallLayout.cmake'), 'ocv_update(OPENCV_INSTALL_BINARIES_PREFIX "${OpenCV_ARCH}/${OpenCV_RUNTIME}/")', 'ocv_update(OPENCV_INSTALL_BINARIES_PREFIX "")')

        # It is necessary to remove the global configured Debug postfix for the Python binding library, otherwise there would be two postfix
        tools.replace_in_file(os.path.join('sources', 'modules', 'python', 'common.cmake'), 'PREFIX ""', 'PREFIX "" DEBUG_POSTFIX ""')

        # Without this patch, the debug Python binding library would not be installed
        tools.replace_in_file(os.path.join('sources', 'modules', 'python', 'common.cmake'), 'set(PYTHON_INSTALL_CONFIGURATIONS CONFIGURATIONS Release)', 'set(PYTHON_INSTALL_CONFIGURATIONS "")')


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True

            self._cmake.definitions["OPENCV_ENABLE_NONFREE"] = False
            self._cmake.definitions["OPENCV_FORCE_3RDPARTY_BUILD"] = False

            self._cmake.definitions["INSTALL_TO_MANGLED_PATHS"] = False
            self._cmake.definitions["INSTALL_TESTS"] = False
            self._cmake.definitions['INSTALL_C_EXAMPLES'] = False
            self._cmake.definitions['INSTALL_PYTHON_EXAMPLES'] = False

            self._cmake.definitions["ENABLE_PROFILING"] = False
            self._cmake.definitions["ENABLE_COVERAGE"] = False

            self._cmake.definitions['BUILD_EXAMPLES'] = False
            self._cmake.definitions['BUILD_DOCS'] = False
            self._cmake.definitions['BUILD_TESTS'] = False
            self._cmake.definitions['BUILD_PACKAGE'] = False
            self._cmake.definitions['BUILD_PERF_TESTS'] = False

            if self.settings.compiler == 'Visual Studio':
                self._cmake.definitions['BUILD_WITH_STATIC_CRT'] = 'MT' in str(self.settings.compiler.runtime)

            # disable builds for all 3rd-party components, use conan libraries only
            self._cmake.definitions["BUILD_ZLIB"] = False
            self._cmake.definitions["BUILD_TIFF"] = False
            self._cmake.definitions["BUILD_OPENJPEG"] = False
            self._cmake.definitions["BUILD_JASPER"] = False
            self._cmake.definitions["BUILD_JPEG"] = False
            self._cmake.definitions["BUILD_PNG"] = False
            self._cmake.definitions["BUILD_OPENEXR"] = False
            self._cmake.definitions["BUILD_WEBP"] = False
            self._cmake.definitions["BUILD_TBB"] = False
            self._cmake.definitions["BUILD_IPP_IW"] = False
            self._cmake.definitions["BUILD_ITT"] = False
            self._cmake.definitions['BUILD_JPEG_TURBO_DISABLE'] = True
            self._cmake.definitions['BUILD_PROTOBUF'] = False

            self._cmake.definitions['BUILD_opencv_apps'] = False
            self._cmake.definitions['BUILD_opencv_java'] = False
            self._cmake.definitions['BUILD_opencv_python'] = False
            self._cmake.definitions['BUILD_opencv_python2'] = False
            self._cmake.definitions['BUILD_opencv_python3'] = True
            self._cmake.definitions['BUILD_opencv_python_bindings_generator'] = True
            self._cmake.definitions['BUILD_opencv_js'] = False
            self._cmake.definitions['BUILD_opencv_java_bindings_generator'] = False

            self._cmake.definitions["WITH_1394"]               = False
            self._cmake.definitions["WITH_ANDROID_MEDIANDK"]   = False
            self._cmake.definitions["WITH_ARAVIS"]             = False
            self._cmake.definitions["WITH_CAROTENE"]           = False
            self._cmake.definitions["WITH_CLP"]                = False
            self._cmake.definitions["WITH_CUBLAS"]             = False
            self._cmake.definitions["WITH_CUDA"]               = False
            self._cmake.definitions["WITH_CUDNN"]              = False
            self._cmake.definitions["WITH_CUFFT"]              = False
            self._cmake.definitions["WITH_DIRECTX"]            = tools.os_info.is_windows
            self._cmake.definitions["WITH_DSHOW"]              = False
            self._cmake.definitions["WITH_EIGEN"]              = True
            self._cmake.definitions["WITH_FFMPEG"]             = False
            self._cmake.definitions["WITH_GDAL"]               = False
            self._cmake.definitions["WITH_GDCM"]               = False
            self._cmake.definitions["WITH_GPHOTO2"]            = False
            self._cmake.definitions["WITH_GSTREAMER"]          = tools.os_info.is_linux
            self._cmake.definitions["WITH_GTK"]                = False
            self._cmake.definitions["WITH_GTK_2_X"]            = False
            self._cmake.definitions["WITH_HALIDE"]             = False
            self._cmake.definitions["WITH_HPX"]                = False
            self._cmake.definitions["WITH_IMGCODEC_HDR"]       = True
            self._cmake.definitions["WITH_IMGCODEC_PFM"]       = True
            self._cmake.definitions["WITH_IMGCODEC_PXM"]       = True
            self._cmake.definitions["WITH_IMGCODEC_SUNRASTER"] = True
            self._cmake.definitions["WITH_INF_ENGINE"]         = False
            self._cmake.definitions["WITH_IPP"]                = False
            self._cmake.definitions["WITH_ITT"]                = False
            self._cmake.definitions["WITH_JASPER"]             = False
            self._cmake.definitions["WITH_JPEG"]               = True
            self._cmake.definitions["WITH_LAPACK"]             = False
            self._cmake.definitions["WITH_LIBREALSENSE"]       = False
            self._cmake.definitions["WITH_MFX"]                = False
            self._cmake.definitions["WITH_MSMF"]               = tools.os_info.is_windows
            self._cmake.definitions["WITH_MSMF_DXVA"]          = False
            self._cmake.definitions["WITH_NGRAPH"]             = False
            self._cmake.definitions["WITH_ONNX"]               = False
            self._cmake.definitions["WITH_OPENCL"]             = False
            self._cmake.definitions["WITH_OPENCL_D3D11_NV"]    = tools.os_info.is_windows
            self._cmake.definitions["WITH_OPENCL_SVM"]         = False
            self._cmake.definitions["WITH_OPENCLAMDBLAS"]      = True
            self._cmake.definitions["WITH_OPENCLAMDFFT"]       = True
            self._cmake.definitions["WITH_OPENEXR"]            = False
            self._cmake.definitions["WITH_OPENGL"]             = False
            self._cmake.definitions["WITH_OPENJPEG"]           = False
            self._cmake.definitions["WITH_OPENMP"]             = False
            self._cmake.definitions["WITH_OPENNI"]             = False
            self._cmake.definitions["WITH_OPENNI2"]            = False
            self._cmake.definitions["WITH_OPENVX"]             = False
            self._cmake.definitions["WITH_PNG"]                = True
            self._cmake.definitions["WITH_PROTOBUF"]           = True
            self._cmake.definitions["WITH_PVAPI"]              = False
            self._cmake.definitions["WITH_QT"]                 = True
            self._cmake.definitions["WITH_QUIRC"]              = False
            self._cmake.definitions["WITH_TBB"]                = False
            self._cmake.definitions["WITH_TENGINE"]            = False
            self._cmake.definitions["WITH_TIFF"]               = True
            self._cmake.definitions["WITH_UEYE"]               = False
            self._cmake.definitions["WITH_V4L"]                = tools.os_info.is_linux
            self._cmake.definitions["WITH_VA"]                 = False
            self._cmake.definitions["WITH_VA_INTEL"]           = False
            self._cmake.definitions["WITH_VTK"]                = False
            self._cmake.definitions["WITH_VULKAN"]             = False
            self._cmake.definitions["WITH_WEBP"]               = True
            self._cmake.definitions["WITH_WIN32UI"]            = tools.os_info.is_windows
            self._cmake.definitions["WITH_XIMEA"]              = False
            self._cmake.definitions["WITH_XINE"]               = False

            self._cmake.definitions["PROTOBUF_UPDATE_FILES"]    = True
            self._cmake.definitions["Protobuf_USE_STATIC_LIBS"] = True

            # Avoid link dependency on gstreamer:
            self._cmake.definitions["VIDEOIO_PLUGIN_LIST"]      = "ffmpeg;gstreamer"  # could also be "all"
            self._cmake.definitions["OPENCV_GAPI_GSTREAMER"]    = False               # because this is currently not a plugin


            python_package = self.deps_cpp_info['python']
            version = python_package.version.split('.')
            major, minor = version[0], version[1]

            if tools.os_info.is_windows:
                self._cmake.definitions["PYTHON3_EXECUTABLE"] = os.path.join(os.environ['PYTHONHOME'], os.environ['MEVIS_PYTHON_CMD'])
            else:
                self._cmake.definitions["PYTHON3_EXECUTABLE"] = os.path.join(os.environ['PYTHONHOME'], 'bin', os.environ['MEVIS_PYTHON_CMD'])
            self._cmake.definitions["PYTHON3_INCLUDE_DIR"] = os.path.join(os.environ['PYTHONHOME'], python_package.includedirs[0])
            self._cmake.definitions["PYTHON3_INCLUDE_DIR2"] = os.path.join(os.environ['PYTHONHOME'], python_package.includedirs[1])
            if tools.os_info.is_windows:
                self._cmake.definitions["PYTHON3_LIBRARY"] = os.path.join(os.environ['PYTHONHOME'], 'libs', f'python{major}{minor}_d.lib' if self.settings.build_type == 'Debug' else f'python{major}{minor}.lib' ).replace("\\","/")
            else:
                self._cmake.definitions["PYTHON3_LIBRARY"] = os.path.join(os.environ['PYTHONHOME'], 'lib', f'libpython{major}.so')

            self._cmake.definitions["PYTHON3_PACKAGES_PATH"] = os.path.join(os.environ['PYTHONHOME'], os.environ['MEVIS_PYTHON_SITE_PACKAGES_FOLDER'])
            self._cmake.definitions["PYTHON3_NUMPY_INCLUDE_DIRS"] = os.path.join(self.deps_cpp_info['numpy'].rootpath, 'site-packages', 'numpy', 'core', 'include')

            self._cmake.definitions["OPENCV_PYTHON_INSTALL_PATH"] = os.path.join(self.package_folder, os.environ['MEVIS_PYTHON_SITE_PACKAGES_FOLDER'])

            self._cmake.configure()

        return self._cmake


    def build(self):
        # Without the following lines the release build of OpenCV will work,
        # but not the debug build. That's how it works, but I have no idea
        # where the cause of the problem lies.

        if tools.os_info.linux_distro in ["ubuntu", "debian"]:
            installer = tools.SystemPackageTool()
            packages = [
                'libgstreamer1.0-dev',
                'libgstreamer-plugins-base1.0-dev',
                ]
            installer.install_packages(packages)

        find_libs_grfmt = os.path.join("sources", 'cmake', 'OpenCVFindLibsGrfmt.cmake')
        tools.replace_in_file(find_libs_grfmt, 'if(NOT ZLIB_FOUND)', '''
            set(ZLIB_INCLUDE_DIRS "${CONAN_INCLUDE_DIRS_ZLIB}")
            set(ZLIB_LIBRARY "${CONAN_LIBS_ZLIB}")
            set(ZLIB_LIBRARIES "${CONAN_LIBS_ZLIB}")
            set(ZLIB_FOUND 1)

            if(NOT ZLIB_FOUND)''')

        tools.replace_in_file(find_libs_grfmt, 'if(NOT PNG_FOUND)', '''
            set(PNG_INCLUDE_DIRS "${CONAN_INCLUDE_DIRS_PNG}")
            set(PNG_LIBRARY "${CONAN_LIBS_PNG}")
            set(PNG_LIBRARIES "${CONAN_LIBS_PNG}")
            set(PNG_FOUND 1)

            if(NOT PNG_FOUND)''')

        # allow to find conan-supplied OpenEXR
        find_openexr = os.path.join("sources", 'cmake', 'OpenCVFindOpenEXR.cmake')
        tools.replace_in_file(find_openexr, r'SET(OPENEXR_ROOT "C:/Deploy" CACHE STRING "Path to the OpenEXR \"Deploy\" folder")', '')
        tools.replace_in_file(find_openexr, 'SET(OPENEXR_LIBSEARCH_SUFFIXES x64/Release x64 x64/Debug)', '')
        tools.replace_in_file(find_openexr, 'SET(OPENEXR_LIBSEARCH_SUFFIXES Win32/Release Win32 Win32/Debug)', '')

        python_package = self.deps_cpp_info['python']
        version = python_package.version.split('.')
        major, minor = version[0], version[1]

        # These config files must be patched, because they contain the conan package dir as library path for the library
        tools.replace_in_file(os.path.join('sources', 'modules', 'python', 'package', 'template', 'config-x.y.py.in'), '@CMAKE_PYTHON_EXTENSION_PATH@', f"os.path.join(os.path.dirname(os.path.abspath(os.path.realpath(__file__))), 'python-{major}.{minor}')")
        tools.replace_in_file(os.path.join('sources', 'modules', 'python', 'package', 'template', 'config.py.in'), '@CMAKE_PYTHON_BINARIES_PATH@', f"os.path.join(os.path.dirname(os.path.abspath(os.path.realpath(__file__))), 'python-{major}.{minor}')")

        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        self.copy("*.pdb", src="bin", dst="bin")

        if not tools.os_info.is_windows:
            tools.rmdir(os.path.join(self.package_folder, 'bin'))
        tools.rmdir(os.path.join(self.package_folder, 'etc'))
        tools.rmdir(os.path.join(self.package_folder, 'share'))
        tools.rmdir(os.path.join(self.package_folder, 'lib', 'cmake'))

        for cmakefile in glob.glob(os.path.join(self.package_folder, 'lib', '*.cmake')):
            os.remove(cmakefile)
        for cmakefile in glob.glob(os.path.join(self.package_folder, '*.cmake')):
            os.remove(cmakefile)
        if os.path.exists(os.path.join(self.package_folder, "setup_vars_opencv4.cmd")):
            os.remove(os.path.join(self.package_folder, "setup_vars_opencv4.cmd"))

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.cpp_info.name = "OpenCV"
        self.cpp_info.names["cmake_find_package"] = "OpenCV"
        self.cpp_info.names["cmake_find_package_multi"] = "OpenCV"
        
        # list dependencies of the components
        comp_dependencies = {
            "core":       [],
            "flann":      [],
            "imgproc":    [],
            "ml":         [],
            "photo":      ["imgproc"],
            "dnn":        ["imgproc", "protobuf::protobuf"],
            "features2d": ["flann", "imgproc"],
            "imgcodecs":  ["imgproc", "libpng::libpng", "libjpeg::libjpeg", "tiff::tiff", "webp::webp"],
            "videoio":    ["imgproc", "imgcodecs"],
            "calib3d":    ["flann", "imgproc", "features2d"],
            "objdetect":  ["flann", "imgproc", "features2d", "calib3d"],
            "highgui":    ["imgproc", "imgcodecs", "videoio", "qt5::qt5"],
            "stitching":  ["flann", "imgproc", "features2d", "calib3d"],
            "video":      ["flann", "imgproc", "features2d", "calib3d"],
            "gapi":       ["imgproc", "calib3d", "video"],
        }
        
        prefix = "opencv_"
        full_core = prefix + "core"
        version = "".join(self.version.split(".")) if self.settings.os == "Windows" else ""
        debug_suffix = "d" if self.settings.build_type == "Debug" else ""
        # keep track of existing libs that don't belong to an explicit component:
        unassigned_libs = tools.collect_libs(self)
        # filter out (potential) plugins:
        plugin_re = re.compile(".*(ffmpeg|gstreamer).*")
        unassigned_libs = [name for name in unassigned_libs if not plugin_re.match(name)]
        for comp in comp_dependencies:
            full_comp = prefix + comp
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
                self.output.warn(f"{lib_name} not found in list of unassigned libs: {unassigned_libs}")
            
            if tools.os_info.is_linux:
                self.cpp_info.components[full_comp].system_libs.extend(["pthread", "m", "dl"])
            if not tools.os_info.is_windows:
                self.cpp_info.components[full_comp].includedirs = ['include', 'include/opencv4']

        # self.cpp_info.components[full_core].libs += tools.collect_libs(self)
        if tools.os_info.is_macos:
            self.cpp_info.components["opencv_highgui"].frameworks = ["Cocoa"]
            self.cpp_info.components["opencv_videoio"].frameworks = ["Cocoa", "Accelerate", "AVFoundation", "CoreGraphics", "CoreMedia", "CoreVideo", "QuartzCore"]
        elif tools.os_info.is_windows:
            self.cpp_info.components["opencv_highgui"].system_libs = ["Vfw32"]
        
        # create a dummy component for compatibility with our old one-component CMake file:
        self.cpp_info.components["OpenCV"].requires = [prefix + comp for comp in comp_dependencies]
        # Conan demands that all project requirements are used:
        self.cpp_info.components["OpenCV"].requires += ["python::python", "numpy::numpy"]
        # Put all unused libs in this dummy component:
        if unassigned_libs:
            self.output.warn(f'Adding the following libs to the dummy "OpenCV" component: {unassigned_libs}')
            self.cpp_info.components["OpenCV"].libs += unassigned_libs
        
