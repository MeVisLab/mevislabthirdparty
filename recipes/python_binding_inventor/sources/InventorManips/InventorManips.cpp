/*************************************************************************************
**
** Copyright 2014, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/

#include "PythonQt.h"
#include "PythonQtConversion.h"

void PythonQt_init_InventorManips(PyObject*);

static PyMethodDef NoMethods[] = {
    {nullptr, nullptr, 0, nullptr}        /* Sentinel */
};

static PyModuleDef manipsModuleDef = {
  PyModuleDef_HEAD_INIT,
  "manips",
  nullptr,
  -1,
  NoMethods,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};

#define PyInitModFunc(name) PyInit_##name(void)
  #define PyModuleInit(name) PyModule_Create(&manipsModuleDef)

#ifdef UNIX
PyMODINIT_FUNC
PyInitModFunc(manips) ML_LIBRARY_EXPORT_ATTRIBUTE ;
#endif

PyMODINIT_FUNC
PyInitModFunc(manips)
{
  PyObject* draggers = PyImport_ImportModule("Inventor.draggers");
  Py_XDECREF(draggers);

  PyObject* module = PyModuleInit("manips");
  PythonQt_init_InventorManips(module);

  return module;
}


