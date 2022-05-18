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
#include <Inventor/events/SoEvent.h>
#include <Inventor/fields/SoField.h>
#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/misc/SoBase.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/nodes/SoAnnotation.h>
#include <Inventor/nodes/SoAntiSquish.h>
#include <Inventor/nodes/SoArray.h>
#include <Inventor/nodes/SoAsciiText.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoBlinker.h>
#include <Inventor/nodes/SoCallback.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/nodes/SoClipPlane.h>
#include <Inventor/nodes/SoComplexity.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoCoordinate4.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoEnvironment.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/nodes/SoFile.h>
#include <Inventor/nodes/SoFont.h>
#include <Inventor/nodes/SoFontStyle.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoIndexedNurbsCurve.h>
#include <Inventor/nodes/SoIndexedNurbsSurface.h>
#include <Inventor/nodes/SoIndexedShape.h>
#include <Inventor/nodes/SoIndexedTriangleSet.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoVertexProperty.h>
#include <Inventor/sensors/SoSensor.h>
#include <stdexcept>



class PythonQtShell_SoAnnotation : public SoAnnotation
{
public:
    PythonQtShell_SoAnnotation():SoAnnotation(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoAnnotation() override;

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

class PythonQtPublicPromoter_SoAnnotation : public SoAnnotation
{ public:
inline void py_q_GLRenderBelowPath(SoGLRenderAction*  action) { SoAnnotation::GLRenderBelowPath(action); }
inline void py_q_GLRenderInPath(SoGLRenderAction*  action) { SoAnnotation::GLRenderInPath(action); }
};

class PythonQtWrapper_SoAnnotation : public QObject
{ Q_OBJECT
public:
public slots:
SoAnnotation* new_SoAnnotation();
   void py_q_GLRenderBelowPath(SoAnnotation* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoAnnotation*)theWrappedObject)->py_q_GLRenderBelowPath(action));}
   void py_q_GLRenderInPath(SoAnnotation* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoAnnotation*)theWrappedObject)->py_q_GLRenderInPath(action));}
   SoType  static_SoAnnotation_getClassTypeId();
SoSFBool*  py_get_clearDepthBuffer(SoAnnotation* theWrappedObject){ return &theWrappedObject->clearDepthBuffer; }
SoSFBool*  py_get_disableDepthBuffer(SoAnnotation* theWrappedObject){ return &theWrappedObject->disableDepthBuffer; }
};





class PythonQtShell_SoAntiSquish : public SoAntiSquish
{
public:
    PythonQtShell_SoAntiSquish():SoAntiSquish(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoAntiSquish() override;

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

class PythonQtPublicPromoter_SoAntiSquish : public SoAntiSquish
{ public:
inline void promoted_GLRender(SoGLRenderAction*  action) { this->GLRender(action); }
inline void promoted_callback(SoCallbackAction*  action) { this->callback(action); }
inline void promoted_getBoundingBox(SoGetBoundingBoxAction*  action) { this->getBoundingBox(action); }
inline void promoted_getMatrix(SoGetMatrixAction*  action) { this->getMatrix(action); }
inline SbMatrix  promoted_getUnsquishingMatrix(SbMatrix  squishedMatrix, bool  doInverse, SbMatrix&  inverseAnswer) { return this->getUnsquishingMatrix(squishedMatrix, doInverse, inverseAnswer); }
inline void promoted_pick(SoPickAction*  action) { this->pick(action); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoAntiSquish::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoAntiSquish::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoAntiSquish::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoAntiSquish::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoAntiSquish::getMatrix(action); }
inline void py_q_pick(SoPickAction*  action) { SoAntiSquish::pick(action); }
};

class PythonQtWrapper_SoAntiSquish : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Sizing )
enum Sizing{
  X = SoAntiSquish::X,   Y = SoAntiSquish::Y,   Z = SoAntiSquish::Z,   AVERAGE_DIMENSION = SoAntiSquish::AVERAGE_DIMENSION,   BIGGEST_DIMENSION = SoAntiSquish::BIGGEST_DIMENSION,   SMALLEST_DIMENSION = SoAntiSquish::SMALLEST_DIMENSION,   LONGEST_DIAGONAL = SoAntiSquish::LONGEST_DIAGONAL};
public slots:
SoAntiSquish* new_SoAntiSquish();
   void py_q_GLRender(SoAntiSquish* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoAntiSquish*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoAntiSquish* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoAntiSquish*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoAntiSquish* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoAntiSquish*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoAntiSquish* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoAntiSquish*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoAntiSquish_getClassTypeId();
   void py_q_getMatrix(SoAntiSquish* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoAntiSquish*)theWrappedObject)->py_q_getMatrix(action));}
   SbMatrix  getUnsquishingMatrix(SoAntiSquish* theWrappedObject, SbMatrix  squishedMatrix, bool  doInverse, SbMatrix&  inverseAnswer);
   void py_q_pick(SoAntiSquish* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoAntiSquish*)theWrappedObject)->py_q_pick(action));}
   void recalc(SoAntiSquish* theWrappedObject);
SoSFBool*  py_get_recalcAlways(SoAntiSquish* theWrappedObject){ return &theWrappedObject->recalcAlways; }
SoSFEnum*  py_get_sizing(SoAntiSquish* theWrappedObject){ return &theWrappedObject->sizing; }
};





class PythonQtShell_SoArray : public SoArray
{
public:
    PythonQtShell_SoArray():SoArray(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoArray() override;

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

class PythonQtPublicPromoter_SoArray : public SoArray
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoArray::GLRender(action); }
inline bool  py_q_affectsState() const { return SoArray::affectsState(); }
inline void py_q_callback(SoCallbackAction*  action) { SoArray::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoArray::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoArray::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoArray::getMatrix(action); }
inline void py_q_handleEvent(SoHandleEventAction*  action) { SoArray::handleEvent(action); }
inline void py_q_pick(SoPickAction*  action) { SoArray::pick(action); }
inline void py_q_search(SoSearchAction*  action) { SoArray::search(action); }
};

class PythonQtWrapper_SoArray : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Origin )
enum Origin{
  FIRST = SoArray::FIRST,   CENTER = SoArray::CENTER,   LAST = SoArray::LAST};
public slots:
SoArray* new_SoArray();
   void py_q_GLRender(SoArray* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoArray*)theWrappedObject)->py_q_GLRender(action));}
   bool  py_q_affectsState(SoArray* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoArray*)theWrappedObject)->py_q_affectsState());}
   void py_q_callback(SoArray* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoArray*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoArray* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoArray*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoArray* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoArray*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoArray_getClassTypeId();
   void py_q_getMatrix(SoArray* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoArray*)theWrappedObject)->py_q_getMatrix(action));}
   void py_q_handleEvent(SoArray* theWrappedObject, SoHandleEventAction*  action){  (((PythonQtPublicPromoter_SoArray*)theWrappedObject)->py_q_handleEvent(action));}
   void py_q_pick(SoArray* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoArray*)theWrappedObject)->py_q_pick(action));}
   void py_q_search(SoArray* theWrappedObject, SoSearchAction*  action){  (((PythonQtPublicPromoter_SoArray*)theWrappedObject)->py_q_search(action));}
SoSFShort*  py_get_numElements1(SoArray* theWrappedObject){ return &theWrappedObject->numElements1; }
SoSFShort*  py_get_numElements2(SoArray* theWrappedObject){ return &theWrappedObject->numElements2; }
SoSFShort*  py_get_numElements3(SoArray* theWrappedObject){ return &theWrappedObject->numElements3; }
SoSFEnum*  py_get_origin(SoArray* theWrappedObject){ return &theWrappedObject->origin; }
SoSFVec3f*  py_get_separation1(SoArray* theWrappedObject){ return &theWrappedObject->separation1; }
SoSFVec3f*  py_get_separation2(SoArray* theWrappedObject){ return &theWrappedObject->separation2; }
SoSFVec3f*  py_get_separation3(SoArray* theWrappedObject){ return &theWrappedObject->separation3; }
};





