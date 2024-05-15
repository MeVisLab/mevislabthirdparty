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

#define PyInitModFunc(name) PyInit_##name(void)
  #define PyModuleInit(name) PyModule_Create(&nodesModuleDef)

#ifdef UNIX
PyMODINIT_FUNC
PyInitModFunc(nodes) ML_LIBRARY_EXPORT_ATTRIBUTE ;
#endif

PyMODINIT_FUNC
PyInitModFunc(nodes)
{
  PyObject* base = PyImport_ImportModule("Inventor.base");
  Py_XDECREF(base);
  PyObject* fields = PyImport_ImportModule("Inventor.fields");
  Py_XDECREF(fields);

  PyObject* module = PyModuleInit("nodes");
  PythonQt_init_InventorNodes(module);

  return module;
}


