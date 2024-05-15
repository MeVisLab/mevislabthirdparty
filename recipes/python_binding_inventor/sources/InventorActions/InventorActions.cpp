/*************************************************************************************
**
** Copyright 2014, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/

#include "PythonQt.h"
#include "PythonQtConversion.h"
#include <Inventor/actions/SoAction.h>

void PythonQt_init_InventorActions(PyObject*);

static PyMethodDef NoMethods[] = {
    {nullptr, nullptr, 0, nullptr}        /* Sentinel */
};

static void* polymorphicHandler_SoAction(const void *ptr, const char **class_name)
{
  static QHash<QByteArray, QByteArray> names;
  SoAction *object = (SoAction*)ptr;
  QByteArray name = object->getTypeId().getName().getString();
  QByteArray resultName = names.value(name);
  if (resultName.isEmpty()) {
    QByteArray fullName = name;
    if (!fullName.startsWith("So")) {
      fullName = "So" + name;
    }
    names[name] = fullName;
    resultName = fullName;
  }
  PythonQtClassInfo* info = PythonQt::priv()->getClassInfo(resultName);
  if (!info) {
    // if the class is not yet known to PythonQt, register the whole parent hierachy...
    SoType type = object->getTypeId();
    do {
      QByteArray name = type.getName().getString();
      if (!name.startsWith("So")) {
        name = "So" + name;
      }
      SoType parent = type.getParent();
      QByteArray parentName = parent.getName().getString();
      if (!parentName.startsWith("So")) {
        parentName = "So" + parentName;
      }
      PythonQt::priv()->registerCPPClass(name, parentName);
      type = parent;
      PythonQtClassInfo* info = PythonQt::priv()->getClassInfo(parentName);
      if (info) {
        // stop because parent class is already known
        break;
      }
    } while (!type.isBad() && QByteArray(type.getName().getString()) != "Action");
  }
  *class_name = resultName.constData();
  return object;
}

static PyModuleDef actionsModuleDef = {
  PyModuleDef_HEAD_INIT,
  "actions",
  nullptr,
  -1,
  NoMethods,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};

#define PyInitModFunc(name) PyInit_##name(void)
  #define PyModuleInit(name) PyModule_Create(&actionsModuleDef)

#ifdef UNIX
PyMODINIT_FUNC
PyInitModFunc(actions) ML_LIBRARY_EXPORT_ATTRIBUTE ;
#endif

PyMODINIT_FUNC
PyInitModFunc(actions)
{
  PyObject* nodes = PyImport_ImportModule("Inventor.nodes");
  Py_XDECREF(nodes);

  PyObject* module = PyModuleInit("actions");
  PythonQt_init_InventorActions(module);

  PythonQt::self()->addPolymorphicHandler("SoAction", polymorphicHandler_SoAction);

  return module;
}


