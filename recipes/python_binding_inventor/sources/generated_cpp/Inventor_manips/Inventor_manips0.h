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
#include <Inventor/SoInput.h>
#include <Inventor/SoOutput.h>
#include <Inventor/SoPath.h>
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
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoField.h>
#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/manips/SoCenterballManip.h>
#include <Inventor/manips/SoDirectionalLightManip.h>
#include <Inventor/manips/SoHandleBoxManip.h>
#include <Inventor/manips/SoJackManip.h>
#include <Inventor/manips/SoSpotLightManip.h>
#include <Inventor/manips/SoTabBoxManip.h>
#include <Inventor/manips/SoTrackballManip.h>
#include <Inventor/manips/SoTransformBoxManip.h>
#include <Inventor/manips/SoTransformManip.h>
#include <Inventor/manips/SoTransformerManip.h>
#include <Inventor/misc/SoBase.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoSpotLight.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoTransformation.h>
#include <Inventor/sensors/SoSensor.h>



class PythonQtShell_SoCenterballManip : public SoCenterballManip
{
public:
    PythonQtShell_SoCenterballManip():SoCenterballManip(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoCenterballManip() override;

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
void setDragger(SoDragger*  newDragger) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoCenterballManip : public SoCenterballManip
{ public:
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
inline void promoted_setDragger(SoDragger*  newDragger) { this->setDragger(newDragger); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline void py_q_setDragger(SoDragger*  newDragger) { SoCenterballManip::setDragger(newDragger); }
};

class PythonQtWrapper_SoCenterballManip : public QObject
{ Q_OBJECT
public:
public slots:
SoCenterballManip* new_SoCenterballManip();
   void static_SoCenterballManip_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   SoType  static_SoCenterballManip_getClassTypeId();
   void py_q_setDragger(SoCenterballManip* theWrappedObject, SoDragger*  newDragger){  (((PythonQtPublicPromoter_SoCenterballManip*)theWrappedObject)->py_q_setDragger(newDragger));}
   void static_SoCenterballManip_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
};





class PythonQtShell_SoDirectionalLightManip : public SoDirectionalLightManip
{
public:
    PythonQtShell_SoDirectionalLightManip():SoDirectionalLightManip(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoDirectionalLightManip() override;

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

class PythonQtPublicPromoter_SoDirectionalLightManip : public SoDirectionalLightManip
{ public:
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
inline void promoted_setDragger(SoDragger*  newDragger) { this->setDragger(newDragger); }
static inline void promoted_transferFieldValues(const SoDirectionalLight*  from, SoDirectionalLight*  to) { transferFieldValues(from, to); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoDirectionalLightManip::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoDirectionalLightManip::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoDirectionalLightManip::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoDirectionalLightManip::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoDirectionalLightManip::getMatrix(action); }
inline void py_q_handleEvent(SoHandleEventAction*  action) { SoDirectionalLightManip::handleEvent(action); }
inline void py_q_pick(SoPickAction*  action) { SoDirectionalLightManip::pick(action); }
inline void py_q_search(SoSearchAction*  action) { SoDirectionalLightManip::search(action); }
};

class PythonQtWrapper_SoDirectionalLightManip : public QObject
{ Q_OBJECT
public:
public slots:
SoDirectionalLightManip* new_SoDirectionalLightManip();
   void py_q_GLRender(SoDirectionalLightManip* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoDirectionalLightManip*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoDirectionalLightManip* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoDirectionalLightManip*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoDirectionalLightManip* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoDirectionalLightManip*)theWrappedObject)->py_q_doAction(action));}
   void static_SoDirectionalLightManip_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   void py_q_getBoundingBox(SoDirectionalLightManip* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoDirectionalLightManip*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoDirectionalLightManip_getClassTypeId();
   SoDragger*  getDragger(SoDirectionalLightManip* theWrappedObject);
   void py_q_getMatrix(SoDirectionalLightManip* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoDirectionalLightManip*)theWrappedObject)->py_q_getMatrix(action));}
   void py_q_handleEvent(SoDirectionalLightManip* theWrappedObject, SoHandleEventAction*  action){  (((PythonQtPublicPromoter_SoDirectionalLightManip*)theWrappedObject)->py_q_handleEvent(action));}
   void py_q_pick(SoDirectionalLightManip* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoDirectionalLightManip*)theWrappedObject)->py_q_pick(action));}
   bool  replaceManip(SoDirectionalLightManip* theWrappedObject, SoPath*  p, SoDirectionalLight*  newOne) const;
   bool  replaceNode(SoDirectionalLightManip* theWrappedObject, SoPath*  p);
   void py_q_search(SoDirectionalLightManip* theWrappedObject, SoSearchAction*  action){  (((PythonQtPublicPromoter_SoDirectionalLightManip*)theWrappedObject)->py_q_search(action));}
   void setDragger(SoDirectionalLightManip* theWrappedObject, SoDragger*  newDragger);
   void static_SoDirectionalLightManip_transferFieldValues(const SoDirectionalLight*  from, SoDirectionalLight*  to);
   void static_SoDirectionalLightManip_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
};





