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

#define PyInitModFunc(name) PyInit_##name(void)
#define PyModuleInit(name) PyModule_Create(&QtMultimediaModuleDef)


#ifdef UNIX
PyMODINIT_FUNC
PyInitModFunc(QtMultimedia) ML_LIBRARY_EXPORT_ATTRIBUTE ;
#endif

PyMODINIT_FUNC
PyInitModFunc(QtMultimedia)
{
  PyObject* qtgui = PyImport_ImportModule("PythonQt.QtGui");
  PyObject* module = PyModuleInit("QtMultimedia");
  PythonQt_init_QtMultimedia(module);

  Py_XDECREF(qtgui);

  PythonQt::self()->clearNotFoundCachedMembers();
    return module;
}


