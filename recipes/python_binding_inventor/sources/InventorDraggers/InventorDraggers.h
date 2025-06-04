/*************************************************************************************
**
** Copyright 2014, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/

#pragma once

#include <PythonQt.h>
#include <QObject>
#include <Inventor/nodes/SoCallback.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoSelection.h>
#include <Inventor/draggers/SoDragger.h>
#include <QVariantList>
#include <stdexcept>

class InventorDraggersDecorator : public QObject
{
  Q_OBJECT

public Q_SLOTS:

  void addOtherEventCallback(SoDragger* cb, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      cb->addOtherEventCallback(PySoDraggerCB, callable);
    } else {
      throw std::invalid_argument("SoDragger::addOtherEventCallback requires a callable");
    }
  }
  void removeOtherEventCallback(SoDragger* cb, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      cb->removeOtherEventCallback(PySoDraggerCB, callable);
    } else {
      throw std::invalid_argument("SoDragger::removeOtherEventCallback requires a callable");
    }
  }

  void addStartCallback(SoDragger* cb, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      cb->addStartCallback(PySoDraggerCB, callable);
    } else {
      throw std::invalid_argument("SoDragger::addStartCallback requires a callable");
    }
  }
  void removeStartCallback(SoDragger* cb, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      cb->removeStartCallback(PySoDraggerCB, callable);
    } else {
      throw std::invalid_argument("SoDragger::removeStartCallback requires a callable");
    }
  }
  void addMotionCallback(SoDragger* cb, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      cb->addMotionCallback(PySoDraggerCB, callable);
    } else {
      throw std::invalid_argument("SoDragger::addMotionCallback requires a callable");
    }
  }
  void removeMotionCallback(SoDragger* cb, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      cb->removeMotionCallback(PySoDraggerCB, callable);
    } else {
      throw std::invalid_argument("SoDragger::removeMotionCallback requires a callable");
    }
  }
  void addFinishCallback(SoDragger* cb, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      cb->addFinishCallback(PySoDraggerCB, callable);
    } else {
      throw std::invalid_argument("SoDragger::addFinishCallback requires a callable");
    }
  }
  void removeFinishCallback(SoDragger* cb, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      cb->removeFinishCallback(PySoDraggerCB, callable);
    } else {
      throw std::invalid_argument("SoDragger::removeFinishCallback requires a callable");
    }
  }
  void addValueChangedCallback(SoDragger* cb, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      cb->addValueChangedCallback(PySoDraggerCB, callable);
    } else {
      throw std::invalid_argument("SoDragger::addValueChangedCallback requires a callable");
    }
  }
  void removeValueChangedCallback(SoDragger* cb, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      cb->removeValueChangedCallback(PySoDraggerCB, callable);
    } else {
      throw std::invalid_argument("SoDragger::removeValueChangedCallback requires a callable");
    }
  }

protected:
  static void PySoDraggerCB(void *userData, SoDragger *dragger );

};

