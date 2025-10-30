import glob
import os
import re
import textwrap

from conan.internal.model.conanfile_interface import ConanFileInterface
from conan.tools.files import chdir

MLI_DIRECTORY: str = "MeVis/ThirdParty/Configuration/Installers/Libraries"

PYTHON_UNIX_DIR_RE: re.Pattern = re.compile(r"python\d\.\d+")


def _is_optional(entry):
    # make pdb/debug files optional, so we don't get an error if they can't be copied
    return entry.endswith(".pdb") or entry.endswith(".debug")


def _create_add_statements(itemList):
    return "".join([(("+? " if _is_optional(entry) else "+ ") + entry + "\n") for entry in sorted(itemList)])


def _is_empty_dir(path, subpath=None):
    """Return if subpath of path is a directory not containing any files, not even in sub-directories."""
    if subpath:
        path = os.path.join(path, subpath)
    if os.path.isdir(path):
        return all([_is_empty_dir(path, entry) for entry in os.listdir(path)])
    else:
        return False


class MLIBaseGenerator:
    def __init__(self, conanfile: ConanFileInterface, library: ConanFileInterface, package_id: str):
        self.conanfile = conanfile
        self.library = library
        self.dependencies = library.dependencies.direct_host
        self.package_id = package_id
        self.mli_directory = package_id + "/Configuration/Installers/Libraries"
        self.name: str = library.ref.name
        self.is_linux: bool = self.conanfile.settings.os == "Linux"
        self.is_macos: bool = self.conanfile.settings.os == "Macos"
        self.is_windows: bool = self.conanfile.settings.os == "Windows"
        self.mli_files: dict[str, str] = {}
        self.external_mli_files: dict[str, str] = {}  # mapping from dependency name to package_id
        self.has_package = self.library.package_folder is not None  # False for skipped packages

    def _get_package_dir_content(self, subdir, excludeFunc=None, prependPath=""):
        if not self.has_package:
            return []
        path = os.path.join(self.library.package_folder, subdir)
        prependPath = (prependPath + "/") if prependPath and not prependPath.endswith("/") else prependPath
        subdir = (subdir + "/") if subdir else ""
        if os.path.isdir(path):
            return [
                prependPath + subdir + entry
                for entry in os.listdir(path)
                if not _is_empty_dir(path, entry) and (excludeFunc is None or not excludeFunc(entry))
            ]
        elif os.path.isfile(path):
            return [prependPath + path]
        else:
            return []

    def _get_glob_package_dir_content(self, subdir, excludeFunc=None, prependPath=""):
        result = []
        if not self.has_package:
            return result
        with chdir(self.conanfile, self.library.package_folder):
            for candidate in glob.iglob(subdir):
                result += self._get_package_dir_content(candidate, excludeFunc=excludeFunc, prependPath=prependPath)
        return result

    def set_external_mli_files(self, mli_files: dict[str, str]):
        """
        Sets a dict that maps dependency names to package names in which they are defined.
        This is used to include .mli for libraries in other packages correctly.
        """
        self.external_mli_files = mli_files

    def _create_includes(self, dependencies, optional=True, indent=0):
        includes = []
        cmd = "INCLUDE_IF_EXISTING" if optional else "INCLUDE"
        for dep in dependencies:
            path = f"{dep}.mli"
            if dep in self.external_mli_files:
                # include from other package
                path = (
                    f"$(MLAB_{self.external_mli_files[dep].replace('/','_')})/Configuration/Installers/Libraries/{path}"
                )
            includes.append(f"{cmd} {path}")
        includes = ("\n" + " " * indent).join(includes)
        return includes

    def guard_name(self, suffix):
        return self.name.upper().replace("-", "_") + suffix

    def _with_include_guard(self, code):
        guardVariable = self.guard_name("_INCLUDE_GUARD")
        return f"""IFNDEF {guardVariable}
  ${guardVariable} 1
{textwrap.indent(code, "  ")}
ENDIF
"""

    def _create_library_mli_files(self):
        """Override this in derived classes."""

    def get_content(self):
        self._create_library_mli_files()
        # prepend target directory:
        return {os.path.join(self.mli_directory, k): v for k, v in self.mli_files.items()}


