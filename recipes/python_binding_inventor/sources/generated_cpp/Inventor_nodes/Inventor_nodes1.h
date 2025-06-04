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
#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SoInput.h>
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
#include <Inventor/details/SoDetail.h>
#include <Inventor/details/SoFaceDetail.h>
#include <Inventor/elements/SoShapeStyleElement.h>
#include <Inventor/fields/SoField.h>
#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/misc/SoBase.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/nodes/SoIndexedTriangleStripSet.h>
#include <Inventor/nodes/SoInfo.h>
#include <Inventor/nodes/SoLOD.h>
#include <Inventor/nodes/SoLabel.h>
#include <Inventor/nodes/SoLevelOfDetail.h>
#include <Inventor/nodes/SoLight.h>
#include <Inventor/nodes/SoLightModel.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoLinearProfile.h>
#include <Inventor/nodes/SoLocateHighlight.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoMaterialBinding.h>
#include <Inventor/nodes/SoMatrixTransform.h>
#include <Inventor/nodes/SoMultipleCopy.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoNonIndexedShape.h>
#include <Inventor/nodes/SoNormal.h>
#include <Inventor/nodes/SoNormalBinding.h>
#include <Inventor/nodes/SoNurbsCurve.h>
#include <Inventor/nodes/SoNurbsProfile.h>
#include <Inventor/nodes/SoNurbsSurface.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoPackedColor.h>
#include <Inventor/nodes/SoPathSwitch.h>
#include <Inventor/nodes/SoPendulum.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoPickStyle.h>
#include <Inventor/nodes/SoPointLight.h>
#include <Inventor/nodes/SoPointSet.h>
#include <Inventor/nodes/SoPolygonOffset.h>
#include <Inventor/nodes/SoVertexProperty.h>
#include <Inventor/sensors/SoSensor.h>
#include <stdexcept>



class PythonQtShell_SoIndexedTriangleStripSet : public SoIndexedTriangleStripSet
{
public:
    PythonQtShell_SoIndexedTriangleStripSet():SoIndexedTriangleStripSet(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoIndexedTriangleStripSet() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) override;
SoDetail*  createLineSegmentDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, SoPickedPoint*  pp) override;
SoDetail*  createPointDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v, SoPickedPoint*  pp) override;
SoDetail*  createTriangleDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp) override;
void doAction(SoAction*  action) override;
void generatePrimitives(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
bool  shouldGLRender(SoGLRenderAction*  action) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoIndexedTriangleStripSet : public SoIndexedTriangleStripSet
{ public:
inline SoDetail*  promoted_createTriangleDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp) { return this->createTriangleDetail(action, v1, v2, v3, pp); }
inline void promoted_generatePrimitives(SoAction*  action) { this->generatePrimitives(action); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoIndexedTriangleStripSet::GLRender(action); }
inline SoDetail*  py_q_createTriangleDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp) { return SoIndexedTriangleStripSet::createTriangleDetail(action, v1, v2, v3, pp); }
inline void py_q_generatePrimitives(SoAction*  action) { SoIndexedTriangleStripSet::generatePrimitives(action); }
};

class PythonQtWrapper_SoIndexedTriangleStripSet : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Binding )
enum Binding{
  OVERALL = SoIndexedTriangleStripSet::OVERALL,   PER_STRIP = SoIndexedTriangleStripSet::PER_STRIP,   PER_STRIP_INDEXED = SoIndexedTriangleStripSet::PER_STRIP_INDEXED,   PER_TRIANGLE = SoIndexedTriangleStripSet::PER_TRIANGLE,   PER_TRIANGLE_INDEXED = SoIndexedTriangleStripSet::PER_TRIANGLE_INDEXED,   PER_VERTEX = SoIndexedTriangleStripSet::PER_VERTEX,   PER_VERTEX_INDEXED = SoIndexedTriangleStripSet::PER_VERTEX_INDEXED};
public Q_SLOTS:
SoIndexedTriangleStripSet* new_SoIndexedTriangleStripSet();
   void py_q_GLRender(SoIndexedTriangleStripSet* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoIndexedTriangleStripSet*)theWrappedObject)->py_q_GLRender(action));}
   SoDetail*  py_q_createTriangleDetail(SoIndexedTriangleStripSet* theWrappedObject, SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp){  return (((PythonQtPublicPromoter_SoIndexedTriangleStripSet*)theWrappedObject)->py_q_createTriangleDetail(action, v1, v2, v3, pp));}
   void py_q_generatePrimitives(SoIndexedTriangleStripSet* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoIndexedTriangleStripSet*)theWrappedObject)->py_q_generatePrimitives(action));}
   SoType  static_SoIndexedTriangleStripSet_getClassTypeId();
};





class PythonQtShell_SoInfo : public SoInfo
{
public:
    PythonQtShell_SoInfo():SoInfo(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoInfo() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void doAction(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoInfo : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoInfo* new_SoInfo();
   SoType  static_SoInfo_getClassTypeId();
SoSFString*  py_get_string(SoInfo* theWrappedObject){ return &theWrappedObject->string; }
};





class PythonQtShell_SoLOD : public SoLOD
{
public:
    PythonQtShell_SoLOD():SoLOD(),_wrapper(nullptr) {_type = getClassTypeId();
};
    PythonQtShell_SoLOD(int  nChildren):SoLOD(nChildren),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoLOD() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void doAction(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
bool  readChildren(SoInput*  in) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
void startNotify() override;
int  whichToTraverse(SoAction*  arg__1) override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoLOD : public SoLOD
{ public:
inline int  promoted_whichToTraverse(SoAction*  arg__1) { return this->whichToTraverse(arg__1); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoLOD::GLRender(action); }
inline void py_q_GLRenderBelowPath(SoGLRenderAction*  action) { SoLOD::GLRenderBelowPath(action); }
inline void py_q_GLRenderInPath(SoGLRenderAction*  action) { SoLOD::GLRenderInPath(action); }
inline void py_q_GLRenderOffPath(SoGLRenderAction*  action) { SoLOD::GLRenderOffPath(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoLOD::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoLOD::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoLOD::getBoundingBox(action); }
inline void py_q_rayPick(SoRayPickAction*  action) { SoLOD::rayPick(action); }
inline int  py_q_whichToTraverse(SoAction*  arg__1) { return SoLOD::whichToTraverse(arg__1); }
};

class PythonQtWrapper_SoLOD : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoLOD* new_SoLOD();
SoLOD* new_SoLOD(int  nChildren);
   void py_q_GLRender(SoLOD* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoLOD*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_GLRenderBelowPath(SoLOD* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoLOD*)theWrappedObject)->py_q_GLRenderBelowPath(action));}
   void py_q_GLRenderInPath(SoLOD* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoLOD*)theWrappedObject)->py_q_GLRenderInPath(action));}
   void py_q_GLRenderOffPath(SoLOD* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoLOD*)theWrappedObject)->py_q_GLRenderOffPath(action));}
   void py_q_callback(SoLOD* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoLOD*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoLOD* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoLOD*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoLOD* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoLOD*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoLOD_getClassTypeId();
   void py_q_rayPick(SoLOD* theWrappedObject, SoRayPickAction*  action){  (((PythonQtPublicPromoter_SoLOD*)theWrappedObject)->py_q_rayPick(action));}
   int  whichToTraverse(SoLOD* theWrappedObject, SoAction*  arg__1);
   int  py_q_whichToTraverse(SoLOD* theWrappedObject, SoAction*  arg__1){  return (((PythonQtPublicPromoter_SoLOD*)theWrappedObject)->py_q_whichToTraverse(arg__1));}
SoSFVec3f*  py_get_center(SoLOD* theWrappedObject){ return &theWrappedObject->center; }
SoMFFloat*  py_get_range(SoLOD* theWrappedObject){ return &theWrappedObject->range; }
};





