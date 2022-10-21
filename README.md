# MeVisLab ThirdParty

Recipes for MeVisLab Thirdparty packages

The `recipes` directory contains all recipes.

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

## Build a package

```
cd recipes/<recipe_name>
conan create .
```
