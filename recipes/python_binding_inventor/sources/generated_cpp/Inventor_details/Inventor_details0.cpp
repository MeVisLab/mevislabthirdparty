#include "inventor_details0.h"
#include <Inventor/SoType.h>
#include <Inventor/details/SoDetail.h>
#include <Inventor/details/SoPointDetail.h>
#include <PythonQtConversion.h>
#include <PythonQtMethodInfo.h>
#include <PythonQtSignalReceiver.h>
#include <QVariant>

PythonQtShell_SoConeDetail::~PythonQtShell_SoConeDetail() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SoDetail*  PythonQtShell_SoConeDetail::copy() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("copy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoDetail*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoDetail* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copy", methodInfo, result);
          } else {
            returnValue = *((SoDetail**)args[0]);
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
  return SoConeDetail::copy();
}
SoConeDetail* PythonQtWrapper_SoConeDetail::new_SoConeDetail()
{ 
return new PythonQtShell_SoConeDetail(); }

SoType  PythonQtWrapper_SoConeDetail::static_SoConeDetail_getClassTypeId()
{
  return (SoConeDetail::getClassTypeId());
}

int  PythonQtWrapper_SoConeDetail::getPart(SoConeDetail* theWrappedObject) const
{
  return ( theWrappedObject->getPart());
}

void PythonQtWrapper_SoConeDetail::setPart(SoConeDetail* theWrappedObject, int  _part)
{
  ( theWrappedObject->setPart(_part));
}



PythonQtShell_SoCubeDetail::~PythonQtShell_SoCubeDetail() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SoDetail*  PythonQtShell_SoCubeDetail::copy() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("copy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoDetail*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoDetail* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copy", methodInfo, result);
          } else {
            returnValue = *((SoDetail**)args[0]);
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
  return SoCubeDetail::copy();
}
SoCubeDetail* PythonQtWrapper_SoCubeDetail::new_SoCubeDetail()
{ 
return new PythonQtShell_SoCubeDetail(); }

SoType  PythonQtWrapper_SoCubeDetail::static_SoCubeDetail_getClassTypeId()
{
  return (SoCubeDetail::getClassTypeId());
}

int  PythonQtWrapper_SoCubeDetail::getPart(SoCubeDetail* theWrappedObject) const
{
  return ( theWrappedObject->getPart());
}

void PythonQtWrapper_SoCubeDetail::setPart(SoCubeDetail* theWrappedObject, int  _part)
{
  ( theWrappedObject->setPart(_part));
}



PythonQtShell_SoCylinderDetail::~PythonQtShell_SoCylinderDetail() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SoDetail*  PythonQtShell_SoCylinderDetail::copy() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("copy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoDetail*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoDetail* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copy", methodInfo, result);
          } else {
            returnValue = *((SoDetail**)args[0]);
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
  return SoCylinderDetail::copy();
}
SoCylinderDetail* PythonQtWrapper_SoCylinderDetail::new_SoCylinderDetail()
{ 
return new PythonQtShell_SoCylinderDetail(); }

SoType  PythonQtWrapper_SoCylinderDetail::static_SoCylinderDetail_getClassTypeId()
{
  return (SoCylinderDetail::getClassTypeId());
}

int  PythonQtWrapper_SoCylinderDetail::getPart(SoCylinderDetail* theWrappedObject) const
{
  return ( theWrappedObject->getPart());
}

void PythonQtWrapper_SoCylinderDetail::setPart(SoCylinderDetail* theWrappedObject, int  _part)
{
  ( theWrappedObject->setPart(_part));
}



SoDetail*  PythonQtWrapper_SoDetail::copy(SoDetail* theWrappedObject) const
{
  return ( theWrappedObject->copy());
}

SoType  PythonQtWrapper_SoDetail::static_SoDetail_getClassTypeId()
{
  return (SoDetail::getClassTypeId());
}

bool  PythonQtWrapper_SoDetail::isOfType(SoDetail* theWrappedObject, SoType  type) const
{
  return ( theWrappedObject->isOfType(type));
}