class PythonQtShell_SoLabel : public SoLabel
{
public:
    PythonQtShell_SoLabel():SoLabel(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoLabel() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void doAction(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoLabel : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoLabel* new_SoLabel();
   SoType  static_SoLabel_getClassTypeId();
SoSFName*  py_get_label(SoLabel* theWrappedObject){ return &theWrappedObject->label; }
};





class PythonQtShell_SoLevelOfDetail : public SoLevelOfDetail
{
public:
    PythonQtShell_SoLevelOfDetail():SoLevelOfDetail(),_wrapper(nullptr) {_type = getClassTypeId();
};
    PythonQtShell_SoLevelOfDetail(int  nChildren):SoLevelOfDetail(nChildren),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoLevelOfDetail() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void doAction(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
bool  readChildren(SoInput*  in) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoLevelOfDetail : public SoLevelOfDetail
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoLevelOfDetail::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoLevelOfDetail::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoLevelOfDetail::doAction(action); }
inline void py_q_rayPick(SoRayPickAction*  action) { SoLevelOfDetail::rayPick(action); }
};

class PythonQtWrapper_SoLevelOfDetail : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoLevelOfDetail* new_SoLevelOfDetail();
SoLevelOfDetail* new_SoLevelOfDetail(int  nChildren);
   void py_q_GLRender(SoLevelOfDetail* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoLevelOfDetail*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoLevelOfDetail* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoLevelOfDetail*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoLevelOfDetail* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoLevelOfDetail*)theWrappedObject)->py_q_doAction(action));}
   SoType  static_SoLevelOfDetail_getClassTypeId();
   void py_q_rayPick(SoLevelOfDetail* theWrappedObject, SoRayPickAction*  action){  (((PythonQtPublicPromoter_SoLevelOfDetail*)theWrappedObject)->py_q_rayPick(action));}
SoMFFloat*  py_get_screenArea(SoLevelOfDetail* theWrappedObject){ return &theWrappedObject->screenArea; }
};





class PythonQtShell_SoLight : public SoLight
{
public:
    PythonQtShell_SoLight():SoLight(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoLight() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void doAction(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoLight : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoLight* new_SoLight();
   SoType  static_SoLight_getClassTypeId();
SoSFColor*  py_get_color(SoLight* theWrappedObject){ return &theWrappedObject->color; }
SoSFFloat*  py_get_intensity(SoLight* theWrappedObject){ return &theWrappedObject->intensity; }
SoSFBool*  py_get_on(SoLight* theWrappedObject){ return &theWrappedObject->on; }
};





class PythonQtShell_SoLightModel : public SoLightModel
{
public:
    PythonQtShell_SoLightModel():SoLightModel(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoLightModel() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void doAction(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoLightModel : public SoLightModel
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoLightModel::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoLightModel::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoLightModel::doAction(action); }
};

class PythonQtWrapper_SoLightModel : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Model )
enum Model{
  BASE_COLOR = SoLightModel::BASE_COLOR,   PHONG = SoLightModel::PHONG};
public Q_SLOTS:
SoLightModel* new_SoLightModel();
   void py_q_GLRender(SoLightModel* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoLightModel*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoLightModel* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoLightModel*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoLightModel* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoLightModel*)theWrappedObject)->py_q_doAction(action));}
   SoType  static_SoLightModel_getClassTypeId();
SoSFEnum*  py_get_model(SoLightModel* theWrappedObject){ return &theWrappedObject->model; }
};





class PythonQtShell_SoLineSet : public SoLineSet
{
public:
    PythonQtShell_SoLineSet():SoLineSet(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoLineSet() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) override;
SoDetail*  createLineSegmentDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, SoPickedPoint*  pp) override;
SoDetail*  createPointDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v, SoPickedPoint*  pp) override;
SoDetail*  createTriangleDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp) override;
void doAction(SoAction*  action) override;
void generatePrimitives(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
bool  shouldGLRender(SoGLRenderAction*  action) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoLineSet : public SoLineSet
{ public:
inline void promoted_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { this->computeBBox(action, box, center); }
inline SoDetail*  promoted_createLineSegmentDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, SoPickedPoint*  pp) { return this->createLineSegmentDetail(action, v1, v2, pp); }
inline void promoted_generatePrimitives(SoAction*  action) { this->generatePrimitives(action); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoLineSet::GLRender(action); }
inline void py_q_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { SoLineSet::computeBBox(action, box, center); }
inline SoDetail*  py_q_createLineSegmentDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, SoPickedPoint*  pp) { return SoLineSet::createLineSegmentDetail(action, v1, v2, pp); }
inline void py_q_generatePrimitives(SoAction*  action) { SoLineSet::generatePrimitives(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoLineSet::getBoundingBox(action); }
};

class PythonQtWrapper_SoLineSet : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Binding )
enum Binding{
  OVERALL = SoLineSet::OVERALL,   PER_LINE = SoLineSet::PER_LINE,   PER_SEGMENT = SoLineSet::PER_SEGMENT,   PER_VERTEX = SoLineSet::PER_VERTEX};
public Q_SLOTS:
SoLineSet* new_SoLineSet();
   void py_q_GLRender(SoLineSet* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoLineSet*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_computeBBox(SoLineSet* theWrappedObject, SoAction*  action, SbBox3f&  box, SbVec3f&  center){  (((PythonQtPublicPromoter_SoLineSet*)theWrappedObject)->py_q_computeBBox(action, box, center));}
   SoDetail*  py_q_createLineSegmentDetail(SoLineSet* theWrappedObject, SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, SoPickedPoint*  pp){  return (((PythonQtPublicPromoter_SoLineSet*)theWrappedObject)->py_q_createLineSegmentDetail(action, v1, v2, pp));}
   void py_q_generatePrimitives(SoLineSet* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoLineSet*)theWrappedObject)->py_q_generatePrimitives(action));}
   void py_q_getBoundingBox(SoLineSet* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoLineSet*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoLineSet_getClassTypeId();
SoSFBool*  py_get_independentLines(SoLineSet* theWrappedObject){ return &theWrappedObject->independentLines; }
SoMFInt32*  py_get_numVertices(SoLineSet* theWrappedObject){ return &theWrappedObject->numVertices; }
SoSFBool*  py_get_sendAdjacency(SoLineSet* theWrappedObject){ return &theWrappedObject->sendAdjacency; }
};





