/*************************************************************************************
**
** Copyright 2010, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/

#include "Python.h"

static PyMethodDef NoMethods[] = {
    {nullptr, nullptr, 0, nullptr}        /* Sentinel */
};

static void addModuleToDict(PyObject* dict, const char* moduleName) {
  PyObject* module = PyImport_ImportModule(moduleName);
  if (module) {
    PyObject* moduleDict = PyModule_GetDict(module);
    PyDict_Merge(dict, moduleDict, false);
    Py_DECREF(module);
  }
}

#if PY_MAJOR_VERSION >= 3

static PyModuleDef QtModuleDef = {
  PyModuleDef_HEAD_INIT,
  "Qt",
  nullptr,
  -1,
  NoMethods,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};

  #define Py_2_3_InitModFunc(name) PyInit_##name(void)
  #define Py_2_3_ModuleInit(name) PyModule_Create(&QtModuleDef)

#else
  #define Py_2_3_InitModFunc(name) init##name(void)
  #define Py_2_3_ModuleInit(name) Py_InitModule(name, NoMethods)
#endif


#ifdef UNIX
PyMODINIT_FUNC
Py_2_3_InitModFunc(Qt) ML_LIBRARY_EXPORT_ATTRIBUTE ;
#endif

PyMODINIT_FUNC
Py_2_3_InitModFunc(Qt)
{
  PyObject* module = Py_2_3_ModuleInit("Qt");
  PyObject* dict = PyModule_GetDict(module);
  addModuleToDict(dict, "PythonQt.QtCore");
  addModuleToDict(dict, "PythonQt.QtGui");
  // I decided to only have QtCore and QtGui inside of the Qt module,
  // in contrast to PyQt4 and PySide, who add all Qt modules.
  // I think this will avoid that everyone uses the Qt module
  // instead of importing the correct submodule

//  addModuleToDict(dict, "PythonQt.QtNetwork");
//  addModuleToDict(dict, "PythonQt.QtSvg");
//  addModuleToDict(dict, "PythonQt.QtSql");
//  addModuleToDict(dict, "PythonQt.QtXml");
//  addModuleToDict(dict, "PythonQt.QtOpenGL");
//  addModuleToDict(dict, "PythonQt.QtWebKit");
//  addModuleToDict(dict, "PythonQt.QtXml");
//  addModuleToDict(dict, "PythonQt.QtXmlPatterns");

#if PY_MAJOR_VERSION >= 3
  return module;
#endif
}


