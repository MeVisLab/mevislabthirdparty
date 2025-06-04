from textwrap import dedent
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get, rmdir, patch
from conan.tools.scm import Version

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "dcmtk"
    version = "3.6.9"
    description = "The DICOM Toolkit"
    license = "BSD-3-Clause"
    homepage = "https://dicom.offis.de/dcmtk.php.en"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch"

    def requirements(self):
        self.requires("zlib/[>=1.2]")
        self.requires("libpng/[>=1.6]")
        self.requires("libxml2/[>=2.9]")
        self.requires("tiff/[>=4.1]")
        # self.requires("openssl/[>=3.2]")
        self.requires("libjpeg-turbo/[>=2.1]")
        self.requires("libiconv/[>=1.16]")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        v = Version(self.version)
        get(
            self,
            sha256="b93ff5561244916a6e1e7e3ecccf2e26e6932c4edb5961268401cea7d4ab9c16",
            url=f"https://dicom.offis.de/download/dcmtk/dcmtk{v.major}{v.minor}{v.patch}/dcmtk-{self.version}.tar.gz",
            strip_root=True,
        )
        patch(
            self,
            patch_file="patches/002-dcdictbi.cc.patch",
            patch_type="compatibility",
            patch_description="replaces retired tags with ACR NEMA tags",
        )
        patch(
            self,
            patch_file="patches/003-dcpixel.cc.patch",
            patch_type="feature",
            patch_description=dedent(
                """
                handles specific case of invalid multi-frame padding (padding byte for each frame)
                note that the detection of this case is not completely certain:
                """
            ),
        )
        patch(
            self,
            patch_file="patches/004-dcuid.cc.patch",
            patch_type="feature",
            patch_description="handling of machines without network adapter (e.g. VM)",
        )
        patch(
            self,
            patch_file="patches/005-find_package_required.patch",
            patch_type="bugfix",
            patch_description="makes configured packages mandatory, e.g. an error instead of a warning is issued if they are missing",
        )
        patch(
            self,
            patch_file="patches/006-on_the_fly_compression.patch",
            patch_type="feature",
            patch_description="enables on the fly compression in storescu",
        )
        patch(
            self,
            patch_file="patches/007-storescp.cc.patch",
            patch_type="feature",
            patch_description=dedent(
                """
                option 'short-info': decreased verbosity, creates standardized one-line descriptions per association
                option 'flat-study-path': incoming files will be saved top-level regardless of the study
                option 'tempfile-while-saving': write incoming file into temp file and renames it after completion
                """
            ),
        )
        patch(
            self,
            patch_file="patches/008-storescu.cc.patch",
            patch_type="feature",
            patch_description=dedent(
                """
                option 'from-file': read file list to send from file
                option 'accept-dicom-only': skip files without preamble to avoid long processing times
                """
            ),
        )
        patch(self, patch_file="patches/010-find_3rdparty.patch", patch_description="find and use our conan dependencies")
        patch(
            self,
            patch_file="patches/012-cmake_module_path.patch",
            patch_description="do not prefer CMake modules, Conan generated modules should come first",
        )
        patch(self, patch_file="patches/013-find_libcharset.patch", patch_description="find libcharset debug library")
        patch(self, patch_file="patches/014-libiconv.patch", patch_description="disable libiconv configure test")
        patch(self, patch_file="patches/015-disable_nsl_test.patch", patch_description="disable test for nsl socket")

    def generate(self):
        cd = CMakeDeps(self)
        cd.generate()
        tc = CMakeToolchain(self, generator="Ninja")
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["CMAKE_INSTALL_RPATH_USE_LINK_PATH"] = False
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["BUILD_APPS"] = True
        tc.variables["DCMTK_USE_FIND_PACKAGE"] = True
        tc.variables["DCMTK_ENABLE_PRIVATE_TAGS"] = True
        tc.variables["DCMTK_ENABLE_CXX11"] = True
        tc.variables["DCMTK_DEFAULT_DICT"] = "builtin"
        tc.variables["DCMTK_USE_DCMDICTPATH"] = False
        tc.variables["DCMTK_WIDE_CHAR_FILE_IO_FUNCTIONS"] = True
        tc.variables["DCMTK_WIDE_CHAR_MAIN_FUNCTION"] = True
        tc.variables["DCMTK_WITH_DOXYGEN"] = False
        tc.variables["DCMTK_WITH_THREADS"] = True
        tc.variables["DCMTK_WITH_STDLIBC_ICONV"] = False
        tc.variables["DCMTK_WITH_XML"] = True if "libxml2" in self.dependencies else False
        tc.variables["DCMTK_WITH_PNG"] = True if "libpng" in self.dependencies else False
        tc.variables["DCMTK_WITH_TIFF"] = True if "tiff" in self.dependencies else False
        tc.variables["DCMTK_WITH_ZLIB"] = True if "zlib" in self.dependencies else False
        tc.variables["DCMTK_WITH_ICU"] = True if "icu" in self.dependencies else False
        tc.variables["DCMTK_WITH_OPENSSL"] = True if "openssl" in self.dependencies else False
        tc.variables["DCMTK_WITH_OPENJPEG"] = True if "openjpeg" in self.dependencies else False
        tc.variables["DCMTK_WITH_SNDFILE"] = True if "sndfile" in self.dependencies else False
        tc.variables["DCMTK_WITH_WRAP"] = False
        tc.variables["DCMTK_WITH_ICONV"] = True if "libiconv" in self.dependencies else False
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "COPYRIGHT", src=self.source_path, dst=self.package_path / "licenses")
        cmake = CMake(self)
        cmake.install()
        copy(self, "*.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False, excludes="*vc???.pdb")
        rmdir(self, self.package_path / "cmake")
        rmdir(self, self.package_path / "share")
        rmdir(self, self.package_path / "etc")
        rmdir(self, self.package_path / "lib" / "pkgconfig")
        rmdir(self, self.package_path / "lib" / "cmake")

    @property
    def _dcmtk_components(self):
        zlib = ["zlib::zlib"] if "zlib" in self.dependencies else []
        openssl = ["openssl::openssl"] if "openssl" in self.dependencies else []
        libiconv = ["libiconv::libiconv"] if "libiconv" in self.dependencies else []
        tiff = ["tiff::tiff"] if "tiff" in self.dependencies else []
        libxml2 = ["libxml2::libxml2"] if "libxml2" in self.dependencies else []
        libpng = ["libpng::libpng"] if "libpng" in self.dependencies else []
        jpeg = ["libjpeg-turbo::libjpeg-turbo"] if "libjpeg-turbo" in self.dependencies else []

        return {
            "ofstd": ["oficonv"] + libiconv,
            "oficonv": [],
            "oflog": ["ofstd"],
            "dcmdata": ["ofstd", "oflog"] + zlib,
            "i2d": ["dcmdata", "dcmxml"],
            "dcmxml": [
                "dcmdata",
                "ofstd",
                "oflog",
            ]
            + zlib
            + libxml2,
            "dcmimgle": ["ofstd", "oflog", "dcmdata"],
            "dcmimage": ["oflog", "dcmdata", "dcmimgle"] + libpng + tiff,
            "dcmjpeg": ["ofstd", "oflog", "dcmdata", "dcmimgle", "dcmimage", "ijg8", "ijg12", "ijg16"] + jpeg,
            "ijg8": [],
            "ijg12": [],
            "ijg16": [],
            "dcmjpls": ["ofstd", "oflog", "dcmdata", "dcmimgle", "dcmimage", "dcmtkcharls"],
            "dcmtkcharls": ["ofstd", "oflog"],
            "dcmtls": ["ofstd", "dcmdata", "dcmnet"] + openssl,
            "dcmnet": ["ofstd", "oflog", "dcmdata"],
            "dcmsr": ["ofstd", "oflog", "dcmdata", "dcmimgle", "dcmimage", "libxml2::libxml2"],
            "cmr": ["dcmsr"],
            "dcmdsig": ["ofstd", "dcmdata"] + openssl,
            "dcmwlm": ["ofstd", "dcmdata", "dcmnet"],
            "dcmqrdb": ["ofstd", "dcmdata", "dcmnet"],
            "dcmpstat": ["ofstd", "oflog", "dcmdata", "dcmimgle", "dcmimage", "dcmnet", "dcmiod", "dcmdsig", "dcmtls", "dcmsr", "dcmqrdb"]
            + openssl,
            "dcmrt": ["ofstd", "oflog", "dcmdata", "dcmimgle"],
            "dcmiod": ["dcmdata", "ofstd", "oflog"],
            "dcmfg": ["dcmiod", "dcmdata", "ofstd", "oflog"],
            "dcmseg": ["dcmfg", "dcmiod", "dcmdata", "ofstd", "oflog"],
            "dcmtract": ["dcmiod", "dcmdata", "ofstd", "oflog"],
            "dcmpmap": ["dcmfg", "dcmiod", "dcmdata", "ofstd", "oflog"],
        }

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:dicom:dcmtk:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/DCMTK/DCMTK@DCMTK-{self.version}")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "DCMTK")
        self.cpp_info.set_property("cmake_target_name", "DCMTK::DCMTK")
        lib_postfix = "_d" if self.settings.build_type == "Debug" else ""

        def register_components(components):
            for target_lib, requires in components.items():
                self.cpp_info.components[target_lib].set_property("cmake_target_name", "DCMTK::" + target_lib)
                self.cpp_info.components[target_lib].libs = [target_lib + lib_postfix]
                self.cpp_info.components[target_lib].includedirs.append("include/dcmtk")
                self.cpp_info.components[target_lib].requires = requires

        register_components(self._dcmtk_components)
        if self.settings.os == "Windows":
            self.cpp_info.components["ofstd"].system_libs.extend(["iphlpapi", "ws2_32", "netapi32", "wsock32"])
        elif self.settings.os == "Linux":
            self.cpp_info.components["ofstd"].system_libs.extend(["m", "pthread"])
