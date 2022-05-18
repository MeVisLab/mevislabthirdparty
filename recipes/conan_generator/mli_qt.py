# -*- coding: utf-8 -*-

import io
import os
import re
import textwrap
from typing import List, Dict, Optional
from conans import tools
from conans.model.build_info import CppInfo
from mli import *

class _QtComponent(object):
    def __init__(self, name, dependencies=None, plugins=None, lib_executables=None, other=None):
        self.name = name
        self.qt_dependencies = []
        self.dependencies = []
        self.plugins = []
        self.lib_executables = []
        self.other = []

    def addQtDependencies(self, dep):
        if isinstance(dep, (list, tuple)):
            self.qt_dependencies.extend(dep)
        else:
            self.qt_dependencies.append(dep)

    def addDependencies(self, dep):
        if isinstance(dep, (list, tuple)):
            self.dependencies.extend(dep)
        else:
            self.dependencies.append(dep)

    def addPlugins(self, plugin):
        if isinstance(plugin, (list, tuple)):
            self.plugins.extend(plugin)
        else:
            self.plugins.append(plugin)

    def addLibExecutables(self, executables):
        if isinstance(executables, (list, tuple)):
            self.lib_executables.extend(executables)
        else:
            self.lib_executables.append(executables)

    def addOther(self, other):
        if isinstance(other, (list, tuple)):
            self.other.extend(other)
        else:
            self.other.append(other)


