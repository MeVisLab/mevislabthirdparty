# -*- coding: utf-8 -*-

from conans import ConanFile
# from conans.model import Generator
from conans.client.generators import CMakeFindPackageGenerator
from conans.client.generators.cmake import DepsCppCmake
from conans.client.generators.cmake_multi import extend

from jinja2 import Environment, FileSystemLoader, select_autoescape

import os

from datetime import datetime
import traceback

from mli import MLI, MLI_Python
from mli_qt import MLI_Qt


class ConanRecipe(ConanFile):
    name = "conan_generator"
    version = "1.0.0"
    url = "http://mevislab.mevis.lokal"
    license = "MIT"
    description = "MeVisLab custom conan generator"
    exports = ["*.jinja", "mli.py", "mli_qt.py"]
    settings = None

    default_user = "mevislab"
    default_channel = "stable"


class mli_generator(CMakeFindPackageGenerator):
    @property
    def filename(self):
        return None

    @property
    def content(self):
        try:
            return self.get_content()
        except Exception as ex:
            print(''.join(traceback.format_exception(etype=type(ex), value=ex, tb=ex.__traceback__)))
            raise ex

    def get_content(self):
        result = {}
        build_type = self.conanfile.settings.build_type
        for dependency in self.deps_build_info.deps:
            cpp_info = self.conanfile.deps_cpp_info[dependency]
            if dependency == "qt5":
                subGenerator = MLI_Qt(cpp_info, self.conanfile.output)
            elif dependency == "python":
                subGenerator = MLI_Python(cpp_info, self.conanfile.output, build_type)
            else:
                cmake_prefix = self._get_name(cpp_info)
                if cpp_info.get_property('generate_cmake') is False:  # None is equivalent to True
                    cmake_prefix = ''
                components = [c[0] for c in self._get_components(dependency, cpp_info)] if cpp_info.components else []
                subGenerator = MLI(cpp_info, self.conanfile.output, cmake_prefix, components, build_type)
            result.update(subGenerator.get_content())
        return result


class mlabdocbook(CMakeFindPackageGenerator):
    def _list_required_by(self, cpp_info):
        res = []
        for other_name, other_cpp_info in self.conanfile.deps_cpp_info.dependencies:
            if cpp_info.name in other_cpp_info.public_deps:
                res.append(other_name)
        return res

    @property
    def filename(self):
        return "MeVisLabThirdParty.xml"


    @property
    def content(self):
        try:
            return self.get_content()
        except Exception as ex:
            print(''.join(traceback.format_exception(etype=type(ex), value=ex, tb=ex.__traceback__)))
            raise ex


    def get_content(self):
        tpl = Environment(loader=FileSystemLoader(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'templates')), trim_blocks=True, autoescape=True)
        template = tpl.get_template('ThirdParty.docbook.jinja')

        items = []

        for pkg_name, cpp_info in self.deps_build_info.dependencies:
            if pkg_name == 'conan_generator':
                    continue

            self._validate_components(cpp_info)

            name = self._get_name(cpp_info)
            if name == 'Qt5Dummy':
                name = "Qt"

            public_sdk_only = pkg_name in [
                'dirsync',
                'httmock',
                'pyyaml',
                'pyzmq',
                'requests',
                'urllib3',
                'cluster',
                'flann',
                'kissfft',
                'libzmq',
                'muparser',
                'nlohmann_json',
                'opencl',
                'opencl',
                'openigtlink',
                'pcl',
                'picojson',
                'spline',
                'vigra',
                'xylib'
            ]

            components = self._get_components(pkg_name, cpp_info) if cpp_info.components else None

            items.append({
                "cpp_info": cpp_info,
                "name": name,
                "version": cpp_info.version,
                "public_sdk_only": public_sdk_only,
                "description": cpp_info.description,
                "components": ["{p}::{c}".format(p=name, c=comp_findname) for comp_findname, _ in reversed(components)] if components else [],
                "required_by": self._list_required_by(cpp_info),
                "requires": ["{}".format(*self._get_require_name(*it)) for it in self.get_public_deps(cpp_info)]
            })

        return template.render(items=sorted(items, key=lambda d: d['name']))



