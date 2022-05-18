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
#include <Inventor/fields/SoField.h>
#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/misc/SoBase.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoProfile.h>
#include <Inventor/nodes/SoProfileCoordinate2.h>
#include <Inventor/nodes/SoProfileCoordinate3.h>
#include <Inventor/nodes/SoQuadMesh.h>
#include <Inventor/nodes/SoResetTransform.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/nodes/SoRotationXYZ.h>
#include <Inventor/nodes/SoRotor.h>
#include <Inventor/nodes/SoScale.h>
#include <Inventor/nodes/SoSelection.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/nodes/SoShapeHints.h>
#include <Inventor/nodes/SoShuttle.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoSpotLight.h>
#include <Inventor/nodes/SoSurroundScale.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoText2.h>
#include <Inventor/nodes/SoText3.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoTexture2Transform.h>
#include <Inventor/nodes/SoTextureCoordinate2.h>
#include <Inventor/nodes/SoTextureCoordinateBinding.h>
#include <Inventor/nodes/SoTextureCoordinateDefault.h>
#include <Inventor/nodes/SoTextureCoordinateEnvironment.h>
#include <Inventor/nodes/SoTextureCoordinateFunction.h>
#include <Inventor/nodes/SoTextureCoordinatePlane.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoTransformSeparator.h>
#include <Inventor/nodes/SoTransformation.h>
#include <Inventor/nodes/SoVertexProperty.h>
#include <Inventor/sensors/SoSensor.h>
#include <stdexcept>



class PythonQtShell_SoProfile : public SoProfile
{
public:
    PythonQtShell_SoProfile():SoProfile(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoProfile() override;

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

class PythonQtPublicPromoter_SoProfile : public SoProfile
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoProfile::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoProfile::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoProfile::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoProfile::getBoundingBox(action); }
inline void py_q_getTrimCurve(SoState*  state, int&  numPoints, float*&  points, int&  floatsPerVec, int&  numKnots, float*&  knotVector) { this->getTrimCurve(state, numPoints, points, floatsPerVec, numKnots, knotVector); }
inline void py_q_getVertices(SoState*  state, int&  nVertices, SbVec2f*&  vertices) { this->getVertices(state, nVertices, vertices); }
inline void py_q_pick(SoPickAction*  action) { SoProfile::pick(action); }
};

class PythonQtWrapper_SoProfile : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Profile )
enum Profile{
  START_FIRST = SoProfile::START_FIRST,   START_NEW = SoProfile::START_NEW,   ADD_TO_CURRENT = SoProfile::ADD_TO_CURRENT};
public slots:
SoProfile* new_SoProfile();
   void py_q_GLRender(SoProfile* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoProfile*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoProfile* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoProfile*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoProfile* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoProfile*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoProfile* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoProfile*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoProfile_getClassTypeId();
   void getTrimCurve(SoProfile* theWrappedObject, SoState*  state, int&  numPoints, float*&  points, int&  floatsPerVec, int&  numKnots, float*&  knotVector);
   void py_q_getTrimCurve(SoProfile* theWrappedObject, SoState*  state, int&  numPoints, float*&  points, int&  floatsPerVec, int&  numKnots, float*&  knotVector){  (((PythonQtPublicPromoter_SoProfile*)theWrappedObject)->py_q_getTrimCurve(state, numPoints, points, floatsPerVec, numKnots, knotVector));}
   void getVertices(SoProfile* theWrappedObject, SoState*  state, int&  nVertices, SbVec2f*&  vertices);
   void py_q_getVertices(SoProfile* theWrappedObject, SoState*  state, int&  nVertices, SbVec2f*&  vertices){  (((PythonQtPublicPromoter_SoProfile*)theWrappedObject)->py_q_getVertices(state, nVertices, vertices));}
   void py_q_pick(SoProfile* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoProfile*)theWrappedObject)->py_q_pick(action));}
SoMFInt32*  py_get_index(SoProfile* theWrappedObject){ return &theWrappedObject->index; }
SoSFEnum*  py_get_linkage(SoProfile* theWrappedObject){ return &theWrappedObject->linkage; }
};





class PythonQtShell_SoProfileCoordinate2 : public SoProfileCoordinate2
{
public:
    PythonQtShell_SoProfileCoordinate2():SoProfileCoordinate2(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoProfileCoordinate2() override;

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

class PythonQtPublicPromoter_SoProfileCoordinate2 : public SoProfileCoordinate2
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoProfileCoordinate2::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoProfileCoordinate2::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoProfileCoordinate2::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoProfileCoordinate2::getBoundingBox(action); }
inline void py_q_pick(SoPickAction*  action) { SoProfileCoordinate2::pick(action); }
};

class PythonQtWrapper_SoProfileCoordinate2 : public QObject
{ Q_OBJECT
public:
public slots:
SoProfileCoordinate2* new_SoProfileCoordinate2();
   void py_q_GLRender(SoProfileCoordinate2* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoProfileCoordinate2*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoProfileCoordinate2* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoProfileCoordinate2*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoProfileCoordinate2* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoProfileCoordinate2*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoProfileCoordinate2* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoProfileCoordinate2*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoProfileCoordinate2_getClassTypeId();
   void py_q_pick(SoProfileCoordinate2* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoProfileCoordinate2*)theWrappedObject)->py_q_pick(action));}
SoMFVec2f*  py_get_point(SoProfileCoordinate2* theWrappedObject){ return &theWrappedObject->point; }
};





class PythonQtShell_SoProfileCoordinate3 : public SoProfileCoordinate3
{
public:
    PythonQtShell_SoProfileCoordinate3():SoProfileCoordinate3(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoProfileCoordinate3() override;

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

class PythonQtPublicPromoter_SoProfileCoordinate3 : public SoProfileCoordinate3
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoProfileCoordinate3::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoProfileCoordinate3::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoProfileCoordinate3::doAction(action); }
inline void py_q_pick(SoPickAction*  action) { SoProfileCoordinate3::pick(action); }
};

class PythonQtWrapper_SoProfileCoordinate3 : public QObject
{ Q_OBJECT
public:
public slots:
SoProfileCoordinate3* new_SoProfileCoordinate3();
   void py_q_GLRender(SoProfileCoordinate3* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoProfileCoordinate3*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoProfileCoordinate3* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoProfileCoordinate3*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoProfileCoordinate3* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoProfileCoordinate3*)theWrappedObject)->py_q_doAction(action));}
   SoType  static_SoProfileCoordinate3_getClassTypeId();
   void py_q_pick(SoProfileCoordinate3* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoProfileCoordinate3*)theWrappedObject)->py_q_pick(action));}
SoMFVec3f*  py_get_point(SoProfileCoordinate3* theWrappedObject){ return &theWrappedObject->point; }
};





class PythonQtShell_SoQuadMesh : public SoQuadMesh
{
public:
    PythonQtShell_SoQuadMesh():SoQuadMesh(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoQuadMesh() override;

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

class PythonQtPublicPromoter_SoQuadMesh : public SoQuadMesh
{ public:
inline void promoted_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { this->computeBBox(action, box, center); }
inline SoDetail*  promoted_createTriangleDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp) { return this->createTriangleDetail(action, v1, v2, v3, pp); }
inline void promoted_generatePrimitives(SoAction*  action) { this->generatePrimitives(action); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoQuadMesh::GLRender(action); }
inline void py_q_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { SoQuadMesh::computeBBox(action, box, center); }
inline SoDetail*  py_q_createTriangleDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp) { return SoQuadMesh::createTriangleDetail(action, v1, v2, v3, pp); }
inline void py_q_generatePrimitives(SoAction*  action) { SoQuadMesh::generatePrimitives(action); }
};

class PythonQtWrapper_SoQuadMesh : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Binding )
enum Binding{
  OVERALL = SoQuadMesh::OVERALL,   PER_ROW = SoQuadMesh::PER_ROW,   PER_QUAD = SoQuadMesh::PER_QUAD,   PER_VERTEX = SoQuadMesh::PER_VERTEX};
