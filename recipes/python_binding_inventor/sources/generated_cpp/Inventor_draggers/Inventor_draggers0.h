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
#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SoInput.h>
#include <Inventor/SoOutput.h>
#include <Inventor/SoPath.h>
#include <Inventor/SoPickedPoint.h>
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
#include <Inventor/draggers/SoCenterballDragger.h>
#include <Inventor/draggers/SoDirectionalLightDragger.h>
#include <Inventor/draggers/SoDragPointDragger.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/draggers/SoHandleBoxDragger.h>
#include <Inventor/draggers/SoJackDragger.h>
#include <Inventor/draggers/SoPointLightDragger.h>
#include <Inventor/draggers/SoRotateCylindricalDragger.h>
#include <Inventor/draggers/SoRotateDiscDragger.h>
#include <Inventor/draggers/SoRotateSphericalDragger.h>
#include <Inventor/draggers/SoScale1Dragger.h>
#include <Inventor/draggers/SoScale2Dragger.h>
#include <Inventor/draggers/SoScale2UniformDragger.h>
#include <Inventor/draggers/SoScaleUniformDragger.h>
#include <Inventor/draggers/SoSpotLightDragger.h>
#include <Inventor/draggers/SoTabBoxDragger.h>
#include <Inventor/draggers/SoTabPlaneDragger.h>
#include <Inventor/draggers/SoTrackballDragger.h>
#include <Inventor/draggers/SoTransformBoxDragger.h>
#include <Inventor/draggers/SoTransformerDragger.h>
#include <Inventor/draggers/SoTranslate1Dragger.h>
#include <Inventor/draggers/SoTranslate2Dragger.h>
#include <Inventor/events/SoEvent.h>
#include <Inventor/fields/SoField.h>
#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/fields/SoFieldData.h>
#include <Inventor/misc/SoBase.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/projectors/SbCylinderProjector.h>
#include <Inventor/projectors/SbProjector.h>
#include <Inventor/projectors/SbSphereProjector.h>
#include <Inventor/sensors/SoSensor.h>
#include <stdexcept>



class PythonQtShell_SoCenterballDragger : public SoCenterballDragger
{
public:
    PythonQtShell_SoCenterballDragger():SoCenterballDragger(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoCenterballDragger() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void createDefaultParts() override;
void doAction(SoAction*  action) override;
SoNode*  getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
SoNode*  getPart(const SbName&  partName, bool  makeIfNeeded) override;
void handleEvent(SoHandleEventAction*  ha) override;
bool  mouseButtonPressed(const SoEvent*  ev) override;
bool  mouseButtonReleased(const SoEvent*  ev) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void saveStartParameters() override;
void search(SoSearchAction*  action) override;
bool  setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsPath(const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0) override;
void setDefaultOnNonWritingFields() override;
void setName(const SbName&  name) override;
bool  setPart(const SbName&  partName, SoNode*  from) override;
bool  setPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1) override;
bool  setPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1) override;
bool  setPartAsPath(const SbName&  partName, SoPath*  surrogatePath) override;
bool  setUpConnections(bool  onOff, bool  doItAlways = 0) override;
bool  shouldGrabBasedOnSurrogate(const SoPath*  pickPath, const SoPath*  surrogatePath) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoCenterballDragger : public SoCenterballDragger
{ public:
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
inline void promoted_getBoundingBox(SoGetBoundingBoxAction*  action) { this->getBoundingBox(action); }
inline void promoted_getMatrix(SoGetMatrixAction*  action) { this->getMatrix(action); }
static inline void promoted_kidFinishCB(void*  arg__1, SoDragger*  arg__2) { kidFinishCB(arg__1, arg__2); }
static inline void promoted_kidStartCB(void*  arg__1, SoDragger*  arg__2) { kidStartCB(arg__1, arg__2); }
inline void promoted_setDefaultOnNonWritingFields() { this->setDefaultOnNonWritingFields(); }
inline void promoted_setSwitches(SoDragger*  activeChild) { this->setSwitches(activeChild); }
inline bool  promoted_setUpConnections(bool  onOff, bool  doItAlways = 0) { return this->setUpConnections(onOff, doItAlways); }
inline void promoted_transferCenterDraggerMotion(SoDragger*  childDragger) { this->transferCenterDraggerMotion(childDragger); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoCenterballDragger::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoCenterballDragger::getMatrix(action); }
inline void py_q_saveStartParameters() { SoCenterballDragger::saveStartParameters(); }
inline void py_q_setDefaultOnNonWritingFields() { SoCenterballDragger::setDefaultOnNonWritingFields(); }
inline bool  py_q_setUpConnections(bool  onOff, bool  doItAlways = 0) { return SoCenterballDragger::setUpConnections(onOff, doItAlways); }
};

class PythonQtWrapper_SoCenterballDragger : public QObject
{ Q_OBJECT
public:
public slots:
SoCenterballDragger* new_SoCenterballDragger();
   void static_SoCenterballDragger_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   void py_q_getBoundingBox(SoCenterballDragger* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoCenterballDragger*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoCenterballDragger_getClassTypeId();
   void py_q_getMatrix(SoCenterballDragger* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoCenterballDragger*)theWrappedObject)->py_q_getMatrix(action));}
   void static_SoCenterballDragger_kidFinishCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoCenterballDragger_kidStartCB(void*  arg__1, SoDragger*  arg__2);
   void py_q_saveStartParameters(SoCenterballDragger* theWrappedObject){  (((PythonQtPublicPromoter_SoCenterballDragger*)theWrappedObject)->py_q_saveStartParameters());}
   void py_q_setDefaultOnNonWritingFields(SoCenterballDragger* theWrappedObject){  (((PythonQtPublicPromoter_SoCenterballDragger*)theWrappedObject)->py_q_setDefaultOnNonWritingFields());}
   void setSwitches(SoCenterballDragger* theWrappedObject, SoDragger*  activeChild);
   bool  py_q_setUpConnections(SoCenterballDragger* theWrappedObject, bool  onOff, bool  doItAlways = 0){  return (((PythonQtPublicPromoter_SoCenterballDragger*)theWrappedObject)->py_q_setUpConnections(onOff, doItAlways));}
   void transferCenterDraggerMotion(SoCenterballDragger* theWrappedObject, SoDragger*  childDragger);
   void static_SoCenterballDragger_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
SoSFVec3f*  py_get_center(SoCenterballDragger* theWrappedObject){ return &theWrappedObject->center; }
SoSFRotation*  py_get_rotation(SoCenterballDragger* theWrappedObject){ return &theWrappedObject->rotation; }
};





