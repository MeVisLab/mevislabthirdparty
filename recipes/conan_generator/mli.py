# -*- coding: utf-8 -*-

import io
import os
import glob
import textwrap
from typing import List, Dict, Optional
from conans import tools
from conans.model.build_info import CppInfo
from conans.client.output import ScopedOutput


MLI_DIRECTORY: str = 'MeVis/ThirdParty/Configuration/Installers/Libraries'


def _is_optional(entry):
    # make pdb/debug files optional, so we don't get an error if they can't be copied
    return entry.endswith('.pdb') or entry.endswith('.debug')


def _create_add_statements(itemList):
    return "".join([(("+? " if _is_optional(entry) else "+ ") + entry + "\n") for entry in sorted(itemList)])


class MLIBaseGenerator(object):
    def __init__(self, cpp_info:CppInfo, output:ScopedOutput):
        self.name: str = cpp_info.name
        self.output = output
        self.package_folder: str = cpp_info.rootpath
        self.dependencies: List[str] = cpp_info.public_deps
        self.mli_files: Dict[str,str] = {}

    def _get_package_content(self, subdir, excludeFunc=None, prependPath=""):
        path = os.path.join(self.package_folder, subdir)
        prependPath = (prependPath + "/") if prependPath and not prependPath.endswith('/') else prependPath
        subdir = (subdir + "/") if subdir else ""
        if os.path.isdir(path):
            return [prependPath + subdir + entry for entry in os.listdir(path) if excludeFunc is None or not excludeFunc(entry)]
        elif os.path.isfile(path):
            return [prependPath + path]
        else:
            return []

    def _get_glob_package_content(self, subdir, excludeFunc=None, prependPath=""):
        result = []
        with tools.chdir(self.package_folder):
            for candidate in glob.iglob(subdir):
                result += self._get_package_content(candidate, excludeFunc=excludeFunc, prependPath=prependPath)
        return result

    def _create_includes(self, dependencies, optional=True, indent=0):
        includes = [f"INCLUDE_IF_EXISTING {dep}.mli" if optional else f"INCLUDE {dep}.mli" \
            for dep in dependencies]
        includes = ('\n' + ' '*indent).join(includes)
        return includes

    def _with_include_guard(self, code, guardName):
        guardVariable = guardName.upper() + "_INCLUDE_GUARD"
        return f"""IFNDEF {guardVariable}
  ${guardVariable} 1
{textwrap.indent(code, "  ")}
ENDIF
"""

    def get_content(self):
        # prepend target directory:
        return {os.path.join(MLI_DIRECTORY, k): v for k, v in self.mli_files.items()}
        