class PythonQtShell_SoAsciiText : public SoAsciiText
{
public:
    PythonQtShell_SoAsciiText():SoAsciiText(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoAsciiText() override;

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

class PythonQtPublicPromoter_SoAsciiText : public SoAsciiText
{ public:
inline void promoted_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { this->computeBBox(action, box, center); }
inline void promoted_generatePrimitives(SoAction*  arg__1) { this->generatePrimitives(arg__1); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoAsciiText::GLRender(action); }
inline void py_q_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { SoAsciiText::computeBBox(action, box, center); }
inline void py_q_generatePrimitives(SoAction*  arg__1) { SoAsciiText::generatePrimitives(arg__1); }
inline void py_q_rayPick(SoRayPickAction*  action) { SoAsciiText::rayPick(action); }
};

class PythonQtWrapper_SoAsciiText : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Justification )
enum Justification{
  LEFT = SoAsciiText::LEFT,   RIGHT = SoAsciiText::RIGHT,   CENTER = SoAsciiText::CENTER};
public slots:
SoAsciiText* new_SoAsciiText();
   void py_q_GLRender(SoAsciiText* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoAsciiText*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_computeBBox(SoAsciiText* theWrappedObject, SoAction*  action, SbBox3f&  box, SbVec3f&  center){  (((PythonQtPublicPromoter_SoAsciiText*)theWrappedObject)->py_q_computeBBox(action, box, center));}
   void py_q_generatePrimitives(SoAsciiText* theWrappedObject, SoAction*  arg__1){  (((PythonQtPublicPromoter_SoAsciiText*)theWrappedObject)->py_q_generatePrimitives(arg__1));}
   SoType  static_SoAsciiText_getClassTypeId();
   void py_q_rayPick(SoAsciiText* theWrappedObject, SoRayPickAction*  action){  (((PythonQtPublicPromoter_SoAsciiText*)theWrappedObject)->py_q_rayPick(action));}
SoSFEnum*  py_get_justification(SoAsciiText* theWrappedObject){ return &theWrappedObject->justification; }
SoSFFloat*  py_get_spacing(SoAsciiText* theWrappedObject){ return &theWrappedObject->spacing; }
SoMFString*  py_get_string(SoAsciiText* theWrappedObject){ return &theWrappedObject->string; }
SoMFFloat*  py_get_width(SoAsciiText* theWrappedObject){ return &theWrappedObject->width; }
};





class PythonQtShell_SoBaseColor : public SoBaseColor
{
public:
    PythonQtShell_SoBaseColor():SoBaseColor(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoBaseColor() override;

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

class PythonQtPublicPromoter_SoBaseColor : public SoBaseColor
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoBaseColor::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoBaseColor::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoBaseColor::doAction(action); }
};

class PythonQtWrapper_SoBaseColor : public QObject
{ Q_OBJECT
public:
public slots:
SoBaseColor* new_SoBaseColor();
   void py_q_GLRender(SoBaseColor* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoBaseColor*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoBaseColor* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoBaseColor*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoBaseColor* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoBaseColor*)theWrappedObject)->py_q_doAction(action));}
   SoType  static_SoBaseColor_getClassTypeId();
SoMFColor*  py_get_rgb(SoBaseColor* theWrappedObject){ return &theWrappedObject->rgb; }
};





class PythonQtShell_SoBlinker : public SoBlinker
{
public:
    PythonQtShell_SoBlinker():SoBlinker(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoBlinker() override;

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

class PythonQtPublicPromoter_SoBlinker : public SoBlinker
{ public:
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoBlinker::getBoundingBox(action); }
inline void py_q_write(SoWriteAction*  action) { SoBlinker::write(action); }
};

class PythonQtWrapper_SoBlinker : public QObject
{ Q_OBJECT
public:
public slots:
SoBlinker* new_SoBlinker();
   void py_q_getBoundingBox(SoBlinker* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoBlinker*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoBlinker_getClassTypeId();
   void py_q_write(SoBlinker* theWrappedObject, SoWriteAction*  action){  (((PythonQtPublicPromoter_SoBlinker*)theWrappedObject)->py_q_write(action));}
SoSFBool*  py_get_on(SoBlinker* theWrappedObject){ return &theWrappedObject->on; }
SoSFFloat*  py_get_speed(SoBlinker* theWrappedObject){ return &theWrappedObject->speed; }
};





class PythonQtShell_SoCallback : public SoCallback
{
public:
    PythonQtShell_SoCallback():SoCallback(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoCallback() override;

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

class PythonQtPublicPromoter_SoCallback : public SoCallback
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoCallback::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoCallback::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoCallback::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoCallback::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoCallback::getMatrix(action); }
inline void py_q_handleEvent(SoHandleEventAction*  action) { SoCallback::handleEvent(action); }
inline void py_q_pick(SoPickAction*  action) { SoCallback::pick(action); }
inline void py_q_search(SoSearchAction*  action) { SoCallback::search(action); }
inline void py_q_write(SoWriteAction*  action) { SoCallback::write(action); }
};

class PythonQtWrapper_SoCallback : public QObject
{ Q_OBJECT
public:
public slots:
SoCallback* new_SoCallback();
   void py_q_GLRender(SoCallback* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoCallback*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoCallback* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoCallback*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoCallback* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoCallback*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoCallback* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoCallback*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoCallback_getClassTypeId();
   void py_q_getMatrix(SoCallback* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoCallback*)theWrappedObject)->py_q_getMatrix(action));}
   void py_q_handleEvent(SoCallback* theWrappedObject, SoHandleEventAction*  action){  (((PythonQtPublicPromoter_SoCallback*)theWrappedObject)->py_q_handleEvent(action));}
   void py_q_pick(SoCallback* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoCallback*)theWrappedObject)->py_q_pick(action));}
   void py_q_search(SoCallback* theWrappedObject, SoSearchAction*  action){  (((PythonQtPublicPromoter_SoCallback*)theWrappedObject)->py_q_search(action));}
   void py_q_write(SoCallback* theWrappedObject, SoWriteAction*  action){  (((PythonQtPublicPromoter_SoCallback*)theWrappedObject)->py_q_write(action));}
};





