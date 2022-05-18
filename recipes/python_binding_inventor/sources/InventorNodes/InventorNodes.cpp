/*************************************************************************************
**
** Copyright 2014, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/

#include "PythonQt.h"
#include "PythonQtConversion.h"

void PythonQt_init_InventorNodes(PyObject*);

static PyMethodDef NoMethods[] = {
    {nullptr, nullptr, 0, nullptr}        /* Sentinel */
};

#if PY_MAJOR_VERSION >= 3

static PyModuleDef nodesModuleDef = {
  PyModuleDef_HEAD_INIT,
  "nodes",
  nullptr,
  -1,
  NoMethods,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};

  #define Py_2_3_InitModFunc(name) PyInit_##name(void)
  #define Py_2_3_ModuleInit(name) PyModule_Create(&nodesModuleDef)

#else
  #define Py_2_3_InitModFunc(name) init##name(void)
  #define Py_2_3_ModuleInit(name) Py_InitModule(name, NoMethods)
#endif

#ifdef UNIX
PyMODINIT_FUNC
Py_2_3_InitModFunc(nodes) ML_LIBRARY_EXPORT_ATTRIBUTE ;
#endif

PyMODINIT_FUNC
Py_2_3_InitModFunc(nodes)
{
  PyObject* base = PyImport_ImportModule("Inventor.base");
  Py_XDECREF(base);
  PyObject* fields = PyImport_ImportModule("Inventor.fields");
  Py_XDECREF(fields);

  PyObject* module = Py_2_3_ModuleInit("nodes");
  PythonQt_init_InventorNodes(module);

#if PY_MAJOR_VERSION >= 3
  return module;
#endif
}


