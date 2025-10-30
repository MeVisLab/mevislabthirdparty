#include "inventor_projectors0.h"
#include <Inventor/SbLinear.h>
#include <Inventor/projectors/SbProjector.h>
#include <PythonQtConversion.h>
#include <PythonQtMethodInfo.h>
#include <PythonQtSignalReceiver.h>
#include <QVariant>

PythonQtShell_SbCylinderPlaneProjector::~PythonQtShell_SbCylinderPlaneProjector() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SbProjector*  PythonQtShell_SbCylinderPlaneProjector::copy() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("copy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbProjector*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SbProjector* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copy", methodInfo, result);
          } else {
            returnValue = *((SbProjector**)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbCylinderPlaneProjector::copy();
}
SbRotation  PythonQtShell_SbCylinderPlaneProjector::getRotation(const SbVec3f&  point10, const SbVec3f&  point21)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("getRotation");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbRotation" , "const SbVec3f&" , "const SbVec3f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      SbRotation returnValue{};
      void* args[3] = {nullptr, (void*)&point10, (void*)&point21};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getRotation", methodInfo, result);
          } else {
            returnValue = *((SbRotation*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbCylinderPlaneProjector::getRotation(point10, point21);
}
SbVec3f  PythonQtShell_SbCylinderPlaneProjector::project(const SbVec2f&  point0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("project");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbVec3f" , "const SbVec2f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      SbVec3f returnValue{};
      void* args[2] = {nullptr, (void*)&point0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("project", methodInfo, result);
          } else {
            returnValue = *((SbVec3f*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbCylinderPlaneProjector::project(point0);
}
void PythonQtShell_SbCylinderPlaneProjector::setViewVolume(const SbViewVolume&  vol0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setViewVolume");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbViewVolume&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&vol0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbCylinderPlaneProjector::setViewVolume(vol0);
}
void PythonQtShell_SbCylinderPlaneProjector::setWorkingSpace(const SbMatrix&  space0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setWorkingSpace");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbMatrix&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&space0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbCylinderPlaneProjector::setWorkingSpace(space0);
}
void PythonQtShell_SbCylinderPlaneProjector::setupTolerance()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setupTolerance");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={""};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbCylinderPlaneProjector::setupTolerance();
}
SbCylinderPlaneProjector* PythonQtWrapper_SbCylinderPlaneProjector::new_SbCylinderPlaneProjector(const SbCylinder&  cyl, float  edgeTol, bool  orientToEye)
{ 
return new PythonQtShell_SbCylinderPlaneProjector(cyl, edgeTol, orientToEye); }

SbCylinderPlaneProjector* PythonQtWrapper_SbCylinderPlaneProjector::new_SbCylinderPlaneProjector(float  edgeTol, bool  orientToEye)
{ 
return new PythonQtShell_SbCylinderPlaneProjector(edgeTol, orientToEye); }

SbRotation  PythonQtWrapper_SbCylinderPlaneProjector::getRotation(SbCylinderPlaneProjector* theWrappedObject, const SbVec3f&  point1, bool  tol1, const SbVec3f&  point2, bool  tol2)
{
  return ( ((PythonQtPublicPromoter_SbCylinderPlaneProjector*)theWrappedObject)->promoted_getRotation(point1, tol1, point2, tol2));
}



PythonQtShell_SbCylinderProjector::~PythonQtShell_SbCylinderProjector() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SbProjector*  PythonQtShell_SbCylinderProjector::copy() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("copy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbProjector*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SbProjector* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copy", methodInfo, result);
          } else {
            returnValue = *((SbProjector**)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return nullptr;
}
SbRotation  PythonQtShell_SbCylinderProjector::getRotation(const SbVec3f&  point10, const SbVec3f&  point21)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("getRotation");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbRotation" , "const SbVec3f&" , "const SbVec3f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      SbRotation returnValue{};
      void* args[3] = {nullptr, (void*)&point10, (void*)&point21};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getRotation", methodInfo, result);
          } else {
            returnValue = *((SbRotation*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbRotation();
}
SbVec3f  PythonQtShell_SbCylinderProjector::project(const SbVec2f&  point0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("project");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbVec3f" , "const SbVec2f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      SbVec3f returnValue{};
      void* args[2] = {nullptr, (void*)&point0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("project", methodInfo, result);
          } else {
            returnValue = *((SbVec3f*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbVec3f();
}
void PythonQtShell_SbCylinderProjector::setViewVolume(const SbViewVolume&  vol0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setViewVolume");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbViewVolume&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&vol0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbCylinderProjector::setViewVolume(vol0);
}
void PythonQtShell_SbCylinderProjector::setWorkingSpace(const SbMatrix&  space0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setWorkingSpace");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbMatrix&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&space0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbCylinderProjector::setWorkingSpace(space0);
}
SbCylinderProjector* PythonQtWrapper_SbCylinderProjector::new_SbCylinderProjector(bool  orientToEye)
{ 
return new PythonQtShell_SbCylinderProjector(orientToEye); }

SbCylinderProjector* PythonQtWrapper_SbCylinderProjector::new_SbCylinderProjector(const SbCylinder&  cyl, bool  orientToEye)
{ 
return new PythonQtShell_SbCylinderProjector(cyl, orientToEye); }

const SbCylinder*  PythonQtWrapper_SbCylinderProjector::getCylinder(SbCylinderProjector* theWrappedObject) const
{
  return &( theWrappedObject->getCylinder());
}

SbRotation  PythonQtWrapper_SbCylinderProjector::getRotation(SbCylinderProjector* theWrappedObject, const SbVec3f&  point1, const SbVec3f&  point2)
{
  return ( theWrappedObject->getRotation(point1, point2));
}

bool  PythonQtWrapper_SbCylinderProjector::isFront(SbCylinderProjector* theWrappedObject) const
{
  return ( theWrappedObject->isFront());
}

bool  PythonQtWrapper_SbCylinderProjector::isOrientToEye(SbCylinderProjector* theWrappedObject) const
{
  return ( theWrappedObject->isOrientToEye());
}

bool  PythonQtWrapper_SbCylinderProjector::isPointInFront(SbCylinderProjector* theWrappedObject, const SbVec3f&  point) const
{
  return ( theWrappedObject->isPointInFront(point));
}

void PythonQtWrapper_SbCylinderProjector::setCylinder(SbCylinderProjector* theWrappedObject, const SbCylinder&  cyl)
{
  ( theWrappedObject->setCylinder(cyl));
}

void PythonQtWrapper_SbCylinderProjector::setFront(SbCylinderProjector* theWrappedObject, bool  isFront)
{
  ( theWrappedObject->setFront(isFront));
}

void PythonQtWrapper_SbCylinderProjector::setOrientToEye(SbCylinderProjector* theWrappedObject, bool  orientToEye)
{
  ( theWrappedObject->setOrientToEye(orientToEye));
}



PythonQtShell_SbCylinderSectionProjector::~PythonQtShell_SbCylinderSectionProjector() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SbProjector*  PythonQtShell_SbCylinderSectionProjector::copy() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("copy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbProjector*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SbProjector* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copy", methodInfo, result);
          } else {
            returnValue = *((SbProjector**)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbCylinderSectionProjector::copy();
}
SbRotation  PythonQtShell_SbCylinderSectionProjector::getRotation(const SbVec3f&  point10, const SbVec3f&  point21)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("getRotation");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbRotation" , "const SbVec3f&" , "const SbVec3f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      SbRotation returnValue{};
      void* args[3] = {nullptr, (void*)&point10, (void*)&point21};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getRotation", methodInfo, result);
          } else {
            returnValue = *((SbRotation*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbCylinderSectionProjector::getRotation(point10, point21);
}
SbVec3f  PythonQtShell_SbCylinderSectionProjector::project(const SbVec2f&  point0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("project");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbVec3f" , "const SbVec2f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      SbVec3f returnValue{};
      void* args[2] = {nullptr, (void*)&point0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("project", methodInfo, result);
          } else {
            returnValue = *((SbVec3f*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbCylinderSectionProjector::project(point0);
}
void PythonQtShell_SbCylinderSectionProjector::setViewVolume(const SbViewVolume&  vol0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setViewVolume");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbViewVolume&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&vol0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbCylinderSectionProjector::setViewVolume(vol0);
}
void PythonQtShell_SbCylinderSectionProjector::setWorkingSpace(const SbMatrix&  space0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setWorkingSpace");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbMatrix&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&space0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbCylinderSectionProjector::setWorkingSpace(space0);
}
void PythonQtShell_SbCylinderSectionProjector::setupTolerance()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setupTolerance");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={""};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbCylinderSectionProjector::setupTolerance();
}
SbCylinderSectionProjector* PythonQtWrapper_SbCylinderSectionProjector::new_SbCylinderSectionProjector(const SbCylinder&  cyl, float  edgeTol, bool  orientToEye)
{ 
return new PythonQtShell_SbCylinderSectionProjector(cyl, edgeTol, orientToEye); }

SbCylinderSectionProjector* PythonQtWrapper_SbCylinderSectionProjector::new_SbCylinderSectionProjector(float  edgeTol, bool  orientToEye)
{ 
return new PythonQtShell_SbCylinderSectionProjector(edgeTol, orientToEye); }

float  PythonQtWrapper_SbCylinderSectionProjector::getTolerance(SbCylinderSectionProjector* theWrappedObject) const
{
  return ( theWrappedObject->getTolerance());
}

bool  PythonQtWrapper_SbCylinderSectionProjector::isWithinTolerance(SbCylinderSectionProjector* theWrappedObject, const SbVec3f&  point)
{
  return ( theWrappedObject->isWithinTolerance(point));
}

void PythonQtWrapper_SbCylinderSectionProjector::setTolerance(SbCylinderSectionProjector* theWrappedObject, float  edgeTol)
{
  ( theWrappedObject->setTolerance(edgeTol));
}

void PythonQtWrapper_SbCylinderSectionProjector::setupTolerance(SbCylinderSectionProjector* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_SbCylinderSectionProjector*)theWrappedObject)->promoted_setupTolerance());
}



PythonQtShell_SbCylinderSheetProjector::~PythonQtShell_SbCylinderSheetProjector() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SbProjector*  PythonQtShell_SbCylinderSheetProjector::copy() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("copy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbProjector*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SbProjector* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copy", methodInfo, result);
          } else {
            returnValue = *((SbProjector**)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbCylinderSheetProjector::copy();
}
SbRotation  PythonQtShell_SbCylinderSheetProjector::getRotation(const SbVec3f&  point10, const SbVec3f&  point21)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("getRotation");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbRotation" , "const SbVec3f&" , "const SbVec3f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      SbRotation returnValue{};
      void* args[3] = {nullptr, (void*)&point10, (void*)&point21};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getRotation", methodInfo, result);
          } else {
            returnValue = *((SbRotation*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbCylinderSheetProjector::getRotation(point10, point21);
}
SbVec3f  PythonQtShell_SbCylinderSheetProjector::project(const SbVec2f&  point0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("project");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbVec3f" , "const SbVec2f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      SbVec3f returnValue{};
      void* args[2] = {nullptr, (void*)&point0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("project", methodInfo, result);
          } else {
            returnValue = *((SbVec3f*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbCylinderSheetProjector::project(point0);
}
void PythonQtShell_SbCylinderSheetProjector::setViewVolume(const SbViewVolume&  vol0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setViewVolume");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbViewVolume&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&vol0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbCylinderSheetProjector::setViewVolume(vol0);
}
void PythonQtShell_SbCylinderSheetProjector::setWorkingSpace(const SbMatrix&  space0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setWorkingSpace");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbMatrix&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&space0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbCylinderSheetProjector::setWorkingSpace(space0);
}
void PythonQtShell_SbCylinderSheetProjector::setupPlane()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setupPlane");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={""};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbCylinderSheetProjector::setupPlane();
}
SbCylinderSheetProjector* PythonQtWrapper_SbCylinderSheetProjector::new_SbCylinderSheetProjector(bool  orientToEye)
{ 
return new PythonQtShell_SbCylinderSheetProjector(orientToEye); }

SbCylinderSheetProjector* PythonQtWrapper_SbCylinderSheetProjector::new_SbCylinderSheetProjector(const SbCylinder&  cyl, bool  orientToEye)
{ 
return new PythonQtShell_SbCylinderSheetProjector(cyl, orientToEye); }

void PythonQtWrapper_SbCylinderSheetProjector::setupPlane(SbCylinderSheetProjector* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_SbCylinderSheetProjector*)theWrappedObject)->promoted_setupPlane());
}



PythonQtShell_SbLineProjector::~PythonQtShell_SbLineProjector() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SbProjector*  PythonQtShell_SbLineProjector::copy() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("copy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbProjector*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SbProjector* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copy", methodInfo, result);
          } else {
            returnValue = *((SbProjector**)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbLineProjector::copy();
}
SbVec3f  PythonQtShell_SbLineProjector::getVector(const SbVec2f&  mousePosition0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("getVector");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbVec3f" , "const SbVec2f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      SbVec3f returnValue{};
      void* args[2] = {nullptr, (void*)&mousePosition0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getVector", methodInfo, result);
          } else {
            returnValue = *((SbVec3f*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbLineProjector::getVector(mousePosition0);
}
SbVec3f  PythonQtShell_SbLineProjector::getVector(const SbVec2f&  mousePosition10, const SbVec2f&  mousePosition21)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("getVector");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbVec3f" , "const SbVec2f&" , "const SbVec2f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      SbVec3f returnValue{};
      void* args[3] = {nullptr, (void*)&mousePosition10, (void*)&mousePosition21};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getVector", methodInfo, result);
          } else {
            returnValue = *((SbVec3f*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbLineProjector::getVector(mousePosition10, mousePosition21);
}
SbVec3f  PythonQtShell_SbLineProjector::project(const SbVec2f&  point0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("project");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbVec3f" , "const SbVec2f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      SbVec3f returnValue{};
      void* args[2] = {nullptr, (void*)&point0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("project", methodInfo, result);
          } else {
            returnValue = *((SbVec3f*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbLineProjector::project(point0);
}
void PythonQtShell_SbLineProjector::setViewVolume(const SbViewVolume&  vol0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setViewVolume");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbViewVolume&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&vol0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbLineProjector::setViewVolume(vol0);
}
void PythonQtShell_SbLineProjector::setWorkingSpace(const SbMatrix&  space0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setWorkingSpace");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbMatrix&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&space0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbLineProjector::setWorkingSpace(space0);
}
SbLineProjector* PythonQtWrapper_SbLineProjector::new_SbLineProjector()
{ 
return new PythonQtShell_SbLineProjector(); }

const SbLine*  PythonQtWrapper_SbLineProjector::getLine(SbLineProjector* theWrappedObject) const
{
  return &( theWrappedObject->getLine());
}

SbVec3f  PythonQtWrapper_SbLineProjector::getVector(SbLineProjector* theWrappedObject, const SbVec2f&  mousePosition)
{
  return ( theWrappedObject->getVector(mousePosition));
}

SbVec3f  PythonQtWrapper_SbLineProjector::getVector(SbLineProjector* theWrappedObject, const SbVec2f&  mousePosition1, const SbVec2f&  mousePosition2)
{
  return ( theWrappedObject->getVector(mousePosition1, mousePosition2));
}

void PythonQtWrapper_SbLineProjector::setLine(SbLineProjector* theWrappedObject, const SbLine&  line)
{
  ( theWrappedObject->setLine(line));
}

void PythonQtWrapper_SbLineProjector::setStartPosition(SbLineProjector* theWrappedObject, const SbVec2f&  mousePosition)
{
  ( theWrappedObject->setStartPosition(mousePosition));
}

void PythonQtWrapper_SbLineProjector::setStartPosition(SbLineProjector* theWrappedObject, const SbVec3f&  point)
{
  ( theWrappedObject->setStartPosition(point));
}



PythonQtShell_SbPlaneProjector::~PythonQtShell_SbPlaneProjector() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SbProjector*  PythonQtShell_SbPlaneProjector::copy() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("copy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbProjector*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SbProjector* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copy", methodInfo, result);
          } else {
            returnValue = *((SbProjector**)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbPlaneProjector::copy();
}
SbVec3f  PythonQtShell_SbPlaneProjector::getVector(const SbVec2f&  mousePosition0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("getVector");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbVec3f" , "const SbVec2f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      SbVec3f returnValue{};
      void* args[2] = {nullptr, (void*)&mousePosition0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getVector", methodInfo, result);
          } else {
            returnValue = *((SbVec3f*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbPlaneProjector::getVector(mousePosition0);
}
SbVec3f  PythonQtShell_SbPlaneProjector::getVector(const SbVec2f&  mousePosition10, const SbVec2f&  mousePosition21)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("getVector");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbVec3f" , "const SbVec2f&" , "const SbVec2f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      SbVec3f returnValue{};
      void* args[3] = {nullptr, (void*)&mousePosition10, (void*)&mousePosition21};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getVector", methodInfo, result);
          } else {
            returnValue = *((SbVec3f*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbPlaneProjector::getVector(mousePosition10, mousePosition21);
}
SbVec3f  PythonQtShell_SbPlaneProjector::project(const SbVec2f&  point0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("project");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbVec3f" , "const SbVec2f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      SbVec3f returnValue{};
      void* args[2] = {nullptr, (void*)&point0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("project", methodInfo, result);
          } else {
            returnValue = *((SbVec3f*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbPlaneProjector::project(point0);
}
void PythonQtShell_SbPlaneProjector::setViewVolume(const SbViewVolume&  vol0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setViewVolume");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbViewVolume&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&vol0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbPlaneProjector::setViewVolume(vol0);
}
void PythonQtShell_SbPlaneProjector::setWorkingSpace(const SbMatrix&  space0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setWorkingSpace");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbMatrix&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&space0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbPlaneProjector::setWorkingSpace(space0);
}
SbPlaneProjector* PythonQtWrapper_SbPlaneProjector::new_SbPlaneProjector(bool  orient)
{ 
return new PythonQtShell_SbPlaneProjector(orient); }

SbPlaneProjector* PythonQtWrapper_SbPlaneProjector::new_SbPlaneProjector(const SbPlane&  plane, bool  orient)
{ 
return new PythonQtShell_SbPlaneProjector(plane, orient); }

const SbPlane*  PythonQtWrapper_SbPlaneProjector::getPlane(SbPlaneProjector* theWrappedObject) const
{
  return &( theWrappedObject->getPlane());
}

SbVec3f  PythonQtWrapper_SbPlaneProjector::getVector(SbPlaneProjector* theWrappedObject, const SbVec2f&  mousePosition)
{
  return ( theWrappedObject->getVector(mousePosition));
}

SbVec3f  PythonQtWrapper_SbPlaneProjector::getVector(SbPlaneProjector* theWrappedObject, const SbVec2f&  mousePosition1, const SbVec2f&  mousePosition2)
{
  return ( theWrappedObject->getVector(mousePosition1, mousePosition2));
}

bool  PythonQtWrapper_SbPlaneProjector::isOrientToEye(SbPlaneProjector* theWrappedObject) const
{
  return ( theWrappedObject->isOrientToEye());
}

void PythonQtWrapper_SbPlaneProjector::setOrientToEye(SbPlaneProjector* theWrappedObject, bool  orientToEye)
{
  ( theWrappedObject->setOrientToEye(orientToEye));
}

void PythonQtWrapper_SbPlaneProjector::setPlane(SbPlaneProjector* theWrappedObject, const SbPlane&  plane)
{
  ( theWrappedObject->setPlane(plane));
}

void PythonQtWrapper_SbPlaneProjector::setStartPosition(SbPlaneProjector* theWrappedObject, const SbVec2f&  mousePosition)
{
  ( theWrappedObject->setStartPosition(mousePosition));
}

void PythonQtWrapper_SbPlaneProjector::setStartPosition(SbPlaneProjector* theWrappedObject, const SbVec3f&  point)
{
  ( theWrappedObject->setStartPosition(point));
}

void PythonQtWrapper_SbPlaneProjector::setupPlane(SbPlaneProjector* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_SbPlaneProjector*)theWrappedObject)->promoted_setupPlane());
}



PythonQtShell_SbProjector::~PythonQtShell_SbProjector() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SbProjector*  PythonQtShell_SbProjector::copy() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("copy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbProjector*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SbProjector* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copy", methodInfo, result);
          } else {
            returnValue = *((SbProjector**)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return nullptr;
}
SbVec3f  PythonQtShell_SbProjector::project(const SbVec2f&  point0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("project");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbVec3f" , "const SbVec2f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      SbVec3f returnValue{};
      void* args[2] = {nullptr, (void*)&point0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("project", methodInfo, result);
          } else {
            returnValue = *((SbVec3f*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbVec3f();
}
void PythonQtShell_SbProjector::setViewVolume(const SbViewVolume&  vol0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setViewVolume");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbViewVolume&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&vol0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbProjector::setViewVolume(vol0);
}
void PythonQtShell_SbProjector::setWorkingSpace(const SbMatrix&  space0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setWorkingSpace");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbMatrix&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&space0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbProjector::setWorkingSpace(space0);
}
SbProjector* PythonQtWrapper_SbProjector::new_SbProjector()
{ 
return new PythonQtShell_SbProjector(); }

SbProjector*  PythonQtWrapper_SbProjector::copy(SbProjector* theWrappedObject) const
{
  return ( theWrappedObject->copy());
}

const SbViewVolume*  PythonQtWrapper_SbProjector::getViewVolume(SbProjector* theWrappedObject) const
{
  return &( theWrappedObject->getViewVolume());
}

SbLine  PythonQtWrapper_SbProjector::getWorkingLine(SbProjector* theWrappedObject, const SbVec2f&  point) const
{
  return ( ((PythonQtPublicPromoter_SbProjector*)theWrappedObject)->promoted_getWorkingLine(point));
}

const SbMatrix*  PythonQtWrapper_SbProjector::getWorkingSpace(SbProjector* theWrappedObject) const
{
  return &( theWrappedObject->getWorkingSpace());
}

SbVec3f  PythonQtWrapper_SbProjector::project(SbProjector* theWrappedObject, const SbVec2f&  point)
{
  return ( theWrappedObject->project(point));
}

void PythonQtWrapper_SbProjector::setViewVolume(SbProjector* theWrappedObject, const SbViewVolume&  vol)
{
  ( theWrappedObject->setViewVolume(vol));
}

void PythonQtWrapper_SbProjector::setWorkingSpace(SbProjector* theWrappedObject, const SbMatrix&  space)
{
  ( theWrappedObject->setWorkingSpace(space));
}



PythonQtShell_SbSpherePlaneProjector::~PythonQtShell_SbSpherePlaneProjector() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SbProjector*  PythonQtShell_SbSpherePlaneProjector::copy() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("copy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbProjector*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SbProjector* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copy", methodInfo, result);
          } else {
            returnValue = *((SbProjector**)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbSpherePlaneProjector::copy();
}
SbRotation  PythonQtShell_SbSpherePlaneProjector::getRotation(const SbVec3f&  point10, const SbVec3f&  point21)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("getRotation");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbRotation" , "const SbVec3f&" , "const SbVec3f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      SbRotation returnValue{};
      void* args[3] = {nullptr, (void*)&point10, (void*)&point21};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getRotation", methodInfo, result);
          } else {
            returnValue = *((SbRotation*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbSpherePlaneProjector::getRotation(point10, point21);
}
SbVec3f  PythonQtShell_SbSpherePlaneProjector::project(const SbVec2f&  point0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("project");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbVec3f" , "const SbVec2f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      SbVec3f returnValue{};
      void* args[2] = {nullptr, (void*)&point0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("project", methodInfo, result);
          } else {
            returnValue = *((SbVec3f*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbSpherePlaneProjector::project(point0);
}
void PythonQtShell_SbSpherePlaneProjector::setViewVolume(const SbViewVolume&  vol0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setViewVolume");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbViewVolume&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&vol0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbSpherePlaneProjector::setViewVolume(vol0);
}
void PythonQtShell_SbSpherePlaneProjector::setWorkingSpace(const SbMatrix&  space0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setWorkingSpace");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbMatrix&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&space0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbSpherePlaneProjector::setWorkingSpace(space0);
}
void PythonQtShell_SbSpherePlaneProjector::setupTolerance()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setupTolerance");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={""};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbSpherePlaneProjector::setupTolerance();
}
SbSpherePlaneProjector* PythonQtWrapper_SbSpherePlaneProjector::new_SbSpherePlaneProjector(const SbSphere&  sph, float  edgeTol, bool  orientToEye)
{ 
return new PythonQtShell_SbSpherePlaneProjector(sph, edgeTol, orientToEye); }

SbSpherePlaneProjector* PythonQtWrapper_SbSpherePlaneProjector::new_SbSpherePlaneProjector(float  edgeTol, bool  orientToEye)
{ 
return new PythonQtShell_SbSpherePlaneProjector(edgeTol, orientToEye); }

SbRotation  PythonQtWrapper_SbSpherePlaneProjector::getRotation(SbSpherePlaneProjector* theWrappedObject, const SbVec3f&  point1, bool  tol1, const SbVec3f&  point2, bool  tol2)
{
  return ( ((PythonQtPublicPromoter_SbSpherePlaneProjector*)theWrappedObject)->promoted_getRotation(point1, tol1, point2, tol2));
}



PythonQtShell_SbSphereProjector::~PythonQtShell_SbSphereProjector() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SbProjector*  PythonQtShell_SbSphereProjector::copy() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("copy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbProjector*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SbProjector* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copy", methodInfo, result);
          } else {
            returnValue = *((SbProjector**)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return nullptr;
}
SbRotation  PythonQtShell_SbSphereProjector::getRotation(const SbVec3f&  point10, const SbVec3f&  point21)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("getRotation");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbRotation" , "const SbVec3f&" , "const SbVec3f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      SbRotation returnValue{};
      void* args[3] = {nullptr, (void*)&point10, (void*)&point21};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getRotation", methodInfo, result);
          } else {
            returnValue = *((SbRotation*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbRotation();
}
SbVec3f  PythonQtShell_SbSphereProjector::project(const SbVec2f&  point0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("project");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbVec3f" , "const SbVec2f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      SbVec3f returnValue{};
      void* args[2] = {nullptr, (void*)&point0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("project", methodInfo, result);
          } else {
            returnValue = *((SbVec3f*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbVec3f();
}
void PythonQtShell_SbSphereProjector::setViewVolume(const SbViewVolume&  vol0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setViewVolume");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbViewVolume&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&vol0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbSphereProjector::setViewVolume(vol0);
}
void PythonQtShell_SbSphereProjector::setWorkingSpace(const SbMatrix&  space0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setWorkingSpace");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbMatrix&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&space0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbSphereProjector::setWorkingSpace(space0);
}
SbSphereProjector* PythonQtWrapper_SbSphereProjector::new_SbSphereProjector(bool  orientToEye)
{ 
return new PythonQtShell_SbSphereProjector(orientToEye); }

SbSphereProjector* PythonQtWrapper_SbSphereProjector::new_SbSphereProjector(const SbSphere&  s, bool  orientToEye)
{ 
return new PythonQtShell_SbSphereProjector(s, orientToEye); }

SbRotation  PythonQtWrapper_SbSphereProjector::getRotation(SbSphereProjector* theWrappedObject, const SbVec3f&  point1, const SbVec3f&  point2)
{
  return ( theWrappedObject->getRotation(point1, point2));
}

const SbSphere*  PythonQtWrapper_SbSphereProjector::getSphere(SbSphereProjector* theWrappedObject) const
{
  return &( theWrappedObject->getSphere());
}

bool  PythonQtWrapper_SbSphereProjector::isFront(SbSphereProjector* theWrappedObject) const
{
  return ( theWrappedObject->isFront());
}

bool  PythonQtWrapper_SbSphereProjector::isOrientToEye(SbSphereProjector* theWrappedObject) const
{
  return ( theWrappedObject->isOrientToEye());
}

bool  PythonQtWrapper_SbSphereProjector::isPointInFront(SbSphereProjector* theWrappedObject, const SbVec3f&  point) const
{
  return ( theWrappedObject->isPointInFront(point));
}

SbVec3f  PythonQtWrapper_SbSphereProjector::projectAndGetRotation(SbSphereProjector* theWrappedObject, const SbVec2f&  point, SbRotation&  rot)
{
  return ( theWrappedObject->projectAndGetRotation(point, rot));
}

void PythonQtWrapper_SbSphereProjector::setFront(SbSphereProjector* theWrappedObject, bool  inFront)
{
  ( theWrappedObject->setFront(inFront));
}

void PythonQtWrapper_SbSphereProjector::setOrientToEye(SbSphereProjector* theWrappedObject, bool  orientToEye)
{
  ( theWrappedObject->setOrientToEye(orientToEye));
}

void PythonQtWrapper_SbSphereProjector::setSphere(SbSphereProjector* theWrappedObject, const SbSphere&  sph)
{
  ( theWrappedObject->setSphere(sph));
}



PythonQtShell_SbSphereSectionProjector::~PythonQtShell_SbSphereSectionProjector() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SbProjector*  PythonQtShell_SbSphereSectionProjector::copy() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("copy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbProjector*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SbProjector* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copy", methodInfo, result);
          } else {
            returnValue = *((SbProjector**)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbSphereSectionProjector::copy();
}
SbRotation  PythonQtShell_SbSphereSectionProjector::getRotation(const SbVec3f&  point10, const SbVec3f&  point21)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("getRotation");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbRotation" , "const SbVec3f&" , "const SbVec3f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      SbRotation returnValue{};
      void* args[3] = {nullptr, (void*)&point10, (void*)&point21};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getRotation", methodInfo, result);
          } else {
            returnValue = *((SbRotation*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbSphereSectionProjector::getRotation(point10, point21);
}
SbVec3f  PythonQtShell_SbSphereSectionProjector::project(const SbVec2f&  point0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("project");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbVec3f" , "const SbVec2f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      SbVec3f returnValue{};
      void* args[2] = {nullptr, (void*)&point0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("project", methodInfo, result);
          } else {
            returnValue = *((SbVec3f*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbSphereSectionProjector::project(point0);
}
void PythonQtShell_SbSphereSectionProjector::setViewVolume(const SbViewVolume&  vol0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setViewVolume");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbViewVolume&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&vol0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbSphereSectionProjector::setViewVolume(vol0);
}
void PythonQtShell_SbSphereSectionProjector::setWorkingSpace(const SbMatrix&  space0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setWorkingSpace");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbMatrix&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&space0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbSphereSectionProjector::setWorkingSpace(space0);
}
void PythonQtShell_SbSphereSectionProjector::setupTolerance()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setupTolerance");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={""};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbSphereSectionProjector::setupTolerance();
}
SbSphereSectionProjector* PythonQtWrapper_SbSphereSectionProjector::new_SbSphereSectionProjector(const SbSphere&  sph, float  edgeTol, bool  orientToEye)
{ 
return new PythonQtShell_SbSphereSectionProjector(sph, edgeTol, orientToEye); }

SbSphereSectionProjector* PythonQtWrapper_SbSphereSectionProjector::new_SbSphereSectionProjector(float  edgeTol, bool  orientToEye)
{ 
return new PythonQtShell_SbSphereSectionProjector(edgeTol, orientToEye); }

float  PythonQtWrapper_SbSphereSectionProjector::getRadialFactor(SbSphereSectionProjector* theWrappedObject) const
{
  return ( theWrappedObject->getRadialFactor());
}

float  PythonQtWrapper_SbSphereSectionProjector::getTolerance(SbSphereSectionProjector* theWrappedObject) const
{
  return ( theWrappedObject->getTolerance());
}

bool  PythonQtWrapper_SbSphereSectionProjector::isWithinTolerance(SbSphereSectionProjector* theWrappedObject, const SbVec3f&  point)
{
  return ( theWrappedObject->isWithinTolerance(point));
}

void PythonQtWrapper_SbSphereSectionProjector::setRadialFactor(SbSphereSectionProjector* theWrappedObject, float  rad)
{
  ( theWrappedObject->setRadialFactor(rad));
}

void PythonQtWrapper_SbSphereSectionProjector::setTolerance(SbSphereSectionProjector* theWrappedObject, float  edgeTol)
{
  ( theWrappedObject->setTolerance(edgeTol));
}

void PythonQtWrapper_SbSphereSectionProjector::setupTolerance(SbSphereSectionProjector* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_SbSphereSectionProjector*)theWrappedObject)->promoted_setupTolerance());
}



PythonQtShell_SbSphereSheetProjector::~PythonQtShell_SbSphereSheetProjector() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SbProjector*  PythonQtShell_SbSphereSheetProjector::copy() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("copy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbProjector*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SbProjector* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copy", methodInfo, result);
          } else {
            returnValue = *((SbProjector**)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbSphereSheetProjector::copy();
}
SbRotation  PythonQtShell_SbSphereSheetProjector::getRotation(const SbVec3f&  point10, const SbVec3f&  point21)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("getRotation");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbRotation" , "const SbVec3f&" , "const SbVec3f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      SbRotation returnValue{};
      void* args[3] = {nullptr, (void*)&point10, (void*)&point21};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getRotation", methodInfo, result);
          } else {
            returnValue = *((SbRotation*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbSphereSheetProjector::getRotation(point10, point21);
}
SbVec3f  PythonQtShell_SbSphereSheetProjector::project(const SbVec2f&  point0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("project");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbVec3f" , "const SbVec2f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      SbVec3f returnValue{};
      void* args[2] = {nullptr, (void*)&point0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("project", methodInfo, result);
          } else {
            returnValue = *((SbVec3f*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SbSphereSheetProjector::project(point0);
}
void PythonQtShell_SbSphereSheetProjector::setViewVolume(const SbViewVolume&  vol0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setViewVolume");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbViewVolume&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&vol0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbSphereSheetProjector::setViewVolume(vol0);
}
void PythonQtShell_SbSphereSheetProjector::setWorkingSpace(const SbMatrix&  space0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setWorkingSpace");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbMatrix&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&space0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SbSphereSheetProjector::setWorkingSpace(space0);
}
SbSphereSheetProjector* PythonQtWrapper_SbSphereSheetProjector::new_SbSphereSheetProjector(bool  orientToEye)
{ 
return new PythonQtShell_SbSphereSheetProjector(orientToEye); }

SbSphereSheetProjector* PythonQtWrapper_SbSphereSheetProjector::new_SbSphereSheetProjector(const SbSphere&  sph, bool  orientToEye)
{ 
return new PythonQtShell_SbSphereSheetProjector(sph, orientToEye); }

void PythonQtWrapper_SbSphereSheetProjector::setupPlane(SbSphereSheetProjector* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_SbSphereSheetProjector*)theWrappedObject)->promoted_setupPlane());
}