class PythonQtShell_SoCamera : public SoCamera
{
public:
    PythonQtShell_SoCamera():SoCamera(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoCamera() override;

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

class PythonQtPublicPromoter_SoCamera : public SoCamera
{ public:
inline void promoted_jitter(int  numPasses, int  curPass, const SbViewportRegion&  vpReg, SbVec3f&  jitterAmount) const { this->jitter(numPasses, curPass, vpReg, jitterAmount); }
inline void promoted_viewBoundingBox(const SbBox3f&  box, float  aspect, float  slack) { this->viewBoundingBox(box, aspect, slack); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoCamera::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoCamera::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoCamera::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoCamera::getBoundingBox(action); }
inline SbViewVolume  py_q_getViewVolume(float  useAspectRatio = 0.0) const { return this->getViewVolume(useAspectRatio); }
inline void py_q_handleEvent(SoHandleEventAction*  action) { SoCamera::handleEvent(action); }
inline void py_q_jitter(int  numPasses, int  curPass, const SbViewportRegion&  vpReg, SbVec3f&  jitterAmount) const { SoCamera::jitter(numPasses, curPass, vpReg, jitterAmount); }
inline void py_q_rayPick(SoRayPickAction*  action) { SoCamera::rayPick(action); }
inline void py_q_scaleHeight(float  scaleFactor) { this->scaleHeight(scaleFactor); }
inline void py_q_viewBoundingBox(const SbBox3f&  box, float  aspect, float  slack) { this->viewBoundingBox(box, aspect, slack); }
};

class PythonQtWrapper_SoCamera : public QObject
{ Q_OBJECT
public:
Q_ENUMS(ViewportMapping )
enum ViewportMapping{
  CROP_VIEWPORT_FILL_FRAME = SoCamera::CROP_VIEWPORT_FILL_FRAME,   CROP_VIEWPORT_LINE_FRAME = SoCamera::CROP_VIEWPORT_LINE_FRAME,   CROP_VIEWPORT_NO_FRAME = SoCamera::CROP_VIEWPORT_NO_FRAME,   ADJUST_CAMERA = SoCamera::ADJUST_CAMERA,   LEAVE_ALONE = SoCamera::LEAVE_ALONE};
public slots:
SoCamera* new_SoCamera();
   void py_q_GLRender(SoCamera* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoCamera*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoCamera* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoCamera*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoCamera* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoCamera*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoCamera* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoCamera*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoCamera_getClassTypeId();
   SbViewVolume  getViewVolume(SoCamera* theWrappedObject, float  useAspectRatio = 0.0) const;
   SbViewVolume  py_q_getViewVolume(SoCamera* theWrappedObject, float  useAspectRatio = 0.0) const{  return (((PythonQtPublicPromoter_SoCamera*)theWrappedObject)->py_q_getViewVolume(useAspectRatio));}
   SbViewportRegion  getViewportBounds(SoCamera* theWrappedObject, const SbViewportRegion&  region) const;
   void py_q_handleEvent(SoCamera* theWrappedObject, SoHandleEventAction*  action){  (((PythonQtPublicPromoter_SoCamera*)theWrappedObject)->py_q_handleEvent(action));}
   void jitter(SoCamera* theWrappedObject, int  numPasses, int  curPass, const SbViewportRegion&  vpReg, SbVec3f&  jitterAmount) const;
   void py_q_jitter(SoCamera* theWrappedObject, int  numPasses, int  curPass, const SbViewportRegion&  vpReg, SbVec3f&  jitterAmount) const{  (((PythonQtPublicPromoter_SoCamera*)theWrappedObject)->py_q_jitter(numPasses, curPass, vpReg, jitterAmount));}
   void pointAt(SoCamera* theWrappedObject, const SbVec3f&  targetPoint);
   void py_q_rayPick(SoCamera* theWrappedObject, SoRayPickAction*  action){  (((PythonQtPublicPromoter_SoCamera*)theWrappedObject)->py_q_rayPick(action));}
   void scaleHeight(SoCamera* theWrappedObject, float  scaleFactor);
   void py_q_scaleHeight(SoCamera* theWrappedObject, float  scaleFactor){  (((PythonQtPublicPromoter_SoCamera*)theWrappedObject)->py_q_scaleHeight(scaleFactor));}
   void viewAll(SoCamera* theWrappedObject, SoNode*  sceneRoot, const SbViewportRegion&  vpRegion, float  slack = 1.0);
   void viewAll(SoCamera* theWrappedObject, SoPath*  path, const SbViewportRegion&  vpRegion, float  slack = 1.0);
   void viewBoundingBox(SoCamera* theWrappedObject, const SbBox3f&  box, float  aspect, float  slack);
   void py_q_viewBoundingBox(SoCamera* theWrappedObject, const SbBox3f&  box, float  aspect, float  slack){  (((PythonQtPublicPromoter_SoCamera*)theWrappedObject)->py_q_viewBoundingBox(box, aspect, slack));}
SoSFFloat*  py_get_aspectRatio(SoCamera* theWrappedObject){ return &theWrappedObject->aspectRatio; }
SoSFFloat*  py_get_farDistance(SoCamera* theWrappedObject){ return &theWrappedObject->farDistance; }
SoSFFloat*  py_get_focalDistance(SoCamera* theWrappedObject){ return &theWrappedObject->focalDistance; }
SoSFFloat*  py_get_nearDistance(SoCamera* theWrappedObject){ return &theWrappedObject->nearDistance; }
SoSFRotation*  py_get_orientation(SoCamera* theWrappedObject){ return &theWrappedObject->orientation; }
SoSFVec3f*  py_get_position(SoCamera* theWrappedObject){ return &theWrappedObject->position; }
SoSFEnum*  py_get_viewportMapping(SoCamera* theWrappedObject){ return &theWrappedObject->viewportMapping; }
};





class PythonQtShell_SoClipPlane : public SoClipPlane
{
public:
    PythonQtShell_SoClipPlane():SoClipPlane(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoClipPlane() override;

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

class PythonQtPublicPromoter_SoClipPlane : public SoClipPlane
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoClipPlane::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoClipPlane::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoClipPlane::doAction(action); }
inline void py_q_pick(SoPickAction*  action) { SoClipPlane::pick(action); }
};

class PythonQtWrapper_SoClipPlane : public QObject
{ Q_OBJECT
public:
public slots:
SoClipPlane* new_SoClipPlane();
   void py_q_GLRender(SoClipPlane* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoClipPlane*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoClipPlane* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoClipPlane*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoClipPlane* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoClipPlane*)theWrappedObject)->py_q_doAction(action));}
   SoType  static_SoClipPlane_getClassTypeId();
   void py_q_pick(SoClipPlane* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoClipPlane*)theWrappedObject)->py_q_pick(action));}
SoSFBool*  py_get_on(SoClipPlane* theWrappedObject){ return &theWrappedObject->on; }
SoSFPlane*  py_get_plane(SoClipPlane* theWrappedObject){ return &theWrappedObject->plane; }
};





class PythonQtShell_SoComplexity : public SoComplexity
{
public:
    PythonQtShell_SoComplexity():SoComplexity(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoComplexity() override;

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

class PythonQtPublicPromoter_SoComplexity : public SoComplexity
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoComplexity::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoComplexity::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoComplexity::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoComplexity::getBoundingBox(action); }
inline void py_q_pick(SoPickAction*  action) { SoComplexity::pick(action); }
};

class PythonQtWrapper_SoComplexity : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Type )
enum Type{
  OBJECT_SPACE = SoComplexity::OBJECT_SPACE,   SCREEN_SPACE = SoComplexity::SCREEN_SPACE,   BOUNDING_BOX = SoComplexity::BOUNDING_BOX};
public slots:
SoComplexity* new_SoComplexity();
   void py_q_GLRender(SoComplexity* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoComplexity*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoComplexity* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoComplexity*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoComplexity* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoComplexity*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoComplexity* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoComplexity*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoComplexity_getClassTypeId();
   void py_q_pick(SoComplexity* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoComplexity*)theWrappedObject)->py_q_pick(action));}
SoSFFloat*  py_get_textureQuality(SoComplexity* theWrappedObject){ return &theWrappedObject->textureQuality; }
SoSFEnum*  py_get_type(SoComplexity* theWrappedObject){ return &theWrappedObject->type; }
SoSFFloat*  py_get_value(SoComplexity* theWrappedObject){ return &theWrappedObject->value; }
};





class PythonQtShell_SoCone : public SoCone
{
public:
    PythonQtShell_SoCone():SoCone(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoCone() override;

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

class PythonQtPublicPromoter_SoCone : public SoCone
{ public:
inline void promoted_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { this->computeBBox(action, box, center); }
inline void promoted_generatePrimitives(SoAction*  action) { this->generatePrimitives(action); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoCone::GLRender(action); }
inline void py_q_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { SoCone::computeBBox(action, box, center); }
inline void py_q_generatePrimitives(SoAction*  action) { SoCone::generatePrimitives(action); }
inline void py_q_rayPick(SoRayPickAction*  action) { SoCone::rayPick(action); }
};

class PythonQtWrapper_SoCone : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Part )
enum Part{
  SIDES = SoCone::SIDES,   BOTTOM = SoCone::BOTTOM,   ALL = SoCone::ALL};
public slots:
SoCone* new_SoCone();
   void py_q_GLRender(SoCone* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoCone*)theWrappedObject)->py_q_GLRender(action));}
   void addPart(SoCone* theWrappedObject, SoCone::Part  part);
   void py_q_computeBBox(SoCone* theWrappedObject, SoAction*  action, SbBox3f&  box, SbVec3f&  center){  (((PythonQtPublicPromoter_SoCone*)theWrappedObject)->py_q_computeBBox(action, box, center));}
   void py_q_generatePrimitives(SoCone* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoCone*)theWrappedObject)->py_q_generatePrimitives(action));}
   SoType  static_SoCone_getClassTypeId();
   bool  hasPart(SoCone* theWrappedObject, SoCone::Part  part) const;
   void py_q_rayPick(SoCone* theWrappedObject, SoRayPickAction*  action){  (((PythonQtPublicPromoter_SoCone*)theWrappedObject)->py_q_rayPick(action));}
   void removePart(SoCone* theWrappedObject, SoCone::Part  part);