class MLI(MLIBaseGenerator):
    def __init__(self, conanfile: ConanFileInterface, library: ConanFileInterface, package_id: str):
        super().__init__(conanfile, library, package_id)
        self.build_type: str = conanfile.settings.get_safe("build_type")
        self.otherStuff: list[str] = []

    def get_cmake_target_names(self) -> list[str]:
        """
        Get list of all usable CMake target names, to create mli redirects
        (as these are used by the mldepends mechanism).
        """

        def _get_component_target_names(name, cpp_info):
            if self.library.cpp_info.get_property("cmake_find_mode") == "none":
                return []
            primary_name = cpp_info.get_property("cmake_target_name")
            if primary_name is None:
                primary_name = self.name + "::" + name
            name_list = [primary_name]
            aliases_list = cpp_info.get_property("cmake_target_aliases")
            if aliases_list:
                name_list.extend(aliases_list)
            return name_list

        cmake_target_names = _get_component_target_names(self.name, self.library.cpp_info)
        for name, comp in self.library.cpp_info.components.items():
            # also create redirects for the components of this package
            # (for now at least; we would rather only package the DLLs for this component)
            cmake_target_names += _get_component_target_names(name, comp)
        return cmake_target_names

    def get_dependencies(self) -> list[str]:
        """Get list of dependencies to include in the mli file."""
        return [dep.ref.name for dep in self.dependencies.values()]

    def is_tool(self, full_path):
        """
        Check if a file should be treated as an (optional) tool.
        Usually all executables are tools, but this method can be overridden for fine-tuning.
        """

        # DLLs can have executable rights on Linux, better to check the suffix, too:
        def _hasDllSuffix(name):
            if self.is_linux:
                return name.endswith(".so") or ".so." in name
            elif self.is_macos:
                name = name.lower()
                return name.endswith(".dylib") or ".dylib." in name
            elif self.is_windows:
                name = name.lower()
                return name.endswith(".dll")

        if full_path.endswith((".exe", ".bat", ".sh")) or (
            not self.is_windows
            and os.access(os.path.join(self.library.package_folder, full_path), os.X_OK)
            and not _hasDllSuffix(full_path)
        ):
            return True
        if self.is_windows and full_path.endswith(".pdb"):
            # PDBs should have the same state as the executable (if any) to which they belong:
            exeName = os.path.splitext(full_path)[0] + ".exe"
            if os.path.exists(exeName) and self.is_tool(exeName):
                return True
        elif self.is_linux and full_path.endswith(".debug"):
            # same as above, for Linux:
            exeName = os.path.splitext(full_path)[0]
            if os.path.exists(exeName) and self.is_tool(exeName):
                return True
        return False

    def _create_library_mli_files(self):
        if self.has_package and (self.library.package_path / self.mli_directory).exists():
            return

        # generate .mli files
        dependencyIncludes = self._create_includes(self.get_dependencies())

        mainFile = f"""
IFDEF EXCLUDE_{self.name.upper()}
  PRINT Note: {self.name} was explicitly excluded from the installer!
ELSE
  # Include possible dependencies
{textwrap.indent(dependencyIncludes, "  ")}

  SWITCH_PACKAGE {self.package_id}
  + ThirdPartyInformation/{self.name.lower()}

  IFDEF RELEASE
    INCLUDE_IF_EXISTING {self.name}_Release.mli
  ENDIF

  IFDEF DEBUG
    INCLUDE_IF_EXISTING {self.name}_Debug.mli
  ENDIF
ENDIF
"""

        self.mli_files[f"{self.name}.mli"] = self._with_include_guard(mainFile)
        if self.build_type:
            pythonImportNames = self.create_mli_content(self.build_type)
        else:
            # no different builds for Release and Debug, but we still create different files,
            # because the paths to be copied might be different in the installed SDK
            self.create_mli_content("Release")
            pythonImportNames = self.create_mli_content("Debug")  # pythonImportNames should be the same, only get once

        def _normalized(name):
            # only Linux differentiates between upper and lower case in file names
            return name if self.is_linux else name.upper()

        created_mli_names = {_normalized(self.name)}

        def _create_redirect(name):
            if not _normalized(name) in created_mli_names:
                self.mli_files[f"{name}.mli"] = f"INCLUDE {self.name}.mli"
                created_mli_names.add(_normalized(name))

        redirect_list = []
        mli_name = self.library.cpp_info.get_property("mli_name")
        if mli_name:
            redirect_list.append(mli_name)
        redirect_list += self.get_cmake_target_names()
        # ModuleDependencyAnalyzer was modified to prefer the "python_" prefix for Python imports,
        # this fixes some name clashes
        redirect_list += ["python_" + name for name in pythonImportNames]
        for redirect in redirect_list:
            _create_redirect(redirect.replace(":", "_"))

    def create_mli_content(self, build_type):
        """
        Create .mli sub-file for the given build_type. Also returns a list of
        python import names found in the process, to create suitable redirects.
        """

        def _binExcludes(entry):
            # do not add .lib files for Windows,
            # and do also not add the whole site-packages path
            return (
                (self.is_windows and (entry.endswith(".lib") or entry.endswith(".exp") or entry.endswith(".prl")))
                or entry.endswith(".cmake")
                or entry in ["python", "site-packages", "cmake"]
                or PYTHON_UNIX_DIR_RE.fullmatch(entry)
            )

        def _redirectableBinContent(subdir):
            """
            Create content to copy content of bin or lib dir.
            The output can be redirected to the directory in the REDIRECT_BIN_OUTPUT variable.
            Some file types are automatically suppressed.
            """
            subContent = ""
            subContentList = self._get_package_dir_content(subdir, excludeFunc=_binExcludes)
            if subContentList:
                subContent += f"""SWITCH_PACKAGE {self.package_id}

$INPUT $(INPUT)/{subdir}
IFDEF REDIRECT_BIN_OUTPUT
  $OUTPUT $(REDIRECT_BIN_OUTPUT)
ELSE
  $OUTPUT $(OUTPUT)/{subdir}
ENDIF

"""
                subContentLibList = [entry for entry in subContentList if not self.is_tool(entry)]
                subContentToolList = [entry for entry in subContentList if self.is_tool(entry)]
                # remove f'{subdir}/' from entries:
                subContentLibList = [entry[len(subdir) + 1 :] for entry in subContentLibList]
                subContentToolList = [entry[len(subdir) + 1 :] for entry in subContentToolList]
                subContent += _create_add_statements(subContentLibList)
                subContent += "\n"
                if subContentToolList:
                    subContent += f"IFDEF {self.guard_name('_TOOLS')}\n"
                    subContent += textwrap.indent(_create_add_statements(subContentToolList), "  ")
                    subContent += "ENDIF\n"
                    subContent += "\n"
            return subContent

        def _otherRedirectableContent(subdir):
            """
            This method copies the given subdir into the given output directory, unlike
            _redirectableBinContent, which copies the content.
            """
            subContent = ""
            subContentList = self._get_package_dir_content(subdir)
            if subContentList:
                subContent += _create_add_statements(subContentList)
                subContent += "\n"
            return subContent

        # First add binary redirectable content:
        if self.has_package:
            content = _redirectableBinContent("lib") + _redirectableBinContent("bin")
        else:
            content = ""

        # Then add other redirectable content, which stays in its sub-directory (this is used for Qt):
        hasSwitched = False
        for d in self.otherStuff:
            otherContent = _otherRedirectableContent(d)
            if otherContent and not hasSwitched:
                content += f"""SWITCH_PACKAGE {self.package_id}

IFDEF REDIRECT_BIN_OUTPUT
  $OUTPUT $(REDIRECT_BIN_OUTPUT)
ENDIF

"""
                hasSwitched = True
            content += otherContent

        # Now the stuff that goes directly to MeVis/ThirdParty (or whatever the target package is):
        contentList = self._get_package_dir_content("web", prependPath="Sources")

        # Python content:
        sitePackagesContentList, pythonImportNames, _ = self._scan_site_packages(build_type)
        contentList += sitePackagesContentList

        if contentList:
            content += f"SWITCH_PACKAGE {self.package_id}\n"
            content += _create_add_statements(contentList)

        if content:
            # only create if not empty
            self.mli_files[f"{self.name}_{build_type}.mli"] = content

        return pythonImportNames

    def _scan_site_packages(self, build_type: str):
        """
        This method returns the content of an optional site-packages directory,
        the top-level import names derived from this, and the path prefix where these
        will be installed in the SDK.
        """

        def _pythonExcludes(entry):
            return entry == "__pycache__"

        # Python content:
        pythonImportNames = []
        if self.is_windows:
            sitePackagesContentList = self._get_package_dir_content("Lib/site-packages", excludeFunc=_pythonExcludes)
            pythonPrefix = "Python/"
        else:
            sitePackagesContentList = self._get_glob_package_dir_content(
                "lib/python*/site-packages/", excludeFunc=_pythonExcludes
            )
            pythonPrefix = f"Python/{build_type}/"

        # extract import names:
        for entry in sitePackagesContentList:
            if not entry.endswith("-info"):  # egg-info or dist-info
                fullName = self.library.package_folder + "/" + entry
                importName = entry.split("/")[-1]
                if importName.endswith(".py"):
                    importName = importName[:-3]
                elif not os.path.isdir(fullName) or importName == "__pycache__":
                    # This excludes everything that isn't a .py file or a directory not ending with -info
                    # which also excludes e.g. .pyd files. pyodbc is such a project, but luckily there the
                    # project name matches the import name anyway .
                    continue
                pythonImportNames.append(importName)

        # Python has its own sub-directory in the installed SDK:
        sitePackagesContentList = [pythonPrefix + entry for entry in sitePackagesContentList]

        return sitePackagesContentList, pythonImportNames, pythonPrefix


