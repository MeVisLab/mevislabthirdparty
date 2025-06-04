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
#include <Inventor/fields/SoField.h>
#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/fields/SoFieldData.h>
#include <Inventor/misc/SoBase.h>
#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/nodekits/SoInteractionKit.h>
#include <Inventor/nodekits/SoNodeKit.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/sensors/SoSensor.h>



class PythonQtShell_SoBaseKit : public SoBaseKit
{
public:
    PythonQtShell_SoBaseKit():SoBaseKit(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoBaseKit() override;

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
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
void search(SoSearchAction*  action) override;
bool  setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) override;
void setDefaultOnNonWritingFields() override;
void setName(const SbName&  name) override;
bool  setPart(const SbName&  partName, SoNode*  from) override;
bool  setUpConnections(bool  onOff, bool  doItAlways = 0) override;
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoBaseKit : public SoBaseKit
{ public:
inline void promoted_catalogError() { this->catalogError(); }
inline void promoted_countMyFields(SoOutput*  out) { this->countMyFields(out); }
inline void promoted_createDefaultParts() { this->createDefaultParts(); }
inline void promoted_createNodekitPartsList() { this->createNodekitPartsList(); }
inline SoNode*  promoted_getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) { return this->getAnyPart(partName, makeIfNeeded, leafCheck, publicCheck); }
inline SoGroup*  promoted_getContainerNode(const SbName&  listName, bool  makeIfNeeded = 1) { return this->getContainerNode(listName, makeIfNeeded); }
inline bool  promoted_setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) { return this->setAnyPart(partName, from, anyPart); }
inline void promoted_setDefaultOnNonWritingFields() { this->setDefaultOnNonWritingFields(); }
inline bool  promoted_setUpConnections(bool  onOff, bool  doItAlways = 0) { return this->setUpConnections(onOff, doItAlways); }
inline void py_q_GLRender(SoGLRenderAction*  action) { SoBaseKit::GLRender(action); }
inline void py_q_callback(SoCallbackAction*  action) { SoBaseKit::callback(action); }
inline void py_q_createDefaultParts() { SoBaseKit::createDefaultParts(); }
inline void py_q_doAction(SoAction*  action) { SoBaseKit::doAction(action); }
inline SoNode*  py_q_getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) { return SoBaseKit::getAnyPart(partName, makeIfNeeded, leafCheck, publicCheck); }
inline void py_q_getBoundingBox(SoGetBoundingBoxAction*  action) { SoBaseKit::getBoundingBox(action); }
inline void py_q_getMatrix(SoGetMatrixAction*  action) { SoBaseKit::getMatrix(action); }
inline SoNode*  py_q_getPart(const SbName&  partName, bool  makeIfNeeded) { return SoBaseKit::getPart(partName, makeIfNeeded); }
inline void py_q_handleEvent(SoHandleEventAction*  action) { SoBaseKit::handleEvent(action); }
inline void py_q_rayPick(SoRayPickAction*  action) { SoBaseKit::rayPick(action); }
inline void py_q_search(SoSearchAction*  action) { SoBaseKit::search(action); }
inline bool  py_q_setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) { return SoBaseKit::setAnyPart(partName, from, anyPart); }
inline void py_q_setDefaultOnNonWritingFields() { SoBaseKit::setDefaultOnNonWritingFields(); }
inline bool  py_q_setPart(const SbName&  partName, SoNode*  from) { return SoBaseKit::setPart(partName, from); }
inline bool  py_q_setUpConnections(bool  onOff, bool  doItAlways = 0) { return SoBaseKit::setUpConnections(onOff, doItAlways); }
inline void py_q_write(SoWriteAction*  action) { SoBaseKit::write(action); }
};