class PythonQtShell_SoHandleBoxManip : public SoHandleBoxManip
{
public:
    PythonQtShell_SoHandleBoxManip():SoHandleBoxManip(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoHandleBoxManip() override;

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
void setDragger(SoDragger*  newDragger) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoHandleBoxManip : public QObject
{ Q_OBJECT
public:
public slots:
SoHandleBoxManip* new_SoHandleBoxManip();
   SoType  static_SoHandleBoxManip_getClassTypeId();
};





class PythonQtShell_SoJackManip : public SoJackManip
{
public:
    PythonQtShell_SoJackManip():SoJackManip(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoJackManip() override;

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
void setDragger(SoDragger*  newDragger) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoJackManip : public QObject
{ Q_OBJECT
public:
public slots:
SoJackManip* new_SoJackManip();
   SoType  static_SoJackManip_getClassTypeId();
};





class PythonQtShell_SoSpotLightManip : public SoSpotLightManip
{
public:
    PythonQtShell_SoSpotLightManip():SoSpotLightManip(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoSpotLightManip() override;

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

class PythonQtPublicPromoter_SoSpotLightManip : public SoSpotLightManip
{ public:
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
inline void promoted_setDragger(SoDragger*  newDragger) { this->setDragger(newDragger); }
static inline void promoted_transferFieldValues(const SoSpotLight*  from, SoSpotLight*  to) { transferFieldValues(from, to); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoSpotLightManip::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoSpotLightManip::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoSpotLightManip::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoSpotLightManip::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoSpotLightManip::getMatrix(action); }
inline void py_q_handleEvent(SoHandleEventAction*  action) { SoSpotLightManip::handleEvent(action); }
inline void py_q_pick(SoPickAction*  action) { SoSpotLightManip::pick(action); }
inline void py_q_search(SoSearchAction*  action) { SoSpotLightManip::search(action); }
};

class PythonQtWrapper_SoSpotLightManip : public QObject
{ Q_OBJECT
public:
public slots:
SoSpotLightManip* new_SoSpotLightManip();
   void py_q_GLRender(SoSpotLightManip* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoSpotLightManip*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoSpotLightManip* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoSpotLightManip*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoSpotLightManip* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoSpotLightManip*)theWrappedObject)->py_q_doAction(action));}
   void static_SoSpotLightManip_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   void py_q_getBoundingBox(SoSpotLightManip* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoSpotLightManip*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoSpotLightManip_getClassTypeId();
   SoDragger*  getDragger(SoSpotLightManip* theWrappedObject);
   void py_q_getMatrix(SoSpotLightManip* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoSpotLightManip*)theWrappedObject)->py_q_getMatrix(action));}
   void py_q_handleEvent(SoSpotLightManip* theWrappedObject, SoHandleEventAction*  action){  (((PythonQtPublicPromoter_SoSpotLightManip*)theWrappedObject)->py_q_handleEvent(action));}
   void py_q_pick(SoSpotLightManip* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoSpotLightManip*)theWrappedObject)->py_q_pick(action));}
   bool  replaceManip(SoSpotLightManip* theWrappedObject, SoPath*  p, SoSpotLight*  newOne) const;
   bool  replaceNode(SoSpotLightManip* theWrappedObject, SoPath*  p);
   void py_q_search(SoSpotLightManip* theWrappedObject, SoSearchAction*  action){  (((PythonQtPublicPromoter_SoSpotLightManip*)theWrappedObject)->py_q_search(action));}
   void setDragger(SoSpotLightManip* theWrappedObject, SoDragger*  newDragger);
   void static_SoSpotLightManip_transferFieldValues(const SoSpotLight*  from, SoSpotLight*  to);
   void static_SoSpotLightManip_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
};





