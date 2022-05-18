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
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoTransformation.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoTriangleStripSet.h>
#include <Inventor/nodes/SoUnits.h>
#include <Inventor/nodes/SoVertexProperty.h>
#include <Inventor/nodes/SoVertexShape.h>
#include <Inventor/sensors/SoSensor.h>
#include <stdexcept>



class PythonQtShell_SoTransformation : public SoTransformation
{
public:
    PythonQtShell_SoTransformation():SoTransformation(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTransformation() override;

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

class PythonQtWrapper_SoTransformation : public QObject
{ Q_OBJECT
public:
public slots:
SoTransformation* new_SoTransformation();
   SoType  static_SoTransformation_getClassTypeId();
};





class PythonQtShell_SoTranslation : public SoTranslation
{
public:
    PythonQtShell_SoTranslation():SoTranslation(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTranslation() override;

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

class PythonQtPublicPromoter_SoTranslation : public SoTranslation
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoTranslation::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoTranslation::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoTranslation::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoTranslation::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoTranslation::getMatrix(action); }
inline void py_q_pick(SoPickAction*  action) { SoTranslation::pick(action); }
};

class PythonQtWrapper_SoTranslation : public QObject
{ Q_OBJECT
public:
public slots:
SoTranslation* new_SoTranslation();
   void py_q_GLRender(SoTranslation* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoTranslation*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoTranslation* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoTranslation*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoTranslation* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoTranslation*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoTranslation* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoTranslation*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoTranslation_getClassTypeId();
   void py_q_getMatrix(SoTranslation* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoTranslation*)theWrappedObject)->py_q_getMatrix(action));}
   void py_q_pick(SoTranslation* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoTranslation*)theWrappedObject)->py_q_pick(action));}
SoSFVec3f*  py_get_translation(SoTranslation* theWrappedObject){ return &theWrappedObject->translation; }
};





class PythonQtShell_SoTriangleStripSet : public SoTriangleStripSet
{
public:
    PythonQtShell_SoTriangleStripSet():SoTriangleStripSet(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTriangleStripSet() override;

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

class PythonQtPublicPromoter_SoTriangleStripSet : public SoTriangleStripSet
{ public:
inline void promoted_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { this->computeBBox(action, box, center); }
inline SoDetail*  promoted_createTriangleDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp) { return this->createTriangleDetail(action, v1, v2, v3, pp); }
inline void promoted_generatePrimitives(SoAction*  action) { this->generatePrimitives(action); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoTriangleStripSet::GLRender(action); }
inline void py_q_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { SoTriangleStripSet::computeBBox(action, box, center); }
inline SoDetail*  py_q_createTriangleDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp) { return SoTriangleStripSet::createTriangleDetail(action, v1, v2, v3, pp); }
inline void py_q_generatePrimitives(SoAction*  action) { SoTriangleStripSet::generatePrimitives(action); }
};

class PythonQtWrapper_SoTriangleStripSet : public QObject
{ Q_OBJECT
public:
public slots:
SoTriangleStripSet* new_SoTriangleStripSet();
   void py_q_GLRender(SoTriangleStripSet* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoTriangleStripSet*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_computeBBox(SoTriangleStripSet* theWrappedObject, SoAction*  action, SbBox3f&  box, SbVec3f&  center){  (((PythonQtPublicPromoter_SoTriangleStripSet*)theWrappedObject)->py_q_computeBBox(action, box, center));}
   SoDetail*  py_q_createTriangleDetail(SoTriangleStripSet* theWrappedObject, SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp){  return (((PythonQtPublicPromoter_SoTriangleStripSet*)theWrappedObject)->py_q_createTriangleDetail(action, v1, v2, v3, pp));}
   void py_q_generatePrimitives(SoTriangleStripSet* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoTriangleStripSet*)theWrappedObject)->py_q_generatePrimitives(action));}
   SoType  static_SoTriangleStripSet_getClassTypeId();
SoMFInt32*  py_get_numVertices(SoTriangleStripSet* theWrappedObject){ return &theWrappedObject->numVertices; }
};





class PythonQtShell_SoUnits : public SoUnits
{
public:
    PythonQtShell_SoUnits():SoUnits(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoUnits() override;

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

class PythonQtPublicPromoter_SoUnits : public SoUnits
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoUnits::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoUnits::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoUnits::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoUnits::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoUnits::getMatrix(action); }
inline void py_q_pick(SoPickAction*  action) { SoUnits::pick(action); }
};

class PythonQtWrapper_SoUnits : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Units )
enum Units{
  METERS = SoUnits::METERS,   CENTIMETERS = SoUnits::CENTIMETERS,   MILLIMETERS = SoUnits::MILLIMETERS,   MICROMETERS = SoUnits::MICROMETERS,   MICRONS = SoUnits::MICRONS,   NANOMETERS = SoUnits::NANOMETERS,   ANGSTROMS = SoUnits::ANGSTROMS,   KILOMETERS = SoUnits::KILOMETERS,   FEET = SoUnits::FEET,   INCHES = SoUnits::INCHES,   POINTS = SoUnits::POINTS,   YARDS = SoUnits::YARDS,   MILES = SoUnits::MILES,   NAUTICAL_MILES = SoUnits::NAUTICAL_MILES};