SoSFFloat*  py_get_bottomRadius(SoCone* theWrappedObject){ return &theWrappedObject->bottomRadius; }
SoSFFloat*  py_get_height(SoCone* theWrappedObject){ return &theWrappedObject->height; }
SoSFBitMask*  py_get_parts(SoCone* theWrappedObject){ return &theWrappedObject->parts; }
SoSFInt32*  py_get_sections(SoCone* theWrappedObject){ return &theWrappedObject->sections; }
SoSFInt32*  py_get_sides(SoCone* theWrappedObject){ return &theWrappedObject->sides; }
};





class PythonQtShell_SoCoordinate3 : public SoCoordinate3
{
public:
    PythonQtShell_SoCoordinate3():SoCoordinate3(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoCoordinate3() override;

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

class PythonQtPublicPromoter_SoCoordinate3 : public SoCoordinate3
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoCoordinate3::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoCoordinate3::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoCoordinate3::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoCoordinate3::getBoundingBox(action); }
inline void py_q_pick(SoPickAction*  action) { SoCoordinate3::pick(action); }
};

class PythonQtWrapper_SoCoordinate3 : public QObject
{ Q_OBJECT
public:
public slots:
SoCoordinate3* new_SoCoordinate3();
   void py_q_GLRender(SoCoordinate3* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoCoordinate3*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoCoordinate3* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoCoordinate3*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoCoordinate3* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoCoordinate3*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoCoordinate3* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoCoordinate3*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoCoordinate3_getClassTypeId();
   void py_q_pick(SoCoordinate3* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoCoordinate3*)theWrappedObject)->py_q_pick(action));}
SoMFVec3f*  py_get_point(SoCoordinate3* theWrappedObject){ return &theWrappedObject->point; }
};





class PythonQtShell_SoCoordinate4 : public SoCoordinate4
{
public:
    PythonQtShell_SoCoordinate4():SoCoordinate4(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoCoordinate4() override;

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

class PythonQtPublicPromoter_SoCoordinate4 : public SoCoordinate4
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoCoordinate4::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoCoordinate4::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoCoordinate4::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoCoordinate4::getBoundingBox(action); }
inline void py_q_pick(SoPickAction*  action) { SoCoordinate4::pick(action); }
};

class PythonQtWrapper_SoCoordinate4 : public QObject
{ Q_OBJECT
public:
public slots:
SoCoordinate4* new_SoCoordinate4();
   void py_q_GLRender(SoCoordinate4* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoCoordinate4*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoCoordinate4* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoCoordinate4*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoCoordinate4* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoCoordinate4*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoCoordinate4* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoCoordinate4*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoCoordinate4_getClassTypeId();
   void py_q_pick(SoCoordinate4* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoCoordinate4*)theWrappedObject)->py_q_pick(action));}
SoMFVec4f*  py_get_point(SoCoordinate4* theWrappedObject){ return &theWrappedObject->point; }
};





class PythonQtShell_SoCube : public SoCube
{
public:
    PythonQtShell_SoCube():SoCube(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoCube() override;

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

class PythonQtPublicPromoter_SoCube : public SoCube
{ public:
inline void promoted_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { this->computeBBox(action, box, center); }
inline SoDetail*  promoted_createTriangleDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp) { return this->createTriangleDetail(action, v1, v2, v3, pp); }
inline void promoted_generatePrimitives(SoAction*  action) { this->generatePrimitives(action); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoCube::GLRender(action); }
inline void py_q_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { SoCube::computeBBox(action, box, center); }
inline SoDetail*  py_q_createTriangleDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp) { return SoCube::createTriangleDetail(action, v1, v2, v3, pp); }
inline void py_q_generatePrimitives(SoAction*  action) { SoCube::generatePrimitives(action); }
inline void py_q_rayPick(SoRayPickAction*  action) { SoCube::rayPick(action); }
};

class PythonQtWrapper_SoCube : public QObject
{ Q_OBJECT
public:
public slots:
SoCube* new_SoCube();
   void py_q_GLRender(SoCube* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoCube*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_computeBBox(SoCube* theWrappedObject, SoAction*  action, SbBox3f&  box, SbVec3f&  center){  (((PythonQtPublicPromoter_SoCube*)theWrappedObject)->py_q_computeBBox(action, box, center));}
   SoDetail*  py_q_createTriangleDetail(SoCube* theWrappedObject, SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp){  return (((PythonQtPublicPromoter_SoCube*)theWrappedObject)->py_q_createTriangleDetail(action, v1, v2, v3, pp));}
   void py_q_generatePrimitives(SoCube* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoCube*)theWrappedObject)->py_q_generatePrimitives(action));}
   SoType  static_SoCube_getClassTypeId();
   void py_q_rayPick(SoCube* theWrappedObject, SoRayPickAction*  action){  (((PythonQtPublicPromoter_SoCube*)theWrappedObject)->py_q_rayPick(action));}
SoSFFloat*  py_get_depth(SoCube* theWrappedObject){ return &theWrappedObject->depth; }
SoSFFloat*  py_get_height(SoCube* theWrappedObject){ return &theWrappedObject->height; }
SoSFFloat*  py_get_width(SoCube* theWrappedObject){ return &theWrappedObject->width; }
};





class PythonQtShell_SoCylinder : public SoCylinder
{
public:
    PythonQtShell_SoCylinder():SoCylinder(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoCylinder() override;

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

class PythonQtPublicPromoter_SoCylinder : public SoCylinder
{ public:
inline void promoted_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { this->computeBBox(action, box, center); }
inline void promoted_generatePrimitives(SoAction*  action) { this->generatePrimitives(action); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoCylinder::GLRender(action); }
inline void py_q_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { SoCylinder::computeBBox(action, box, center); }
inline void py_q_generatePrimitives(SoAction*  action) { SoCylinder::generatePrimitives(action); }
inline void py_q_rayPick(SoRayPickAction*  action) { SoCylinder::rayPick(action); }
};

class PythonQtWrapper_SoCylinder : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Part )
enum Part{
  SIDES = SoCylinder::SIDES,   TOP = SoCylinder::TOP,   BOTTOM = SoCylinder::BOTTOM,   ALL = SoCylinder::ALL};
public slots:
SoCylinder* new_SoCylinder();
   void py_q_GLRender(SoCylinder* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoCylinder*)theWrappedObject)->py_q_GLRender(action));}
   void addPart(SoCylinder* theWrappedObject, SoCylinder::Part  part);
   void py_q_computeBBox(SoCylinder* theWrappedObject, SoAction*  action, SbBox3f&  box, SbVec3f&  center){  (((PythonQtPublicPromoter_SoCylinder*)theWrappedObject)->py_q_computeBBox(action, box, center));}
   void py_q_generatePrimitives(SoCylinder* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoCylinder*)theWrappedObject)->py_q_generatePrimitives(action));}
   SoType  static_SoCylinder_getClassTypeId();
   bool  hasPart(SoCylinder* theWrappedObject, SoCylinder::Part  part) const;
   void py_q_rayPick(SoCylinder* theWrappedObject, SoRayPickAction*  action){  (((PythonQtPublicPromoter_SoCylinder*)theWrappedObject)->py_q_rayPick(action));}
   void removePart(SoCylinder* theWrappedObject, SoCylinder::Part  part);
SoSFFloat*  py_get_height(SoCylinder* theWrappedObject){ return &theWrappedObject->height; }
SoSFBitMask*  py_get_parts(SoCylinder* theWrappedObject){ return &theWrappedObject->parts; }
SoSFFloat*  py_get_radius(SoCylinder* theWrappedObject){ return &theWrappedObject->radius; }
SoSFInt32*  py_get_sections(SoCylinder* theWrappedObject){ return &theWrappedObject->sections; }
SoSFInt32*  py_get_sides(SoCylinder* theWrappedObject){ return &theWrappedObject->sides; }
};





