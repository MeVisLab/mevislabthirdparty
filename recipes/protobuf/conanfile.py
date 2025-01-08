import os
import textwrap

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import replace_in_file, copy, get, rmdir, rm, save
from conan.tools.microsoft import is_msvc

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "protobuf"
    version = "28.3"
    homepage = "https://developers.google.com/protocol-buffers"
    description = "Google's Protocol Buffers are a language-neutral, platform-neutral extensible mechanism for serializing structured data"
    license = "BSD-3-Clause"
    package_type = "static-library"
    settings = "os", "arch", "compiler", "build_type"

    mlab_hooks = {
        "cmake_files.exclude": [
            "lib/cmake/protobuf/protobuf*.cmake",
            "lib/cmake/protobuf/FindProtobuf.cmake",
            "lib/cmake/utf8_range/utf8_range-*.cmake",
        ]
    }

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("zlib/[>=1.2.11]")
        self.requires("abseil/[>=20230802.1]", transitive_headers=True)

    def source(self):
        get(
            self,
            sha256="7c3ebd7aaedd86fa5dc479a0fda803f602caaf78d8aff7ce83b89e1b8ae7442a",
            url=f"https://github.com/protocolbuffers/protobuf/releases/download/v{self.version}/protobuf-{self.version}.tar.gz",
            strip_root=True,
        )
        replace_in_file(
            self, os.path.join(self.source_folder, "CMakeLists.txt"), 'set(protobuf_DEBUG_POSTFIX "d"', 'set(protobuf_DEBUG_POSTFIX "_d"'
        )

    def generate(self):
        cd = CMakeDeps(self)
        cd.generate()

        tc = CMakeToolchain(self)
        tc.cache_variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.cache_variables["BUILD_SHARED_LIBS"] = False
        tc.cache_variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.cache_variables["protobuf_BUILD_TESTS"] = False
        tc.cache_variables["protobuf_WITH_ZLIB"] = True
        tc.cache_variables["protobuf_BUILD_PROTOC_BINARIES"] = True
        tc.cache_variables["protobuf_ABSL_PROVIDER"] = "package"
        tc.cache_variables["protobuf_MSVC_STATIC_RUNTIME"] = False
        tc.cache_variables["protobuf_DISABLE_RTTI"] = False
        tc.cache_variables["protobuf_BUILD_LIBUPB"] = True
        tc.cache_variables["CMAKE_INSTALL_CMAKEDIR"] = "lib/cmake/protobuf"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake", "utf8_range"))
        cmake_config_folder = os.path.join(self.package_folder, "lib", "cmake", "protobuf")
        rm(self, "protobuf-config*.cmake", folder=cmake_config_folder)
        rm(self, "protobuf-targets*.cmake", folder=cmake_config_folder)
        replace_in_file(
            self,
            os.path.join(self.package_folder, "lib", "cmake", "protobuf", "protobuf-module.cmake"),
            "VERSION_VAR Protobuf_VERSION",
            "VERSION_VAR Protobuf_VERSION NAME_MISMATCHED",
        )
        content = textwrap.dedent(
            """
                if(NOT TARGET protobuf::protoc)
                    find_program(PROTOC_PROGRAM NAMES protoc REQUIRED)
                    # find_program(PROTOC_PROGRAM NAMES protoc HINTS ${Protobuf_BIN_DIRS_RELEASE} ${Protobuf_BIN_DIRS_DEBUG} ${protobuf_BIN_DIRS_RELEASE} ${protobuf_BIN_DIRS_DEBUG})
                    # if(NOT PROTOC_PROGRAM)
                    #     set(PROTOC_PROGRAM "${CMAKE_CURRENT_LIST_DIR}/../../../bin/protoc${CMAKE_EXECUTABLE_SUFFIX}")
                    # endif()

                    # if(NOT PROTOC_PROGRAM)
                    #     message(FATAL_ERROR "protoc compiler not found")
                    # endif()

                    get_filename_component(PROTOC_PROGRAM "${PROTOC_PROGRAM}" ABSOLUTE)
                    set(Protobuf_PROTOC_EXECUTABLE ${PROTOC_PROGRAM} CACHE FILEPATH "The protoc compiler")
                    add_executable(protobuf::protoc IMPORTED)
                    set_property(TARGET protobuf::protoc PROPERTY IMPORTED_LOCATION ${Protobuf_PROTOC_EXECUTABLE})
                endif()
            """
        )
        save(self, os.path.join(self.package_folder, "lib", "cmake", "protobuf", "protobuf-protoc-target.cmake"), content)

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:protobuf:protobuf:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("base_purl", "github/protocolbuffers/protobuf")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_module_file_name", "Protobuf")
        self.cpp_info.set_property("cmake_file_name", "protobuf")
        self.cpp_info.set_property("pkg_config_name", "protobuf_full_package")

        cmake_base_path = os.path.join("lib", "cmake", "protobuf")
        build_modules = [
            os.path.join(cmake_base_path, "protobuf-protoc-target.cmake"),
            os.path.join(cmake_base_path, "protobuf-generate.cmake"),
            os.path.join(cmake_base_path, "protobuf-module.cmake"),
            os.path.join(cmake_base_path, "protobuf-options.cmake"),
        ]
        self.cpp_info.set_property("cmake_build_modules", build_modules)

        lib_prefix = "lib" if is_msvc(self) else ""
        lib_suffix = "_d" if self.settings.build_type == "Debug" else ""

        self.cpp_info.components["utf8_range"].set_property("cmake_target_name", "utf8_range::utf8_range")
        self.cpp_info.components["utf8_range"].libs = ["utf8_range" + lib_suffix]

        self.cpp_info.components["utf8_validity"].set_property("cmake_target_name", "utf8_range::utf8_validity")
        self.cpp_info.components["utf8_validity"].libs = ["utf8_validity" + lib_suffix]
        self.cpp_info.components["utf8_validity"].requires = ["abseil::absl_strings"]

        self.cpp_info.components["upb"].set_property("cmake_target_name", "protobuf::libupb")
        self.cpp_info.components["upb"].libs = [lib_prefix + "upb" + lib_suffix]
        self.cpp_info.components["upb"].requires = ["utf8_range"]

        self.cpp_info.components["libprotobuf"].set_property("cmake_target_name", "protobuf::libprotobuf")
        self.cpp_info.components["libprotobuf"].set_property("pkg_config_name", "protobuf")
        self.cpp_info.components["libprotobuf"].builddirs.append(cmake_base_path)
        self.cpp_info.components["libprotobuf"].libs = [lib_prefix + "protobuf" + lib_suffix]
        self.cpp_info.components["libprotobuf"].requires = ["zlib::zlib", "utf8_range", "utf8_validity", "abseil::abseil"]
        if self.settings.os == "Linux":
            self.cpp_info.components["libprotobuf"].system_libs.extend(["m", "pthread"])

        self.cpp_info.components["libprotoc"].set_property("cmake_target_name", "protobuf::libprotoc")
        self.cpp_info.components["libprotoc"].libs = [lib_prefix + "protoc" + lib_suffix]
        self.cpp_info.components["libprotoc"].requires = ["libprotobuf", "abseil::abseil"]

        self.cpp_info.components["libprotobuf-lite"].set_property("cmake_target_name", "protobuf::libprotobuf-lite")
        self.cpp_info.components["libprotobuf-lite"].set_property("pkg_config_name", "protobuf-lite")
        self.cpp_info.components["libprotobuf-lite"].builddirs.append(cmake_base_path)
        self.cpp_info.components["libprotobuf-lite"].libs = [lib_prefix + "protobuf-lite" + lib_suffix]
        self.cpp_info.components["libprotobuf-lite"].requires = ["abseil::abseil"]
        if self.settings.os == "Linux":
            self.cpp_info.components["libprotobuf-lite"].system_libs.extend(["m", "pthread"])

        self.buildenv_info.prepend_path("PATH", os.path.join(self.package_folder, "bin"))
        self.runenv_info.prepend_path("PATH", os.path.join(self.package_folder, "bin"))
