import os
import textwrap

from conan import ConanFile
from conan.tools.env import VirtualBuildEnv
from conan.tools.files import copy, collect_libs, get, replace_in_file, rm, rmdir, rename, patch, save
from conan.tools.gnu import Autotools, AutotoolsToolchain
from conan.tools.layout import basic_layout
from conan.tools.microsoft import is_msvc, MSBuild, MSBuildToolchain
from conan.tools.scm import Version

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "libsodium"
    version = "1.0.20"
    homepage = "https://libsodium.org"
    description = "A portable fork of NaCl, a higher-level cryptographic library"
    license = "ISC"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*"

    def configure(self):
        self.settings.rm_safe("compiler.cppstd")
        self.settings.rm_safe("compiler.libcxx")

    def layout(self):
        basic_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="ebb65ef6ca439333c2bb41a0c1990587288da07f6c7fd07cb3a18cc18d30ce19",
            url=f"https://download.libsodium.org/libsodium/releases/libsodium-{self.version}.tar.gz",
            strip_root=True,
        )
        patch(self, patch_file="patches/001-debug_ext.patch")

    def generate(self):
        if is_msvc(self):
            tc = MSBuildToolchain(self)
            tc.configuration = f"Dyn{self.settings.build_type}DLL"
            tc.generate()
        else:
            env = VirtualBuildEnv(self)
            env.generate()
            tc = AutotoolsToolchain(self)
            tc.configure_args.append("--disable-static")
            tc.configure_args.append("--enable-shared")
            tc.configure_args.append("--with-pic")
            if self.settings.build_type == "Debug":
                tc.configure_args.append("--enable-debug")
            tc.generate()

    def build(self):
        if is_msvc(self):
            sln_path = os.path.join(self.source_folder, "builds", "msvc", "vs2019")
            proj_path = os.path.join(sln_path, "libsodium")
            vcxproj_path = os.path.join(proj_path, "libsodium.vcxproj")

            # TODO: to remove once https://github.com/conan-io/conan/pull/12817 is merged
            replace_in_file(
                self,
                vcxproj_path,
                search="<PlatformToolset>v142</PlatformToolset>",
                replace=f"<PlatformToolset>{MSBuildToolchain(self).toolset}</PlatformToolset>",
            )

            props = os.path.join(self.generators_folder, MSBuildToolchain.filename)
            replace_in_file(
                self,
                vcxproj_path,
                '<Import Project="$(VCTargetsPath)\\Microsoft.Cpp.targets" />',
                f'<Import Project="{props}" /><Import Project="$(VCTargetsPath)\\Microsoft.Cpp.targets" />',
            )

            if self.settings.build_type == "Debug":
                for filename in os.listdir(proj_path):
                    old_path = os.path.join(proj_path, filename)
                    new_name = filename.replace("libsodium", "libsodium_d")
                    new_path = os.path.join(proj_path, new_name)
                    rename(self, old_path, new_path)
                replace_in_file(
                    self,
                    os.path.join(proj_path, "libsodium_d.vcxproj"),
                    "<ProjectName>libsodium</ProjectName>",
                    "<ProjectName>libsodium_d</ProjectName>",
                )
                replace_in_file(
                    self,
                    os.path.join(sln_path, "libsodium.sln"),
                    r'"libsodium", "libsodium\libsodium.vcxproj"',
                    r'"libsodium", "libsodium\libsodium_d.vcxproj"',
                )
            # END

            msbuild = MSBuild(self)
            msbuild.build_type = f"Dyn{self.settings.build_type}"
            msbuild.build(os.path.join(self.source_folder, "builds", "msvc", "vs2019", "libsodium.sln"))
        else:
            autotools = Autotools(self)
            autotools.configure()
            autotools.make()

    def package(self):
        copy(self, "*LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        if is_msvc(self):
            copy(
                self,
                "*.dll",
                src=os.path.join(self.source_folder, "bin"),
                dst=os.path.join(self.package_folder, "bin"),
                keep_path=False,
            )
            copy(
                self,
                "*.pdb",
                src=os.path.join(self.source_folder, "bin"),
                dst=os.path.join(self.package_folder, "bin"),
                keep_path=False,
            )
            copy(
                self,
                "*.lib",
                src=os.path.join(self.source_folder, "bin"),
                dst=os.path.join(self.package_folder, "lib"),
                keep_path=False,
            )
            copy(
                self,
                "*.h",
                src=os.path.join(self.source_folder, "src", "libsodium", "include"),
                dst=os.path.join(self.package_folder, "include"),
                excludes="*/private/*",
            )
        else:
            autotools = Autotools(self)
            autotools.install()
            rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
            rm(self, "*.la", os.path.join(self.package_folder, "lib"))
        self._cmake_module_file_write()

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        # self.cpp_info.set_property("purl", "")   # official repository is at https://download.libsodium.org
        self.cpp_info.set_property("cmake_file_name", "sodium")
        self.cpp_info.set_property("cmake_target_name", "sodium::sodium")
        self.cpp_info.set_property("pkg_config_name", "libsodium")
        self.cpp_info.set_property("cmake_build_modules", [self._cmake_module_file])
        self.cpp_info.set_property("cmake_find_package", [self._cmake_module_file])
        self.cpp_info.libs = collect_libs(self)
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.append("pthread")

    @property
    def _cmake_module_file(self):
        return os.path.join("lib", "cmake", f"{self.name}-variables.cmake")

    def _cmake_module_file_write(self):
        v = Version(self.version)
        file = os.path.join(self.package_folder, self._cmake_module_file)
        content = textwrap.dedent(
            f"""\
            set(SODIUM_FOUND TRUE)
            set(SODIUM_LIBRARY ${{sodium_LIBRARY}})
            set(SODIUM_LIBRARIES ${{sodium_LIBRARIES}})
            set(SODIUM_INCLUDE_DIRS ${{sodium_INCLUDE_DIR}})
            set(SODIUM_INCLUDE_DIR ${{sodium_INCLUDE_DIR}})
            set(SODIUM_VERSION "{self.version}")
            set(SODIUM_VERSION_STRING "{self.version}")
            set(SODIUM_VERSION_MAJOR {v.major})
            set(SODIUM_VERSION_MINOR {v.minor})
            set(SODIUM_VERSION_PATCH {v.patch})
            set(SODIUM_MAJOR_VERSION {v.major})
            set(SODIUM_MINOR_VERSION {v.minor})
            set(SODIUM_PATCH_VERSION {v.patch})
            """
        )
        save(self, file, content)
