from conan import ConanFile


required_conan_version = ">=2.2.2"

class ConanRecipe(ConanFile):
    python_requires = "qt_package/1.0.0"
    python_requires_extend = "qt_package.QtPackage"
    package_type = "header-library"

    def package_info(self):
        super().package_info()
        self.cpp_info.includedirs = []