public slots:
SoUnits* new_SoUnits();
   void py_q_GLRender(SoUnits* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoUnits*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoUnits* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoUnits*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoUnits* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoUnits*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoUnits* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoUnits*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoUnits_getClassTypeId();
   void py_q_getMatrix(SoUnits* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoUnits*)theWrappedObject)->py_q_getMatrix(action));}
   void py_q_pick(SoUnits* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoUnits*)theWrappedObject)->py_q_pick(action));}
SoSFEnum*  py_get_units(SoUnits* theWrappedObject){ return &theWrappedObject->units; }
};





class PythonQtShell_SoVertexProperty : public SoVertexProperty
{
public:
    PythonQtShell_SoVertexProperty():SoVertexProperty(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoVertexProperty() override;

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

class PythonQtPublicPromoter_SoVertexProperty : public SoVertexProperty
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoVertexProperty::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoVertexProperty::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoVertexProperty::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoVertexProperty::getBoundingBox(action); }
inline void py_q_pick(SoPickAction*  action) { SoVertexProperty::pick(action); }
};

class PythonQtWrapper_SoVertexProperty : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Binding )
enum Binding{
  OVERALL = SoVertexProperty::OVERALL,   PER_PART = SoVertexProperty::PER_PART,   PER_PART_INDEXED = SoVertexProperty::PER_PART_INDEXED,   PER_FACE = SoVertexProperty::PER_FACE,   PER_FACE_INDEXED = SoVertexProperty::PER_FACE_INDEXED,   PER_VERTEX = SoVertexProperty::PER_VERTEX,   PER_VERTEX_INDEXED = SoVertexProperty::PER_VERTEX_INDEXED};
public slots:
SoVertexProperty* new_SoVertexProperty();
   void py_q_GLRender(SoVertexProperty* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoVertexProperty*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoVertexProperty* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoVertexProperty*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoVertexProperty* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoVertexProperty*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoVertexProperty* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoVertexProperty*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoVertexProperty_getClassTypeId();
   void py_q_pick(SoVertexProperty* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoVertexProperty*)theWrappedObject)->py_q_pick(action));}
   void putVBOsIntoState(SoVertexProperty* theWrappedObject, SoState*  state);
SoSFEnum*  py_get_materialBinding(SoVertexProperty* theWrappedObject){ return &theWrappedObject->materialBinding; }
SoMFVec3f*  py_get_normal(SoVertexProperty* theWrappedObject){ return &theWrappedObject->normal; }
SoSFEnum*  py_get_normalBinding(SoVertexProperty* theWrappedObject){ return &theWrappedObject->normalBinding; }
SoMFUInt32*  py_get_orderedRGBA(SoVertexProperty* theWrappedObject){ return &theWrappedObject->orderedRGBA; }
SoMFVec2f*  py_get_texCoord(SoVertexProperty* theWrappedObject){ return &theWrappedObject->texCoord; }
SoMFVec3f*  py_get_vertex(SoVertexProperty* theWrappedObject){ return &theWrappedObject->vertex; }
};





class PythonQtShell_SoVertexShape : public SoVertexShape
{
public:
    PythonQtShell_SoVertexShape():SoVertexShape(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoVertexShape() override;

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

class PythonQtPublicPromoter_SoVertexShape : public SoVertexShape
{ public:
inline bool  promoted_beginVertexArrayRendering(SoGLRenderAction*  action) { return this->beginVertexArrayRendering(action); }
inline void promoted_endVertexArrayRendering(SoGLRenderAction*  action, bool  vboWasUsed) { this->endVertexArrayRendering(action, vboWasUsed); }
inline SoVertexProperty*  promoted_getVertexProperty() { return this->getVertexProperty(); }
inline void promoted_setNormalCache(SoState*  state, int  numNormals, const SbVec3f*  normals) { this->setNormalCache(state, numNormals, normals); }
inline bool  promoted_shouldGLRender(SoGLRenderAction*  action) { return this->shouldGLRender(action); }
inline bool  py_q_shouldGLRender(SoGLRenderAction*  action) { return SoVertexShape::shouldGLRender(action); }
};

class PythonQtWrapper_SoVertexShape : public QObject
{ Q_OBJECT
public:
public slots:
SoVertexShape* new_SoVertexShape();
   bool  beginVertexArrayRendering(SoVertexShape* theWrappedObject, SoGLRenderAction*  action);
   void endVertexArrayRendering(SoVertexShape* theWrappedObject, SoGLRenderAction*  action, bool  vboWasUsed);
   SoType  static_SoVertexShape_getClassTypeId();
   SoVertexProperty*  getVertexProperty(SoVertexShape* theWrappedObject);
   void setNormalCache(SoVertexShape* theWrappedObject, SoState*  state, int  numNormals, const SbVec3f*  normals);
   bool  py_q_shouldGLRender(SoVertexShape* theWrappedObject, SoGLRenderAction*  action){  return (((PythonQtPublicPromoter_SoVertexShape*)theWrappedObject)->py_q_shouldGLRender(action));}
SoSFNode*  py_get_vertexProperty(SoVertexShape* theWrappedObject){ return &theWrappedObject->vertexProperty; }
};