PythonQtShell_SoFaceDetail::~PythonQtShell_SoFaceDetail() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SoDetail*  PythonQtShell_SoFaceDetail::copy() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("copy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoDetail*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoDetail* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copy", methodInfo, result);
          } else {
            returnValue = *((SoDetail**)args[0]);
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
  return SoFaceDetail::copy();
}
SoFaceDetail* PythonQtWrapper_SoFaceDetail::new_SoFaceDetail()
{ 
return new PythonQtShell_SoFaceDetail(); }

SoType  PythonQtWrapper_SoFaceDetail::static_SoFaceDetail_getClassTypeId()
{
  return (SoFaceDetail::getClassTypeId());
}

int  PythonQtWrapper_SoFaceDetail::getFaceIndex(SoFaceDetail* theWrappedObject) const
{
  return ( theWrappedObject->getFaceIndex());
}

int  PythonQtWrapper_SoFaceDetail::getNumPoints(SoFaceDetail* theWrappedObject) const
{
  return ( theWrappedObject->getNumPoints());
}

int  PythonQtWrapper_SoFaceDetail::getPartIndex(SoFaceDetail* theWrappedObject) const
{
  return ( theWrappedObject->getPartIndex());
}

const SoPointDetail*  PythonQtWrapper_SoFaceDetail::getPoint(SoFaceDetail* theWrappedObject, int  i) const
{
  return ( theWrappedObject->getPoint(i));
}

SoPointDetail*  PythonQtWrapper_SoFaceDetail::getPoints(SoFaceDetail* theWrappedObject)
{
  return ( theWrappedObject->getPoints());
}

void PythonQtWrapper_SoFaceDetail::setFaceIndex(SoFaceDetail* theWrappedObject, int  i)
{
  ( theWrappedObject->setFaceIndex(i));
}

void PythonQtWrapper_SoFaceDetail::setNumPoints(SoFaceDetail* theWrappedObject, int  num)
{
  ( theWrappedObject->setNumPoints(num));
}

void PythonQtWrapper_SoFaceDetail::setPartIndex(SoFaceDetail* theWrappedObject, int  i)
{
  ( theWrappedObject->setPartIndex(i));
}

void PythonQtWrapper_SoFaceDetail::setPoint(SoFaceDetail* theWrappedObject, int  index, const SoPointDetail*  pd)
{
  ( theWrappedObject->setPoint(index, pd));
}



PythonQtShell_SoLineDetail::~PythonQtShell_SoLineDetail() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SoDetail*  PythonQtShell_SoLineDetail::copy() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("copy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoDetail*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoDetail* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copy", methodInfo, result);
          } else {
            returnValue = *((SoDetail**)args[0]);
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
  return SoLineDetail::copy();
}
SoLineDetail* PythonQtWrapper_SoLineDetail::new_SoLineDetail()
{ 
return new PythonQtShell_SoLineDetail(); }

SoType  PythonQtWrapper_SoLineDetail::static_SoLineDetail_getClassTypeId()
{
  return (SoLineDetail::getClassTypeId());
}

int  PythonQtWrapper_SoLineDetail::getLineIndex(SoLineDetail* theWrappedObject) const
{
  return ( theWrappedObject->getLineIndex());
}

int  PythonQtWrapper_SoLineDetail::getPartIndex(SoLineDetail* theWrappedObject) const
{
  return ( theWrappedObject->getPartIndex());
}

const SoPointDetail*  PythonQtWrapper_SoLineDetail::getPoint0(SoLineDetail* theWrappedObject) const
{
  return ( theWrappedObject->getPoint0());
}

const SoPointDetail*  PythonQtWrapper_SoLineDetail::getPoint1(SoLineDetail* theWrappedObject) const
{
  return ( theWrappedObject->getPoint1());
}

void PythonQtWrapper_SoLineDetail::setLineIndex(SoLineDetail* theWrappedObject, int  i)
{
  ( theWrappedObject->setLineIndex(i));
}

void PythonQtWrapper_SoLineDetail::setPartIndex(SoLineDetail* theWrappedObject, int  i)
{
  ( theWrappedObject->setPartIndex(i));
}

void PythonQtWrapper_SoLineDetail::setPoint0(SoLineDetail* theWrappedObject, const SoPointDetail*  pd)
{
  ( theWrappedObject->setPoint0(pd));
}