class PythonQtShell_SoDirectionalLight : public SoDirectionalLight
{
public:
    PythonQtShell_SoDirectionalLight():SoDirectionalLight(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoDirectionalLight() override;

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

class PythonQtPublicPromoter_SoDirectionalLight : public SoDirectionalLight
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoDirectionalLight::GLRender(action); }
};

class PythonQtWrapper_SoDirectionalLight : public QObject
{ Q_OBJECT
public:
public slots:
SoDirectionalLight* new_SoDirectionalLight();
   void py_q_GLRender(SoDirectionalLight* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoDirectionalLight*)theWrappedObject)->py_q_GLRender(action));}
   SoType  static_SoDirectionalLight_getClassTypeId();
SoSFVec3f*  py_get_direction(SoDirectionalLight* theWrappedObject){ return &theWrappedObject->direction; }
};





class PythonQtShell_SoDrawStyle : public SoDrawStyle
{
public:
    PythonQtShell_SoDrawStyle():SoDrawStyle(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoDrawStyle() override;

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

class PythonQtPublicPromoter_SoDrawStyle : public SoDrawStyle
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoDrawStyle::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoDrawStyle::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoDrawStyle::doAction(action); }
};

class PythonQtWrapper_SoDrawStyle : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Style )
enum Style{
  FILLED = SoDrawStyle::FILLED,   LINES = SoDrawStyle::LINES,   POINTS = SoDrawStyle::POINTS,   INVISIBLE = SoDrawStyle::INVISIBLE};
public slots:
SoDrawStyle* new_SoDrawStyle();
   void py_q_GLRender(SoDrawStyle* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoDrawStyle*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoDrawStyle* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoDrawStyle*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoDrawStyle* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoDrawStyle*)theWrappedObject)->py_q_doAction(action));}
   SoType  static_SoDrawStyle_getClassTypeId();
SoSFUShort*  py_get_linePattern(SoDrawStyle* theWrappedObject){ return &theWrappedObject->linePattern; }
SoSFFloat*  py_get_lineWidth(SoDrawStyle* theWrappedObject){ return &theWrappedObject->lineWidth; }
SoSFFloat*  py_get_pointSize(SoDrawStyle* theWrappedObject){ return &theWrappedObject->pointSize; }
SoSFEnum*  py_get_style(SoDrawStyle* theWrappedObject){ return &theWrappedObject->style; }
};





class PythonQtShell_SoEnvironment : public SoEnvironment
{
public:
    PythonQtShell_SoEnvironment():SoEnvironment(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoEnvironment() override;

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

class PythonQtPublicPromoter_SoEnvironment : public SoEnvironment
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoEnvironment::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoEnvironment::callback(action); }
};

class PythonQtWrapper_SoEnvironment : public QObject
{ Q_OBJECT
public:
Q_ENUMS(FogType )
enum FogType{
  NONE = SoEnvironment::NONE,   HAZE = SoEnvironment::HAZE,   FOG = SoEnvironment::FOG,   SMOKE = SoEnvironment::SMOKE};
public slots:
SoEnvironment* new_SoEnvironment();
   void py_q_GLRender(SoEnvironment* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoEnvironment*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoEnvironment* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoEnvironment*)theWrappedObject)->py_q_callback(action));}
   SoType  static_SoEnvironment_getClassTypeId();
SoSFColor*  py_get_ambientColor(SoEnvironment* theWrappedObject){ return &theWrappedObject->ambientColor; }
SoSFFloat*  py_get_ambientIntensity(SoEnvironment* theWrappedObject){ return &theWrappedObject->ambientIntensity; }
SoSFVec3f*  py_get_attenuation(SoEnvironment* theWrappedObject){ return &theWrappedObject->attenuation; }
SoSFColor*  py_get_fogColor(SoEnvironment* theWrappedObject){ return &theWrappedObject->fogColor; }
SoSFEnum*  py_get_fogType(SoEnvironment* theWrappedObject){ return &theWrappedObject->fogType; }
SoSFFloat*  py_get_fogVisibility(SoEnvironment* theWrappedObject){ return &theWrappedObject->fogVisibility; }
};





class PythonQtShell_SoEventCallback : public SoEventCallback
{
public:
    PythonQtShell_SoEventCallback():SoEventCallback(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoEventCallback() override;

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
void handleEvent(SoHandleEventAction*  ha) override;
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

class PythonQtPublicPromoter_SoEventCallback : public SoEventCallback
{ public:
inline void promoted_handleEvent(SoHandleEventAction*  ha) { this->handleEvent(ha); }
inline void py_q_handleEvent(SoHandleEventAction*  ha) { SoEventCallback::handleEvent(ha); }
};

class PythonQtWrapper_SoEventCallback : public QObject
{ Q_OBJECT
public:
public slots:
SoEventCallback* new_SoEventCallback();
   SoHandleEventAction*  getAction(SoEventCallback* theWrappedObject) const;
   SoType  static_SoEventCallback_getClassTypeId();
   const SoEvent*  getEvent(SoEventCallback* theWrappedObject) const;
   const SoPath*  getPath(SoEventCallback* theWrappedObject);
   const SoPickedPoint*  getPickedPoint(SoEventCallback* theWrappedObject) const;
   void grabEvents(SoEventCallback* theWrappedObject);
   void py_q_handleEvent(SoEventCallback* theWrappedObject, SoHandleEventAction*  ha){  (((PythonQtPublicPromoter_SoEventCallback*)theWrappedObject)->py_q_handleEvent(ha));}
   bool  isHandled(SoEventCallback* theWrappedObject) const;
   void releaseEvents(SoEventCallback* theWrappedObject);
   void setHandled(SoEventCallback* theWrappedObject);
   void setPath(SoEventCallback* theWrappedObject, SoPath*  path);
};





class PythonQtShell_SoFaceSet : public SoFaceSet
{
public:
    PythonQtShell_SoFaceSet():SoFaceSet(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoFaceSet() override;

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

class PythonQtPublicPromoter_SoFaceSet : public SoFaceSet
{ public:
inline void promoted_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { this->computeBBox(action, box, center); }
inline SoDetail*  promoted_createTriangleDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp) { return this->createTriangleDetail(action, v1, v2, v3, pp); }
inline void promoted_generatePrimitives(SoAction*  action) { this->generatePrimitives(action); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoFaceSet::GLRender(action); }
inline void py_q_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { SoFaceSet::computeBBox(action, box, center); }
inline SoDetail*  py_q_createTriangleDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp) { return SoFaceSet::createTriangleDetail(action, v1, v2, v3, pp); }
inline void py_q_generatePrimitives(SoAction*  action) { SoFaceSet::generatePrimitives(action); }
};

class PythonQtWrapper_SoFaceSet : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Binding )
enum Binding{
  OVERALL = SoFaceSet::OVERALL,   PER_FACE = SoFaceSet::PER_FACE,   PER_VERTEX = SoFaceSet::PER_VERTEX};
public slots:
SoFaceSet* new_SoFaceSet();
   void py_q_GLRender(SoFaceSet* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoFaceSet*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_computeBBox(SoFaceSet* theWrappedObject, SoAction*  action, SbBox3f&  box, SbVec3f&  center){  (((PythonQtPublicPromoter_SoFaceSet*)theWrappedObject)->py_q_computeBBox(action, box, center));}
   SoDetail*  py_q_createTriangleDetail(SoFaceSet* theWrappedObject, SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp){  return (((PythonQtPublicPromoter_SoFaceSet*)theWrappedObject)->py_q_createTriangleDetail(action, v1, v2, v3, pp));}
   void py_q_generatePrimitives(SoFaceSet* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoFaceSet*)theWrappedObject)->py_q_generatePrimitives(action));}
   SoType  static_SoFaceSet_getClassTypeId();
