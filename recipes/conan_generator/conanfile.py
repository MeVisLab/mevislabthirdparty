# pylint: skip-file
import glob
import json
import os
import re
import textwrap
import traceback
from dataclasses import dataclass
from datetime import datetime
from pathlib import Path

from conan import ConanFile, conan_version
from conan.internal.model.conanfile_interface import ConanFileInterface
from conan.tools.cmake import CMakeDeps
from conan.tools.files import load, save, chdir, mkdir, replace_in_file
from conan.tools.scm import Version
from jinja2 import Environment, FileSystemLoader

from licenses import spdx_licenses, other_licenses
from mli import MLI, MLI_Python, MLI_Qt

required_conan_version = ">=2.0"


# these packages should neither be installed, nor listed as third-party dependency
def is_excluded_package(pkg_name):
    return pkg_name == "conan_generator" or pkg_name.endswith("_installer")


class ConanRecipe(ConanFile):
    name = "conan_generator"
    version = "2.0.0"
    url = "http://mevislab.mevis.lokal"
    license = "MIT"
    description = "MeVisLab custom conan generator"
    exports = "templates/*.jinja", "mli.py", "licenses/*.py"
    package_type = "python-require"
    settings = None

    def package_id(self):
        self.info.clear()

    def package_info(self):
        self.cpp_info.set_property("cmake_find_mode", "none")


def get_display_name(dependency):
    cmakeName = dependency.cpp_info.get_property("cmake_file_name")
    if cmakeName and cmakeName.lower().endswith("dummy"):
        cmakeName = None
    return dependency.cpp_info.get_property("display_name") or cmakeName or dependency.ref.name


class MLIDeps:

    def __init__(self, conanfile: ConanFileInterface):
        self.conanfile = conanfile
        self.external_mli_files = {}

    def refer_to_existing_mlab_package(self, package_id: str, package_path: str):
        """If generating .mli files for a MeVisLab package other than MeVis/ThirdParty,
        some dependencies might come from MeVis/ThirdParty, and need to be included
        correctly.

        So scan the given package for .mli files with the name of a dependency,
        and remember the package_id to use for this dependency, which will be used
        for includes of this .mli file.

        :param: package_id a package id like "MeVis/ThirdParty"
        :param: package_path is the root path of the package."""
        path = Path(package_path) / "Configuration" / "Installers" / "Libraries"
        for entry in path.glob("*.mli"):
            dep_name = entry[:-4]
            # Is this a known dependency?
            if dep_name in self.conanfile.dependencies.host:
                self.external_mli_files[dep_name] = package_id

    def get_content(self, package_id: str):
        result = {}
        # check only non-build requirements, but include skipped ones (some static libraries)
        for dependency in self.conanfile.dependencies.filter({"build": False, "test": False}).values():
            dependency_name = dependency.ref.name
            if is_excluded_package(dependency_name):
                continue

            if dependency_name.startswith("qt") and dependency_name != "qtservice":
                subGenerator = MLI_Qt(self.conanfile, dependency, package_id)
            elif dependency_name == "python":
                subGenerator = MLI_Python(self.conanfile, dependency, package_id)
            else:
                subGenerator = MLI(self.conanfile, dependency, package_id)
            subGenerator.set_external_mli_files(self.external_mli_files)
            result.update(subGenerator.get_content())
        return result

    def generate(self, package_id="MeVis/ThirdParty"):
        generator_files = self.get_content(package_id)
        for generator_file, content in generator_files.items():
            save(self.conanfile, generator_file, content)


@dataclass
class PackageDeps:
    """Holds all transitive dependencies of a package, separated by mandatory and optional."""

    mandatory: set[ConanFileInterface]
    optional: set[ConanFileInterface]