void PythonQtWrapper_SoLineDetail::setPoint1(SoLineDetail* theWrappedObject, const SoPointDetail*  pd)
{
  ( theWrappedObject->setPoint1(pd));
}



PythonQtShell_SoPointDetail::~PythonQtShell_SoPointDetail() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SoDetail*  PythonQtShell_SoPointDetail::copy() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("copy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoDetail*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoDetail* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copy", methodInfo, result);
          } else {
            returnValue = *((SoDetail**)args[0]);
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
  return SoPointDetail::copy();
}
SoPointDetail* PythonQtWrapper_SoPointDetail::new_SoPointDetail()
{ 
return new PythonQtShell_SoPointDetail(); }

SoType  PythonQtWrapper_SoPointDetail::static_SoPointDetail_getClassTypeId()
{
  return (SoPointDetail::getClassTypeId());
}

int  PythonQtWrapper_SoPointDetail::getCoordinateIndex(SoPointDetail* theWrappedObject) const
{
  return ( theWrappedObject->getCoordinateIndex());
}

int  PythonQtWrapper_SoPointDetail::getMaterialIndex(SoPointDetail* theWrappedObject) const
{
  return ( theWrappedObject->getMaterialIndex());
}

int  PythonQtWrapper_SoPointDetail::getNormalIndex(SoPointDetail* theWrappedObject) const
{
  return ( theWrappedObject->getNormalIndex());
}

int  PythonQtWrapper_SoPointDetail::getTextureCoordIndex(SoPointDetail* theWrappedObject) const
{
  return ( theWrappedObject->getTextureCoordIndex());
}

void PythonQtWrapper_SoPointDetail::setCoordinateIndex(SoPointDetail* theWrappedObject, int  i)
{
  ( theWrappedObject->setCoordinateIndex(i));
}

void PythonQtWrapper_SoPointDetail::setMaterialIndex(SoPointDetail* theWrappedObject, int  i)
{
  ( theWrappedObject->setMaterialIndex(i));
}

void PythonQtWrapper_SoPointDetail::setNormalIndex(SoPointDetail* theWrappedObject, int  i)
{
  ( theWrappedObject->setNormalIndex(i));
}

void PythonQtWrapper_SoPointDetail::setTextureCoordIndex(SoPointDetail* theWrappedObject, int  i)
{
  ( theWrappedObject->setTextureCoordIndex(i));
}



PythonQtShell_SoTextDetail::~PythonQtShell_SoTextDetail() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SoDetail*  PythonQtShell_SoTextDetail::copy() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("copy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoDetail*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoDetail* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copy", methodInfo, result);
          } else {
            returnValue = *((SoDetail**)args[0]);
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
  return SoTextDetail::copy();
}
SoTextDetail* PythonQtWrapper_SoTextDetail::new_SoTextDetail()
{ 
return new PythonQtShell_SoTextDetail(); }

int  PythonQtWrapper_SoTextDetail::getCharacterIndex(SoTextDetail* theWrappedObject) const
{
  return ( theWrappedObject->getCharacterIndex());
}

SoType  PythonQtWrapper_SoTextDetail::static_SoTextDetail_getClassTypeId()
{
  return (SoTextDetail::getClassTypeId());
}

SoText3::Part  PythonQtWrapper_SoTextDetail::getPart(SoTextDetail* theWrappedObject) const
{
  return ( theWrappedObject->getPart());
}

int  PythonQtWrapper_SoTextDetail::getStringIndex(SoTextDetail* theWrappedObject) const
{
  return ( theWrappedObject->getStringIndex());
}

void PythonQtWrapper_SoTextDetail::setCharacterIndex(SoTextDetail* theWrappedObject, int  i)
{
  ( theWrappedObject->setCharacterIndex(i));
}

void PythonQtWrapper_SoTextDetail::setPart(SoTextDetail* theWrappedObject, SoText3::Part  p)
{
  ( theWrappedObject->setPart(p));
}

void PythonQtWrapper_SoTextDetail::setStringIndex(SoTextDetail* theWrappedObject, int  i)
{
  ( theWrappedObject->setStringIndex(i));
}


