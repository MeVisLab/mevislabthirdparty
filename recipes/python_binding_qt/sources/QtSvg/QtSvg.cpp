/*************************************************************************************
**
** Copyright 2010, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/

#include "PythonQt.h"

void PythonQt_init_QtSvg(PyObject*);

static PyMethodDef NoMethods[] = {
    {nullptr, nullptr, 0, nullptr}        /* Sentinel */
};

static PyModuleDef QtSvgModuleDef = {
  PyModuleDef_HEAD_INIT,
  "QtSvg",
  nullptr,
  -1,
  NoMethods,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};

#define PyInitModFunc(name) PyInit_##name(void)
  #define PyModuleInit(name) PyModule_Create(&QtSvgModuleDef)

#ifdef UNIX
PyMODINIT_FUNC
PyInitModFunc(QtSvg) ML_LIBRARY_EXPORT_ATTRIBUTE ;
#endif

PyMODINIT_FUNC
PyInitModFunc(QtSvg)
{
  PyObject* qtgui = PyImport_ImportModule("PythonQt.QtGui");
  PyObject* module = PyModuleInit("QtSvg");
  PythonQt_init_QtSvg(module);

  Py_XDECREF(qtgui);

  PythonQt::self()->clearNotFoundCachedMembers();

  return module;
}