class _ThirdPartyInformationBase:

    def __init__(self, conanfile: ConanFile):
        self.conanfile = conanfile

    def _get_licenses_of_dependency(self, dependency):

        def partition_all(s: str, separators: tuple[str, ...]):
            if separators:
                before, sep, after = s.partition(separators[0])
                if sep:
                    # separator occurred in sub-string, also separate strings left and right of it
                    return partition_all(before, separators[1:]) + [sep] + partition_all(after, separators)
                else:
                    # separator didn't occur, try next separator
                    return partition_all(s, separators[1:])
            elif s:
                return [s]
            else:
                return []

        license_separators = (" ", "(", ")")
        non_parts = license_separators + ("AND", "OR")
        licenses = dependency.license
        if isinstance(licenses, (list, tuple)):
            # support license lists:
            license_list = licenses
            licenses = " AND ".join(licenses)
        else:
            if licenses:
                # split potential SPDX license expression
                license_list = partition_all(licenses, license_separators)
            else:
                license_list = []
        license_names = []
        for license_id in license_list:
            if license_id in non_parts:
                # license_names.append(license_id)  # should we retain the license expression???
                continue
            lic = spdx_licenses.get(license_id.lower(), other_licenses.get(license_id.lower()))
            if lic:
                license_names.append(lic["name"])
            else:
                # use license id unchanged
                license_names.append(license_id)
                if not license_id.lower().startswith("licenseref-"):
                    self.conanfile.output.info("\n\n")
                    self.conanfile.output.error(f"Invalid license: '{license_id}' in {dependency.ref.name}")
                    self.conanfile.output.info("Please use a SPDX license identifier (https://spdx.org/licenses/).")
        return licenses, ", ".join(license_names)

    def collect_all_dependencies(
        self,
        dependencies: dict[ConanFileInterface, PackageDeps],
        *,
        for_dependency: ConanFileInterface | None = None,
    ):
        top_level_dep = for_dependency or self.conanfile
        deps = {d for d in top_level_dep.dependencies.direct_host.values()}
        optional_dep_names = (top_level_dep.cpp_info.get_property("optional_deps") or "").split(",")
        top_level_optional_deps = {d for d in deps if d.ref.name in optional_dep_names}
        optional_deps = set(top_level_optional_deps)
        mandatory_deps = deps - optional_deps
        for d in deps:
            if d not in dependencies:
                self.collect_all_dependencies(dependencies, for_dependency=d)
            secondary_deps = dependencies[d]
            if d in top_level_optional_deps:
                # all secondary dependencies are initially optional
                optional_deps |= secondary_deps.optional | secondary_deps.mandatory
            else:
                # only secondary optional dependencies are optional
                mandatory_deps |= secondary_deps.mandatory
                optional_deps |= secondary_deps.optional
        # dependencies that are in both groups are mandatory
        optional_deps -= mandatory_deps
        dependencies[top_level_dep] = PackageDeps(mandatory_deps, optional_deps)


