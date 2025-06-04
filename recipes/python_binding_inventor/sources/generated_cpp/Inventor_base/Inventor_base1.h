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
#include <Inventor/SbBoxd.h>
#include <Inventor/SbColor.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbLineard.h>
#include <Inventor/SbString.h>
#include <Inventor/SbTime.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SoDB.h>
#include <Inventor/SoInput.h>
#include <Inventor/SoOutput.h>
#include <Inventor/SoPath.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/SoPrimitiveVertex.h>
#include <Inventor/SoSceneManager.h>
#include <Inventor/SoType.h>
#include <Inventor/actions/SoAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/details/SoDetail.h>
#include <Inventor/elements/SoElement.h>
#include <Inventor/events/SoEvent.h>
#include <Inventor/fields/SoField.h>
#include <Inventor/misc/SoBase.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/sensors/SoSensor.h>
#include <stdexcept>



class PythonQtWrapper_SbXfBox3d : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbXfBox3d* new_SbXfBox3d();
SbXfBox3d* new_SbXfBox3d(const SbBox3d&  box);
SbXfBox3d* new_SbXfBox3d(const SbVec3d&  _min, const SbVec3d&  _max);
SbXfBox3d* new_SbXfBox3d(const SbXfBox3d& other) {
SbXfBox3d* a = new SbXfBox3d();
*((SbXfBox3d*)a) = other;
return a; }
void delete_SbXfBox3d(SbXfBox3d* obj) { delete obj; }
   void extendBy(SbXfBox3d* theWrappedObject, const SbBox3d&  bb);
   void extendBy(SbXfBox3d* theWrappedObject, const SbVec3d&  pt);
   void extendBy(SbXfBox3d* theWrappedObject, const SbXfBox3d&  bb);
   SbVec3d  getCenter(SbXfBox3d* theWrappedObject) const;
   const SbMatrixd*  getInverse(SbXfBox3d* theWrappedObject) const;
   const SbMatrixd*  getTransform(SbXfBox3d* theWrappedObject) const;
   double  getVolume(SbXfBox3d* theWrappedObject) const;
   bool  hasVolume(SbXfBox3d* theWrappedObject) const;
   bool  intersect(SbXfBox3d* theWrappedObject, const SbBox3d&  bb) const;
   bool  intersect(SbXfBox3d* theWrappedObject, const SbVec3d&  pt) const;
   bool  isEmpty(SbXfBox3d* theWrappedObject) const;
   void makeEmpty(SbXfBox3d* theWrappedObject);
   bool  __ne__(SbXfBox3d* theWrappedObject, const SbXfBox3d&  b2);
   bool  __eq__(SbXfBox3d* theWrappedObject, const SbXfBox3d&  b2);
   SbBox3d  project(SbXfBox3d* theWrappedObject) const;
   void setBounds(SbXfBox3d* theWrappedObject, const SbVec3d&  _min, const SbVec3d&  _max);
   void setBounds(SbXfBox3d* theWrappedObject, double  xmin, double  ymin, double  zmin, double  xmax, double  ymax, double  zmax);
   void setTransform(SbXfBox3d* theWrappedObject, const SbMatrixd&  m);
   void transform(SbXfBox3d* theWrappedObject, const SbMatrixd&  m);
    bool __nonzero__(SbXfBox3d* obj) { return !obj->isEmpty(); }
};