class PythonQtShell_SoLinearProfile : public SoLinearProfile
{
public:
    PythonQtShell_SoLinearProfile():SoLinearProfile(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoLinearProfile() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void doAction(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void getTrimCurve(SoState*  state, int&  numPoints, float*&  points, int&  floatsPerVec, int&  numKnots, float*&  knotVector) override;
void getVertices(SoState*  state, int&  nVertices, SbVec2f*&  vertices) override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoLinearProfile : public SoLinearProfile
{ public:
inline void py_q_getTrimCurve(SoState*  state, int&  numPoints, float*&  points, int&  floatsPerVec, int&  numKnots, float*&  knotVector) { SoLinearProfile::getTrimCurve(state, numPoints, points, floatsPerVec, numKnots, knotVector); }
inline void py_q_getVertices(SoState*  state, int&  nVertices, SbVec2f*&  vertices) { SoLinearProfile::getVertices(state, nVertices, vertices); }
};

class PythonQtWrapper_SoLinearProfile : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoLinearProfile* new_SoLinearProfile();
   SoType  static_SoLinearProfile_getClassTypeId();
   void py_q_getTrimCurve(SoLinearProfile* theWrappedObject, SoState*  state, int&  numPoints, float*&  points, int&  floatsPerVec, int&  numKnots, float*&  knotVector){  (((PythonQtPublicPromoter_SoLinearProfile*)theWrappedObject)->py_q_getTrimCurve(state, numPoints, points, floatsPerVec, numKnots, knotVector));}
   void py_q_getVertices(SoLinearProfile* theWrappedObject, SoState*  state, int&  nVertices, SbVec2f*&  vertices){  (((PythonQtPublicPromoter_SoLinearProfile*)theWrappedObject)->py_q_getVertices(state, nVertices, vertices));}
};





class PythonQtShell_SoLocateHighlight : public SoLocateHighlight
{
public:
    PythonQtShell_SoLocateHighlight():SoLocateHighlight(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoLocateHighlight() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void doAction(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
bool  readChildren(SoInput*  in) override;
void redrawHighlighted(SoAction*  act, bool  flag) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoLocateHighlight : public SoLocateHighlight
{ public:
inline void promoted_redrawHighlighted(SoAction*  act, bool  flag) { this->redrawHighlighted(act, flag); }
inline void py_q_GLRenderBelowPath(SoGLRenderAction*  action) { SoLocateHighlight::GLRenderBelowPath(action); }
inline void py_q_GLRenderInPath(SoGLRenderAction*  action) { SoLocateHighlight::GLRenderInPath(action); }
inline void py_q_handleEvent(SoHandleEventAction*  action) { SoLocateHighlight::handleEvent(action); }
inline void py_q_redrawHighlighted(SoAction*  act, bool  flag) { SoLocateHighlight::redrawHighlighted(act, flag); }
};

class PythonQtWrapper_SoLocateHighlight : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Modes Styles )
enum Modes{
  AUTO = SoLocateHighlight::AUTO,   ON = SoLocateHighlight::ON,   OFF = SoLocateHighlight::OFF};
enum Styles{
  EMISSIVE = SoLocateHighlight::EMISSIVE,   EMISSIVE_DIFFUSE = SoLocateHighlight::EMISSIVE_DIFFUSE};
public Q_SLOTS:
SoLocateHighlight* new_SoLocateHighlight();
   void py_q_GLRenderBelowPath(SoLocateHighlight* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoLocateHighlight*)theWrappedObject)->py_q_GLRenderBelowPath(action));}
   void py_q_GLRenderInPath(SoLocateHighlight* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoLocateHighlight*)theWrappedObject)->py_q_GLRenderInPath(action));}
   SoType  static_SoLocateHighlight_getClassTypeId();
   void py_q_handleEvent(SoLocateHighlight* theWrappedObject, SoHandleEventAction*  action){  (((PythonQtPublicPromoter_SoLocateHighlight*)theWrappedObject)->py_q_handleEvent(action));}
   void redrawHighlighted(SoLocateHighlight* theWrappedObject, SoAction*  act, bool  flag);
   void py_q_redrawHighlighted(SoLocateHighlight* theWrappedObject, SoAction*  act, bool  flag){  (((PythonQtPublicPromoter_SoLocateHighlight*)theWrappedObject)->py_q_redrawHighlighted(act, flag));}
   void static_SoLocateHighlight_turnOffCurrentHighlight(SoGLRenderAction*  action);
SoSFColor*  py_get_color(SoLocateHighlight* theWrappedObject){ return &theWrappedObject->color; }
SoSFEnum*  py_get_mode(SoLocateHighlight* theWrappedObject){ return &theWrappedObject->mode; }
SoSFEnum*  py_get_style(SoLocateHighlight* theWrappedObject){ return &theWrappedObject->style; }
};





class PythonQtShell_SoMaterial : public SoMaterial
{
public:
    PythonQtShell_SoMaterial():SoMaterial(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoMaterial() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void doAction(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoMaterial : public SoMaterial
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoMaterial::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoMaterial::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoMaterial::doAction(action); }
};

class PythonQtWrapper_SoMaterial : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMaterial* new_SoMaterial();
   void py_q_GLRender(SoMaterial* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoMaterial*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoMaterial* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoMaterial*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoMaterial* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoMaterial*)theWrappedObject)->py_q_doAction(action));}
   SoType  static_SoMaterial_getClassTypeId();
SoMFColor*  py_get_ambientColor(SoMaterial* theWrappedObject){ return &theWrappedObject->ambientColor; }
SoMFColor*  py_get_diffuseColor(SoMaterial* theWrappedObject){ return &theWrappedObject->diffuseColor; }
SoMFColor*  py_get_emissiveColor(SoMaterial* theWrappedObject){ return &theWrappedObject->emissiveColor; }
SoMFFloat*  py_get_shininess(SoMaterial* theWrappedObject){ return &theWrappedObject->shininess; }
SoMFColor*  py_get_specularColor(SoMaterial* theWrappedObject){ return &theWrappedObject->specularColor; }
SoMFFloat*  py_get_transparency(SoMaterial* theWrappedObject){ return &theWrappedObject->transparency; }
};





class PythonQtShell_SoMaterialBinding : public SoMaterialBinding
{
public:
    PythonQtShell_SoMaterialBinding():SoMaterialBinding(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoMaterialBinding() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void doAction(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoMaterialBinding : public SoMaterialBinding
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoMaterialBinding::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoMaterialBinding::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoMaterialBinding::doAction(action); }
inline void py_q_pick(SoPickAction*  action) { SoMaterialBinding::pick(action); }
};

class PythonQtWrapper_SoMaterialBinding : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Binding )
enum Binding{
  OVERALL = SoMaterialBinding::OVERALL,   PER_PART = SoMaterialBinding::PER_PART,   PER_PART_INDEXED = SoMaterialBinding::PER_PART_INDEXED,   PER_FACE = SoMaterialBinding::PER_FACE,   PER_FACE_INDEXED = SoMaterialBinding::PER_FACE_INDEXED,   PER_VERTEX = SoMaterialBinding::PER_VERTEX,   PER_VERTEX_INDEXED = SoMaterialBinding::PER_VERTEX_INDEXED};