SoMFInt32*  py_get_numVertices(SoFaceSet* theWrappedObject){ return &theWrappedObject->numVertices; }
SoSFBool*  py_get_sendAdjacency(SoFaceSet* theWrappedObject){ return &theWrappedObject->sendAdjacency; }
};





class PythonQtShell_SoFile : public SoFile
{
public:
    PythonQtShell_SoFile():SoFile(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoFile() override;

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

class PythonQtPublicPromoter_SoFile : public SoFile
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoFile::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoFile::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoFile::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoFile::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoFile::getMatrix(action); }
inline void py_q_handleEvent(SoHandleEventAction*  action) { SoFile::handleEvent(action); }
inline void py_q_pick(SoPickAction*  action) { SoFile::pick(action); }
};

class PythonQtWrapper_SoFile : public QObject
{ Q_OBJECT
public:
public slots:
SoFile* new_SoFile();
   void py_q_GLRender(SoFile* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoFile*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoFile* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoFile*)theWrappedObject)->py_q_callback(action));}
   SoGroup*  copyChildren(SoFile* theWrappedObject) const;
   void py_q_doAction(SoFile* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoFile*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoFile* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoFile*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoFile_getClassTypeId();
   void py_q_getMatrix(SoFile* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoFile*)theWrappedObject)->py_q_getMatrix(action));}
   void py_q_handleEvent(SoFile* theWrappedObject, SoHandleEventAction*  action){  (((PythonQtPublicPromoter_SoFile*)theWrappedObject)->py_q_handleEvent(action));}
   void py_q_pick(SoFile* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoFile*)theWrappedObject)->py_q_pick(action));}
SoSFString*  py_get_name(SoFile* theWrappedObject){ return &theWrappedObject->name; }
};





class PythonQtShell_SoFont : public SoFont
{
public:
    PythonQtShell_SoFont():SoFont(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoFont() override;

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

class PythonQtPublicPromoter_SoFont : public SoFont
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoFont::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoFont::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoFont::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoFont::getBoundingBox(action); }
inline void py_q_pick(SoPickAction*  action) { SoFont::pick(action); }
};

class PythonQtWrapper_SoFont : public QObject
{ Q_OBJECT
public:
public slots:
SoFont* new_SoFont();
   void py_q_GLRender(SoFont* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoFont*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoFont* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoFont*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoFont* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoFont*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoFont* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoFont*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoFont_getClassTypeId();
   void py_q_pick(SoFont* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoFont*)theWrappedObject)->py_q_pick(action));}
SoSFName*  py_get_name(SoFont* theWrappedObject){ return &theWrappedObject->name; }
SoSFFloat*  py_get_size(SoFont* theWrappedObject){ return &theWrappedObject->size; }
};





class PythonQtShell_SoFontStyle : public SoFontStyle
{
public:
    PythonQtShell_SoFontStyle():SoFontStyle(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoFontStyle() override;

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

class PythonQtPublicPromoter_SoFontStyle : public SoFontStyle
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoFontStyle::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoFontStyle::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoFontStyle::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoFontStyle::getBoundingBox(action); }
inline void py_q_pick(SoPickAction*  action) { SoFontStyle::pick(action); }
};

class PythonQtWrapper_SoFontStyle : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Family Style )
enum Family{
  SERIF = SoFontStyle::SERIF,   SANS = SoFontStyle::SANS,   TYPEWRITER = SoFontStyle::TYPEWRITER};
enum Style{
  NONE = SoFontStyle::NONE,   BOLD = SoFontStyle::BOLD,   ITALIC = SoFontStyle::ITALIC};
public slots:
SoFontStyle* new_SoFontStyle();
   void py_q_GLRender(SoFontStyle* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoFontStyle*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoFontStyle* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoFontStyle*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoFontStyle* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoFontStyle*)theWrappedObject)->py_q_doAction(action));}
   void py_q_getBoundingBox(SoFontStyle* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoFontStyle*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoFontStyle_getClassTypeId();
   SbString  getFontName(SoFontStyle* theWrappedObject);
   void py_q_pick(SoFontStyle* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoFontStyle*)theWrappedObject)->py_q_pick(action));}
SoSFEnum*  py_get_family(SoFontStyle* theWrappedObject){ return &theWrappedObject->family; }
SoSFBitMask*  py_get_style(SoFontStyle* theWrappedObject){ return &theWrappedObject->style; }
};





class PythonQtShell_SoGroup : public SoGroup
{
public:
    PythonQtShell_SoGroup():SoGroup(),_wrapper(nullptr) {_type = getClassTypeId();
};
    PythonQtShell_SoGroup(int  nChildren):SoGroup(nChildren),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoGroup() override;

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

class PythonQtPublicPromoter_SoGroup : public SoGroup
{ public:
inline bool  promoted_readChildren(SoInput*  in) { return this->readChildren(in); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoGroup::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoGroup::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoGroup::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoGroup::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoGroup::getMatrix(action); }
inline void py_q_handleEvent(SoHandleEventAction*  action) { SoGroup::handleEvent(action); }
inline void py_q_pick(SoPickAction*  action) { SoGroup::pick(action); }
inline bool  py_q_readChildren(SoInput*  in) { return SoGroup::readChildren(in); }
inline void py_q_search(SoSearchAction*  action) { SoGroup::search(action); }
inline void py_q_write(SoWriteAction*  action) { SoGroup::write(action); }
};

class PythonQtWrapper_SoGroup : public QObject
{ Q_OBJECT
public:
public slots:
SoGroup* new_SoGroup();
SoGroup* new_SoGroup(int  nChildren);
   void py_q_GLRender(SoGroup* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoGroup*)theWrappedObject)->py_q_GLRender(action));}
   void addChild(SoGroup* theWrappedObject, SoNode*  child);
   void py_q_callback(SoGroup* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoGroup*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoGroup* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoGroup*)theWrappedObject)->py_q_doAction(action));}
   int  findChild(SoGroup* theWrappedObject, const SoNode*  child) const;
   void py_q_getBoundingBox(SoGroup* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoGroup*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoNode*  getChild(SoGroup* theWrappedObject, int  index) const;
   SoType  static_SoGroup_getClassTypeId();
   void py_q_getMatrix(SoGroup* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoGroup*)theWrappedObject)->py_q_getMatrix(action));}
   int  getNumChildren(SoGroup* theWrappedObject) const;
   void py_q_handleEvent(SoGroup* theWrappedObject, SoHandleEventAction*  action){  (((PythonQtPublicPromoter_SoGroup*)theWrappedObject)->py_q_handleEvent(action));}
   void insertChild(SoGroup* theWrappedObject, SoNode*  child, int  newChildIndex);
   void py_q_pick(SoGroup* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoGroup*)theWrappedObject)->py_q_pick(action));}
   bool  readChildren(SoGroup* theWrappedObject, SoInput*  in);
   bool  py_q_readChildren(SoGroup* theWrappedObject, SoInput*  in){  return (((PythonQtPublicPromoter_SoGroup*)theWrappedObject)->py_q_readChildren(in));}
   void removeAllChildren(SoGroup* theWrappedObject);
   void removeChild(SoGroup* theWrappedObject, SoNode*  child);
   void removeChild(SoGroup* theWrappedObject, int  index);
   void replaceChild(SoGroup* theWrappedObject, SoNode*  oldChild, SoNode*  newChild);
   void replaceChild(SoGroup* theWrappedObject, int  index, SoNode*  newChild);
   void py_q_search(SoGroup* theWrappedObject, SoSearchAction*  action){  (((PythonQtPublicPromoter_SoGroup*)theWrappedObject)->py_q_search(action));}
   void py_q_write(SoGroup* theWrappedObject, SoWriteAction*  action){  (((PythonQtPublicPromoter_SoGroup*)theWrappedObject)->py_q_write(action));}
};





