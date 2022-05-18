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

#if PY_MAJOR_VERSION >= 3

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

  #define Py_2_3_InitModFunc(name) PyInit_##name(void)
  #define Py_2_3_ModuleInit(name) PyModule_Create(&projectorsModuleDef)

#else
  #define Py_2_3_InitModFunc(name) init##name(void)
  #define Py_2_3_ModuleInit(name) Py_InitModule(name, NoMethods)
#endif

#ifdef UNIX
PyMODINIT_FUNC
Py_2_3_InitModFunc(projectors) ML_LIBRARY_EXPORT_ATTRIBUTE ;
#endif

PyMODINIT_FUNC
Py_2_3_InitModFunc(projectors)
{
  PyObject* base = PyImport_ImportModule("Inventor.base");
  Py_XDECREF(base);

  PyObject* module = Py_2_3_ModuleInit("projectors");
  PythonQt_init_InventorProjectors(module);

#if PY_MAJOR_VERSION >= 3
  return module;
#endif
}