public Q_SLOTS:
SoMaterialBinding* new_SoMaterialBinding();
   void py_q_GLRender(SoMaterialBinding* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoMaterialBinding*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoMaterialBinding* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoMaterialBinding*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoMaterialBinding* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoMaterialBinding*)theWrappedObject)->py_q_doAction(action));}
   SoType  static_SoMaterialBinding_getClassTypeId();
   void py_q_pick(SoMaterialBinding* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoMaterialBinding*)theWrappedObject)->py_q_pick(action));}
SoSFEnum*  py_get_value(SoMaterialBinding* theWrappedObject){ return &theWrappedObject->value; }
};





class PythonQtShell_SoMatrixTransform : public SoMatrixTransform
{
public:
    PythonQtShell_SoMatrixTransform():SoMatrixTransform(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoMatrixTransform() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void doAction(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoMatrixTransform : public SoMatrixTransform
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoMatrixTransform::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoMatrixTransform::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoMatrixTransform::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoMatrixTransform::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoMatrixTransform::getMatrix(action); }
inline void py_q_pick(SoPickAction*  action) { SoMatrixTransform::pick(action); }
};

class PythonQtWrapper_SoMatrixTransform : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMatrixTransform* new_SoMatrixTransform();
   void py_q_GLRender(SoMatrixTransform* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoMatrixTransform*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoMatrixTransform* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoMatrixTransform*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoMatrixTransform* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoMatrixTransform*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoMatrixTransform* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoMatrixTransform*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoMatrixTransform_getClassTypeId();
   void py_q_getMatrix(SoMatrixTransform* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoMatrixTransform*)theWrappedObject)->py_q_getMatrix(action));}
   void py_q_pick(SoMatrixTransform* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoMatrixTransform*)theWrappedObject)->py_q_pick(action));}
SoSFMatrix*  py_get_matrix(SoMatrixTransform* theWrappedObject){ return &theWrappedObject->matrix; }
};





class PythonQtShell_SoMultipleCopy : public SoMultipleCopy
{
public:
    PythonQtShell_SoMultipleCopy():SoMultipleCopy(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoMultipleCopy() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void doAction(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
bool  readChildren(SoInput*  in) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoMultipleCopy : public SoMultipleCopy
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoMultipleCopy::GLRender(action); }
inline bool  py_q_affectsState() const { return SoMultipleCopy::affectsState(); }
inline void py_q_callback(SoCallbackAction*  action) { SoMultipleCopy::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoMultipleCopy::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoMultipleCopy::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoMultipleCopy::getMatrix(action); }
inline void py_q_handleEvent(SoHandleEventAction*  action) { SoMultipleCopy::handleEvent(action); }
inline void py_q_pick(SoPickAction*  action) { SoMultipleCopy::pick(action); }
inline void py_q_search(SoSearchAction*  action) { SoMultipleCopy::search(action); }
};

class PythonQtWrapper_SoMultipleCopy : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMultipleCopy* new_SoMultipleCopy();
   void py_q_GLRender(SoMultipleCopy* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoMultipleCopy*)theWrappedObject)->py_q_GLRender(action));}
   bool  py_q_affectsState(SoMultipleCopy* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoMultipleCopy*)theWrappedObject)->py_q_affectsState());}
   void py_q_callback(SoMultipleCopy* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoMultipleCopy*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoMultipleCopy* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoMultipleCopy*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoMultipleCopy* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoMultipleCopy*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoMultipleCopy_getClassTypeId();
   void py_q_getMatrix(SoMultipleCopy* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoMultipleCopy*)theWrappedObject)->py_q_getMatrix(action));}
   void py_q_handleEvent(SoMultipleCopy* theWrappedObject, SoHandleEventAction*  action){  (((PythonQtPublicPromoter_SoMultipleCopy*)theWrappedObject)->py_q_handleEvent(action));}
   void py_q_pick(SoMultipleCopy* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoMultipleCopy*)theWrappedObject)->py_q_pick(action));}
   void py_q_search(SoMultipleCopy* theWrappedObject, SoSearchAction*  action){  (((PythonQtPublicPromoter_SoMultipleCopy*)theWrappedObject)->py_q_search(action));}
SoMFMatrix*  py_get_matrix(SoMultipleCopy* theWrappedObject){ return &theWrappedObject->matrix; }
};





class PythonQtShell_SoNode : public SoNode
{
public:
    PythonQtShell_SoNode():SoNode(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoNode() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void doAction(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoNode : public SoNode
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoNode::GLRender(action); }
inline void py_q_GLRenderBelowPath(SoGLRenderAction*  action) { SoNode::GLRenderBelowPath(action); }
inline void py_q_GLRenderInPath(SoGLRenderAction*  action) { SoNode::GLRenderInPath(action); }
inline void py_q_GLRenderOffPath(SoGLRenderAction*  action) { SoNode::GLRenderOffPath(action); }
inline bool  py_q_affectsState() const { return SoNode::affectsState(); }
inline void py_q_callback(SoCallbackAction*  action) { SoNode::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoNode::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoNode::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoNode::getMatrix(action); }
inline void py_q_handleEvent(SoHandleEventAction*  action) { SoNode::handleEvent(action); }
inline void py_q_pick(SoPickAction*  action) { SoNode::pick(action); }
inline void py_q_rayPick(SoRayPickAction*  action) { SoNode::rayPick(action); }
inline void py_q_search(SoSearchAction*  action) { SoNode::search(action); }
inline void py_q_startNotify() { SoNode::startNotify(); }
inline void py_q_write(SoWriteAction*  action) { SoNode::write(action); }
};

class PythonQtWrapper_SoNode : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoNode* new_SoNode();
   void GLRender(SoNode* theWrappedObject, SoGLRenderAction*  action);
   void py_q_GLRender(SoNode* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoNode*)theWrappedObject)->py_q_GLRender(action));}
   void GLRenderBelowPath(SoNode* theWrappedObject, SoGLRenderAction*  action);
   void py_q_GLRenderBelowPath(SoNode* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoNode*)theWrappedObject)->py_q_GLRenderBelowPath(action));}
   void GLRenderInPath(SoNode* theWrappedObject, SoGLRenderAction*  action);
   void py_q_GLRenderInPath(SoNode* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoNode*)theWrappedObject)->py_q_GLRenderInPath(action));}
   void GLRenderOffPath(SoNode* theWrappedObject, SoGLRenderAction*  action);
   void py_q_GLRenderOffPath(SoNode* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoNode*)theWrappedObject)->py_q_GLRenderOffPath(action));}
   bool  affectsState(SoNode* theWrappedObject) const;
   bool  py_q_affectsState(SoNode* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoNode*)theWrappedObject)->py_q_affectsState());}
   void callback(SoNode* theWrappedObject, SoCallbackAction*  action);
   void py_q_callback(SoNode* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoNode*)theWrappedObject)->py_q_callback(action));}
   SoNode*  copy(SoNode* theWrappedObject, bool  copyConnections = 0) const;
   void doAction(SoNode* theWrappedObject, SoAction*  action);
   void py_q_doAction(SoNode* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoNode*)theWrappedObject)->py_q_doAction(action));}
   void getBoundingBox(SoNode* theWrappedObject, SoGetBoundingBoxAction*  action);
   void py_q_getBoundingBox(SoNode* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoNode*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoNode*  static_SoNode_getByName(const SbName&  name);
   SoType  static_SoNode_getClassTypeId();
   void getMatrix(SoNode* theWrappedObject, SoGetMatrixAction*  action);
   void py_q_getMatrix(SoNode* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoNode*)theWrappedObject)->py_q_getMatrix(action));}
   void handleEvent(SoNode* theWrappedObject, SoHandleEventAction*  action);
   void py_q_handleEvent(SoNode* theWrappedObject, SoHandleEventAction*  action){  (((PythonQtPublicPromoter_SoNode*)theWrappedObject)->py_q_handleEvent(action));}
   bool  isOverride(SoNode* theWrappedObject) const;
   void pick(SoNode* theWrappedObject, SoPickAction*  action);
   void py_q_pick(SoNode* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoNode*)theWrappedObject)->py_q_pick(action));}
   void rayPick(SoNode* theWrappedObject, SoRayPickAction*  action);
   void py_q_rayPick(SoNode* theWrappedObject, SoRayPickAction*  action){  (((PythonQtPublicPromoter_SoNode*)theWrappedObject)->py_q_rayPick(action));}
   void search(SoNode* theWrappedObject, SoSearchAction*  action);
   void py_q_search(SoNode* theWrappedObject, SoSearchAction*  action){  (((PythonQtPublicPromoter_SoNode*)theWrappedObject)->py_q_search(action));}
   void setOverride(SoNode* theWrappedObject, bool  state);
   void py_q_startNotify(SoNode* theWrappedObject){  (((PythonQtPublicPromoter_SoNode*)theWrappedObject)->py_q_startNotify());}
   void write(SoNode* theWrappedObject, SoWriteAction*  action);
   void py_q_write(SoNode* theWrappedObject, SoWriteAction*  action){  (((PythonQtPublicPromoter_SoNode*)theWrappedObject)->py_q_write(action));}
};





