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

#define PyInitModFunc(name) PyInit_##name(void)
  #define PyModuleInit(name) PyModule_Create(&QtNetworkModuleDef)


#ifdef UNIX
PyMODINIT_FUNC
PyInitModFunc(QtNetwork) ML_LIBRARY_EXPORT_ATTRIBUTE ;
#endif

PyMODINIT_FUNC
PyInitModFunc(QtNetwork)
{
  PyObject* qtcore = PyImport_ImportModule("PythonQt.QtCore");
  PyObject* module = PyModuleInit("QtNetwork");
  PythonQt_init_QtNetwork(module);

  Py_XDECREF(qtcore);

  PythonQt::self()->clearNotFoundCachedMembers();

  return module;
}


