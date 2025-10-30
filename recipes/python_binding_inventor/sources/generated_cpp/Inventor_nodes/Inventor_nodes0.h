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
#include <Inventor/elements/SoGLCoordinateElement.h>
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
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoTriangleStripSet.h>
#include <Inventor/nodes/SoUnits.h>
#include <Inventor/nodes/SoVertexProperty.h>
#include <Inventor/nodes/SoVertexShape.h>
#include <Inventor/sensors/SoSensor.h>
#include <PythonQt.h>
#include <QObject>
#include <QVariant>



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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoDirectionalLight : public SoDirectionalLight
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoDirectionalLight::GLRender(action); }
};

class PythonQtWrapper_SoDirectionalLight : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
SoIndexedTriangleSet* new_SoIndexedTriangleSet();
   void py_q_GLRender(SoIndexedTriangleSet* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoIndexedTriangleSet*)theWrappedObject)->py_q_GLRender(action));}
   SoDetail*  py_q_createTriangleDetail(SoIndexedTriangleSet* theWrappedObject, SoRayPickAction*  action, const SoPrimitiveVertex*  v1, const SoPrimitiveVertex*  v2, const SoPrimitiveVertex*  v3, SoPickedPoint*  pp){  return (((PythonQtPublicPromoter_SoIndexedTriangleSet*)theWrappedObject)->py_q_createTriangleDetail(action, v1, v2, v3, pp));}
   void py_q_generatePrimitives(SoIndexedTriangleSet* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoIndexedTriangleSet*)theWrappedObject)->py_q_generatePrimitives(action));}
   SoType  static_SoIndexedTriangleSet_getClassTypeId();
SoSFBool*  py_get_sendAdjacency(SoIndexedTriangleSet* theWrappedObject){ return &theWrappedObject->sendAdjacency; }
};





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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoRotor : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoShuttle : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoSpotLight : public SoSpotLight
{ public:
inline void py_q_GLRender(SoGLRenderAction*  action) { SoSpotLight::GLRender(action); }
};

class PythonQtWrapper_SoSpotLight : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoTextureCoordinateFunction : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoTransformation : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
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
   virtual SoType getTypeId() const { return _type; }
   
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
public Q_SLOTS:
SoVertexShape* new_SoVertexShape();
   bool  beginVertexArrayRendering(SoVertexShape* theWrappedObject, SoGLRenderAction*  action);
   void endVertexArrayRendering(SoVertexShape* theWrappedObject, SoGLRenderAction*  action, bool  vboWasUsed);
   SoType  static_SoVertexShape_getClassTypeId();
   SoVertexProperty*  getVertexProperty(SoVertexShape* theWrappedObject);
   void setNormalCache(SoVertexShape* theWrappedObject, SoState*  state, int  numNormals, const SbVec3f*  normals);
   bool  py_q_shouldGLRender(SoVertexShape* theWrappedObject, SoGLRenderAction*  action){  return (((PythonQtPublicPromoter_SoVertexShape*)theWrappedObject)->py_q_shouldGLRender(action));}
SoSFNode*  py_get_vertexProperty(SoVertexShape* theWrappedObject){ return &theWrappedObject->vertexProperty; }
};