class PythonQtShell_SoNonIndexedShape : public SoNonIndexedShape
{
public:
    PythonQtShell_SoNonIndexedShape():SoNonIndexedShape(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoNonIndexedShape() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) override;
SoDetail*  createLineSegmentDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, SoPickedPoint*  pp) override;
SoDetail*  createPointDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v, SoPickedPoint*  pp) override;
SoDetail*  createTriangleDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp) override;
void doAction(SoAction*  action) override;
void generatePrimitives(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
bool  shouldGLRender(SoGLRenderAction*  action) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoNonIndexedShape : public SoNonIndexedShape
{ public:
inline void promoted_computeCoordBBox(SoAction*  action, int  numVertices, SbBox3f&  box, SbVec3f&  center) { this->computeCoordBBox(action, numVertices, box, center); }
};

class PythonQtWrapper_SoNonIndexedShape : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoNonIndexedShape* new_SoNonIndexedShape();
   void computeCoordBBox(SoNonIndexedShape* theWrappedObject, SoAction*  action, int  numVertices, SbBox3f&  box, SbVec3f&  center);
   SoType  static_SoNonIndexedShape_getClassTypeId();
SoSFInt32*  py_get_startIndex(SoNonIndexedShape* theWrappedObject){ return &theWrappedObject->startIndex; }
};





class PythonQtShell_SoNormal : public SoNormal
{
public:
    PythonQtShell_SoNormal():SoNormal(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoNormal() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void doAction(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoNormal : public SoNormal
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoNormal::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoNormal::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoNormal::doAction(action); }
inline void py_q_pick(SoPickAction*  action) { SoNormal::pick(action); }
};

class PythonQtWrapper_SoNormal : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoNormal* new_SoNormal();
   void py_q_GLRender(SoNormal* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoNormal*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoNormal* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoNormal*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoNormal* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoNormal*)theWrappedObject)->py_q_doAction(action));}
   SoType  static_SoNormal_getClassTypeId();
   void py_q_pick(SoNormal* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoNormal*)theWrappedObject)->py_q_pick(action));}
SoMFVec3f*  py_get_vector(SoNormal* theWrappedObject){ return &theWrappedObject->vector; }
};





class PythonQtShell_SoNormalBinding : public SoNormalBinding
{
public:
    PythonQtShell_SoNormalBinding():SoNormalBinding(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoNormalBinding() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void doAction(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoNormalBinding : public SoNormalBinding
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoNormalBinding::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoNormalBinding::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoNormalBinding::doAction(action); }
inline void py_q_pick(SoPickAction*  action) { SoNormalBinding::pick(action); }
};

class PythonQtWrapper_SoNormalBinding : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Binding )
enum Binding{
  OVERALL = SoNormalBinding::OVERALL,   PER_PART = SoNormalBinding::PER_PART,   PER_PART_INDEXED = SoNormalBinding::PER_PART_INDEXED,   PER_FACE = SoNormalBinding::PER_FACE,   PER_FACE_INDEXED = SoNormalBinding::PER_FACE_INDEXED,   PER_VERTEX = SoNormalBinding::PER_VERTEX,   PER_VERTEX_INDEXED = SoNormalBinding::PER_VERTEX_INDEXED};
public Q_SLOTS:
SoNormalBinding* new_SoNormalBinding();
   void py_q_GLRender(SoNormalBinding* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoNormalBinding*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoNormalBinding* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoNormalBinding*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoNormalBinding* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoNormalBinding*)theWrappedObject)->py_q_doAction(action));}
   SoType  static_SoNormalBinding_getClassTypeId();
   void py_q_pick(SoNormalBinding* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoNormalBinding*)theWrappedObject)->py_q_pick(action));}
SoSFEnum*  py_get_value(SoNormalBinding* theWrappedObject){ return &theWrappedObject->value; }
};





