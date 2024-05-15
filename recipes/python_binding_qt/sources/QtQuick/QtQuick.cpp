/*************************************************************************************
**
** Copyright 2010, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/

#include "PythonQt.h"

void PythonQt_init_QtQuick(PyObject*);

static PyMethodDef NoMethods[] = {
    {nullptr, nullptr, 0, nullptr}        /* Sentinel */
};

static PyModuleDef QtQuickModuleDef = {
  PyModuleDef_HEAD_INIT,
  "QtQuick",
  nullptr,
  -1,
  NoMethods,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};

#define PyInitModFunc(name) PyInit_##name(void)
  #define PyModuleInit(name) PyModule_Create(&QtQuickModuleDef)

#ifdef UNIX
PyMODINIT_FUNC
PyInitModFunc(QtQuick) ML_LIBRARY_EXPORT_ATTRIBUTE ;
#endif

PyMODINIT_FUNC
PyInitModFunc(QtQuick)
{
  PyObject* qtgui = PyImport_ImportModule("PythonQt.QtGui");
  PyObject* qtqml = PyImport_ImportModule("PythonQt.QtQml");
  PyObject* module = PyModuleInit("QtQuick");
  PythonQt_init_QtQuick(module);

  Py_XDECREF(qtgui);
  Py_XDECREF(qtqml);

  PythonQt::self()->clearNotFoundCachedMembers();

  return module;
}