public slots:
SoQuadMesh* new_SoQuadMesh();
   void py_q_GLRender(SoQuadMesh* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoQuadMesh*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_computeBBox(SoQuadMesh* theWrappedObject, SoAction*  action, SbBox3f&  box, SbVec3f&  center){  (((PythonQtPublicPromoter_SoQuadMesh*)theWrappedObject)->py_q_computeBBox(action, box, center));}
   SoDetail*  py_q_createTriangleDetail(SoQuadMesh* theWrappedObject, SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp){  return (((PythonQtPublicPromoter_SoQuadMesh*)theWrappedObject)->py_q_createTriangleDetail(action, v1, v2, v3, pp));}
   void py_q_generatePrimitives(SoQuadMesh* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoQuadMesh*)theWrappedObject)->py_q_generatePrimitives(action));}
   SoType  static_SoQuadMesh_getClassTypeId();
SoSFInt32*  py_get_verticesPerColumn(SoQuadMesh* theWrappedObject){ return &theWrappedObject->verticesPerColumn; }
SoSFInt32*  py_get_verticesPerRow(SoQuadMesh* theWrappedObject){ return &theWrappedObject->verticesPerRow; }
};





class PythonQtShell_SoResetTransform : public SoResetTransform
{
public:
    PythonQtShell_SoResetTransform():SoResetTransform(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoResetTransform() override;

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

class PythonQtPublicPromoter_SoResetTransform : public SoResetTransform
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoResetTransform::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoResetTransform::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoResetTransform::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoResetTransform::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoResetTransform::getMatrix(action); }
inline void py_q_pick(SoPickAction*  action) { SoResetTransform::pick(action); }
};

class PythonQtWrapper_SoResetTransform : public QObject
{ Q_OBJECT
public:
Q_ENUMS(ResetType )
enum ResetType{
  TRANSFORM = SoResetTransform::TRANSFORM,   BBOX = SoResetTransform::BBOX};
public slots:
SoResetTransform* new_SoResetTransform();
   void py_q_GLRender(SoResetTransform* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoResetTransform*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoResetTransform* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoResetTransform*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoResetTransform* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoResetTransform*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoResetTransform* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoResetTransform*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoResetTransform_getClassTypeId();
   void py_q_getMatrix(SoResetTransform* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoResetTransform*)theWrappedObject)->py_q_getMatrix(action));}
   void py_q_pick(SoResetTransform* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoResetTransform*)theWrappedObject)->py_q_pick(action));}
SoSFBitMask*  py_get_whatToReset(SoResetTransform* theWrappedObject){ return &theWrappedObject->whatToReset; }
};





class PythonQtShell_SoRotation : public SoRotation
{
public:
    PythonQtShell_SoRotation():SoRotation(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoRotation() override;

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

class PythonQtPublicPromoter_SoRotation : public SoRotation
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoRotation::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoRotation::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoRotation::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoRotation::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoRotation::getMatrix(action); }
inline void py_q_pick(SoPickAction*  action) { SoRotation::pick(action); }
};

class PythonQtWrapper_SoRotation : public QObject
{ Q_OBJECT
public:
public slots:
SoRotation* new_SoRotation();
   void py_q_GLRender(SoRotation* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoRotation*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoRotation* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoRotation*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoRotation* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoRotation*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoRotation* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoRotation*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoRotation_getClassTypeId();
   void py_q_getMatrix(SoRotation* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoRotation*)theWrappedObject)->py_q_getMatrix(action));}
   void py_q_pick(SoRotation* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoRotation*)theWrappedObject)->py_q_pick(action));}
SoSFRotation*  py_get_rotation(SoRotation* theWrappedObject){ return &theWrappedObject->rotation; }
};





class PythonQtShell_SoRotationXYZ : public SoRotationXYZ
{
public:
    PythonQtShell_SoRotationXYZ():SoRotationXYZ(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoRotationXYZ() override;

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

class PythonQtPublicPromoter_SoRotationXYZ : public SoRotationXYZ
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoRotationXYZ::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoRotationXYZ::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoRotationXYZ::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoRotationXYZ::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoRotationXYZ::getMatrix(action); }
inline void py_q_pick(SoPickAction*  action) { SoRotationXYZ::pick(action); }
};

class PythonQtWrapper_SoRotationXYZ : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Axis )
enum Axis{
  X = SoRotationXYZ::X,   Y = SoRotationXYZ::Y,   Z = SoRotationXYZ::Z};
public slots:
SoRotationXYZ* new_SoRotationXYZ();
   void py_q_GLRender(SoRotationXYZ* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoRotationXYZ*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoRotationXYZ* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoRotationXYZ*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoRotationXYZ* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoRotationXYZ*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoRotationXYZ* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoRotationXYZ*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoRotationXYZ_getClassTypeId();
   void py_q_getMatrix(SoRotationXYZ* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoRotationXYZ*)theWrappedObject)->py_q_getMatrix(action));}
   SbRotation  getRotation(SoRotationXYZ* theWrappedObject) const;
   void py_q_pick(SoRotationXYZ* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoRotationXYZ*)theWrappedObject)->py_q_pick(action));}
SoSFFloat*  py_get_angle(SoRotationXYZ* theWrappedObject){ return &theWrappedObject->angle; }
SoSFEnum*  py_get_axis(SoRotationXYZ* theWrappedObject){ return &theWrappedObject->axis; }
};





class PythonQtShell_SoRotor : public SoRotor
{
public:
    PythonQtShell_SoRotor():SoRotor(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoRotor() override;

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

class PythonQtWrapper_SoRotor : public QObject
{ Q_OBJECT
public:
public slots:
SoRotor* new_SoRotor();
   SoType  static_SoRotor_getClassTypeId();
SoSFBool*  py_get_on(SoRotor* theWrappedObject){ return &theWrappedObject->on; }
SoSFFloat*  py_get_speed(SoRotor* theWrappedObject){ return &theWrappedObject->speed; }
};





class PythonQtShell_SoScale : public SoScale
{
public:
    PythonQtShell_SoScale():SoScale(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoScale() override;

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

class PythonQtPublicPromoter_SoScale : public SoScale
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoScale::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoScale::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoScale::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoScale::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoScale::getMatrix(action); }
inline void py_q_pick(SoPickAction*  action) { SoScale::pick(action); }
};

class PythonQtWrapper_SoScale : public QObject
{ Q_OBJECT
public:
public slots:
SoScale* new_SoScale();
   void py_q_GLRender(SoScale* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoScale*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoScale* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoScale*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoScale* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoScale*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoScale* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoScale*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoScale_getClassTypeId();
   void py_q_getMatrix(SoScale* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoScale*)theWrappedObject)->py_q_getMatrix(action));}
   void py_q_pick(SoScale* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoScale*)theWrappedObject)->py_q_pick(action));}
SoSFVec3f*  py_get_scaleFactor(SoScale* theWrappedObject){ return &theWrappedObject->scaleFactor; }
};





class PythonQtShell_SoSelection : public SoSelection
{
public:
    PythonQtShell_SoSelection():SoSelection(),_wrapper(nullptr) {_type = getClassTypeId();
};
    PythonQtShell_SoSelection(int  nChildren):SoSelection(nChildren),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoSelection() override;

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

class PythonQtPublicPromoter_SoSelection : public SoSelection
{ public:
inline void promoted_addPath(SoPath*  path) { this->addPath(path); }
inline SoPath*  promoted_copyFromThis(const SoPath*  path) const { return this->copyFromThis(path); }
inline int  promoted_findPath(const SoPath*  path) const { return this->findPath(path); }
inline SoPath*  promoted_getPickedPath(const SoPickedPoint*  pickedPoint) { return this->getPickedPath(pickedPoint); }
inline void promoted_handleEvent(SoHandleEventAction*  action) { this->handleEvent(action); }
inline void promoted_invokeSelectionPolicy(SoPath*  path, bool  shiftDown) { this->invokeSelectionPolicy(path, shiftDown); }
inline void promoted_performSingleSelection(SoPath*  path) { this->performSingleSelection(path); }
inline void promoted_performToggleSelection(SoPath*  path) { this->performToggleSelection(path); }
inline void promoted_removePath(int  which) { this->removePath(which); }
inline void py_q_handleEvent(SoHandleEventAction*  action) { SoSelection::handleEvent(action); }
};

class PythonQtWrapper_SoSelection : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Policy )
enum Policy{
  SINGLE = SoSelection::SINGLE,   TOGGLE = SoSelection::TOGGLE,   SHIFT = SoSelection::SHIFT};