class PythonQtShell_SoDirectionalLightDragger : public SoDirectionalLightDragger
{
public:
    PythonQtShell_SoDirectionalLightDragger():SoDirectionalLightDragger(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoDirectionalLightDragger() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void createDefaultParts() override;
void doAction(SoAction*  action) override;
SoNode*  getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
SoNode*  getPart(const SbName&  partName, bool  makeIfNeeded) override;
void handleEvent(SoHandleEventAction*  ha) override;
bool  mouseButtonPressed(const SoEvent*  ev) override;
bool  mouseButtonReleased(const SoEvent*  ev) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void saveStartParameters() override;
void search(SoSearchAction*  action) override;
bool  setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsPath(const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0) override;
void setDefaultOnNonWritingFields() override;
void setName(const SbName&  name) override;
bool  setPart(const SbName&  partName, SoNode*  from) override;
bool  setPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1) override;
bool  setPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1) override;
bool  setPartAsPath(const SbName&  partName, SoPath*  surrogatePath) override;
bool  setUpConnections(bool  onOff, bool  doItAlways = 0) override;
bool  shouldGrabBasedOnSurrogate(const SoPath*  pickPath, const SoPath*  surrogatePath) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoDirectionalLightDragger : public SoDirectionalLightDragger
{ public:
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
inline void promoted_setDefaultOnNonWritingFields() { this->setDefaultOnNonWritingFields(); }
inline bool  promoted_setUpConnections(bool  onOff, bool  doItAlways = 0) { return this->setUpConnections(onOff, doItAlways); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline void py_q_setDefaultOnNonWritingFields() { SoDirectionalLightDragger::setDefaultOnNonWritingFields(); }
inline bool  py_q_setUpConnections(bool  onOff, bool  doItAlways = 0) { return SoDirectionalLightDragger::setUpConnections(onOff, doItAlways); }
};

class PythonQtWrapper_SoDirectionalLightDragger : public QObject
{ Q_OBJECT
public:
public slots:
SoDirectionalLightDragger* new_SoDirectionalLightDragger();
   void static_SoDirectionalLightDragger_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   SoType  static_SoDirectionalLightDragger_getClassTypeId();
   void py_q_setDefaultOnNonWritingFields(SoDirectionalLightDragger* theWrappedObject){  (((PythonQtPublicPromoter_SoDirectionalLightDragger*)theWrappedObject)->py_q_setDefaultOnNonWritingFields());}
   bool  py_q_setUpConnections(SoDirectionalLightDragger* theWrappedObject, bool  onOff, bool  doItAlways = 0){  return (((PythonQtPublicPromoter_SoDirectionalLightDragger*)theWrappedObject)->py_q_setUpConnections(onOff, doItAlways));}
   void static_SoDirectionalLightDragger_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
SoSFRotation*  py_get_rotation(SoDirectionalLightDragger* theWrappedObject){ return &theWrappedObject->rotation; }
SoSFVec3f*  py_get_translation(SoDirectionalLightDragger* theWrappedObject){ return &theWrappedObject->translation; }
};





class PythonQtShell_SoDragPointDragger : public SoDragPointDragger
{
public:
    PythonQtShell_SoDragPointDragger():SoDragPointDragger(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoDragPointDragger() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void createDefaultParts() override;
void doAction(SoAction*  action) override;
SoNode*  getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
SoNode*  getPart(const SbName&  partName, bool  makeIfNeeded) override;
void handleEvent(SoHandleEventAction*  ha) override;
bool  mouseButtonPressed(const SoEvent*  ev) override;
bool  mouseButtonReleased(const SoEvent*  ev) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void saveStartParameters() override;
void search(SoSearchAction*  action) override;
bool  setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsPath(const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0) override;
void setDefaultOnNonWritingFields() override;
void setName(const SbName&  name) override;
bool  setPart(const SbName&  partName, SoNode*  from) override;
bool  setPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1) override;
bool  setPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1) override;
bool  setPartAsPath(const SbName&  partName, SoPath*  surrogatePath) override;
bool  setUpConnections(bool  onOff, bool  doItAlways = 0) override;
bool  shouldGrabBasedOnSurrogate(const SoPath*  pickPath, const SoPath*  surrogatePath) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoDragPointDragger : public SoDragPointDragger
{ public:
inline void promoted_drag() { this->drag(); }
inline void promoted_dragFinish() { this->dragFinish(); }
inline void promoted_dragStart() { this->dragStart(); }
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
static inline void promoted_finishCB(void*  arg__1, SoDragger*  arg__2) { finishCB(arg__1, arg__2); }
static inline void promoted_metaKeyChangeCB(void*  arg__1, SoDragger*  arg__2) { metaKeyChangeCB(arg__1, arg__2); }
static inline void promoted_motionCB(void*  arg__1, SoDragger*  arg__2) { motionCB(arg__1, arg__2); }
inline void promoted_setDefaultOnNonWritingFields() { this->setDefaultOnNonWritingFields(); }
inline bool  promoted_setUpConnections(bool  onOff, bool  doItAlways = 0) { return this->setUpConnections(onOff, doItAlways); }
static inline void promoted_startCB(void*  arg__1, SoDragger*  arg__2) { startCB(arg__1, arg__2); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline void py_q_setDefaultOnNonWritingFields() { SoDragPointDragger::setDefaultOnNonWritingFields(); }
inline bool  py_q_setUpConnections(bool  onOff, bool  doItAlways = 0) { return SoDragPointDragger::setUpConnections(onOff, doItAlways); }
};

class PythonQtWrapper_SoDragPointDragger : public QObject
{ Q_OBJECT
public:
public slots:
SoDragPointDragger* new_SoDragPointDragger();
   void drag(SoDragPointDragger* theWrappedObject);
   void dragFinish(SoDragPointDragger* theWrappedObject);
   void dragStart(SoDragPointDragger* theWrappedObject);
   void static_SoDragPointDragger_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   void static_SoDragPointDragger_finishCB(void*  arg__1, SoDragger*  arg__2);
   SoType  static_SoDragPointDragger_getClassTypeId();
   float  getJumpLimit(SoDragPointDragger* theWrappedObject) const;
   void static_SoDragPointDragger_metaKeyChangeCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoDragPointDragger_motionCB(void*  arg__1, SoDragger*  arg__2);
   void py_q_setDefaultOnNonWritingFields(SoDragPointDragger* theWrappedObject){  (((PythonQtPublicPromoter_SoDragPointDragger*)theWrappedObject)->py_q_setDefaultOnNonWritingFields());}
   void setJumpLimit(SoDragPointDragger* theWrappedObject, float  limit);
   bool  py_q_setUpConnections(SoDragPointDragger* theWrappedObject, bool  onOff, bool  doItAlways = 0){  return (((PythonQtPublicPromoter_SoDragPointDragger*)theWrappedObject)->py_q_setUpConnections(onOff, doItAlways));}
   void showNextDraggerSet(SoDragPointDragger* theWrappedObject);
   void static_SoDragPointDragger_startCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoDragPointDragger_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
SoSFVec3f*  py_get_translation(SoDragPointDragger* theWrappedObject){ return &theWrappedObject->translation; }
};





class PythonQtShell_SoDragger : public SoDragger
{
public:
    PythonQtShell_SoDragger():SoDragger(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoDragger() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void createDefaultParts() override;
void doAction(SoAction*  action) override;
SoNode*  getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
SoNode*  getPart(const SbName&  partName, bool  makeIfNeeded) override;
void handleEvent(SoHandleEventAction*  ha) override;
bool  mouseButtonPressed(const SoEvent*  ev) override;
bool  mouseButtonReleased(const SoEvent*  ev) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void saveStartParameters() override;
void search(SoSearchAction*  action) override;
bool  setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsPath(const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0) override;
void setDefaultOnNonWritingFields() override;
void setName(const SbName&  name) override;
bool  setPart(const SbName&  partName, SoNode*  from) override;
bool  setPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1) override;
bool  setPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1) override;
bool  setPartAsPath(const SbName&  partName, SoPath*  surrogatePath) override;
bool  setUpConnections(bool  onOff, bool  doItAlways = 0) override;
bool  shouldGrabBasedOnSurrogate(const SoPath*  pickPath, const SoPath*  surrogatePath) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoDragger : public SoDragger
{ public:
static inline void promoted_childFinishCB(void*  arg__1, SoDragger*  arg__2) { childFinishCB(arg__1, arg__2); }
static inline void promoted_childMotionCB(void*  arg__1, SoDragger*  arg__2) { childMotionCB(arg__1, arg__2); }
static inline void promoted_childOtherEventCB(void*  arg__1, SoDragger*  arg__2) { childOtherEventCB(arg__1, arg__2); }
static inline void promoted_childStartCB(void*  arg__1, SoDragger*  arg__2) { childStartCB(arg__1, arg__2); }
static inline void promoted_childTransferMotionAndValueChangedCB(void*  arg__1, SoDragger*  arg__2) { childTransferMotionAndValueChangedCB(arg__1, arg__2); }
static inline void promoted_childValueChangedCB(void*  arg__1, SoDragger*  arg__2) { childValueChangedCB(arg__1, arg__2); }
inline SoDragger*  promoted_getActiveChildDragger() const { return this->getActiveChildDragger(); }
inline void promoted_getBoundingBox(SoGetBoundingBoxAction*  action) { this->getBoundingBox(action); }
inline SbVec2s  promoted_getLocaterPosition() { return this->getLocaterPosition(); }
inline SbVec2f  promoted_getNormalizedLocaterPosition() { return this->getNormalizedLocaterPosition(); }
inline SbVec2s  promoted_getStartLocaterPosition() const { return this->getStartLocaterPosition(); }
inline void promoted_handleEvent(SoHandleEventAction*  ha) { this->handleEvent(ha); }
inline bool  promoted_isAdequateConstraintMotion() { return this->isAdequateConstraintMotion(); }
inline bool  promoted_isIgnoreInBbox() { return this->isIgnoreInBbox(); }
inline bool  promoted_mouseButtonPressed(const SoEvent*  ev) { return this->mouseButtonPressed(ev); }
inline bool  promoted_mouseButtonReleased(const SoEvent*  ev) { return this->mouseButtonReleased(ev); }
inline void promoted_setActiveChildDragger(SoDragger*  newChildDragger) { this->setActiveChildDragger(newChildDragger); }
inline void promoted_setCameraInfo(SoAction*  action) { this->setCameraInfo(action); }
inline void promoted_setDefaultOnNonWritingFields() { this->setDefaultOnNonWritingFields(); }
inline void promoted_setIgnoreInBbox(bool  newVal) { this->setIgnoreInBbox(newVal); }
inline void promoted_setStartLocaterPosition(SbVec2s  p) { this->setStartLocaterPosition(p); }
inline bool  promoted_shouldGrabBasedOnSurrogate(const SoPath*  pickPath, const SoPath*  surrogatePath) { return this->shouldGrabBasedOnSurrogate(pickPath, surrogatePath); }
inline void promoted_transferMotion(SoDragger*  child) { this->transferMotion(child); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoDragger::getBoundingBox(action); }
inline void py_q_handleEvent(SoHandleEventAction*  ha) { SoDragger::handleEvent(ha); }
inline bool  py_q_mouseButtonPressed(const SoEvent*  ev) { return SoDragger::mouseButtonPressed(ev); }
inline bool  py_q_mouseButtonReleased(const SoEvent*  ev) { return SoDragger::mouseButtonReleased(ev); }
inline void py_q_saveStartParameters() { SoDragger::saveStartParameters(); }
inline void py_q_setDefaultOnNonWritingFields() { SoDragger::setDefaultOnNonWritingFields(); }
inline bool  py_q_shouldGrabBasedOnSurrogate(const SoPath*  pickPath, const SoPath*  surrogatePath) { return SoDragger::shouldGrabBasedOnSurrogate(pickPath, surrogatePath); }
};

class PythonQtWrapper_SoDragger : public QObject
{ Q_OBJECT
public:
Q_ENUMS(ProjectorFrontSetting )
enum ProjectorFrontSetting{
  FRONT = SoDragger::FRONT,   BACK = SoDragger::BACK,   USE_PICK = SoDragger::USE_PICK};
public slots:
SoDragger* new_SoDragger();
   SbMatrix  static_SoDragger_appendRotation(const SbMatrix&  mtx, const SbRotation&  rot, const SbVec3f&  rotCenter, const SbMatrix*  conversion = nullptr);
   SbMatrix  static_SoDragger_appendScale(const SbMatrix&  mtx, const SbVec3f&  scale, const SbVec3f&  scaleCenter, const SbMatrix*  conversion = nullptr);
   SbMatrix  static_SoDragger_appendTranslation(const SbMatrix&  mtx, const SbVec3f&  translation, const SbMatrix*  conversion = nullptr);
   void static_SoDragger_childFinishCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoDragger_childMotionCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoDragger_childOtherEventCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoDragger_childStartCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoDragger_childTransferMotionAndValueChangedCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoDragger_childValueChangedCB(void*  arg__1, SoDragger*  arg__2);
   SoPath*  createPathToThis(SoDragger* theWrappedObject);
   bool  enableValueChangedCallbacks(SoDragger* theWrappedObject, bool  newVal);
   SoDragger*  getActiveChildDragger(SoDragger* theWrappedObject) const;
   void py_q_getBoundingBox(SoDragger* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoDragger*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoDragger_getClassTypeId();
   const SoEvent*  getEvent(SoDragger* theWrappedObject) const;
   SoDragger::ProjectorFrontSetting  getFrontOnProjector(SoDragger* theWrappedObject) const;
   SoHandleEventAction*  getHandleEventAction(SoDragger* theWrappedObject) const;
   SbVec3f  getLocalStartingPoint(SoDragger* theWrappedObject);
   SbMatrix  getLocalToWorldMatrix(SoDragger* theWrappedObject);
   SbVec2s  getLocaterPosition(SoDragger* theWrappedObject);
   int  getMinGesture(SoDragger* theWrappedObject) const;
   float  static_SoDragger_getMinScale();
   const SbMatrix*  getMotionMatrix(SoDragger* theWrappedObject);
   SbVec2f  getNormalizedLocaterPosition(SoDragger* theWrappedObject);
   void getPartToLocalMatrix(SoDragger* theWrappedObject, const SbName&  partName, SbMatrix&  partToLocalMatrix, SbMatrix&  localToPartMatrix);
   const SoPath*  getPickPath(SoDragger* theWrappedObject) const;
   SbVec2s  getStartLocaterPosition(SoDragger* theWrappedObject) const;
   const SbMatrix*  getStartMotionMatrix(SoDragger* theWrappedObject);
   const SbName*  getSurrogatePartPickedName(SoDragger* theWrappedObject) const;
   const SoPath*  getSurrogatePartPickedOwner(SoDragger* theWrappedObject) const;
   const SoPath*  getSurrogatePartPickedPath(SoDragger* theWrappedObject) const;
   void static_SoDragger_getTransformFast(SbMatrix&  mtx, SbVec3f&  translation, SbRotation&  rotation, SbVec3f&  scaleFactor, SbRotation&  scaleOrientation);
   void static_SoDragger_getTransformFast(SbMatrix&  mtx, SbVec3f&  translation, SbRotation&  rotation, SbVec3f&  scaleFactor, SbRotation&  scaleOrientation, const SbVec3f&  center);
   const SbViewVolume*  getViewVolume(SoDragger* theWrappedObject);
   const SbViewportRegion*  getViewportRegion(SoDragger* theWrappedObject);
   SbVec3f  getWorldStartingPoint(SoDragger* theWrappedObject);
   SbMatrix  getWorldToLocalMatrix(SoDragger* theWrappedObject);
   void py_q_handleEvent(SoDragger* theWrappedObject, SoHandleEventAction*  ha){  (((PythonQtPublicPromoter_SoDragger*)theWrappedObject)->py_q_handleEvent(ha));}
   bool  isAdequateConstraintMotion(SoDragger* theWrappedObject);
   bool  isIgnoreInBbox(SoDragger* theWrappedObject);
   bool  mouseButtonPressed(SoDragger* theWrappedObject, const SoEvent*  ev);
   bool  py_q_mouseButtonPressed(SoDragger* theWrappedObject, const SoEvent*  ev){  return (((PythonQtPublicPromoter_SoDragger*)theWrappedObject)->py_q_mouseButtonPressed(ev));}
   bool  mouseButtonReleased(SoDragger* theWrappedObject, const SoEvent*  ev);
   bool  py_q_mouseButtonReleased(SoDragger* theWrappedObject, const SoEvent*  ev){  return (((PythonQtPublicPromoter_SoDragger*)theWrappedObject)->py_q_mouseButtonReleased(ev));}
   void registerChildDragger(SoDragger* theWrappedObject, SoDragger*  child);
   void registerChildDraggerMovingIndependently(SoDragger* theWrappedObject, SoDragger*  child);
   void saveStartParameters(SoDragger* theWrappedObject);
   void py_q_saveStartParameters(SoDragger* theWrappedObject){  (((PythonQtPublicPromoter_SoDragger*)theWrappedObject)->py_q_saveStartParameters());}
   void setActiveChildDragger(SoDragger* theWrappedObject, SoDragger*  newChildDragger);
   void setCameraInfo(SoDragger* theWrappedObject, SoAction*  action);
   void py_q_setDefaultOnNonWritingFields(SoDragger* theWrappedObject){  (((PythonQtPublicPromoter_SoDragger*)theWrappedObject)->py_q_setDefaultOnNonWritingFields());}
   void setFrontOnProjector(SoDragger* theWrappedObject, SoDragger::ProjectorFrontSetting  newVal);
   void setHandleEventAction(SoDragger* theWrappedObject, SoHandleEventAction*  newAction);
   void setIgnoreInBbox(SoDragger* theWrappedObject, bool  newVal);
   void setMinGesture(SoDragger* theWrappedObject, int  pixels);
   void static_SoDragger_setMinScale(float  newMinScale);
   void setMotionMatrix(SoDragger* theWrappedObject, const SbMatrix&  newMatrix);
   void setStartLocaterPosition(SoDragger* theWrappedObject, SbVec2s  p);
   void setStartingPoint(SoDragger* theWrappedObject, const SbVec3f&  newPoint);
   void setStartingPoint(SoDragger* theWrappedObject, const SoPickedPoint*  newPoint);
   void setTempPathToThis(SoDragger* theWrappedObject, const SoPath*  somethingClose);
   void setViewVolume(SoDragger* theWrappedObject, const SbViewVolume&  vol);
   void setViewportRegion(SoDragger* theWrappedObject, const SbViewportRegion&  reg);
   bool  shouldGrabBasedOnSurrogate(SoDragger* theWrappedObject, const SoPath*  pickPath, const SoPath*  surrogatePath);
   bool  py_q_shouldGrabBasedOnSurrogate(SoDragger* theWrappedObject, const SoPath*  pickPath, const SoPath*  surrogatePath){  return (((PythonQtPublicPromoter_SoDragger*)theWrappedObject)->py_q_shouldGrabBasedOnSurrogate(pickPath, surrogatePath));}
   void transferMotion(SoDragger* theWrappedObject, SoDragger*  child);
   void transformMatrixLocalToWorld(SoDragger* theWrappedObject, const SbMatrix&  fromMatrix, SbMatrix&  toMatrix);
   void transformMatrixToLocalSpace(SoDragger* theWrappedObject, const SbMatrix&  fromMatrix, SbMatrix&  toMatrix, const SbName&  fromSpacePartName);
   void transformMatrixWorldToLocal(SoDragger* theWrappedObject, const SbMatrix&  fromMatrix, SbMatrix&  toMatrix);
   void unregisterChildDragger(SoDragger* theWrappedObject, SoDragger*  child);
   void unregisterChildDraggerMovingIndependently(SoDragger* theWrappedObject, SoDragger*  child);
   void valueChanged(SoDragger* theWrappedObject);
   void workFieldsIntoTransform(SoDragger* theWrappedObject, SbMatrix&  mtx);
   void static_SoDragger_workValuesIntoTransform(SbMatrix&  mtx, const SbVec3f*  translationPtr, const SbRotation*  rotationPtr, const SbVec3f*  scaleFactorPtr, const SbRotation*  scaleOrientationPtr, const SbVec3f*  centerPtr);
SoSFBool*  py_get_enable(SoDragger* theWrappedObject){ return &theWrappedObject->enable; }
SoSFBool*  py_get_isActive(SoDragger* theWrappedObject){ return &theWrappedObject->isActive; }
};





class PythonQtShell_SoHandleBoxDragger : public SoHandleBoxDragger
{
public:
    PythonQtShell_SoHandleBoxDragger():SoHandleBoxDragger(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoHandleBoxDragger() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void createDefaultParts() override;
void doAction(SoAction*  action) override;
SoNode*  getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
SoNode*  getPart(const SbName&  partName, bool  makeIfNeeded) override;
void handleEvent(SoHandleEventAction*  ha) override;
bool  mouseButtonPressed(const SoEvent*  ev) override;
bool  mouseButtonReleased(const SoEvent*  ev) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void saveStartParameters() override;
void search(SoSearchAction*  action) override;
bool  setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsPath(const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0) override;
void setDefaultOnNonWritingFields() override;
void setName(const SbName&  name) override;
bool  setPart(const SbName&  partName, SoNode*  from) override;
bool  setPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1) override;
bool  setPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1) override;
bool  setPartAsPath(const SbName&  partName, SoPath*  surrogatePath) override;
bool  setUpConnections(bool  onOff, bool  doItAlways = 0) override;
bool  shouldGrabBasedOnSurrogate(const SoPath*  pickPath, const SoPath*  surrogatePath) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoHandleBoxDragger : public SoHandleBoxDragger
{ public:
inline void promoted_drag() { this->drag(); }
inline void promoted_dragFinish() { this->dragFinish(); }
inline void promoted_dragStart() { this->dragStart(); }
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
static inline void promoted_finishCB(void*  arg__1, SoDragger*  arg__2) { finishCB(arg__1, arg__2); }
static inline void promoted_metaKeyChangeCB(void*  arg__1, SoDragger*  arg__2) { metaKeyChangeCB(arg__1, arg__2); }
static inline void promoted_motionCB(void*  arg__1, SoDragger*  arg__2) { motionCB(arg__1, arg__2); }
inline void promoted_setAllPartsActive(bool  onOrOff) { this->setAllPartsActive(onOrOff); }
inline void promoted_setDefaultOnNonWritingFields() { this->setDefaultOnNonWritingFields(); }
inline bool  promoted_setUpConnections(bool  onOff, bool  doItAlways = 0) { return this->setUpConnections(onOff, doItAlways); }
static inline void promoted_startCB(void*  arg__1, SoDragger*  arg__2) { startCB(arg__1, arg__2); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline void py_q_setDefaultOnNonWritingFields() { SoHandleBoxDragger::setDefaultOnNonWritingFields(); }
inline bool  py_q_setUpConnections(bool  onOff, bool  doItAlways = 0) { return SoHandleBoxDragger::setUpConnections(onOff, doItAlways); }
};

class PythonQtWrapper_SoHandleBoxDragger : public QObject
{ Q_OBJECT
public:
public slots:
SoHandleBoxDragger* new_SoHandleBoxDragger();
   void drag(SoHandleBoxDragger* theWrappedObject);
   void dragFinish(SoHandleBoxDragger* theWrappedObject);
   void dragStart(SoHandleBoxDragger* theWrappedObject);
   void static_SoHandleBoxDragger_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   void static_SoHandleBoxDragger_finishCB(void*  arg__1, SoDragger*  arg__2);
   SoType  static_SoHandleBoxDragger_getClassTypeId();
   void static_SoHandleBoxDragger_metaKeyChangeCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoHandleBoxDragger_motionCB(void*  arg__1, SoDragger*  arg__2);
   void setAllPartsActive(SoHandleBoxDragger* theWrappedObject, bool  onOrOff);
   void py_q_setDefaultOnNonWritingFields(SoHandleBoxDragger* theWrappedObject){  (((PythonQtPublicPromoter_SoHandleBoxDragger*)theWrappedObject)->py_q_setDefaultOnNonWritingFields());}
   bool  py_q_setUpConnections(SoHandleBoxDragger* theWrappedObject, bool  onOff, bool  doItAlways = 0){  return (((PythonQtPublicPromoter_SoHandleBoxDragger*)theWrappedObject)->py_q_setUpConnections(onOff, doItAlways));}
   void static_SoHandleBoxDragger_startCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoHandleBoxDragger_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
SoSFVec3f*  py_get_scaleFactor(SoHandleBoxDragger* theWrappedObject){ return &theWrappedObject->scaleFactor; }
SoSFVec3f*  py_get_translation(SoHandleBoxDragger* theWrappedObject){ return &theWrappedObject->translation; }
};





class PythonQtShell_SoJackDragger : public SoJackDragger
{
public:
    PythonQtShell_SoJackDragger():SoJackDragger(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoJackDragger() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void createDefaultParts() override;
void doAction(SoAction*  action) override;
SoNode*  getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
SoNode*  getPart(const SbName&  partName, bool  makeIfNeeded) override;
void handleEvent(SoHandleEventAction*  ha) override;
bool  mouseButtonPressed(const SoEvent*  ev) override;
bool  mouseButtonReleased(const SoEvent*  ev) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void saveStartParameters() override;
void search(SoSearchAction*  action) override;
bool  setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsPath(const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0) override;
void setDefaultOnNonWritingFields() override;
void setName(const SbName&  name) override;
bool  setPart(const SbName&  partName, SoNode*  from) override;
bool  setPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1) override;
bool  setPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1) override;
bool  setPartAsPath(const SbName&  partName, SoPath*  surrogatePath) override;
bool  setUpConnections(bool  onOff, bool  doItAlways = 0) override;
bool  shouldGrabBasedOnSurrogate(const SoPath*  pickPath, const SoPath*  surrogatePath) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoJackDragger : public SoJackDragger
{ public:
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
static inline void promoted_invalidateSurroundScaleCB(void*  arg__1, SoDragger*  arg__2) { invalidateSurroundScaleCB(arg__1, arg__2); }
inline void promoted_setDefaultOnNonWritingFields() { this->setDefaultOnNonWritingFields(); }
inline bool  promoted_setUpConnections(bool  onOff, bool  doItAlways = 0) { return this->setUpConnections(onOff, doItAlways); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline void py_q_setDefaultOnNonWritingFields() { SoJackDragger::setDefaultOnNonWritingFields(); }
inline bool  py_q_setUpConnections(bool  onOff, bool  doItAlways = 0) { return SoJackDragger::setUpConnections(onOff, doItAlways); }
};

class PythonQtWrapper_SoJackDragger : public QObject
{ Q_OBJECT
public:
public slots:
SoJackDragger* new_SoJackDragger();
   void static_SoJackDragger_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   SoType  static_SoJackDragger_getClassTypeId();
   void static_SoJackDragger_invalidateSurroundScaleCB(void*  arg__1, SoDragger*  arg__2);
   void py_q_setDefaultOnNonWritingFields(SoJackDragger* theWrappedObject){  (((PythonQtPublicPromoter_SoJackDragger*)theWrappedObject)->py_q_setDefaultOnNonWritingFields());}
   bool  py_q_setUpConnections(SoJackDragger* theWrappedObject, bool  onOff, bool  doItAlways = 0){  return (((PythonQtPublicPromoter_SoJackDragger*)theWrappedObject)->py_q_setUpConnections(onOff, doItAlways));}
   void static_SoJackDragger_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
SoSFRotation*  py_get_rotation(SoJackDragger* theWrappedObject){ return &theWrappedObject->rotation; }
SoSFVec3f*  py_get_scaleFactor(SoJackDragger* theWrappedObject){ return &theWrappedObject->scaleFactor; }
SoSFVec3f*  py_get_translation(SoJackDragger* theWrappedObject){ return &theWrappedObject->translation; }
};





class PythonQtShell_SoPointLightDragger : public SoPointLightDragger
{
public:
    PythonQtShell_SoPointLightDragger():SoPointLightDragger(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoPointLightDragger() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void createDefaultParts() override;
void doAction(SoAction*  action) override;
SoNode*  getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
SoNode*  getPart(const SbName&  partName, bool  makeIfNeeded) override;
void handleEvent(SoHandleEventAction*  ha) override;
bool  mouseButtonPressed(const SoEvent*  ev) override;
bool  mouseButtonReleased(const SoEvent*  ev) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void saveStartParameters() override;
void search(SoSearchAction*  action) override;
bool  setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsPath(const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0) override;
void setDefaultOnNonWritingFields() override;
void setName(const SbName&  name) override;
bool  setPart(const SbName&  partName, SoNode*  from) override;
bool  setPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1) override;
bool  setPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1) override;
bool  setPartAsPath(const SbName&  partName, SoPath*  surrogatePath) override;
bool  setUpConnections(bool  onOff, bool  doItAlways = 0) override;
bool  shouldGrabBasedOnSurrogate(const SoPath*  pickPath, const SoPath*  surrogatePath) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoPointLightDragger : public SoPointLightDragger
{ public:
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
inline void promoted_setDefaultOnNonWritingFields() { this->setDefaultOnNonWritingFields(); }
inline bool  promoted_setUpConnections(bool  onOff, bool  doItAlways = 0) { return this->setUpConnections(onOff, doItAlways); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline void py_q_setDefaultOnNonWritingFields() { SoPointLightDragger::setDefaultOnNonWritingFields(); }
inline bool  py_q_setUpConnections(bool  onOff, bool  doItAlways = 0) { return SoPointLightDragger::setUpConnections(onOff, doItAlways); }
};

class PythonQtWrapper_SoPointLightDragger : public QObject
{ Q_OBJECT
public:
public slots:
SoPointLightDragger* new_SoPointLightDragger();
   void static_SoPointLightDragger_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   SoType  static_SoPointLightDragger_getClassTypeId();
   void py_q_setDefaultOnNonWritingFields(SoPointLightDragger* theWrappedObject){  (((PythonQtPublicPromoter_SoPointLightDragger*)theWrappedObject)->py_q_setDefaultOnNonWritingFields());}
   bool  py_q_setUpConnections(SoPointLightDragger* theWrappedObject, bool  onOff, bool  doItAlways = 0){  return (((PythonQtPublicPromoter_SoPointLightDragger*)theWrappedObject)->py_q_setUpConnections(onOff, doItAlways));}
   void static_SoPointLightDragger_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
SoSFVec3f*  py_get_translation(SoPointLightDragger* theWrappedObject){ return &theWrappedObject->translation; }
};





class PythonQtShell_SoRotateCylindricalDragger : public SoRotateCylindricalDragger
{
public:
    PythonQtShell_SoRotateCylindricalDragger():SoRotateCylindricalDragger(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoRotateCylindricalDragger() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void createDefaultParts() override;
void doAction(SoAction*  action) override;
SoNode*  getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
SoNode*  getPart(const SbName&  partName, bool  makeIfNeeded) override;
void handleEvent(SoHandleEventAction*  ha) override;
bool  mouseButtonPressed(const SoEvent*  ev) override;
bool  mouseButtonReleased(const SoEvent*  ev) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void saveStartParameters() override;
void search(SoSearchAction*  action) override;
bool  setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsPath(const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0) override;
void setDefaultOnNonWritingFields() override;
void setName(const SbName&  name) override;
bool  setPart(const SbName&  partName, SoNode*  from) override;
bool  setPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1) override;
bool  setPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1) override;
bool  setPartAsPath(const SbName&  partName, SoPath*  surrogatePath) override;
bool  setUpConnections(bool  onOff, bool  doItAlways = 0) override;
bool  shouldGrabBasedOnSurrogate(const SoPath*  pickPath, const SoPath*  surrogatePath) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoRotateCylindricalDragger : public SoRotateCylindricalDragger
{ public:
static inline void promoted_doneCB(void*  arg__1, SoDragger*  arg__2) { doneCB(arg__1, arg__2); }
inline void promoted_drag() { this->drag(); }
inline void promoted_dragFinish() { this->dragFinish(); }
inline void promoted_dragStart() { this->dragStart(); }
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
static inline void promoted_motionCB(void*  arg__1, SoDragger*  arg__2) { motionCB(arg__1, arg__2); }
inline bool  promoted_setUpConnections(bool  onOff, bool  doItAlways = 0) { return this->setUpConnections(onOff, doItAlways); }
static inline void promoted_startCB(void*  arg__1, SoDragger*  arg__2) { startCB(arg__1, arg__2); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline bool  py_q_setUpConnections(bool  onOff, bool  doItAlways = 0) { return SoRotateCylindricalDragger::setUpConnections(onOff, doItAlways); }
};

class PythonQtWrapper_SoRotateCylindricalDragger : public QObject
{ Q_OBJECT
public:
public slots:
SoRotateCylindricalDragger* new_SoRotateCylindricalDragger();
   void static_SoRotateCylindricalDragger_doneCB(void*  arg__1, SoDragger*  arg__2);
   void drag(SoRotateCylindricalDragger* theWrappedObject);
   void dragFinish(SoRotateCylindricalDragger* theWrappedObject);
   void dragStart(SoRotateCylindricalDragger* theWrappedObject);
   void static_SoRotateCylindricalDragger_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   SoType  static_SoRotateCylindricalDragger_getClassTypeId();
   const SbCylinderProjector*  getProjector(SoRotateCylindricalDragger* theWrappedObject) const;
   void static_SoRotateCylindricalDragger_motionCB(void*  arg__1, SoDragger*  arg__2);
   void setProjector(SoRotateCylindricalDragger* theWrappedObject, SbCylinderProjector*  p);
   bool  py_q_setUpConnections(SoRotateCylindricalDragger* theWrappedObject, bool  onOff, bool  doItAlways = 0){  return (((PythonQtPublicPromoter_SoRotateCylindricalDragger*)theWrappedObject)->py_q_setUpConnections(onOff, doItAlways));}
   void static_SoRotateCylindricalDragger_startCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoRotateCylindricalDragger_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
SoSFRotation*  py_get_rotation(SoRotateCylindricalDragger* theWrappedObject){ return &theWrappedObject->rotation; }
};





class PythonQtShell_SoRotateDiscDragger : public SoRotateDiscDragger
{
public:
    PythonQtShell_SoRotateDiscDragger():SoRotateDiscDragger(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoRotateDiscDragger() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void createDefaultParts() override;
void doAction(SoAction*  action) override;
SoNode*  getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
SoNode*  getPart(const SbName&  partName, bool  makeIfNeeded) override;
void handleEvent(SoHandleEventAction*  ha) override;
bool  mouseButtonPressed(const SoEvent*  ev) override;
bool  mouseButtonReleased(const SoEvent*  ev) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void saveStartParameters() override;
void search(SoSearchAction*  action) override;
bool  setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsPath(const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0) override;
void setDefaultOnNonWritingFields() override;
void setName(const SbName&  name) override;
bool  setPart(const SbName&  partName, SoNode*  from) override;
bool  setPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1) override;
bool  setPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1) override;
bool  setPartAsPath(const SbName&  partName, SoPath*  surrogatePath) override;
bool  setUpConnections(bool  onOff, bool  doItAlways = 0) override;
bool  shouldGrabBasedOnSurrogate(const SoPath*  pickPath, const SoPath*  surrogatePath) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoRotateDiscDragger : public SoRotateDiscDragger
{ public:
static inline void promoted_doneCB(void*  arg__1, SoDragger*  arg__2) { doneCB(arg__1, arg__2); }
inline void promoted_drag() { this->drag(); }
inline void promoted_dragFinish() { this->dragFinish(); }
inline void promoted_dragStart() { this->dragStart(); }
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
static inline void promoted_motionCB(void*  arg__1, SoDragger*  arg__2) { motionCB(arg__1, arg__2); }
inline bool  promoted_setUpConnections(bool  onOff, bool  doItAlways = 0) { return this->setUpConnections(onOff, doItAlways); }
static inline void promoted_startCB(void*  arg__1, SoDragger*  arg__2) { startCB(arg__1, arg__2); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline bool  py_q_setUpConnections(bool  onOff, bool  doItAlways = 0) { return SoRotateDiscDragger::setUpConnections(onOff, doItAlways); }
};

class PythonQtWrapper_SoRotateDiscDragger : public QObject
{ Q_OBJECT
public:
public slots:
SoRotateDiscDragger* new_SoRotateDiscDragger();
   void static_SoRotateDiscDragger_doneCB(void*  arg__1, SoDragger*  arg__2);
   void drag(SoRotateDiscDragger* theWrappedObject);
   void dragFinish(SoRotateDiscDragger* theWrappedObject);
   void dragStart(SoRotateDiscDragger* theWrappedObject);
   void static_SoRotateDiscDragger_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   SoType  static_SoRotateDiscDragger_getClassTypeId();
   void static_SoRotateDiscDragger_motionCB(void*  arg__1, SoDragger*  arg__2);
   bool  py_q_setUpConnections(SoRotateDiscDragger* theWrappedObject, bool  onOff, bool  doItAlways = 0){  return (((PythonQtPublicPromoter_SoRotateDiscDragger*)theWrappedObject)->py_q_setUpConnections(onOff, doItAlways));}
   void static_SoRotateDiscDragger_startCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoRotateDiscDragger_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
SoSFRotation*  py_get_rotation(SoRotateDiscDragger* theWrappedObject){ return &theWrappedObject->rotation; }
};





class PythonQtShell_SoRotateSphericalDragger : public SoRotateSphericalDragger
{
public:
    PythonQtShell_SoRotateSphericalDragger():SoRotateSphericalDragger(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoRotateSphericalDragger() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void createDefaultParts() override;
void doAction(SoAction*  action) override;
SoNode*  getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
SoNode*  getPart(const SbName&  partName, bool  makeIfNeeded) override;
void handleEvent(SoHandleEventAction*  ha) override;
bool  mouseButtonPressed(const SoEvent*  ev) override;
bool  mouseButtonReleased(const SoEvent*  ev) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void saveStartParameters() override;
void search(SoSearchAction*  action) override;
bool  setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsPath(const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0) override;
void setDefaultOnNonWritingFields() override;
void setName(const SbName&  name) override;
bool  setPart(const SbName&  partName, SoNode*  from) override;
bool  setPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1) override;
bool  setPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1) override;
bool  setPartAsPath(const SbName&  partName, SoPath*  surrogatePath) override;
bool  setUpConnections(bool  onOff, bool  doItAlways = 0) override;
bool  shouldGrabBasedOnSurrogate(const SoPath*  pickPath, const SoPath*  surrogatePath) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoRotateSphericalDragger : public SoRotateSphericalDragger
{ public:
static inline void promoted_doneCB(void*  arg__1, SoDragger*  arg__2) { doneCB(arg__1, arg__2); }
inline void promoted_drag() { this->drag(); }
inline void promoted_dragFinish() { this->dragFinish(); }
inline void promoted_dragStart() { this->dragStart(); }
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
static inline void promoted_motionCB(void*  arg__1, SoDragger*  arg__2) { motionCB(arg__1, arg__2); }
inline bool  promoted_setUpConnections(bool  onOff, bool  doItAlways = 0) { return this->setUpConnections(onOff, doItAlways); }
static inline void promoted_startCB(void*  arg__1, SoDragger*  arg__2) { startCB(arg__1, arg__2); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline bool  py_q_setUpConnections(bool  onOff, bool  doItAlways = 0) { return SoRotateSphericalDragger::setUpConnections(onOff, doItAlways); }
};

class PythonQtWrapper_SoRotateSphericalDragger : public QObject
{ Q_OBJECT
public:
public slots:
SoRotateSphericalDragger* new_SoRotateSphericalDragger();
   void static_SoRotateSphericalDragger_doneCB(void*  arg__1, SoDragger*  arg__2);
   void drag(SoRotateSphericalDragger* theWrappedObject);
   void dragFinish(SoRotateSphericalDragger* theWrappedObject);
   void dragStart(SoRotateSphericalDragger* theWrappedObject);
   void static_SoRotateSphericalDragger_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   SoType  static_SoRotateSphericalDragger_getClassTypeId();
   const SbSphereProjector*  getProjector(SoRotateSphericalDragger* theWrappedObject) const;
   void static_SoRotateSphericalDragger_motionCB(void*  arg__1, SoDragger*  arg__2);
   void setProjector(SoRotateSphericalDragger* theWrappedObject, SbSphereProjector*  p);
   bool  py_q_setUpConnections(SoRotateSphericalDragger* theWrappedObject, bool  onOff, bool  doItAlways = 0){  return (((PythonQtPublicPromoter_SoRotateSphericalDragger*)theWrappedObject)->py_q_setUpConnections(onOff, doItAlways));}
   void static_SoRotateSphericalDragger_startCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoRotateSphericalDragger_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
SoSFRotation*  py_get_rotation(SoRotateSphericalDragger* theWrappedObject){ return &theWrappedObject->rotation; }
};





class PythonQtShell_SoScale1Dragger : public SoScale1Dragger
{
public:
    PythonQtShell_SoScale1Dragger():SoScale1Dragger(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoScale1Dragger() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void createDefaultParts() override;
void doAction(SoAction*  action) override;
SoNode*  getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
SoNode*  getPart(const SbName&  partName, bool  makeIfNeeded) override;
void handleEvent(SoHandleEventAction*  ha) override;
bool  mouseButtonPressed(const SoEvent*  ev) override;
bool  mouseButtonReleased(const SoEvent*  ev) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void saveStartParameters() override;
void search(SoSearchAction*  action) override;
bool  setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsPath(const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0) override;
void setDefaultOnNonWritingFields() override;
void setName(const SbName&  name) override;
bool  setPart(const SbName&  partName, SoNode*  from) override;
bool  setPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1) override;
bool  setPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1) override;
bool  setPartAsPath(const SbName&  partName, SoPath*  surrogatePath) override;
bool  setUpConnections(bool  onOff, bool  doItAlways = 0) override;
bool  shouldGrabBasedOnSurrogate(const SoPath*  pickPath, const SoPath*  surrogatePath) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoScale1Dragger : public SoScale1Dragger
{ public:
inline void promoted_drag() { this->drag(); }
inline void promoted_dragFinish() { this->dragFinish(); }
inline void promoted_dragStart() { this->dragStart(); }
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
static inline void promoted_finishCB(void*  arg__1, SoDragger*  arg__2) { finishCB(arg__1, arg__2); }
static inline void promoted_motionCB(void*  arg__1, SoDragger*  arg__2) { motionCB(arg__1, arg__2); }
inline bool  promoted_setUpConnections(bool  onOff, bool  doItAlways = 0) { return this->setUpConnections(onOff, doItAlways); }
static inline void promoted_startCB(void*  arg__1, SoDragger*  arg__2) { startCB(arg__1, arg__2); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline bool  py_q_setUpConnections(bool  onOff, bool  doItAlways = 0) { return SoScale1Dragger::setUpConnections(onOff, doItAlways); }
};

class PythonQtWrapper_SoScale1Dragger : public QObject
{ Q_OBJECT
public:
public slots:
SoScale1Dragger* new_SoScale1Dragger();
   void drag(SoScale1Dragger* theWrappedObject);
   void dragFinish(SoScale1Dragger* theWrappedObject);
   void dragStart(SoScale1Dragger* theWrappedObject);
   void static_SoScale1Dragger_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   void static_SoScale1Dragger_finishCB(void*  arg__1, SoDragger*  arg__2);
   SoType  static_SoScale1Dragger_getClassTypeId();
   void static_SoScale1Dragger_motionCB(void*  arg__1, SoDragger*  arg__2);
   bool  py_q_setUpConnections(SoScale1Dragger* theWrappedObject, bool  onOff, bool  doItAlways = 0){  return (((PythonQtPublicPromoter_SoScale1Dragger*)theWrappedObject)->py_q_setUpConnections(onOff, doItAlways));}
   void static_SoScale1Dragger_startCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoScale1Dragger_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
SoSFVec3f*  py_get_scaleFactor(SoScale1Dragger* theWrappedObject){ return &theWrappedObject->scaleFactor; }
};





class PythonQtShell_SoScale2Dragger : public SoScale2Dragger
{
public:
    PythonQtShell_SoScale2Dragger():SoScale2Dragger(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoScale2Dragger() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void createDefaultParts() override;
void doAction(SoAction*  action) override;
SoNode*  getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
SoNode*  getPart(const SbName&  partName, bool  makeIfNeeded) override;
void handleEvent(SoHandleEventAction*  ha) override;
bool  mouseButtonPressed(const SoEvent*  ev) override;
bool  mouseButtonReleased(const SoEvent*  ev) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void saveStartParameters() override;
void search(SoSearchAction*  action) override;
bool  setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsPath(const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0) override;
void setDefaultOnNonWritingFields() override;
void setName(const SbName&  name) override;
bool  setPart(const SbName&  partName, SoNode*  from) override;
bool  setPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1) override;
bool  setPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1) override;
bool  setPartAsPath(const SbName&  partName, SoPath*  surrogatePath) override;
bool  setUpConnections(bool  onOff, bool  doItAlways = 0) override;
bool  shouldGrabBasedOnSurrogate(const SoPath*  pickPath, const SoPath*  surrogatePath) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoScale2Dragger : public SoScale2Dragger
{ public:
inline void promoted_drag() { this->drag(); }
inline void promoted_dragFinish() { this->dragFinish(); }
inline void promoted_dragStart() { this->dragStart(); }
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
static inline void promoted_finishCB(void*  arg__1, SoDragger*  arg__2) { finishCB(arg__1, arg__2); }
static inline void promoted_motionCB(void*  arg__1, SoDragger*  arg__2) { motionCB(arg__1, arg__2); }
inline bool  promoted_setUpConnections(bool  onOff, bool  doItAlways = 0) { return this->setUpConnections(onOff, doItAlways); }
static inline void promoted_startCB(void*  arg__1, SoDragger*  arg__2) { startCB(arg__1, arg__2); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline bool  py_q_setUpConnections(bool  onOff, bool  doItAlways = 0) { return SoScale2Dragger::setUpConnections(onOff, doItAlways); }
};

class PythonQtWrapper_SoScale2Dragger : public QObject
{ Q_OBJECT
public:
public slots:
SoScale2Dragger* new_SoScale2Dragger();
   void drag(SoScale2Dragger* theWrappedObject);
   void dragFinish(SoScale2Dragger* theWrappedObject);
   void dragStart(SoScale2Dragger* theWrappedObject);
   void static_SoScale2Dragger_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   void static_SoScale2Dragger_finishCB(void*  arg__1, SoDragger*  arg__2);
   SoType  static_SoScale2Dragger_getClassTypeId();
   void static_SoScale2Dragger_motionCB(void*  arg__1, SoDragger*  arg__2);
   bool  py_q_setUpConnections(SoScale2Dragger* theWrappedObject, bool  onOff, bool  doItAlways = 0){  return (((PythonQtPublicPromoter_SoScale2Dragger*)theWrappedObject)->py_q_setUpConnections(onOff, doItAlways));}
   void static_SoScale2Dragger_startCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoScale2Dragger_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
SoSFVec3f*  py_get_scaleFactor(SoScale2Dragger* theWrappedObject){ return &theWrappedObject->scaleFactor; }
};





class PythonQtShell_SoScale2UniformDragger : public SoScale2UniformDragger
{
public:
    PythonQtShell_SoScale2UniformDragger():SoScale2UniformDragger(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoScale2UniformDragger() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void createDefaultParts() override;
void doAction(SoAction*  action) override;
SoNode*  getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
SoNode*  getPart(const SbName&  partName, bool  makeIfNeeded) override;
void handleEvent(SoHandleEventAction*  ha) override;
bool  mouseButtonPressed(const SoEvent*  ev) override;
bool  mouseButtonReleased(const SoEvent*  ev) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void saveStartParameters() override;
void search(SoSearchAction*  action) override;
bool  setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsPath(const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0) override;
void setDefaultOnNonWritingFields() override;
void setName(const SbName&  name) override;
bool  setPart(const SbName&  partName, SoNode*  from) override;
bool  setPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1) override;
bool  setPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1) override;
bool  setPartAsPath(const SbName&  partName, SoPath*  surrogatePath) override;
bool  setUpConnections(bool  onOff, bool  doItAlways = 0) override;
bool  shouldGrabBasedOnSurrogate(const SoPath*  pickPath, const SoPath*  surrogatePath) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoScale2UniformDragger : public SoScale2UniformDragger
{ public:
inline void promoted_drag() { this->drag(); }
inline void promoted_dragFinish() { this->dragFinish(); }
inline void promoted_dragStart() { this->dragStart(); }
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
static inline void promoted_finishCB(void*  arg__1, SoDragger*  arg__2) { finishCB(arg__1, arg__2); }
static inline void promoted_motionCB(void*  arg__1, SoDragger*  arg__2) { motionCB(arg__1, arg__2); }
inline bool  promoted_setUpConnections(bool  onOff, bool  doItAlways = 0) { return this->setUpConnections(onOff, doItAlways); }
static inline void promoted_startCB(void*  arg__1, SoDragger*  arg__2) { startCB(arg__1, arg__2); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline bool  py_q_setUpConnections(bool  onOff, bool  doItAlways = 0) { return SoScale2UniformDragger::setUpConnections(onOff, doItAlways); }
};

class PythonQtWrapper_SoScale2UniformDragger : public QObject
{ Q_OBJECT
public:
public slots:
SoScale2UniformDragger* new_SoScale2UniformDragger();
   void drag(SoScale2UniformDragger* theWrappedObject);
   void dragFinish(SoScale2UniformDragger* theWrappedObject);
   void dragStart(SoScale2UniformDragger* theWrappedObject);
   void static_SoScale2UniformDragger_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   void static_SoScale2UniformDragger_finishCB(void*  arg__1, SoDragger*  arg__2);
   SoType  static_SoScale2UniformDragger_getClassTypeId();
   void static_SoScale2UniformDragger_motionCB(void*  arg__1, SoDragger*  arg__2);
   bool  py_q_setUpConnections(SoScale2UniformDragger* theWrappedObject, bool  onOff, bool  doItAlways = 0){  return (((PythonQtPublicPromoter_SoScale2UniformDragger*)theWrappedObject)->py_q_setUpConnections(onOff, doItAlways));}
   void static_SoScale2UniformDragger_startCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoScale2UniformDragger_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
SoSFVec3f*  py_get_scaleFactor(SoScale2UniformDragger* theWrappedObject){ return &theWrappedObject->scaleFactor; }
};





class PythonQtShell_SoScaleUniformDragger : public SoScaleUniformDragger
{
public:
    PythonQtShell_SoScaleUniformDragger():SoScaleUniformDragger(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoScaleUniformDragger() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void createDefaultParts() override;
void doAction(SoAction*  action) override;
SoNode*  getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
SoNode*  getPart(const SbName&  partName, bool  makeIfNeeded) override;
void handleEvent(SoHandleEventAction*  ha) override;
bool  mouseButtonPressed(const SoEvent*  ev) override;
bool  mouseButtonReleased(const SoEvent*  ev) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void saveStartParameters() override;
void search(SoSearchAction*  action) override;
bool  setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsPath(const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0) override;
void setDefaultOnNonWritingFields() override;
void setName(const SbName&  name) override;
bool  setPart(const SbName&  partName, SoNode*  from) override;
bool  setPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1) override;
bool  setPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1) override;
bool  setPartAsPath(const SbName&  partName, SoPath*  surrogatePath) override;
bool  setUpConnections(bool  onOff, bool  doItAlways = 0) override;
bool  shouldGrabBasedOnSurrogate(const SoPath*  pickPath, const SoPath*  surrogatePath) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoScaleUniformDragger : public SoScaleUniformDragger
{ public:
inline void promoted_drag() { this->drag(); }
inline void promoted_dragFinish() { this->dragFinish(); }
inline void promoted_dragStart() { this->dragStart(); }
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
static inline void promoted_finishCB(void*  arg__1, SoDragger*  arg__2) { finishCB(arg__1, arg__2); }
static inline void promoted_motionCB(void*  arg__1, SoDragger*  arg__2) { motionCB(arg__1, arg__2); }
inline bool  promoted_setUpConnections(bool  onOff, bool  doItAlways = 0) { return this->setUpConnections(onOff, doItAlways); }
static inline void promoted_startCB(void*  arg__1, SoDragger*  arg__2) { startCB(arg__1, arg__2); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline bool  py_q_setUpConnections(bool  onOff, bool  doItAlways = 0) { return SoScaleUniformDragger::setUpConnections(onOff, doItAlways); }
};

class PythonQtWrapper_SoScaleUniformDragger : public QObject
{ Q_OBJECT
public:
public slots:
SoScaleUniformDragger* new_SoScaleUniformDragger();
   void drag(SoScaleUniformDragger* theWrappedObject);
   void dragFinish(SoScaleUniformDragger* theWrappedObject);
   void dragStart(SoScaleUniformDragger* theWrappedObject);
   void static_SoScaleUniformDragger_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   void static_SoScaleUniformDragger_finishCB(void*  arg__1, SoDragger*  arg__2);
   SoType  static_SoScaleUniformDragger_getClassTypeId();
   void static_SoScaleUniformDragger_motionCB(void*  arg__1, SoDragger*  arg__2);
   bool  py_q_setUpConnections(SoScaleUniformDragger* theWrappedObject, bool  onOff, bool  doItAlways = 0){  return (((PythonQtPublicPromoter_SoScaleUniformDragger*)theWrappedObject)->py_q_setUpConnections(onOff, doItAlways));}
   void static_SoScaleUniformDragger_startCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoScaleUniformDragger_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
SoSFVec3f*  py_get_scaleFactor(SoScaleUniformDragger* theWrappedObject){ return &theWrappedObject->scaleFactor; }
};





class PythonQtShell_SoSpotLightDragger : public SoSpotLightDragger
{
public:
    PythonQtShell_SoSpotLightDragger():SoSpotLightDragger(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoSpotLightDragger() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void createDefaultParts() override;
void doAction(SoAction*  action) override;
SoNode*  getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
SoNode*  getPart(const SbName&  partName, bool  makeIfNeeded) override;
void handleEvent(SoHandleEventAction*  ha) override;
bool  mouseButtonPressed(const SoEvent*  ev) override;
bool  mouseButtonReleased(const SoEvent*  ev) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void saveStartParameters() override;
void search(SoSearchAction*  action) override;
bool  setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsPath(const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0) override;
void setDefaultOnNonWritingFields() override;
void setName(const SbName&  name) override;
bool  setPart(const SbName&  partName, SoNode*  from) override;
bool  setPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1) override;
bool  setPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1) override;
bool  setPartAsPath(const SbName&  partName, SoPath*  surrogatePath) override;
bool  setUpConnections(bool  onOff, bool  doItAlways = 0) override;
bool  shouldGrabBasedOnSurrogate(const SoPath*  pickPath, const SoPath*  surrogatePath) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoSpotLightDragger : public SoSpotLightDragger
{ public:
static inline void promoted_doneCB(void*  arg__1, SoDragger*  arg__2) { doneCB(arg__1, arg__2); }
inline void promoted_drag() { this->drag(); }
inline void promoted_dragFinish() { this->dragFinish(); }
inline void promoted_dragStart() { this->dragStart(); }
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
static inline void promoted_motionCB(void*  arg__1, SoDragger*  arg__2) { motionCB(arg__1, arg__2); }
inline void promoted_setBeamScaleFromAngle(float  beamAngle) { this->setBeamScaleFromAngle(beamAngle); }
inline void promoted_setDefaultOnNonWritingFields() { this->setDefaultOnNonWritingFields(); }
inline bool  promoted_setUpConnections(bool  onOff, bool  doItAlways = 0) { return this->setUpConnections(onOff, doItAlways); }
static inline void promoted_startCB(void*  arg__1, SoDragger*  arg__2) { startCB(arg__1, arg__2); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline void py_q_setDefaultOnNonWritingFields() { SoSpotLightDragger::setDefaultOnNonWritingFields(); }
inline bool  py_q_setUpConnections(bool  onOff, bool  doItAlways = 0) { return SoSpotLightDragger::setUpConnections(onOff, doItAlways); }
};

class PythonQtWrapper_SoSpotLightDragger : public QObject
{ Q_OBJECT
public:
public slots:
SoSpotLightDragger* new_SoSpotLightDragger();
   void static_SoSpotLightDragger_doneCB(void*  arg__1, SoDragger*  arg__2);
   void drag(SoSpotLightDragger* theWrappedObject);
   void dragFinish(SoSpotLightDragger* theWrappedObject);
   void dragStart(SoSpotLightDragger* theWrappedObject);
   void static_SoSpotLightDragger_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   SoType  static_SoSpotLightDragger_getClassTypeId();
   void static_SoSpotLightDragger_motionCB(void*  arg__1, SoDragger*  arg__2);
   void setBeamScaleFromAngle(SoSpotLightDragger* theWrappedObject, float  beamAngle);
   void py_q_setDefaultOnNonWritingFields(SoSpotLightDragger* theWrappedObject){  (((PythonQtPublicPromoter_SoSpotLightDragger*)theWrappedObject)->py_q_setDefaultOnNonWritingFields());}
   bool  py_q_setUpConnections(SoSpotLightDragger* theWrappedObject, bool  onOff, bool  doItAlways = 0){  return (((PythonQtPublicPromoter_SoSpotLightDragger*)theWrappedObject)->py_q_setUpConnections(onOff, doItAlways));}
   void static_SoSpotLightDragger_startCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoSpotLightDragger_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
SoSFFloat*  py_get_angle(SoSpotLightDragger* theWrappedObject){ return &theWrappedObject->angle; }
SoSFRotation*  py_get_rotation(SoSpotLightDragger* theWrappedObject){ return &theWrappedObject->rotation; }
SoSFVec3f*  py_get_translation(SoSpotLightDragger* theWrappedObject){ return &theWrappedObject->translation; }
};





class PythonQtShell_SoTabBoxDragger : public SoTabBoxDragger
{
public:
    PythonQtShell_SoTabBoxDragger():SoTabBoxDragger(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTabBoxDragger() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void createDefaultParts() override;
void doAction(SoAction*  action) override;
SoNode*  getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
SoNode*  getPart(const SbName&  partName, bool  makeIfNeeded) override;
void handleEvent(SoHandleEventAction*  ha) override;
bool  mouseButtonPressed(const SoEvent*  ev) override;
bool  mouseButtonReleased(const SoEvent*  ev) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void saveStartParameters() override;
void search(SoSearchAction*  action) override;
bool  setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsPath(const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0) override;
void setDefaultOnNonWritingFields() override;
void setName(const SbName&  name) override;
bool  setPart(const SbName&  partName, SoNode*  from) override;
bool  setPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1) override;
bool  setPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1) override;
bool  setPartAsPath(const SbName&  partName, SoPath*  surrogatePath) override;
bool  setUpConnections(bool  onOff, bool  doItAlways = 0) override;
bool  shouldGrabBasedOnSurrogate(const SoPath*  pickPath, const SoPath*  surrogatePath) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoTabBoxDragger : public SoTabBoxDragger
{ public:
static inline void promoted_adjustScaleTabSizeCB(void*  arg__1, SoDragger*  arg__2) { adjustScaleTabSizeCB(arg__1, arg__2); }
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
static inline void promoted_invalidateSurroundScaleCB(void*  arg__1, SoDragger*  arg__2) { invalidateSurroundScaleCB(arg__1, arg__2); }
inline void promoted_setDefaultOnNonWritingFields() { this->setDefaultOnNonWritingFields(); }
inline bool  promoted_setUpConnections(bool  onOff, bool  doItAlways = 0) { return this->setUpConnections(onOff, doItAlways); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline void py_q_setDefaultOnNonWritingFields() { SoTabBoxDragger::setDefaultOnNonWritingFields(); }
inline bool  py_q_setUpConnections(bool  onOff, bool  doItAlways = 0) { return SoTabBoxDragger::setUpConnections(onOff, doItAlways); }
};

class PythonQtWrapper_SoTabBoxDragger : public QObject
{ Q_OBJECT
public:
public slots:
SoTabBoxDragger* new_SoTabBoxDragger();
   void adjustScaleTabSize(SoTabBoxDragger* theWrappedObject);
   void static_SoTabBoxDragger_adjustScaleTabSizeCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoTabBoxDragger_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   SoType  static_SoTabBoxDragger_getClassTypeId();
   void static_SoTabBoxDragger_invalidateSurroundScaleCB(void*  arg__1, SoDragger*  arg__2);
   void py_q_setDefaultOnNonWritingFields(SoTabBoxDragger* theWrappedObject){  (((PythonQtPublicPromoter_SoTabBoxDragger*)theWrappedObject)->py_q_setDefaultOnNonWritingFields());}
   bool  py_q_setUpConnections(SoTabBoxDragger* theWrappedObject, bool  onOff, bool  doItAlways = 0){  return (((PythonQtPublicPromoter_SoTabBoxDragger*)theWrappedObject)->py_q_setUpConnections(onOff, doItAlways));}
   void static_SoTabBoxDragger_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
SoSFVec3f*  py_get_scaleFactor(SoTabBoxDragger* theWrappedObject){ return &theWrappedObject->scaleFactor; }
SoSFVec3f*  py_get_translation(SoTabBoxDragger* theWrappedObject){ return &theWrappedObject->translation; }
};





class PythonQtShell_SoTabPlaneDragger : public SoTabPlaneDragger
{
public:
    PythonQtShell_SoTabPlaneDragger():SoTabPlaneDragger(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTabPlaneDragger() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void createDefaultParts() override;
void doAction(SoAction*  action) override;
SoNode*  getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
SoNode*  getPart(const SbName&  partName, bool  makeIfNeeded) override;
void handleEvent(SoHandleEventAction*  ha) override;
bool  mouseButtonPressed(const SoEvent*  ev) override;
bool  mouseButtonReleased(const SoEvent*  ev) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void saveStartParameters() override;
void search(SoSearchAction*  action) override;
bool  setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsPath(const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0) override;
void setDefaultOnNonWritingFields() override;
void setName(const SbName&  name) override;
bool  setPart(const SbName&  partName, SoNode*  from) override;
bool  setPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1) override;
bool  setPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1) override;
bool  setPartAsPath(const SbName&  partName, SoPath*  surrogatePath) override;
bool  setUpConnections(bool  onOff, bool  doItAlways = 0) override;
bool  shouldGrabBasedOnSurrogate(const SoPath*  pickPath, const SoPath*  surrogatePath) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoTabPlaneDragger : public SoTabPlaneDragger
{ public:
enum State{
  INACTIVE = SoTabPlaneDragger::INACTIVE,   TRANSLATING = SoTabPlaneDragger::TRANSLATING,   EDGE_SCALING = SoTabPlaneDragger::EDGE_SCALING,   CORNER_SCALING = SoTabPlaneDragger::CORNER_SCALING,   UNIFORM_SCALING = SoTabPlaneDragger::UNIFORM_SCALING};
inline void promoted_GLRender(SoGLRenderAction*  action) { this->GLRender(action); }
inline void promoted_cornerScaleDrag() { this->cornerScaleDrag(); }
inline void promoted_cornerScaleStart() { this->cornerScaleStart(); }
inline void promoted_drag() { this->drag(); }
inline void promoted_dragFinish() { this->dragFinish(); }
inline void promoted_dragStart() { this->dragStart(); }
inline void promoted_edgeScaleDrag() { this->edgeScaleDrag(); }
inline void promoted_edgeScaleStart() { this->edgeScaleStart(); }
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
static inline void promoted_finishCB(void*  arg__1, SoDragger*  arg__2) { finishCB(arg__1, arg__2); }
inline void promoted_getXYScreenLengths(SbVec2f&  lengths, const SbMatrix&  localToScreen, const SbVec2s&  winSize) { this->getXYScreenLengths(lengths, localToScreen, winSize); }
static inline void promoted_metaKeyChangeCB(void*  arg__1, SoDragger*  arg__2) { metaKeyChangeCB(arg__1, arg__2); }
static inline void promoted_motionCB(void*  arg__1, SoDragger*  arg__2) { motionCB(arg__1, arg__2); }
inline void promoted_reallyAdjustScaleTabSize(SoGLRenderAction*  action) { this->reallyAdjustScaleTabSize(action); }
inline void promoted_scaleUniformDrag() { this->scaleUniformDrag(); }
inline void promoted_scaleUniformStart() { this->scaleUniformStart(); }
inline void promoted_setDefaultOnNonWritingFields() { this->setDefaultOnNonWritingFields(); }
inline bool  promoted_setUpConnections(bool  onOff, bool  doItAlways = 0) { return this->setUpConnections(onOff, doItAlways); }
static inline void promoted_startCB(void*  arg__1, SoDragger*  arg__2) { startCB(arg__1, arg__2); }
inline void promoted_translateDrag() { this->translateDrag(); }
inline void promoted_translateStart() { this->translateStart(); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoTabPlaneDragger::GLRender(action); }
inline void py_q_setDefaultOnNonWritingFields() { SoTabPlaneDragger::setDefaultOnNonWritingFields(); }
inline bool  py_q_setUpConnections(bool  onOff, bool  doItAlways = 0) { return SoTabPlaneDragger::setUpConnections(onOff, doItAlways); }
};

class PythonQtWrapper_SoTabPlaneDragger : public QObject
{ Q_OBJECT
public:
Q_ENUMS(State )
enum State{
  INACTIVE = PythonQtPublicPromoter_SoTabPlaneDragger::INACTIVE,   TRANSLATING = PythonQtPublicPromoter_SoTabPlaneDragger::TRANSLATING,   EDGE_SCALING = PythonQtPublicPromoter_SoTabPlaneDragger::EDGE_SCALING,   CORNER_SCALING = PythonQtPublicPromoter_SoTabPlaneDragger::CORNER_SCALING,   UNIFORM_SCALING = PythonQtPublicPromoter_SoTabPlaneDragger::UNIFORM_SCALING};
public slots:
SoTabPlaneDragger* new_SoTabPlaneDragger();
   void py_q_GLRender(SoTabPlaneDragger* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoTabPlaneDragger*)theWrappedObject)->py_q_GLRender(action));}
   void adjustScaleTabSize(SoTabPlaneDragger* theWrappedObject);
   void cornerScaleDrag(SoTabPlaneDragger* theWrappedObject);
   void cornerScaleStart(SoTabPlaneDragger* theWrappedObject);
   void drag(SoTabPlaneDragger* theWrappedObject);
   void dragFinish(SoTabPlaneDragger* theWrappedObject);
   void dragStart(SoTabPlaneDragger* theWrappedObject);
   void edgeScaleDrag(SoTabPlaneDragger* theWrappedObject);
   void edgeScaleStart(SoTabPlaneDragger* theWrappedObject);
   void static_SoTabPlaneDragger_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   void static_SoTabPlaneDragger_finishCB(void*  arg__1, SoDragger*  arg__2);
   SoType  static_SoTabPlaneDragger_getClassTypeId();
   void getXYScreenLengths(SoTabPlaneDragger* theWrappedObject, SbVec2f&  lengths, const SbMatrix&  localToScreen, const SbVec2s&  winSize);
   void static_SoTabPlaneDragger_metaKeyChangeCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoTabPlaneDragger_motionCB(void*  arg__1, SoDragger*  arg__2);
   void reallyAdjustScaleTabSize(SoTabPlaneDragger* theWrappedObject, SoGLRenderAction*  action);
   void scaleUniformDrag(SoTabPlaneDragger* theWrappedObject);
   void scaleUniformStart(SoTabPlaneDragger* theWrappedObject);
   void py_q_setDefaultOnNonWritingFields(SoTabPlaneDragger* theWrappedObject){  (((PythonQtPublicPromoter_SoTabPlaneDragger*)theWrappedObject)->py_q_setDefaultOnNonWritingFields());}
   bool  py_q_setUpConnections(SoTabPlaneDragger* theWrappedObject, bool  onOff, bool  doItAlways = 0){  return (((PythonQtPublicPromoter_SoTabPlaneDragger*)theWrappedObject)->py_q_setUpConnections(onOff, doItAlways));}
   void static_SoTabPlaneDragger_startCB(void*  arg__1, SoDragger*  arg__2);
   void translateDrag(SoTabPlaneDragger* theWrappedObject);
   void translateStart(SoTabPlaneDragger* theWrappedObject);
   void static_SoTabPlaneDragger_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
SoSFVec3f*  py_get_scaleFactor(SoTabPlaneDragger* theWrappedObject){ return &theWrappedObject->scaleFactor; }
SoSFVec3f*  py_get_translation(SoTabPlaneDragger* theWrappedObject){ return &theWrappedObject->translation; }
};





class PythonQtShell_SoTrackballDragger : public SoTrackballDragger
{
public:
    PythonQtShell_SoTrackballDragger():SoTrackballDragger(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTrackballDragger() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void createDefaultParts() override;
void doAction(SoAction*  action) override;
SoNode*  getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
SoNode*  getPart(const SbName&  partName, bool  makeIfNeeded) override;
void getSphereDeltaRotation(SbRotation&  deltaRot, SbVec3f&  newHitPt, SbVec3f  prevHitPt, SbMatrix  workingSpace) override;
void getStripeDeltaRotation(SbRotation&  deltaRot, SbVec3f&  newHitPt, SbVec3f  prevHitPt, SbMatrix  workingSpace) override;
void handleEvent(SoHandleEventAction*  ha) override;
void initDragState() override;
SbProjector*  initSphereProjector(SbVec3f  center, float  radius, SbVec3f  startWorkSpaceHitPt, SbMatrix  workingSpace) override;
SbProjector*  initStripeProjector(SbLine  axis, float  radius, SbVec3f  startWorkSpaceHitPt, SbMatrix  workingSpace) override;
bool  mouseButtonPressed(const SoEvent*  ev) override;
bool  mouseButtonReleased(const SoEvent*  ev) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void saveStartParameters() override;
void search(SoSearchAction*  action) override;
void setAllPartsActive(bool  onOrOff) override;
bool  setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsPath(const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0) override;
void setDefaultOnNonWritingFields() override;
void setName(const SbName&  name) override;
bool  setPart(const SbName&  partName, SoNode*  from) override;
bool  setPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1) override;
bool  setPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1) override;
bool  setPartAsPath(const SbName&  partName, SoPath*  surrogatePath) override;
bool  setUpConnections(bool  onOff, bool  doItAlways = 0) override;
bool  shouldGrabBasedOnSurrogate(const SoPath*  pickPath, const SoPath*  surrogatePath) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoTrackballDragger : public SoTrackballDragger
{ public:
enum State{
  INACTIVE = SoTrackballDragger::INACTIVE,   FREE_ROTATE = SoTrackballDragger::FREE_ROTATE,   X_ROTATE = SoTrackballDragger::X_ROTATE,   Y_ROTATE = SoTrackballDragger::Y_ROTATE,   Z_ROTATE = SoTrackballDragger::Z_ROTATE,   SCALE = SoTrackballDragger::SCALE,   USER_AXIS_ADJUST = SoTrackballDragger::USER_AXIS_ADJUST,   USER_AXIS_ROTATE = SoTrackballDragger::USER_AXIS_ROTATE,   SPINNING = SoTrackballDragger::SPINNING};
inline void promoted_drag() { this->drag(); }
inline void promoted_dragFinish() { this->dragFinish(); }
inline void promoted_dragStart() { this->dragStart(); }
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
static inline void promoted_finishCB(void*  arg__1, SoDragger*  arg__2) { finishCB(arg__1, arg__2); }
inline void promoted_getSphereDeltaRotation(SbRotation&  deltaRot, SbVec3f&  newHitPt, SbVec3f  prevHitPt, SbMatrix  workingSpace) { this->getSphereDeltaRotation(deltaRot, newHitPt, prevHitPt, workingSpace); }
inline void promoted_getStripeDeltaRotation(SbRotation&  deltaRot, SbVec3f&  newHitPt, SbVec3f  prevHitPt, SbMatrix  workingSpace) { this->getStripeDeltaRotation(deltaRot, newHitPt, prevHitPt, workingSpace); }
inline void promoted_initDragState() { this->initDragState(); }
inline SbProjector*  promoted_initSphereProjector(SbVec3f  center, float  radius, SbVec3f  startWorkSpaceHitPt, SbMatrix  workingSpace) { return this->initSphereProjector(center, radius, startWorkSpaceHitPt, workingSpace); }
inline SbProjector*  promoted_initStripeProjector(SbLine  axis, float  radius, SbVec3f  startWorkSpaceHitPt, SbMatrix  workingSpace) { return this->initStripeProjector(axis, radius, startWorkSpaceHitPt, workingSpace); }
static inline void promoted_metaKeyChangeCB(void*  arg__1, SoDragger*  arg__2) { metaKeyChangeCB(arg__1, arg__2); }
static inline void promoted_motionCB(void*  arg__1, SoDragger*  arg__2) { motionCB(arg__1, arg__2); }
inline void promoted_setAllPartsActive(bool  onOrOff) { this->setAllPartsActive(onOrOff); }
inline void promoted_setDefaultOnNonWritingFields() { this->setDefaultOnNonWritingFields(); }
inline bool  promoted_setUpConnections(bool  onOff, bool  doItAlways = 0) { return this->setUpConnections(onOff, doItAlways); }
static inline void promoted_startCB(void*  arg__1, SoDragger*  arg__2) { startCB(arg__1, arg__2); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline void py_q_getSphereDeltaRotation(SbRotation&  deltaRot, SbVec3f&  newHitPt, SbVec3f  prevHitPt, SbMatrix  workingSpace) { SoTrackballDragger::getSphereDeltaRotation(deltaRot, newHitPt, prevHitPt, workingSpace); }
inline void py_q_getStripeDeltaRotation(SbRotation&  deltaRot, SbVec3f&  newHitPt, SbVec3f  prevHitPt, SbMatrix  workingSpace) { SoTrackballDragger::getStripeDeltaRotation(deltaRot, newHitPt, prevHitPt, workingSpace); }
inline void py_q_initDragState() { SoTrackballDragger::initDragState(); }
inline SbProjector*  py_q_initSphereProjector(SbVec3f  center, float  radius, SbVec3f  startWorkSpaceHitPt, SbMatrix  workingSpace) { return SoTrackballDragger::initSphereProjector(center, radius, startWorkSpaceHitPt, workingSpace); }
inline SbProjector*  py_q_initStripeProjector(SbLine  axis, float  radius, SbVec3f  startWorkSpaceHitPt, SbMatrix  workingSpace) { return SoTrackballDragger::initStripeProjector(axis, radius, startWorkSpaceHitPt, workingSpace); }
inline void py_q_setAllPartsActive(bool  onOrOff) { SoTrackballDragger::setAllPartsActive(onOrOff); }
inline void py_q_setDefaultOnNonWritingFields() { SoTrackballDragger::setDefaultOnNonWritingFields(); }
inline bool  py_q_setUpConnections(bool  onOff, bool  doItAlways = 0) { return SoTrackballDragger::setUpConnections(onOff, doItAlways); }
};

class PythonQtWrapper_SoTrackballDragger : public QObject
{ Q_OBJECT
public:
Q_ENUMS(State )
enum State{
  INACTIVE = PythonQtPublicPromoter_SoTrackballDragger::INACTIVE,   FREE_ROTATE = PythonQtPublicPromoter_SoTrackballDragger::FREE_ROTATE,   X_ROTATE = PythonQtPublicPromoter_SoTrackballDragger::X_ROTATE,   Y_ROTATE = PythonQtPublicPromoter_SoTrackballDragger::Y_ROTATE,   Z_ROTATE = PythonQtPublicPromoter_SoTrackballDragger::Z_ROTATE,   SCALE = PythonQtPublicPromoter_SoTrackballDragger::SCALE,   USER_AXIS_ADJUST = PythonQtPublicPromoter_SoTrackballDragger::USER_AXIS_ADJUST,   USER_AXIS_ROTATE = PythonQtPublicPromoter_SoTrackballDragger::USER_AXIS_ROTATE,   SPINNING = PythonQtPublicPromoter_SoTrackballDragger::SPINNING};
public slots:
SoTrackballDragger* new_SoTrackballDragger();
   void drag(SoTrackballDragger* theWrappedObject);
   void dragFinish(SoTrackballDragger* theWrappedObject);
   void dragStart(SoTrackballDragger* theWrappedObject);
   void static_SoTrackballDragger_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   void static_SoTrackballDragger_finishCB(void*  arg__1, SoDragger*  arg__2);
   SoType  static_SoTrackballDragger_getClassTypeId();
   void getSphereDeltaRotation(SoTrackballDragger* theWrappedObject, SbRotation&  deltaRot, SbVec3f&  newHitPt, SbVec3f  prevHitPt, SbMatrix  workingSpace);
   void py_q_getSphereDeltaRotation(SoTrackballDragger* theWrappedObject, SbRotation&  deltaRot, SbVec3f&  newHitPt, SbVec3f  prevHitPt, SbMatrix  workingSpace){  (((PythonQtPublicPromoter_SoTrackballDragger*)theWrappedObject)->py_q_getSphereDeltaRotation(deltaRot, newHitPt, prevHitPt, workingSpace));}
   void getStripeDeltaRotation(SoTrackballDragger* theWrappedObject, SbRotation&  deltaRot, SbVec3f&  newHitPt, SbVec3f  prevHitPt, SbMatrix  workingSpace);
   void py_q_getStripeDeltaRotation(SoTrackballDragger* theWrappedObject, SbRotation&  deltaRot, SbVec3f&  newHitPt, SbVec3f  prevHitPt, SbMatrix  workingSpace){  (((PythonQtPublicPromoter_SoTrackballDragger*)theWrappedObject)->py_q_getStripeDeltaRotation(deltaRot, newHitPt, prevHitPt, workingSpace));}
   void initDragState(SoTrackballDragger* theWrappedObject);
   void py_q_initDragState(SoTrackballDragger* theWrappedObject){  (((PythonQtPublicPromoter_SoTrackballDragger*)theWrappedObject)->py_q_initDragState());}
   SbProjector*  initSphereProjector(SoTrackballDragger* theWrappedObject, SbVec3f  center, float  radius, SbVec3f  startWorkSpaceHitPt, SbMatrix  workingSpace);
   SbProjector*  py_q_initSphereProjector(SoTrackballDragger* theWrappedObject, SbVec3f  center, float  radius, SbVec3f  startWorkSpaceHitPt, SbMatrix  workingSpace){  return (((PythonQtPublicPromoter_SoTrackballDragger*)theWrappedObject)->py_q_initSphereProjector(center, radius, startWorkSpaceHitPt, workingSpace));}
   SbProjector*  initStripeProjector(SoTrackballDragger* theWrappedObject, SbLine  axis, float  radius, SbVec3f  startWorkSpaceHitPt, SbMatrix  workingSpace);
   SbProjector*  py_q_initStripeProjector(SoTrackballDragger* theWrappedObject, SbLine  axis, float  radius, SbVec3f  startWorkSpaceHitPt, SbMatrix  workingSpace){  return (((PythonQtPublicPromoter_SoTrackballDragger*)theWrappedObject)->py_q_initStripeProjector(axis, radius, startWorkSpaceHitPt, workingSpace));}
   bool  isAnimationEnabled(SoTrackballDragger* theWrappedObject);
   void static_SoTrackballDragger_metaKeyChangeCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoTrackballDragger_motionCB(void*  arg__1, SoDragger*  arg__2);
   void setAllPartsActive(SoTrackballDragger* theWrappedObject, bool  onOrOff);
   void py_q_setAllPartsActive(SoTrackballDragger* theWrappedObject, bool  onOrOff){  (((PythonQtPublicPromoter_SoTrackballDragger*)theWrappedObject)->py_q_setAllPartsActive(onOrOff));}
   void setAnimationEnabled(SoTrackballDragger* theWrappedObject, bool  newVal);
   void py_q_setDefaultOnNonWritingFields(SoTrackballDragger* theWrappedObject){  (((PythonQtPublicPromoter_SoTrackballDragger*)theWrappedObject)->py_q_setDefaultOnNonWritingFields());}
   bool  py_q_setUpConnections(SoTrackballDragger* theWrappedObject, bool  onOff, bool  doItAlways = 0){  return (((PythonQtPublicPromoter_SoTrackballDragger*)theWrappedObject)->py_q_setUpConnections(onOff, doItAlways));}
   void static_SoTrackballDragger_startCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoTrackballDragger_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
SoSFRotation*  py_get_rotation(SoTrackballDragger* theWrappedObject){ return &theWrappedObject->rotation; }
SoSFVec3f*  py_get_scaleFactor(SoTrackballDragger* theWrappedObject){ return &theWrappedObject->scaleFactor; }
};





class PythonQtShell_SoTransformBoxDragger : public SoTransformBoxDragger
{
public:
    PythonQtShell_SoTransformBoxDragger():SoTransformBoxDragger(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTransformBoxDragger() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void createDefaultParts() override;
void doAction(SoAction*  action) override;
SoNode*  getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
SoNode*  getPart(const SbName&  partName, bool  makeIfNeeded) override;
void handleEvent(SoHandleEventAction*  ha) override;
bool  mouseButtonPressed(const SoEvent*  ev) override;
bool  mouseButtonReleased(const SoEvent*  ev) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void saveStartParameters() override;
void search(SoSearchAction*  action) override;
bool  setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsPath(const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0) override;
void setDefaultOnNonWritingFields() override;
void setName(const SbName&  name) override;
bool  setPart(const SbName&  partName, SoNode*  from) override;
bool  setPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1) override;
bool  setPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1) override;
bool  setPartAsPath(const SbName&  partName, SoPath*  surrogatePath) override;
bool  setUpConnections(bool  onOff, bool  doItAlways = 0) override;
bool  shouldGrabBasedOnSurrogate(const SoPath*  pickPath, const SoPath*  surrogatePath) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoTransformBoxDragger : public SoTransformBoxDragger
{ public:
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
static inline void promoted_invalidateSurroundScaleCB(void*  arg__1, SoDragger*  arg__2) { invalidateSurroundScaleCB(arg__1, arg__2); }
inline void promoted_setDefaultOnNonWritingFields() { this->setDefaultOnNonWritingFields(); }
inline bool  promoted_setUpConnections(bool  onOff, bool  doItAlways = 0) { return this->setUpConnections(onOff, doItAlways); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline void py_q_setDefaultOnNonWritingFields() { SoTransformBoxDragger::setDefaultOnNonWritingFields(); }
inline bool  py_q_setUpConnections(bool  onOff, bool  doItAlways = 0) { return SoTransformBoxDragger::setUpConnections(onOff, doItAlways); }
};

class PythonQtWrapper_SoTransformBoxDragger : public QObject
{ Q_OBJECT
public:
public slots:
SoTransformBoxDragger* new_SoTransformBoxDragger();
   void static_SoTransformBoxDragger_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   SoType  static_SoTransformBoxDragger_getClassTypeId();
   void static_SoTransformBoxDragger_invalidateSurroundScaleCB(void*  arg__1, SoDragger*  arg__2);
   void py_q_setDefaultOnNonWritingFields(SoTransformBoxDragger* theWrappedObject){  (((PythonQtPublicPromoter_SoTransformBoxDragger*)theWrappedObject)->py_q_setDefaultOnNonWritingFields());}
   bool  py_q_setUpConnections(SoTransformBoxDragger* theWrappedObject, bool  onOff, bool  doItAlways = 0){  return (((PythonQtPublicPromoter_SoTransformBoxDragger*)theWrappedObject)->py_q_setUpConnections(onOff, doItAlways));}
   void static_SoTransformBoxDragger_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
SoSFRotation*  py_get_rotation(SoTransformBoxDragger* theWrappedObject){ return &theWrappedObject->rotation; }
SoSFVec3f*  py_get_scaleFactor(SoTransformBoxDragger* theWrappedObject){ return &theWrappedObject->scaleFactor; }
SoSFVec3f*  py_get_translation(SoTransformBoxDragger* theWrappedObject){ return &theWrappedObject->translation; }
};





class PythonQtShell_SoTransformerDragger : public SoTransformerDragger
{
public:
    PythonQtShell_SoTransformerDragger():SoTransformerDragger(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTransformerDragger() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void createDefaultParts() override;
void doAction(SoAction*  action) override;
SoNode*  getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
SoNode*  getPart(const SbName&  partName, bool  makeIfNeeded) override;
void handleEvent(SoHandleEventAction*  ha) override;
bool  mouseButtonPressed(const SoEvent*  ev) override;
bool  mouseButtonReleased(const SoEvent*  ev) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void saveStartParameters() override;
void search(SoSearchAction*  action) override;
bool  setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsPath(const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0) override;
void setDefaultOnNonWritingFields() override;
void setName(const SbName&  name) override;
bool  setPart(const SbName&  partName, SoNode*  from) override;
bool  setPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1) override;
bool  setPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1) override;
bool  setPartAsPath(const SbName&  partName, SoPath*  surrogatePath) override;
bool  setUpConnections(bool  onOff, bool  doItAlways = 0) override;
bool  shouldGrabBasedOnSurrogate(const SoPath*  pickPath, const SoPath*  surrogatePath) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoTransformerDragger : public SoTransformerDragger
{ public:
inline void promoted_drag() { this->drag(); }
inline void promoted_dragFinish() { this->dragFinish(); }
inline void promoted_dragStart() { this->dragStart(); }
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
static inline void promoted_finishCB(void*  arg__1, SoDragger*  arg__2) { finishCB(arg__1, arg__2); }
inline int  promoted_getMouseGestureDirection(bool  xAllowed, bool  yAllowed, bool  zAllowed) { return this->getMouseGestureDirection(xAllowed, yAllowed, zAllowed); }
inline void promoted_setAllPartSwitches(int  scaleAssemblyWhich, int  rotateAssemblyWhich, int  translateAssemblyWhich) { this->setAllPartSwitches(scaleAssemblyWhich, rotateAssemblyWhich, translateAssemblyWhich); }
inline void promoted_setDefaultOnNonWritingFields() { this->setDefaultOnNonWritingFields(); }
inline bool  promoted_setUpConnections(bool  onOff, bool  doItAlways = 0) { return this->setUpConnections(onOff, doItAlways); }
static inline void promoted_startCB(void*  arg__1, SoDragger*  arg__2) { startCB(arg__1, arg__2); }
inline void promoted_updateAntiSquishList() { this->updateAntiSquishList(); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline void py_q_setDefaultOnNonWritingFields() { SoTransformerDragger::setDefaultOnNonWritingFields(); }
inline bool  py_q_setUpConnections(bool  onOff, bool  doItAlways = 0) { return SoTransformerDragger::setUpConnections(onOff, doItAlways); }
};

class PythonQtWrapper_SoTransformerDragger : public QObject
{ Q_OBJECT
public:
Q_ENUMS(State )
enum State{
  INACTIVE = SoTransformerDragger::INACTIVE,   RIT_X_ROTATE = SoTransformerDragger::RIT_X_ROTATE,   TOP_Y_ROTATE = SoTransformerDragger::TOP_Y_ROTATE,   FNT_Z_ROTATE = SoTransformerDragger::FNT_Z_ROTATE,   LFT_X_ROTATE = SoTransformerDragger::LFT_X_ROTATE,   BOT_Y_ROTATE = SoTransformerDragger::BOT_Y_ROTATE,   BAK_Z_ROTATE = SoTransformerDragger::BAK_Z_ROTATE,   PX_PY_PZ_3D_SCALE = SoTransformerDragger::PX_PY_PZ_3D_SCALE,   PX_PY_NZ_3D_SCALE = SoTransformerDragger::PX_PY_NZ_3D_SCALE,   PX_NY_PZ_3D_SCALE = SoTransformerDragger::PX_NY_PZ_3D_SCALE,   PX_NY_NZ_3D_SCALE = SoTransformerDragger::PX_NY_NZ_3D_SCALE,   NX_PY_PZ_3D_SCALE = SoTransformerDragger::NX_PY_PZ_3D_SCALE,   NX_PY_NZ_3D_SCALE = SoTransformerDragger::NX_PY_NZ_3D_SCALE,   NX_NY_PZ_3D_SCALE = SoTransformerDragger::NX_NY_PZ_3D_SCALE,   NX_NY_NZ_3D_SCALE = SoTransformerDragger::NX_NY_NZ_3D_SCALE,   RIT_TRANSLATE = SoTransformerDragger::RIT_TRANSLATE,   TOP_TRANSLATE = SoTransformerDragger::TOP_TRANSLATE,   FNT_TRANSLATE = SoTransformerDragger::FNT_TRANSLATE,   LFT_TRANSLATE = SoTransformerDragger::LFT_TRANSLATE,   BOT_TRANSLATE = SoTransformerDragger::BOT_TRANSLATE,   BAK_TRANSLATE = SoTransformerDragger::BAK_TRANSLATE};
public slots:
SoTransformerDragger* new_SoTransformerDragger();
   void drag(SoTransformerDragger* theWrappedObject);
   void dragFinish(SoTransformerDragger* theWrappedObject);
   void dragStart(SoTransformerDragger* theWrappedObject);
   void static_SoTransformerDragger_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   void static_SoTransformerDragger_finishCB(void*  arg__1, SoDragger*  arg__2);
   SbVec3f  getBoxDirInWorldSpace(SoTransformerDragger* theWrappedObject, const SbVec3f&  dirOnUnitBox);
   SbVec3f  getBoxPointInWorldSpace(SoTransformerDragger* theWrappedObject, const SbVec3f&  pointOnUnitBox);
   SoType  static_SoTransformerDragger_getClassTypeId();
   int  static_SoTransformerDragger_getColinearThreshold();
   SoTransformerDragger::State  getCurrentState(SoTransformerDragger* theWrappedObject);
   SbVec3f  getInteractiveCenterInBoxSpace(SoTransformerDragger* theWrappedObject);
   int  getMouseGestureDirection(SoTransformerDragger* theWrappedObject, bool  xAllowed, bool  yAllowed, bool  zAllowed);
   SbVec3f  getWorldPointInBoxSpace(SoTransformerDragger* theWrappedObject, const SbVec3f&  pointInWorldSpace);
   SbVec2f  getWorldPointInPixelSpace(SoTransformerDragger* theWrappedObject, const SbVec3f&  thePoint);
   bool  isLocateHighlighting(SoTransformerDragger* theWrappedObject);
   void setAllPartSwitches(SoTransformerDragger* theWrappedObject, int  scaleAssemblyWhich, int  rotateAssemblyWhich, int  translateAssemblyWhich);
   void static_SoTransformerDragger_setColinearThreshold(int  newVal);
   void py_q_setDefaultOnNonWritingFields(SoTransformerDragger* theWrappedObject){  (((PythonQtPublicPromoter_SoTransformerDragger*)theWrappedObject)->py_q_setDefaultOnNonWritingFields());}
   void setLocateHighlighting(SoTransformerDragger* theWrappedObject, bool  onOff);
   bool  py_q_setUpConnections(SoTransformerDragger* theWrappedObject, bool  onOff, bool  doItAlways = 0){  return (((PythonQtPublicPromoter_SoTransformerDragger*)theWrappedObject)->py_q_setUpConnections(onOff, doItAlways));}
   void static_SoTransformerDragger_startCB(void*  arg__1, SoDragger*  arg__2);
   void unsquishKnobs(SoTransformerDragger* theWrappedObject);
   void updateAntiSquishList(SoTransformerDragger* theWrappedObject);
   void static_SoTransformerDragger_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
SoSFFloat*  py_get_minDiscRotDot(SoTransformerDragger* theWrappedObject){ return &theWrappedObject->minDiscRotDot; }
SoSFRotation*  py_get_rotation(SoTransformerDragger* theWrappedObject){ return &theWrappedObject->rotation; }
SoSFVec3f*  py_get_scaleFactor(SoTransformerDragger* theWrappedObject){ return &theWrappedObject->scaleFactor; }
SoSFVec3f*  py_get_translation(SoTransformerDragger* theWrappedObject){ return &theWrappedObject->translation; }
};





class PythonQtShell_SoTranslate1Dragger : public SoTranslate1Dragger
{
public:
    PythonQtShell_SoTranslate1Dragger():SoTranslate1Dragger(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTranslate1Dragger() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void createDefaultParts() override;
void doAction(SoAction*  action) override;
SoNode*  getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
SoNode*  getPart(const SbName&  partName, bool  makeIfNeeded) override;
void handleEvent(SoHandleEventAction*  ha) override;
bool  mouseButtonPressed(const SoEvent*  ev) override;
bool  mouseButtonReleased(const SoEvent*  ev) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void saveStartParameters() override;
void search(SoSearchAction*  action) override;
bool  setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsPath(const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0) override;
void setDefaultOnNonWritingFields() override;
void setName(const SbName&  name) override;
bool  setPart(const SbName&  partName, SoNode*  from) override;
bool  setPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1) override;
bool  setPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1) override;
bool  setPartAsPath(const SbName&  partName, SoPath*  surrogatePath) override;
bool  setUpConnections(bool  onOff, bool  doItAlways = 0) override;
bool  shouldGrabBasedOnSurrogate(const SoPath*  pickPath, const SoPath*  surrogatePath) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoTranslate1Dragger : public SoTranslate1Dragger
{ public:
inline void promoted_drag() { this->drag(); }
inline void promoted_dragFinish() { this->dragFinish(); }
inline void promoted_dragStart() { this->dragStart(); }
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
static inline void promoted_finishCB(void*  arg__1, SoDragger*  arg__2) { finishCB(arg__1, arg__2); }
static inline void promoted_motionCB(void*  arg__1, SoDragger*  arg__2) { motionCB(arg__1, arg__2); }
inline bool  promoted_setUpConnections(bool  onOff, bool  doItAlways = 0) { return this->setUpConnections(onOff, doItAlways); }
static inline void promoted_startCB(void*  arg__1, SoDragger*  arg__2) { startCB(arg__1, arg__2); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline bool  py_q_setUpConnections(bool  onOff, bool  doItAlways = 0) { return SoTranslate1Dragger::setUpConnections(onOff, doItAlways); }
};

class PythonQtWrapper_SoTranslate1Dragger : public QObject
{ Q_OBJECT
public:
public slots:
SoTranslate1Dragger* new_SoTranslate1Dragger();
   void drag(SoTranslate1Dragger* theWrappedObject);
   void dragFinish(SoTranslate1Dragger* theWrappedObject);
   void dragStart(SoTranslate1Dragger* theWrappedObject);
   void static_SoTranslate1Dragger_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   void static_SoTranslate1Dragger_finishCB(void*  arg__1, SoDragger*  arg__2);
   SoType  static_SoTranslate1Dragger_getClassTypeId();
   void static_SoTranslate1Dragger_motionCB(void*  arg__1, SoDragger*  arg__2);
   bool  py_q_setUpConnections(SoTranslate1Dragger* theWrappedObject, bool  onOff, bool  doItAlways = 0){  return (((PythonQtPublicPromoter_SoTranslate1Dragger*)theWrappedObject)->py_q_setUpConnections(onOff, doItAlways));}
   void static_SoTranslate1Dragger_startCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoTranslate1Dragger_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
SoSFVec3f*  py_get_translation(SoTranslate1Dragger* theWrappedObject){ return &theWrappedObject->translation; }
};





class PythonQtShell_SoTranslate2Dragger : public SoTranslate2Dragger
{
public:
    PythonQtShell_SoTranslate2Dragger():SoTranslate2Dragger(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTranslate2Dragger() override;

void GLRender(SoGLRenderAction*  action) override;
void GLRenderBelowPath(SoGLRenderAction*  action) override;
void GLRenderInPath(SoGLRenderAction*  action) override;
void GLRenderOffPath(SoGLRenderAction*  action) override;
bool  affectsState() const override;
void callback(SoCallbackAction*  action) override;
void createDefaultParts() override;
void doAction(SoAction*  action) override;
SoNode*  getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) override;
void getBoundingBox(SoGetBoundingBoxAction*  action) override;
SoField*  getField(const SbName&  fieldName) const override;
void getMatrix(SoGetMatrixAction*  action) override;
SbName  getName() const override;
SoNode*  getPart(const SbName&  partName, bool  makeIfNeeded) override;
void handleEvent(SoHandleEventAction*  ha) override;
void initPlaneProjector() override;
bool  mouseButtonPressed(const SoEvent*  ev) override;
bool  mouseButtonReleased(const SoEvent*  ev) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void saveStartParameters() override;
void search(SoSearchAction*  action) override;
bool  setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1) override;
bool  setAnyPartAsPath(const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0) override;
void setDefaultOnNonWritingFields() override;
void setName(const SbName&  name) override;
bool  setPart(const SbName&  partName, SoNode*  from) override;
bool  setPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1) override;
bool  setPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1) override;
bool  setPartAsPath(const SbName&  partName, SoPath*  surrogatePath) override;
bool  setUpConnections(bool  onOff, bool  doItAlways = 0) override;
bool  shouldGrabBasedOnSurrogate(const SoPath*  pickPath, const SoPath*  surrogatePath) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoTranslate2Dragger : public SoTranslate2Dragger
{ public:
inline void promoted_drag() { this->drag(); }
inline void promoted_dragFinish() { this->dragFinish(); }
inline void promoted_dragStart() { this->dragStart(); }
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
static inline void promoted_finishCB(void*  arg__1, SoDragger*  arg__2) { finishCB(arg__1, arg__2); }
inline void promoted_initPlaneProjector() { this->initPlaneProjector(); }
static inline void promoted_metaKeyChangeCB(void*  arg__1, SoDragger*  arg__2) { metaKeyChangeCB(arg__1, arg__2); }
static inline void promoted_motionCB(void*  arg__1, SoDragger*  arg__2) { motionCB(arg__1, arg__2); }
inline bool  promoted_setUpConnections(bool  onOff, bool  doItAlways = 0) { return this->setUpConnections(onOff, doItAlways); }
static inline void promoted_startCB(void*  arg__1, SoDragger*  arg__2) { startCB(arg__1, arg__2); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline void py_q_initPlaneProjector() { SoTranslate2Dragger::initPlaneProjector(); }
inline bool  py_q_setUpConnections(bool  onOff, bool  doItAlways = 0) { return SoTranslate2Dragger::setUpConnections(onOff, doItAlways); }
};

class PythonQtWrapper_SoTranslate2Dragger : public QObject
{ Q_OBJECT
public:
public slots:
SoTranslate2Dragger* new_SoTranslate2Dragger();
   void drag(SoTranslate2Dragger* theWrappedObject);
   void dragFinish(SoTranslate2Dragger* theWrappedObject);
   void dragStart(SoTranslate2Dragger* theWrappedObject);
   void static_SoTranslate2Dragger_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   void static_SoTranslate2Dragger_finishCB(void*  arg__1, SoDragger*  arg__2);
   SoType  static_SoTranslate2Dragger_getClassTypeId();
   void initPlaneProjector(SoTranslate2Dragger* theWrappedObject);
   void py_q_initPlaneProjector(SoTranslate2Dragger* theWrappedObject){  (((PythonQtPublicPromoter_SoTranslate2Dragger*)theWrappedObject)->py_q_initPlaneProjector());}
   void static_SoTranslate2Dragger_metaKeyChangeCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoTranslate2Dragger_motionCB(void*  arg__1, SoDragger*  arg__2);
   bool  py_q_setUpConnections(SoTranslate2Dragger* theWrappedObject, bool  onOff, bool  doItAlways = 0){  return (((PythonQtPublicPromoter_SoTranslate2Dragger*)theWrappedObject)->py_q_setUpConnections(onOff, doItAlways));}
   void static_SoTranslate2Dragger_startCB(void*  arg__1, SoDragger*  arg__2);
   void static_SoTranslate2Dragger_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
SoSFVec3f*  py_get_translation(SoTranslate2Dragger* theWrappedObject){ return &theWrappedObject->translation; }
};


