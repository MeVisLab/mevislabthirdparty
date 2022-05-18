/*************************************************************************************
**
** Copyright 2022, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/
#include <PythonQt.h>
#include <QObject>
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
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoGetMatrixAction.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/actions/SoPickAction.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/events/SoEvent.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoShape.h>
#include <stdexcept>



class PythonQtPublicPromoter_SoAction : public SoAction
{ public:
inline void promoted_beginTraversal(SoNode*  node) { this->beginTraversal(node); }
inline void promoted_setTerminated(bool  flag) { this->setTerminated(flag); }
inline bool  promoted_shouldCompactPathLists() const { return this->shouldCompactPathLists(); }
inline void py_q_apply(SoNode*  node) { SoAction::apply(node); }
inline void py_q_apply(SoPath*  path) { SoAction::apply(path); }
inline void py_q_beginTraversal(SoNode*  node) { SoAction::beginTraversal(node); }
inline SoNode*  py_q_getCurPathTail() { return SoAction::getCurPathTail(); }
inline void py_q_invalidateState() { SoAction::invalidateState(); }
inline bool  py_q_shouldCompactPathLists() const { return SoAction::shouldCompactPathLists(); }
};

class PythonQtWrapper_SoAction : public QObject
{ Q_OBJECT
public:
Q_ENUMS(AppliedCode PathCode )
enum AppliedCode{
  NODE = SoAction::NODE,   PATH = SoAction::PATH,   PATH_LIST = SoAction::PATH_LIST};
enum PathCode{
  NO_PATH = SoAction::NO_PATH,   IN_PATH = SoAction::IN_PATH,   BELOW_PATH = SoAction::BELOW_PATH,   OFF_PATH = SoAction::OFF_PATH};
public slots:
void delete_SoAction(SoAction* obj) { delete obj; }
   void apply(SoAction* theWrappedObject, SoNode*  node);
   void py_q_apply(SoAction* theWrappedObject, SoNode*  node){  (((PythonQtPublicPromoter_SoAction*)theWrappedObject)->py_q_apply(node));}
   void apply(SoAction* theWrappedObject, SoPath*  path);
   void py_q_apply(SoAction* theWrappedObject, SoPath*  path){  (((PythonQtPublicPromoter_SoAction*)theWrappedObject)->py_q_apply(path));}
   void beginTraversal(SoAction* theWrappedObject, SoNode*  node);
   void py_q_beginTraversal(SoAction* theWrappedObject, SoNode*  node){  (((PythonQtPublicPromoter_SoAction*)theWrappedObject)->py_q_beginTraversal(node));}
   SoType  static_SoAction_getClassTypeId();
   const SoPath*  getCurPath(SoAction* theWrappedObject);
   SoAction::PathCode  getCurPathCode(SoAction* theWrappedObject) const;
   SoNode*  getCurPathTail(SoAction* theWrappedObject);
   SoNode*  py_q_getCurPathTail(SoAction* theWrappedObject){  return (((PythonQtPublicPromoter_SoAction*)theWrappedObject)->py_q_getCurPathTail());}
   SoNode*  getNodeAppliedTo(SoAction* theWrappedObject) const;
   SoPath*  getPathAppliedTo(SoAction* theWrappedObject) const;
   SoState*  getState(SoAction* theWrappedObject) const;
   SoAction::AppliedCode  getWhatAppliedTo(SoAction* theWrappedObject) const;
   bool  hasTerminated(SoAction* theWrappedObject) const;
   void invalidateState(SoAction* theWrappedObject);
   void py_q_invalidateState(SoAction* theWrappedObject){  (((PythonQtPublicPromoter_SoAction*)theWrappedObject)->py_q_invalidateState());}
   bool  isLastPathListAppliedTo(SoAction* theWrappedObject) const;
   bool  isOfType(SoAction* theWrappedObject, SoType  type) const;
   void static_SoAction_nullAction(SoAction*  arg__1, SoNode*  arg__2);
   void popCurPath(SoAction* theWrappedObject);
   void popCurPath(SoAction* theWrappedObject, SoAction::PathCode  prevPathCode);
   void popPushCurPath(SoAction* theWrappedObject, int  childIndex);
   void pushCurPath(SoAction* theWrappedObject);
   void pushCurPath(SoAction* theWrappedObject, int  childIndex);
   void setTerminated(SoAction* theWrappedObject, bool  flag);
   bool  shouldCompactPathLists(SoAction* theWrappedObject) const;
   bool  py_q_shouldCompactPathLists(SoAction* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoAction*)theWrappedObject)->py_q_shouldCompactPathLists());}
   void traverse(SoAction* theWrappedObject, SoNode*  node);
};





class PythonQtShell_SoCallbackAction : public SoCallbackAction
{
public:
    PythonQtShell_SoCallbackAction():SoCallbackAction(),_wrapper(nullptr) {};

   ~PythonQtShell_SoCallbackAction() override;

void apply(SoNode*  node) override;
void apply(SoPath*  path) override;
void beginTraversal(SoNode*  node) override;
SoNode*  getCurPathTail() override;
void invalidateState() override;
bool  shouldCompactPathLists() const override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoCallbackAction : public SoCallbackAction
{ public:
inline void promoted_beginTraversal(SoNode*  node) { this->beginTraversal(node); }
inline void py_q_beginTraversal(SoNode*  node) { SoCallbackAction::beginTraversal(node); }
inline SoNode*  py_q_getCurPathTail() { return SoCallbackAction::getCurPathTail(); }
};

class PythonQtWrapper_SoCallbackAction : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Response )
enum Response{
  CONTINUE = SoCallbackAction::CONTINUE,   ABORT = SoCallbackAction::ABORT,   PRUNE = SoCallbackAction::PRUNE};
public slots:
SoCallbackAction* new_SoCallbackAction();
void delete_SoCallbackAction(SoCallbackAction* obj) { delete obj; }
   void py_q_beginTraversal(SoCallbackAction* theWrappedObject, SoNode*  node){  (((PythonQtPublicPromoter_SoCallbackAction*)theWrappedObject)->py_q_beginTraversal(node));}
   void static_SoCallbackAction_enableElement(SoType  t, int  stkIndex);
   SoType  static_SoCallbackAction_getClassTypeId();
   float  getComplexity(SoCallbackAction* theWrappedObject) const;
   SoComplexity::Type  getComplexityType(SoCallbackAction* theWrappedObject) const;
   const SbVec3f*  getCoordinate3(SoCallbackAction* theWrappedObject, int  index) const;
   const SbVec4f*  getCoordinate4(SoCallbackAction* theWrappedObject, int  index) const;
   float  getCreaseAngle(SoCallbackAction* theWrappedObject) const;
   SoNode*  py_q_getCurPathTail(SoCallbackAction* theWrappedObject){  return (((PythonQtPublicPromoter_SoCallbackAction*)theWrappedObject)->py_q_getCurPathTail());}
   SoCallbackAction::Response  getCurrentResponse(SoCallbackAction* theWrappedObject) const;
   SoDrawStyle::Style  getDrawStyle(SoCallbackAction* theWrappedObject) const;
   SoShapeHints::FaceType  getFaceType(SoCallbackAction* theWrappedObject) const;
   float  getFocalDistance(SoCallbackAction* theWrappedObject) const;
   const SbName*  getFontName(SoCallbackAction* theWrappedObject) const;
   float  getFontSize(SoCallbackAction* theWrappedObject) const;
   const SbVec3f*  getLightAttenuation(SoCallbackAction* theWrappedObject) const;
   SoLightModel::Model  getLightModel(SoCallbackAction* theWrappedObject) const;
   float  getLineWidth(SoCallbackAction* theWrappedObject) const;
   void getMaterial(SoCallbackAction* theWrappedObject, SbColor&  ambient, SbColor&  diffuse, SbColor&  specular, SbColor&  emission, float&  shininess, float&  transparency, int  mtlIndex = 0) const;
   SoMaterialBinding::Binding  getMaterialBinding(SoCallbackAction* theWrappedObject) const;
   const SbMatrix*  getModelMatrix(SoCallbackAction* theWrappedObject) const;
   const SbVec3f*  getNormal(SoCallbackAction* theWrappedObject, int  index) const;
   SoNormalBinding::Binding  getNormalBinding(SoCallbackAction* theWrappedObject) const;
   int  getNumCoordinates(SoCallbackAction* theWrappedObject) const;
   int  getNumNormals(SoCallbackAction* theWrappedObject) const;
   int  getNumProfileCoordinates(SoCallbackAction* theWrappedObject) const;
   int  getNumTextureCoordinates(SoCallbackAction* theWrappedObject) const;
   SoPickStyle::Style  getPickStyle(SoCallbackAction* theWrappedObject) const;
   float  getPointSize(SoCallbackAction* theWrappedObject) const;
   const SbVec2f*  getProfileCoordinate2(SoCallbackAction* theWrappedObject, int  index) const;
   const SbVec3f*  getProfileCoordinate3(SoCallbackAction* theWrappedObject, int  index) const;
   const SbMatrix*  getProjectionMatrix(SoCallbackAction* theWrappedObject) const;
   SoShapeHints::ShapeType  getShapeType(SoCallbackAction* theWrappedObject) const;
   int  getSwitch(SoCallbackAction* theWrappedObject) const;
   const SbColor*  getTextureBlendColor(SoCallbackAction* theWrappedObject) const;
   const SbVec2f*  getTextureCoordinate2(SoCallbackAction* theWrappedObject, int  index) const;
   const SbVec4f*  getTextureCoordinate4(SoCallbackAction* theWrappedObject, int  index) const;
   SoTextureCoordinateBinding::Binding  getTextureCoordinateBinding(SoCallbackAction* theWrappedObject) const;
   const unsigned char*  getTextureImage(SoCallbackAction* theWrappedObject, SbVec2s&  size, int&  numComps) const;
   const SbMatrix*  getTextureMatrix(SoCallbackAction* theWrappedObject) const;
   SoTexture2::Model  getTextureModel(SoCallbackAction* theWrappedObject) const;
   SoTexture2::Wrap  getTextureWrapS(SoCallbackAction* theWrappedObject) const;
   SoTexture2::Wrap  getTextureWrapT(SoCallbackAction* theWrappedObject) const;
   SoUnits::Units  getUnits(SoCallbackAction* theWrappedObject) const;
   SoShapeHints::VertexOrdering  getVertexOrdering(SoCallbackAction* theWrappedObject) const;
   const SbViewVolume*  getViewVolume(SoCallbackAction* theWrappedObject) const;
   const SbMatrix*  getViewingMatrix(SoCallbackAction* theWrappedObject) const;
   void invokeLineSegmentCallbacks(SoCallbackAction* theWrappedObject, const SoShape*  shape, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2);
   void invokePointCallbacks(SoCallbackAction* theWrappedObject, const SoShape*  shape, const SoPrimitiveVertex*  v);
   void invokePostCallbacks(SoCallbackAction* theWrappedObject, const SoNode*  node);
   void invokePreCallbacks(SoCallbackAction* theWrappedObject, const SoNode*  node);
   void invokeTriangleCallbacks(SoCallbackAction* theWrappedObject, const SoShape*  shape, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3);
   void setCurrentNode(SoCallbackAction* theWrappedObject, SoNode*  node);
   bool  shouldGeneratePrimitives(SoCallbackAction* theWrappedObject, const SoShape*  shape) const;
};





class PythonQtShell_SoGLRenderAction : public SoGLRenderAction
{
public:
    PythonQtShell_SoGLRenderAction(const SbViewportRegion&  viewportRegion):SoGLRenderAction(viewportRegion),_wrapper(nullptr) {};

   ~PythonQtShell_SoGLRenderAction() override;

void apply(SoNode*  node) override;
void apply(SoPath*  path) override;
void beginTraversal(SoNode*  node) override;
SoNode*  getCurPathTail() override;
void invalidateState() override;
bool  shouldCompactPathLists() const override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoGLRenderAction : public SoGLRenderAction
{ public:
inline void promoted_beginTraversal(SoNode*  node) { this->beginTraversal(node); }
inline void py_q_beginTraversal(SoNode*  node) { SoGLRenderAction::beginTraversal(node); }
inline void py_q_invalidateState() { SoGLRenderAction::invalidateState(); }
};

class PythonQtWrapper_SoGLRenderAction : public QObject
{ Q_OBJECT
public:
Q_ENUMS(AbortCode TransparencyType )
enum AbortCode{
  CONTINUE = SoGLRenderAction::CONTINUE,   ABORT = SoGLRenderAction::ABORT,   PRUNE = SoGLRenderAction::PRUNE,   DELAY = SoGLRenderAction::DELAY};
enum TransparencyType{
  SCREEN_DOOR = SoGLRenderAction::SCREEN_DOOR,   ADD = SoGLRenderAction::ADD,   DELAYED_ADD = SoGLRenderAction::DELAYED_ADD,   SORTED_OBJECT_ADD = SoGLRenderAction::SORTED_OBJECT_ADD,   BLEND = SoGLRenderAction::BLEND,   DELAYED_BLEND = SoGLRenderAction::DELAYED_BLEND,   SORTED_OBJECT_BLEND = SoGLRenderAction::SORTED_OBJECT_BLEND};
public slots:
SoGLRenderAction* new_SoGLRenderAction(const SbViewportRegion&  viewportRegion);
void delete_SoGLRenderAction(SoGLRenderAction* obj) { delete obj; }
   bool  abortNow(SoGLRenderAction* theWrappedObject);
   void addDelayedPath(SoGLRenderAction* theWrappedObject, SoPath*  path);
   void py_q_beginTraversal(SoGLRenderAction* theWrappedObject, SoNode*  node){  (((PythonQtPublicPromoter_SoGLRenderAction*)theWrappedObject)->py_q_beginTraversal(node));}
   void static_SoGLRenderAction_enableElement(SoType  t, int  stkIndex);
   bool  getAllowDelayedPaths(SoGLRenderAction* theWrappedObject);
   unsigned int  getCacheContext(SoGLRenderAction* theWrappedObject) const;
   SoType  static_SoGLRenderAction_getClassTypeId();
   int  getCullTestResults(SoGLRenderAction* theWrappedObject);
   int  getCurPass(SoGLRenderAction* theWrappedObject) const;
   int  getNumPasses(SoGLRenderAction* theWrappedObject) const;
   SoGLRenderAction::TransparencyType  getTransparencyType(SoGLRenderAction* theWrappedObject) const;
   void getUpdateArea(SoGLRenderAction* theWrappedObject, SbVec2f&  origin, SbVec2f&  size) const;
   const SbViewportRegion*  getViewportRegion(SoGLRenderAction* theWrappedObject) const;
   bool  handleTransparency(SoGLRenderAction* theWrappedObject, bool  isTransparent = 0);
   void py_q_invalidateState(SoGLRenderAction* theWrappedObject){  (((PythonQtPublicPromoter_SoGLRenderAction*)theWrappedObject)->py_q_invalidateState());}
   bool  isDelaying(SoGLRenderAction* theWrappedObject) const;
   bool  isPassUpdate(SoGLRenderAction* theWrappedObject) const;
   bool  isRenderingDelayedPaths(SoGLRenderAction* theWrappedObject) const;
   bool  isSmoothing(SoGLRenderAction* theWrappedObject) const;
   bool  setAllowDelayedPath(SoGLRenderAction* theWrappedObject, bool  flag);
   void setCacheContext(SoGLRenderAction* theWrappedObject, unsigned int  context);
   void setCullTestResults(SoGLRenderAction* theWrappedObject, int  b);
   void setNumPasses(SoGLRenderAction* theWrappedObject, int  num);
   void setPassUpdate(SoGLRenderAction* theWrappedObject, bool  flag);
   void setSmoothing(SoGLRenderAction* theWrappedObject, bool  smooth);
   void setTransparencyType(SoGLRenderAction* theWrappedObject, SoGLRenderAction::TransparencyType  type);
   void setUpdateArea(SoGLRenderAction* theWrappedObject, const SbVec2f&  origin, const SbVec2f&  size);
   void setViewportRegion(SoGLRenderAction* theWrappedObject, const SbViewportRegion&  newRegion);
};





class PythonQtShell_SoGetBoundingBoxAction : public SoGetBoundingBoxAction
{
public:
    PythonQtShell_SoGetBoundingBoxAction(const SbViewportRegion&  viewportRegion):SoGetBoundingBoxAction(viewportRegion),_wrapper(nullptr) {};

   ~PythonQtShell_SoGetBoundingBoxAction() override;

void apply(SoNode*  node) override;
void apply(SoPath*  path) override;
void beginTraversal(SoNode*  node) override;
SoNode*  getCurPathTail() override;
void invalidateState() override;
bool  shouldCompactPathLists() const override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoGetBoundingBoxAction : public SoGetBoundingBoxAction
{ public:
inline void promoted_beginTraversal(SoNode*  node) { this->beginTraversal(node); }
inline void py_q_beginTraversal(SoNode*  node) { SoGetBoundingBoxAction::beginTraversal(node); }
};

class PythonQtWrapper_SoGetBoundingBoxAction : public QObject
{ Q_OBJECT
public:
Q_ENUMS(ResetType )
enum ResetType{
  TRANSFORM = SoGetBoundingBoxAction::TRANSFORM,   BBOX = SoGetBoundingBoxAction::BBOX,   ALL = SoGetBoundingBoxAction::ALL};
public slots:
SoGetBoundingBoxAction* new_SoGetBoundingBoxAction(const SbViewportRegion&  viewportRegion);
void delete_SoGetBoundingBoxAction(SoGetBoundingBoxAction* obj) { delete obj; }
   void py_q_beginTraversal(SoGetBoundingBoxAction* theWrappedObject, SoNode*  node){  (((PythonQtPublicPromoter_SoGetBoundingBoxAction*)theWrappedObject)->py_q_beginTraversal(node));}
   void checkResetAfter(SoGetBoundingBoxAction* theWrappedObject);
   void checkResetBefore(SoGetBoundingBoxAction* theWrappedObject);
   void static_SoGetBoundingBoxAction_enableElement(SoType  t, int  stkIndex);
   void extendBy(SoGetBoundingBoxAction* theWrappedObject, const SbBox3f&  box);
   void extendBy(SoGetBoundingBoxAction* theWrappedObject, const SbXfBox3f&  box);
   SbBox3f  getBoundingBox(SoGetBoundingBoxAction* theWrappedObject) const;
   const SbVec3f*  getCenter(SoGetBoundingBoxAction* theWrappedObject) const;
   SoType  static_SoGetBoundingBoxAction_getClassTypeId();
   const SoPath*  getResetPath(SoGetBoundingBoxAction* theWrappedObject) const;
   const SbViewportRegion*  getViewportRegion(SoGetBoundingBoxAction* theWrappedObject) const;
   SoGetBoundingBoxAction::ResetType  getWhatReset(SoGetBoundingBoxAction* theWrappedObject) const;
   SbXfBox3f*  getXfBoundingBox(SoGetBoundingBoxAction* theWrappedObject);
   bool  isCenterSet(SoGetBoundingBoxAction* theWrappedObject) const;
   bool  isInCameraSpace(SoGetBoundingBoxAction* theWrappedObject) const;
   bool  isResetBefore(SoGetBoundingBoxAction* theWrappedObject) const;
   bool  isResetPath(SoGetBoundingBoxAction* theWrappedObject) const;
   void resetCenter(SoGetBoundingBoxAction* theWrappedObject);
   void setCenter(SoGetBoundingBoxAction* theWrappedObject, const SbVec3f&  center, bool  transformCenter);
   void setInCameraSpace(SoGetBoundingBoxAction* theWrappedObject, bool  flag);
   void setResetPath(SoGetBoundingBoxAction* theWrappedObject, const SoPath*  path, bool  resetBefore = 1, SoGetBoundingBoxAction::ResetType  what = SoGetBoundingBoxAction::ALL);
   void setViewportRegion(SoGetBoundingBoxAction* theWrappedObject, const SbViewportRegion&  newRegion);
};





class PythonQtShell_SoGetMatrixAction : public SoGetMatrixAction
{
public:
    PythonQtShell_SoGetMatrixAction(const SbViewportRegion&  newRegion):SoGetMatrixAction(newRegion),_wrapper(nullptr) {};

   ~PythonQtShell_SoGetMatrixAction() override;

void apply(SoNode*  node) override;
void apply(SoPath*  path) override;
void beginTraversal(SoNode*  node) override;
SoNode*  getCurPathTail() override;
void invalidateState() override;
bool  shouldCompactPathLists() const override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoGetMatrixAction : public SoGetMatrixAction
{ public:
inline void promoted_beginTraversal(SoNode*  node) { this->beginTraversal(node); }
inline void py_q_beginTraversal(SoNode*  node) { SoGetMatrixAction::beginTraversal(node); }
};

class PythonQtWrapper_SoGetMatrixAction : public QObject
{ Q_OBJECT
public:
public slots:
SoGetMatrixAction* new_SoGetMatrixAction(const SbViewportRegion&  newRegion);
void delete_SoGetMatrixAction(SoGetMatrixAction* obj) { delete obj; }
   void py_q_beginTraversal(SoGetMatrixAction* theWrappedObject, SoNode*  node){  (((PythonQtPublicPromoter_SoGetMatrixAction*)theWrappedObject)->py_q_beginTraversal(node));}
   void static_SoGetMatrixAction_enableElement(SoType  t, int  stkIndex);
   SoType  static_SoGetMatrixAction_getClassTypeId();
   SbMatrix*  getInverse(SoGetMatrixAction* theWrappedObject);
   SbMatrix*  getMatrix(SoGetMatrixAction* theWrappedObject);
   SbMatrix*  getTextureInverse(SoGetMatrixAction* theWrappedObject);
   SbMatrix*  getTextureMatrix(SoGetMatrixAction* theWrappedObject);
   const SbViewportRegion*  getViewportRegion(SoGetMatrixAction* theWrappedObject) const;
   void setViewportRegion(SoGetMatrixAction* theWrappedObject, const SbViewportRegion&  newRegion);
};





class PythonQtShell_SoHandleEventAction : public SoHandleEventAction
{
public:
    PythonQtShell_SoHandleEventAction(const SbViewportRegion&  viewportRegion):SoHandleEventAction(viewportRegion),_wrapper(nullptr) {};

   ~PythonQtShell_SoHandleEventAction() override;

void apply(SoNode*  node) override;
void apply(SoPath*  path) override;
void beginTraversal(SoNode*  node) override;
SoNode*  getCurPathTail() override;
void invalidateState() override;
bool  shouldCompactPathLists() const override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoHandleEventAction : public SoHandleEventAction
{ public:
inline void promoted_beginTraversal(SoNode*  node) { this->beginTraversal(node); }
inline void py_q_beginTraversal(SoNode*  node) { SoHandleEventAction::beginTraversal(node); }
};

class PythonQtWrapper_SoHandleEventAction : public QObject
{ Q_OBJECT
public:
public slots:
SoHandleEventAction* new_SoHandleEventAction(const SbViewportRegion&  viewportRegion);
void delete_SoHandleEventAction(SoHandleEventAction* obj) { delete obj; }
   void py_q_beginTraversal(SoHandleEventAction* theWrappedObject, SoNode*  node){  (((PythonQtPublicPromoter_SoHandleEventAction*)theWrappedObject)->py_q_beginTraversal(node));}
   void static_SoHandleEventAction_enableElement(SoType  t, int  stkIndex);
   SoType  static_SoHandleEventAction_getClassTypeId();
   const SoEvent*  getEvent(SoHandleEventAction* theWrappedObject) const;
   SoNode*  getGrabber(SoHandleEventAction* theWrappedObject) const;
   SoNode*  getPickRoot(SoHandleEventAction* theWrappedObject) const;
   const SoPickedPoint*  getPickedPoint(SoHandleEventAction* theWrappedObject);
   const SbViewportRegion*  getViewportRegion(SoHandleEventAction* theWrappedObject) const;
   bool  isHandled(SoHandleEventAction* theWrappedObject) const;
   void releaseGrabber(SoHandleEventAction* theWrappedObject);
   void setEvent(SoHandleEventAction* theWrappedObject, const SoEvent*  ev);
   void setGrabber(SoHandleEventAction* theWrappedObject, SoNode*  node);
   void setHandled(SoHandleEventAction* theWrappedObject);
   void setPickRadius(SoHandleEventAction* theWrappedObject, float  radiusInPixels);
   void setPickRoot(SoHandleEventAction* theWrappedObject, SoNode*  node);
   void setViewportRegion(SoHandleEventAction* theWrappedObject, const SbViewportRegion&  newRegion);
};





class PythonQtShell_SoPickAction : public SoPickAction
{
public:
    PythonQtShell_SoPickAction(const SbViewportRegion&  viewportRegion):SoPickAction(viewportRegion),_wrapper(nullptr) {};

   ~PythonQtShell_SoPickAction() override;

void apply(SoNode*  node) override;
void apply(SoPath*  path) override;
void beginTraversal(SoNode*  node) override;
SoNode*  getCurPathTail() override;
void invalidateState() override;
bool  shouldCompactPathLists() const override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoPickAction : public SoPickAction
{ public:
inline void promoted_beginTraversal(SoNode*  node) { this->beginTraversal(node); }
inline void py_q_beginTraversal(SoNode*  node) { SoPickAction::beginTraversal(node); }
};

class PythonQtWrapper_SoPickAction : public QObject
{ Q_OBJECT
public:
public slots:
SoPickAction* new_SoPickAction(const SbViewportRegion&  viewportRegion);
   void py_q_beginTraversal(SoPickAction* theWrappedObject, SoNode*  node){  (((PythonQtPublicPromoter_SoPickAction*)theWrappedObject)->py_q_beginTraversal(node));}
   void enableCulling(SoPickAction* theWrappedObject, bool  flag);
   void static_SoPickAction_enableElement(SoType  t, int  stkIndex);
   SoType  static_SoPickAction_getClassTypeId();
   const SbViewportRegion*  getViewportRegion(SoPickAction* theWrappedObject) const;
   bool  isCullingEnabled(SoPickAction* theWrappedObject) const;
   void setViewportRegion(SoPickAction* theWrappedObject, const SbViewportRegion&  newRegion);
};





class PythonQtShell_SoRayPickAction : public SoRayPickAction
{
public:
    PythonQtShell_SoRayPickAction(const SbViewportRegion&  viewportRegion):SoRayPickAction(viewportRegion),_wrapper(nullptr) {};

   ~PythonQtShell_SoRayPickAction() override;

void apply(SoNode*  node) override;
void apply(SoPath*  path) override;
void beginTraversal(SoNode*  node) override;
SoNode*  getCurPathTail() override;
void invalidateState() override;
bool  shouldCompactPathLists() const override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoRayPickAction : public SoRayPickAction
{ public:
inline void promoted_beginTraversal(SoNode*  node) { this->beginTraversal(node); }
inline void py_q_beginTraversal(SoNode*  node) { SoRayPickAction::beginTraversal(node); }
};

class PythonQtWrapper_SoRayPickAction : public QObject
{ Q_OBJECT
public:
public slots:
SoRayPickAction* new_SoRayPickAction(const SbViewportRegion&  viewportRegion);
void delete_SoRayPickAction(SoRayPickAction* obj) { delete obj; }
   SoPickedPoint*  addIntersection(SoRayPickAction* theWrappedObject, const SbVec3f&  objectSpacePoint);
   void py_q_beginTraversal(SoRayPickAction* theWrappedObject, SoNode*  node){  (((PythonQtPublicPromoter_SoRayPickAction*)theWrappedObject)->py_q_beginTraversal(node));}
   void computeWorldSpaceRay(SoRayPickAction* theWrappedObject);
   void static_SoRayPickAction_enableElement(SoType  t, int  stkIndex);
   SoType  static_SoRayPickAction_getClassTypeId();
   const SbLine*  getLine(SoRayPickAction* theWrappedObject) const;
   SoPickedPoint*  getPickedPoint(SoRayPickAction* theWrappedObject, int  index = 0) const;
   const SbViewVolume*  getViewVolume(SoRayPickAction* theWrappedObject) const;
   bool  hasWorldSpaceRay(SoRayPickAction* theWrappedObject) const;
   bool  intersect(SoRayPickAction* theWrappedObject, const SbBox3f&  box, bool  useFullViewVolume = 1);
   bool  intersect(SoRayPickAction* theWrappedObject, const SbVec3f&  point) const;
   bool  intersect(SoRayPickAction* theWrappedObject, const SbVec3f&  v0, const SbVec3f&  v1, SbVec3f&  intersection) const;
   bool  intersect(SoRayPickAction* theWrappedObject, const SbVec3f&  v0, const SbVec3f&  v1, const SbVec3f&  v2, SbVec3f&  intersection, SbVec3f&  barycentric, bool&  front) const;
   bool  isBetweenPlanes(SoRayPickAction* theWrappedObject, const SbVec3f&  intersection) const;
   bool  isPickAll(SoRayPickAction* theWrappedObject) const;
   void setNormalizedPoint(SoRayPickAction* theWrappedObject, const SbVec2f&  normPoint);
   void setObjectSpace(SoRayPickAction* theWrappedObject);
   void setObjectSpace(SoRayPickAction* theWrappedObject, const SbMatrix&  matrix);
   void setPickAll(SoRayPickAction* theWrappedObject, bool  flag);
   void setPoint(SoRayPickAction* theWrappedObject, const SbVec2s&  viewportPoint);
   void setRadius(SoRayPickAction* theWrappedObject, float  radiusInPixels);
   void setRay(SoRayPickAction* theWrappedObject, const SbVec3f&  start, const SbVec3f&  direction, float  nearDistance = -1.0, float  farDistance = -1.0);
};





class PythonQtShell_SoSearchAction : public SoSearchAction
{
public:
    PythonQtShell_SoSearchAction():SoSearchAction(),_wrapper(nullptr) {};

   ~PythonQtShell_SoSearchAction() override;

void apply(SoNode*  node) override;
void apply(SoPath*  path) override;
void beginTraversal(SoNode*  node) override;
SoNode*  getCurPathTail() override;
void invalidateState() override;
bool  shouldCompactPathLists() const override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoSearchAction : public SoSearchAction
{ public:
inline void promoted_beginTraversal(SoNode*  node) { this->beginTraversal(node); }
inline void py_q_beginTraversal(SoNode*  node) { SoSearchAction::beginTraversal(node); }
};

class PythonQtWrapper_SoSearchAction : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Interest LookFor )
enum Interest{
  FIRST = SoSearchAction::FIRST,   LAST = SoSearchAction::LAST,   ALL = SoSearchAction::ALL};
enum LookFor{
  NODE = SoSearchAction::NODE,   TYPE = SoSearchAction::TYPE,   NAME = SoSearchAction::NAME};
public slots:
SoSearchAction* new_SoSearchAction();
void delete_SoSearchAction(SoSearchAction* obj) { delete obj; }
   void addPath(SoSearchAction* theWrappedObject, SoPath*  path);
   void py_q_beginTraversal(SoSearchAction* theWrappedObject, SoNode*  node){  (((PythonQtPublicPromoter_SoSearchAction*)theWrappedObject)->py_q_beginTraversal(node));}
   void static_SoSearchAction_enableElement(SoType  t, int  stkIndex);
   SoType  static_SoSearchAction_getClassTypeId();
   int  getFind(SoSearchAction* theWrappedObject);
   SoSearchAction::Interest  getInterest(SoSearchAction* theWrappedObject) const;
   const SbName*  getName(SoSearchAction* theWrappedObject) const;
   SoNode*  getNode(SoSearchAction* theWrappedObject) const;
   SoPath*  getPath(SoSearchAction* theWrappedObject) const;
   bool  isFound(SoSearchAction* theWrappedObject) const;
   bool  isSearchingAll(SoSearchAction* theWrappedObject) const;
   void reset(SoSearchAction* theWrappedObject);
   void setFind(SoSearchAction* theWrappedObject, int  what);
   void setFound(SoSearchAction* theWrappedObject);
   void setInterest(SoSearchAction* theWrappedObject, SoSearchAction::Interest  i);
   void setName(SoSearchAction* theWrappedObject, const SbName&  n);
   void setNode(SoSearchAction* theWrappedObject, SoNode*  n);
   void setSearchingAll(SoSearchAction* theWrappedObject, bool  flag);
   void setType(SoSearchAction* theWrappedObject, SoType  t, bool  derivedIsOk = 1);

   QList<SoPath*> getPaths(SoSearchAction* action) {
     QList<SoPath*> result;
     SoPathList& paths = action->getPaths();
     for (int i = 0; i< paths.getLength(); i++) {
       result << paths[i];
     }
     return result;
   }

};





class PythonQtShell_SoWriteAction : public SoWriteAction
{
public:
    PythonQtShell_SoWriteAction():SoWriteAction(),_wrapper(nullptr) {};
    PythonQtShell_SoWriteAction(SoOutput*  out):SoWriteAction(out),_wrapper(nullptr) {};

   ~PythonQtShell_SoWriteAction() override;

void apply(SoNode*  node) override;
void apply(SoPath*  path) override;
void beginTraversal(SoNode*  node) override;
SoNode*  getCurPathTail() override;
void invalidateState() override;
bool  shouldCompactPathLists() const override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoWriteAction : public SoWriteAction
{ public:
inline void promoted_beginTraversal(SoNode*  node) { this->beginTraversal(node); }
inline bool  promoted_shouldCompactPathLists() const { return this->shouldCompactPathLists(); }
inline void py_q_beginTraversal(SoNode*  node) { SoWriteAction::beginTraversal(node); }
inline bool  py_q_shouldCompactPathLists() const { return SoWriteAction::shouldCompactPathLists(); }
};

class PythonQtWrapper_SoWriteAction : public QObject
{ Q_OBJECT
public:
public slots:
SoWriteAction* new_SoWriteAction();
SoWriteAction* new_SoWriteAction(SoOutput*  out);
void delete_SoWriteAction(SoWriteAction* obj) { delete obj; }
   void py_q_beginTraversal(SoWriteAction* theWrappedObject, SoNode*  node){  (((PythonQtPublicPromoter_SoWriteAction*)theWrappedObject)->py_q_beginTraversal(node));}
   void continueToApply(SoWriteAction* theWrappedObject, SoNode*  node);
   void continueToApply(SoWriteAction* theWrappedObject, SoPath*  path);
   void static_SoWriteAction_enableElement(SoType  t, int  stkIndex);
   SoType  static_SoWriteAction_getClassTypeId();
   SoOutput*  getOutput(SoWriteAction* theWrappedObject) const;
   bool  py_q_shouldCompactPathLists(SoWriteAction* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoWriteAction*)theWrappedObject)->py_q_shouldCompactPathLists());}
};