class MLI_Python(MLI):

    def create_mli_content(self, build_type):
        sitePackagesContentList, pythonImportNames, pythonPrefix = self._scan_site_packages(build_type)

        content = f"SWITCH_PACKAGE {self.package_id}\n"
        if self.is_windows:

            def notDllOrExe(name):
                name = name.lower()
                return not name.endswith((".exe", ".dll", ".pdb"))

            # Add Python interpreter executable and DLLs explicitly, because we should not add "*"
            exeContent = self._get_package_dir_content("", prependPath=pythonPrefix, excludeFunc=notDllOrExe)
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
+ Python/{build_type}/bin
+ Python/{build_type}/lib
- Python/{build_type}/lib/python*/site-packages
"""
        content += _create_add_statements(sitePackagesContentList)
        self.mli_files[f"{self.name}_{build_type}.mli"] = content
        return pythonImportNames


class MLI_Qt(MLI):

    def __init__(self, conanfile, library, package_id: str):
        super().__init__(conanfile, library, package_id)
        self.qt_name: str = "Qt6"
        self.otherStuff: list[str] = ["plugins", "resources", "translations", "qml", "libexec"]

    def get_cmake_target_names(self):
        """Must look into the CMake files generated by Qt itself."""
        targets: list[str] = []
        cmakePath = self.library.package_path / "lib" / "cmake"
        name_len = len(self.qt_name)
        for fullPath in cmakePath.iterdir():
            fileName = fullPath.name
            # CMake link targets each have their own sub-directory, but we
            # require certain files to exist to accept this as a target name
            if (
                fullPath.is_dir()
                and fileName.startswith(self.qt_name)
                and len(fileName) > name_len
                and (fullPath / f"{fileName}Dependencies.cmake").exists()
                and (fullPath / f"{fileName}Targets.cmake").exists()
            ):
                targets.append(self.qt_name + "::" + fileName[name_len:])
        return targets

    def is_tool(self, full_path):
        # Do not treat QtWebEngineProcess as an optional tool
        return super().is_tool(full_path) and not os.path.basename(full_path).startswith("QtWebEngineProcess")
