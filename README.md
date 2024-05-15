# MeVisLab ThirdParty

Recipes for MeVisLab Thirdparty packages

The `recipes` directory contains all recipes. The overall build order is currently defined in the `build_configuration.yml`.

## Local package development

### Preconditions

First of all we need [Python >=3.10 and Pip](https://www.python.org/).
Currently we recommend Python 3.11.

Check the installed versions with:
```
python -V
pip --version
```

Note that on POSIX platforms the Python 3 executable is called `python3`, while under Windows it is called `python`. 
Additionally, under POSIX, `pip3` is not installed per default, while under Windows it is installed with Python as `pip`. 
To be compatible with Windows _(yes, that's the wrong way around - blame MS!)_, we currently need the `python` and `pip` symlinks point to `python3` and `pip3` _(or better `python3 -m pip`)_ respectively.  Everything else may work, but has not been tested.

Note also that on current Windows versions [Microsoft hijacks](https://docs.microsoft.com/en-us/windows/python/faqs#why-does-running-pythonexe-open-the-microsoft-store) the `python` and `python3` executables.


### Install Conan

[Conan](https://conan.io) is the package manager used to build our third party libraries.
On Windows, use:
```
python -m pip install -U conan packaging spdx-license-list tomli
```

On Linux, use:
```
pip3 install -U conan packaging spdx-license-list tomli pyelftools
```


## Build a package

To build the debug and release versions of a package:
```
cd recipes/<recipe_name>
conan create -s build_type=Debug .
conan create -s build_type=Release .
```

If you have the `conan-config` package installed (MeVisLab internal only, see README.md in the main MeVisLab directory), you can instead use:
```
cd recipes/<recipe_name>
conan tp:build .
```
to build both the debug and release packages.


To fetch the package sources (includes applying patches):
```
cd recipes/<recipe_name>
conan source .
```


## Jenkins Integration

### Pipeline Description
There are mainly two Jenkins files that control the build of all thirdparty libraries and tools: `Jenkinsfile` and `JenkinsfileLibrary` (both in the repository root). The first file parses `build_configuration.yml` and triggers the sequential build of all tiers, starting with tier0. For further details see the chapter _Build Configuration_.

The conan package system is written in a way that it checks if the package itself or one of its dependencies has been changed since the last successful build. If nothing has changed, then the build and archiving step is skipped.
Since even this check takes a certain amount of time, an additional optimization has been implemented. All changed files are collected since the last successful build of the complete thirdparty/branch build. And only those directly affected projects and the tiers below are triggered to be rebuild. This shortens the build time enormously. If one of the files `Jenkinsfile`, `JenkinsfileLibrary`, or `build_configuration.yml` is part of any changeset, then this optimization is skipped and all tiers with all projects are build.

### Build Configuration
The build configuration is described in the `build_configuration.yml` file, which references all the libraries and tools needed to build MeVisLab.
Organizing the dependencies can be very tedious and cumbersome, especially when attempting to describe the smallest possible dependency graph.
To simplify this, dependencies are broken down into different tiers, with the content of each tier organized according to the dependencies of the individual libraries and tools.
For instance, if library A depends on another library B, then B must be referenced in one of the upper tiers (e.g. a tier with a lower number).

The build of each library and tool for all specified platforms and build types must finish within a defined time frame. There is a default timeout that is used for all packages.
However, if a certain package requires significantly more time, there is the possibility to define a timeout exception.

These are the parameters that are defined in the file:

| Parameter | Description |
| --------- | ------------|
| timeout_default: | Default time in minutes for all packages not specified otherwise |
| timeout_exception: | A map of all packages with their individual timeouts |
| tiers: | An ordered list of all tiers, starting with tier0 |