public slots:
SoSelection* new_SoSelection();
SoSelection* new_SoSelection(int  nChildren);
   void addPath(SoSelection* theWrappedObject, SoPath*  path);
   SoPath*  copyFromThis(SoSelection* theWrappedObject, const SoPath*  path) const;
   void deselect(SoSelection* theWrappedObject, SoNode*  node);
   void deselect(SoSelection* theWrappedObject, const SoPath*  path);
   void deselect(SoSelection* theWrappedObject, int  which);
   void deselectAll(SoSelection* theWrappedObject);
   int  findPath(SoSelection* theWrappedObject, const SoPath*  path) const;
   SoType  static_SoSelection_getClassTypeId();
   int  getNumSelected(SoSelection* theWrappedObject) const;
   SoPath*  getPath(SoSelection* theWrappedObject, int  index) const;
   bool  getPickMatching(SoSelection* theWrappedObject) const;
   SoPath*  getPickedPath(SoSelection* theWrappedObject, const SoPickedPoint*  pickedPoint);
   void py_q_handleEvent(SoSelection* theWrappedObject, SoHandleEventAction*  action){  (((PythonQtPublicPromoter_SoSelection*)theWrappedObject)->py_q_handleEvent(action));}
   void invokeSelectionPolicy(SoSelection* theWrappedObject, SoPath*  path, bool  shiftDown);
   bool  isPickMatching(SoSelection* theWrappedObject) const;
   bool  isSelected(SoSelection* theWrappedObject, SoNode*  node) const;
   bool  isSelected(SoSelection* theWrappedObject, const SoPath*  path) const;
   SoPath*  operator_subscript(SoSelection* theWrappedObject, int  i) const;
   void performSingleSelection(SoSelection* theWrappedObject, SoPath*  path);
   void performToggleSelection(SoSelection* theWrappedObject, SoPath*  path);
   void removePath(SoSelection* theWrappedObject, int  which);
   void select(SoSelection* theWrappedObject, SoNode*  node);
   void select(SoSelection* theWrappedObject, const SoPath*  path);
   void setPickMatching(SoSelection* theWrappedObject, bool  pickTwice);
   void toggle(SoSelection* theWrappedObject, SoNode*  node);
   void toggle(SoSelection* theWrappedObject, const SoPath*  path);
SoSFEnum*  py_get_policy(SoSelection* theWrappedObject){ return &theWrappedObject->policy; }
SoSFBool*  py_get_selectOnlyOnClick(SoSelection* theWrappedObject){ return &theWrappedObject->selectOnlyOnClick; }
};





class PythonQtShell_SoSeparator : public SoSeparator
{
public:
    PythonQtShell_SoSeparator():SoSeparator(),_wrapper(nullptr) {_type = getClassTypeId();
};
    PythonQtShell_SoSeparator(int  nChildren):SoSeparator(nChildren),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoSeparator() override;

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

class PythonQtPublicPromoter_SoSeparator : public SoSeparator
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoSeparator::GLRender(action); }
inline void py_q_GLRenderBelowPath(SoGLRenderAction*  action) { SoSeparator::GLRenderBelowPath(action); }
inline void py_q_GLRenderInPath(SoGLRenderAction*  action) { SoSeparator::GLRenderInPath(action); }
inline void py_q_GLRenderOffPath(SoGLRenderAction*  action) { SoSeparator::GLRenderOffPath(action); }
inline bool  py_q_affectsState() const { return SoSeparator::affectsState(); }
inline void py_q_callback(SoCallbackAction*  action) { SoSeparator::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoSeparator::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoSeparator::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoSeparator::getMatrix(action); }
inline void py_q_handleEvent(SoHandleEventAction*  action) { SoSeparator::handleEvent(action); }
inline void py_q_rayPick(SoRayPickAction*  action) { SoSeparator::rayPick(action); }
inline void py_q_search(SoSearchAction*  action) { SoSeparator::search(action); }
};

class PythonQtWrapper_SoSeparator : public QObject
{ Q_OBJECT
public:
Q_ENUMS(CacheEnabled )
enum CacheEnabled{
  OFF = SoSeparator::OFF,   ON = SoSeparator::ON,   AUTO = SoSeparator::AUTO};
public slots:
SoSeparator* new_SoSeparator();
SoSeparator* new_SoSeparator(int  nChildren);
   void py_q_GLRender(SoSeparator* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoSeparator*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_GLRenderBelowPath(SoSeparator* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoSeparator*)theWrappedObject)->py_q_GLRenderBelowPath(action));}
   void py_q_GLRenderInPath(SoSeparator* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoSeparator*)theWrappedObject)->py_q_GLRenderInPath(action));}
   void py_q_GLRenderOffPath(SoSeparator* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoSeparator*)theWrappedObject)->py_q_GLRenderOffPath(action));}
   bool  py_q_affectsState(SoSeparator* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoSeparator*)theWrappedObject)->py_q_affectsState());}
   void py_q_callback(SoSeparator* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoSeparator*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoSeparator* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoSeparator*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoSeparator* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoSeparator*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoSeparator_getClassTypeId();
   void py_q_getMatrix(SoSeparator* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoSeparator*)theWrappedObject)->py_q_getMatrix(action));}
   int  static_SoSeparator_getNumRenderCaches();
   void py_q_handleEvent(SoSeparator* theWrappedObject, SoHandleEventAction*  action){  (((PythonQtPublicPromoter_SoSeparator*)theWrappedObject)->py_q_handleEvent(action));}
   void py_q_rayPick(SoSeparator* theWrappedObject, SoRayPickAction*  action){  (((PythonQtPublicPromoter_SoSeparator*)theWrappedObject)->py_q_rayPick(action));}
   void py_q_search(SoSeparator* theWrappedObject, SoSearchAction*  action){  (((PythonQtPublicPromoter_SoSeparator*)theWrappedObject)->py_q_search(action));}
   void static_SoSeparator_setNumRenderCaches(int  howMany);
SoSFEnum*  py_get_boundingBoxCaching(SoSeparator* theWrappedObject){ return &theWrappedObject->boundingBoxCaching; }
SoSFEnum*  py_get_pickCulling(SoSeparator* theWrappedObject){ return &theWrappedObject->pickCulling; }
SoSFEnum*  py_get_renderCaching(SoSeparator* theWrappedObject){ return &theWrappedObject->renderCaching; }
SoSFEnum*  py_get_renderCulling(SoSeparator* theWrappedObject){ return &theWrappedObject->renderCulling; }
};