class PythonQtShell_SoNurbsCurve : public SoNurbsCurve
{
public:
    PythonQtShell_SoNurbsCurve():SoNurbsCurve(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoNurbsCurve() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) override;
SoDetail*  createLineSegmentDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, SoPickedPoint*  pp) override;
SoDetail*  createPointDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v, SoPickedPoint*  pp) override;
SoDetail*  createTriangleDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp) override;
void doAction(SoAction*  action) override;
void generatePrimitives(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
bool  shouldGLRender(SoGLRenderAction*  action) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoNurbsCurve : public SoNurbsCurve
{ public:
inline void promoted_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { this->computeBBox(action, box, center); }
inline void promoted_generatePrimitives(SoAction*  action) { this->generatePrimitives(action); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoNurbsCurve::GLRender(action); }
inline void py_q_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { SoNurbsCurve::computeBBox(action, box, center); }
inline void py_q_generatePrimitives(SoAction*  action) { SoNurbsCurve::generatePrimitives(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoNurbsCurve::getBoundingBox(action); }
inline void py_q_rayPick(SoRayPickAction*  action) { SoNurbsCurve::rayPick(action); }
};

class PythonQtWrapper_SoNurbsCurve : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoNurbsCurve* new_SoNurbsCurve();
   void py_q_GLRender(SoNurbsCurve* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoNurbsCurve*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_computeBBox(SoNurbsCurve* theWrappedObject, SoAction*  action, SbBox3f&  box, SbVec3f&  center){  (((PythonQtPublicPromoter_SoNurbsCurve*)theWrappedObject)->py_q_computeBBox(action, box, center));}
   void py_q_generatePrimitives(SoNurbsCurve* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoNurbsCurve*)theWrappedObject)->py_q_generatePrimitives(action));}
   void py_q_getBoundingBox(SoNurbsCurve* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoNurbsCurve*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoNurbsCurve_getClassTypeId();
   void py_q_rayPick(SoNurbsCurve* theWrappedObject, SoRayPickAction*  action){  (((PythonQtPublicPromoter_SoNurbsCurve*)theWrappedObject)->py_q_rayPick(action));}
   void sendPrimitive(SoNurbsCurve* theWrappedObject, SoAction*  arg__1, SoPrimitiveVertex*  arg__2);
SoMFFloat*  py_get_knotVector(SoNurbsCurve* theWrappedObject){ return &theWrappedObject->knotVector; }
SoSFInt32*  py_get_numControlPoints(SoNurbsCurve* theWrappedObject){ return &theWrappedObject->numControlPoints; }
};





class PythonQtShell_SoNurbsProfile : public SoNurbsProfile
{
public:
    PythonQtShell_SoNurbsProfile():SoNurbsProfile(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoNurbsProfile() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void doAction(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void getTrimCurve(SoState*  state, int&  numPoints, float*&  points, int&  floatsPerVec, int&  numKnots, float*&  knotVector) override;
void getVertices(SoState*  state, int&  nVertices, SbVec2f*&  vertices) override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoNurbsProfile : public SoNurbsProfile
{ public:
inline void py_q_getTrimCurve(SoState*  state, int&  numPoints, float*&  points, int&  floatsPerVec, int&  numKnots, float*&  knotVector) { SoNurbsProfile::getTrimCurve(state, numPoints, points, floatsPerVec, numKnots, knotVector); }
inline void py_q_getVertices(SoState*  state, int&  nVertices, SbVec2f*&  vertices) { SoNurbsProfile::getVertices(state, nVertices, vertices); }
};

class PythonQtWrapper_SoNurbsProfile : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoNurbsProfile* new_SoNurbsProfile();
   SoType  static_SoNurbsProfile_getClassTypeId();
   void py_q_getTrimCurve(SoNurbsProfile* theWrappedObject, SoState*  state, int&  numPoints, float*&  points, int&  floatsPerVec, int&  numKnots, float*&  knotVector){  (((PythonQtPublicPromoter_SoNurbsProfile*)theWrappedObject)->py_q_getTrimCurve(state, numPoints, points, floatsPerVec, numKnots, knotVector));}
   void py_q_getVertices(SoNurbsProfile* theWrappedObject, SoState*  state, int&  nVertices, SbVec2f*&  vertices){  (((PythonQtPublicPromoter_SoNurbsProfile*)theWrappedObject)->py_q_getVertices(state, nVertices, vertices));}
SoMFFloat*  py_get_knotVector(SoNurbsProfile* theWrappedObject){ return &theWrappedObject->knotVector; }
};





class PythonQtShell_SoNurbsSurface : public SoNurbsSurface
{
public:
    PythonQtShell_SoNurbsSurface():SoNurbsSurface(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoNurbsSurface() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) override;
SoDetail*  createLineSegmentDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, SoPickedPoint*  pp) override;
SoDetail*  createPointDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v, SoPickedPoint*  pp) override;
SoDetail*  createTriangleDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp) override;
void doAction(SoAction*  action) override;
void generatePrimitives(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
bool  shouldGLRender(SoGLRenderAction*  action) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoNurbsSurface : public SoNurbsSurface
{ public:
inline void promoted_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { this->computeBBox(action, box, center); }
inline void promoted_generatePrimitives(SoAction*  action) { this->generatePrimitives(action); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoNurbsSurface::GLRender(action); }
inline void py_q_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { SoNurbsSurface::computeBBox(action, box, center); }
inline void py_q_generatePrimitives(SoAction*  action) { SoNurbsSurface::generatePrimitives(action); }
inline void py_q_rayPick(SoRayPickAction*  action) { SoNurbsSurface::rayPick(action); }
};

class PythonQtWrapper_SoNurbsSurface : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoNurbsSurface* new_SoNurbsSurface();
   void py_q_GLRender(SoNurbsSurface* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoNurbsSurface*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_computeBBox(SoNurbsSurface* theWrappedObject, SoAction*  action, SbBox3f&  box, SbVec3f&  center){  (((PythonQtPublicPromoter_SoNurbsSurface*)theWrappedObject)->py_q_computeBBox(action, box, center));}
   void py_q_generatePrimitives(SoNurbsSurface* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoNurbsSurface*)theWrappedObject)->py_q_generatePrimitives(action));}
   SoType  static_SoNurbsSurface_getClassTypeId();
   void py_q_rayPick(SoNurbsSurface* theWrappedObject, SoRayPickAction*  action){  (((PythonQtPublicPromoter_SoNurbsSurface*)theWrappedObject)->py_q_rayPick(action));}
   void sendPrimitive(SoNurbsSurface* theWrappedObject, SoAction*  arg__1, SoPrimitiveVertex*  arg__2);
SoSFInt32*  py_get_numSControlPoints(SoNurbsSurface* theWrappedObject){ return &theWrappedObject->numSControlPoints; }
SoSFInt32*  py_get_numTControlPoints(SoNurbsSurface* theWrappedObject){ return &theWrappedObject->numTControlPoints; }
SoSFInt32*  py_get_numUControlPoints(SoNurbsSurface* theWrappedObject){ return &theWrappedObject->numUControlPoints; }
SoSFInt32*  py_get_numVControlPoints(SoNurbsSurface* theWrappedObject){ return &theWrappedObject->numVControlPoints; }
SoMFFloat*  py_get_sKnotVector(SoNurbsSurface* theWrappedObject){ return &theWrappedObject->sKnotVector; }
SoMFFloat*  py_get_tKnotVector(SoNurbsSurface* theWrappedObject){ return &theWrappedObject->tKnotVector; }
SoMFFloat*  py_get_uKnotVector(SoNurbsSurface* theWrappedObject){ return &theWrappedObject->uKnotVector; }
SoMFFloat*  py_get_vKnotVector(SoNurbsSurface* theWrappedObject){ return &theWrappedObject->vKnotVector; }
};