class PythonQtShell_SoIndexedFaceSet : public SoIndexedFaceSet
{
public:
    PythonQtShell_SoIndexedFaceSet():SoIndexedFaceSet(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoIndexedFaceSet() override;

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

class PythonQtPublicPromoter_SoIndexedFaceSet : public SoIndexedFaceSet
{ public:
inline SoDetail*  promoted_createTriangleDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp) { return this->createTriangleDetail(action, v1, v2, v3, pp); }
inline void promoted_generatePrimitives(SoAction*  action) { this->generatePrimitives(action); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoIndexedFaceSet::GLRender(action); }
inline SoDetail*  py_q_createTriangleDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp) { return SoIndexedFaceSet::createTriangleDetail(action, v1, v2, v3, pp); }
inline void py_q_generatePrimitives(SoAction*  action) { SoIndexedFaceSet::generatePrimitives(action); }
};

class PythonQtWrapper_SoIndexedFaceSet : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Binding )
enum Binding{
  OVERALL = SoIndexedFaceSet::OVERALL,   PER_FACE = SoIndexedFaceSet::PER_FACE,   PER_FACE_INDEXED = SoIndexedFaceSet::PER_FACE_INDEXED,   PER_VERTEX = SoIndexedFaceSet::PER_VERTEX,   PER_VERTEX_INDEXED = SoIndexedFaceSet::PER_VERTEX_INDEXED};
public slots:
SoIndexedFaceSet* new_SoIndexedFaceSet();
   void py_q_GLRender(SoIndexedFaceSet* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoIndexedFaceSet*)theWrappedObject)->py_q_GLRender(action));}
   SoDetail*  py_q_createTriangleDetail(SoIndexedFaceSet* theWrappedObject, SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp){  return (((PythonQtPublicPromoter_SoIndexedFaceSet*)theWrappedObject)->py_q_createTriangleDetail(action, v1, v2, v3, pp));}
   void py_q_generatePrimitives(SoIndexedFaceSet* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoIndexedFaceSet*)theWrappedObject)->py_q_generatePrimitives(action));}
   SoType  static_SoIndexedFaceSet_getClassTypeId();
};





class PythonQtShell_SoIndexedLineSet : public SoIndexedLineSet
{
public:
    PythonQtShell_SoIndexedLineSet():SoIndexedLineSet(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoIndexedLineSet() override;

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

class PythonQtPublicPromoter_SoIndexedLineSet : public SoIndexedLineSet
{ public:
inline SoDetail*  promoted_createLineSegmentDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, SoPickedPoint*  pp) { return this->createLineSegmentDetail(action, v1, v2, pp); }
inline void promoted_generatePrimitives(SoAction*  action) { this->generatePrimitives(action); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoIndexedLineSet::GLRender(action); }
inline SoDetail*  py_q_createLineSegmentDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, SoPickedPoint*  pp) { return SoIndexedLineSet::createLineSegmentDetail(action, v1, v2, pp); }
inline void py_q_generatePrimitives(SoAction*  action) { SoIndexedLineSet::generatePrimitives(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoIndexedLineSet::getBoundingBox(action); }
};

class PythonQtWrapper_SoIndexedLineSet : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Binding )
enum Binding{
  OVERALL = SoIndexedLineSet::OVERALL,   PER_SEGMENT = SoIndexedLineSet::PER_SEGMENT,   PER_SEGMENT_INDEXED = SoIndexedLineSet::PER_SEGMENT_INDEXED,   PER_LINE = SoIndexedLineSet::PER_LINE,   PER_LINE_INDEXED = SoIndexedLineSet::PER_LINE_INDEXED,   PER_VERTEX = SoIndexedLineSet::PER_VERTEX,   PER_VERTEX_INDEXED = SoIndexedLineSet::PER_VERTEX_INDEXED};
public slots:
SoIndexedLineSet* new_SoIndexedLineSet();
   void py_q_GLRender(SoIndexedLineSet* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoIndexedLineSet*)theWrappedObject)->py_q_GLRender(action));}
   SoDetail*  py_q_createLineSegmentDetail(SoIndexedLineSet* theWrappedObject, SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, SoPickedPoint*  pp){  return (((PythonQtPublicPromoter_SoIndexedLineSet*)theWrappedObject)->py_q_createLineSegmentDetail(action, v1, v2, pp));}
   void py_q_generatePrimitives(SoIndexedLineSet* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoIndexedLineSet*)theWrappedObject)->py_q_generatePrimitives(action));}
   void py_q_getBoundingBox(SoIndexedLineSet* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoIndexedLineSet*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoIndexedLineSet_getClassTypeId();
SoSFBool*  py_get_sendAdjacency(SoIndexedLineSet* theWrappedObject){ return &theWrappedObject->sendAdjacency; }
};