class PythonQtWrapper_SoBaseKit : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoBaseKit* new_SoBaseKit();
   void py_q_GLRender(SoBaseKit* theWrappedObject, SoGLRenderAction*  action){  (((PythonQtPublicPromoter_SoBaseKit*)theWrappedObject)->py_q_GLRender(action));}
   void py_q_callback(SoBaseKit* theWrappedObject, SoCallbackAction*  action){  (((PythonQtPublicPromoter_SoBaseKit*)theWrappedObject)->py_q_callback(action));}
   void catalogError(SoBaseKit* theWrappedObject);
   void countMyFields(SoBaseKit* theWrappedObject, SoOutput*  out);
   void createDefaultParts(SoBaseKit* theWrappedObject);
   void py_q_createDefaultParts(SoBaseKit* theWrappedObject){  (((PythonQtPublicPromoter_SoBaseKit*)theWrappedObject)->py_q_createDefaultParts());}
   void createNodekitPartsList(SoBaseKit* theWrappedObject);
   void py_q_doAction(SoBaseKit* theWrappedObject, SoAction*  action){  (((PythonQtPublicPromoter_SoBaseKit*)theWrappedObject)->py_q_doAction(action));}
   bool  forceChildDrivenWriteRefs(SoBaseKit* theWrappedObject, SoOutput*  out);
   SoNode*  getAnyPart(SoBaseKit* theWrappedObject, const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0);
   SoNode*  py_q_getAnyPart(SoBaseKit* theWrappedObject, const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0){  return (((PythonQtPublicPromoter_SoBaseKit*)theWrappedObject)->py_q_getAnyPart(partName, makeIfNeeded, leafCheck, publicCheck));}
   void py_q_getBoundingBox(SoBaseKit* theWrappedObject, SoGetBoundingBoxAction*  action){  (((PythonQtPublicPromoter_SoBaseKit*)theWrappedObject)->py_q_getBoundingBox(action));}
   SoType  static_SoBaseKit_getClassTypeId();
   SoGroup*  getContainerNode(SoBaseKit* theWrappedObject, const SbName&  listName, bool  makeIfNeeded = 1);
   void py_q_getMatrix(SoBaseKit* theWrappedObject, SoGetMatrixAction*  action){  (((PythonQtPublicPromoter_SoBaseKit*)theWrappedObject)->py_q_getMatrix(action));}
   SoNode*  getPart(SoBaseKit* theWrappedObject, const SbName&  partName, bool  makeIfNeeded);
   SoNode*  py_q_getPart(SoBaseKit* theWrappedObject, const SbName&  partName, bool  makeIfNeeded){  return (((PythonQtPublicPromoter_SoBaseKit*)theWrappedObject)->py_q_getPart(partName, makeIfNeeded));}
   SbString  getPartString(SoBaseKit* theWrappedObject, const SoBase*  part);
   void py_q_handleEvent(SoBaseKit* theWrappedObject, SoHandleEventAction*  action){  (((PythonQtPublicPromoter_SoBaseKit*)theWrappedObject)->py_q_handleEvent(action));}
   bool  static_SoBaseKit_isSearchingChildren();
   void printDiagram(SoBaseKit* theWrappedObject);
   void printSubDiagram(SoBaseKit* theWrappedObject, const SbName&  rootName, int  level);
   void printTable(SoBaseKit* theWrappedObject);
   void py_q_rayPick(SoBaseKit* theWrappedObject, SoRayPickAction*  action){  (((PythonQtPublicPromoter_SoBaseKit*)theWrappedObject)->py_q_rayPick(action));}
   void py_q_search(SoBaseKit* theWrappedObject, SoSearchAction*  action){  (((PythonQtPublicPromoter_SoBaseKit*)theWrappedObject)->py_q_search(action));}
   bool  set(SoBaseKit* theWrappedObject, char*  nameValuePairListString);
   bool  set(SoBaseKit* theWrappedObject, char*  partNameString, char*  parameterString);
   bool  setAnyPart(SoBaseKit* theWrappedObject, const SbName&  partName, SoNode*  from, bool  anyPart = 1);
   bool  py_q_setAnyPart(SoBaseKit* theWrappedObject, const SbName&  partName, SoNode*  from, bool  anyPart = 1){  return (((PythonQtPublicPromoter_SoBaseKit*)theWrappedObject)->py_q_setAnyPart(partName, from, anyPart));}
   void setDefaultOnNonWritingFields(SoBaseKit* theWrappedObject);
   void py_q_setDefaultOnNonWritingFields(SoBaseKit* theWrappedObject){  (((PythonQtPublicPromoter_SoBaseKit*)theWrappedObject)->py_q_setDefaultOnNonWritingFields());}
   bool  setPart(SoBaseKit* theWrappedObject, const SbName&  partName, SoNode*  from);
   bool  py_q_setPart(SoBaseKit* theWrappedObject, const SbName&  partName, SoNode*  from){  return (((PythonQtPublicPromoter_SoBaseKit*)theWrappedObject)->py_q_setPart(partName, from));}
   void static_SoBaseKit_setSearchingChildren(bool  newVal);
   bool  setUpConnections(SoBaseKit* theWrappedObject, bool  onOff, bool  doItAlways = 0);
   bool  py_q_setUpConnections(SoBaseKit* theWrappedObject, bool  onOff, bool  doItAlways = 0){  return (((PythonQtPublicPromoter_SoBaseKit*)theWrappedObject)->py_q_setUpConnections(onOff, doItAlways));}
   SoNode*  static_SoBaseKit_typeCheck(const SbName&  partName, const SoType&  partType, SoNode*  node);
   void py_q_write(SoBaseKit* theWrappedObject, SoWriteAction*  action){  (((PythonQtPublicPromoter_SoBaseKit*)theWrappedObject)->py_q_write(action));}
};