class PythonQtShell_SoShape : public SoShape
{
public:
    PythonQtShell_SoShape():SoShape(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoShape() override;

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

class PythonQtPublicPromoter_SoShape : public SoShape
{ public:
inline void promoted_GLRenderBoundingBox(SoGLRenderAction*  action) { this->GLRenderBoundingBox(action); }
inline void promoted_beginShape(SoAction*  action, SoShape::TriangleShape  shapeType, SoFaceDetail*  faceDetail = nullptr) { this->beginShape(action, shapeType, faceDetail); }
inline void promoted_beginSolidShape(SoGLRenderAction*  action) { this->beginSolidShape(action); }
inline void promoted_computeObjectSpaceRay(SoRayPickAction*  action) { this->computeObjectSpaceRay(action); }
inline void promoted_computeObjectSpaceRay(SoRayPickAction*  action, const SbMatrix&  matrix) { this->computeObjectSpaceRay(action, matrix); }
inline SoDetail*  promoted_createLineSegmentDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, SoPickedPoint*  pp) { return this->createLineSegmentDetail(action, v1, v2, pp); }
inline SoDetail*  promoted_createPointDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v, SoPickedPoint*  pp) { return this->createPointDetail(action, v, pp); }
inline SoDetail*  promoted_createTriangleDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp) { return this->createTriangleDetail(action, v1, v2, v3, pp); }
inline void promoted_endShape() { this->endShape(); }
inline void promoted_endSolidShape(SoGLRenderAction*  action) { this->endSolidShape(action); }
inline void promoted_generatePrimitives(SoAction*  action) { this->generatePrimitives(action); }
inline void promoted_invokeLineSegmentCallbacks(SoAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2) { this->invokeLineSegmentCallbacks(action, v1, v2); }
inline void promoted_invokePointCallbacks(SoAction*  action, const SoPrimitiveVertex*  v) { this->invokePointCallbacks(action, v); }
inline void promoted_invokeTriangleCallbacks(SoAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3) { this->invokeTriangleCallbacks(action, v1, v2, v3); }
inline void promoted_shapeVertex(const SoPrimitiveVertex*  v) { this->shapeVertex(v); }
inline bool  promoted_shouldGLRender(SoGLRenderAction*  action) { return this->shouldGLRender(action); }
inline bool  promoted_shouldRayPick(SoRayPickAction*  action) { return this->shouldRayPick(action); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoShape::GLRender(action); }
inline bool  py_q_affectsState() const { return SoShape::affectsState(); }
inline void py_q_callback(SoCallbackAction*  action) { SoShape::callback(action); }
inline void py_q_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { this->computeBBox(action, box, center); }
inline SoDetail*  py_q_createLineSegmentDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, SoPickedPoint*  pp) { return SoShape::createLineSegmentDetail(action, v1, v2, pp); }
inline SoDetail*  py_q_createPointDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v, SoPickedPoint*  pp) { return SoShape::createPointDetail(action, v, pp); }
inline SoDetail*  py_q_createTriangleDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp) { return SoShape::createTriangleDetail(action, v1, v2, v3, pp); }
inline void py_q_generatePrimitives(SoAction*  action) { this->generatePrimitives(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoShape::getBoundingBox(action); }
inline void py_q_rayPick(SoRayPickAction*  action) { SoShape::rayPick(action); }
inline bool  py_q_shouldGLRender(SoGLRenderAction*  action) { return SoShape::shouldGLRender(action); }
};

class PythonQtWrapper_SoShape : public QObject
{ Q_OBJECT
public:
Q_ENUMS(TriangleShape )
enum TriangleShape{
  TRIANGLE_STRIP = SoShape::TRIANGLE_STRIP,   TRIANGLE_FAN = SoShape::TRIANGLE_FAN,   TRIANGLES = SoShape::TRIANGLES,   POLYGON = SoShape::POLYGON};
public slots:
SoShape* new_SoShape();
   void py_q_GLRender(SoShape* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoShape*)theWrappedObject)->py_q_GLRender(action));}
   void GLRenderBoundingBox(SoShape* theWrappedObject, SoGLRenderAction*  action);
   bool  py_q_affectsState(SoShape* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoShape*)theWrappedObject)->py_q_affectsState());}
   void beginShape(SoShape* theWrappedObject, SoAction*  action, SoShape::TriangleShape  shapeType, SoFaceDetail*  faceDetail = nullptr);
   void beginSolidShape(SoShape* theWrappedObject, SoGLRenderAction*  action);
   void py_q_callback(SoShape* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoShape*)theWrappedObject)->py_q_callback(action));}
   void computeBBox(SoShape* theWrappedObject, SoAction*  action, SbBox3f&  box, SbVec3f&  center);
   void py_q_computeBBox(SoShape* theWrappedObject, SoAction*  action, SbBox3f&  box, SbVec3f&  center){  (((PythonQtPublicPromoter_SoShape*)theWrappedObject)->py_q_computeBBox(action, box, center));}
   void computeObjectSpaceRay(SoShape* theWrappedObject, SoRayPickAction*  action);
   void computeObjectSpaceRay(SoShape* theWrappedObject, SoRayPickAction*  action, const SbMatrix&  matrix);
   SoDetail*  createLineSegmentDetail(SoShape* theWrappedObject, SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, SoPickedPoint*  pp);
   SoDetail*  py_q_createLineSegmentDetail(SoShape* theWrappedObject, SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, SoPickedPoint*  pp){  return (((PythonQtPublicPromoter_SoShape*)theWrappedObject)->py_q_createLineSegmentDetail(action, v1, v2, pp));}
   SoDetail*  createPointDetail(SoShape* theWrappedObject, SoRayPickAction*  action, const SoPrimitiveVertex*  v, SoPickedPoint*  pp);
   SoDetail*  py_q_createPointDetail(SoShape* theWrappedObject, SoRayPickAction*  action, const SoPrimitiveVertex*  v, SoPickedPoint*  pp){  return (((PythonQtPublicPromoter_SoShape*)theWrappedObject)->py_q_createPointDetail(action, v, pp));}
   SoDetail*  createTriangleDetail(SoShape* theWrappedObject, SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp);
   SoDetail*  py_q_createTriangleDetail(SoShape* theWrappedObject, SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp){  return (((PythonQtPublicPromoter_SoShape*)theWrappedObject)->py_q_createTriangleDetail(action, v1, v2, v3, pp));}
   void endShape(SoShape* theWrappedObject);
   void endSolidShape(SoShape* theWrappedObject, SoGLRenderAction*  action);
   void generatePrimitives(SoShape* theWrappedObject, SoAction*  action);
   void py_q_generatePrimitives(SoShape* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoShape*)theWrappedObject)->py_q_generatePrimitives(action));}
   void py_q_getBoundingBox(SoShape* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoShape*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoShape_getClassTypeId();
   void static_SoShape_getScreenSize(SoState*  state, const SbBox3f&  boundingBox, SbVec2s&  rectSize);
   void invokeLineSegmentCallbacks(SoShape* theWrappedObject, SoAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2);
   void invokePointCallbacks(SoShape* theWrappedObject, SoAction*  action, const SoPrimitiveVertex*  v);
   void invokeTriangleCallbacks(SoShape* theWrappedObject, SoAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3);
   void py_q_rayPick(SoShape* theWrappedObject, SoRayPickAction*  action){  (((PythonQtPublicPromoter_SoShape*)theWrappedObject)->py_q_rayPick(action));}
   void shapeVertex(SoShape* theWrappedObject, const SoPrimitiveVertex*  v);
   bool  shouldGLRender(SoShape* theWrappedObject, SoGLRenderAction*  action);
   bool  py_q_shouldGLRender(SoShape* theWrappedObject, SoGLRenderAction*  action){  return (((PythonQtPublicPromoter_SoShape*)theWrappedObject)->py_q_shouldGLRender(action));}
   bool  shouldRayPick(SoShape* theWrappedObject, SoRayPickAction*  action);
};





class PythonQtShell_SoShapeHints : public SoShapeHints
{
public:
    PythonQtShell_SoShapeHints():SoShapeHints(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoShapeHints() override;

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

class PythonQtPublicPromoter_SoShapeHints : public SoShapeHints
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoShapeHints::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoShapeHints::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoShapeHints::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoShapeHints::getBoundingBox(action); }
inline void py_q_pick(SoPickAction*  action) { SoShapeHints::pick(action); }
};

