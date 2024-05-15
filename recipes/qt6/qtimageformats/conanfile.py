from conan import ConanFile


required_conan_version = ">=2.2.2"

class ConanRecipe(ConanFile):
    python_requires = "qt_package/1.0.0"
    python_requires_extend = "qt_package.QtPackage"

    qt_feature = {
		"jasper": False,
		"mng": False,
		"tiff": True,
		"webp": True,
		"system_tiff": True,
		"system_webp": True
    }

    def requirements(self):
        super().requirements()
        self.requires(f"libwebp/[>=1.1.0]")
        self.requires(f"tiff/[>=4.1.0]")
        self.requires(f"zlib/[>=1.2.11]")   # TODO stb: an attempt to fix the Windows build. But this is not the right solution!

    def package_info(self):
        super().package_info()
        self.cpp_info.includedirs.clear()
