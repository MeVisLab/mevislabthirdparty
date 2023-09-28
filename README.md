# MeVisLab ThirdParty

Recipes for MeVisLab Thirdparty packages

The `recipes` directory contains all recipes. The overall build order is currently defined in the `build_configuratuion.yml`.

## Local package development

### Preconditions

First of all we need [Python >=3.9 and Pip](https://www.python.org/).

```
python -V
pip --version
```

Note that on all platforms except Windows the Python 3 executables are mostly called `python3` while `pip3`/`pip` don't exist at all. But to be compatible with Windows _(yes, that's the wrong way around - blame MS!)_, we currently need the `python` and `pip` symlinks point to `python3` and `pip3` _(or better `python3 -m pip`)_ respectively.  Everything else may work, but has not been tested.

Note also that on current Windows versions [Microsoft hijacks](https://docs.microsoft.com/en-us/windows/python/faqs#why-does-running-pythonexe-open-the-microsoft-store) the `python` and `python3` executables.


### Install Conan

[Conan](https://conan.io) is the package manager used to build our third party libraries.
Additionally, we are using [Conan Package Tools](https://github.com/conan-io/conan-package-tools) to generate multiple binary packages from a recipe with ease.

Both packages can be installed using pip:
```
python -m pip install -U conan conan-package-tools
```

Now conan should be installed:
```
conan --version
```

### Install MeVisLab Build Tool

`mbt`, the MeVisLab Build Tool, is a small wrapper for Conan and the Conan Package Tools.
It mainly ensures that Conan is properly configured and initialized before invoking conan itself.

```
python -m pip install -U git+http://gitlab.mevis.lokal/mevislab/mbt.git
```

## Build a package

### Using mbt, conan-package-tools or conan

All wrappers (`mbt`, `conan-package-tools`) are just convenience.
They make certain things easier, while making advanced things very difficult.
That seems to be the nature of wrappers. Therefore it is always possible to
work without these tools.

So a recipe can be built directly with `mbt`:

```
cd recipes/<recipe_name>
mbt build
```

_Note_: If you are building under Windows, have several Visual Studio versions installed and want to use _not_ the
newest one, you have to set an environment variable with the desired version to communicate this to `mbt`:
```
SET CONAN_VISUAL_VERSIONS=16
```

Or using `conan-package-tools`:
```
cd recipes/<recipe_name>
./build.py
```

Or using `conan`:
```
cd recipes/<recipe_name>
conan create .
```

## Jenkins Integration

### Pipeline Description
There are mainly two Jenkinsfiles that control the build of all thirdparty library and tools: Jenkinsfile and JenkinsfileLibrary. The first parses the `build_configuration.yml` and triggers the build of one tier after the other, starting with tier0. For further details see the chapter Build Configuration

The conan package system is written in a way that it checks if the package itself or one of its dependencies has been changed since the last successful build. If nothing has changed then the build and archiving step is been skipped.
Since even this check takes a certain amount of time, an additional optimization has been implemented. All changed files are collected since the last successful build of the complete thirdparty/branch build. And only those directly affected projects and the tiers below are triggered to be rebuild. This shortens the build time enormously. If one of the files `Jenkinsfile`, `JenkinsfileLibrary`, or `build_configuration.yml` is part of any changeset, then this optimisation is skipped and all tiers with all projects are build.

### Build Configuration
The build configuration is organised in the `build_configuration.yml` file. All libraries and tools that are needed to build MeVisLab are organised in this file. Since it very tedios and cumpersome to descripe smallest possible dependecy graph, the dependencies are broken down in different tiers. The content of the different tier is organised according to the dependencies of the individual libraries and tools. So if a e.g. a library A depends on an other library B, then B must be referenced in an one of the upper tiers.

The build of each library and tool for all specified platform and build types must finish in a defined time. There is a default, that is been used for all packages. In case that a certain package needs much more time, e.g. qt5, then there is the possibility to define a timeout exception.

These are the parameters that are defined in the file:

| Parameter | Description |
| --------- | ------------|
| timeout_default: | Default time in minutes for all not other specified packages. |
| timeout_exception: | A map of all packages with their individual timeouts. |
| tiers: | It must contain an ordered list of all tiers, starting with tier0 |
