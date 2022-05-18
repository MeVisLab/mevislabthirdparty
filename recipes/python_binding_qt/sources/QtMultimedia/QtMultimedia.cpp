/*************************************************************************************
**
** Copyright 2010, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/

#include "PythonQt.h"
#include "PythonQtConversion.h"

void PythonQt_init_QtMultimedia(PyObject*);

static PyMethodDef NoMethods[] = {
    {nullptr, nullptr, 0, nullptr}        /* Sentinel */
};

//Q_DECLARE_METATYPE(QWebHistoryItem)
#if QT_VERSION < 0x040800
Q_DECLARE_METATYPE(QWebElement)
#endif

#if PY_MAJOR_VERSION >= 3

static PyModuleDef QtMultimediaModuleDef = {
  PyModuleDef_HEAD_INIT,
  "QtMultimedia",
  nullptr,
  -1,
  NoMethods,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};

  #define Py_2_3_InitModFunc(name) PyInit_##name(void)
  #define Py_2_3_ModuleInit(name) PyModule_Create(&QtMultimediaModuleDef)

#else
  #define Py_2_3_InitModFunc(name) init##name(void)
  #define Py_2_3_ModuleInit(name) Py_InitModule(name, NoMethods)
#endif


#ifdef UNIX
PyMODINIT_FUNC
Py_2_3_InitModFunc(QtMultimedia) ML_LIBRARY_EXPORT_ATTRIBUTE ;
#endif

PyMODINIT_FUNC
Py_2_3_InitModFunc(QtMultimedia)
{
  PyObject* qtgui = PyImport_ImportModule("PythonQt.QtGui");
  PyObject* module = Py_2_3_ModuleInit("QtMultimedia");
  PythonQt_init_QtMultimedia(module);

  Py_XDECREF(qtgui);

  PythonQt::self()->clearNotFoundCachedMembers();

#if PY_MAJOR_VERSION >= 3
  return module;
#endif
}