class MLI_Qt(MLIBaseGenerator):
    def __init__(self, cpp_info:CppInfo, output:ScopedOutput):
        super().__init__(cpp_info, output)
        self.qt_name: str = 'Qt5'
        self.components: Dict[str, _QtComponent] = {}
        self._set_additional_info()
        self._create_library_mli_files()

    def _set_additional_info(self):
        # Things that can't be derived from the cmake files:
        self._set_component("Core",         dependencies=["zlib", "pcre2", "double-conversion", "icu", "libxslt"],
                                            plugins=["platforms", "generic"])
        self._set_component("Gui",          dependencies=["libjpeg", "tiff", "libpng", "webp"],
                                            plugins=["iconengines", "imageformats"])
        self._set_component("Widgets",      plugins=["styles"] if tools.os_info.is_windows else [])
        self._set_component("Network",      dependencies=["openssl"],
                                            plugins=["bearer"])
        self._set_component("Sql",          dependencies=["sqlite3", "libpq"],
                                            plugins=["sqldrivers"])
        self._set_component("3DCore",       dependencies=["assimp"],
                                            plugins=["geometryloaders", "scenegraph", "sceneparsers"])
        self._set_component("PrintSupport", plugins=["printsupport"])
        self._set_component("Multimedia",   dependencies=["libalsa"], # only on Linux, will not exist on other platforms
                                            plugins=["audio", "mediaservice", "playlistformats"])
        self._set_component("TextToSpeech", plugins=["texttospeech"])
        self._set_component("Qml",          plugins=["qmltooling"],
                                            other=["qml"])
        self._set_component("Gamepad",      plugins=["gamepad"])
        self._set_component("WebView",      plugins=["webview"])
        self._set_component("WebEngineCore",lib_executables=["QtWebEngineProcess"],
                                            other=["resources", "translations/qtwebengine_locales"])

    def _get_component(self, name):
        if name not in self.components:
            self.components[name] = _QtComponent(name)
        return self.components[name]

    def _set_component(self, name, dependencies=None, plugins=None, lib_executables=None, other=None):
        comp = self._get_component(name)
        if dependencies:
            comp.addDependencies(dependencies)
        if plugins:
            comp.addPlugins(plugins)
        if lib_executables:
            comp.addLibExecutables(lib_executables)
        if other:
            comp.addOther(other)

    def _create_library_mli_files(self):
        self._scan_cmake_files()
        self._check_all_dependencies_are_used()
        # now create the .mli files for all Qt components:
        for comp in self.components.keys():
            self._create_qt_mli_files(comp)
        # finally create a file that will be used by all other projects that link against Qt:
        # (this redirect is an approximation of what will be required in most cases)
        self.mli_files[f"{self.name}.mli"] = f"""
INCLUDE {self.qt_name}__OpenGL.mli
INCLUDE {self.qt_name}__Network.mli
"""

    def _scan_cmake_files(self):
        cmakeFolder = os.path.join(self.package_folder, "lib", "cmake")
        anyFound = False
        for fullName in os.listdir(cmakeFolder):
            if len(fullName) > 3:
                componentName = fullName[3:]
                component = self._get_component(componentName)
                cmakeFile = os.path.join(cmakeFolder, fullName, f"{fullName}Config.cmake")
                with open(cmakeFile, "r", encoding="latin1") as f:
                    cmakeContent = f.read(-1)
                    # extract module dependencies from cmake statements:
                    match = re.compile(fr'set\(_{fullName}_MODULE_DEPENDENCIES "([^"]*)"\)').search(cmakeContent)
                    moduleDeps = match.group(1).split(";") if match and match.group(1) else []
                    component.addQtDependencies(moduleDeps)
                    anyFound = True
        if not anyFound:
            self.output.error(f"Did not find any relevant CMake files in {cmakeFolder}!")

    def _check_all_dependencies_are_used(self):
        # make sure we miss no dependencies from the recipe:
        unused_deps = set(self.dependencies)
        for comp in self.components.values():
            unused_deps -= set(comp.dependencies)
        if unused_deps:
            unused_deps = sorted(list(unused_deps))
            self.output.warn("Unused Qt third-party dependencies: " + ', '.join(unused_deps))
            self.output.warn("They will be added to Core for now. "
                "Please adapt the MLI_Qt generator, method set_additional_info!")
            self._set_component("Core", unused_deps)        

    def _create_qt_mli_files(self, componentName):
        is_windows = tools.os_info.is_windows
        includeGuardName = f"{self.qt_name.upper()}_{componentName.upper()}_INCLUDE_GUARD"
        component = self.components[componentName]
        
        qtDependencyIncludes = self._create_includes([f"{self.qt_name}__{dep}" for dep in component.qt_dependencies],
            optional=False)
        otherDependencyIncludes = self._create_includes(component.dependencies)
        dependencyIncludes = '\n'.join([qtDependencyIncludes, otherDependencyIncludes])

        # collect statements for the bin directory on Windows, lib on Unix:
        moreCollectStatements = ""
        if component.lib_executables and is_windows:
            for exe in component.lib_executables:
                moreCollectStatements += f"+ {exe}.exe\n"

        # collect other stuff from MeVis/ThirdParty
        otherStatements = ""
        if component.plugins or component.other or (component.lib_executables and not is_windows):
            otherStatements += f"""SWITCH_PACKAGE MeVis/ThirdParty
IFDEF REDIRECT_BIN_OUTPUT
  $OUTPUT $(REDIRECT_BIN_OUTPUT)
ENDIF
"""
            for plugin in component.plugins:
                otherStatements += f"+ plugins/{plugin}\n"
            for other in component.other:
                otherStatements += f"+ {other}\n"
            if not is_windows:
                for exe in component.lib_executables:
                    otherStatements += f"+ libexec/{exe}\n"
            
        subdir = "bin" if is_windows else "lib"
        fileContent = f"""
# Include possible dependencies
{dependencyIncludes}
SWITCH_PACKAGE MeVis/ThirdParty
+ ThirdPartyInformation/{self.name}

$INPUT $(INPUT)/{subdir}
IFDEF REDIRECT_BIN_OUTPUT
  $OUTPUT $(REDIRECT_BIN_OUTPUT)
ELSE
  $OUTPUT $(OUTPUT)/{subdir}
ENDIF

IFDEF RELEASE
  + $(DLLPREFIX){self.qt_name}{componentName}.$(QT_DLLSUFFIX)
ENDIF

IFDEF DEBUG
  + $(DLLPREFIX){self.qt_name}{componentName}d.$(QT_DLLSUFFIX)
ENDIF

{moreCollectStatements}
{otherStatements}
"""
        fullName = f"{self.qt_name}__{componentName}"
        self.mli_files[fullName + ".mli"] = self._with_include_guard(fileContent, fullName)
        
