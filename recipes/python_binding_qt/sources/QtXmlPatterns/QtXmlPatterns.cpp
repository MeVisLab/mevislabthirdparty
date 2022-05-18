/*************************************************************************************
**
** Copyright 2010, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/

#include "PythonQt.h"
#include <QSourceLocation>

void PythonQt_init_QtXmlPatterns(PyObject*);

static PyMethodDef NoMethods[] = {
    {nullptr, nullptr, 0, nullptr}        /* Sentinel */
};

#if PY_MAJOR_VERSION >= 3

static PyModuleDef QtXmlPatternsModuleDef = {
  PyModuleDef_HEAD_INIT,
  "QtXmlPatterns",
  nullptr,
  -1,
  NoMethods,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};

  #define Py_2_3_InitModFunc(name) PyInit_##name(void)
  #define Py_2_3_ModuleInit(name) PyModule_Create(&QtXmlPatternsModuleDef)

#else
  #define Py_2_3_InitModFunc(name) init##name(void)
  #define Py_2_3_ModuleInit(name) Py_InitModule(name, NoMethods)
#endif


#ifdef UNIX
PyMODINIT_FUNC
Py_2_3_InitModFunc(QtXmlPatterns) ML_LIBRARY_EXPORT_ATTRIBUTE ;
#endif

PyMODINIT_FUNC
Py_2_3_InitModFunc(QtXmlPatterns)
{
  PyObject* qtcore = PyImport_ImportModule("PythonQt.QtCore");
  PyObject* qtnetwork = PyImport_ImportModule("PythonQt.QtNetwork");
  PyObject* qtxml  = PyImport_ImportModule("PythonQt.QtXml");
  PyObject* module = Py_2_3_ModuleInit("QtXmlPatterns");
  PythonQt_init_QtXmlPatterns(module);

  qRegisterMetaType<QSourceLocation>("QSourceLocation");
  Py_XDECREF(qtcore);
  Py_XDECREF(qtnetwork);
  Py_XDECREF(qtxml);

  PythonQt::self()->clearNotFoundCachedMembers();
#if PY_MAJOR_VERSION >= 3
  return module;
#endif
}


