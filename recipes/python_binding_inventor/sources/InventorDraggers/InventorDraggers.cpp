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

#define PyInitModFunc(name) PyInit_##name(void)
  #define PyModuleInit(name) PyModule_Create(&draggersModuleDef)

#ifdef UNIX
PyMODINIT_FUNC
PyInitModFunc(draggers) ML_LIBRARY_EXPORT_ATTRIBUTE ;
#endif

PyMODINIT_FUNC
PyInitModFunc(draggers)
{
  PyObject* nodekits = PyImport_ImportModule("Inventor.nodekits");
  Py_XDECREF(nodekits);

  PyObject* module = PyModuleInit("draggers");
  PythonQt_init_InventorDraggers(module);

  PythonQt::self()->addDecorators(new InventorDraggersDecorator());

  return module;
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
