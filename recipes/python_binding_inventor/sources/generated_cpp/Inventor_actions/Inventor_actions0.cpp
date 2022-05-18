/*************************************************************************************
**
** Copyright 2022, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/
#include "Inventor_actions0.h"
#include <PythonQtConversion.h>
#include <PythonQtMethodInfo.h>
#include <PythonQtSignalReceiver.h>
#include <QVariant>
#include <Inventor/SbBox.h>
#include <Inventor/SbColor.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SoOutput.h>
#include <Inventor/SoPath.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/SoPrimitiveVertex.h>
#include <Inventor/SoType.h>
#include <Inventor/actions/SoAction.h>
#include <Inventor/events/SoEvent.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoShape.h>
#include <stdexcept>

void PythonQtWrapper_SoAction::apply(SoAction* theWrappedObject, SoNode*  node)
{
  ( theWrappedObject->apply(node));
}

void PythonQtWrapper_SoAction::apply(SoAction* theWrappedObject, SoPath*  path)
{
  ( theWrappedObject->apply(path));
}

void PythonQtWrapper_SoAction::beginTraversal(SoAction* theWrappedObject, SoNode*  node)
{
  ( ((PythonQtPublicPromoter_SoAction*)theWrappedObject)->promoted_beginTraversal(node));
}

SoType  PythonQtWrapper_SoAction::static_SoAction_getClassTypeId()
{
  return (SoAction::getClassTypeId());
}

const SoPath*  PythonQtWrapper_SoAction::getCurPath(SoAction* theWrappedObject)
{
  return ( theWrappedObject->getCurPath());
}

SoAction::PathCode  PythonQtWrapper_SoAction::getCurPathCode(SoAction* theWrappedObject) const
{
  return ( theWrappedObject->getCurPathCode());
}

SoNode*  PythonQtWrapper_SoAction::getCurPathTail(SoAction* theWrappedObject)
{
  return ( theWrappedObject->getCurPathTail());
}

SoNode*  PythonQtWrapper_SoAction::getNodeAppliedTo(SoAction* theWrappedObject) const
{
  return ( theWrappedObject->getNodeAppliedTo());
}

SoPath*  PythonQtWrapper_SoAction::getPathAppliedTo(SoAction* theWrappedObject) const
{
  return ( theWrappedObject->getPathAppliedTo());
}

SoState*  PythonQtWrapper_SoAction::getState(SoAction* theWrappedObject) const
{
  return ( theWrappedObject->getState());
}

SoAction::AppliedCode  PythonQtWrapper_SoAction::getWhatAppliedTo(SoAction* theWrappedObject) const
{
  return ( theWrappedObject->getWhatAppliedTo());
}

bool  PythonQtWrapper_SoAction::hasTerminated(SoAction* theWrappedObject) const
{
  return ( theWrappedObject->hasTerminated());
}

void PythonQtWrapper_SoAction::invalidateState(SoAction* theWrappedObject)
{
  ( theWrappedObject->invalidateState());
}

bool  PythonQtWrapper_SoAction::isLastPathListAppliedTo(SoAction* theWrappedObject) const
{
  return ( theWrappedObject->isLastPathListAppliedTo());
}

bool  PythonQtWrapper_SoAction::isOfType(SoAction* theWrappedObject, SoType  type) const
{
  return ( theWrappedObject->isOfType(type));
}

void PythonQtWrapper_SoAction::static_SoAction_nullAction(SoAction*  arg__1, SoNode*  arg__2)
{
  (SoAction::nullAction(arg__1, arg__2));
}

void PythonQtWrapper_SoAction::popCurPath(SoAction* theWrappedObject)
{
  ( theWrappedObject->popCurPath());
}

void PythonQtWrapper_SoAction::popCurPath(SoAction* theWrappedObject, SoAction::PathCode  prevPathCode)
{
  ( theWrappedObject->popCurPath(prevPathCode));
}

void PythonQtWrapper_SoAction::popPushCurPath(SoAction* theWrappedObject, int  childIndex)
{
  ( theWrappedObject->popPushCurPath(childIndex));
}

void PythonQtWrapper_SoAction::pushCurPath(SoAction* theWrappedObject)
{
  ( theWrappedObject->pushCurPath());
}

void PythonQtWrapper_SoAction::pushCurPath(SoAction* theWrappedObject, int  childIndex)
{
  ( theWrappedObject->pushCurPath(childIndex));
}

void PythonQtWrapper_SoAction::setTerminated(SoAction* theWrappedObject, bool  flag)
{
  ( ((PythonQtPublicPromoter_SoAction*)theWrappedObject)->promoted_setTerminated(flag));
}

bool  PythonQtWrapper_SoAction::shouldCompactPathLists(SoAction* theWrappedObject) const
{
  return ( ((PythonQtPublicPromoter_SoAction*)theWrappedObject)->promoted_shouldCompactPathLists());
}

void PythonQtWrapper_SoAction::traverse(SoAction* theWrappedObject, SoNode*  node)
{
  ( theWrappedObject->traverse(node));
}



PythonQtShell_SoCallbackAction::~PythonQtShell_SoCallbackAction() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoCallbackAction::apply(SoNode*  node0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("apply");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&node0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoCallbackAction::apply(node0);
}
void PythonQtShell_SoCallbackAction::apply(SoPath*  path0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("apply");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoPath*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&path0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoCallbackAction::apply(path0);
}
void PythonQtShell_SoCallbackAction::beginTraversal(SoNode*  node0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("beginTraversal");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&node0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoCallbackAction::beginTraversal(node0);
}
SoNode*  PythonQtShell_SoCallbackAction::getCurPathTail()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("getCurPathTail");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoNode* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getCurPathTail", methodInfo, result);
          } else {
            returnValue = *((SoNode**)args[0]);
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
  return SoCallbackAction::getCurPathTail();
}
void PythonQtShell_SoCallbackAction::invalidateState()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("invalidateState");
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
  SoCallbackAction::invalidateState();
}
bool  PythonQtShell_SoCallbackAction::shouldCompactPathLists() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("shouldCompactPathLists");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("shouldCompactPathLists", methodInfo, result);
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
  return SoCallbackAction::shouldCompactPathLists();
}
SoCallbackAction* PythonQtWrapper_SoCallbackAction::new_SoCallbackAction()
{ 
return new PythonQtShell_SoCallbackAction(); }

void PythonQtWrapper_SoCallbackAction::static_SoCallbackAction_enableElement(SoType  t, int  stkIndex)
{
  (SoCallbackAction::enableElement(t, stkIndex));
}

SoType  PythonQtWrapper_SoCallbackAction::static_SoCallbackAction_getClassTypeId()
{
  return (SoCallbackAction::getClassTypeId());
}

float  PythonQtWrapper_SoCallbackAction::getComplexity(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getComplexity());
}

SoComplexity::Type  PythonQtWrapper_SoCallbackAction::getComplexityType(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getComplexityType());
}

const SbVec3f*  PythonQtWrapper_SoCallbackAction::getCoordinate3(SoCallbackAction* theWrappedObject, int  index) const
{
  return &( theWrappedObject->getCoordinate3(index));
}

const SbVec4f*  PythonQtWrapper_SoCallbackAction::getCoordinate4(SoCallbackAction* theWrappedObject, int  index) const
{
  return &( theWrappedObject->getCoordinate4(index));
}

float  PythonQtWrapper_SoCallbackAction::getCreaseAngle(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getCreaseAngle());
}

SoCallbackAction::Response  PythonQtWrapper_SoCallbackAction::getCurrentResponse(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getCurrentResponse());
}

SoDrawStyle::Style  PythonQtWrapper_SoCallbackAction::getDrawStyle(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getDrawStyle());
}

SoShapeHints::FaceType  PythonQtWrapper_SoCallbackAction::getFaceType(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getFaceType());
}

float  PythonQtWrapper_SoCallbackAction::getFocalDistance(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getFocalDistance());
}

const SbName*  PythonQtWrapper_SoCallbackAction::getFontName(SoCallbackAction* theWrappedObject) const
{
  return &( theWrappedObject->getFontName());
}

float  PythonQtWrapper_SoCallbackAction::getFontSize(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getFontSize());
}

const SbVec3f*  PythonQtWrapper_SoCallbackAction::getLightAttenuation(SoCallbackAction* theWrappedObject) const
{
  return &( theWrappedObject->getLightAttenuation());
}

SoLightModel::Model  PythonQtWrapper_SoCallbackAction::getLightModel(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getLightModel());
}

float  PythonQtWrapper_SoCallbackAction::getLineWidth(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getLineWidth());
}

void PythonQtWrapper_SoCallbackAction::getMaterial(SoCallbackAction* theWrappedObject, SbColor&  ambient, SbColor&  diffuse, SbColor&  specular, SbColor&  emission, float&  shininess, float&  transparency, int  mtlIndex) const
{
  ( theWrappedObject->getMaterial(ambient, diffuse, specular, emission, shininess, transparency, mtlIndex));
}

SoMaterialBinding::Binding  PythonQtWrapper_SoCallbackAction::getMaterialBinding(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getMaterialBinding());
}

const SbMatrix*  PythonQtWrapper_SoCallbackAction::getModelMatrix(SoCallbackAction* theWrappedObject) const
{
  return &( theWrappedObject->getModelMatrix());
}

const SbVec3f*  PythonQtWrapper_SoCallbackAction::getNormal(SoCallbackAction* theWrappedObject, int  index) const
{
  return &( theWrappedObject->getNormal(index));
}

SoNormalBinding::Binding  PythonQtWrapper_SoCallbackAction::getNormalBinding(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getNormalBinding());
}

int  PythonQtWrapper_SoCallbackAction::getNumCoordinates(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getNumCoordinates());
}

int  PythonQtWrapper_SoCallbackAction::getNumNormals(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getNumNormals());
}

int  PythonQtWrapper_SoCallbackAction::getNumProfileCoordinates(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getNumProfileCoordinates());
}

int  PythonQtWrapper_SoCallbackAction::getNumTextureCoordinates(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getNumTextureCoordinates());
}

SoPickStyle::Style  PythonQtWrapper_SoCallbackAction::getPickStyle(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getPickStyle());
}

float  PythonQtWrapper_SoCallbackAction::getPointSize(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getPointSize());
}

const SbVec2f*  PythonQtWrapper_SoCallbackAction::getProfileCoordinate2(SoCallbackAction* theWrappedObject, int  index) const
{
  return &( theWrappedObject->getProfileCoordinate2(index));
}

const SbVec3f*  PythonQtWrapper_SoCallbackAction::getProfileCoordinate3(SoCallbackAction* theWrappedObject, int  index) const
{
  return &( theWrappedObject->getProfileCoordinate3(index));
}

const SbMatrix*  PythonQtWrapper_SoCallbackAction::getProjectionMatrix(SoCallbackAction* theWrappedObject) const
{
  return &( theWrappedObject->getProjectionMatrix());
}

SoShapeHints::ShapeType  PythonQtWrapper_SoCallbackAction::getShapeType(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getShapeType());
}

int  PythonQtWrapper_SoCallbackAction::getSwitch(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getSwitch());
}

const SbColor*  PythonQtWrapper_SoCallbackAction::getTextureBlendColor(SoCallbackAction* theWrappedObject) const
{
  return &( theWrappedObject->getTextureBlendColor());
}

const SbVec2f*  PythonQtWrapper_SoCallbackAction::getTextureCoordinate2(SoCallbackAction* theWrappedObject, int  index) const
{
  return &( theWrappedObject->getTextureCoordinate2(index));
}

const SbVec4f*  PythonQtWrapper_SoCallbackAction::getTextureCoordinate4(SoCallbackAction* theWrappedObject, int  index) const
{
  return &( theWrappedObject->getTextureCoordinate4(index));
}

SoTextureCoordinateBinding::Binding  PythonQtWrapper_SoCallbackAction::getTextureCoordinateBinding(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getTextureCoordinateBinding());
}

const unsigned char*  PythonQtWrapper_SoCallbackAction::getTextureImage(SoCallbackAction* theWrappedObject, SbVec2s&  size, int&  numComps) const
{
  return ( theWrappedObject->getTextureImage(size, numComps));
}

const SbMatrix*  PythonQtWrapper_SoCallbackAction::getTextureMatrix(SoCallbackAction* theWrappedObject) const
{
  return &( theWrappedObject->getTextureMatrix());
}

SoTexture2::Model  PythonQtWrapper_SoCallbackAction::getTextureModel(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getTextureModel());
}

SoTexture2::Wrap  PythonQtWrapper_SoCallbackAction::getTextureWrapS(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getTextureWrapS());
}

SoTexture2::Wrap  PythonQtWrapper_SoCallbackAction::getTextureWrapT(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getTextureWrapT());
}

SoUnits::Units  PythonQtWrapper_SoCallbackAction::getUnits(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getUnits());
}

SoShapeHints::VertexOrdering  PythonQtWrapper_SoCallbackAction::getVertexOrdering(SoCallbackAction* theWrappedObject) const
{
  return ( theWrappedObject->getVertexOrdering());
}

const SbViewVolume*  PythonQtWrapper_SoCallbackAction::getViewVolume(SoCallbackAction* theWrappedObject) const
{
  return &( theWrappedObject->getViewVolume());
}

const SbMatrix*  PythonQtWrapper_SoCallbackAction::getViewingMatrix(SoCallbackAction* theWrappedObject) const
{
  return &( theWrappedObject->getViewingMatrix());
}

void PythonQtWrapper_SoCallbackAction::invokeLineSegmentCallbacks(SoCallbackAction* theWrappedObject, const SoShape*  shape, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2)
{
  ( theWrappedObject->invokeLineSegmentCallbacks(shape, v1, v2));
}

void PythonQtWrapper_SoCallbackAction::invokePointCallbacks(SoCallbackAction* theWrappedObject, const SoShape*  shape, const SoPrimitiveVertex*  v)
{
  ( theWrappedObject->invokePointCallbacks(shape, v));
}

void PythonQtWrapper_SoCallbackAction::invokePostCallbacks(SoCallbackAction* theWrappedObject, const SoNode*  node)
{
  ( theWrappedObject->invokePostCallbacks(node));
}

void PythonQtWrapper_SoCallbackAction::invokePreCallbacks(SoCallbackAction* theWrappedObject, const SoNode*  node)
{
  ( theWrappedObject->invokePreCallbacks(node));
}

void PythonQtWrapper_SoCallbackAction::invokeTriangleCallbacks(SoCallbackAction* theWrappedObject, const SoShape*  shape, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3)
{
  ( theWrappedObject->invokeTriangleCallbacks(shape, v1, v2, v3));
}

void PythonQtWrapper_SoCallbackAction::setCurrentNode(SoCallbackAction* theWrappedObject, SoNode*  node)
{
  ( theWrappedObject->setCurrentNode(node));
}

bool  PythonQtWrapper_SoCallbackAction::shouldGeneratePrimitives(SoCallbackAction* theWrappedObject, const SoShape*  shape) const
{
  return ( theWrappedObject->shouldGeneratePrimitives(shape));
}



PythonQtShell_SoGLRenderAction::~PythonQtShell_SoGLRenderAction() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoGLRenderAction::apply(SoNode*  node0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("apply");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&node0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLRenderAction::apply(node0);
}
void PythonQtShell_SoGLRenderAction::apply(SoPath*  path0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("apply");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoPath*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&path0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLRenderAction::apply(path0);
}
void PythonQtShell_SoGLRenderAction::beginTraversal(SoNode*  node0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("beginTraversal");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&node0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGLRenderAction::beginTraversal(node0);
}
SoNode*  PythonQtShell_SoGLRenderAction::getCurPathTail()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("getCurPathTail");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoNode* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getCurPathTail", methodInfo, result);
          } else {
            returnValue = *((SoNode**)args[0]);
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
  return SoGLRenderAction::getCurPathTail();
}
void PythonQtShell_SoGLRenderAction::invalidateState()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("invalidateState");
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
  SoGLRenderAction::invalidateState();
}
bool  PythonQtShell_SoGLRenderAction::shouldCompactPathLists() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("shouldCompactPathLists");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("shouldCompactPathLists", methodInfo, result);
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
  return SoGLRenderAction::shouldCompactPathLists();
}
SoGLRenderAction* PythonQtWrapper_SoGLRenderAction::new_SoGLRenderAction(const SbViewportRegion&  viewportRegion)
{ 
return new PythonQtShell_SoGLRenderAction(viewportRegion); }

bool  PythonQtWrapper_SoGLRenderAction::abortNow(SoGLRenderAction* theWrappedObject)
{
  return ( theWrappedObject->abortNow());
}

void PythonQtWrapper_SoGLRenderAction::addDelayedPath(SoGLRenderAction* theWrappedObject, SoPath*  path)
{
  ( theWrappedObject->addDelayedPath(path));
}

void PythonQtWrapper_SoGLRenderAction::static_SoGLRenderAction_enableElement(SoType  t, int  stkIndex)
{
  (SoGLRenderAction::enableElement(t, stkIndex));
}

bool  PythonQtWrapper_SoGLRenderAction::getAllowDelayedPaths(SoGLRenderAction* theWrappedObject)
{
  return ( theWrappedObject->getAllowDelayedPaths());
}

unsigned int  PythonQtWrapper_SoGLRenderAction::getCacheContext(SoGLRenderAction* theWrappedObject) const
{
  return ( theWrappedObject->getCacheContext());
}

SoType  PythonQtWrapper_SoGLRenderAction::static_SoGLRenderAction_getClassTypeId()
{
  return (SoGLRenderAction::getClassTypeId());
}

int  PythonQtWrapper_SoGLRenderAction::getCullTestResults(SoGLRenderAction* theWrappedObject)
{
  return ( theWrappedObject->getCullTestResults());
}

int  PythonQtWrapper_SoGLRenderAction::getCurPass(SoGLRenderAction* theWrappedObject) const
{
  return ( theWrappedObject->getCurPass());
}

int  PythonQtWrapper_SoGLRenderAction::getNumPasses(SoGLRenderAction* theWrappedObject) const
{
  return ( theWrappedObject->getNumPasses());
}

SoGLRenderAction::TransparencyType  PythonQtWrapper_SoGLRenderAction::getTransparencyType(SoGLRenderAction* theWrappedObject) const
{
  return ( theWrappedObject->getTransparencyType());
}

void PythonQtWrapper_SoGLRenderAction::getUpdateArea(SoGLRenderAction* theWrappedObject, SbVec2f&  origin, SbVec2f&  size) const
{
  ( theWrappedObject->getUpdateArea(origin, size));
}

const SbViewportRegion*  PythonQtWrapper_SoGLRenderAction::getViewportRegion(SoGLRenderAction* theWrappedObject) const
{
  return &( theWrappedObject->getViewportRegion());
}

bool  PythonQtWrapper_SoGLRenderAction::handleTransparency(SoGLRenderAction* theWrappedObject, bool  isTransparent)
{
  return ( theWrappedObject->handleTransparency(isTransparent));
}

bool  PythonQtWrapper_SoGLRenderAction::isDelaying(SoGLRenderAction* theWrappedObject) const
{
  return ( theWrappedObject->isDelaying());
}

bool  PythonQtWrapper_SoGLRenderAction::isPassUpdate(SoGLRenderAction* theWrappedObject) const
{
  return ( theWrappedObject->isPassUpdate());
}

bool  PythonQtWrapper_SoGLRenderAction::isRenderingDelayedPaths(SoGLRenderAction* theWrappedObject) const
{
  return ( theWrappedObject->isRenderingDelayedPaths());
}

bool  PythonQtWrapper_SoGLRenderAction::isSmoothing(SoGLRenderAction* theWrappedObject) const
{
  return ( theWrappedObject->isSmoothing());
}

bool  PythonQtWrapper_SoGLRenderAction::setAllowDelayedPath(SoGLRenderAction* theWrappedObject, bool  flag)
{
  return ( theWrappedObject->setAllowDelayedPath(flag));
}

void PythonQtWrapper_SoGLRenderAction::setCacheContext(SoGLRenderAction* theWrappedObject, unsigned int  context)
{
  ( theWrappedObject->setCacheContext(context));
}

void PythonQtWrapper_SoGLRenderAction::setCullTestResults(SoGLRenderAction* theWrappedObject, int  b)
{
  ( theWrappedObject->setCullTestResults(b));
}

void PythonQtWrapper_SoGLRenderAction::setNumPasses(SoGLRenderAction* theWrappedObject, int  num)
{
  ( theWrappedObject->setNumPasses(num));
}

void PythonQtWrapper_SoGLRenderAction::setPassUpdate(SoGLRenderAction* theWrappedObject, bool  flag)
{
  ( theWrappedObject->setPassUpdate(flag));
}

void PythonQtWrapper_SoGLRenderAction::setSmoothing(SoGLRenderAction* theWrappedObject, bool  smooth)
{
  ( theWrappedObject->setSmoothing(smooth));
}

void PythonQtWrapper_SoGLRenderAction::setTransparencyType(SoGLRenderAction* theWrappedObject, SoGLRenderAction::TransparencyType  type)
{
  ( theWrappedObject->setTransparencyType(type));
}

void PythonQtWrapper_SoGLRenderAction::setUpdateArea(SoGLRenderAction* theWrappedObject, const SbVec2f&  origin, const SbVec2f&  size)
{
  ( theWrappedObject->setUpdateArea(origin, size));
}

void PythonQtWrapper_SoGLRenderAction::setViewportRegion(SoGLRenderAction* theWrappedObject, const SbViewportRegion&  newRegion)
{
  ( theWrappedObject->setViewportRegion(newRegion));
}



PythonQtShell_SoGetBoundingBoxAction::~PythonQtShell_SoGetBoundingBoxAction() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoGetBoundingBoxAction::apply(SoNode*  node0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("apply");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&node0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGetBoundingBoxAction::apply(node0);
}
void PythonQtShell_SoGetBoundingBoxAction::apply(SoPath*  path0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("apply");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoPath*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&path0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGetBoundingBoxAction::apply(path0);
}
void PythonQtShell_SoGetBoundingBoxAction::beginTraversal(SoNode*  node0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("beginTraversal");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&node0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGetBoundingBoxAction::beginTraversal(node0);
}
SoNode*  PythonQtShell_SoGetBoundingBoxAction::getCurPathTail()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("getCurPathTail");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoNode* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getCurPathTail", methodInfo, result);
          } else {
            returnValue = *((SoNode**)args[0]);
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
  return SoGetBoundingBoxAction::getCurPathTail();
}
void PythonQtShell_SoGetBoundingBoxAction::invalidateState()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("invalidateState");
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
  SoGetBoundingBoxAction::invalidateState();
}
bool  PythonQtShell_SoGetBoundingBoxAction::shouldCompactPathLists() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("shouldCompactPathLists");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("shouldCompactPathLists", methodInfo, result);
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
  return SoGetBoundingBoxAction::shouldCompactPathLists();
}
SoGetBoundingBoxAction* PythonQtWrapper_SoGetBoundingBoxAction::new_SoGetBoundingBoxAction(const SbViewportRegion&  viewportRegion)
{ 
return new PythonQtShell_SoGetBoundingBoxAction(viewportRegion); }

void PythonQtWrapper_SoGetBoundingBoxAction::checkResetAfter(SoGetBoundingBoxAction* theWrappedObject)
{
  ( theWrappedObject->checkResetAfter());
}

void PythonQtWrapper_SoGetBoundingBoxAction::checkResetBefore(SoGetBoundingBoxAction* theWrappedObject)
{
  ( theWrappedObject->checkResetBefore());
}

void PythonQtWrapper_SoGetBoundingBoxAction::static_SoGetBoundingBoxAction_enableElement(SoType  t, int  stkIndex)
{
  (SoGetBoundingBoxAction::enableElement(t, stkIndex));
}

void PythonQtWrapper_SoGetBoundingBoxAction::extendBy(SoGetBoundingBoxAction* theWrappedObject, const SbBox3f&  box)
{
  ( theWrappedObject->extendBy(box));
}

void PythonQtWrapper_SoGetBoundingBoxAction::extendBy(SoGetBoundingBoxAction* theWrappedObject, const SbXfBox3f&  box)
{
  ( theWrappedObject->extendBy(box));
}

SbBox3f  PythonQtWrapper_SoGetBoundingBoxAction::getBoundingBox(SoGetBoundingBoxAction* theWrappedObject) const
{
  return ( theWrappedObject->getBoundingBox());
}

const SbVec3f*  PythonQtWrapper_SoGetBoundingBoxAction::getCenter(SoGetBoundingBoxAction* theWrappedObject) const
{
  return &( theWrappedObject->getCenter());
}

SoType  PythonQtWrapper_SoGetBoundingBoxAction::static_SoGetBoundingBoxAction_getClassTypeId()
{
  return (SoGetBoundingBoxAction::getClassTypeId());
}

const SoPath*  PythonQtWrapper_SoGetBoundingBoxAction::getResetPath(SoGetBoundingBoxAction* theWrappedObject) const
{
  return ( theWrappedObject->getResetPath());
}

const SbViewportRegion*  PythonQtWrapper_SoGetBoundingBoxAction::getViewportRegion(SoGetBoundingBoxAction* theWrappedObject) const
{
  return &( theWrappedObject->getViewportRegion());
}

SoGetBoundingBoxAction::ResetType  PythonQtWrapper_SoGetBoundingBoxAction::getWhatReset(SoGetBoundingBoxAction* theWrappedObject) const
{
  return ( theWrappedObject->getWhatReset());
}

SbXfBox3f*  PythonQtWrapper_SoGetBoundingBoxAction::getXfBoundingBox(SoGetBoundingBoxAction* theWrappedObject)
{
  return &( theWrappedObject->getXfBoundingBox());
}

bool  PythonQtWrapper_SoGetBoundingBoxAction::isCenterSet(SoGetBoundingBoxAction* theWrappedObject) const
{
  return ( theWrappedObject->isCenterSet());
}

bool  PythonQtWrapper_SoGetBoundingBoxAction::isInCameraSpace(SoGetBoundingBoxAction* theWrappedObject) const
{
  return ( theWrappedObject->isInCameraSpace());
}

bool  PythonQtWrapper_SoGetBoundingBoxAction::isResetBefore(SoGetBoundingBoxAction* theWrappedObject) const
{
  return ( theWrappedObject->isResetBefore());
}

bool  PythonQtWrapper_SoGetBoundingBoxAction::isResetPath(SoGetBoundingBoxAction* theWrappedObject) const
{
  return ( theWrappedObject->isResetPath());
}

void PythonQtWrapper_SoGetBoundingBoxAction::resetCenter(SoGetBoundingBoxAction* theWrappedObject)
{
  ( theWrappedObject->resetCenter());
}

void PythonQtWrapper_SoGetBoundingBoxAction::setCenter(SoGetBoundingBoxAction* theWrappedObject, const SbVec3f&  center, bool  transformCenter)
{
  ( theWrappedObject->setCenter(center, transformCenter));
}

void PythonQtWrapper_SoGetBoundingBoxAction::setInCameraSpace(SoGetBoundingBoxAction* theWrappedObject, bool  flag)
{
  ( theWrappedObject->setInCameraSpace(flag));
}

void PythonQtWrapper_SoGetBoundingBoxAction::setResetPath(SoGetBoundingBoxAction* theWrappedObject, const SoPath*  path, bool  resetBefore, SoGetBoundingBoxAction::ResetType  what)
{
  ( theWrappedObject->setResetPath(path, resetBefore, what));
}

void PythonQtWrapper_SoGetBoundingBoxAction::setViewportRegion(SoGetBoundingBoxAction* theWrappedObject, const SbViewportRegion&  newRegion)
{
  ( theWrappedObject->setViewportRegion(newRegion));
}



PythonQtShell_SoGetMatrixAction::~PythonQtShell_SoGetMatrixAction() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoGetMatrixAction::apply(SoNode*  node0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("apply");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&node0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGetMatrixAction::apply(node0);
}
void PythonQtShell_SoGetMatrixAction::apply(SoPath*  path0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("apply");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoPath*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&path0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGetMatrixAction::apply(path0);
}
void PythonQtShell_SoGetMatrixAction::beginTraversal(SoNode*  node0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("beginTraversal");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&node0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoGetMatrixAction::beginTraversal(node0);
}
SoNode*  PythonQtShell_SoGetMatrixAction::getCurPathTail()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("getCurPathTail");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoNode* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getCurPathTail", methodInfo, result);
          } else {
            returnValue = *((SoNode**)args[0]);
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
  return SoGetMatrixAction::getCurPathTail();
}
void PythonQtShell_SoGetMatrixAction::invalidateState()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("invalidateState");
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
  SoGetMatrixAction::invalidateState();
}
bool  PythonQtShell_SoGetMatrixAction::shouldCompactPathLists() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("shouldCompactPathLists");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("shouldCompactPathLists", methodInfo, result);
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
  return SoGetMatrixAction::shouldCompactPathLists();
}
SoGetMatrixAction* PythonQtWrapper_SoGetMatrixAction::new_SoGetMatrixAction(const SbViewportRegion&  newRegion)
{ 
return new PythonQtShell_SoGetMatrixAction(newRegion); }

void PythonQtWrapper_SoGetMatrixAction::static_SoGetMatrixAction_enableElement(SoType  t, int  stkIndex)
{
  (SoGetMatrixAction::enableElement(t, stkIndex));
}

SoType  PythonQtWrapper_SoGetMatrixAction::static_SoGetMatrixAction_getClassTypeId()
{
  return (SoGetMatrixAction::getClassTypeId());
}

SbMatrix*  PythonQtWrapper_SoGetMatrixAction::getInverse(SoGetMatrixAction* theWrappedObject)
{
  return &( theWrappedObject->getInverse());
}

SbMatrix*  PythonQtWrapper_SoGetMatrixAction::getMatrix(SoGetMatrixAction* theWrappedObject)
{
  return &( theWrappedObject->getMatrix());
}

SbMatrix*  PythonQtWrapper_SoGetMatrixAction::getTextureInverse(SoGetMatrixAction* theWrappedObject)
{
  return &( theWrappedObject->getTextureInverse());
}

SbMatrix*  PythonQtWrapper_SoGetMatrixAction::getTextureMatrix(SoGetMatrixAction* theWrappedObject)
{
  return &( theWrappedObject->getTextureMatrix());
}

const SbViewportRegion*  PythonQtWrapper_SoGetMatrixAction::getViewportRegion(SoGetMatrixAction* theWrappedObject) const
{
  return &( theWrappedObject->getViewportRegion());
}

void PythonQtWrapper_SoGetMatrixAction::setViewportRegion(SoGetMatrixAction* theWrappedObject, const SbViewportRegion&  newRegion)
{
  ( theWrappedObject->setViewportRegion(newRegion));
}



PythonQtShell_SoHandleEventAction::~PythonQtShell_SoHandleEventAction() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoHandleEventAction::apply(SoNode*  node0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("apply");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&node0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoHandleEventAction::apply(node0);
}
void PythonQtShell_SoHandleEventAction::apply(SoPath*  path0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("apply");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoPath*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&path0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoHandleEventAction::apply(path0);
}
void PythonQtShell_SoHandleEventAction::beginTraversal(SoNode*  node0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("beginTraversal");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&node0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoHandleEventAction::beginTraversal(node0);
}
SoNode*  PythonQtShell_SoHandleEventAction::getCurPathTail()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("getCurPathTail");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoNode* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getCurPathTail", methodInfo, result);
          } else {
            returnValue = *((SoNode**)args[0]);
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
  return SoHandleEventAction::getCurPathTail();
}
void PythonQtShell_SoHandleEventAction::invalidateState()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("invalidateState");
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
  SoHandleEventAction::invalidateState();
}
bool  PythonQtShell_SoHandleEventAction::shouldCompactPathLists() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("shouldCompactPathLists");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("shouldCompactPathLists", methodInfo, result);
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
  return SoHandleEventAction::shouldCompactPathLists();
}
SoHandleEventAction* PythonQtWrapper_SoHandleEventAction::new_SoHandleEventAction(const SbViewportRegion&  viewportRegion)
{ 
return new PythonQtShell_SoHandleEventAction(viewportRegion); }

void PythonQtWrapper_SoHandleEventAction::static_SoHandleEventAction_enableElement(SoType  t, int  stkIndex)
{
  (SoHandleEventAction::enableElement(t, stkIndex));
}

SoType  PythonQtWrapper_SoHandleEventAction::static_SoHandleEventAction_getClassTypeId()
{
  return (SoHandleEventAction::getClassTypeId());
}

const SoEvent*  PythonQtWrapper_SoHandleEventAction::getEvent(SoHandleEventAction* theWrappedObject) const
{
  return ( theWrappedObject->getEvent());
}

SoNode*  PythonQtWrapper_SoHandleEventAction::getGrabber(SoHandleEventAction* theWrappedObject) const
{
  return ( theWrappedObject->getGrabber());
}

SoNode*  PythonQtWrapper_SoHandleEventAction::getPickRoot(SoHandleEventAction* theWrappedObject) const
{
  return ( theWrappedObject->getPickRoot());
}

const SoPickedPoint*  PythonQtWrapper_SoHandleEventAction::getPickedPoint(SoHandleEventAction* theWrappedObject)
{
  return ( theWrappedObject->getPickedPoint());
}

const SbViewportRegion*  PythonQtWrapper_SoHandleEventAction::getViewportRegion(SoHandleEventAction* theWrappedObject) const
{
  return &( theWrappedObject->getViewportRegion());
}

bool  PythonQtWrapper_SoHandleEventAction::isHandled(SoHandleEventAction* theWrappedObject) const
{
  return ( theWrappedObject->isHandled());
}

void PythonQtWrapper_SoHandleEventAction::releaseGrabber(SoHandleEventAction* theWrappedObject)
{
  ( theWrappedObject->releaseGrabber());
}

void PythonQtWrapper_SoHandleEventAction::setEvent(SoHandleEventAction* theWrappedObject, const SoEvent*  ev)
{
  ( theWrappedObject->setEvent(ev));
}

void PythonQtWrapper_SoHandleEventAction::setGrabber(SoHandleEventAction* theWrappedObject, SoNode*  node)
{
  ( theWrappedObject->setGrabber(node));
}

void PythonQtWrapper_SoHandleEventAction::setHandled(SoHandleEventAction* theWrappedObject)
{
  ( theWrappedObject->setHandled());
}

void PythonQtWrapper_SoHandleEventAction::setPickRadius(SoHandleEventAction* theWrappedObject, float  radiusInPixels)
{
  ( theWrappedObject->setPickRadius(radiusInPixels));
}

void PythonQtWrapper_SoHandleEventAction::setPickRoot(SoHandleEventAction* theWrappedObject, SoNode*  node)
{
  ( theWrappedObject->setPickRoot(node));
}

void PythonQtWrapper_SoHandleEventAction::setViewportRegion(SoHandleEventAction* theWrappedObject, const SbViewportRegion&  newRegion)
{
  ( theWrappedObject->setViewportRegion(newRegion));
}



PythonQtShell_SoPickAction::~PythonQtShell_SoPickAction() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoPickAction::apply(SoNode*  node0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("apply");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&node0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoPickAction::apply(node0);
}
void PythonQtShell_SoPickAction::apply(SoPath*  path0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("apply");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoPath*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&path0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoPickAction::apply(path0);
}
void PythonQtShell_SoPickAction::beginTraversal(SoNode*  node0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("beginTraversal");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&node0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoPickAction::beginTraversal(node0);
}
SoNode*  PythonQtShell_SoPickAction::getCurPathTail()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("getCurPathTail");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoNode* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getCurPathTail", methodInfo, result);
          } else {
            returnValue = *((SoNode**)args[0]);
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
  return SoPickAction::getCurPathTail();
}
void PythonQtShell_SoPickAction::invalidateState()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("invalidateState");
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
  SoPickAction::invalidateState();
}
bool  PythonQtShell_SoPickAction::shouldCompactPathLists() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("shouldCompactPathLists");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("shouldCompactPathLists", methodInfo, result);
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
  return SoPickAction::shouldCompactPathLists();
}
SoPickAction* PythonQtWrapper_SoPickAction::new_SoPickAction(const SbViewportRegion&  viewportRegion)
{ 
return new PythonQtShell_SoPickAction(viewportRegion); }

void PythonQtWrapper_SoPickAction::enableCulling(SoPickAction* theWrappedObject, bool  flag)
{
  ( theWrappedObject->enableCulling(flag));
}

void PythonQtWrapper_SoPickAction::static_SoPickAction_enableElement(SoType  t, int  stkIndex)
{
  (SoPickAction::enableElement(t, stkIndex));
}

SoType  PythonQtWrapper_SoPickAction::static_SoPickAction_getClassTypeId()
{
  return (SoPickAction::getClassTypeId());
}

const SbViewportRegion*  PythonQtWrapper_SoPickAction::getViewportRegion(SoPickAction* theWrappedObject) const
{
  return &( theWrappedObject->getViewportRegion());
}

bool  PythonQtWrapper_SoPickAction::isCullingEnabled(SoPickAction* theWrappedObject) const
{
  return ( theWrappedObject->isCullingEnabled());
}

void PythonQtWrapper_SoPickAction::setViewportRegion(SoPickAction* theWrappedObject, const SbViewportRegion&  newRegion)
{
  ( theWrappedObject->setViewportRegion(newRegion));
}



PythonQtShell_SoRayPickAction::~PythonQtShell_SoRayPickAction() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoRayPickAction::apply(SoNode*  node0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("apply");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&node0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoRayPickAction::apply(node0);
}
void PythonQtShell_SoRayPickAction::apply(SoPath*  path0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("apply");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoPath*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&path0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoRayPickAction::apply(path0);
}
void PythonQtShell_SoRayPickAction::beginTraversal(SoNode*  node0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("beginTraversal");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&node0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoRayPickAction::beginTraversal(node0);
}
SoNode*  PythonQtShell_SoRayPickAction::getCurPathTail()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("getCurPathTail");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoNode* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getCurPathTail", methodInfo, result);
          } else {
            returnValue = *((SoNode**)args[0]);
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
  return SoRayPickAction::getCurPathTail();
}
void PythonQtShell_SoRayPickAction::invalidateState()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("invalidateState");
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
  SoRayPickAction::invalidateState();
}
bool  PythonQtShell_SoRayPickAction::shouldCompactPathLists() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("shouldCompactPathLists");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("shouldCompactPathLists", methodInfo, result);
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
  return SoRayPickAction::shouldCompactPathLists();
}
SoRayPickAction* PythonQtWrapper_SoRayPickAction::new_SoRayPickAction(const SbViewportRegion&  viewportRegion)
{ 
return new PythonQtShell_SoRayPickAction(viewportRegion); }

SoPickedPoint*  PythonQtWrapper_SoRayPickAction::addIntersection(SoRayPickAction* theWrappedObject, const SbVec3f&  objectSpacePoint)
{
  return ( theWrappedObject->addIntersection(objectSpacePoint));
}

void PythonQtWrapper_SoRayPickAction::computeWorldSpaceRay(SoRayPickAction* theWrappedObject)
{
  ( theWrappedObject->computeWorldSpaceRay());
}

void PythonQtWrapper_SoRayPickAction::static_SoRayPickAction_enableElement(SoType  t, int  stkIndex)
{
  (SoRayPickAction::enableElement(t, stkIndex));
}

SoType  PythonQtWrapper_SoRayPickAction::static_SoRayPickAction_getClassTypeId()
{
  return (SoRayPickAction::getClassTypeId());
}

const SbLine*  PythonQtWrapper_SoRayPickAction::getLine(SoRayPickAction* theWrappedObject) const
{
  return &( theWrappedObject->getLine());
}

SoPickedPoint*  PythonQtWrapper_SoRayPickAction::getPickedPoint(SoRayPickAction* theWrappedObject, int  index) const
{
  return ( theWrappedObject->getPickedPoint(index));
}

const SbViewVolume*  PythonQtWrapper_SoRayPickAction::getViewVolume(SoRayPickAction* theWrappedObject) const
{
  return &( theWrappedObject->getViewVolume());
}

bool  PythonQtWrapper_SoRayPickAction::hasWorldSpaceRay(SoRayPickAction* theWrappedObject) const
{
  return ( theWrappedObject->hasWorldSpaceRay());
}

bool  PythonQtWrapper_SoRayPickAction::intersect(SoRayPickAction* theWrappedObject, const SbBox3f&  box, bool  useFullViewVolume)
{
  return ( theWrappedObject->intersect(box, useFullViewVolume));
}

bool  PythonQtWrapper_SoRayPickAction::intersect(SoRayPickAction* theWrappedObject, const SbVec3f&  point) const
{
  return ( theWrappedObject->intersect(point));
}

bool  PythonQtWrapper_SoRayPickAction::intersect(SoRayPickAction* theWrappedObject, const SbVec3f&  v0, const SbVec3f&  v1, SbVec3f&  intersection) const
{
  return ( theWrappedObject->intersect(v0, v1, intersection));
}

bool  PythonQtWrapper_SoRayPickAction::intersect(SoRayPickAction* theWrappedObject, const SbVec3f&  v0, const SbVec3f&  v1, const SbVec3f&  v2, SbVec3f&  intersection, SbVec3f&  barycentric, bool&  front) const
{
  return ( theWrappedObject->intersect(v0, v1, v2, intersection, barycentric, front));
}

bool  PythonQtWrapper_SoRayPickAction::isBetweenPlanes(SoRayPickAction* theWrappedObject, const SbVec3f&  intersection) const
{
  return ( theWrappedObject->isBetweenPlanes(intersection));
}

bool  PythonQtWrapper_SoRayPickAction::isPickAll(SoRayPickAction* theWrappedObject) const
{
  return ( theWrappedObject->isPickAll());
}

void PythonQtWrapper_SoRayPickAction::setNormalizedPoint(SoRayPickAction* theWrappedObject, const SbVec2f&  normPoint)
{
  ( theWrappedObject->setNormalizedPoint(normPoint));
}

void PythonQtWrapper_SoRayPickAction::setObjectSpace(SoRayPickAction* theWrappedObject)
{
  ( theWrappedObject->setObjectSpace());
}

void PythonQtWrapper_SoRayPickAction::setObjectSpace(SoRayPickAction* theWrappedObject, const SbMatrix&  matrix)
{
  ( theWrappedObject->setObjectSpace(matrix));
}

void PythonQtWrapper_SoRayPickAction::setPickAll(SoRayPickAction* theWrappedObject, bool  flag)
{
  ( theWrappedObject->setPickAll(flag));
}

void PythonQtWrapper_SoRayPickAction::setPoint(SoRayPickAction* theWrappedObject, const SbVec2s&  viewportPoint)
{
  ( theWrappedObject->setPoint(viewportPoint));
}

void PythonQtWrapper_SoRayPickAction::setRadius(SoRayPickAction* theWrappedObject, float  radiusInPixels)
{
  ( theWrappedObject->setRadius(radiusInPixels));
}

void PythonQtWrapper_SoRayPickAction::setRay(SoRayPickAction* theWrappedObject, const SbVec3f&  start, const SbVec3f&  direction, float  nearDistance, float  farDistance)
{
  ( theWrappedObject->setRay(start, direction, nearDistance, farDistance));
}



PythonQtShell_SoSearchAction::~PythonQtShell_SoSearchAction() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoSearchAction::apply(SoNode*  node0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("apply");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&node0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoSearchAction::apply(node0);
}
void PythonQtShell_SoSearchAction::apply(SoPath*  path0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("apply");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoPath*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&path0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoSearchAction::apply(path0);
}
void PythonQtShell_SoSearchAction::beginTraversal(SoNode*  node0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("beginTraversal");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&node0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoSearchAction::beginTraversal(node0);
}
SoNode*  PythonQtShell_SoSearchAction::getCurPathTail()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("getCurPathTail");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoNode* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getCurPathTail", methodInfo, result);
          } else {
            returnValue = *((SoNode**)args[0]);
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
  return SoSearchAction::getCurPathTail();
}
void PythonQtShell_SoSearchAction::invalidateState()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("invalidateState");
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
  SoSearchAction::invalidateState();
}
bool  PythonQtShell_SoSearchAction::shouldCompactPathLists() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("shouldCompactPathLists");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("shouldCompactPathLists", methodInfo, result);
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
  return SoSearchAction::shouldCompactPathLists();
}
SoSearchAction* PythonQtWrapper_SoSearchAction::new_SoSearchAction()
{ 
return new PythonQtShell_SoSearchAction(); }

void PythonQtWrapper_SoSearchAction::addPath(SoSearchAction* theWrappedObject, SoPath*  path)
{
  ( theWrappedObject->addPath(path));
}

void PythonQtWrapper_SoSearchAction::static_SoSearchAction_enableElement(SoType  t, int  stkIndex)
{
  (SoSearchAction::enableElement(t, stkIndex));
}

SoType  PythonQtWrapper_SoSearchAction::static_SoSearchAction_getClassTypeId()
{
  return (SoSearchAction::getClassTypeId());
}

int  PythonQtWrapper_SoSearchAction::getFind(SoSearchAction* theWrappedObject)
{
  return ( theWrappedObject->getFind());
}

SoSearchAction::Interest  PythonQtWrapper_SoSearchAction::getInterest(SoSearchAction* theWrappedObject) const
{
  return ( theWrappedObject->getInterest());
}

const SbName*  PythonQtWrapper_SoSearchAction::getName(SoSearchAction* theWrappedObject) const
{
  return &( theWrappedObject->getName());
}

SoNode*  PythonQtWrapper_SoSearchAction::getNode(SoSearchAction* theWrappedObject) const
{
  return ( theWrappedObject->getNode());
}

SoPath*  PythonQtWrapper_SoSearchAction::getPath(SoSearchAction* theWrappedObject) const
{
  return ( theWrappedObject->getPath());
}

bool  PythonQtWrapper_SoSearchAction::isFound(SoSearchAction* theWrappedObject) const
{
  return ( theWrappedObject->isFound());
}

bool  PythonQtWrapper_SoSearchAction::isSearchingAll(SoSearchAction* theWrappedObject) const
{
  return ( theWrappedObject->isSearchingAll());
}

void PythonQtWrapper_SoSearchAction::reset(SoSearchAction* theWrappedObject)
{
  ( theWrappedObject->reset());
}

void PythonQtWrapper_SoSearchAction::setFind(SoSearchAction* theWrappedObject, int  what)
{
  ( theWrappedObject->setFind(what));
}

void PythonQtWrapper_SoSearchAction::setFound(SoSearchAction* theWrappedObject)
{
  ( theWrappedObject->setFound());
}

void PythonQtWrapper_SoSearchAction::setInterest(SoSearchAction* theWrappedObject, SoSearchAction::Interest  i)
{
  ( theWrappedObject->setInterest(i));
}

void PythonQtWrapper_SoSearchAction::setName(SoSearchAction* theWrappedObject, const SbName&  n)
{
  ( theWrappedObject->setName(n));
}

void PythonQtWrapper_SoSearchAction::setNode(SoSearchAction* theWrappedObject, SoNode*  n)
{
  ( theWrappedObject->setNode(n));
}

void PythonQtWrapper_SoSearchAction::setSearchingAll(SoSearchAction* theWrappedObject, bool  flag)
{
  ( theWrappedObject->setSearchingAll(flag));
}

void PythonQtWrapper_SoSearchAction::setType(SoSearchAction* theWrappedObject, SoType  t, bool  derivedIsOk)
{
  ( theWrappedObject->setType(t, derivedIsOk));
}



PythonQtShell_SoWriteAction::~PythonQtShell_SoWriteAction() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoWriteAction::apply(SoNode*  node0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("apply");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&node0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoWriteAction::apply(node0);
}
void PythonQtShell_SoWriteAction::apply(SoPath*  path0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("apply");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoPath*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&path0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoWriteAction::apply(path0);
}
void PythonQtShell_SoWriteAction::beginTraversal(SoNode*  node0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("beginTraversal");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&node0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoWriteAction::beginTraversal(node0);
}
SoNode*  PythonQtShell_SoWriteAction::getCurPathTail()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("getCurPathTail");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoNode* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getCurPathTail", methodInfo, result);
          } else {
            returnValue = *((SoNode**)args[0]);
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
  return SoWriteAction::getCurPathTail();
}
void PythonQtShell_SoWriteAction::invalidateState()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("invalidateState");
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
  SoWriteAction::invalidateState();
}
bool  PythonQtShell_SoWriteAction::shouldCompactPathLists() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("shouldCompactPathLists");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("shouldCompactPathLists", methodInfo, result);
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
  return SoWriteAction::shouldCompactPathLists();
}
SoWriteAction* PythonQtWrapper_SoWriteAction::new_SoWriteAction()
{ 
return new PythonQtShell_SoWriteAction(); }

SoWriteAction* PythonQtWrapper_SoWriteAction::new_SoWriteAction(SoOutput*  out)
{ 
return new PythonQtShell_SoWriteAction(out); }

void PythonQtWrapper_SoWriteAction::continueToApply(SoWriteAction* theWrappedObject, SoNode*  node)
{
  ( theWrappedObject->continueToApply(node));
}

void PythonQtWrapper_SoWriteAction::continueToApply(SoWriteAction* theWrappedObject, SoPath*  path)
{
  ( theWrappedObject->continueToApply(path));
}

void PythonQtWrapper_SoWriteAction::static_SoWriteAction_enableElement(SoType  t, int  stkIndex)
{
  (SoWriteAction::enableElement(t, stkIndex));
}

SoType  PythonQtWrapper_SoWriteAction::static_SoWriteAction_getClassTypeId()
{
  return (SoWriteAction::getClassTypeId());
}

SoOutput*  PythonQtWrapper_SoWriteAction::getOutput(SoWriteAction* theWrappedObject) const
{
  return ( theWrappedObject->getOutput());
}