class PythonQtWrapper_SoShapeHints : public QObject
{ Q_OBJECT
public:
Q_ENUMS(FaceType ShapeType VertexOrdering )
enum FaceType{
  UNKNOWN_FACE_TYPE = SoShapeHints::UNKNOWN_FACE_TYPE,   CONVEX = SoShapeHints::CONVEX};
enum ShapeType{
  UNKNOWN_SHAPE_TYPE = SoShapeHints::UNKNOWN_SHAPE_TYPE,   SOLID = SoShapeHints::SOLID};
enum VertexOrdering{
  UNKNOWN_ORDERING = SoShapeHints::UNKNOWN_ORDERING,   CLOCKWISE = SoShapeHints::CLOCKWISE,   COUNTERCLOCKWISE = SoShapeHints::COUNTERCLOCKWISE};
public slots:
SoShapeHints* new_SoShapeHints();
   void py_q_GLRender(SoShapeHints* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoShapeHints*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoShapeHints* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoShapeHints*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoShapeHints* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoShapeHints*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoShapeHints* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoShapeHints*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoShapeHints_getClassTypeId();
   void py_q_pick(SoShapeHints* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoShapeHints*)theWrappedObject)->py_q_pick(action));}
SoSFFloat*  py_get_creaseAngle(SoShapeHints* theWrappedObject){ return &theWrappedObject->creaseAngle; }
SoSFEnum*  py_get_faceType(SoShapeHints* theWrappedObject){ return &theWrappedObject->faceType; }
SoSFEnum*  py_get_shapeType(SoShapeHints* theWrappedObject){ return &theWrappedObject->shapeType; }
SoSFBool*  py_get_useVBO(SoShapeHints* theWrappedObject){ return &theWrappedObject->useVBO; }
SoSFEnum*  py_get_vertexOrdering(SoShapeHints* theWrappedObject){ return &theWrappedObject->vertexOrdering; }
};





class PythonQtShell_SoShuttle : public SoShuttle
{
public:
    PythonQtShell_SoShuttle():SoShuttle(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoShuttle() override;

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

class PythonQtWrapper_SoShuttle : public QObject
{ Q_OBJECT
public:
public slots:
SoShuttle* new_SoShuttle();
   SoType  static_SoShuttle_getClassTypeId();
SoSFBool*  py_get_on(SoShuttle* theWrappedObject){ return &theWrappedObject->on; }
SoSFFloat*  py_get_speed(SoShuttle* theWrappedObject){ return &theWrappedObject->speed; }
SoSFVec3f*  py_get_translation0(SoShuttle* theWrappedObject){ return &theWrappedObject->translation0; }
SoSFVec3f*  py_get_translation1(SoShuttle* theWrappedObject){ return &theWrappedObject->translation1; }
};





class PythonQtShell_SoSphere : public SoSphere
{
public:
    PythonQtShell_SoSphere():SoSphere(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoSphere() override;

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

class PythonQtPublicPromoter_SoSphere : public SoSphere
{ public:
inline void promoted_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { this->computeBBox(action, box, center); }
inline void promoted_generatePrimitives(SoAction*  action) { this->generatePrimitives(action); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoSphere::GLRender(action); }
inline void py_q_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { SoSphere::computeBBox(action, box, center); }
inline void py_q_generatePrimitives(SoAction*  action) { SoSphere::generatePrimitives(action); }
inline void py_q_rayPick(SoRayPickAction*  action) { SoSphere::rayPick(action); }
};

class PythonQtWrapper_SoSphere : public QObject
{ Q_OBJECT
public:
public slots:
SoSphere* new_SoSphere();
   void py_q_GLRender(SoSphere* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoSphere*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_computeBBox(SoSphere* theWrappedObject, SoAction*  action, SbBox3f&  box, SbVec3f&  center){  (((PythonQtPublicPromoter_SoSphere*)theWrappedObject)->py_q_computeBBox(action, box, center));}
   void py_q_generatePrimitives(SoSphere* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoSphere*)theWrappedObject)->py_q_generatePrimitives(action));}
   SoType  static_SoSphere_getClassTypeId();
   void py_q_rayPick(SoSphere* theWrappedObject, SoRayPickAction*  action){  (((PythonQtPublicPromoter_SoSphere*)theWrappedObject)->py_q_rayPick(action));}
SoSFFloat*  py_get_radius(SoSphere* theWrappedObject){ return &theWrappedObject->radius; }
SoSFInt32*  py_get_subdivision(SoSphere* theWrappedObject){ return &theWrappedObject->subdivision; }
};





class PythonQtShell_SoSpotLight : public SoSpotLight
{
public:
    PythonQtShell_SoSpotLight():SoSpotLight(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoSpotLight() override;

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

class PythonQtPublicPromoter_SoSpotLight : public SoSpotLight
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoSpotLight::GLRender(action); }
};

class PythonQtWrapper_SoSpotLight : public QObject
{ Q_OBJECT
public:
public slots:
SoSpotLight* new_SoSpotLight();
   void py_q_GLRender(SoSpotLight* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoSpotLight*)theWrappedObject)->py_q_GLRender(action));}
   SoType  static_SoSpotLight_getClassTypeId();
SoSFFloat*  py_get_cutOffAngle(SoSpotLight* theWrappedObject){ return &theWrappedObject->cutOffAngle; }
SoSFVec3f*  py_get_direction(SoSpotLight* theWrappedObject){ return &theWrappedObject->direction; }
SoSFFloat*  py_get_dropOffRate(SoSpotLight* theWrappedObject){ return &theWrappedObject->dropOffRate; }
SoSFVec3f*  py_get_location(SoSpotLight* theWrappedObject){ return &theWrappedObject->location; }
};





class PythonQtShell_SoSurroundScale : public SoSurroundScale
{
public:
    PythonQtShell_SoSurroundScale():SoSurroundScale(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoSurroundScale() override;

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

class PythonQtPublicPromoter_SoSurroundScale : public SoSurroundScale
{ public:
inline void promoted_GLRender(SoGLRenderAction*  action) { this->GLRender(action); }
inline void promoted_callback(SoCallbackAction*  action) { this->callback(action); }
inline void promoted_getBoundingBox(SoGetBoundingBoxAction*  action) { this->getBoundingBox(action); }
inline void promoted_getMatrix(SoGetMatrixAction*  action) { this->getMatrix(action); }
inline bool  promoted_isIgnoreInBbox() { return this->isIgnoreInBbox(); }
inline void promoted_pick(SoPickAction*  action) { this->pick(action); }
inline void promoted_setIgnoreInBbox(bool  newVal) { this->setIgnoreInBbox(newVal); }
inline void promoted_updateMySurroundParams(SoAction*  action, const SbMatrix&  inv) { this->updateMySurroundParams(action, inv); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoSurroundScale::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoSurroundScale::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoSurroundScale::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoSurroundScale::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoSurroundScale::getMatrix(action); }
inline void py_q_pick(SoPickAction*  action) { SoSurroundScale::pick(action); }
};

class PythonQtWrapper_SoSurroundScale : public QObject
{ Q_OBJECT
public:
public slots:
SoSurroundScale* new_SoSurroundScale();
   void py_q_GLRender(SoSurroundScale* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoSurroundScale*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoSurroundScale* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoSurroundScale*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoSurroundScale* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoSurroundScale*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoSurroundScale* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoSurroundScale*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoSurroundScale_getClassTypeId();
   void py_q_getMatrix(SoSurroundScale* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoSurroundScale*)theWrappedObject)->py_q_getMatrix(action));}
   void invalidate(SoSurroundScale* theWrappedObject);
   bool  isDoingTranslations(SoSurroundScale* theWrappedObject);
   bool  isIgnoreInBbox(SoSurroundScale* theWrappedObject);
   void py_q_pick(SoSurroundScale* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoSurroundScale*)theWrappedObject)->py_q_pick(action));}
   void setDoingTranslations(SoSurroundScale* theWrappedObject, bool  doEm);
   void setIgnoreInBbox(SoSurroundScale* theWrappedObject, bool  newVal);
   void updateMySurroundParams(SoSurroundScale* theWrappedObject, SoAction*  action, const SbMatrix&  inv);
