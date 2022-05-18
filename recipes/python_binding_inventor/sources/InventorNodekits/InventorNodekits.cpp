/*************************************************************************************
**
** Copyright 2014, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/

#include "PythonQt.h"
#include "PythonQtConversion.h"

void PythonQt_init_InventorNodekits(PyObject*);

static PyMethodDef NoMethods[] = {
    {nullptr, nullptr, 0, nullptr}        /* Sentinel */
};

#if PY_MAJOR_VERSION >= 3

static PyModuleDef nodekitsModuleDef = {
  PyModuleDef_HEAD_INIT,
  "nodekits",
  nullptr,
  -1,
  NoMethods,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};

  #define Py_2_3_InitModFunc(name) PyInit_##name(void)
  #define Py_2_3_ModuleInit(name) PyModule_Create(&nodekitsModuleDef)

#else
  #define Py_2_3_InitModFunc(name) init##name(void)
  #define Py_2_3_ModuleInit(name) Py_InitModule(name, NoMethods)
#endif

#ifdef UNIX
PyMODINIT_FUNC
Py_2_3_InitModFunc(nodekits) ML_LIBRARY_EXPORT_ATTRIBUTE ;
#endif

PyMODINIT_FUNC
Py_2_3_InitModFunc(nodekits)
{
  PyObject* nodes = PyImport_ImportModule("Inventor.nodes");
  Py_XDECREF(nodes);

  PyObject* module = Py_2_3_ModuleInit("nodekits");
  PythonQt_init_InventorNodekits(module);

#if PY_MAJOR_VERSION >= 3
  return module;
#endif
}