class PythonQtWrapper_SbXfBox3f : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbXfBox3f* new_SbXfBox3f();
SbXfBox3f* new_SbXfBox3f(const SbBox3f&  box);
SbXfBox3f* new_SbXfBox3f(const SbVec3f&  _min, const SbVec3f&  _max);
SbXfBox3f* new_SbXfBox3f(const SbXfBox3f& other) {
SbXfBox3f* a = new SbXfBox3f();
*((SbXfBox3f*)a) = other;
return a; }
void delete_SbXfBox3f(SbXfBox3f* obj) { delete obj; }
   void extendBy(SbXfBox3f* theWrappedObject, const SbBox3f&  bb);
   void extendBy(SbXfBox3f* theWrappedObject, const SbVec3f&  pt);
   void extendBy(SbXfBox3f* theWrappedObject, const SbXfBox3f&  bb);
   SbVec3f  getCenter(SbXfBox3f* theWrappedObject) const;
   const SbMatrix*  getInverse(SbXfBox3f* theWrappedObject) const;
   const SbMatrix*  getTransform(SbXfBox3f* theWrappedObject) const;
   float  getVolume(SbXfBox3f* theWrappedObject) const;
   bool  hasVolume(SbXfBox3f* theWrappedObject) const;
   bool  intersect(SbXfBox3f* theWrappedObject, const SbBox3f&  bb) const;
   bool  intersect(SbXfBox3f* theWrappedObject, const SbVec3f&  pt) const;
   bool  isEmpty(SbXfBox3f* theWrappedObject) const;
   void makeEmpty(SbXfBox3f* theWrappedObject);
   bool  __ne__(SbXfBox3f* theWrappedObject, const SbXfBox3f&  b2);
   bool  __eq__(SbXfBox3f* theWrappedObject, const SbXfBox3f&  b2);
   SbBox3f  project(SbXfBox3f* theWrappedObject) const;
   void setBounds(SbXfBox3f* theWrappedObject, const SbVec3f&  _min, const SbVec3f&  _max);
   void setBounds(SbXfBox3f* theWrappedObject, float  xmin, float  ymin, float  zmin, float  xmax, float  ymax, float  zmax);
   void setTransform(SbXfBox3f* theWrappedObject, const SbMatrix&  m);
   void transform(SbXfBox3f* theWrappedObject, const SbMatrix&  m);
    bool __nonzero__(SbXfBox3f* obj) { return !obj->isEmpty(); }
};





class PythonQtPublicPromoter_SoBase : public SoBase
{ public:
inline SbName  py_q_getName() const { return SoBase::getName(); }
inline void py_q_setName(const SbName&  name) { SoBase::setName(name); }
inline void py_q_startNotify() { SoBase::startNotify(); }
};

class PythonQtWrapper_SoBase : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
   SoType  static_SoBase_getClassTypeId();
   SbName  getName(SoBase* theWrappedObject) const;
   SbName  py_q_getName(SoBase* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoBase*)theWrappedObject)->py_q_getName());}
   int  getRefCount(SoBase* theWrappedObject) const;
   bool  isOfType(SoBase* theWrappedObject, SoType  type) const;
   void setName(SoBase* theWrappedObject, const SbName&  name);
   void py_q_setName(SoBase* theWrappedObject, const SbName&  name){  (((PythonQtPublicPromoter_SoBase*)theWrappedObject)->py_q_setName(name));}
   void startNotify(SoBase* theWrappedObject);
   void py_q_startNotify(SoBase* theWrappedObject){  (((PythonQtPublicPromoter_SoBase*)theWrappedObject)->py_q_startNotify());}
   void touch(SoBase* theWrappedObject);

   SoType getTypeId(SoBase* o) const { return o->getTypeId(); }

};





class PythonQtShell_SoDB : public SoDB
{
public:
    PythonQtShell_SoDB():SoDB(),_wrapper(nullptr) {};

   ~PythonQtShell_SoDB();


  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoDB : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoDB* new_SoDB();
SoDB* new_SoDB(const SoDB& other) {
PythonQtShell_SoDB* a = new PythonQtShell_SoDB();
*((SoDB*)a) = other;
return a; }
void delete_SoDB(SoDB* obj) { delete obj; }
   void static_SoDB_addConverter(SoType  fromField, SoType  toField, SoType  converterEngine);
   SoField*  static_SoDB_createGlobalField(const SbName&  name, SoType  type);
   void static_SoDB_enableRealTimeSensor(bool  enable);
   void static_SoDB_endNotify();
   SoType  static_SoDB_getConverter(SoType  fromField, SoType  toField);
   const SbTime*  static_SoDB_getDelaySensorTimeout();
   SoField*  static_SoDB_getGlobalField(const SbName&  name);
   SbString  static_SoDB_getHeaderString(int  i);
   int  static_SoDB_getNumHeaders();
   const SbTime*  static_SoDB_getRealTimeInterval();
   const char*  static_SoDB_getVersion();
   void static_SoDB_init();
   bool  static_SoDB_isInitialized();
   bool  static_SoDB_isNotifying();
   bool  static_SoDB_isValidHeader(const char*  testString);
   SoSeparator*  static_SoDB_readAll(SoInput*  in);
   void static_SoDB_renameGlobalField(const SbName&  oldName, const SbName&  newName);
   void static_SoDB_setDelaySensorTimeout(const SbTime&  t);
   void static_SoDB_setRealTimeInterval(const SbTime&  deltaT);
   void static_SoDB_startNotify();
};