class PythonQtShell_SoInteractionKit : public SoInteractionKit
{
public:
    PythonQtShell_SoInteractionKit():SoInteractionKit(),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoInteractionKit() override;

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
void handleEvent(SoHandleEventAction*  action) override;
void pick(SoPickAction*  action) override;
void rayPick(SoRayPickAction*  action) override;
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
void startNotify() override;
void write(SoWriteAction*  action) override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoInteractionKit : public SoInteractionKit
{ public:
inline void promoted_connectSeparatorFields(SoSeparator*  dest, bool  onOff) { this->connectSeparatorFields(dest, onOff); }
static inline void promoted_fieldSensorCB(void*  arg__1, SoSensor*  arg__2) { fieldSensorCB(arg__1, arg__2); }
inline SoNode*  promoted_getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) { return this->getAnyPart(partName, makeIfNeeded, leafCheck, publicCheck); }
static inline void promoted_readDefaultParts(const char*  fileName, const char*  defaultBuffer, int  defBufSize) { readDefaultParts(fileName, defaultBuffer, defBufSize); }
inline bool  promoted_setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) { return this->setAnyPart(partName, from, anyPart); }
inline bool  promoted_setAnyPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1) { return this->setAnyPartAsDefault(partName, newNode, anyPart, onlyIfAlready); }
inline bool  promoted_setAnyPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1) { return this->setAnyPartAsDefault(partName, newNodeName, anyPart, onlyIfAlready); }
inline bool  promoted_setAnyPartAsPath(const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0) { return this->setAnyPartAsPath(partName, surrogatePath, leafCheck, publicCheck); }
inline bool  promoted_setAnySurrogatePath(const SbName&  inName, SoPath*  inPath, bool  leafCheck = 0, bool  publicCheck = 0) { return this->setAnySurrogatePath(inName, inPath, leafCheck, publicCheck); }
inline void promoted_setDefaultOnNonWritingFields() { this->setDefaultOnNonWritingFields(); }
inline bool  promoted_setUpConnections(bool  onOff, bool  doItAlways = 0) { return this->setUpConnections(onOff, doItAlways); }
inline bool  py_q_affectsState() const { return SoInteractionKit::affectsState(); }
inline SoNode*  py_q_getAnyPart(const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0) { return SoInteractionKit::getAnyPart(partName, makeIfNeeded, leafCheck, publicCheck); }
inline bool  py_q_setAnyPart(const SbName&  partName, SoNode*  from, bool  anyPart = 1) { return SoInteractionKit::setAnyPart(partName, from, anyPart); }
inline bool  py_q_setAnyPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1) { return SoInteractionKit::setAnyPartAsDefault(partName, newNode, anyPart, onlyIfAlready); }
inline bool  py_q_setAnyPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1) { return SoInteractionKit::setAnyPartAsDefault(partName, newNodeName, anyPart, onlyIfAlready); }
inline bool  py_q_setAnyPartAsPath(const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0) { return SoInteractionKit::setAnyPartAsPath(partName, surrogatePath, leafCheck, publicCheck); }
inline void py_q_setDefaultOnNonWritingFields() { SoInteractionKit::setDefaultOnNonWritingFields(); }
inline bool  py_q_setPartAsDefault(const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1) { return SoInteractionKit::setPartAsDefault(partName, newNode, onlyIfAlready); }
inline bool  py_q_setPartAsDefault(const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1) { return SoInteractionKit::setPartAsDefault(partName, newNodeName, onlyIfAlready); }
inline bool  py_q_setPartAsPath(const SbName&  partName, SoPath*  surrogatePath) { return SoInteractionKit::setPartAsPath(partName, surrogatePath); }
inline bool  py_q_setUpConnections(bool  onOff, bool  doItAlways = 0) { return SoInteractionKit::setUpConnections(onOff, doItAlways); }
};