class ThirdPartyInformationDeps(_ThirdPartyInformationBase):

    @staticmethod
    def assert_exists(value):
        if not value:
            raise AssertionError()
        return value

    def generate_dependency(
        self,
        dependency: ConanFile,
        package_id: str,
        contents: dict,
        mandatory_deps: set[ConanFile],
        optional_deps: set[ConanFile],
    ):
        tp_info_path = package_id + "/ThirdPartyInformation"
        pkg_name = dependency.ref.name
        base_path = f"{tp_info_path}/{pkg_name}"
        licenses, license_names = self._get_licenses_of_dependency(dependency)

        info = {
            "id": pkg_name.lower(),
            "name": get_display_name(dependency),
            "version": str(dependency.ref.version),
            "license": licenses,
            "license_name": license_names,
            "homepage": dependency.homepage,
            "description": dependency.description,
            # This package was created with conan:
            "package_source": "conan-mevislab-MMS",
            # TODO MeVisLab shows all licenses anyway.
            #      However, some customers use this information for their OTS monitoring.
            #      So when we provide that information, we have to be absolutely sure that we don't have false negatives.
            "aboutNeeded": True,
        }
        for key, value in info.items():
            if not value:
                self.conanfile.output.warning(f"Missing value for {key} in .mlinfo for {pkg_name}")
        # cpe are IDs for CVE entries, and must be set manually on the conan recipe.
        cpe = dependency.cpp_info.get_property("cpe")
        if cpe:
            info["cpe"] = cpe
        # purl are IDs that are used, e.g., by dependency track to determine if a newer
        # version is available
        purl = dependency.cpp_info.get_property("purl")
        if purl:
            info["purl"] = purl
        # list dependencies:
        if mandatory_deps or optional_deps:
            # we list both mandatory and optional dependencies in the "dependencies" entry
            info["dependencies"] = sorted([d.ref.name.lower() for d in (mandatory_deps | optional_deps)])
        if optional_deps:
            info["optional_dependencies"] = sorted([d.ref.name.lower() for d in optional_deps])
        # create JSON:
        contents[f"{base_path}/{pkg_name}.mlinfo"] = json.dumps(info, indent=4)

        if not dependency.package_folder:
            return

        license_folder = dependency.package_path / "licenses"
        license_files = list(license_folder.glob("**/*")) if license_folder.exists() else []
        license_files = [f for f in license_files if (license_folder / f).is_file()]  # remove pure sub-directories
        if not license_files:
            self.conanfile.output.error(f"No license found for ThirdPartyInformation of {pkg_name}")
        else:
            contents[f"{base_path}/{pkg_name}.license"] = load(self.conanfile, license_folder / license_files[0])
            # in case there is more than one license file:
            for num, filename in enumerate(license_files[1:], start=2):
                contents[f"{base_path}/{pkg_name}.license{num}"] = load(self.conanfile, license_folder / filename)

    def generate(self, package_id="MeVis/ThirdParty"):
        dependencies = {}
        self.collect_all_dependencies(dependencies)
        contents = {}
        for dependency, values in dependencies.items():
            if dependency.ref.name == self.conanfile.ref.name:
                continue
            self.generate_dependency(dependency, package_id, contents, values.mandatory, values.optional)
        for generator_file, content in contents.items():
            save(self.conanfile, generator_file, content)


class ThirdPartyDocBookDeps(_ThirdPartyInformationBase):

    def _list_required_by(self, name):
        res = []
        for dep in self.conanfile.dependencies.host.values():
            for dep2 in dep.dependencies.host.values():
                if dep2.ref.name == name:
                    res.append(get_display_name(dep))
        return res

    @property
    def filename(self):
        return "MeVisLabThirdParty.xml"

    @property
    def content(self):
        try:
            return self.get_content()
        except Exception as ex:
            print("".join(traceback.format_exception(type(ex), value=ex, tb=ex.__traceback__)))
            raise ex

    def get_content(self):
        tpl = Environment(
            loader=FileSystemLoader(os.path.join(os.path.dirname(os.path.abspath(__file__)), "templates")),
            trim_blocks=True,
            lstrip_blocks=True,
            autoescape=True,
        )
        template = tpl.get_template("ThirdParty.docbook.jinja")

        items = []

        for dependency in self.conanfile.dependencies.host.values():
            pkg_name = dependency.ref.name
            if is_excluded_package(pkg_name):
                continue

            public_sdk_only = pkg_name in [
                "cluster",
                "ctk-cli",
                "dirsync",
                "flann",
                "httmock",
                "kissfft",
                "libzmq",
                "muparser",
                "nlohmann_json",
                "opencl-headers",
                "opencl-icd-loader",
                "openigtlink",
                "pcl",
                "picojson",
                "pyyaml",
                "pyzmq",
                "spline",
                "vigra",
                "xylib",
            ]

            components = dependency.cpp_info.components.keys()
            requirements = [get_display_name(d) for d in dependency.dependencies.host.values()]

            _, licenses = self._get_licenses_of_dependency(dependency)
            items.append(
                {
                    "cpp_info": dependency.cpp_info,
                    "name": get_display_name(dependency),
                    "version": str(dependency.ref.version),
                    "license": licenses,
                    "public_sdk_only": public_sdk_only,
                    "description": dependency.description,
                    "homepage": dependency.homepage,
                    "components": components,
                    "required_by": self._list_required_by(pkg_name),
                    "requires": requirements,
                }
            )

        return template.render(items=sorted(items, key=lambda d: d["name"]))

    def generate(self):
        save(self.conanfile, self.filename, self.content)