class PythonQtWrapper_SoInput : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoInput* new_SoInput();
SoInput* new_SoInput(SoInput*  dictIn);
void delete_SoInput(SoInput* obj) { delete obj; }
   void static_SoInput_addDirectoryFirst(const char*  dirName);
   void static_SoInput_addDirectoryLast(const char*  dirName);
   void static_SoInput_addEnvDirectoriesFirst(const char*  envVarName);
   void static_SoInput_addEnvDirectoriesLast(const char*  envVarName);
   void addReference(SoInput* theWrappedObject, const SbName&  name, SoBase*  base, bool  addToGlobalDict = 1);
   void static_SoInput_clearDirectories();
   void closeFile(SoInput* theWrappedObject);
   bool  eof(SoInput* theWrappedObject) const;
   SoBase*  findReference(SoInput* theWrappedObject, const SbName&  name) const;
   const char*  getCurFileName(SoInput* theWrappedObject) const;
   SbString  getHeader(SoInput* theWrappedObject);
   float  getIVVersion(SoInput* theWrappedObject);
   void static_SoInput_init();
   bool  isBinary(SoInput* theWrappedObject);
   bool  isValidFile(SoInput* theWrappedObject);
   bool  openFile(SoInput* theWrappedObject, const char*  fileName, bool  okIfNotFound = 0);
   bool  pushFile(SoInput* theWrappedObject, const char*  fileName);
   void putBack(SoInput* theWrappedObject, char  c);
   void putBack(SoInput* theWrappedObject, const char*  string);
   bool  readBinaryArray(SoInput* theWrappedObject, double*  d, int  length);
   bool  readBinaryArray(SoInput* theWrappedObject, float*  f, int  length);
   bool  readBinaryArray(SoInput* theWrappedObject, int*  l, int  length);
   bool  readBinaryArray(SoInput* theWrappedObject, unsigned char*  c, int  length);
   void static_SoInput_removeDirectory(const char*  dirName);
   void removeReference(SoInput* theWrappedObject, const SbName&  name);
};





class PythonQtWrapper_SoOutput : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Annotations Stage )
enum Annotations{
  ADDRESSES = SoOutput::ADDRESSES,   REF_COUNTS = SoOutput::REF_COUNTS};
enum Stage{
  COUNT_REFS = SoOutput::COUNT_REFS,   WRITE = SoOutput::WRITE};
