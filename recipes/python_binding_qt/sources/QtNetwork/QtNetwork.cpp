/*************************************************************************************
**
** Copyright 2010, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/

#include "PythonQt.h"

void PythonQt_init_QtNetwork(PyObject*);

static PyMethodDef NoMethods[] = {
    {nullptr, nullptr, 0, nullptr}        /* Sentinel */
};

#include <iostream>

#if PY_MAJOR_VERSION >= 3

static PyModuleDef QtNetworkModuleDef = {
  PyModuleDef_HEAD_INIT,
  "QtNetwork",
  nullptr,
  -1,
  NoMethods,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};

  #define Py_2_3_InitModFunc(name) PyInit_##name(void)
  #define Py_2_3_ModuleInit(name) PyModule_Create(&QtNetworkModuleDef)

#else
  #define Py_2_3_InitModFunc(name) init##name(void)
  #define Py_2_3_ModuleInit(name) Py_InitModule(name, NoMethods)
#endif


#ifdef UNIX
PyMODINIT_FUNC
Py_2_3_InitModFunc(QtNetwork) ML_LIBRARY_EXPORT_ATTRIBUTE ;
#endif

PyMODINIT_FUNC
Py_2_3_InitModFunc(QtNetwork)
{
  PyObject* qtcore = PyImport_ImportModule("PythonQt.QtCore");
  PyObject* module = Py_2_3_ModuleInit("QtNetwork");
  PythonQt_init_QtNetwork(module);

  Py_XDECREF(qtcore);

  PythonQt::self()->clearNotFoundCachedMembers();

#if PY_MAJOR_VERSION >= 3
  return module;
#endif
}