class MLI(MLIBaseGenerator):
    def __init__(self, cpp_info:CppInfo, output:ScopedOutput, cmake_prefix:str, components:List[str], build_type:str):
        super().__init__(cpp_info, output)
        self.mli_name: Optional[str] = cpp_info.get_property('mli_name')
        self.build_type: str = build_type
        self.components: List[str] = components
        self.cmake_prefix: str = cmake_prefix
        self._create_library_mli_files()
        

    def _create_library_mli_files(self):
        if self.mli_name == 'None':
            self.mli_name = None   # always create a .mli file now
    
        existingMliDirectory = os.path.join(self.package_folder, MLI_DIRECTORY)
        if os.path.exists(existingMliDirectory): 
            return {}

        # generate .mli files
        dependencyIncludes = self._create_includes(self.dependencies)

        mainFile = f"""
# Include possible dependencies
{dependencyIncludes}

SWITCH_PACKAGE MeVis/ThirdParty
+ ThirdPartyInformation/{self.name.lower()}

IFDEF RELEASE
  INCLUDE_IF_EXISTING {self.name}_Release.mli
ENDIF

IFDEF DEBUG
  INCLUDE_IF_EXISTING {self.name}_Debug.mli
ENDIF
"""

        self.mli_files[f"{self.name}.mli"] = self._with_include_guard(mainFile, self.name)
        if self.build_type:
            pythonImportNames = self.create_mli_content(self.build_type)
        else:
            # no different builds for Release and Debug, but we still create different files,
            # because the paths to be copied might be different in the installed SDK
            self.create_mli_content("Release")
            pythonImportNames = self.create_mli_content("Debug") # pythonImportNames should be the same, only get once


        def _normalized(name):
            # only Linux differentiates between upper and lower case in file names
            return name if tools.os_info.is_linux else name.upper()

        created_mli_names = set([_normalized(self.name)])

        def _create_redirect(name):
            if not _normalized(name) in created_mli_names:
                self.mli_files[f"{name}.mli"] = f"INCLUDE {self.name}.mli"
                created_mli_names.add(_normalized(name))

        if self.mli_name:
            _create_redirect(self.mli_name)
        elif self.cmake_prefix and not self.components:
            _create_redirect(f"{self.cmake_prefix}__{self.cmake_prefix}")
        for comp in self.components:
            # also create redirects for the components of this package
            # (for now at least; we would rather only package the DLLs for this component)
            _create_redirect(self.cmake_prefix + "__" + comp)
        for name in pythonImportNames:
            # ModuleDependencyAnalyzer was modified to prefer the "python_" prefix for Python imports,
            # this fixes some name clashes
            _create_redirect("python_" + name)

    def create_mli_content(self, variant):

        def _binExcludes(entry):
            # do not add .lib files for Windows,
            # and do also not add the whole site-packages path
            return (tools.os_info.is_windows and (entry.endswith('.lib') or entry.endswith('.exp'))) or entry in ['python', 'site-packages']

        # DLLs can have executable rights on Linux, better to check the suffix, too:
        def _hasDllSuffix(name):
            if tools.os_info.is_linux:
                return name.endswith('.so') or '.so.' in name
            elif tools.os_info.is_macos:
                name = name.lower()
                return name.endswith('.dylib') or '.dylib.' in name
            elif tools.os_info.is_windows:
                name = name.lower()
                return name.endswith('.dll')

        def _isExecutable(entry):
            return entry.endswith('.exe') or \
                (not tools.os_info.is_windows and os.access(os.path.join(self.package_folder, entry), os.X_OK) and
                 not _hasDllSuffix(entry))

        def _addRedirectableContent(subdir):
            subContent = ''
            subContentList = self._get_package_content(subdir, excludeFunc=_binExcludes)
            if subContentList:
                subContent += f"""SWITCH_PACKAGE MeVis/ThirdParty

$INPUT $(INPUT)/{subdir}
IFDEF REDIRECT_BIN_OUTPUT
  $OUTPUT $(REDIRECT_BIN_OUTPUT)
ELSE
  $OUTPUT $(OUTPUT)/{subdir}
ENDIF

"""
                subContentLibList = [entry for entry in subContentList if not _isExecutable(entry)]
                subContentExeList = [entry for entry in subContentList if _isExecutable(entry)]
                subContentLibList = [entry[len(subdir)+1:] for entry in subContentLibList]  # remove f'{subdir}/' from entries
                subContentExeList = [entry[len(subdir)+1:] for entry in subContentExeList]  # remove f'{subdir}/' from entries
                subContent += _create_add_statements(subContentLibList)
                subContent += '\n'
                if subContentExeList:
                    subContent += f'IFDEF {self.name.upper()}_TOOLS\n'
                    subContent += textwrap.indent(_create_add_statements(subContentExeList), '  ')
                    subContent += 'ENDIF\n'
                    subContent += '\n'
            return subContent

        # First add redirectable content:
        content = _addRedirectableContent('lib') + _addRedirectableContent('bin')

        # Now the stuff that goes directly to MeVis/ThirdParty:
        contentList = self._get_package_content('web', prependPath="Sources")

        # Python content:
        sitePackagesContentList, pythonImportNames, _ = self._scan_site_packages(variant)
        contentList += sitePackagesContentList

        if contentList:
            content += "SWITCH_PACKAGE MeVis/ThirdParty\n"
            content += _create_add_statements(contentList)

        if content:
            # only create if not empty
            self.mli_files[f"{self.name}_{variant}.mli"] = content

        return pythonImportNames


    def _scan_site_packages(self, variant:str):
        """
        This method returns the content of an optional site-packages directory,
        the top-level import names derived from this, and the path prefix where these
        will be installed in the SDK.
        """

        def _pythonExcludes(entry):
            return entry == '__pycache__'

        # Python content:
        pythonImportNames = []
        if tools.os_info.is_windows:
            sitePackagesContentList = self._get_package_content('Lib/site-packages', excludeFunc=_pythonExcludes)
            pythonPrefix = 'Python/'
        else:
            sitePackagesContentList = self._get_glob_package_content('lib/python*/site-packages/', excludeFunc=_pythonExcludes)
            pythonPrefix = f'Python/{variant}/'

        # extract import names:
        for entry in sitePackagesContentList:
            if not entry.endswith('-info'):
                fullName = self.package_folder + '/' + entry
                importName = entry.split('/')[-1]
                if importName.endswith('.py'):
                    importName = importName[:-3]
                elif not os.path.isdir(fullName) or importName == '__pycache__':
                    # This excludes everything that isn't a .py file or a directory not ending with -info
                    # which also excludes e.g. .pyd files. pyodbc is such a project, but luckily there the
                    # project name matches the import name anyway .
                    continue
                pythonImportNames += [importName]

        # Python has its own sub-directory in the installed SDK:
        sitePackagesContentList = [pythonPrefix + entry for entry in sitePackagesContentList]
        
        return sitePackagesContentList, pythonImportNames, pythonPrefix


class MLI_Python(MLI):
    def __init__(self, cpp_info:CppInfo, output:ScopedOutput, build_type:str):
        super().__init__(cpp_info, output, 'Python3', ['Python'], build_type)

    def create_mli_content(self, variant):
        sitePackagesContentList, pythonImportNames, pythonPrefix = self._scan_site_packages(variant)
        
        content="SWITCH_PACKAGE MeVis/ThirdParty\n"
        if tools.os_info.is_windows:
            def notDllOrExe(name):
                name = name.lower()
                return not name.endswith(".exe") and not name.endswith(".dll") and not name.endswith(".pdb")
            
            # Add Python interpreter executable and DLLs explicitly
            exeContent = self._get_package_content("", prependPath=pythonPrefix, excludeFunc=notDllOrExe)
            content += _create_add_statements(exeContent)
            content += """
+ Python/DLLs
+ Python/Scripts
+ Python/Lib
- Python/Lib/site-packages
"""
        else:
            # Unix
            content += f"""
+ Python/{variant}/bin
+ Python/{variant}/lib
- Python/{variant}/lib/python*/site-packages
"""
        content += _create_add_statements(sitePackagesContentList)
        self.mli_files[f"{self.name}_{variant}.mli"] = content
        return pythonImportNames