public Q_SLOTS:
SoOutput* new_SoOutput();
SoOutput* new_SoOutput(SoOutput*  dictOut);
void delete_SoOutput(SoOutput* obj) { delete obj; }
   void closeFile(SoOutput* theWrappedObject);
   void decrementIndent(SoOutput* theWrappedObject, int  amount = 1);
   unsigned int  getAnnotation(SoOutput* theWrappedObject);
   SbString  static_SoOutput_getDefaultASCIIHeader();
   SbString  static_SoOutput_getDefaultBinaryHeader();
   SoOutput::Stage  getStage(SoOutput* theWrappedObject) const;
   void incrementIndent(SoOutput* theWrappedObject, int  amount = 1);
   void indent(SoOutput* theWrappedObject);
   bool  isBinary(SoOutput* theWrappedObject) const;
   bool  isCompact(SoOutput* theWrappedObject) const;
   bool  openFile(SoOutput* theWrappedObject, const char*  fileName);
   void reset(SoOutput* theWrappedObject);
   void resetBuffer(SoOutput* theWrappedObject);
   void resetHeaderString(SoOutput* theWrappedObject);
   void setAnnotation(SoOutput* theWrappedObject, unsigned int  bits);
   void setBinary(SoOutput* theWrappedObject, bool  flag);
   void setCompact(SoOutput* theWrappedObject, bool  flag);
   void setFloatPrecision(SoOutput* theWrappedObject, int  precision);
   void setHeaderString(SoOutput* theWrappedObject, const SbString&  str);
   void setStage(SoOutput* theWrappedObject, SoOutput::Stage  stage);
   void write(SoOutput* theWrappedObject, char  c);
   void write(SoOutput* theWrappedObject, const SbName&  n);
   void write(SoOutput* theWrappedObject, const SbString&  s);
   void write(SoOutput* theWrappedObject, const char*  s);
   void write(SoOutput* theWrappedObject, double  d);
   void write(SoOutput* theWrappedObject, float  f);
   void write(SoOutput* theWrappedObject, int  i);
   void write(SoOutput* theWrappedObject, short  s);
   void write(SoOutput* theWrappedObject, unsigned int  i);
   void write(SoOutput* theWrappedObject, unsigned short  s);
   void writeBinaryArray(SoOutput* theWrappedObject, double*  d, int  length);
   void writeBinaryArray(SoOutput* theWrappedObject, float*  f, int  length);
   void writeBinaryArray(SoOutput* theWrappedObject, int*  l, int  length);
   void writeBinaryArray(SoOutput* theWrappedObject, unsigned char*  c, int  length);
};





class PythonQtShell_SoPath : public SoPath
{
public:
    PythonQtShell_SoPath():SoPath(),_wrapper(nullptr) {_type = getClassTypeId();
};
    PythonQtShell_SoPath(SoNode*  node):SoPath(node),_wrapper(nullptr) {_type = getClassTypeId();
};
    PythonQtShell_SoPath(int  approxLength):SoPath(approxLength),_wrapper(nullptr) {_type = getClassTypeId();
};

   ~PythonQtShell_SoPath() override;

SbName  getName() const override;
void setName(const SbName&  name) override;
void startNotify() override;
void write(SoWriteAction*  writeAction) const override;


   SoType _type;
   SoType getTypeId() const override { return _type; }

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoPath : public SoPath
{ public:
inline void promoted_auditPath(bool  flag) { this->auditPath(flag); }
inline void py_q_write(SoWriteAction*  writeAction) const { SoPath::write(writeAction); }
};

class PythonQtWrapper_SoPath : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoPath* new_SoPath();
SoPath* new_SoPath(SoNode*  node);
SoPath* new_SoPath(int  approxLength);
SoPath* new_SoPath(const SoPath& other) {
PythonQtShell_SoPath* a = new PythonQtShell_SoPath();
*((SoPath*)a) = other;
return a; }
   void append(SoPath* theWrappedObject, SoNode*  childNode);
   void append(SoPath* theWrappedObject, const SoPath*  fromPath);
   void append(SoPath* theWrappedObject, int  childIndex);
   void auditPath(SoPath* theWrappedObject, bool  flag);
   bool  containsNode(SoPath* theWrappedObject, const SoNode*  node) const;
   bool  containsPath(SoPath* theWrappedObject, const SoPath*  path) const;
   SoPath*  copy(SoPath* theWrappedObject, int  startFromNodeIndex = 0, int  numNodes = 0) const;
   int  findFork(SoPath* theWrappedObject, const SoPath*  path) const;
   SoPath*  static_SoPath_getByName(const SbName&  name);
   SoType  static_SoPath_getClassTypeId();
   SoNode*  getHead(SoPath* theWrappedObject) const;
   int  getIndex(SoPath* theWrappedObject, int  i) const;
   int  getIndexFromTail(SoPath* theWrappedObject, int  i) const;
   int  getLength(SoPath* theWrappedObject) const;
   SoNode*  getNode(SoPath* theWrappedObject, int  i) const;
   SoNode*  getNodeFromTail(SoPath* theWrappedObject, int  i) const;
   SoNode*  getTail(SoPath* theWrappedObject) const;
   void insertIndex(SoPath* theWrappedObject, SoNode*  parent, int  newIndex);
   bool  __eq__(SoPath* theWrappedObject, const SoPath&  p2);
   void pop(SoPath* theWrappedObject);
   void push(SoPath* theWrappedObject, int  childIndex);
   void removeIndex(SoPath* theWrappedObject, SoNode*  parent, int  oldIndex);
   void replaceIndex(SoPath* theWrappedObject, SoNode*  parent, int  index, SoNode*  newChild);
   void setHead(SoPath* theWrappedObject, SoNode*  node);
   void truncate(SoPath* theWrappedObject, int  start);
   void write(SoPath* theWrappedObject, SoWriteAction*  writeAction) const;
   void py_q_write(SoPath* theWrappedObject, SoWriteAction*  writeAction) const{  (((PythonQtPublicPromoter_SoPath*)theWrappedObject)->py_q_write(writeAction));}
};





