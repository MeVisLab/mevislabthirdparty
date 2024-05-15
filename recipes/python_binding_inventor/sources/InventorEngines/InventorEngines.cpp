/*************************************************************************************
**
** Copyright 2014, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/

#include "PythonQt.h"
#include "PythonQtConversion.h"

void PythonQt_init_InventorEngines(PyObject*);

static PyMethodDef NoMethods[] = {
    {nullptr, nullptr, 0, nullptr}        /* Sentinel */
};

static PyModuleDef enginesModuleDef = {
  PyModuleDef_HEAD_INIT,
  "engines",
  nullptr,
  -1,
  NoMethods,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};

#define PyInitModFunc(name) PyInit_##name(void)
  #define PyModuleInit(name) PyModule_Create(&enginesModuleDef)

#ifdef UNIX
PyMODINIT_FUNC
PyInitModFunc(engines) ML_LIBRARY_EXPORT_ATTRIBUTE ;
#endif

PyMODINIT_FUNC
PyInitModFunc(engines)
{
  PyObject* fields = PyImport_ImportModule("Inventor.fields");
  Py_XDECREF(fields);

  PyObject* module = PyModuleInit("engines");
  PythonQt_init_InventorEngines(module);

  return module;
}