SoSFInt32*  py_get_numNodesUpToContainer(SoSurroundScale* theWrappedObject){ return &theWrappedObject->numNodesUpToContainer; }
SoSFInt32*  py_get_numNodesUpToReset(SoSurroundScale* theWrappedObject){ return &theWrappedObject->numNodesUpToReset; }
};





class PythonQtShell_SoSwitch : public SoSwitch
{
public:
    PythonQtShell_SoSwitch():SoSwitch(),_wrapper(nullptr) {_type = getClassTypeId();
};
    PythonQtShell_SoSwitch(int  nChildren):SoSwitch(nChildren),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoSwitch() override;

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

class PythonQtPublicPromoter_SoSwitch : public SoSwitch
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoSwitch::GLRender(action); }
inline bool  py_q_affectsState() const { return SoSwitch::affectsState(); }
inline void py_q_callback(SoCallbackAction*  action) { SoSwitch::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoSwitch::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoSwitch::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoSwitch::getMatrix(action); }
inline void py_q_handleEvent(SoHandleEventAction*  action) { SoSwitch::handleEvent(action); }
inline void py_q_pick(SoPickAction*  action) { SoSwitch::pick(action); }
inline void py_q_search(SoSearchAction*  action) { SoSwitch::search(action); }
inline void py_q_write(SoWriteAction*  action) { SoSwitch::write(action); }
};

class PythonQtWrapper_SoSwitch : public QObject
{ Q_OBJECT
public:
public slots:
SoSwitch* new_SoSwitch();
SoSwitch* new_SoSwitch(int  nChildren);
   void py_q_GLRender(SoSwitch* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoSwitch*)theWrappedObject)->py_q_GLRender(action));}
   bool  py_q_affectsState(SoSwitch* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoSwitch*)theWrappedObject)->py_q_affectsState());}
   void py_q_callback(SoSwitch* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoSwitch*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoSwitch* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoSwitch*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoSwitch* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoSwitch*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoSwitch_getClassTypeId();
   void py_q_getMatrix(SoSwitch* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoSwitch*)theWrappedObject)->py_q_getMatrix(action));}
   void py_q_handleEvent(SoSwitch* theWrappedObject, SoHandleEventAction*  action){  (((PythonQtPublicPromoter_SoSwitch*)theWrappedObject)->py_q_handleEvent(action));}
   void py_q_pick(SoSwitch* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoSwitch*)theWrappedObject)->py_q_pick(action));}
   void py_q_search(SoSwitch* theWrappedObject, SoSearchAction*  action){  (((PythonQtPublicPromoter_SoSwitch*)theWrappedObject)->py_q_search(action));}
   void py_q_write(SoSwitch* theWrappedObject, SoWriteAction*  action){  (((PythonQtPublicPromoter_SoSwitch*)theWrappedObject)->py_q_write(action));}
SoSFInt32*  py_get_whichChild(SoSwitch* theWrappedObject){ return &theWrappedObject->whichChild; }
};





class PythonQtShell_SoText2 : public SoText2
{
public:
    PythonQtShell_SoText2():SoText2(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoText2() override;

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

class PythonQtPublicPromoter_SoText2 : public SoText2
{ public:
inline void promoted_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { this->computeBBox(action, box, center); }
inline void promoted_generatePrimitives(SoAction*  action) { this->generatePrimitives(action); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoText2::GLRender(action); }
inline void py_q_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { SoText2::computeBBox(action, box, center); }
inline void py_q_generatePrimitives(SoAction*  action) { SoText2::generatePrimitives(action); }
inline void py_q_rayPick(SoRayPickAction*  action) { SoText2::rayPick(action); }
};

class PythonQtWrapper_SoText2 : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Justification )
enum Justification{
  LEFT = SoText2::LEFT,   RIGHT = SoText2::RIGHT,   CENTER = SoText2::CENTER};
public slots:
SoText2* new_SoText2();
   void py_q_GLRender(SoText2* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoText2*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_computeBBox(SoText2* theWrappedObject, SoAction*  action, SbBox3f&  box, SbVec3f&  center){  (((PythonQtPublicPromoter_SoText2*)theWrappedObject)->py_q_computeBBox(action, box, center));}
   void py_q_generatePrimitives(SoText2* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoText2*)theWrappedObject)->py_q_generatePrimitives(action));}
   SoType  static_SoText2_getClassTypeId();
   void py_q_rayPick(SoText2* theWrappedObject, SoRayPickAction*  action){  (((PythonQtPublicPromoter_SoText2*)theWrappedObject)->py_q_rayPick(action));}
SoSFEnum*  py_get_justification(SoText2* theWrappedObject){ return &theWrappedObject->justification; }
SoSFFloat*  py_get_spacing(SoText2* theWrappedObject){ return &theWrappedObject->spacing; }
SoMFString*  py_get_string(SoText2* theWrappedObject){ return &theWrappedObject->string; }
};





class PythonQtShell_SoText3 : public SoText3
{
public:
    PythonQtShell_SoText3():SoText3(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoText3() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) override;
SoDetail*  createLineSegmentDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, SoPickedPoint*  pp) override;
SoDetail*  createPointDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v, SoPickedPoint*  pp) override;
void doAction(SoAction*  action) override;
void generatePrimitives(SoAction*  arg__1) override;
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

class PythonQtPublicPromoter_SoText3 : public SoText3
{ public:
inline void promoted_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { this->computeBBox(action, box, center); }
inline void promoted_generatePrimitives(SoAction*  arg__1) { this->generatePrimitives(arg__1); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoText3::GLRender(action); }
inline void py_q_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { SoText3::computeBBox(action, box, center); }
inline void py_q_generatePrimitives(SoAction*  arg__1) { SoText3::generatePrimitives(arg__1); }
inline void py_q_rayPick(SoRayPickAction*  action) { SoText3::rayPick(action); }
};

class PythonQtWrapper_SoText3 : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Justification Part )
enum Justification{
  LEFT = SoText3::LEFT,   RIGHT = SoText3::RIGHT,   CENTER = SoText3::CENTER};
enum Part{
  FRONT = SoText3::FRONT,   SIDES = SoText3::SIDES,   BACK = SoText3::BACK,   ALL = SoText3::ALL};
public slots:
SoText3* new_SoText3();
   void py_q_GLRender(SoText3* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoText3*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_computeBBox(SoText3* theWrappedObject, SoAction*  action, SbBox3f&  box, SbVec3f&  center){  (((PythonQtPublicPromoter_SoText3*)theWrappedObject)->py_q_computeBBox(action, box, center));}
   void py_q_generatePrimitives(SoText3* theWrappedObject, SoAction*  arg__1){  (((PythonQtPublicPromoter_SoText3*)theWrappedObject)->py_q_generatePrimitives(arg__1));}
   SbBox3f  getCharacterBounds(SoText3* theWrappedObject, SoState*  state, int  stringIndex, int  charIndex);
   SoType  static_SoText3_getClassTypeId();
   void py_q_rayPick(SoText3* theWrappedObject, SoRayPickAction*  action){  (((PythonQtPublicPromoter_SoText3*)theWrappedObject)->py_q_rayPick(action));}
SoSFEnum*  py_get_justification(SoText3* theWrappedObject){ return &theWrappedObject->justification; }
SoSFBitMask*  py_get_parts(SoText3* theWrappedObject){ return &theWrappedObject->parts; }
SoSFFloat*  py_get_spacing(SoText3* theWrappedObject){ return &theWrappedObject->spacing; }
SoMFString*  py_get_string(SoText3* theWrappedObject){ return &theWrappedObject->string; }
};