class PythonQtWrapper_SoPickedPoint : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoPickedPoint* new_SoPickedPoint(const SoPath*  path, SoState*  state, const SbVec3f&  objSpacePoint);
SoPickedPoint* new_SoPickedPoint(const SoPickedPoint&  pp);
void delete_SoPickedPoint(SoPickedPoint* obj) { delete obj; }
   SoPickedPoint*  copy(SoPickedPoint* theWrappedObject) const;
   const SoDetail*  getDetail(SoPickedPoint* theWrappedObject, const SoNode*  node = nullptr) const;
   SbMatrix  getImageToObject(SoPickedPoint* theWrappedObject, const SoNode*  node = nullptr) const;
   int  getMaterialIndex(SoPickedPoint* theWrappedObject) const;
   const SbVec3f*  getNormal(SoPickedPoint* theWrappedObject) const;
   SbVec3f  getObjectNormal(SoPickedPoint* theWrappedObject, const SoNode*  node = nullptr) const;
   SbVec3f  getObjectPoint(SoPickedPoint* theWrappedObject, const SoNode*  node = nullptr) const;
   SbVec4f  getObjectTextureCoords(SoPickedPoint* theWrappedObject, const SoNode*  node = nullptr) const;
   SbMatrix  getObjectToImage(SoPickedPoint* theWrappedObject, const SoNode*  node = nullptr) const;
   SbMatrix  getObjectToWorld(SoPickedPoint* theWrappedObject, const SoNode*  node = nullptr) const;
   SoPath*  getPath(SoPickedPoint* theWrappedObject) const;
   const SbVec3f*  getPoint(SoPickedPoint* theWrappedObject) const;
   const SbVec4f*  getTextureCoords(SoPickedPoint* theWrappedObject) const;
   SbMatrix  getWorldToObject(SoPickedPoint* theWrappedObject, const SoNode*  node = nullptr) const;
   bool  isOnGeometry(SoPickedPoint* theWrappedObject) const;
   void setDetail(SoPickedPoint* theWrappedObject, SoDetail*  detail, SoNode*  node);
   void setMaterialIndex(SoPickedPoint* theWrappedObject, int  index);
   void setObjectNormal(SoPickedPoint* theWrappedObject, const SbVec3f&  normal);
   void setObjectTextureCoords(SoPickedPoint* theWrappedObject, const SbVec4f&  texCoords);
};





class PythonQtWrapper_SoPrimitiveVertex : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoPrimitiveVertex* new_SoPrimitiveVertex();
SoPrimitiveVertex* new_SoPrimitiveVertex(const SoPrimitiveVertex&  pv);
void delete_SoPrimitiveVertex(SoPrimitiveVertex* obj) { delete obj; }
   const SoDetail*  getDetail(SoPrimitiveVertex* theWrappedObject) const;
   int  getMaterialIndex(SoPrimitiveVertex* theWrappedObject) const;
   const SbVec3f*  getNormal(SoPrimitiveVertex* theWrappedObject) const;
   const SbVec3f*  getPoint(SoPrimitiveVertex* theWrappedObject) const;
   const SbVec4f*  getTextureCoords(SoPrimitiveVertex* theWrappedObject) const;
   SoPrimitiveVertex*  operator_assign(SoPrimitiveVertex* theWrappedObject, const SoPrimitiveVertex&  pv);
   void setDetail(SoPrimitiveVertex* theWrappedObject, SoDetail*  d);
   void setMaterialIndex(SoPrimitiveVertex* theWrappedObject, int  index);
   void setNormal(SoPrimitiveVertex* theWrappedObject, const SbVec3f&  norm);
   void setPoint(SoPrimitiveVertex* theWrappedObject, const SbVec3f&  pt);
   void setTextureCoords(SoPrimitiveVertex* theWrappedObject, const SbVec4f&  t);
};





