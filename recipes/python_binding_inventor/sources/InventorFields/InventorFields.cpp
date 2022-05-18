/*************************************************************************************
**
** Copyright 2014, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/

#include "PythonQt.h"
#include "PythonQtConversion.h"
#include <Inventor/fields/SoField.h>

void PythonQt_init_InventorFields(PyObject*);

static PyMethodDef NoMethods[] = {
    {nullptr, nullptr, 0, nullptr}        /* Sentinel */
};

static void* polymorphicHandler_SoField(const void *ptr, const char **class_name)
{
  static QHash<QByteArray, QByteArray> names;
  SoField *object = (SoField*)ptr;
  QByteArray name = object->getTypeId().getName().getString();
  const char* result = names.value(name).constData();
  if (!result || result[0]==0) {
    QByteArray fullName = name;
    if (!fullName.startsWith("So")) {
      fullName = "So" + name;
    }
    names[name] = fullName;
    result = fullName.constData();
  }
  *class_name = result;
  return object;
}

#if PY_MAJOR_VERSION >= 3

static PyModuleDef fieldsModuleDef = {
  PyModuleDef_HEAD_INIT,
  "fields",
  nullptr,
  -1,
  NoMethods,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};

  #define Py_2_3_InitModFunc(name) PyInit_##name(void)
  #define Py_2_3_ModuleInit(name) PyModule_Create(&fieldsModuleDef)

#else
  #define Py_2_3_InitModFunc(name) init##name(void)
  #define Py_2_3_ModuleInit(name) Py_InitModule(name, NoMethods)
#endif

#ifdef UNIX
PyMODINIT_FUNC
Py_2_3_InitModFunc(fields) ML_LIBRARY_EXPORT_ATTRIBUTE ;
#endif

PyMODINIT_FUNC
Py_2_3_InitModFunc(fields)
{
  PyObject* base = PyImport_ImportModule("Inventor.base");
  Py_XDECREF(base);

  PyObject* module = Py_2_3_ModuleInit("fields");
  PythonQt_init_InventorFields(module);

  PythonQt::self()->addPolymorphicHandler("SoField", polymorphicHandler_SoField);

#if PY_MAJOR_VERSION >= 3
  return module;
#endif
}


