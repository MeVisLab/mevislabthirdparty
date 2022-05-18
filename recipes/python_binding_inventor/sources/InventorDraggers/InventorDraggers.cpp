/*************************************************************************************
**
** Copyright 2014, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/

#include "InventorDraggers.h"
#include "PythonQtConversion.h"

void PythonQt_init_InventorDraggers(PyObject*);

static PyMethodDef NoMethods[] = {
    {nullptr, nullptr, 0, nullptr}        /* Sentinel */
};

#if PY_MAJOR_VERSION >= 3

static PyModuleDef draggersModuleDef = {
  PyModuleDef_HEAD_INIT,
  "draggers",
  nullptr,
  -1,
  NoMethods,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};

  #define Py_2_3_InitModFunc(name) PyInit_##name(void)
  #define Py_2_3_ModuleInit(name) PyModule_Create(&draggersModuleDef)

#else
  #define Py_2_3_InitModFunc(name) init##name(void)
  #define Py_2_3_ModuleInit(name) Py_InitModule(name, NoMethods)
#endif

#ifdef UNIX
PyMODINIT_FUNC
Py_2_3_InitModFunc(draggers) ML_LIBRARY_EXPORT_ATTRIBUTE ;
#endif

PyMODINIT_FUNC
Py_2_3_InitModFunc(draggers)
{
  PyObject* nodekits = PyImport_ImportModule("Inventor.nodekits");
  Py_XDECREF(nodekits);

  PyObject* module = Py_2_3_ModuleInit("draggers");
  PythonQt_init_InventorDraggers(module);

  PythonQt::self()->addDecorators(new InventorDraggersDecorator());

#if PY_MAJOR_VERSION >= 3
  return module;
#endif
}


void InventorDraggersDecorator::PySoDraggerCB(void *userData, SoDragger *dragger)
{
  PyObject* callable = (PyObject*)userData;
  PyObject* tuple = PyTuple_New(1);
  PyTuple_SET_ITEM(tuple, 0, PythonQt::priv()->wrapPtr(dragger, "SoDragger"));
  PyObject* result = PyObject_CallObject(callable, tuple);
  if (!result) {
    PythonQt::self()->handleError();
  }
  Py_DECREF(tuple);
  Py_XDECREF(result);
}