class PythonQtShell_SoSceneManager : public SoSceneManager
{
public:
    PythonQtShell_SoSceneManager():SoSceneManager(),_wrapper(nullptr) {};

   ~PythonQtShell_SoSceneManager() override;

void activate() override;
void deactivate() override;
SoNode*  getSceneGraph() const override;
bool  processEvent(const SoEvent*  event) override;
void render(bool  clearWindow = 1, bool  clearZbuffer = 1) override;
void setSceneGraph(SoNode*  newScene) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoSceneManager : public SoSceneManager
{ public:
inline bool  promoted_isActive() const { return this->isActive(); }
inline void promoted_redraw() { this->redraw(); }
inline void py_q_activate() { SoSceneManager::activate(); }
inline void py_q_deactivate() { SoSceneManager::deactivate(); }
inline SoNode*  py_q_getSceneGraph() const { return SoSceneManager::getSceneGraph(); }
inline bool  py_q_processEvent(const SoEvent*  event) { return SoSceneManager::processEvent(event); }
inline void py_q_render(bool  clearWindow = 1, bool  clearZbuffer = 1) { SoSceneManager::render(clearWindow, clearZbuffer); }
inline void py_q_setSceneGraph(SoNode*  newScene) { SoSceneManager::setSceneGraph(newScene); }
};

class PythonQtWrapper_SoSceneManager : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSceneManager* new_SoSceneManager();
SoSceneManager* new_SoSceneManager(const SoSceneManager& other) {
PythonQtShell_SoSceneManager* a = new PythonQtShell_SoSceneManager();
*((SoSceneManager*)a) = other;
return a; }
void delete_SoSceneManager(SoSceneManager* obj) { delete obj; }
   void activate(SoSceneManager* theWrappedObject);
   void py_q_activate(SoSceneManager* theWrappedObject){  (((PythonQtPublicPromoter_SoSceneManager*)theWrappedObject)->py_q_activate());}
   void deactivate(SoSceneManager* theWrappedObject);
   void py_q_deactivate(SoSceneManager* theWrappedObject){  (((PythonQtPublicPromoter_SoSceneManager*)theWrappedObject)->py_q_deactivate());}
   void static_SoSceneManager_enableRealTimeUpdate(bool  flag);
   void getAntialiasing(SoSceneManager* theWrappedObject, bool&  smoothing, int&  numPasses) const;
   const SbColor*  getBackgroundColor(SoSceneManager* theWrappedObject) const;
   unsigned int  static_SoSceneManager_getDefaultRedrawPriority();
   SoGLRenderAction*  getGLRenderAction(SoSceneManager* theWrappedObject) const;
   SoHandleEventAction*  getHandleEventAction(SoSceneManager* theWrappedObject) const;
   const SbVec2s*  getOrigin(SoSceneManager* theWrappedObject) const;
   unsigned int  getRedrawPriority(SoSceneManager* theWrappedObject) const;
   SoNode*  getSceneGraph(SoSceneManager* theWrappedObject) const;
   SoNode*  py_q_getSceneGraph(SoSceneManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoSceneManager*)theWrappedObject)->py_q_getSceneGraph());}
   const SbVec2s*  getSize(SoSceneManager* theWrappedObject) const;
   const SbViewportRegion*  getViewportRegion(SoSceneManager* theWrappedObject) const;
   const SbVec2s*  getWindowSize(SoSceneManager* theWrappedObject) const;
   bool  isActive(SoSceneManager* theWrappedObject) const;
   bool  isAutoRedraw(SoSceneManager* theWrappedObject) const;
   bool  static_SoSceneManager_isRealTimeUpdateEnabled();
   bool  processEvent(SoSceneManager* theWrappedObject, const SoEvent*  event);
   bool  py_q_processEvent(SoSceneManager* theWrappedObject, const SoEvent*  event){  return (((PythonQtPublicPromoter_SoSceneManager*)theWrappedObject)->py_q_processEvent(event));}
   void redraw(SoSceneManager* theWrappedObject);
   void reinitialize(SoSceneManager* theWrappedObject);
   void render(SoSceneManager* theWrappedObject, bool  clearWindow = 1, bool  clearZbuffer = 1);
   void py_q_render(SoSceneManager* theWrappedObject, bool  clearWindow = 1, bool  clearZbuffer = 1){  (((PythonQtPublicPromoter_SoSceneManager*)theWrappedObject)->py_q_render(clearWindow, clearZbuffer));}
   void scheduleRedraw(SoSceneManager* theWrappedObject);
   void setAntialiasing(SoSceneManager* theWrappedObject, bool  smoothing, int  numPasses);
   void setBackgroundColor(SoSceneManager* theWrappedObject, const SbColor&  c);
   void setGLRenderAction(SoSceneManager* theWrappedObject, SoGLRenderAction*  ra);
   void setHandleEventAction(SoSceneManager* theWrappedObject, SoHandleEventAction*  hea);
   void setOrigin(SoSceneManager* theWrappedObject, const SbVec2s&  newOrigin);
   void setRedrawPriority(SoSceneManager* theWrappedObject, unsigned int  priority);
   void setSceneGraph(SoSceneManager* theWrappedObject, SoNode*  newScene);
   void py_q_setSceneGraph(SoSceneManager* theWrappedObject, SoNode*  newScene){  (((PythonQtPublicPromoter_SoSceneManager*)theWrappedObject)->py_q_setSceneGraph(newScene));}
   void setSize(SoSceneManager* theWrappedObject, const SbVec2s&  newSize);
   void setViewportRegion(SoSceneManager* theWrappedObject, const SbViewportRegion&  newRegion);
   void setWindowSize(SoSceneManager* theWrappedObject, const SbVec2s&  newSize);
};