class PythonQtShell_SoTabBoxManip : public SoTabBoxManip
{
public:
    PythonQtShell_SoTabBoxManip():SoTabBoxManip(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTabBoxManip() override;

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
void setDragger(SoDragger*  newDragger) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoTabBoxManip : public QObject
{ Q_OBJECT
public:
public slots:
SoTabBoxManip* new_SoTabBoxManip();
   SoType  static_SoTabBoxManip_getClassTypeId();
};





class PythonQtShell_SoTrackballManip : public SoTrackballManip
{
public:
    PythonQtShell_SoTrackballManip():SoTrackballManip(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTrackballManip() override;

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
void setDragger(SoDragger*  newDragger) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoTrackballManip : public QObject
{ Q_OBJECT
public:
public slots:
SoTrackballManip* new_SoTrackballManip();
   SoType  static_SoTrackballManip_getClassTypeId();
};





class PythonQtShell_SoTransformBoxManip : public SoTransformBoxManip
{
public:
    PythonQtShell_SoTransformBoxManip():SoTransformBoxManip(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTransformBoxManip() override;

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
void setDragger(SoDragger*  newDragger) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoTransformBoxManip : public QObject
{ Q_OBJECT
public:
public slots:
SoTransformBoxManip* new_SoTransformBoxManip();
   SoType  static_SoTransformBoxManip_getClassTypeId();
};





class PythonQtShell_SoTransformManip : public SoTransformManip
{
public:
    PythonQtShell_SoTransformManip():SoTransformManip(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTransformManip() override;

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
void setDragger(SoDragger*  newDragger) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoTransformManip : public SoTransformManip
{ public:
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
inline void promoted_setDragger(SoDragger*  newDragger) { this->setDragger(newDragger); }
static inline void promoted_transferFieldValues(const SoTransform*  from, SoTransform*  to) { transferFieldValues(from, to); }
static inline void promoted_valueChangedCB(void*  arg__1, SoDragger*  arg__2) { valueChangedCB(arg__1, arg__2); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoTransformManip::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoTransformManip::callback(action); }
inline void py_q_doAction(SoAction*  action) { SoTransformManip::doAction(action); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoTransformManip::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoTransformManip::getMatrix(action); }
inline void py_q_handleEvent(SoHandleEventAction*  action) { SoTransformManip::handleEvent(action); }
inline void py_q_pick(SoPickAction*  action) { SoTransformManip::pick(action); }
inline void py_q_search(SoSearchAction*  action) { SoTransformManip::search(action); }
inline void py_q_setDragger(SoDragger*  newDragger) { SoTransformManip::setDragger(newDragger); }
};

class PythonQtWrapper_SoTransformManip : public QObject
{ Q_OBJECT
public:
public slots:
SoTransformManip* new_SoTransformManip();
   void py_q_GLRender(SoTransformManip* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoTransformManip*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoTransformManip* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoTransformManip*)theWrappedObject)->py_q_callback(action));}
   void py_q_doAction(SoTransformManip* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoTransformManip*)theWrappedObject)->py_q_doAction(action));}
   void static_SoTransformManip_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   void py_q_getBoundingBox(SoTransformManip* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoTransformManip*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoTransformManip_getClassTypeId();
   SoDragger*  getDragger(SoTransformManip* theWrappedObject);
   void py_q_getMatrix(SoTransformManip* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoTransformManip*)theWrappedObject)->py_q_getMatrix(action));}
   void py_q_handleEvent(SoTransformManip* theWrappedObject, SoHandleEventAction*  action){  (((PythonQtPublicPromoter_SoTransformManip*)theWrappedObject)->py_q_handleEvent(action));}
   void py_q_pick(SoTransformManip* theWrappedObject, SoPickAction*  action){  (((PythonQtPublicPromoter_SoTransformManip*)theWrappedObject)->py_q_pick(action));}
   bool  replaceManip(SoTransformManip* theWrappedObject, SoPath*  p, SoTransform*  newOne) const;
   bool  replaceNode(SoTransformManip* theWrappedObject, SoPath*  p);
   void py_q_search(SoTransformManip* theWrappedObject, SoSearchAction*  action){  (((PythonQtPublicPromoter_SoTransformManip*)theWrappedObject)->py_q_search(action));}
   void setDragger(SoTransformManip* theWrappedObject, SoDragger*  newDragger);
   void py_q_setDragger(SoTransformManip* theWrappedObject, SoDragger*  newDragger){  (((PythonQtPublicPromoter_SoTransformManip*)theWrappedObject)->py_q_setDragger(newDragger));}
   void static_SoTransformManip_transferFieldValues(const SoTransform*  from, SoTransform*  to);
   void static_SoTransformManip_valueChangedCB(void*  arg__1, SoDragger*  arg__2);
};





class PythonQtShell_SoTransformerManip : public SoTransformerManip
{
public:
    PythonQtShell_SoTransformerManip():SoTransformerManip(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoTransformerManip() override;

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
void setDragger(SoDragger*  newDragger) override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoTransformerManip : public QObject
{ Q_OBJECT
public:
public slots:
SoTransformerManip* new_SoTransformerManip();
   SoType  static_SoTransformerManip_getClassTypeId();
   bool  isLocateHighlighting(SoTransformerManip* theWrappedObject);
   void setLocateHighlighting(SoTransformerManip* theWrappedObject, bool  onOff);
   void unsquishKnobs(SoTransformerManip* theWrappedObject);
};