class mevislab(CMakeFindPackageGenerator):
    @property
    def filename(self):
        return None

    @property
    def content(self):
        try:
            return self.get_content()
        except Exception as ex:
            print(''.join(traceback.format_exception(etype=type(ex), value=ex, tb=ex.__traceback__)))
            raise ex


    def get_content(self):
        ret = {}

        build_type = str(self.conanfile.settings.build_type).upper()

        # initialize template engine
        tpl = Environment(loader=FileSystemLoader(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'templates')), trim_blocks=True)
        tpl.globals['header_date'] = datetime.now().strftime("%d/%m/%Y")
        tpl.globals['min_cmake_version'] = "3.20.0"
        tpl.globals['build_type'] = build_type
        tpl.globals['build_type_suffix'] = "_{}".format(build_type) if build_type else ""
        tpl.globals['configs'] = ["Release", "RelWithDebInfo", "MinSizeRel", "Debug"]

        if 'python' in self.deps_build_info.deps:
            major, minor, _ = self.deps_build_info['python'].version.split('.', 3)
            tpl.globals['python_major_version'] = major
            tpl.globals['python_minor_version'] = minor
        else:
            tpl.globals['python_major_version'] = None
            tpl.globals['python_minor_version'] = None

        # load templates
        package_config_tpl = tpl.get_template('PackageConfig.jinja')
        package_config_targets_tpl = tpl.get_template('PackageConfigTargets.jinja')
        package_config_target_type_tpl = tpl.get_template('PackageConfigTargetType.jinja')
        package_config_version_tpl = tpl.get_template('PackageConfigVersion.jinja')
        thirdparty_install_target_tpl = tpl.get_template('MeVisLabInstallThirdPartyTarget.jinja')

        # Mapping pkg_name to conan package root dir - used in MeVisLabThirdPartyPaths.jinja
        package_root_dirs = {}

        for pkg_name, cpp_info in self.deps_build_info.dependencies:
            if pkg_name == 'conan_generator':
                continue

            self._validate_components(cpp_info)

            pkg_filename = self._get_filename(cpp_info)
            pkg_findname = self._get_name(cpp_info)
            deps_names = ';'.join(["{}::{}".format(*self._get_require_name(*it)) for it in self.get_public_deps(cpp_info)])
            pkg_public_deps_filenames = [self._get_filename(self.deps_build_info[it[0]]) for it in self.get_public_deps(cpp_info)]
            cpp_info = extend(cpp_info, build_type.lower())
            deps = DepsCppCmake(cpp_info, self.name)

            components = self._get_components(pkg_name, cpp_info) if cpp_info.components else None
            pkg_components = " ".join(["{p}::{c}".format(p=pkg_findname, c=comp_findname) for comp_findname, _ in reversed(components)]) if components else None

            pkg_rootpath = cpp_info.rootpath.replace('\\', '/').replace('$', '\\$').replace('"', '\\"')

            ret[f"cmake_intern/MeVisLabInstallThirdParty-{pkg_name.lower()}-{build_type}.cmake"] = thirdparty_install_target_tpl.render(
                name=pkg_name,
                rootpath=pkg_rootpath,
                bin_paths=self.unique_prefix_paths(cpp_info.bin_paths),
                lib_paths=self.unique_prefix_paths(cpp_info.lib_paths),
                res_paths=self.unique_prefix_paths(cpp_info.res_paths),
                include_paths=self.unique_prefix_paths(cpp_info.include_paths),
            )

            generate_cmake = cpp_info.get_property('generate_cmake')
            if generate_cmake or generate_cmake is None:  # default is True (when None)
                package_root_dirs[pkg_findname] = pkg_rootpath

                args = {
                    "name": pkg_findname,
                    "version": cpp_info.version,
                    "pkg_rootpath": pkg_rootpath,
                    "components": components,
                    "public_deps_names": pkg_public_deps_filenames,
                    "deps": deps,
                    "deps_names": deps_names,
                    "pkg_components": pkg_components,
                }

                ret[f"cmake_thirdparty/{pkg_filename}ConfigVersion.cmake"] = package_config_version_tpl.render(**args)
                ret[f"cmake_thirdparty/{pkg_filename}Targets.cmake"] = package_config_targets_tpl.render(**args)
                ret[f"cmake_thirdparty/{pkg_filename}Config.cmake"] = package_config_tpl.render(**args)
                ret[f"cmake_thirdparty/{pkg_filename}Target-{build_type.lower()}.cmake"] = package_config_target_type_tpl.render(**args)

                # we only have release and debug builds. Generate the other two default build types based on them:
                if build_type.lower() == "release":
                    ret[f"cmake_thirdparty/{pkg_filename}Target-relwithdebinfo.cmake"] = package_config_target_type_tpl.render(**args)
                    ret[f"cmake_thirdparty/{pkg_filename}Target-minsizerel.cmake"] = package_config_target_type_tpl.render(**args)

        ret["cmake_thirdparty/MeVisLabThirdPartyMacros.cmake"] = tpl.get_template('MeVisLabThirdPartyMacros.jinja').render()

        ret[f"cmake_intern/MeVisLabInstallThirdParty.cmake"] = tpl.get_template('MeVisLabInstallThirdParty.jinja').render()
        ret[f"cmake_intern/MeVisLabThirdPartyPaths-{build_type.lower()}.cmake"] = tpl.get_template('MeVisLabThirdPartyPathsType.jinja').render(package_root_dirs=package_root_dirs)

        ret[f"cmake_intern/MeVisLabThirdPartyPaths.cmake"] = tpl.get_template('MeVisLabThirdPartyPaths.jinja').render()

        return ret


    def unique_prefix_paths(self, paths):
        ret = []
        last = None
        for i in sorted(paths):
            if last == None or not i.startswith(last):
                ret.append(i)
                last = i

        return " ".join('"%s"' % p.replace('\\', '/').replace('$', '\\$').replace('"', '\\"') for p in ret)