class PythonQtWrapper_SoInteractionKit : public QObject
{ Q_OBJECT
public:
Q_ENUMS(CacheEnabled )
enum CacheEnabled{
  OFF = SoInteractionKit::OFF,   ON = SoInteractionKit::ON,   AUTO = SoInteractionKit::AUTO};
public Q_SLOTS:
SoInteractionKit* new_SoInteractionKit();
   bool  py_q_affectsState(SoInteractionKit* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoInteractionKit*)theWrappedObject)->py_q_affectsState());}
   void connectSeparatorFields(SoInteractionKit* theWrappedObject, SoSeparator*  dest, bool  onOff);
   void static_SoInteractionKit_fieldSensorCB(void*  arg__1, SoSensor*  arg__2);
   SoNode*  py_q_getAnyPart(SoInteractionKit* theWrappedObject, const SbName&  partName, bool  makeIfNeeded, bool  leafCheck = 0, bool  publicCheck = 0){  return (((PythonQtPublicPromoter_SoInteractionKit*)theWrappedObject)->py_q_getAnyPart(partName, makeIfNeeded, leafCheck, publicCheck));}
   SoType  static_SoInteractionKit_getClassTypeId();
   bool  isPathSurrogateInMySubgraph(SoInteractionKit* theWrappedObject, const SoPath*  pathToCheck);
   bool  isPathSurrogateInMySubgraph(SoInteractionKit* theWrappedObject, const SoPath*  pathToCheck, SoPath*&  pathToOwner, SbName&  surrogateNameInOwner, SoPath*&  surrogatePathInOwner, bool  fillArgs = 1);
   void static_SoInteractionKit_readDefaultParts(const char*  fileName, const char*  defaultBuffer, int  defBufSize);
   bool  py_q_setAnyPart(SoInteractionKit* theWrappedObject, const SbName&  partName, SoNode*  from, bool  anyPart = 1){  return (((PythonQtPublicPromoter_SoInteractionKit*)theWrappedObject)->py_q_setAnyPart(partName, from, anyPart));}
   bool  setAnyPartAsDefault(SoInteractionKit* theWrappedObject, const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1);
   bool  py_q_setAnyPartAsDefault(SoInteractionKit* theWrappedObject, const SbName&  partName, SoNode*  newNode, bool  anyPart = 1, bool  onlyIfAlready = 1){  return (((PythonQtPublicPromoter_SoInteractionKit*)theWrappedObject)->py_q_setAnyPartAsDefault(partName, newNode, anyPart, onlyIfAlready));}
   bool  setAnyPartAsDefault(SoInteractionKit* theWrappedObject, const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1);
   bool  py_q_setAnyPartAsDefault(SoInteractionKit* theWrappedObject, const SbName&  partName, const SbName&  newNodeName, bool  anyPart = 1, bool  onlyIfAlready = 1){  return (((PythonQtPublicPromoter_SoInteractionKit*)theWrappedObject)->py_q_setAnyPartAsDefault(partName, newNodeName, anyPart, onlyIfAlready));}
   bool  setAnyPartAsPath(SoInteractionKit* theWrappedObject, const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0);
   bool  py_q_setAnyPartAsPath(SoInteractionKit* theWrappedObject, const SbName&  partName, SoPath*  surrogatePath, bool  leafCheck = 0, bool  publicCheck = 0){  return (((PythonQtPublicPromoter_SoInteractionKit*)theWrappedObject)->py_q_setAnyPartAsPath(partName, surrogatePath, leafCheck, publicCheck));}
   bool  setAnySurrogatePath(SoInteractionKit* theWrappedObject, const SbName&  inName, SoPath*  inPath, bool  leafCheck = 0, bool  publicCheck = 0);
   void py_q_setDefaultOnNonWritingFields(SoInteractionKit* theWrappedObject){  (((PythonQtPublicPromoter_SoInteractionKit*)theWrappedObject)->py_q_setDefaultOnNonWritingFields());}
   bool  setPartAsDefault(SoInteractionKit* theWrappedObject, const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1);
   bool  py_q_setPartAsDefault(SoInteractionKit* theWrappedObject, const SbName&  partName, SoNode*  newNode, bool  onlyIfAlready = 1){  return (((PythonQtPublicPromoter_SoInteractionKit*)theWrappedObject)->py_q_setPartAsDefault(partName, newNode, onlyIfAlready));}
   bool  setPartAsDefault(SoInteractionKit* theWrappedObject, const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1);
   bool  py_q_setPartAsDefault(SoInteractionKit* theWrappedObject, const SbName&  partName, const SbName&  newNodeName, bool  onlyIfAlready = 1){  return (((PythonQtPublicPromoter_SoInteractionKit*)theWrappedObject)->py_q_setPartAsDefault(partName, newNodeName, onlyIfAlready));}
   bool  setPartAsPath(SoInteractionKit* theWrappedObject, const SbName&  partName, SoPath*  surrogatePath);
   bool  py_q_setPartAsPath(SoInteractionKit* theWrappedObject, const SbName&  partName, SoPath*  surrogatePath){  return (((PythonQtPublicPromoter_SoInteractionKit*)theWrappedObject)->py_q_setPartAsPath(partName, surrogatePath));}
   void static_SoInteractionKit_setSwitchValue(SoNode*  n, int  newVal);
   bool  py_q_setUpConnections(SoInteractionKit* theWrappedObject, bool  onOff, bool  doItAlways = 0){  return (((PythonQtPublicPromoter_SoInteractionKit*)theWrappedObject)->py_q_setUpConnections(onOff, doItAlways));}
SoSFEnum*  py_get_boundingBoxCaching(SoInteractionKit* theWrappedObject){ return &theWrappedObject->boundingBoxCaching; }
SoSFEnum*  py_get_pickCulling(SoInteractionKit* theWrappedObject){ return &theWrappedObject->pickCulling; }
SoSFEnum*  py_get_renderCaching(SoInteractionKit* theWrappedObject){ return &theWrappedObject->renderCaching; }
SoSFEnum*  py_get_renderCulling(SoInteractionKit* theWrappedObject){ return &theWrappedObject->renderCulling; }
};





class PythonQtShell_SoNodeKit : public SoNodeKit
{
public:
    PythonQtShell_SoNodeKit():SoNodeKit(),_wrapper(nullptr) {};

   ~PythonQtShell_SoNodeKit();


  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoNodeKit : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoNodeKit* new_SoNodeKit();
void delete_SoNodeKit(SoNodeKit* obj) { delete obj; }
   void static_SoNodeKit_init();
};