class PythonQtShell_SoTexture2 : public SoTexture2
{
public:
    PythonQtShell_SoTexture2():SoTexture2(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTexture2() override;

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

class PythonQtPublicPromoter_SoTexture2 : public SoTexture2
{ public:
inline int  promoted_getReadStatus() { return this->getReadStatus(); }
inline void promoted_setReadStatus(int  s) { this->setReadStatus(s); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoTexture2::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoTexture2::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoTexture2::doAction(action); }
};

class PythonQtWrapper_SoTexture2 : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Model Wrap )
enum Model{
  MODULATE = SoTexture2::MODULATE,   DECAL = SoTexture2::DECAL,   BLEND = SoTexture2::BLEND};
enum Wrap{
  REPEAT = SoTexture2::REPEAT,   CLAMP = SoTexture2::CLAMP};
public slots:
SoTexture2* new_SoTexture2();
   void py_q_GLRender(SoTexture2* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoTexture2*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoTexture2* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoTexture2*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoTexture2* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoTexture2*)theWrappedObject)->py_q_doAction(action));}
   SoType  static_SoTexture2_getClassTypeId();
   int  getReadStatus(SoTexture2* theWrappedObject);
   bool  static_SoTexture2_readImage(const SbString&  fname, int&  w, int&  h, int&  nc, unsigned char*&  bytes);
   void setReadStatus(SoTexture2* theWrappedObject, int  s);
SoSFColor*  py_get_blendColor(SoTexture2* theWrappedObject){ return &theWrappedObject->blendColor; }
SoSFString*  py_get_filename(SoTexture2* theWrappedObject){ return &theWrappedObject->filename; }
SoSFImage*  py_get_image(SoTexture2* theWrappedObject){ return &theWrappedObject->image; }
SoSFEnum*  py_get_model(SoTexture2* theWrappedObject){ return &theWrappedObject->model; }
SoSFEnum*  py_get_wrapS(SoTexture2* theWrappedObject){ return &theWrappedObject->wrapS; }
SoSFEnum*  py_get_wrapT(SoTexture2* theWrappedObject){ return &theWrappedObject->wrapT; }
};





class PythonQtShell_SoTexture2Transform : public SoTexture2Transform
{
public:
    PythonQtShell_SoTexture2Transform():SoTexture2Transform(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTexture2Transform() override;

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

class PythonQtPublicPromoter_SoTexture2Transform : public SoTexture2Transform
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoTexture2Transform::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoTexture2Transform::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoTexture2Transform::doAction(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoTexture2Transform::getMatrix(action); }
inline void py_q_pick(SoPickAction*  action) { SoTexture2Transform::pick(action); }
};

class PythonQtWrapper_SoTexture2Transform : public QObject
{ Q_OBJECT
public:
public slots:
SoTexture2Transform* new_SoTexture2Transform();
   void py_q_GLRender(SoTexture2Transform* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoTexture2Transform*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoTexture2Transform* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoTexture2Transform*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoTexture2Transform* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoTexture2Transform*)theWrappedObject)->py_q_doAction(action));}
   SoType  static_SoTexture2Transform_getClassTypeId();
   void py_q_getMatrix(SoTexture2Transform* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoTexture2Transform*)theWrappedObject)->py_q_getMatrix(action));}
   void py_q_pick(SoTexture2Transform* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoTexture2Transform*)theWrappedObject)->py_q_pick(action));}
SoSFVec2f*  py_get_center(SoTexture2Transform* theWrappedObject){ return &theWrappedObject->center; }
SoSFFloat*  py_get_rotation(SoTexture2Transform* theWrappedObject){ return &theWrappedObject->rotation; }
SoSFVec2f*  py_get_scaleFactor(SoTexture2Transform* theWrappedObject){ return &theWrappedObject->scaleFactor; }
SoSFVec2f*  py_get_translation(SoTexture2Transform* theWrappedObject){ return &theWrappedObject->translation; }
};





class PythonQtShell_SoTextureCoordinate2 : public SoTextureCoordinate2
{
public:
    PythonQtShell_SoTextureCoordinate2():SoTextureCoordinate2(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTextureCoordinate2() override;

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

class PythonQtPublicPromoter_SoTextureCoordinate2 : public SoTextureCoordinate2
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoTextureCoordinate2::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoTextureCoordinate2::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoTextureCoordinate2::doAction(action); }
inline void py_q_pick(SoPickAction*  action) { SoTextureCoordinate2::pick(action); }
};

class PythonQtWrapper_SoTextureCoordinate2 : public QObject
{ Q_OBJECT
public:
public slots:
SoTextureCoordinate2* new_SoTextureCoordinate2();
   void py_q_GLRender(SoTextureCoordinate2* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoTextureCoordinate2*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoTextureCoordinate2* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoTextureCoordinate2*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoTextureCoordinate2* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoTextureCoordinate2*)theWrappedObject)->py_q_doAction(action));}
   SoType  static_SoTextureCoordinate2_getClassTypeId();
   void py_q_pick(SoTextureCoordinate2* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoTextureCoordinate2*)theWrappedObject)->py_q_pick(action));}
SoMFVec2f*  py_get_point(SoTextureCoordinate2* theWrappedObject){ return &theWrappedObject->point; }
};





class PythonQtShell_SoTextureCoordinateBinding : public SoTextureCoordinateBinding
{
public:
    PythonQtShell_SoTextureCoordinateBinding():SoTextureCoordinateBinding(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTextureCoordinateBinding() override;

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

class PythonQtPublicPromoter_SoTextureCoordinateBinding : public SoTextureCoordinateBinding
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoTextureCoordinateBinding::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoTextureCoordinateBinding::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoTextureCoordinateBinding::doAction(action); }
inline void py_q_pick(SoPickAction*  action) { SoTextureCoordinateBinding::pick(action); }
};

class PythonQtWrapper_SoTextureCoordinateBinding : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Binding )
enum Binding{
  PER_VERTEX = SoTextureCoordinateBinding::PER_VERTEX,   PER_VERTEX_INDEXED = SoTextureCoordinateBinding::PER_VERTEX_INDEXED};
public slots:
SoTextureCoordinateBinding* new_SoTextureCoordinateBinding();
   void py_q_GLRender(SoTextureCoordinateBinding* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoTextureCoordinateBinding*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoTextureCoordinateBinding* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoTextureCoordinateBinding*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoTextureCoordinateBinding* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoTextureCoordinateBinding*)theWrappedObject)->py_q_doAction(action));}
   SoType  static_SoTextureCoordinateBinding_getClassTypeId();
   void py_q_pick(SoTextureCoordinateBinding* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoTextureCoordinateBinding*)theWrappedObject)->py_q_pick(action));}
SoSFEnum*  py_get_value(SoTextureCoordinateBinding* theWrappedObject){ return &theWrappedObject->value; }
};





class PythonQtShell_SoTextureCoordinateDefault : public SoTextureCoordinateDefault
{
public:
    PythonQtShell_SoTextureCoordinateDefault():SoTextureCoordinateDefault(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTextureCoordinateDefault() override;

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

class PythonQtPublicPromoter_SoTextureCoordinateDefault : public SoTextureCoordinateDefault
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoTextureCoordinateDefault::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoTextureCoordinateDefault::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoTextureCoordinateDefault::doAction(action); }
inline void py_q_pick(SoPickAction*  action) { SoTextureCoordinateDefault::pick(action); }
};

class PythonQtWrapper_SoTextureCoordinateDefault : public QObject
{ Q_OBJECT
public:
public slots:
SoTextureCoordinateDefault* new_SoTextureCoordinateDefault();
   void py_q_GLRender(SoTextureCoordinateDefault* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoTextureCoordinateDefault*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoTextureCoordinateDefault* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoTextureCoordinateDefault*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoTextureCoordinateDefault* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoTextureCoordinateDefault*)theWrappedObject)->py_q_doAction(action));}
   SoType  static_SoTextureCoordinateDefault_getClassTypeId();
   void py_q_pick(SoTextureCoordinateDefault* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoTextureCoordinateDefault*)theWrappedObject)->py_q_pick(action));}
};





