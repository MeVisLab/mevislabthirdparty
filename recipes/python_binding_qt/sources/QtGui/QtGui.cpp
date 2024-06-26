/*************************************************************************************
**
** Copyright 2010, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/

#include "PythonQt.h"

#include <QGraphicsLayout>
#include <QGraphicsEffect>

void PythonQt_init_QtGui(PyObject*);

static PyMethodDef NoMethods[] = {
    {nullptr, nullptr, 0, nullptr}        /* Sentinel */
};

static PyModuleDef QtGuiModuleDef = {
  PyModuleDef_HEAD_INIT,
  "QtGui",
  nullptr,
  -1,
  NoMethods,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};

#define PyInitModFunc(name) PyInit_##name(void)
#define PyModuleInit(name) PyModule_Create(&QtGuiModuleDef)


#ifdef UNIX
PyMODINIT_FUNC
PyInitModFunc(QtGui) ML_LIBRARY_EXPORT_ATTRIBUTE ;
#endif

PyMODINIT_FUNC
PyInitModFunc(QtGui)
{
  // these are needed for QGraphicsWidget::layout and QGraphicsObject::effect
  qRegisterMetaType<QGraphicsLayout*>("QGraphicsLayout*");
  qRegisterMetaType<QGraphicsEffect*>("QGraphicsEffect*");

  PyObject* qtcore = PyImport_ImportModule("PythonQt.QtCore");
  PyObject* module = PyModuleInit("QtGui");
  PythonQt_init_QtGui(module);
  PyObject* qtguiDict = PyModule_GetDict(module);

  // TODO: should this ask PythonQt about the module name or do we force _PythonQt?
  PyObject* builtins = PyImport_ImportModule("_PythonQt.QtGui");

  // change the __module__ of the builtins to ourself
  // otherwise they would show the internal _PythonQt module name
  PyObject* dict = PyModule_GetDict(builtins);
  PyObject* key;
  PyObject* value;
  Py_ssize_t pos = 0;
  while (PyDict_Next(dict, &pos, &key, &value)) {
    if (!PyDict_Contains(qtguiDict, key)) {
      if (PyObject_HasAttrString(value, "__module__")) {
        PyObject_SetAttrString(value, "__module__", PyObject_GetAttrString(module, "__name__"));
        // we had to clear the error because setting __module__ does not work on built-in types
        PyErr_Clear();
      }
    }
  }
  // and merge them into the qtcore dict
  PyDict_Merge(qtguiDict, dict, false);

  Py_XDECREF(qtcore);

  PythonQt::self()->clearNotFoundCachedMembers();

  return module;
}


