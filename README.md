# MeVisLab ThirdParty

Recipes for MeVisLab Thirdparty packages

The `recipes` directory contains all recipes.

## Local package development
### Preconditions

First of all [Python >=3.9 and Pip](https://www.python.org/) is needed.

```
python -V
pip --version
```

Note that on all platforms except Windows the Python 3 executables are mostly called `python3` and `pip3`. `python` or `pip` don't exist at all. But to be compatible with Windows, currently is is needed that `python` and `pip` have symlinks point to `python3` and `pip3` _(or better `python3 -m pip`)_ respectively.  Everything else may work, but has not been tested.

Note also that on current Windows versions [Microsoft hijacks](https://docs.microsoft.com/en-us/windows/python/faqs#why-does-running-pythonexe-open-the-microsoft-store) the `python` and `python3` executables.


### Install Conan

[Conan](https://conan.io) is the package manager used to build all third party libraries.
MeVisLab 3.5.0 is currently build with Conan version 1.41.0.

The package can be installed using pip:
```
python -m pip install -U conan
```

Now conan should respond with its installed version by calling:
```
conan --version
```

## Build a package

```
cd recipes/<recipe_name>
conan create .
```