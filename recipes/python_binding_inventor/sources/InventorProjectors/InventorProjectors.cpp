/*************************************************************************************
**
** Copyright 2014, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/

#include "PythonQt.h"
#include "PythonQtConversion.h"

void PythonQt_init_InventorProjectors(PyObject*);

static PyMethodDef NoMethods[] = {
    {nullptr, nullptr, 0, nullptr}        /* Sentinel */
};

static PyModuleDef projectorsModuleDef = {
  PyModuleDef_HEAD_INIT,
  "projectors",
  nullptr,
  -1,
  NoMethods,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};

#define PyInitModFunc(name) PyInit_##name(void)
  #define PyModuleInit(name) PyModule_Create(&projectorsModuleDef)

#ifdef UNIX
PyMODINIT_FUNC
PyInitModFunc(projectors) ML_LIBRARY_EXPORT_ATTRIBUTE ;
#endif

PyMODINIT_FUNC
PyInitModFunc(projectors)
{
  PyObject* base = PyImport_ImportModule("Inventor.base");
  Py_XDECREF(base);

  PyObject* module = PyModuleInit("projectors");
  PythonQt_init_InventorProjectors(module);

  return module;
}