class PythonQtShell_SoOrthographicCamera : public SoOrthographicCamera
{
public:
    PythonQtShell_SoOrthographicCamera():SoOrthographicCamera(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoOrthographicCamera() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void doAction(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
SbViewVolume  getViewVolume(float  useAspectRatio = 0.0) const override;
void handleEvent(SoHandleEventAction*  action) override;
void jitter(int  numPasses, int  curPass, const SbViewportRegion&  vpReg, SbVec3f&  jitterAmount) const override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void scaleHeight(float  scaleFactor) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
void startNotify() override;
void viewBoundingBox(const SbBox3f&  box, float  aspect, float  slack) override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoOrthographicCamera : public SoOrthographicCamera
{ public:
inline void promoted_viewBoundingBox(const SbBox3f&  box, float  aspect, float  slack) { this->viewBoundingBox(box, aspect, slack); }
inline SbViewVolume  py_q_getViewVolume(float  useAspectRatio = 0.0) const { return SoOrthographicCamera::getViewVolume(useAspectRatio); }
inline void py_q_scaleHeight(float  scaleFactor) { SoOrthographicCamera::scaleHeight(scaleFactor); }
inline void py_q_viewBoundingBox(const SbBox3f&  box, float  aspect, float  slack) { SoOrthographicCamera::viewBoundingBox(box, aspect, slack); }
};

class PythonQtWrapper_SoOrthographicCamera : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoOrthographicCamera* new_SoOrthographicCamera();
   SoType  static_SoOrthographicCamera_getClassTypeId();
   SbViewVolume  py_q_getViewVolume(SoOrthographicCamera* theWrappedObject, float  useAspectRatio = 0.0) const{  return (((PythonQtPublicPromoter_SoOrthographicCamera*)theWrappedObject)->py_q_getViewVolume(useAspectRatio));}
   void py_q_scaleHeight(SoOrthographicCamera* theWrappedObject, float  scaleFactor){  (((PythonQtPublicPromoter_SoOrthographicCamera*)theWrappedObject)->py_q_scaleHeight(scaleFactor));}
   void py_q_viewBoundingBox(SoOrthographicCamera* theWrappedObject, const SbBox3f&  box, float  aspect, float  slack){  (((PythonQtPublicPromoter_SoOrthographicCamera*)theWrappedObject)->py_q_viewBoundingBox(box, aspect, slack));}
SoSFFloat*  py_get_height(SoOrthographicCamera* theWrappedObject){ return &theWrappedObject->height; }
};





class PythonQtShell_SoPackedColor : public SoPackedColor
{
public:
    PythonQtShell_SoPackedColor():SoPackedColor(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoPackedColor() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void doAction(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoPackedColor : public SoPackedColor
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoPackedColor::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoPackedColor::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoPackedColor::doAction(action); }
};

class PythonQtWrapper_SoPackedColor : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoPackedColor* new_SoPackedColor();
   void py_q_GLRender(SoPackedColor* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoPackedColor*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoPackedColor* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoPackedColor*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoPackedColor* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoPackedColor*)theWrappedObject)->py_q_doAction(action));}
   SoType  static_SoPackedColor_getClassTypeId();
   bool  isTransparent(SoPackedColor* theWrappedObject);
SoMFUInt32*  py_get_orderedRGBA(SoPackedColor* theWrappedObject){ return &theWrappedObject->orderedRGBA; }
};





class PythonQtShell_SoPathSwitch : public SoPathSwitch
{
public:
    PythonQtShell_SoPathSwitch():SoPathSwitch(),_wrapper(nullptr) {_type = getClassTypeId();
};
    PythonQtShell_SoPathSwitch(int  nChildren):SoPathSwitch(nChildren),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoPathSwitch() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void doAction(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
bool  readChildren(SoInput*  in) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoPathSwitch : public SoPathSwitch
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoPathSwitch::GLRender(action); }
inline void py_q_doAction(SoAction*  action) { SoPathSwitch::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoPathSwitch::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoPathSwitch::getMatrix(action); }
inline void py_q_handleEvent(SoHandleEventAction*  action) { SoPathSwitch::handleEvent(action); }
inline void py_q_pick(SoPickAction*  action) { SoPathSwitch::pick(action); }
inline void py_q_search(SoSearchAction*  action) { SoPathSwitch::search(action); }
};

class PythonQtWrapper_SoPathSwitch : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoPathSwitch* new_SoPathSwitch();
SoPathSwitch* new_SoPathSwitch(int  nChildren);
   void py_q_GLRender(SoPathSwitch* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoPathSwitch*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_doAction(SoPathSwitch* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoPathSwitch*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoPathSwitch* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoPathSwitch*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoPathSwitch_getClassTypeId();
   void py_q_getMatrix(SoPathSwitch* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoPathSwitch*)theWrappedObject)->py_q_getMatrix(action));}
   void py_q_handleEvent(SoPathSwitch* theWrappedObject, SoHandleEventAction*  action){  (((PythonQtPublicPromoter_SoPathSwitch*)theWrappedObject)->py_q_handleEvent(action));}
   void py_q_pick(SoPathSwitch* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoPathSwitch*)theWrappedObject)->py_q_pick(action));}
   void py_q_search(SoPathSwitch* theWrappedObject, SoSearchAction*  action){  (((PythonQtPublicPromoter_SoPathSwitch*)theWrappedObject)->py_q_search(action));}
SoSFPath*  py_get_path(SoPathSwitch* theWrappedObject){ return &theWrappedObject->path; }
};