class PythonQtWrapper_SoState : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
void delete_SoState(SoState* obj) { delete obj; }
   SoAction*  getAction(SoState* theWrappedObject) const;
   const SoElement*  getConstElement(SoState* theWrappedObject, int  stackIndex) const;
   int  getDepth(SoState* theWrappedObject) const;
   SoElement*  getElement(SoState* theWrappedObject, int  stackIndex);
   SoElement*  getElementNoPush(SoState* theWrappedObject, int  stackIndex) const;
   bool  isCacheOpen(SoState* theWrappedObject) const;
   bool  isElementEnabled(SoState* theWrappedObject, int  stackIndex) const;
   void pop(SoState* theWrappedObject);
   void push(SoState* theWrappedObject);
   void setCacheOpen(SoState* theWrappedObject, bool  flag);
};





class PythonQtShell_SoType : public SoType
{
public:
    PythonQtShell_SoType():SoType(),_wrapper(nullptr) {};

   ~PythonQtShell_SoType();


  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoType : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoType* new_SoType();
SoType* new_SoType(const SoType& other) {
PythonQtShell_SoType* a = new PythonQtShell_SoType();
*((SoType*)a) = other;
return a; }
void delete_SoType(SoType* obj) { delete obj; }
   SoType  static_SoType_badType();
   bool  canCreateInstance(SoType* theWrappedObject) const;
   void*  createInstance(SoType* theWrappedObject) const;
   SoType  static_SoType_fromName(SbName  name);
   short  getData(SoType* theWrappedObject) const;
   short  getKey(SoType* theWrappedObject) const;
   SbName  getName(SoType* theWrappedObject) const;
   int  static_SoType_getNumTypes();
   SoType  getParent(SoType* theWrappedObject) const;
   void static_SoType_init();
   bool  isBad(SoType* theWrappedObject) const;
   bool  isDerivedFrom(SoType* theWrappedObject, SoType  t) const;
   void makeInternal(SoType* theWrappedObject);
   bool  __ne__(SoType* theWrappedObject, const SoType  t) const;
   bool  __lt__(SoType* theWrappedObject, const SoType  t) const;
   bool  __eq__(SoType* theWrappedObject, const SoType  t) const;
};


