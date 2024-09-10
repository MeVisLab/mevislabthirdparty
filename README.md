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

To fetch the package sources (includes applying patches):
```
cd recipes/<recipe_name>
conan source .
```