class PythonQtShell_SoPendulum : public SoPendulum
{
public:
    PythonQtShell_SoPendulum():SoPendulum(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoPendulum() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void doAction(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
void startNotify() override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoPendulum : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoPendulum* new_SoPendulum();
   SoType  static_SoPendulum_getClassTypeId();
SoSFBool*  py_get_on(SoPendulum* theWrappedObject){ return &theWrappedObject->on; }
SoSFRotation*  py_get_rotation0(SoPendulum* theWrappedObject){ return &theWrappedObject->rotation0; }
SoSFRotation*  py_get_rotation1(SoPendulum* theWrappedObject){ return &theWrappedObject->rotation1; }
SoSFFloat*  py_get_speed(SoPendulum* theWrappedObject){ return &theWrappedObject->speed; }
};





class PythonQtShell_SoPerspectiveCamera : public SoPerspectiveCamera
{
public:
    PythonQtShell_SoPerspectiveCamera():SoPerspectiveCamera(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoPerspectiveCamera() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void doAction(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
SbViewVolume  getViewVolume(float  useAspectRatio = 0.0) const override;
void handleEvent(SoHandleEventAction*  action) override;
void jitter(int  numPasses, int  curPass, const SbViewportRegion&  vpReg, SbVec3f&  jitterAmount) const override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void scaleHeight(float  scaleFactor) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
void startNotify() override;
void viewBoundingBox(const SbBox3f&  box, float  aspect, float  slack) override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoPerspectiveCamera : public SoPerspectiveCamera
{ public:
inline void promoted_viewBoundingBox(const SbBox3f&  box, float  aspect, float  slack) { this->viewBoundingBox(box, aspect, slack); }
inline SbViewVolume  py_q_getViewVolume(float  useAspectRatio = 0.0) const { return SoPerspectiveCamera::getViewVolume(useAspectRatio); }
inline void py_q_scaleHeight(float  scaleFactor) { SoPerspectiveCamera::scaleHeight(scaleFactor); }
inline void py_q_viewBoundingBox(const SbBox3f&  box, float  aspect, float  slack) { SoPerspectiveCamera::viewBoundingBox(box, aspect, slack); }
};

class PythonQtWrapper_SoPerspectiveCamera : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoPerspectiveCamera* new_SoPerspectiveCamera();
   SoType  static_SoPerspectiveCamera_getClassTypeId();
   SbViewVolume  py_q_getViewVolume(SoPerspectiveCamera* theWrappedObject, float  useAspectRatio = 0.0) const{  return (((PythonQtPublicPromoter_SoPerspectiveCamera*)theWrappedObject)->py_q_getViewVolume(useAspectRatio));}
   void py_q_scaleHeight(SoPerspectiveCamera* theWrappedObject, float  scaleFactor){  (((PythonQtPublicPromoter_SoPerspectiveCamera*)theWrappedObject)->py_q_scaleHeight(scaleFactor));}
   void py_q_viewBoundingBox(SoPerspectiveCamera* theWrappedObject, const SbBox3f&  box, float  aspect, float  slack){  (((PythonQtPublicPromoter_SoPerspectiveCamera*)theWrappedObject)->py_q_viewBoundingBox(box, aspect, slack));}
SoSFFloat*  py_get_heightAngle(SoPerspectiveCamera* theWrappedObject){ return &theWrappedObject->heightAngle; }
};





class PythonQtShell_SoPickStyle : public SoPickStyle
{
public:
    PythonQtShell_SoPickStyle():SoPickStyle(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoPickStyle() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void doAction(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoPickStyle : public SoPickStyle
{ public:
inline void py_q_callback(SoCallbackAction*  action) { SoPickStyle::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoPickStyle::doAction(action); }
inline void py_q_pick(SoPickAction*  action) { SoPickStyle::pick(action); }
};

class PythonQtWrapper_SoPickStyle : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Style )
enum Style{
  SHAPE = SoPickStyle::SHAPE,   BOUNDING_BOX = SoPickStyle::BOUNDING_BOX,   UNPICKABLE = SoPickStyle::UNPICKABLE};
public Q_SLOTS:
SoPickStyle* new_SoPickStyle();
   void py_q_callback(SoPickStyle* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoPickStyle*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoPickStyle* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoPickStyle*)theWrappedObject)->py_q_doAction(action));}
   SoType  static_SoPickStyle_getClassTypeId();
   void py_q_pick(SoPickStyle* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoPickStyle*)theWrappedObject)->py_q_pick(action));}
SoSFEnum*  py_get_style(SoPickStyle* theWrappedObject){ return &theWrappedObject->style; }
};





class PythonQtShell_SoPointLight : public SoPointLight
{
public:
    PythonQtShell_SoPointLight():SoPointLight(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoPointLight() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void doAction(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoPointLight : public SoPointLight
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoPointLight::GLRender(action); }
};

class PythonQtWrapper_SoPointLight : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoPointLight* new_SoPointLight();
   void py_q_GLRender(SoPointLight* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoPointLight*)theWrappedObject)->py_q_GLRender(action));}
   SoType  static_SoPointLight_getClassTypeId();
SoSFVec3f*  py_get_location(SoPointLight* theWrappedObject){ return &theWrappedObject->location; }
};





class PythonQtShell_SoPointSet : public SoPointSet
{
public:
    PythonQtShell_SoPointSet():SoPointSet(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoPointSet() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) override;
SoDetail*  createLineSegmentDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, SoPickedPoint*  pp) override;
SoDetail*  createPointDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v, SoPickedPoint*  pp) override;
SoDetail*  createTriangleDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp) override;
void doAction(SoAction*  action) override;
void generatePrimitives(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
bool  shouldGLRender(SoGLRenderAction*  action) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoPointSet : public SoPointSet
{ public:
inline void promoted_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { this->computeBBox(action, box, center); }
inline SoDetail*  promoted_createPointDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v, SoPickedPoint*  pp) { return this->createPointDetail(action, v, pp); }
inline void promoted_generatePrimitives(SoAction*  action) { this->generatePrimitives(action); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoPointSet::GLRender(action); }
inline void py_q_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { SoPointSet::computeBBox(action, box, center); }
inline SoDetail*  py_q_createPointDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v, SoPickedPoint*  pp) { return SoPointSet::createPointDetail(action, v, pp); }
inline void py_q_generatePrimitives(SoAction*  action) { SoPointSet::generatePrimitives(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoPointSet::getBoundingBox(action); }
};

class PythonQtWrapper_SoPointSet : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoPointSet* new_SoPointSet();
   void py_q_GLRender(SoPointSet* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoPointSet*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_computeBBox(SoPointSet* theWrappedObject, SoAction*  action, SbBox3f&  box, SbVec3f&  center){  (((PythonQtPublicPromoter_SoPointSet*)theWrappedObject)->py_q_computeBBox(action, box, center));}
   SoDetail*  py_q_createPointDetail(SoPointSet* theWrappedObject, SoRayPickAction*  action, const SoPrimitiveVertex*  v, SoPickedPoint*  pp){  return (((PythonQtPublicPromoter_SoPointSet*)theWrappedObject)->py_q_createPointDetail(action, v, pp));}
   void py_q_generatePrimitives(SoPointSet* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoPointSet*)theWrappedObject)->py_q_generatePrimitives(action));}
   void py_q_getBoundingBox(SoPointSet* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoPointSet*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoPointSet_getClassTypeId();
SoSFInt32*  py_get_numPoints(SoPointSet* theWrappedObject){ return &theWrappedObject->numPoints; }
};





class PythonQtShell_SoPolygonOffset : public SoPolygonOffset
{
public:
    PythonQtShell_SoPolygonOffset():SoPolygonOffset(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoPolygonOffset() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void doAction(SoAction*  action) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void search(SoSearchAction*  action) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoPolygonOffset : public SoPolygonOffset
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoPolygonOffset::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoPolygonOffset::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoPolygonOffset::doAction(action); }
};

class PythonQtWrapper_SoPolygonOffset : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Style )
enum Style{
  FILLED = SoPolygonOffset::FILLED,   LINES = SoPolygonOffset::LINES,   POINTS = SoPolygonOffset::POINTS,   ALL = SoPolygonOffset::ALL};
public Q_SLOTS:
SoPolygonOffset* new_SoPolygonOffset();
   void py_q_GLRender(SoPolygonOffset* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoPolygonOffset*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoPolygonOffset* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoPolygonOffset*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoPolygonOffset* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoPolygonOffset*)theWrappedObject)->py_q_doAction(action));}
   SoType  static_SoPolygonOffset_getClassTypeId();
SoSFFloat*  py_get_factor(SoPolygonOffset* theWrappedObject){ return &theWrappedObject->factor; }
SoSFBool*  py_get_on(SoPolygonOffset* theWrappedObject){ return &theWrappedObject->on; }
SoSFBitMask*  py_get_styles(SoPolygonOffset* theWrappedObject){ return &theWrappedObject->styles; }
SoSFFloat*  py_get_units(SoPolygonOffset* theWrappedObject){ return &theWrappedObject->units; }
};