class MeVisLabCMakeDeps:

    def __init__(self, conanfile):
        self.conanfile = conanfile
        # Make target package configurable:
        self.cmake_intern_folder = "cmake_intern"  # for internal cmake files, not in SDK
        self.cmake_sub_folder = "cmake_thirdparty"  # exported cmake folder
        self.package_id = "MeVis/ThirdParty"  # target package
        self.make_cmake_files_silent = False  # By default the generated cmake files print a lot of messages

    @property
    def content(self):
        try:
            return self.get_content()
        except Exception as ex:
            print("".join(traceback.format_exception(type(ex), value=ex, tb=ex.__traceback__)))
            raise ex

    @staticmethod
    def unique_prefix_paths(paths):
        ret = []
        last = None
        for path in sorted(paths):
            if last is None or not path.startswith(last):
                ret.append(path)
                last = path

        return " ".join('"%s"' % p.replace("\\", "/").replace("$", "\\$").replace('"', '\\"') for p in ret)

    def get_template_engine(self, build_type):
        # initialize template engine
        tpl = Environment(
            loader=FileSystemLoader(os.path.join(os.path.dirname(os.path.abspath(__file__)), "templates")),
            trim_blocks=True,
        )
        tpl.globals["header_date"] = datetime.now().strftime("%d/%m/%Y")
        tpl.globals["min_cmake_version"] = "3.20.0"
        tpl.globals["build_type"] = build_type
        tpl.globals["build_type_suffix"] = f"_{build_type}" if build_type else ""
        tpl.globals["configs"] = ["Release", "RelWithDebInfo", "MinSizeRel", "Debug"]
        tpl.globals["package_id"] = self.package_id
        return tpl

    def get_content(self):
        ret = {}

        build_type = str(self.conanfile.settings.build_type).upper()

        tpl = self.get_template_engine(build_type)

        try:
            python_version = self.conanfile.dependencies["python"].ref.version
            tpl.globals["python_major_version"] = python_version.major
            tpl.globals["python_minor_version"] = python_version.minor
        except KeyError:
            tpl.globals["python_major_version"] = None
            tpl.globals["python_minor_version"] = None

        # load templates
        thirdparty_install_target_tpl = tpl.get_template("MeVisLabInstallThirdPartyTarget.jinja")

        # Mapping pkg_name to conan package root dir - used in MeVisLabThirdPartyPaths.jinja
        package_root_dirs = {}

        for dependency in self.conanfile.dependencies.host.values():
            pkg_name = dependency.ref.name
            if is_excluded_package(pkg_name):
                continue

            cpp_info = dependency.cpp_info

            pkg_rootpath = dependency.package_folder.replace("\\", "/").replace("$", "\\$").replace('"', '\\"')
            package_root_dirs[pkg_name] = pkg_rootpath

            ret[f"{self.cmake_intern_folder}/MeVisLabInstallThirdParty-{pkg_name.lower()}-{build_type}.cmake"] = (
                thirdparty_install_target_tpl.render(
                    name=pkg_name,
                    rootpath=pkg_rootpath,
                    bin_paths=self.unique_prefix_paths(cpp_info.bindirs),
                    lib_paths=self.unique_prefix_paths(cpp_info.libdirs),
                    res_paths=self.unique_prefix_paths(cpp_info.resdirs),
                    include_paths=self.unique_prefix_paths(cpp_info.includedirs),
                )
            )

        ret[f"{self.cmake_intern_folder}/MeVisLabInstallThirdParty.cmake"] = tpl.get_template(
            "MeVisLabInstallThirdParty.jinja"
        ).render()
        ret[f"{self.cmake_intern_folder}/MeVisLabThirdPartyPaths-{build_type.lower()}.cmake"] = tpl.get_template(
            "MeVisLabThirdPartyPathsType.jinja"
        ).render(package_root_dirs=package_root_dirs)

        ret[f"{self.cmake_intern_folder}/MeVisLabThirdPartyPaths.cmake"] = tpl.get_template(
            "MeVisLabThirdPartyPaths.jinja"
        ).render()

        return ret

    def _generate_and_patch_cmake_config(self):
        mkdir(self.conanfile, self.cmake_sub_folder)
        with chdir(self.conanfile, self.cmake_sub_folder):
            deps = CMakeDeps(self.conanfile)
            deps.generate()
            absolute_path_statement = re.compile(
                r'set\((?P<name>[-\w]+)_PACKAGE_FOLDER_(?P<build_type>[-\w]+) "[^"]*"\)'
            )
            # patch cmake files, files like Eigen3-debug-x86_64-data.cmake
            for filename in glob.glob("*-*-*-data.cmake"):
                content = load(self.conanfile, filename)
                match = absolute_path_statement.search(content)
                if match is None:
                    raise AssertionError(f"Necessary path assignment not found in {filename}")
                # replace absolute package path with something relative (using MeVisLabThirdPartyMacros),
                # which might also be overridden to be absolute
                pkg_name = match.group("name")
                build_type = match.group("build_type")
                subpath = ""
                if pkg_name in ("python", "numpy"):
                    subpath = "/Python"
                    if self.conanfile.settings.os != "Windows":
                        subpath += "/" + build_type.capitalize()
                package_file_part = self.package_id.replace("/", "")
                package_var_part = self.package_id.replace("/", "_").upper()
                root_dir_variable = f"MEVISLAB_{pkg_name}_ROOTDIR_{build_type}"
                if root_dir_variable not in content:  # do not patch twice!
                    path_statement = textwrap.dedent(
                        rf"""
                        if(DEFINED {root_dir_variable})
                            set({pkg_name}_PACKAGE_FOLDER_{build_type} "${{{root_dir_variable}}}")
                        else()
                            include(${{CMAKE_CURRENT_LIST_DIR}}/{package_file_part}Macros.cmake)
                            set({pkg_name}_PACKAGE_FOLDER_{build_type} "${{{package_var_part}_ROOT_DIR}}{subpath}")
                        endif()
                    """
                    )
                    content = content[: match.start()] + path_statement + content[match.end() :]
                    save(self.conanfile, filename, content)

                # TODO (not ported from Conan 1):
                #     # we only have release and debug builds. Generate the other two default build types based on them:
                #     if build_type.lower() == "release":
                #         ret[f"cmake_thirdparty/{pkg_filename}Target-relwithdebinfo.cmake"] = package_config_target_type_tpl.render(**args)
                #         ret[f"cmake_thirdparty/{pkg_filename}Target-minsizerel.cmake"] = package_config_target_type_tpl.render(**args)

            # remove annoying status message in conan < 2.11, because either
            # a) the DLL has not the same name as the .lib file (e.g. version number appended), or
            # b) the project has a mix of shared and static libraries.
            # a) is icu and OpenSSL, b) can be found in ITK and VTK
            if conan_version < Version("2.11.0"):
                replace_in_file(
                    self.conanfile,
                    "cmakedeps_macros.cmake",
                    'message(STATUS "Cannot locate shared library: ${_LIBRARY_NAME}")',
                    "",
                    strict=False,
                )

            tpl = self.get_template_engine(build_type)
            save(
                self.conanfile,
                f"{package_file_part}Macros.cmake",
                tpl.get_template("MeVisLabThirdPartyMacros.jinja").render(package_var_part=package_var_part),
            )

            if self.make_cmake_files_silent:
                # The cmake files are quite chatty if the QUIET option is not specified
                set_message_mode_re = re.compile(r"set\((?P<name>[-\w]+)_MESSAGE_MODE STATUS\)")
                for filename in glob.glob("*-config.cmake") + glob.glob("*Config.cmake"):
                    content = load(self.conanfile, filename)
                    new_content = set_message_mode_re.sub("set(\g<name>_MESSAGE_MODE VERBOSE)", content)
                    if new_content != content:
                        save(self.conanfile, filename, new_content)

    def generate(self):
        self._generate_and_patch_cmake_config()
        generator_files = self.content
        for generator_file, content in generator_files.items():
            save(self.conanfile, generator_file, content)