class PythonQtShell_SoTextureCoordinateEnvironment : public SoTextureCoordinateEnvironment
{
public:
    PythonQtShell_SoTextureCoordinateEnvironment():SoTextureCoordinateEnvironment(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTextureCoordinateEnvironment() override;

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

class PythonQtPublicPromoter_SoTextureCoordinateEnvironment : public SoTextureCoordinateEnvironment
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoTextureCoordinateEnvironment::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoTextureCoordinateEnvironment::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoTextureCoordinateEnvironment::doAction(action); }
inline void py_q_pick(SoPickAction*  action) { SoTextureCoordinateEnvironment::pick(action); }
};

class PythonQtWrapper_SoTextureCoordinateEnvironment : public QObject
{ Q_OBJECT
public:
public slots:
SoTextureCoordinateEnvironment* new_SoTextureCoordinateEnvironment();
   void py_q_GLRender(SoTextureCoordinateEnvironment* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoTextureCoordinateEnvironment*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoTextureCoordinateEnvironment* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoTextureCoordinateEnvironment*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoTextureCoordinateEnvironment* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoTextureCoordinateEnvironment*)theWrappedObject)->py_q_doAction(action));}
   SoType  static_SoTextureCoordinateEnvironment_getClassTypeId();
   void py_q_pick(SoTextureCoordinateEnvironment* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoTextureCoordinateEnvironment*)theWrappedObject)->py_q_pick(action));}
};





class PythonQtShell_SoTextureCoordinateFunction : public SoTextureCoordinateFunction
{
public:
    PythonQtShell_SoTextureCoordinateFunction():SoTextureCoordinateFunction(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTextureCoordinateFunction() override;

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

class PythonQtWrapper_SoTextureCoordinateFunction : public QObject
{ Q_OBJECT
public:
public slots:
SoTextureCoordinateFunction* new_SoTextureCoordinateFunction();
   SoType  static_SoTextureCoordinateFunction_getClassTypeId();
};





class PythonQtShell_SoTextureCoordinatePlane : public SoTextureCoordinatePlane
{
public:
    PythonQtShell_SoTextureCoordinatePlane():SoTextureCoordinatePlane(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTextureCoordinatePlane() override;

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

class PythonQtPublicPromoter_SoTextureCoordinatePlane : public SoTextureCoordinatePlane
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoTextureCoordinatePlane::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoTextureCoordinatePlane::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoTextureCoordinatePlane::doAction(action); }
inline void py_q_pick(SoPickAction*  action) { SoTextureCoordinatePlane::pick(action); }
};

class PythonQtWrapper_SoTextureCoordinatePlane : public QObject
{ Q_OBJECT
public:
public slots:
SoTextureCoordinatePlane* new_SoTextureCoordinatePlane();
   void py_q_GLRender(SoTextureCoordinatePlane* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoTextureCoordinatePlane*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoTextureCoordinatePlane* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoTextureCoordinatePlane*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoTextureCoordinatePlane* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoTextureCoordinatePlane*)theWrappedObject)->py_q_doAction(action));}
   SoType  static_SoTextureCoordinatePlane_getClassTypeId();
   void py_q_pick(SoTextureCoordinatePlane* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoTextureCoordinatePlane*)theWrappedObject)->py_q_pick(action));}
SoSFVec3f*  py_get_directionS(SoTextureCoordinatePlane* theWrappedObject){ return &theWrappedObject->directionS; }
SoSFVec3f*  py_get_directionT(SoTextureCoordinatePlane* theWrappedObject){ return &theWrappedObject->directionT; }
};





class PythonQtShell_SoTransform : public SoTransform
{
public:
    PythonQtShell_SoTransform():SoTransform(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTransform() override;

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

class PythonQtPublicPromoter_SoTransform : public SoTransform
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoTransform::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoTransform::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoTransform::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoTransform::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoTransform::getMatrix(action); }
inline void py_q_pick(SoPickAction*  action) { SoTransform::pick(action); }
};

class PythonQtWrapper_SoTransform : public QObject
{ Q_OBJECT
public:
public slots:
SoTransform* new_SoTransform();
   void py_q_GLRender(SoTransform* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoTransform*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoTransform* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoTransform*)theWrappedObject)->py_q_callback(action));}
   void combineLeft(SoTransform* theWrappedObject, SoTransformation*  nodeOnLeft);
   void combineRight(SoTransform* theWrappedObject, SoTransformation*  nodeOnRight);
   void py_q_doAction(SoTransform* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoTransform*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoTransform* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoTransform*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoTransform_getClassTypeId();
   void py_q_getMatrix(SoTransform* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoTransform*)theWrappedObject)->py_q_getMatrix(action));}
   void getRotationSpaceMatrix(SoTransform* theWrappedObject, SbMatrix&  mat, SbMatrix&  inv) const;
   void getScaleSpaceMatrix(SoTransform* theWrappedObject, SbMatrix&  mat, SbMatrix&  inv) const;
   void getTranslationSpaceMatrix(SoTransform* theWrappedObject, SbMatrix&  mat, SbMatrix&  inv) const;
   void multLeft(SoTransform* theWrappedObject, const SbMatrix&  mat);
   void multRight(SoTransform* theWrappedObject, const SbMatrix&  mat);
   void py_q_pick(SoTransform* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoTransform*)theWrappedObject)->py_q_pick(action));}
   void pointAt(SoTransform* theWrappedObject, const SbVec3f&  fromPoint, const SbVec3f&  toPoint);
   void recenter(SoTransform* theWrappedObject, const SbVec3f&  newCenter);
   void setMatrix(SoTransform* theWrappedObject, const SbMatrix&  mat);
SoSFVec3f*  py_get_center(SoTransform* theWrappedObject){ return &theWrappedObject->center; }
SoSFRotation*  py_get_rotation(SoTransform* theWrappedObject){ return &theWrappedObject->rotation; }
SoSFVec3f*  py_get_scaleFactor(SoTransform* theWrappedObject){ return &theWrappedObject->scaleFactor; }
SoSFRotation*  py_get_scaleOrientation(SoTransform* theWrappedObject){ return &theWrappedObject->scaleOrientation; }
SoSFVec3f*  py_get_translation(SoTransform* theWrappedObject){ return &theWrappedObject->translation; }
};





class PythonQtShell_SoTransformSeparator : public SoTransformSeparator
{
public:
    PythonQtShell_SoTransformSeparator():SoTransformSeparator(),_wrapper(nullptr) {_type = getClassTypeId();
};
    PythonQtShell_SoTransformSeparator(int  nChildren):SoTransformSeparator(nChildren),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTransformSeparator() override;

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

class PythonQtPublicPromoter_SoTransformSeparator : public SoTransformSeparator
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoTransformSeparator::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoTransformSeparator::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoTransformSeparator::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoTransformSeparator::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoTransformSeparator::getMatrix(action); }
inline void py_q_pick(SoPickAction*  action) { SoTransformSeparator::pick(action); }
};

class PythonQtWrapper_SoTransformSeparator : public QObject
{ Q_OBJECT
public:
public slots:
SoTransformSeparator* new_SoTransformSeparator();
SoTransformSeparator* new_SoTransformSeparator(int  nChildren);
   void py_q_GLRender(SoTransformSeparator* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoTransformSeparator*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoTransformSeparator* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoTransformSeparator*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoTransformSeparator* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoTransformSeparator*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoTransformSeparator* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoTransformSeparator*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoTransformSeparator_getClassTypeId();
   void py_q_getMatrix(SoTransformSeparator* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoTransformSeparator*)theWrappedObject)->py_q_getMatrix(action));}
   void py_q_pick(SoTransformSeparator* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoTransformSeparator*)theWrappedObject)->py_q_pick(action));}
};


