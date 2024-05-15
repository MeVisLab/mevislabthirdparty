/*************************************************************************************
**
** Copyright 2014, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/

#include "PythonQt.h"
#include "PythonQtConversion.h"
#include <Inventor/events/SoEvent.h>

void PythonQt_init_InventorEvents(PyObject*);

static PyMethodDef NoMethods[] = {
    {nullptr, nullptr, 0, nullptr}        /* Sentinel */
};

static void* polymorphicHandler_SoEvent(const void *ptr, const char **class_name)
{
  static QHash<QByteArray, QByteArray> names;
  SoEvent *object = (SoEvent*)ptr;
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
    } while (!type.isBad() && QByteArray(type.getName().getString()) != "Event");
  }
  *class_name = resultName.constData();
  return object;
}

static PyModuleDef eventsModuleDef = {
  PyModuleDef_HEAD_INIT,
  "events",
  nullptr,
  -1,
  NoMethods,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};

#define PyInitModFunc(name) PyInit_##name(void)
  #define PyModuleInit(name) PyModule_Create(&eventsModuleDef)

#ifdef UNIX
PyMODINIT_FUNC
PyInitModFunc(events) ML_LIBRARY_EXPORT_ATTRIBUTE ;
#endif

PyMODINIT_FUNC
PyInitModFunc(events)
{
  PyObject* base = PyImport_ImportModule("Inventor.base");
  Py_XDECREF(base);

  PyObject* module = PyModuleInit("events");
  PythonQt_init_InventorEvents(module);

  PythonQt::self()->addPolymorphicHandler("SoEvent", polymorphicHandler_SoEvent);

  return module;
}


