import os
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import collect_libs, get, copy, rmdir, patch

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "cryptopp"
    version = "8.9.0"
    homepage = "https://github.com/weidai11/cryptopp"
    description = "A library of cryptographic schemes"
    license = "BSL-1.0"
    package_type = "static-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(self,
            sha256="ab5174b9b5c6236588e15a1aa1aaecb6658cdbe09501c7981ac8db276a24d9ab",
            url=f"https://github.com/weidai11/cryptopp/archive/CRYPTOPP_{self.version.replace('.', '_')}.tar.gz",
            strip_root=True
        )
        get(self,
            sha256="191d69061c56602de1610ebf03b44dcf75636006e7e60ef8105bee6472ec0caf",
            url=f"https://github.com/abdes/cryptopp-cmake/archive/CRYPTOPP_{self.version.replace('.', '_')}.tar.gz",
            destination=os.path.join(self.source_folder, "cryptopp-cmake"),
            strip_root=True
        )
        patch(self,
              patch_file="patches/001-check_for_prime.patch",
              patch_description="CVE-2023-50981, see https://github.com/weidai11/cryptopp/pull/1255")
        patch(self,
              patch_file="patches/002-vaildate_poly_coefficients.patch",
              patch_description="CVE-2023-50980, see https://github.com/weidai11/cryptopp/issues/1248")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["BUILD_SHARED_LIBS"] = False
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.cache_variables["CRYPTOPP_SOURCES"] = self.source_folder.replace("\\", "/")
        tc.cache_variables["CRYPTOPP_BUILD_TESTING"] = False
        tc.cache_variables["CRYPTOPP_BUILD_DOCUMENTATION"] = False
        tc.cache_variables["CRYPTOPP_USE_INTERMEDIATE_OBJECTS_TARGET"] = False
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder="cryptopp-cmake")
        cmake.build()

    def package(self):
        copy(self, "License.txt", src=self.source_path, dst=self.package_path / "licenses")
        cmake = CMake(self)
        cmake.install()
        rmdir(self, self.package_path / "share")

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:cryptopp:crypto\\+\\+:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/weidai11/cryptopp@CRYPTOPP_{self.version.replace('.', '_')}")
        self.cpp_info.set_property("cmake_file_name", "CryptoPP")
        self.cpp_info.set_property("cmake_target_name", "CryptoPP::CryptoPP")
        self.cpp_info.set_property("display_name", "Crypto++")
        self.cpp_info.set_property("pkg_config_name", "libcryptopp")
        self.cpp_info.libs = collect_libs(self)
        if self.settings.os == "Linux":
            self.cpp_info.system_libs = ["pthread", "m"]
        elif self.settings.os == "Windows":
            self.cpp_info.system_libs = ["bcrypt", "ws2_32"]
