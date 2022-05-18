/*************************************************************************************
**
** Copyright 2010, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/

#include "PythonQt.h"
#include "PythonQtConversion.h"

#include <QWebElement>
#include <QWebHistoryItem>

void PythonQt_init_QtWebKit(PyObject*);

static PyMethodDef NoMethods[] = {
    {nullptr, nullptr, 0, nullptr}        /* Sentinel */
};

//Q_DECLARE_METATYPE(QWebHistoryItem)
#if QT_VERSION < 0x040800
Q_DECLARE_METATYPE(QWebElement)
#endif

#if PY_MAJOR_VERSION >= 3

static PyModuleDef QtWebKitModuleDef = {
  PyModuleDef_HEAD_INIT,
  "QtWebKit",
  nullptr,
  -1,
  NoMethods,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};

  #define Py_2_3_InitModFunc(name) PyInit_##name(void)
  #define Py_2_3_ModuleInit(name) PyModule_Create(&QtWebKitModuleDef)

#else
  #define Py_2_3_InitModFunc(name) init##name(void)
  #define Py_2_3_ModuleInit(name) Py_InitModule(name, NoMethods)
#endif


#ifdef UNIX
PyMODINIT_FUNC
Py_2_3_InitModFunc(QtWebKit) ML_LIBRARY_EXPORT_ATTRIBUTE ;
#endif

PyMODINIT_FUNC
Py_2_3_InitModFunc(QtWebKit)
{
  PyObject* qtgui = PyImport_ImportModule("PythonQt.QtGui");
  PyObject* qtnetwork = PyImport_ImportModule("PythonQt.QtNetwork");
  PyObject* module = Py_2_3_ModuleInit("QtWebKit");
  PythonQt_init_QtWebKit(module);

  qRegisterMetaType<QWebElement>("QWebElement");
  //PythonQtRegisterToolClassesTemplateConverter(QWebHistoryItem);
  PythonQtRegisterToolClassesTemplateConverter(QWebElement);

  Py_XDECREF(qtgui);
  Py_XDECREF(qtnetwork);

  PythonQt::self()->clearNotFoundCachedMembers();

#if PY_MAJOR_VERSION >= 3
  return module;
#endif
}