class PythonQtShell_SoIndexedNurbsCurve : public SoIndexedNurbsCurve
{
public:
    PythonQtShell_SoIndexedNurbsCurve():SoIndexedNurbsCurve(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoIndexedNurbsCurve() override;

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

class PythonQtPublicPromoter_SoIndexedNurbsCurve : public SoIndexedNurbsCurve
{ public:
inline void promoted_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { this->computeBBox(action, box, center); }
inline void promoted_generatePrimitives(SoAction*  action) { this->generatePrimitives(action); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoIndexedNurbsCurve::GLRender(action); }
inline void py_q_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { SoIndexedNurbsCurve::computeBBox(action, box, center); }
inline void py_q_generatePrimitives(SoAction*  action) { SoIndexedNurbsCurve::generatePrimitives(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoIndexedNurbsCurve::getBoundingBox(action); }
inline void py_q_rayPick(SoRayPickAction*  action) { SoIndexedNurbsCurve::rayPick(action); }
};

class PythonQtWrapper_SoIndexedNurbsCurve : public QObject
{ Q_OBJECT
public:
public slots:
SoIndexedNurbsCurve* new_SoIndexedNurbsCurve();
   void py_q_GLRender(SoIndexedNurbsCurve* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoIndexedNurbsCurve*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_computeBBox(SoIndexedNurbsCurve* theWrappedObject, SoAction*  action, SbBox3f&  box, SbVec3f&  center){  (((PythonQtPublicPromoter_SoIndexedNurbsCurve*)theWrappedObject)->py_q_computeBBox(action, box, center));}
   void py_q_generatePrimitives(SoIndexedNurbsCurve* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoIndexedNurbsCurve*)theWrappedObject)->py_q_generatePrimitives(action));}
   void py_q_getBoundingBox(SoIndexedNurbsCurve* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoIndexedNurbsCurve*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoIndexedNurbsCurve_getClassTypeId();
   void py_q_rayPick(SoIndexedNurbsCurve* theWrappedObject, SoRayPickAction*  action){  (((PythonQtPublicPromoter_SoIndexedNurbsCurve*)theWrappedObject)->py_q_rayPick(action));}
   void sendPrimitive(SoIndexedNurbsCurve* theWrappedObject, SoAction*  arg__1, SoPrimitiveVertex*  arg__2);
SoMFInt32*  py_get_coordIndex(SoIndexedNurbsCurve* theWrappedObject){ return &theWrappedObject->coordIndex; }
SoMFFloat*  py_get_knotVector(SoIndexedNurbsCurve* theWrappedObject){ return &theWrappedObject->knotVector; }
SoSFInt32*  py_get_numControlPoints(SoIndexedNurbsCurve* theWrappedObject){ return &theWrappedObject->numControlPoints; }
};





class PythonQtShell_SoIndexedNurbsSurface : public SoIndexedNurbsSurface
{
public:
    PythonQtShell_SoIndexedNurbsSurface():SoIndexedNurbsSurface(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoIndexedNurbsSurface() override;

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

class PythonQtPublicPromoter_SoIndexedNurbsSurface : public SoIndexedNurbsSurface
{ public:
inline void promoted_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { this->computeBBox(action, box, center); }
inline void promoted_generatePrimitives(SoAction*  action) { this->generatePrimitives(action); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoIndexedNurbsSurface::GLRender(action); }
inline void py_q_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { SoIndexedNurbsSurface::computeBBox(action, box, center); }
inline void py_q_generatePrimitives(SoAction*  action) { SoIndexedNurbsSurface::generatePrimitives(action); }
inline void py_q_rayPick(SoRayPickAction*  action) { SoIndexedNurbsSurface::rayPick(action); }
};

class PythonQtWrapper_SoIndexedNurbsSurface : public QObject
{ Q_OBJECT
public:
public slots:
SoIndexedNurbsSurface* new_SoIndexedNurbsSurface();
   void py_q_GLRender(SoIndexedNurbsSurface* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoIndexedNurbsSurface*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_computeBBox(SoIndexedNurbsSurface* theWrappedObject, SoAction*  action, SbBox3f&  box, SbVec3f&  center){  (((PythonQtPublicPromoter_SoIndexedNurbsSurface*)theWrappedObject)->py_q_computeBBox(action, box, center));}
   void py_q_generatePrimitives(SoIndexedNurbsSurface* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoIndexedNurbsSurface*)theWrappedObject)->py_q_generatePrimitives(action));}
   SoType  static_SoIndexedNurbsSurface_getClassTypeId();
   void py_q_rayPick(SoIndexedNurbsSurface* theWrappedObject, SoRayPickAction*  action){  (((PythonQtPublicPromoter_SoIndexedNurbsSurface*)theWrappedObject)->py_q_rayPick(action));}
   void sendPrimitive(SoIndexedNurbsSurface* theWrappedObject, SoAction*  arg__1, SoPrimitiveVertex*  arg__2);
SoMFInt32*  py_get_coordIndex(SoIndexedNurbsSurface* theWrappedObject){ return &theWrappedObject->coordIndex; }
SoSFInt32*  py_get_numSControlPoints(SoIndexedNurbsSurface* theWrappedObject){ return &theWrappedObject->numSControlPoints; }
SoSFInt32*  py_get_numTControlPoints(SoIndexedNurbsSurface* theWrappedObject){ return &theWrappedObject->numTControlPoints; }
SoSFInt32*  py_get_numUControlPoints(SoIndexedNurbsSurface* theWrappedObject){ return &theWrappedObject->numUControlPoints; }
SoSFInt32*  py_get_numVControlPoints(SoIndexedNurbsSurface* theWrappedObject){ return &theWrappedObject->numVControlPoints; }
SoMFFloat*  py_get_sKnotVector(SoIndexedNurbsSurface* theWrappedObject){ return &theWrappedObject->sKnotVector; }
SoMFFloat*  py_get_tKnotVector(SoIndexedNurbsSurface* theWrappedObject){ return &theWrappedObject->tKnotVector; }
SoMFInt32*  py_get_textureCoordIndex(SoIndexedNurbsSurface* theWrappedObject){ return &theWrappedObject->textureCoordIndex; }
SoMFFloat*  py_get_uKnotVector(SoIndexedNurbsSurface* theWrappedObject){ return &theWrappedObject->uKnotVector; }
SoMFFloat*  py_get_vKnotVector(SoIndexedNurbsSurface* theWrappedObject){ return &theWrappedObject->vKnotVector; }
};





class PythonQtShell_SoIndexedShape : public SoIndexedShape
{
public:
    PythonQtShell_SoIndexedShape():SoIndexedShape(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoIndexedShape() override;

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

class PythonQtPublicPromoter_SoIndexedShape : public SoIndexedShape
{ public:
static inline bool  promoted_areTexCoordsIndexed(SoAction*  action) { return areTexCoordsIndexed(action); }
inline void promoted_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { this->computeBBox(action, box, center); }
inline const int*  promoted_getColorIndices() { return this->getColorIndices(); }
inline const int*  promoted_getNormalIndices() { return this->getNormalIndices(); }
inline int  promoted_getNumVerts(int  startCoord) { return this->getNumVerts(startCoord); }
inline const int*  promoted_getTexCoordIndices() { return this->getTexCoordIndices(); }
inline void promoted_setupIndices(int  numParts, int  numFaces, bool  needNormals, bool  needTexCoords) { this->setupIndices(numParts, numFaces, needNormals, needTexCoords); }
inline void py_q_computeBBox(SoAction*  action, SbBox3f&  box, SbVec3f&  center) { SoIndexedShape::computeBBox(action, box, center); }
};

class PythonQtWrapper_SoIndexedShape : public QObject
{ Q_OBJECT
public:
public slots:
SoIndexedShape* new_SoIndexedShape();
   bool  static_SoIndexedShape_areTexCoordsIndexed(SoAction*  action);
   void py_q_computeBBox(SoIndexedShape* theWrappedObject, SoAction*  action, SbBox3f&  box, SbVec3f&  center){  (((PythonQtPublicPromoter_SoIndexedShape*)theWrappedObject)->py_q_computeBBox(action, box, center));}
   SoType  static_SoIndexedShape_getClassTypeId();
   const int*  getColorIndices(SoIndexedShape* theWrappedObject);
   const int*  getNormalIndices(SoIndexedShape* theWrappedObject);
   int  getNumVerts(SoIndexedShape* theWrappedObject, int  startCoord);
   const int*  getTexCoordIndices(SoIndexedShape* theWrappedObject);
   void setupIndices(SoIndexedShape* theWrappedObject, int  numParts, int  numFaces, bool  needNormals, bool  needTexCoords);
SoMFInt32*  py_get_coordIndex(SoIndexedShape* theWrappedObject){ return &theWrappedObject->coordIndex; }
SoMFInt32*  py_get_materialIndex(SoIndexedShape* theWrappedObject){ return &theWrappedObject->materialIndex; }
SoMFInt32*  py_get_normalIndex(SoIndexedShape* theWrappedObject){ return &theWrappedObject->normalIndex; }
SoMFInt32*  py_get_textureCoordIndex(SoIndexedShape* theWrappedObject){ return &theWrappedObject->textureCoordIndex; }
};





class PythonQtShell_SoIndexedTriangleSet : public SoIndexedTriangleSet
{
public:
    PythonQtShell_SoIndexedTriangleSet():SoIndexedTriangleSet(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoIndexedTriangleSet() override;

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

class PythonQtPublicPromoter_SoIndexedTriangleSet : public SoIndexedTriangleSet
{ public:
inline SoDetail*  promoted_createTriangleDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp) { return this->createTriangleDetail(action, v1, v2, v3, pp); }
inline void promoted_generatePrimitives(SoAction*  action) { this->generatePrimitives(action); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoIndexedTriangleSet::GLRender(action); }
inline SoDetail*  py_q_createTriangleDetail(SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp) { return SoIndexedTriangleSet::createTriangleDetail(action, v1, v2, v3, pp); }
inline void py_q_generatePrimitives(SoAction*  action) { SoIndexedTriangleSet::generatePrimitives(action); }
};

class PythonQtWrapper_SoIndexedTriangleSet : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Binding )
enum Binding{
  OVERALL = SoIndexedTriangleSet::OVERALL,   PER_FACE = SoIndexedTriangleSet::PER_FACE,   PER_FACE_INDEXED = SoIndexedTriangleSet::PER_FACE_INDEXED,   PER_VERTEX = SoIndexedTriangleSet::PER_VERTEX,   PER_VERTEX_INDEXED = SoIndexedTriangleSet::PER_VERTEX_INDEXED};
public slots:
SoIndexedTriangleSet* new_SoIndexedTriangleSet();
   void py_q_GLRender(SoIndexedTriangleSet* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoIndexedTriangleSet*)theWrappedObject)->py_q_GLRender(action));}
   SoDetail*  py_q_createTriangleDetail(SoIndexedTriangleSet* theWrappedObject, SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp){  return (((PythonQtPublicPromoter_SoIndexedTriangleSet*)theWrappedObject)->py_q_createTriangleDetail(action, v1, v2, v3, pp));}
   void py_q_generatePrimitives(SoIndexedTriangleSet* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoIndexedTriangleSet*)theWrappedObject)->py_q_generatePrimitives(action));}
   SoType  static_SoIndexedTriangleSet_getClassTypeId();
SoSFBool*  py_get_sendAdjacency(SoIndexedTriangleSet* theWrappedObject){ return &theWrappedObject->sendAdjacency; }
};


