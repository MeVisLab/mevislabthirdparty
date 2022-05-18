/*************************************************************************************
**
** Copyright 2022, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/
#include "Inventor_elements1.h"
#include <PythonQtConversion.h>
#include <PythonQtMethodInfo.h>
#include <PythonQtSignalReceiver.h>
#include <QVariant>
#include <Inventor/SbColor.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SoType.h>
#include <Inventor/elements/SoElement.h>
#include <Inventor/elements/SoLazyElement.h>
#include <Inventor/elements/SoNormalElement.h>
#include <Inventor/elements/SoProfileCoordinateElement.h>
#include <Inventor/elements/SoShapeStyleElement.h>
#include <Inventor/elements/SoTextureCoordinateElement.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoProfile.h>
#include <stdexcept>

PythonQtShell_SoGLTextureImageElement::~PythonQtShell_SoGLTextureImageElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoGLTextureImageElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLTextureImageElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoGLTextureImageElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoGLTextureImageElement::copyMatchInfo();
}
void PythonQtShell_SoGLTextureImageElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLTextureImageElement::init(state0);
}
bool  PythonQtShell_SoGLTextureImageElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoGLTextureImageElement::matches(elt0);
}
void PythonQtShell_SoGLTextureImageElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLTextureImageElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoGLTextureImageElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLTextureImageElement::push(state0);
}
void PythonQtShell_SoGLTextureImageElement::setElt(const SbVec2s&  s0, int  nc1, const unsigned char*  bytes2, int  wrapS3, int  wrapT4, int  model5, const SbColor&  blendColor6)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("setElt");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbVec2s&" , "int" , "const unsigned char*" , "int" , "int" , "int" , "const SbColor&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(8, argumentList);
      void* args[8] = {nullptr, (void*)&s0, (void*)&nc1, (void*)&bytes2, (void*)&wrapS3, (void*)&wrapT4, (void*)&model5, (void*)&blendColor6};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLTextureImageElement::setElt(s0, nc1, bytes2, wrapS3, wrapT4, model5, blendColor6);
}
SoGLTextureImageElement* PythonQtWrapper_SoGLTextureImageElement::new_SoGLTextureImageElement()
{ 
return new PythonQtShell_SoGLTextureImageElement(); }

int  PythonQtWrapper_SoGLTextureImageElement::static_SoGLTextureImageElement_getClassStackIndex()
{
  return (SoGLTextureImageElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoGLTextureImageElement::static_SoGLTextureImageElement_getClassTypeId()
{
  return (SoGLTextureImageElement::getClassTypeId());
}



PythonQtShell_SoGLTextureMatrixElement::~PythonQtShell_SoGLTextureMatrixElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoGLTextureMatrixElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLTextureMatrixElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoGLTextureMatrixElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoGLTextureMatrixElement::copyMatchInfo();
}
void PythonQtShell_SoGLTextureMatrixElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLTextureMatrixElement::init(state0);
}
void PythonQtShell_SoGLTextureMatrixElement::makeEltIdentity()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("makeEltIdentity");
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
  SoGLTextureMatrixElement::makeEltIdentity();
}
bool  PythonQtShell_SoGLTextureMatrixElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoGLTextureMatrixElement::matches(elt0);
}
void PythonQtShell_SoGLTextureMatrixElement::multElt(const SbMatrix&  matrix0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("multElt");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbMatrix&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&matrix0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLTextureMatrixElement::multElt(matrix0);
}
void PythonQtShell_SoGLTextureMatrixElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLTextureMatrixElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoGLTextureMatrixElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLTextureMatrixElement::push(state0);
}
void PythonQtShell_SoGLTextureMatrixElement::rotateEltBy(const SbRotation&  translation0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("rotateEltBy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbRotation&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&translation0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLTextureMatrixElement::rotateEltBy(translation0);
}
void PythonQtShell_SoGLTextureMatrixElement::scaleEltBy(const SbVec3f&  scaleFactor0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("scaleEltBy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbVec3f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&scaleFactor0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLTextureMatrixElement::scaleEltBy(scaleFactor0);
}
void PythonQtShell_SoGLTextureMatrixElement::translateEltBy(const SbVec3f&  translation0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("translateEltBy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbVec3f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&translation0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLTextureMatrixElement::translateEltBy(translation0);
}
SoGLTextureMatrixElement* PythonQtWrapper_SoGLTextureMatrixElement::new_SoGLTextureMatrixElement()
{ 
return new PythonQtShell_SoGLTextureMatrixElement(); }

int  PythonQtWrapper_SoGLTextureMatrixElement::static_SoGLTextureMatrixElement_getClassStackIndex()
{
  return (SoGLTextureMatrixElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoGLTextureMatrixElement::static_SoGLTextureMatrixElement_getClassTypeId()
{
  return (SoGLTextureMatrixElement::getClassTypeId());
}



PythonQtShell_SoGLUpdateAreaElement::~PythonQtShell_SoGLUpdateAreaElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoGLUpdateAreaElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLUpdateAreaElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoGLUpdateAreaElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoGLUpdateAreaElement::copyMatchInfo();
}
void PythonQtShell_SoGLUpdateAreaElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLUpdateAreaElement::init(state0);
}
bool  PythonQtShell_SoGLUpdateAreaElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoGLUpdateAreaElement::matches(elt0);
}
void PythonQtShell_SoGLUpdateAreaElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLUpdateAreaElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoGLUpdateAreaElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLUpdateAreaElement::push(state0);
}
SoGLUpdateAreaElement* PythonQtWrapper_SoGLUpdateAreaElement::new_SoGLUpdateAreaElement()
{ 
return new PythonQtShell_SoGLUpdateAreaElement(); }

bool  PythonQtWrapper_SoGLUpdateAreaElement::static_SoGLUpdateAreaElement_get(SoState*  state, SbVec2f&  origin, SbVec2f&  size)
{
  return (SoGLUpdateAreaElement::get(state, origin, size));
}

int  PythonQtWrapper_SoGLUpdateAreaElement::static_SoGLUpdateAreaElement_getClassStackIndex()
{
  return (SoGLUpdateAreaElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoGLUpdateAreaElement::static_SoGLUpdateAreaElement_getClassTypeId()
{
  return (SoGLUpdateAreaElement::getClassTypeId());
}

SbVec2f  PythonQtWrapper_SoGLUpdateAreaElement::static_SoGLUpdateAreaElement_getDefaultOrigin()
{
  return (SoGLUpdateAreaElement::getDefaultOrigin());
}

SbVec2f  PythonQtWrapper_SoGLUpdateAreaElement::static_SoGLUpdateAreaElement_getDefaultSize()
{
  return (SoGLUpdateAreaElement::getDefaultSize());
}

void PythonQtWrapper_SoGLUpdateAreaElement::static_SoGLUpdateAreaElement_set(SoState*  state, const SbVec2f&  origin, const SbVec2f&  size)
{
  (SoGLUpdateAreaElement::set(state, origin, size));
}



PythonQtShell_SoGLViewingMatrixElement::~PythonQtShell_SoGLViewingMatrixElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoGLViewingMatrixElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLViewingMatrixElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoGLViewingMatrixElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoGLViewingMatrixElement::copyMatchInfo();
}
void PythonQtShell_SoGLViewingMatrixElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLViewingMatrixElement::init(state0);
}
bool  PythonQtShell_SoGLViewingMatrixElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoGLViewingMatrixElement::matches(elt0);
}
void PythonQtShell_SoGLViewingMatrixElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLViewingMatrixElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoGLViewingMatrixElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLViewingMatrixElement::push(state0);
}
void PythonQtShell_SoGLViewingMatrixElement::setElt(const SbMatrix&  matrix0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("setElt");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbMatrix&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&matrix0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLViewingMatrixElement::setElt(matrix0);
}
SoGLViewingMatrixElement* PythonQtWrapper_SoGLViewingMatrixElement::new_SoGLViewingMatrixElement()
{ 
return new PythonQtShell_SoGLViewingMatrixElement(); }

int  PythonQtWrapper_SoGLViewingMatrixElement::static_SoGLViewingMatrixElement_getClassStackIndex()
{
  return (SoGLViewingMatrixElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoGLViewingMatrixElement::static_SoGLViewingMatrixElement_getClassTypeId()
{
  return (SoGLViewingMatrixElement::getClassTypeId());
}



PythonQtShell_SoGLViewportRegionElement::~PythonQtShell_SoGLViewportRegionElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoGLViewportRegionElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLViewportRegionElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoGLViewportRegionElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoGLViewportRegionElement::copyMatchInfo();
}
void PythonQtShell_SoGLViewportRegionElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLViewportRegionElement::init(state0);
}
bool  PythonQtShell_SoGLViewportRegionElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoGLViewportRegionElement::matches(elt0);
}
void PythonQtShell_SoGLViewportRegionElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLViewportRegionElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoGLViewportRegionElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLViewportRegionElement::push(state0);
}
void PythonQtShell_SoGLViewportRegionElement::setElt(const SbViewportRegion&  vpReg0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("setElt");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbViewportRegion&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&vpReg0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLViewportRegionElement::setElt(vpReg0);
}
SoGLViewportRegionElement* PythonQtWrapper_SoGLViewportRegionElement::new_SoGLViewportRegionElement()
{ 
return new PythonQtShell_SoGLViewportRegionElement(); }

int  PythonQtWrapper_SoGLViewportRegionElement::static_SoGLViewportRegionElement_getClassStackIndex()
{
  return (SoGLViewportRegionElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoGLViewportRegionElement::static_SoGLViewportRegionElement_getClassTypeId()
{
  return (SoGLViewportRegionElement::getClassTypeId());
}



PythonQtShell_SoInt32Element::~PythonQtShell_SoInt32Element() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoInt32Element::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoInt32Element::captureThis(state0);
}
SoElement*  PythonQtShell_SoInt32Element::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoInt32Element::copyMatchInfo();
}
void PythonQtShell_SoInt32Element::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoInt32Element::init(state0);
}
bool  PythonQtShell_SoInt32Element::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoInt32Element::matches(elt0);
}
void PythonQtShell_SoInt32Element::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoInt32Element::pop(state0, prevTopElement1);
}
void PythonQtShell_SoInt32Element::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoInt32Element::push(state0);
}
void PythonQtShell_SoInt32Element::setElt(int  value0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("setElt");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "int"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&value0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoInt32Element::setElt(value0);
}
SoInt32Element* PythonQtWrapper_SoInt32Element::new_SoInt32Element()
{ 
return new PythonQtShell_SoInt32Element(); }

int  PythonQtWrapper_SoInt32Element::static_SoInt32Element_get(int  stackIndex, SoState*  state)
{
  return (SoInt32Element::get(stackIndex, state));
}

int  PythonQtWrapper_SoInt32Element::static_SoInt32Element_getClassStackIndex()
{
  return (SoInt32Element::getClassStackIndex());
}

SoType  PythonQtWrapper_SoInt32Element::static_SoInt32Element_getClassTypeId()
{
  return (SoInt32Element::getClassTypeId());
}

void PythonQtWrapper_SoInt32Element::static_SoInt32Element_set(int  stackIndex, SoState*  state, int  value)
{
  (SoInt32Element::set(stackIndex, state, value));
}

void PythonQtWrapper_SoInt32Element::setElt(SoInt32Element* theWrappedObject, int  value)
{
  ( theWrappedObject->setElt(value));
}



PythonQtShell_SoLazyElement::~PythonQtShell_SoLazyElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoLazyElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoLazyElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoLazyElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoLazyElement::copyMatchInfo();
}
void PythonQtShell_SoLazyElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoLazyElement::init(state0);
}
bool  PythonQtShell_SoLazyElement::matches(const SoElement*  arg__1) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&arg__1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoLazyElement::matches(arg__1);
}
void PythonQtShell_SoLazyElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoLazyElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoLazyElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoLazyElement::push(state0);
}
void PythonQtShell_SoLazyElement::registerGetDependence(SoState*  arg__1, unsigned int  arg__2)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("registerGetDependence");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "unsigned int"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&arg__1, (void*)&arg__2};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoLazyElement::registerGetDependence(arg__1, arg__2);
}
void PythonQtShell_SoLazyElement::registerRedundantSet(SoState*  arg__1, unsigned int  arg__2)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("registerRedundantSet");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "unsigned int"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&arg__1, (void*)&arg__2};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoLazyElement::registerRedundantSet(arg__1, arg__2);
}
SoLazyElement* PythonQtWrapper_SoLazyElement::new_SoLazyElement()
{ 
return new PythonQtShell_SoLazyElement(); }

void PythonQtWrapper_SoLazyElement::static_SoLazyElement_drawArrays(SoState*  state, GLenum  mode, GLint  first, GLsizei  count)
{
  (SoLazyElement::drawArrays(state, mode, first, count));
}

void PythonQtWrapper_SoLazyElement::static_SoLazyElement_drawElements(SoState*  state, GLenum  mode, GLsizei  count, GLenum  type, const GLvoid*  indices)
{
  (SoLazyElement::drawElements(state, mode, count, type, indices));
}

const SbColor*  PythonQtWrapper_SoLazyElement::static_SoLazyElement_getAmbient(SoState*  arg__1)
{
  return &(SoLazyElement::getAmbient(arg__1));
}

bool  PythonQtWrapper_SoLazyElement::static_SoLazyElement_getBlending(SoState*  arg__1)
{
  return (SoLazyElement::getBlending(arg__1));
}

int  PythonQtWrapper_SoLazyElement::static_SoLazyElement_getClassStackIndex()
{
  return (SoLazyElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoLazyElement::static_SoLazyElement_getClassTypeId()
{
  return (SoLazyElement::getClassTypeId());
}

bool  PythonQtWrapper_SoLazyElement::static_SoLazyElement_getColorMaterial(SoState*  arg__1)
{
  return (SoLazyElement::getColorMaterial(arg__1));
}

SbColor  PythonQtWrapper_SoLazyElement::static_SoLazyElement_getDefaultAmbient()
{
  return (SoLazyElement::getDefaultAmbient());
}

SbColor  PythonQtWrapper_SoLazyElement::static_SoLazyElement_getDefaultDiffuse()
{
  return (SoLazyElement::getDefaultDiffuse());
}

SbColor  PythonQtWrapper_SoLazyElement::static_SoLazyElement_getDefaultEmissive()
{
  return (SoLazyElement::getDefaultEmissive());
}

int  PythonQtWrapper_SoLazyElement::static_SoLazyElement_getDefaultLightModel()
{
  return (SoLazyElement::getDefaultLightModel());
}

unsigned int  PythonQtWrapper_SoLazyElement::static_SoLazyElement_getDefaultPacked()
{
  return (SoLazyElement::getDefaultPacked());
}

float  PythonQtWrapper_SoLazyElement::static_SoLazyElement_getDefaultShininess()
{
  return (SoLazyElement::getDefaultShininess());
}

SbColor  PythonQtWrapper_SoLazyElement::static_SoLazyElement_getDefaultSpecular()
{
  return (SoLazyElement::getDefaultSpecular());
}

float  PythonQtWrapper_SoLazyElement::static_SoLazyElement_getDefaultTransparency()
{
  return (SoLazyElement::getDefaultTransparency());
}

const SbColor*  PythonQtWrapper_SoLazyElement::static_SoLazyElement_getDiffuse(SoState*  state, int  index)
{
  return &(SoLazyElement::getDiffuse(state, index));
}

const SbColor*  PythonQtWrapper_SoLazyElement::getDiffusePointer(SoLazyElement* theWrappedObject) const
{
  return ( theWrappedObject->getDiffusePointer());
}

const SbColor*  PythonQtWrapper_SoLazyElement::static_SoLazyElement_getEmissive(SoState*  arg__1)
{
  return &(SoLazyElement::getEmissive(arg__1));
}

SoLazyElement*  PythonQtWrapper_SoLazyElement::static_SoLazyElement_getInstance(SoState*  state)
{
  return (SoLazyElement::getInstance(state));
}

int  PythonQtWrapper_SoLazyElement::static_SoLazyElement_getLightModel(SoState*  arg__1)
{
  return (SoLazyElement::getLightModel(arg__1));
}

int  PythonQtWrapper_SoLazyElement::getNumDiffuse(SoLazyElement* theWrappedObject) const
{
  return ( theWrappedObject->getNumDiffuse());
}

int  PythonQtWrapper_SoLazyElement::static_SoLazyElement_getNumPatterns()
{
  return (PythonQtPublicPromoter_SoLazyElement::promoted_getNumPatterns());
}

int  PythonQtWrapper_SoLazyElement::getNumTransparencies(SoLazyElement* theWrappedObject) const
{
  return ( theWrappedObject->getNumTransparencies());
}

const unsigned int*  PythonQtWrapper_SoLazyElement::static_SoLazyElement_getPackedColors(SoState*  arg__1)
{
  return (SoLazyElement::getPackedColors(arg__1));
}

const unsigned int*  PythonQtWrapper_SoLazyElement::getPackedPointer(SoLazyElement* theWrappedObject) const
{
  return ( theWrappedObject->getPackedPointer());
}

float  PythonQtWrapper_SoLazyElement::static_SoLazyElement_getShininess(SoState*  arg__1)
{
  return (SoLazyElement::getShininess(arg__1));
}

const SbColor*  PythonQtWrapper_SoLazyElement::static_SoLazyElement_getSpecular(SoState*  arg__1)
{
  return &(SoLazyElement::getSpecular(arg__1));
}

float  PythonQtWrapper_SoLazyElement::static_SoLazyElement_getTransparency(SoState*  arg__1, int  index)
{
  return (SoLazyElement::getTransparency(arg__1, index));
}

const float*  PythonQtWrapper_SoLazyElement::getTransparencyPointer(SoLazyElement* theWrappedObject) const
{
  return ( theWrappedObject->getTransparencyPointer());
}

SoLazyElement*  PythonQtWrapper_SoLazyElement::static_SoLazyElement_getWInstance(SoState*  state)
{
  return (SoLazyElement::getWInstance(state));
}

bool  PythonQtWrapper_SoLazyElement::isPacked(SoLazyElement* theWrappedObject) const
{
  return ( theWrappedObject->isPacked());
}

bool  PythonQtWrapper_SoLazyElement::isTransparent(SoLazyElement* theWrappedObject) const
{
  return ( theWrappedObject->isTransparent());
}

void PythonQtWrapper_SoLazyElement::registerGetDependence(SoLazyElement* theWrappedObject, SoState*  arg__1, unsigned int  arg__2)
{
  ( ((PythonQtPublicPromoter_SoLazyElement*)theWrappedObject)->promoted_registerGetDependence(arg__1, arg__2));
}

void PythonQtWrapper_SoLazyElement::registerRedundantSet(SoLazyElement* theWrappedObject, SoState*  arg__1, unsigned int  arg__2)
{
  ( ((PythonQtPublicPromoter_SoLazyElement*)theWrappedObject)->promoted_registerRedundantSet(arg__1, arg__2));
}

void PythonQtWrapper_SoLazyElement::static_SoLazyElement_setAmbient(SoState*  state, const SbColor*  color)
{
  (SoLazyElement::setAmbient(state, color));
}

void PythonQtWrapper_SoLazyElement::static_SoLazyElement_setBlending(SoState*  state, bool  value)
{
  (SoLazyElement::setBlending(state, value));
}

void PythonQtWrapper_SoLazyElement::static_SoLazyElement_setColorMaterial(SoState*  state, bool  value)
{
  (SoLazyElement::setColorMaterial(state, value));
}

void PythonQtWrapper_SoLazyElement::static_SoLazyElement_setEmissive(SoState*  state, const SbColor*  color)
{
  (SoLazyElement::setEmissive(state, color));
}

void PythonQtWrapper_SoLazyElement::static_SoLazyElement_setLightModel(SoState*  state, const int  model)
{
  (SoLazyElement::setLightModel(state, model));
}

void PythonQtWrapper_SoLazyElement::static_SoLazyElement_setOverrideBlending(SoState*  state, bool  flag)
{
  (SoLazyElement::setOverrideBlending(state, flag));
}

void PythonQtWrapper_SoLazyElement::static_SoLazyElement_setPacked(SoState*  state, SoNode*  node, int  numColors, const unsigned int*  colors)
{
  (SoLazyElement::setPacked(state, node, numColors, colors));
}

void PythonQtWrapper_SoLazyElement::static_SoLazyElement_setShininess(SoState*  state, float  value)
{
  (SoLazyElement::setShininess(state, value));
}

void PythonQtWrapper_SoLazyElement::static_SoLazyElement_setSpecular(SoState*  state, const SbColor*  color)
{
  (SoLazyElement::setSpecular(state, color));
}

void PythonQtWrapper_SoLazyElement::static_SoLazyElement_setTransparencyType(SoState*  state, int  type)
{
  (SoLazyElement::setTransparencyType(state, type));
}

void PythonQtWrapper_SoLazyElement::static_SoLazyElement_setUseVertexAttributes(SoState*  state, bool  flag)
{
  (SoLazyElement::setUseVertexAttributes(state, flag));
}

bool  PythonQtWrapper_SoLazyElement::static_SoLazyElement_shouldUseVertexAttributes(SoState*  state)
{
  return (SoLazyElement::shouldUseVertexAttributes(state));
}



PythonQtShell_SoLightAttenuationElement::~PythonQtShell_SoLightAttenuationElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoLightAttenuationElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoLightAttenuationElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoLightAttenuationElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoLightAttenuationElement::copyMatchInfo();
}
void PythonQtShell_SoLightAttenuationElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoLightAttenuationElement::init(state0);
}
bool  PythonQtShell_SoLightAttenuationElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoLightAttenuationElement::matches(elt0);
}
void PythonQtShell_SoLightAttenuationElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoLightAttenuationElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoLightAttenuationElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoLightAttenuationElement::push(state0);
}
SoLightAttenuationElement* PythonQtWrapper_SoLightAttenuationElement::new_SoLightAttenuationElement()
{ 
return new PythonQtShell_SoLightAttenuationElement(); }

const SbVec3f*  PythonQtWrapper_SoLightAttenuationElement::static_SoLightAttenuationElement_get(SoState*  state)
{
  return &(SoLightAttenuationElement::get(state));
}

int  PythonQtWrapper_SoLightAttenuationElement::static_SoLightAttenuationElement_getClassStackIndex()
{
  return (SoLightAttenuationElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoLightAttenuationElement::static_SoLightAttenuationElement_getClassTypeId()
{
  return (SoLightAttenuationElement::getClassTypeId());
}

SbVec3f  PythonQtWrapper_SoLightAttenuationElement::static_SoLightAttenuationElement_getDefault()
{
  return (SoLightAttenuationElement::getDefault());
}

void PythonQtWrapper_SoLightAttenuationElement::static_SoLightAttenuationElement_set(SoState*  state, SoNode*  node, const SbVec3f&  attenuation)
{
  (SoLightAttenuationElement::set(state, node, attenuation));
}



PythonQtShell_SoLinePatternElement::~PythonQtShell_SoLinePatternElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoLinePatternElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoLinePatternElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoLinePatternElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoLinePatternElement::copyMatchInfo();
}
void PythonQtShell_SoLinePatternElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoLinePatternElement::init(state0);
}
bool  PythonQtShell_SoLinePatternElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoLinePatternElement::matches(elt0);
}
void PythonQtShell_SoLinePatternElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoLinePatternElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoLinePatternElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoLinePatternElement::push(state0);
}
void PythonQtShell_SoLinePatternElement::setElt(int  value0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("setElt");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "int"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&value0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoLinePatternElement::setElt(value0);
}
SoLinePatternElement* PythonQtWrapper_SoLinePatternElement::new_SoLinePatternElement()
{ 
return new PythonQtShell_SoLinePatternElement(); }

int  PythonQtWrapper_SoLinePatternElement::static_SoLinePatternElement_getClassStackIndex()
{
  return (SoLinePatternElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoLinePatternElement::static_SoLinePatternElement_getClassTypeId()
{
  return (SoLinePatternElement::getClassTypeId());
}



PythonQtShell_SoLineWidthElement::~PythonQtShell_SoLineWidthElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoLineWidthElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoLineWidthElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoLineWidthElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoLineWidthElement::copyMatchInfo();
}
void PythonQtShell_SoLineWidthElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoLineWidthElement::init(state0);
}
bool  PythonQtShell_SoLineWidthElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoLineWidthElement::matches(elt0);
}
void PythonQtShell_SoLineWidthElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoLineWidthElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoLineWidthElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoLineWidthElement::push(state0);
}
void PythonQtShell_SoLineWidthElement::setElt(float  value0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("setElt");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "float"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&value0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoLineWidthElement::setElt(value0);
}
SoLineWidthElement* PythonQtWrapper_SoLineWidthElement::new_SoLineWidthElement()
{ 
return new PythonQtShell_SoLineWidthElement(); }

float  PythonQtWrapper_SoLineWidthElement::static_SoLineWidthElement_get(SoState*  state)
{
  return (SoLineWidthElement::get(state));
}

int  PythonQtWrapper_SoLineWidthElement::static_SoLineWidthElement_getClassStackIndex()
{
  return (SoLineWidthElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoLineWidthElement::static_SoLineWidthElement_getClassTypeId()
{
  return (SoLineWidthElement::getClassTypeId());
}

float  PythonQtWrapper_SoLineWidthElement::static_SoLineWidthElement_getDefault()
{
  return (SoLineWidthElement::getDefault());
}

void PythonQtWrapper_SoLineWidthElement::static_SoLineWidthElement_set(SoState*  state, float  width)
{
  (SoLineWidthElement::set(state, width));
}



PythonQtShell_SoLocalBBoxMatrixElement::~PythonQtShell_SoLocalBBoxMatrixElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoLocalBBoxMatrixElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoLocalBBoxMatrixElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoLocalBBoxMatrixElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoLocalBBoxMatrixElement::copyMatchInfo();
}
void PythonQtShell_SoLocalBBoxMatrixElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoLocalBBoxMatrixElement::init(state0);
}
bool  PythonQtShell_SoLocalBBoxMatrixElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoLocalBBoxMatrixElement::matches(elt0);
}
void PythonQtShell_SoLocalBBoxMatrixElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoLocalBBoxMatrixElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoLocalBBoxMatrixElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoLocalBBoxMatrixElement::push(state0);
}
SoLocalBBoxMatrixElement* PythonQtWrapper_SoLocalBBoxMatrixElement::new_SoLocalBBoxMatrixElement()
{ 
return new PythonQtShell_SoLocalBBoxMatrixElement(); }

const SbMatrix*  PythonQtWrapper_SoLocalBBoxMatrixElement::static_SoLocalBBoxMatrixElement_get(SoState*  state)
{
  return &(SoLocalBBoxMatrixElement::get(state));
}

int  PythonQtWrapper_SoLocalBBoxMatrixElement::static_SoLocalBBoxMatrixElement_getClassStackIndex()
{
  return (SoLocalBBoxMatrixElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoLocalBBoxMatrixElement::static_SoLocalBBoxMatrixElement_getClassTypeId()
{
  return (SoLocalBBoxMatrixElement::getClassTypeId());
}

void PythonQtWrapper_SoLocalBBoxMatrixElement::static_SoLocalBBoxMatrixElement_makeIdentity(SoState*  state)
{
  (SoLocalBBoxMatrixElement::makeIdentity(state));
}

void PythonQtWrapper_SoLocalBBoxMatrixElement::static_SoLocalBBoxMatrixElement_mult(SoState*  state, const SbMatrix&  matrix)
{
  (SoLocalBBoxMatrixElement::mult(state, matrix));
}

void PythonQtWrapper_SoLocalBBoxMatrixElement::static_SoLocalBBoxMatrixElement_popMatrix(SoState*  state, const SbMatrix&  m)
{
  (SoLocalBBoxMatrixElement::popMatrix(state, m));
}

SbMatrix  PythonQtWrapper_SoLocalBBoxMatrixElement::static_SoLocalBBoxMatrixElement_pushMatrix(SoState*  state)
{
  return (SoLocalBBoxMatrixElement::pushMatrix(state));
}

void PythonQtWrapper_SoLocalBBoxMatrixElement::static_SoLocalBBoxMatrixElement_resetAll(SoState*  state)
{
  (SoLocalBBoxMatrixElement::resetAll(state));
}

void PythonQtWrapper_SoLocalBBoxMatrixElement::static_SoLocalBBoxMatrixElement_rotateBy(SoState*  state, const SbRotation&  rotation)
{
  (SoLocalBBoxMatrixElement::rotateBy(state, rotation));
}

void PythonQtWrapper_SoLocalBBoxMatrixElement::static_SoLocalBBoxMatrixElement_scaleBy(SoState*  state, const SbVec3f&  scaleFactor)
{
  (SoLocalBBoxMatrixElement::scaleBy(state, scaleFactor));
}

void PythonQtWrapper_SoLocalBBoxMatrixElement::static_SoLocalBBoxMatrixElement_set(SoState*  state, const SbMatrix&  matrix)
{
  (SoLocalBBoxMatrixElement::set(state, matrix));
}

void PythonQtWrapper_SoLocalBBoxMatrixElement::static_SoLocalBBoxMatrixElement_translateBy(SoState*  state, const SbVec3f&  translation)
{
  (SoLocalBBoxMatrixElement::translateBy(state, translation));
}



PythonQtShell_SoMaterialBindingElement::~PythonQtShell_SoMaterialBindingElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoMaterialBindingElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoMaterialBindingElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoMaterialBindingElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoMaterialBindingElement::copyMatchInfo();
}
void PythonQtShell_SoMaterialBindingElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoMaterialBindingElement::init(state0);
}
bool  PythonQtShell_SoMaterialBindingElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoMaterialBindingElement::matches(elt0);
}
void PythonQtShell_SoMaterialBindingElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoMaterialBindingElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoMaterialBindingElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoMaterialBindingElement::push(state0);
}
void PythonQtShell_SoMaterialBindingElement::setElt(int  value0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("setElt");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "int"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&value0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoMaterialBindingElement::setElt(value0);
}
SoMaterialBindingElement* PythonQtWrapper_SoMaterialBindingElement::new_SoMaterialBindingElement()
{ 
return new PythonQtShell_SoMaterialBindingElement(); }

SoMaterialBindingElement::Binding  PythonQtWrapper_SoMaterialBindingElement::static_SoMaterialBindingElement_get(SoState*  state)
{
  return (SoMaterialBindingElement::get(state));
}

int  PythonQtWrapper_SoMaterialBindingElement::static_SoMaterialBindingElement_getClassStackIndex()
{
  return (SoMaterialBindingElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoMaterialBindingElement::static_SoMaterialBindingElement_getClassTypeId()
{
  return (SoMaterialBindingElement::getClassTypeId());
}

SoMaterialBindingElement::Binding  PythonQtWrapper_SoMaterialBindingElement::static_SoMaterialBindingElement_getDefault()
{
  return (SoMaterialBindingElement::getDefault());
}

void PythonQtWrapper_SoMaterialBindingElement::static_SoMaterialBindingElement_set(SoState*  state, SoMaterialBindingElement::Binding  binding)
{
  (SoMaterialBindingElement::set(state, binding));
}



PythonQtShell_SoModelMatrixElement::~PythonQtShell_SoModelMatrixElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoModelMatrixElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoModelMatrixElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoModelMatrixElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoModelMatrixElement::copyMatchInfo();
}
void PythonQtShell_SoModelMatrixElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoModelMatrixElement::init(state0);
}
void PythonQtShell_SoModelMatrixElement::makeEltIdentity()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("makeEltIdentity");
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
  SoModelMatrixElement::makeEltIdentity();
}
bool  PythonQtShell_SoModelMatrixElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoModelMatrixElement::matches(elt0);
}
void PythonQtShell_SoModelMatrixElement::multElt(const SbMatrix&  matrix0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("multElt");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbMatrix&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&matrix0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoModelMatrixElement::multElt(matrix0);
}
void PythonQtShell_SoModelMatrixElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoModelMatrixElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoModelMatrixElement::popMatrixElt(const SbMatrix&  m0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("popMatrixElt");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbMatrix&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&m0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoModelMatrixElement::popMatrixElt(m0);
}
void PythonQtShell_SoModelMatrixElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoModelMatrixElement::push(state0);
}
SbMatrix  PythonQtShell_SoModelMatrixElement::pushMatrixElt()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pushMatrixElt");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbMatrix"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SbMatrix returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("pushMatrixElt", methodInfo, result);
          } else {
            returnValue = *((SbMatrix*)args[0]);
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
  return SoModelMatrixElement::pushMatrixElt();
}
void PythonQtShell_SoModelMatrixElement::rotateEltBy(const SbRotation&  translation0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("rotateEltBy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbRotation&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&translation0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoModelMatrixElement::rotateEltBy(translation0);
}
void PythonQtShell_SoModelMatrixElement::scaleEltBy(const SbVec3f&  scaleFactor0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("scaleEltBy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbVec3f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&scaleFactor0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoModelMatrixElement::scaleEltBy(scaleFactor0);
}
void PythonQtShell_SoModelMatrixElement::setElt(const SbMatrix&  matrix0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("setElt");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbMatrix&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&matrix0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoModelMatrixElement::setElt(matrix0);
}
void PythonQtShell_SoModelMatrixElement::translateEltBy(const SbVec3f&  translation0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("translateEltBy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbVec3f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&translation0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoModelMatrixElement::translateEltBy(translation0);
}
SoModelMatrixElement* PythonQtWrapper_SoModelMatrixElement::new_SoModelMatrixElement()
{ 
return new PythonQtShell_SoModelMatrixElement(); }

const SbMatrix*  PythonQtWrapper_SoModelMatrixElement::static_SoModelMatrixElement_get(SoState*  state)
{
  return &(SoModelMatrixElement::get(state));
}

const SbMatrix*  PythonQtWrapper_SoModelMatrixElement::static_SoModelMatrixElement_get(SoState*  state, bool&  isIdent)
{
  return &(SoModelMatrixElement::get(state, isIdent));
}

int  PythonQtWrapper_SoModelMatrixElement::static_SoModelMatrixElement_getClassStackIndex()
{
  return (SoModelMatrixElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoModelMatrixElement::static_SoModelMatrixElement_getClassTypeId()
{
  return (SoModelMatrixElement::getClassTypeId());
}

const SbMatrix*  PythonQtWrapper_SoModelMatrixElement::static_SoModelMatrixElement_getCombinedCullMatrix(SoState*  state)
{
  return &(SoModelMatrixElement::getCombinedCullMatrix(state));
}

void PythonQtWrapper_SoModelMatrixElement::makeEltIdentity(SoModelMatrixElement* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_SoModelMatrixElement*)theWrappedObject)->promoted_makeEltIdentity());
}

void PythonQtWrapper_SoModelMatrixElement::static_SoModelMatrixElement_makeIdentity(SoState*  state, SoNode*  node)
{
  (SoModelMatrixElement::makeIdentity(state, node));
}

void PythonQtWrapper_SoModelMatrixElement::static_SoModelMatrixElement_mult(SoState*  state, SoNode*  node, const SbMatrix&  matrix)
{
  (SoModelMatrixElement::mult(state, node, matrix));
}

void PythonQtWrapper_SoModelMatrixElement::multElt(SoModelMatrixElement* theWrappedObject, const SbMatrix&  matrix)
{
  ( ((PythonQtPublicPromoter_SoModelMatrixElement*)theWrappedObject)->promoted_multElt(matrix));
}

void PythonQtWrapper_SoModelMatrixElement::static_SoModelMatrixElement_popMatrix(SoState*  state, const SbMatrix&  m)
{
  (SoModelMatrixElement::popMatrix(state, m));
}

void PythonQtWrapper_SoModelMatrixElement::popMatrixElt(SoModelMatrixElement* theWrappedObject, const SbMatrix&  m)
{
  ( ((PythonQtPublicPromoter_SoModelMatrixElement*)theWrappedObject)->promoted_popMatrixElt(m));
}

SbMatrix  PythonQtWrapper_SoModelMatrixElement::static_SoModelMatrixElement_pushMatrix(SoState*  state)
{
  return (SoModelMatrixElement::pushMatrix(state));
}

SbMatrix  PythonQtWrapper_SoModelMatrixElement::pushMatrixElt(SoModelMatrixElement* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_SoModelMatrixElement*)theWrappedObject)->promoted_pushMatrixElt());
}

void PythonQtWrapper_SoModelMatrixElement::static_SoModelMatrixElement_rotateBy(SoState*  state, SoNode*  node, const SbRotation&  rotation)
{
  (SoModelMatrixElement::rotateBy(state, node, rotation));
}

void PythonQtWrapper_SoModelMatrixElement::rotateEltBy(SoModelMatrixElement* theWrappedObject, const SbRotation&  translation)
{
  ( ((PythonQtPublicPromoter_SoModelMatrixElement*)theWrappedObject)->promoted_rotateEltBy(translation));
}

void PythonQtWrapper_SoModelMatrixElement::static_SoModelMatrixElement_scaleBy(SoState*  state, SoNode*  node, const SbVec3f&  scaleFactor)
{
  (SoModelMatrixElement::scaleBy(state, node, scaleFactor));
}

void PythonQtWrapper_SoModelMatrixElement::scaleEltBy(SoModelMatrixElement* theWrappedObject, const SbVec3f&  scaleFactor)
{
  ( ((PythonQtPublicPromoter_SoModelMatrixElement*)theWrappedObject)->promoted_scaleEltBy(scaleFactor));
}

void PythonQtWrapper_SoModelMatrixElement::static_SoModelMatrixElement_set(SoState*  state, SoNode*  node, const SbMatrix&  matrix)
{
  (SoModelMatrixElement::set(state, node, matrix));
}

void PythonQtWrapper_SoModelMatrixElement::static_SoModelMatrixElement_setCullMatrix(SoState*  state, SoNode*  node, const SbMatrix&  matrix)
{
  (SoModelMatrixElement::setCullMatrix(state, node, matrix));
}

void PythonQtWrapper_SoModelMatrixElement::setElt(SoModelMatrixElement* theWrappedObject, const SbMatrix&  matrix)
{
  ( ((PythonQtPublicPromoter_SoModelMatrixElement*)theWrappedObject)->promoted_setElt(matrix));
}

void PythonQtWrapper_SoModelMatrixElement::static_SoModelMatrixElement_translateBy(SoState*  state, SoNode*  node, const SbVec3f&  translation)
{
  (SoModelMatrixElement::translateBy(state, node, translation));
}

void PythonQtWrapper_SoModelMatrixElement::translateEltBy(SoModelMatrixElement* theWrappedObject, const SbVec3f&  translation)
{
  ( ((PythonQtPublicPromoter_SoModelMatrixElement*)theWrappedObject)->promoted_translateEltBy(translation));
}



PythonQtShell_SoNormalBindingElement::~PythonQtShell_SoNormalBindingElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoNormalBindingElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoNormalBindingElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoNormalBindingElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoNormalBindingElement::copyMatchInfo();
}
void PythonQtShell_SoNormalBindingElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoNormalBindingElement::init(state0);
}
bool  PythonQtShell_SoNormalBindingElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoNormalBindingElement::matches(elt0);
}
void PythonQtShell_SoNormalBindingElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoNormalBindingElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoNormalBindingElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoNormalBindingElement::push(state0);
}
void PythonQtShell_SoNormalBindingElement::setElt(int  value0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("setElt");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "int"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&value0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoNormalBindingElement::setElt(value0);
}
SoNormalBindingElement* PythonQtWrapper_SoNormalBindingElement::new_SoNormalBindingElement()
{ 
return new PythonQtShell_SoNormalBindingElement(); }

SoNormalBindingElement::Binding  PythonQtWrapper_SoNormalBindingElement::static_SoNormalBindingElement_get(SoState*  state)
{
  return (SoNormalBindingElement::get(state));
}

int  PythonQtWrapper_SoNormalBindingElement::static_SoNormalBindingElement_getClassStackIndex()
{
  return (SoNormalBindingElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoNormalBindingElement::static_SoNormalBindingElement_getClassTypeId()
{
  return (SoNormalBindingElement::getClassTypeId());
}

SoNormalBindingElement::Binding  PythonQtWrapper_SoNormalBindingElement::static_SoNormalBindingElement_getDefault()
{
  return (SoNormalBindingElement::getDefault());
}

void PythonQtWrapper_SoNormalBindingElement::static_SoNormalBindingElement_set(SoState*  state, SoNormalBindingElement::Binding  binding)
{
  (SoNormalBindingElement::set(state, binding));
}



PythonQtShell_SoNormalElement::~PythonQtShell_SoNormalElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoNormalElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoNormalElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoNormalElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoNormalElement::copyMatchInfo();
}
void PythonQtShell_SoNormalElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoNormalElement::init(state0);
}
bool  PythonQtShell_SoNormalElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoNormalElement::matches(elt0);
}
void PythonQtShell_SoNormalElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoNormalElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoNormalElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoNormalElement::push(state0);
}
SoNormalElement* PythonQtWrapper_SoNormalElement::new_SoNormalElement()
{ 
return new PythonQtShell_SoNormalElement(); }

const SbVec3f*  PythonQtWrapper_SoNormalElement::get(SoNormalElement* theWrappedObject, int  index) const
{
  return &( theWrappedObject->get(index));
}

int  PythonQtWrapper_SoNormalElement::static_SoNormalElement_getClassStackIndex()
{
  return (SoNormalElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoNormalElement::static_SoNormalElement_getClassTypeId()
{
  return (SoNormalElement::getClassTypeId());
}

const SoNormalElement*  PythonQtWrapper_SoNormalElement::static_SoNormalElement_getInstance(SoState*  state)
{
  return (SoNormalElement::getInstance(state));
}

int  PythonQtWrapper_SoNormalElement::getNum(SoNormalElement* theWrappedObject) const
{
  return ( theWrappedObject->getNum());
}

void PythonQtWrapper_SoNormalElement::static_SoNormalElement_set(SoState*  state, SoNode*  node, int  numNormals, const SbVec3f*  normals)
{
  (SoNormalElement::set(state, node, numNormals, normals));
}



PythonQtShell_SoOverrideElement::~PythonQtShell_SoOverrideElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoOverrideElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoOverrideElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoOverrideElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoOverrideElement::copyMatchInfo();
}
void PythonQtShell_SoOverrideElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoOverrideElement::init(state0);
}
bool  PythonQtShell_SoOverrideElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoOverrideElement::matches(elt0);
}
void PythonQtShell_SoOverrideElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoOverrideElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoOverrideElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoOverrideElement::push(state0);
}
SoOverrideElement* PythonQtWrapper_SoOverrideElement::new_SoOverrideElement()
{ 
return new PythonQtShell_SoOverrideElement(); }

bool  PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_getAmbientColorOverride(SoState*  state)
{
  return (SoOverrideElement::getAmbientColorOverride(state));
}

int  PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_getClassStackIndex()
{
  return (SoOverrideElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_getClassTypeId()
{
  return (SoOverrideElement::getClassTypeId());
}

bool  PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_getComplexityOverride(SoState*  state)
{
  return (SoOverrideElement::getComplexityOverride(state));
}

bool  PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_getComplexityTypeOverride(SoState*  state)
{
  return (SoOverrideElement::getComplexityTypeOverride(state));
}

bool  PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_getCreaseAngleOverride(SoState*  state)
{
  return (SoOverrideElement::getCreaseAngleOverride(state));
}

bool  PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_getDiffuseColorOverride(SoState*  state)
{
  return (SoOverrideElement::getDiffuseColorOverride(state));
}

bool  PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_getDrawStyleOverride(SoState*  state)
{
  return (SoOverrideElement::getDrawStyleOverride(state));
}

bool  PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_getEmissiveColorOverride(SoState*  state)
{
  return (SoOverrideElement::getEmissiveColorOverride(state));
}

bool  PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_getFontNameOverride(SoState*  state)
{
  return (SoOverrideElement::getFontNameOverride(state));
}

bool  PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_getFontSizeOverride(SoState*  state)
{
  return (SoOverrideElement::getFontSizeOverride(state));
}

bool  PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_getLightModelOverride(SoState*  state)
{
  return (SoOverrideElement::getLightModelOverride(state));
}

bool  PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_getLinePatternOverride(SoState*  state)
{
  return (SoOverrideElement::getLinePatternOverride(state));
}

bool  PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_getLineWidthOverride(SoState*  state)
{
  return (SoOverrideElement::getLineWidthOverride(state));
}

bool  PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_getMaterialBindingOverride(SoState*  state)
{
  return (SoOverrideElement::getMaterialBindingOverride(state));
}

bool  PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_getPickStyleOverride(SoState*  state)
{
  return (SoOverrideElement::getPickStyleOverride(state));
}

bool  PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_getPointSizeOverride(SoState*  state)
{
  return (SoOverrideElement::getPointSizeOverride(state));
}

bool  PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_getPolygonOffsetOverride(SoState*  state)
{
  return (SoOverrideElement::getPolygonOffsetOverride(state));
}

bool  PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_getShapeHintsOverride(SoState*  state)
{
  return (SoOverrideElement::getShapeHintsOverride(state));
}

bool  PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_getShininessOverride(SoState*  state)
{
  return (SoOverrideElement::getShininessOverride(state));
}

bool  PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_getSpecularColorOverride(SoState*  state)
{
  return (SoOverrideElement::getSpecularColorOverride(state));
}

bool  PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_getTransparencyOverride(SoState*  state)
{
  return (SoOverrideElement::getTransparencyOverride(state));
}

void PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_setAmbientColorOverride(SoState*  state, SoNode*  arg__2, bool  override)
{
  (SoOverrideElement::setAmbientColorOverride(state, arg__2, override));
}

void PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_setComplexityOverride(SoState*  state, SoNode*  arg__2, bool  override)
{
  (SoOverrideElement::setComplexityOverride(state, arg__2, override));
}

void PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_setComplexityTypeOverride(SoState*  state, SoNode*  arg__2, bool  override)
{
  (SoOverrideElement::setComplexityTypeOverride(state, arg__2, override));
}

void PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_setCreaseAngleOverride(SoState*  state, SoNode*  arg__2, bool  override)
{
  (SoOverrideElement::setCreaseAngleOverride(state, arg__2, override));
}

void PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_setDiffuseColorOverride(SoState*  state, SoNode*  arg__2, bool  override)
{
  (SoOverrideElement::setDiffuseColorOverride(state, arg__2, override));
}

void PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_setDrawStyleOverride(SoState*  state, SoNode*  arg__2, bool  override)
{
  (SoOverrideElement::setDrawStyleOverride(state, arg__2, override));
}

void PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_setEmissiveColorOverride(SoState*  state, SoNode*  arg__2, bool  override)
{
  (SoOverrideElement::setEmissiveColorOverride(state, arg__2, override));
}

void PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_setFontNameOverride(SoState*  state, SoNode*  arg__2, bool  override)
{
  (SoOverrideElement::setFontNameOverride(state, arg__2, override));
}

void PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_setFontSizeOverride(SoState*  state, SoNode*  arg__2, bool  override)
{
  (SoOverrideElement::setFontSizeOverride(state, arg__2, override));
}

void PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_setLightModelOverride(SoState*  state, SoNode*  arg__2, bool  override)
{
  (SoOverrideElement::setLightModelOverride(state, arg__2, override));
}

void PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_setLinePatternOverride(SoState*  state, SoNode*  arg__2, bool  override)
{
  (SoOverrideElement::setLinePatternOverride(state, arg__2, override));
}

void PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_setLineWidthOverride(SoState*  state, SoNode*  arg__2, bool  override)
{
  (SoOverrideElement::setLineWidthOverride(state, arg__2, override));
}

void PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_setMaterialBindingOverride(SoState*  state, SoNode*  arg__2, bool  override)
{
  (SoOverrideElement::setMaterialBindingOverride(state, arg__2, override));
}

void PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_setPickStyleOverride(SoState*  state, SoNode*  arg__2, bool  override)
{
  (SoOverrideElement::setPickStyleOverride(state, arg__2, override));
}

void PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_setPointSizeOverride(SoState*  state, SoNode*  arg__2, bool  override)
{
  (SoOverrideElement::setPointSizeOverride(state, arg__2, override));
}

void PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_setPolygonOffsetOverride(SoState*  state, SoNode*  arg__2, bool  override)
{
  (SoOverrideElement::setPolygonOffsetOverride(state, arg__2, override));
}

void PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_setShapeHintsOverride(SoState*  state, SoNode*  arg__2, bool  override)
{
  (SoOverrideElement::setShapeHintsOverride(state, arg__2, override));
}

void PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_setShininessOverride(SoState*  state, SoNode*  arg__2, bool  override)
{
  (SoOverrideElement::setShininessOverride(state, arg__2, override));
}

void PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_setSpecularColorOverride(SoState*  state, SoNode*  arg__2, bool  override)
{
  (SoOverrideElement::setSpecularColorOverride(state, arg__2, override));
}

void PythonQtWrapper_SoOverrideElement::static_SoOverrideElement_setTransparencyOverride(SoState*  state, SoNode*  arg__2, bool  override)
{
  (SoOverrideElement::setTransparencyOverride(state, arg__2, override));
}



PythonQtShell_SoPickRayElement::~PythonQtShell_SoPickRayElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoPickRayElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoPickRayElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoPickRayElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoPickRayElement::copyMatchInfo();
}
void PythonQtShell_SoPickRayElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoPickRayElement::init(state0);
}
bool  PythonQtShell_SoPickRayElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoPickRayElement::matches(elt0);
}
void PythonQtShell_SoPickRayElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoPickRayElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoPickRayElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoPickRayElement::push(state0);
}
SoPickRayElement* PythonQtWrapper_SoPickRayElement::new_SoPickRayElement()
{ 
return new PythonQtShell_SoPickRayElement(); }

const SbViewVolume*  PythonQtWrapper_SoPickRayElement::static_SoPickRayElement_get(SoState*  state)
{
  return &(SoPickRayElement::get(state));
}

int  PythonQtWrapper_SoPickRayElement::static_SoPickRayElement_getClassStackIndex()
{
  return (SoPickRayElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoPickRayElement::static_SoPickRayElement_getClassTypeId()
{
  return (SoPickRayElement::getClassTypeId());
}

void PythonQtWrapper_SoPickRayElement::static_SoPickRayElement_set(SoState*  state, const SbViewVolume&  volume)
{
  (SoPickRayElement::set(state, volume));
}



PythonQtShell_SoPickStyleElement::~PythonQtShell_SoPickStyleElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoPickStyleElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoPickStyleElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoPickStyleElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoPickStyleElement::copyMatchInfo();
}
void PythonQtShell_SoPickStyleElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoPickStyleElement::init(state0);
}
bool  PythonQtShell_SoPickStyleElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoPickStyleElement::matches(elt0);
}
void PythonQtShell_SoPickStyleElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoPickStyleElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoPickStyleElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoPickStyleElement::push(state0);
}
void PythonQtShell_SoPickStyleElement::setElt(int  value0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("setElt");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "int"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&value0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoPickStyleElement::setElt(value0);
}
SoPickStyleElement* PythonQtWrapper_SoPickStyleElement::new_SoPickStyleElement()
{ 
return new PythonQtShell_SoPickStyleElement(); }

SoPickStyleElement::Style  PythonQtWrapper_SoPickStyleElement::static_SoPickStyleElement_get(SoState*  state)
{
  return (SoPickStyleElement::get(state));
}

int  PythonQtWrapper_SoPickStyleElement::static_SoPickStyleElement_getClassStackIndex()
{
  return (SoPickStyleElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoPickStyleElement::static_SoPickStyleElement_getClassTypeId()
{
  return (SoPickStyleElement::getClassTypeId());
}

SoPickStyleElement::Style  PythonQtWrapper_SoPickStyleElement::static_SoPickStyleElement_getDefault()
{
  return (SoPickStyleElement::getDefault());
}

void PythonQtWrapper_SoPickStyleElement::static_SoPickStyleElement_set(SoState*  state, SoPickStyleElement::Style  style)
{
  (SoPickStyleElement::set(state, style));
}



PythonQtShell_SoPointSizeElement::~PythonQtShell_SoPointSizeElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoPointSizeElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoPointSizeElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoPointSizeElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoPointSizeElement::copyMatchInfo();
}
void PythonQtShell_SoPointSizeElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoPointSizeElement::init(state0);
}
bool  PythonQtShell_SoPointSizeElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoPointSizeElement::matches(elt0);
}
void PythonQtShell_SoPointSizeElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoPointSizeElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoPointSizeElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoPointSizeElement::push(state0);
}
void PythonQtShell_SoPointSizeElement::setElt(float  value0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("setElt");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "float"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&value0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoPointSizeElement::setElt(value0);
}
SoPointSizeElement* PythonQtWrapper_SoPointSizeElement::new_SoPointSizeElement()
{ 
return new PythonQtShell_SoPointSizeElement(); }

float  PythonQtWrapper_SoPointSizeElement::static_SoPointSizeElement_get(SoState*  state)
{
  return (SoPointSizeElement::get(state));
}

int  PythonQtWrapper_SoPointSizeElement::static_SoPointSizeElement_getClassStackIndex()
{
  return (SoPointSizeElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoPointSizeElement::static_SoPointSizeElement_getClassTypeId()
{
  return (SoPointSizeElement::getClassTypeId());
}

float  PythonQtWrapper_SoPointSizeElement::static_SoPointSizeElement_getDefault()
{
  return (SoPointSizeElement::getDefault());
}

void PythonQtWrapper_SoPointSizeElement::static_SoPointSizeElement_set(SoState*  state, float  size)
{
  (SoPointSizeElement::set(state, size));
}



PythonQtShell_SoProfileCoordinateElement::~PythonQtShell_SoProfileCoordinateElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoProfileCoordinateElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoProfileCoordinateElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoProfileCoordinateElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoProfileCoordinateElement::copyMatchInfo();
}
void PythonQtShell_SoProfileCoordinateElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoProfileCoordinateElement::init(state0);
}
bool  PythonQtShell_SoProfileCoordinateElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoProfileCoordinateElement::matches(elt0);
}
void PythonQtShell_SoProfileCoordinateElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoProfileCoordinateElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoProfileCoordinateElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoProfileCoordinateElement::push(state0);
}
SoProfileCoordinateElement* PythonQtWrapper_SoProfileCoordinateElement::new_SoProfileCoordinateElement()
{ 
return new PythonQtShell_SoProfileCoordinateElement(); }

const SbVec2f*  PythonQtWrapper_SoProfileCoordinateElement::get2(SoProfileCoordinateElement* theWrappedObject, int  index) const
{
  return &( theWrappedObject->get2(index));
}

const SbVec3f*  PythonQtWrapper_SoProfileCoordinateElement::get3(SoProfileCoordinateElement* theWrappedObject, int  index) const
{
  return &( theWrappedObject->get3(index));
}

int  PythonQtWrapper_SoProfileCoordinateElement::static_SoProfileCoordinateElement_getClassStackIndex()
{
  return (SoProfileCoordinateElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoProfileCoordinateElement::static_SoProfileCoordinateElement_getClassTypeId()
{
  return (SoProfileCoordinateElement::getClassTypeId());
}

SbVec2f  PythonQtWrapper_SoProfileCoordinateElement::static_SoProfileCoordinateElement_getDefault2()
{
  return (SoProfileCoordinateElement::getDefault2());
}

SbVec3f  PythonQtWrapper_SoProfileCoordinateElement::static_SoProfileCoordinateElement_getDefault3()
{
  return (SoProfileCoordinateElement::getDefault3());
}

const SoProfileCoordinateElement*  PythonQtWrapper_SoProfileCoordinateElement::static_SoProfileCoordinateElement_getInstance(SoState*  state)
{
  return (SoProfileCoordinateElement::getInstance(state));
}

int  PythonQtWrapper_SoProfileCoordinateElement::getNum(SoProfileCoordinateElement* theWrappedObject) const
{
  return ( theWrappedObject->getNum());
}

bool  PythonQtWrapper_SoProfileCoordinateElement::is2D(SoProfileCoordinateElement* theWrappedObject) const
{
  return ( theWrappedObject->is2D());
}

void PythonQtWrapper_SoProfileCoordinateElement::static_SoProfileCoordinateElement_set2(SoState*  state, SoNode*  node, int  numCoords, const SbVec2f*  coords)
{
  (SoProfileCoordinateElement::set2(state, node, numCoords, coords));
}

void PythonQtWrapper_SoProfileCoordinateElement::static_SoProfileCoordinateElement_set3(SoState*  state, SoNode*  node, int  numCoords, const SbVec3f*  coords)
{
  (SoProfileCoordinateElement::set3(state, node, numCoords, coords));
}



PythonQtShell_SoProfileElement::~PythonQtShell_SoProfileElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoProfileElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoProfileElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoProfileElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoProfileElement::copyMatchInfo();
}
void PythonQtShell_SoProfileElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoProfileElement::init(state0);
}
bool  PythonQtShell_SoProfileElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoProfileElement::matches(elt0);
}
void PythonQtShell_SoProfileElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoProfileElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoProfileElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoProfileElement::push(state0);
}
SoProfileElement* PythonQtWrapper_SoProfileElement::new_SoProfileElement()
{ 
return new PythonQtShell_SoProfileElement(); }

void PythonQtWrapper_SoProfileElement::static_SoProfileElement_add(SoState*  state, SoProfile*  profile)
{
  (SoProfileElement::add(state, profile));
}

int  PythonQtWrapper_SoProfileElement::static_SoProfileElement_getClassStackIndex()
{
  return (SoProfileElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoProfileElement::static_SoProfileElement_getClassTypeId()
{
  return (SoProfileElement::getClassTypeId());
}



PythonQtShell_SoProjectionMatrixElement::~PythonQtShell_SoProjectionMatrixElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoProjectionMatrixElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoProjectionMatrixElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoProjectionMatrixElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoProjectionMatrixElement::copyMatchInfo();
}
void PythonQtShell_SoProjectionMatrixElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoProjectionMatrixElement::init(state0);
}
bool  PythonQtShell_SoProjectionMatrixElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoProjectionMatrixElement::matches(elt0);
}
void PythonQtShell_SoProjectionMatrixElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoProjectionMatrixElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoProjectionMatrixElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoProjectionMatrixElement::push(state0);
}
void PythonQtShell_SoProjectionMatrixElement::setElt(const SbMatrix&  matrix0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("setElt");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbMatrix&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&matrix0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoProjectionMatrixElement::setElt(matrix0);
}
SoProjectionMatrixElement* PythonQtWrapper_SoProjectionMatrixElement::new_SoProjectionMatrixElement()
{ 
return new PythonQtShell_SoProjectionMatrixElement(); }

const SbMatrix*  PythonQtWrapper_SoProjectionMatrixElement::static_SoProjectionMatrixElement_get(SoState*  state)
{
  return &(SoProjectionMatrixElement::get(state));
}

int  PythonQtWrapper_SoProjectionMatrixElement::static_SoProjectionMatrixElement_getClassStackIndex()
{
  return (SoProjectionMatrixElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoProjectionMatrixElement::static_SoProjectionMatrixElement_getClassTypeId()
{
  return (SoProjectionMatrixElement::getClassTypeId());
}

void PythonQtWrapper_SoProjectionMatrixElement::static_SoProjectionMatrixElement_set(SoState*  state, SoNode*  node, const SbMatrix&  matrix)
{
  (SoProjectionMatrixElement::set(state, node, matrix));
}

void PythonQtWrapper_SoProjectionMatrixElement::setElt(SoProjectionMatrixElement* theWrappedObject, const SbMatrix&  matrix)
{
  ( ((PythonQtPublicPromoter_SoProjectionMatrixElement*)theWrappedObject)->promoted_setElt(matrix));
}



PythonQtShell_SoReplacedElement::~PythonQtShell_SoReplacedElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoReplacedElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoReplacedElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoReplacedElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoReplacedElement::copyMatchInfo();
}
void PythonQtShell_SoReplacedElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoReplacedElement::init(state0);
}
bool  PythonQtShell_SoReplacedElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoReplacedElement::matches(elt0);
}
void PythonQtShell_SoReplacedElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoReplacedElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoReplacedElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoReplacedElement::push(state0);
}
SoReplacedElement* PythonQtWrapper_SoReplacedElement::new_SoReplacedElement()
{ 
return new PythonQtShell_SoReplacedElement(); }

int  PythonQtWrapper_SoReplacedElement::static_SoReplacedElement_getClassStackIndex()
{
  return (SoReplacedElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoReplacedElement::static_SoReplacedElement_getClassTypeId()
{
  return (SoReplacedElement::getClassTypeId());
}

SoElement*  PythonQtWrapper_SoReplacedElement::static_SoReplacedElement_getElement(SoState*  state, int  stackIndex, SoNode*  node)
{
  return (PythonQtPublicPromoter_SoReplacedElement::promoted_getElement(state, stackIndex, node));
}



PythonQtShell_SoShapeHintsElement::~PythonQtShell_SoShapeHintsElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoShapeHintsElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoShapeHintsElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoShapeHintsElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoShapeHintsElement::copyMatchInfo();
}
void PythonQtShell_SoShapeHintsElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoShapeHintsElement::init(state0);
}
bool  PythonQtShell_SoShapeHintsElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoShapeHintsElement::matches(elt0);
}
void PythonQtShell_SoShapeHintsElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoShapeHintsElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoShapeHintsElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoShapeHintsElement::push(state0);
}
void PythonQtShell_SoShapeHintsElement::setElt(SoShapeHintsElement::VertexOrdering  vertexOrdering0, SoShapeHintsElement::ShapeType  shapeType1, SoShapeHintsElement::FaceType  faceType2)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("setElt");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoShapeHintsElement::VertexOrdering" , "SoShapeHintsElement::ShapeType" , "SoShapeHintsElement::FaceType"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(4, argumentList);
      void* args[4] = {nullptr, (void*)&vertexOrdering0, (void*)&shapeType1, (void*)&faceType2};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoShapeHintsElement::setElt(vertexOrdering0, shapeType1, faceType2);
}
SoShapeHintsElement* PythonQtWrapper_SoShapeHintsElement::new_SoShapeHintsElement()
{ 
return new PythonQtShell_SoShapeHintsElement(); }

void PythonQtWrapper_SoShapeHintsElement::static_SoShapeHintsElement_get(SoState*  state, SoShapeHintsElement::VertexOrdering&  vertexOrdering, SoShapeHintsElement::ShapeType&  shapeType, SoShapeHintsElement::FaceType&  faceType)
{
  (SoShapeHintsElement::get(state, vertexOrdering, shapeType, faceType));
}

int  PythonQtWrapper_SoShapeHintsElement::static_SoShapeHintsElement_getClassStackIndex()
{
  return (SoShapeHintsElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoShapeHintsElement::static_SoShapeHintsElement_getClassTypeId()
{
  return (SoShapeHintsElement::getClassTypeId());
}

SoShapeHintsElement::FaceType  PythonQtWrapper_SoShapeHintsElement::static_SoShapeHintsElement_getDefaultFaceType()
{
  return (SoShapeHintsElement::getDefaultFaceType());
}

SoShapeHintsElement::ShapeType  PythonQtWrapper_SoShapeHintsElement::static_SoShapeHintsElement_getDefaultShapeType()
{
  return (SoShapeHintsElement::getDefaultShapeType());
}

bool  PythonQtWrapper_SoShapeHintsElement::static_SoShapeHintsElement_getDefaultVBOUsage()
{
  return (SoShapeHintsElement::getDefaultVBOUsage());
}

SoShapeHintsElement::VertexOrdering  PythonQtWrapper_SoShapeHintsElement::static_SoShapeHintsElement_getDefaultVertexOrdering()
{
  return (SoShapeHintsElement::getDefaultVertexOrdering());
}

bool  PythonQtWrapper_SoShapeHintsElement::static_SoShapeHintsElement_isVBOUsed(SoState*  state)
{
  return (SoShapeHintsElement::isVBOUsed(state));
}

void PythonQtWrapper_SoShapeHintsElement::static_SoShapeHintsElement_set(SoState*  state, SoShapeHintsElement::VertexOrdering  vertexOrdering, SoShapeHintsElement::ShapeType  shapeType, SoShapeHintsElement::FaceType  faceType)
{
  (SoShapeHintsElement::set(state, vertexOrdering, shapeType, faceType));
}

void PythonQtWrapper_SoShapeHintsElement::static_SoShapeHintsElement_set(SoState*  state, bool  useVBO)
{
  (SoShapeHintsElement::set(state, useVBO));
}

void PythonQtWrapper_SoShapeHintsElement::setElt(SoShapeHintsElement* theWrappedObject, SoShapeHintsElement::VertexOrdering  vertexOrdering, SoShapeHintsElement::ShapeType  shapeType, SoShapeHintsElement::FaceType  faceType)
{
  ( ((PythonQtPublicPromoter_SoShapeHintsElement*)theWrappedObject)->promoted_setElt(vertexOrdering, shapeType, faceType));
}



PythonQtShell_SoShapeStyleElement::~PythonQtShell_SoShapeStyleElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoShapeStyleElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoShapeStyleElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoShapeStyleElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoShapeStyleElement::copyMatchInfo();
}
void PythonQtShell_SoShapeStyleElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoShapeStyleElement::init(state0);
}
bool  PythonQtShell_SoShapeStyleElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoShapeStyleElement::matches(elt0);
}
void PythonQtShell_SoShapeStyleElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoShapeStyleElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoShapeStyleElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoShapeStyleElement::push(state0);
}
SoShapeStyleElement* PythonQtWrapper_SoShapeStyleElement::new_SoShapeStyleElement()
{ 
return new PythonQtShell_SoShapeStyleElement(); }

const SoShapeStyleElement*  PythonQtWrapper_SoShapeStyleElement::static_SoShapeStyleElement_get(SoState*  state)
{
  return (SoShapeStyleElement::get(state));
}

int  PythonQtWrapper_SoShapeStyleElement::static_SoShapeStyleElement_getClassStackIndex()
{
  return (SoShapeStyleElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoShapeStyleElement::static_SoShapeStyleElement_getClassTypeId()
{
  return (SoShapeStyleElement::getClassTypeId());
}

int  PythonQtWrapper_SoShapeStyleElement::getRenderCaseMask(SoShapeStyleElement* theWrappedObject) const
{
  return ( theWrappedObject->getRenderCaseMask());
}

bool  PythonQtWrapper_SoShapeStyleElement::static_SoShapeStyleElement_isScreenDoor(SoState*  state)
{
  return (SoShapeStyleElement::isScreenDoor(state));
}

bool  PythonQtWrapper_SoShapeStyleElement::isTextureFunction(SoShapeStyleElement* theWrappedObject) const
{
  return ( theWrappedObject->isTextureFunction());
}

bool  PythonQtWrapper_SoShapeStyleElement::mightNotRender(SoShapeStyleElement* theWrappedObject) const
{
  return ( theWrappedObject->mightNotRender());
}

bool  PythonQtWrapper_SoShapeStyleElement::needNormals(SoShapeStyleElement* theWrappedObject) const
{
  return ( theWrappedObject->needNormals());
}

bool  PythonQtWrapper_SoShapeStyleElement::needTexCoords(SoShapeStyleElement* theWrappedObject) const
{
  return ( theWrappedObject->needTexCoords());
}

void PythonQtWrapper_SoShapeStyleElement::static_SoShapeStyleElement_setComplexityType(SoState*  state, int  value)
{
  (SoShapeStyleElement::setComplexityType(state, value));
}

void PythonQtWrapper_SoShapeStyleElement::static_SoShapeStyleElement_setDrawStyle(SoState*  state, int  value)
{
  (SoShapeStyleElement::setDrawStyle(state, value));
}

void PythonQtWrapper_SoShapeStyleElement::static_SoShapeStyleElement_setLightModel(SoState*  state, int  value)
{
  (SoShapeStyleElement::setLightModel(state, value));
}

void PythonQtWrapper_SoShapeStyleElement::static_SoShapeStyleElement_setOverrides(SoState*  state, bool  value)
{
  (SoShapeStyleElement::setOverrides(state, value));
}

void PythonQtWrapper_SoShapeStyleElement::static_SoShapeStyleElement_setTextureEnabled(SoState*  state, bool  value)
{
  (SoShapeStyleElement::setTextureEnabled(state, value));
}

void PythonQtWrapper_SoShapeStyleElement::static_SoShapeStyleElement_setTextureFunction(SoState*  state, bool  value)
{
  (SoShapeStyleElement::setTextureFunction(state, value));
}

void PythonQtWrapper_SoShapeStyleElement::static_SoShapeStyleElement_setTransparencyType(SoState*  state, int  value)
{
  (SoShapeStyleElement::setTransparencyType(state, value));
}



PythonQtShell_SoSwitchElement::~PythonQtShell_SoSwitchElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoSwitchElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoSwitchElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoSwitchElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoSwitchElement::copyMatchInfo();
}
void PythonQtShell_SoSwitchElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoSwitchElement::init(state0);
}
bool  PythonQtShell_SoSwitchElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoSwitchElement::matches(elt0);
}
void PythonQtShell_SoSwitchElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoSwitchElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoSwitchElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoSwitchElement::push(state0);
}
void PythonQtShell_SoSwitchElement::setElt(int  value0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("setElt");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "int"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&value0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoSwitchElement::setElt(value0);
}
SoSwitchElement* PythonQtWrapper_SoSwitchElement::new_SoSwitchElement()
{ 
return new PythonQtShell_SoSwitchElement(); }

int  PythonQtWrapper_SoSwitchElement::static_SoSwitchElement_get(SoState*  state)
{
  return (SoSwitchElement::get(state));
}

int  PythonQtWrapper_SoSwitchElement::static_SoSwitchElement_getClassStackIndex()
{
  return (SoSwitchElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoSwitchElement::static_SoSwitchElement_getClassTypeId()
{
  return (SoSwitchElement::getClassTypeId());
}

int  PythonQtWrapper_SoSwitchElement::static_SoSwitchElement_getDefault()
{
  return (SoSwitchElement::getDefault());
}

void PythonQtWrapper_SoSwitchElement::static_SoSwitchElement_set(SoState*  state, int  index)
{
  (SoSwitchElement::set(state, index));
}



PythonQtShell_SoTextureCoordinateBindingElement::~PythonQtShell_SoTextureCoordinateBindingElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoTextureCoordinateBindingElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoTextureCoordinateBindingElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoTextureCoordinateBindingElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoTextureCoordinateBindingElement::copyMatchInfo();
}
void PythonQtShell_SoTextureCoordinateBindingElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoTextureCoordinateBindingElement::init(state0);
}
bool  PythonQtShell_SoTextureCoordinateBindingElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoTextureCoordinateBindingElement::matches(elt0);
}
void PythonQtShell_SoTextureCoordinateBindingElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoTextureCoordinateBindingElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoTextureCoordinateBindingElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoTextureCoordinateBindingElement::push(state0);
}
void PythonQtShell_SoTextureCoordinateBindingElement::setElt(int  value0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("setElt");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "int"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&value0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoTextureCoordinateBindingElement::setElt(value0);
}
SoTextureCoordinateBindingElement* PythonQtWrapper_SoTextureCoordinateBindingElement::new_SoTextureCoordinateBindingElement()
{ 
return new PythonQtShell_SoTextureCoordinateBindingElement(); }

SoTextureCoordinateBindingElement::Binding  PythonQtWrapper_SoTextureCoordinateBindingElement::static_SoTextureCoordinateBindingElement_get(SoState*  state)
{
  return (SoTextureCoordinateBindingElement::get(state));
}

int  PythonQtWrapper_SoTextureCoordinateBindingElement::static_SoTextureCoordinateBindingElement_getClassStackIndex()
{
  return (SoTextureCoordinateBindingElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoTextureCoordinateBindingElement::static_SoTextureCoordinateBindingElement_getClassTypeId()
{
  return (SoTextureCoordinateBindingElement::getClassTypeId());
}

SoTextureCoordinateBindingElement::Binding  PythonQtWrapper_SoTextureCoordinateBindingElement::static_SoTextureCoordinateBindingElement_getDefault()
{
  return (SoTextureCoordinateBindingElement::getDefault());
}

void PythonQtWrapper_SoTextureCoordinateBindingElement::static_SoTextureCoordinateBindingElement_set(SoState*  state, SoTextureCoordinateBindingElement::Binding  binding)
{
  (SoTextureCoordinateBindingElement::set(state, binding));
}



PythonQtShell_SoTextureCoordinateElement::~PythonQtShell_SoTextureCoordinateElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoTextureCoordinateElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoTextureCoordinateElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoTextureCoordinateElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoTextureCoordinateElement::copyMatchInfo();
}
SoTextureCoordinateElement::CoordType  PythonQtShell_SoTextureCoordinateElement::getType() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("getType");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoTextureCoordinateElement::CoordType"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoTextureCoordinateElement::CoordType returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getType", methodInfo, result);
          } else {
            returnValue = *((SoTextureCoordinateElement::CoordType*)args[0]);
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
  return SoTextureCoordinateElement::getType();
}
void PythonQtShell_SoTextureCoordinateElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoTextureCoordinateElement::init(state0);
}
bool  PythonQtShell_SoTextureCoordinateElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoTextureCoordinateElement::matches(elt0);
}
void PythonQtShell_SoTextureCoordinateElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoTextureCoordinateElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoTextureCoordinateElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoTextureCoordinateElement::push(state0);
}
SoTextureCoordinateElement* PythonQtWrapper_SoTextureCoordinateElement::new_SoTextureCoordinateElement()
{ 
return new PythonQtShell_SoTextureCoordinateElement(); }

const SbVec4f*  PythonQtWrapper_SoTextureCoordinateElement::get(SoTextureCoordinateElement* theWrappedObject, const SbVec3f&  point, const SbVec3f&  normal) const
{
  return &( theWrappedObject->get(point, normal));
}

const SbVec2f*  PythonQtWrapper_SoTextureCoordinateElement::get2(SoTextureCoordinateElement* theWrappedObject, int  index) const
{
  return &( theWrappedObject->get2(index));
}

const SbVec4f*  PythonQtWrapper_SoTextureCoordinateElement::get4(SoTextureCoordinateElement* theWrappedObject, int  index) const
{
  return &( theWrappedObject->get4(index));
}

int  PythonQtWrapper_SoTextureCoordinateElement::static_SoTextureCoordinateElement_getClassStackIndex()
{
  return (SoTextureCoordinateElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoTextureCoordinateElement::static_SoTextureCoordinateElement_getClassTypeId()
{
  return (SoTextureCoordinateElement::getClassTypeId());
}

const SoTextureCoordinateElement*  PythonQtWrapper_SoTextureCoordinateElement::static_SoTextureCoordinateElement_getInstance(SoState*  state)
{
  return (SoTextureCoordinateElement::getInstance(state));
}

int  PythonQtWrapper_SoTextureCoordinateElement::getNum(SoTextureCoordinateElement* theWrappedObject) const
{
  return ( theWrappedObject->getNum());
}

SoTextureCoordinateElement::CoordType  PythonQtWrapper_SoTextureCoordinateElement::getType(SoTextureCoordinateElement* theWrappedObject) const
{
  return ( theWrappedObject->getType());
}

SoTextureCoordinateElement::CoordType  PythonQtWrapper_SoTextureCoordinateElement::static_SoTextureCoordinateElement_getType(SoState*  state)
{
  return (SoTextureCoordinateElement::getType(state));
}

bool  PythonQtWrapper_SoTextureCoordinateElement::is2D(SoTextureCoordinateElement* theWrappedObject) const
{
  return ( theWrappedObject->is2D());
}

void PythonQtWrapper_SoTextureCoordinateElement::static_SoTextureCoordinateElement_set2(SoState*  state, SoNode*  node, int  numCoords, const SbVec2f*  coords)
{
  (SoTextureCoordinateElement::set2(state, node, numCoords, coords));
}

void PythonQtWrapper_SoTextureCoordinateElement::static_SoTextureCoordinateElement_set4(SoState*  state, SoNode*  node, int  numCoords, const SbVec4f*  coords)
{
  (SoTextureCoordinateElement::set4(state, node, numCoords, coords));
}

void PythonQtWrapper_SoTextureCoordinateElement::static_SoTextureCoordinateElement_setDefault(SoState*  state, SoNode*  node)
{
  (SoTextureCoordinateElement::setDefault(state, node));
}



PythonQtShell_SoTextureImageElement::~PythonQtShell_SoTextureImageElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoTextureImageElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoTextureImageElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoTextureImageElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoTextureImageElement::copyMatchInfo();
}
void PythonQtShell_SoTextureImageElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoTextureImageElement::init(state0);
}
bool  PythonQtShell_SoTextureImageElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoTextureImageElement::matches(elt0);
}
void PythonQtShell_SoTextureImageElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoTextureImageElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoTextureImageElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoTextureImageElement::push(state0);
}
void PythonQtShell_SoTextureImageElement::setElt(const SbVec2s&  s0, int  nc1, const unsigned char*  bytes2, int  wrapS3, int  wrapT4, int  model5, const SbColor&  blendColor6)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("setElt");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbVec2s&" , "int" , "const unsigned char*" , "int" , "int" , "int" , "const SbColor&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(8, argumentList);
      void* args[8] = {nullptr, (void*)&s0, (void*)&nc1, (void*)&bytes2, (void*)&wrapS3, (void*)&wrapT4, (void*)&model5, (void*)&blendColor6};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoTextureImageElement::setElt(s0, nc1, bytes2, wrapS3, wrapT4, model5, blendColor6);
}
SoTextureImageElement* PythonQtWrapper_SoTextureImageElement::new_SoTextureImageElement()
{ 
return new PythonQtShell_SoTextureImageElement(); }

bool  PythonQtWrapper_SoTextureImageElement::static_SoTextureImageElement_containsTransparency(SoState*  state)
{
  return (SoTextureImageElement::containsTransparency(state));
}

const unsigned char*  PythonQtWrapper_SoTextureImageElement::static_SoTextureImageElement_get(SoState*  state, SbVec2s&  size, int&  numComponents, int&  wrapS, int&  wrapT, int&  model, SbColor&  blendColor)
{
  return (SoTextureImageElement::get(state, size, numComponents, wrapS, wrapT, model, blendColor));
}

int  PythonQtWrapper_SoTextureImageElement::static_SoTextureImageElement_getClassStackIndex()
{
  return (SoTextureImageElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoTextureImageElement::static_SoTextureImageElement_getClassTypeId()
{
  return (SoTextureImageElement::getClassTypeId());
}

const unsigned char*  PythonQtWrapper_SoTextureImageElement::static_SoTextureImageElement_getDefault(SbVec2s&  s, int&  nc)
{
  return (SoTextureImageElement::getDefault(s, nc));
}

void PythonQtWrapper_SoTextureImageElement::static_SoTextureImageElement_set(SoState*  state, SoNode*  node, const SbVec2s&  size, int  numComponents, const unsigned char*  bytes, int  wrapS, int  wrapT, int  model, const SbColor&  blendColor)
{
  (SoTextureImageElement::set(state, node, size, numComponents, bytes, wrapS, wrapT, model, blendColor));
}

void PythonQtWrapper_SoTextureImageElement::setElt(SoTextureImageElement* theWrappedObject, const SbVec2s&  s, int  nc, const unsigned char*  bytes, int  wrapS, int  wrapT, int  model, const SbColor&  blendColor)
{
  ( ((PythonQtPublicPromoter_SoTextureImageElement*)theWrappedObject)->promoted_setElt(s, nc, bytes, wrapS, wrapT, model, blendColor));
}



PythonQtShell_SoTextureMatrixElement::~PythonQtShell_SoTextureMatrixElement() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoTextureMatrixElement::captureThis(SoState*  state0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("captureThis");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoTextureMatrixElement::captureThis(state0);
}
SoElement*  PythonQtShell_SoTextureMatrixElement::copyMatchInfo() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("copyMatchInfo");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoElement* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("copyMatchInfo", methodInfo, result);
          } else {
            returnValue = *((SoElement**)args[0]);
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
  return SoTextureMatrixElement::copyMatchInfo();
}
void PythonQtShell_SoTextureMatrixElement::init(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("init");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoTextureMatrixElement::init(state0);
}
void PythonQtShell_SoTextureMatrixElement::makeEltIdentity()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("makeEltIdentity");
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
  SoTextureMatrixElement::makeEltIdentity();
}
bool  PythonQtShell_SoTextureMatrixElement::matches(const SoElement*  elt0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("matches");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&elt0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("matches", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
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
  return SoTextureMatrixElement::matches(elt0);
}
void PythonQtShell_SoTextureMatrixElement::multElt(const SbMatrix&  matrix0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("multElt");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbMatrix&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&matrix0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoTextureMatrixElement::multElt(matrix0);
}
void PythonQtShell_SoTextureMatrixElement::pop(SoState*  state0, const SoElement*  prevTopElement1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("pop");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*" , "const SoElement*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&state0, (void*)&prevTopElement1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoTextureMatrixElement::pop(state0, prevTopElement1);
}
void PythonQtShell_SoTextureMatrixElement::push(SoState*  state0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("push");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoState*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&state0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoTextureMatrixElement::push(state0);
}
void PythonQtShell_SoTextureMatrixElement::rotateEltBy(const SbRotation&  translation0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("rotateEltBy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbRotation&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&translation0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoTextureMatrixElement::rotateEltBy(translation0);
}
void PythonQtShell_SoTextureMatrixElement::scaleEltBy(const SbVec3f&  scaleFactor0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("scaleEltBy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbVec3f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&scaleFactor0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoTextureMatrixElement::scaleEltBy(scaleFactor0);
}
void PythonQtShell_SoTextureMatrixElement::translateEltBy(const SbVec3f&  translation0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("translateEltBy");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbVec3f&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&translation0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoTextureMatrixElement::translateEltBy(translation0);
}
SoTextureMatrixElement* PythonQtWrapper_SoTextureMatrixElement::new_SoTextureMatrixElement()
{ 
return new PythonQtShell_SoTextureMatrixElement(); }

const SbMatrix*  PythonQtWrapper_SoTextureMatrixElement::static_SoTextureMatrixElement_get(SoState*  state)
{
  return &(SoTextureMatrixElement::get(state));
}

int  PythonQtWrapper_SoTextureMatrixElement::static_SoTextureMatrixElement_getClassStackIndex()
{
  return (SoTextureMatrixElement::getClassStackIndex());
}

SoType  PythonQtWrapper_SoTextureMatrixElement::static_SoTextureMatrixElement_getClassTypeId()
{
  return (SoTextureMatrixElement::getClassTypeId());
}

void PythonQtWrapper_SoTextureMatrixElement::makeEltIdentity(SoTextureMatrixElement* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_SoTextureMatrixElement*)theWrappedObject)->promoted_makeEltIdentity());
}

void PythonQtWrapper_SoTextureMatrixElement::static_SoTextureMatrixElement_makeIdentity(SoState*  state, SoNode*  node)
{
  (SoTextureMatrixElement::makeIdentity(state, node));
}

void PythonQtWrapper_SoTextureMatrixElement::static_SoTextureMatrixElement_mult(SoState*  state, SoNode*  node, const SbMatrix&  matrix)
{
  (SoTextureMatrixElement::mult(state, node, matrix));
}

void PythonQtWrapper_SoTextureMatrixElement::multElt(SoTextureMatrixElement* theWrappedObject, const SbMatrix&  matrix)
{
  ( ((PythonQtPublicPromoter_SoTextureMatrixElement*)theWrappedObject)->promoted_multElt(matrix));
}

void PythonQtWrapper_SoTextureMatrixElement::static_SoTextureMatrixElement_rotateBy(SoState*  state, SoNode*  node, const SbRotation&  rotation)
{
  (SoTextureMatrixElement::rotateBy(state, node, rotation));
}

void PythonQtWrapper_SoTextureMatrixElement::rotateEltBy(SoTextureMatrixElement* theWrappedObject, const SbRotation&  translation)
{
  ( ((PythonQtPublicPromoter_SoTextureMatrixElement*)theWrappedObject)->promoted_rotateEltBy(translation));
}

void PythonQtWrapper_SoTextureMatrixElement::static_SoTextureMatrixElement_scaleBy(SoState*  state, SoNode*  node, const SbVec3f&  scaleFactor)
{
  (SoTextureMatrixElement::scaleBy(state, node, scaleFactor));
}

void PythonQtWrapper_SoTextureMatrixElement::scaleEltBy(SoTextureMatrixElement* theWrappedObject, const SbVec3f&  scaleFactor)
{
  ( ((PythonQtPublicPromoter_SoTextureMatrixElement*)theWrappedObject)->promoted_scaleEltBy(scaleFactor));
}

void PythonQtWrapper_SoTextureMatrixElement::static_SoTextureMatrixElement_translateBy(SoState*  state, SoNode*  node, const SbVec3f&  translation)
{
  (SoTextureMatrixElement::translateBy(state, node, translation));
}

void PythonQtWrapper_SoTextureMatrixElement::translateEltBy(SoTextureMatrixElement* theWrappedObject, const SbVec3f&  translation)
{
  ( ((PythonQtPublicPromoter_SoTextureMatrixElement*)theWrappedObject)->promoted_translateEltBy(translation));
}


