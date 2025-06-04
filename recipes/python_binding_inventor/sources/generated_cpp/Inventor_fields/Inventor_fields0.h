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
#include <Inventor/SbColor.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbLineard.h>
#include <Inventor/SbString.h>
#include <Inventor/SbTime.h>
#include <Inventor/SoInput.h>
#include <Inventor/SoOutput.h>
#include <Inventor/SoPath.h>
#include <Inventor/SoType.h>
#include <Inventor/engines/SoEngine.h>
#include <Inventor/engines/SoFieldConverter.h>
#include <Inventor/fields/SoField.h>
#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/fields/SoMFBitMask.h>
#include <Inventor/fields/SoMFBool.h>
#include <Inventor/fields/SoMFColor.h>
#include <Inventor/fields/SoMFDouble.h>
#include <Inventor/fields/SoMFEngine.h>
#include <Inventor/fields/SoMFEnum.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoMFMatrix.h>
#include <Inventor/fields/SoMFMatrixd.h>
#include <Inventor/fields/SoMFName.h>
#include <Inventor/fields/SoMFNode.h>
#include <Inventor/fields/SoMFPath.h>
#include <Inventor/fields/SoMFPlane.h>
#include <Inventor/fields/SoMFPlaned.h>
#include <Inventor/fields/SoMFRotation.h>
#include <Inventor/fields/SoMFRotationd.h>
#include <Inventor/fields/SoMFShort.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoMFTime.h>
#include <Inventor/fields/SoMFUInt32.h>
#include <Inventor/fields/SoMFUShort.h>
#include <Inventor/fields/SoMFVec2d.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoMFVec3d.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFVec4d.h>
#include <Inventor/fields/SoMFVec4f.h>
#include <Inventor/misc/SoBase.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/sensors/SoSensor.h>
#include <stdexcept>



class PythonQtWrapper_SoField : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
void delete_SoField(SoField* obj) { delete obj; }
   bool  connectFrom(SoField* theWrappedObject, SoEngineOutput*  engineOutput);
   bool  connectFrom(SoField* theWrappedObject, SoField*  field);
   void connectionStatusChanged(SoField* theWrappedObject, int  numConnections);
   void copyConnection(SoField* theWrappedObject, const SoField*  fromField);
   void copyFrom(SoField* theWrappedObject, const SoField&  f);
   void countWriteRefs(SoField* theWrappedObject, SoOutput*  out) const;
   void disconnect(SoField* theWrappedObject);
   void enableConnection(SoField* theWrappedObject, bool  flag);
   bool  enableContainerNotify(SoField* theWrappedObject, bool  flag);
   bool  enableNotify(SoField* theWrappedObject, bool  flag);
   void evaluate(SoField* theWrappedObject) const;
   void fixCopy(SoField* theWrappedObject, bool  copyConnections);
   SoType  static_SoField_getClassTypeId();
   SoFieldContainer*  getContainer(SoField* theWrappedObject) const;
   bool  isConnected(SoField* theWrappedObject) const;
   bool  isConnectedFromEngine(SoField* theWrappedObject) const;
   bool  isConnectedFromField(SoField* theWrappedObject) const;
   bool  isConnectionEnabled(SoField* theWrappedObject) const;
   bool  isContainerNotifyEnabled(SoField* theWrappedObject) const;
   bool  isDefault(SoField* theWrappedObject) const;
   bool  isIgnored(SoField* theWrappedObject) const;
   bool  isNotifyEnabled(SoField* theWrappedObject) const;
   bool  isOfType(SoField* theWrappedObject, SoType  type) const;
   bool  isReadOnly(SoField* theWrappedObject) const;
   bool  isSame(SoField* theWrappedObject, const SoField&  f) const;
   bool  __ne__(SoField* theWrappedObject, const SoField&  f) const;
   bool  __eq__(SoField* theWrappedObject, const SoField&  f) const;
   bool  read(SoField* theWrappedObject, SoInput*  in, const SbName&  name);
   bool  referencesCopy(SoField* theWrappedObject) const;
   bool  set(SoField* theWrappedObject, const char*  valueString);
   void setContainer(SoField* theWrappedObject, SoFieldContainer*  cont);
   void setDefault(SoField* theWrappedObject, bool  def);
   void setIgnored(SoField* theWrappedObject, bool  ig);
   void startNotify(SoField* theWrappedObject);
   void touch(SoField* theWrappedObject);
   void write(SoField* theWrappedObject, SoOutput*  out, const SbName&  name) const;
};





class PythonQtWrapper_SoFieldContainer : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
   void addManagedSensor(SoFieldContainer* theWrappedObject, SoSensor*  sensor);
   bool  enableNotify(SoFieldContainer* theWrappedObject, bool  flag);
   bool  fieldsAreEqual(SoFieldContainer* theWrappedObject, const SoFieldContainer*  fc) const;
   SoType  static_SoFieldContainer_getClassTypeId();
   SoField*  getField(SoFieldContainer* theWrappedObject, const SbName&  fieldName) const;
   bool  getIsBuiltIn(SoFieldContainer* theWrappedObject) const;
   bool  hasDefaultValues(SoFieldContainer* theWrappedObject) const;
   bool  isNotifyEnabled(SoFieldContainer* theWrappedObject) const;
   bool  set(SoFieldContainer* theWrappedObject, const char*  fieldDataString);
   bool  set(SoFieldContainer* theWrappedObject, const char*  fieldDataString, SoInput*  dictIn);
   void setToDefaults(SoFieldContainer* theWrappedObject);
};





class PythonQtWrapper_SoMFBitMask : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFBitMask* new_SoMFBitMask();
void delete_SoMFBitMask(SoMFBitMask* obj) { delete obj; }
   void*  static_SoMFBitMask_createInstance();
   SoType  static_SoMFBitMask_getClassTypeId();
   const SoMFBitMask*  operator_assign(SoMFBitMask* theWrappedObject, const SoMFBitMask&  f);
   int  operator_assign(SoMFBitMask* theWrappedObject, int  newValue);
};





class PythonQtWrapper_SoMFBool : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFBool* new_SoMFBool();
void delete_SoMFBool(SoMFBool* obj) { delete obj; }
   void*  static_SoMFBool_createInstance();
   int  find(SoMFBool* theWrappedObject, bool  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFBool* theWrappedObject);
   SoType  static_SoMFBool_getClassTypeId();
   bool  __ne__(SoMFBool* theWrappedObject, const SoMFBool&  f) const;
   bool  operator_assign(SoMFBool* theWrappedObject, bool  newValue);
   const SoMFBool*  operator_assign(SoMFBool* theWrappedObject, const SoMFBool&  f);
   bool  __eq__(SoMFBool* theWrappedObject, const SoMFBool&  f) const;
   bool  operator_subscript(SoMFBool* theWrappedObject, int  i) const;
   void set1Value(SoMFBool* theWrappedObject, int  index, bool  newValue);
   void setValue(SoMFBool* theWrappedObject, bool  newValue);
   void setValues(SoMFBool* theWrappedObject, int  start, int  num, const bool*  newValues);
};





class PythonQtWrapper_SoMFColor : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFColor* new_SoMFColor();
void delete_SoMFColor(SoMFColor* obj) { delete obj; }
   void*  static_SoMFColor_createInstance();
   int  find(SoMFColor* theWrappedObject, const SbColor&  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFColor* theWrappedObject);
   SoType  static_SoMFColor_getClassTypeId();
   bool  __ne__(SoMFColor* theWrappedObject, const SoMFColor&  f) const;
   const SbColor*  operator_assign(SoMFColor* theWrappedObject, const SbColor&  newValue);
   const SoMFColor*  operator_assign(SoMFColor* theWrappedObject, const SoMFColor&  f);
   bool  __eq__(SoMFColor* theWrappedObject, const SoMFColor&  f) const;
   const SbColor*  operator_subscript(SoMFColor* theWrappedObject, int  i) const;
   void set1HSVValue(SoMFColor* theWrappedObject, int  index, float  h, float  s, float  v);
   void set1Value(SoMFColor* theWrappedObject, int  index, const SbColor&  newValue);
   void set1Value(SoMFColor* theWrappedObject, int  index, const SbVec3f&  vec);
   void set1Value(SoMFColor* theWrappedObject, int  index, float  r, float  g, float  b);
   void setHSVValue(SoMFColor* theWrappedObject, float  h, float  s, float  v);
   void setValue(SoMFColor* theWrappedObject, const SbColor&  newValue);
   void setValue(SoMFColor* theWrappedObject, const SbVec3f&  vec);
   void setValue(SoMFColor* theWrappedObject, float  r, float  g, float  b);
   void setValues(SoMFColor* theWrappedObject, int  start, int  num, const SbColor*  newValues);
};





class PythonQtWrapper_SoMFDouble : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFDouble* new_SoMFDouble();
void delete_SoMFDouble(SoMFDouble* obj) { delete obj; }
   void*  static_SoMFDouble_createInstance();
   int  find(SoMFDouble* theWrappedObject, double  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFDouble* theWrappedObject);
   SoType  static_SoMFDouble_getClassTypeId();
   bool  __ne__(SoMFDouble* theWrappedObject, const SoMFDouble&  f) const;
   const SoMFDouble*  operator_assign(SoMFDouble* theWrappedObject, const SoMFDouble&  f);
   double  operator_assign(SoMFDouble* theWrappedObject, double  newValue);
   bool  __eq__(SoMFDouble* theWrappedObject, const SoMFDouble&  f) const;
   double  operator_subscript(SoMFDouble* theWrappedObject, int  i) const;
   void set1Value(SoMFDouble* theWrappedObject, int  index, double  newValue);
   void setValue(SoMFDouble* theWrappedObject, double  newValue);
   void setValues(SoMFDouble* theWrappedObject, int  start, int  num, const double*  newValues);
};





class PythonQtWrapper_SoMFEngine : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFEngine* new_SoMFEngine();
void delete_SoMFEngine(SoMFEngine* obj) { delete obj; }
   void*  static_SoMFEngine_createInstance();
   int  find(SoMFEngine* theWrappedObject, SoEngine*  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFEngine* theWrappedObject);
   SoType  static_SoMFEngine_getClassTypeId();
   bool  __ne__(SoMFEngine* theWrappedObject, const SoMFEngine&  f) const;
   SoEngine*  operator_assign(SoMFEngine* theWrappedObject, SoEngine*  newValue);
   const SoMFEngine*  operator_assign(SoMFEngine* theWrappedObject, const SoMFEngine&  f);
   bool  __eq__(SoMFEngine* theWrappedObject, const SoMFEngine&  f) const;
   SoEngine*  operator_subscript(SoMFEngine* theWrappedObject, int  i) const;
   void set1Value(SoMFEngine* theWrappedObject, int  index, SoEngine*  newValue);
   void setValue(SoMFEngine* theWrappedObject, SoEngine*  newValue);
   void setValues(SoMFEngine* theWrappedObject, int  start, int  num, const SoEngine**  newValues);
};





class PythonQtWrapper_SoMFEnum : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFEnum* new_SoMFEnum();
void delete_SoMFEnum(SoMFEnum* obj) { delete obj; }
   void*  static_SoMFEnum_createInstance();
   int  find(SoMFEnum* theWrappedObject, int  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFEnum* theWrappedObject);
   SoType  static_SoMFEnum_getClassTypeId();
   bool  __ne__(SoMFEnum* theWrappedObject, const SoMFEnum&  f) const;
   const SoMFEnum*  operator_assign(SoMFEnum* theWrappedObject, const SoMFEnum&  f);
   int  operator_assign(SoMFEnum* theWrappedObject, int  newValue);
   bool  __eq__(SoMFEnum* theWrappedObject, const SoMFEnum&  f) const;
   int  operator_subscript(SoMFEnum* theWrappedObject, int  i) const;
   void set1Value(SoMFEnum* theWrappedObject, int  index, const SbName&  name);
   void set1Value(SoMFEnum* theWrappedObject, int  index, int  newValue);
   void setEnums(SoMFEnum* theWrappedObject, int  num, int*  vals, SbName*  names);
   void setValue(SoMFEnum* theWrappedObject, const SbName&  name);
   void setValue(SoMFEnum* theWrappedObject, int  newValue);
   void setValues(SoMFEnum* theWrappedObject, int  start, int  num, const int*  newValues);
};





class PythonQtWrapper_SoMFFloat : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFFloat* new_SoMFFloat();
void delete_SoMFFloat(SoMFFloat* obj) { delete obj; }
   void*  static_SoMFFloat_createInstance();
   int  find(SoMFFloat* theWrappedObject, float  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFFloat* theWrappedObject);
   SoType  static_SoMFFloat_getClassTypeId();
   bool  __ne__(SoMFFloat* theWrappedObject, const SoMFFloat&  f) const;
   const SoMFFloat*  operator_assign(SoMFFloat* theWrappedObject, const SoMFFloat&  f);
   float  operator_assign(SoMFFloat* theWrappedObject, float  newValue);
   bool  __eq__(SoMFFloat* theWrappedObject, const SoMFFloat&  f) const;
   float  operator_subscript(SoMFFloat* theWrappedObject, int  i) const;
   void set1Value(SoMFFloat* theWrappedObject, int  index, float  newValue);
   void setValue(SoMFFloat* theWrappedObject, float  newValue);
   void setValues(SoMFFloat* theWrappedObject, int  start, int  num, const float*  newValues);
};





class PythonQtWrapper_SoMFInt32 : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFInt32* new_SoMFInt32();
void delete_SoMFInt32(SoMFInt32* obj) { delete obj; }
   void*  static_SoMFInt32_createInstance();
   int  find(SoMFInt32* theWrappedObject, int  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFInt32* theWrappedObject);
   SoType  static_SoMFInt32_getClassTypeId();
   bool  __ne__(SoMFInt32* theWrappedObject, const SoMFInt32&  f) const;
   const SoMFInt32*  operator_assign(SoMFInt32* theWrappedObject, const SoMFInt32&  f);
   int  operator_assign(SoMFInt32* theWrappedObject, int  newValue);
   bool  __eq__(SoMFInt32* theWrappedObject, const SoMFInt32&  f) const;
   int  operator_subscript(SoMFInt32* theWrappedObject, int  i) const;
   void set1Value(SoMFInt32* theWrappedObject, int  index, int  newValue);
   void setValue(SoMFInt32* theWrappedObject, int  newValue);
   void setValues(SoMFInt32* theWrappedObject, int  start, int  num, const int*  newValues);
};





class PythonQtWrapper_SoMFMatrix : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFMatrix* new_SoMFMatrix();
void delete_SoMFMatrix(SoMFMatrix* obj) { delete obj; }
   void*  static_SoMFMatrix_createInstance();
   int  find(SoMFMatrix* theWrappedObject, const SbMatrix&  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFMatrix* theWrappedObject);
   SoType  static_SoMFMatrix_getClassTypeId();
   bool  __ne__(SoMFMatrix* theWrappedObject, const SoMFMatrix&  f) const;
   const SbMatrix*  operator_assign(SoMFMatrix* theWrappedObject, const SbMatrix&  newValue);
   const SoMFMatrix*  operator_assign(SoMFMatrix* theWrappedObject, const SoMFMatrix&  f);
   bool  __eq__(SoMFMatrix* theWrappedObject, const SoMFMatrix&  f) const;
   const SbMatrix*  operator_subscript(SoMFMatrix* theWrappedObject, int  i) const;
   void set1Value(SoMFMatrix* theWrappedObject, int  index, const SbMatrix&  newValue);
   void setValue(SoMFMatrix* theWrappedObject, const SbMatrix&  newValue);
   void setValue(SoMFMatrix* theWrappedObject, float  a11, float  a12, float  a13, float  a14, float  a21, float  a22, float  a23, float  a24, float  a31, float  a32, float  a33, float  a34, float  a41, float  a42, float  a43, float  a44);
   void setValues(SoMFMatrix* theWrappedObject, int  start, int  num, const SbMatrix*  newValues);
};





class PythonQtWrapper_SoMFMatrixd : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFMatrixd* new_SoMFMatrixd();
void delete_SoMFMatrixd(SoMFMatrixd* obj) { delete obj; }
   void*  static_SoMFMatrixd_createInstance();
   int  find(SoMFMatrixd* theWrappedObject, const SbMatrixd&  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFMatrixd* theWrappedObject);
   SoType  static_SoMFMatrixd_getClassTypeId();
   bool  __ne__(SoMFMatrixd* theWrappedObject, const SoMFMatrixd&  f) const;
   const SbMatrixd*  operator_assign(SoMFMatrixd* theWrappedObject, const SbMatrixd&  newValue);
   const SoMFMatrixd*  operator_assign(SoMFMatrixd* theWrappedObject, const SoMFMatrixd&  f);
   bool  __eq__(SoMFMatrixd* theWrappedObject, const SoMFMatrixd&  f) const;
   const SbMatrixd*  operator_subscript(SoMFMatrixd* theWrappedObject, int  i) const;
   void set1Value(SoMFMatrixd* theWrappedObject, int  index, const SbMatrixd&  newValue);
   void setValue(SoMFMatrixd* theWrappedObject, const SbMatrixd&  newValue);
   void setValue(SoMFMatrixd* theWrappedObject, double  a11, double  a12, double  a13, double  a14, double  a21, double  a22, double  a23, double  a24, double  a31, double  a32, double  a33, double  a34, double  a41, double  a42, double  a43, double  a44);
   void setValues(SoMFMatrixd* theWrappedObject, int  start, int  num, const SbMatrixd*  newValues);
};





class PythonQtWrapper_SoMFName : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFName* new_SoMFName();
void delete_SoMFName(SoMFName* obj) { delete obj; }
   void*  static_SoMFName_createInstance();
   int  find(SoMFName* theWrappedObject, const SbName&  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFName* theWrappedObject);
   SoType  static_SoMFName_getClassTypeId();
   bool  __ne__(SoMFName* theWrappedObject, const SoMFName&  f) const;
   const SbName*  operator_assign(SoMFName* theWrappedObject, const SbName&  newValue);
   const SoMFName*  operator_assign(SoMFName* theWrappedObject, const SoMFName&  f);
   bool  __eq__(SoMFName* theWrappedObject, const SoMFName&  f) const;
   const SbName*  operator_subscript(SoMFName* theWrappedObject, int  i) const;
   void set1Value(SoMFName* theWrappedObject, int  index, const SbName&  newValue);
   void setValue(SoMFName* theWrappedObject, const SbName&  newValue);
   void setValue(SoMFName* theWrappedObject, const char*  string);
   void setValues(SoMFName* theWrappedObject, int  start, int  num, const SbName*  newValues);
   void setValues(SoMFName* theWrappedObject, int  start, int  num, const char**  strings);
};





class PythonQtWrapper_SoMFNode : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFNode* new_SoMFNode();
void delete_SoMFNode(SoMFNode* obj) { delete obj; }
   void*  static_SoMFNode_createInstance();
   int  find(SoMFNode* theWrappedObject, SoNode*  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFNode* theWrappedObject);
   SoType  static_SoMFNode_getClassTypeId();
   bool  __ne__(SoMFNode* theWrappedObject, const SoMFNode&  f) const;
   SoNode*  operator_assign(SoMFNode* theWrappedObject, SoNode*  newValue);
   const SoMFNode*  operator_assign(SoMFNode* theWrappedObject, const SoMFNode&  f);
   bool  __eq__(SoMFNode* theWrappedObject, const SoMFNode&  f) const;
   SoNode*  operator_subscript(SoMFNode* theWrappedObject, int  i) const;
   void set1Value(SoMFNode* theWrappedObject, int  index, SoNode*  newValue);
   void setValue(SoMFNode* theWrappedObject, SoNode*  newValue);
   void setValues(SoMFNode* theWrappedObject, int  start, int  num, const SoNode**  newValues);
};





class PythonQtWrapper_SoMFPath : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFPath* new_SoMFPath();
void delete_SoMFPath(SoMFPath* obj) { delete obj; }
   void*  static_SoMFPath_createInstance();
   int  find(SoMFPath* theWrappedObject, SoPath*  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFPath* theWrappedObject);
   SoType  static_SoMFPath_getClassTypeId();
   bool  __ne__(SoMFPath* theWrappedObject, const SoMFPath&  f) const;
   SoPath*  operator_assign(SoMFPath* theWrappedObject, SoPath*  newValue);
   const SoMFPath*  operator_assign(SoMFPath* theWrappedObject, const SoMFPath&  f);
   bool  __eq__(SoMFPath* theWrappedObject, const SoMFPath&  f) const;
   SoPath*  operator_subscript(SoMFPath* theWrappedObject, int  i) const;
   void set1Value(SoMFPath* theWrappedObject, int  index, SoPath*  newValue);
   void setValue(SoMFPath* theWrappedObject, SoPath*  newValue);
   void setValues(SoMFPath* theWrappedObject, int  start, int  num, const SoPath**  newValues);
};





class PythonQtWrapper_SoMFPlane : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFPlane* new_SoMFPlane();
void delete_SoMFPlane(SoMFPlane* obj) { delete obj; }
   void*  static_SoMFPlane_createInstance();
   int  find(SoMFPlane* theWrappedObject, SbPlane  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFPlane* theWrappedObject);
   SoType  static_SoMFPlane_getClassTypeId();
   bool  __ne__(SoMFPlane* theWrappedObject, const SoMFPlane&  f) const;
   SbPlane  operator_assign(SoMFPlane* theWrappedObject, SbPlane  newValue);
   const SoMFPlane*  operator_assign(SoMFPlane* theWrappedObject, const SoMFPlane&  f);
   bool  __eq__(SoMFPlane* theWrappedObject, const SoMFPlane&  f) const;
   SbPlane  operator_subscript(SoMFPlane* theWrappedObject, int  i) const;
   void set1Value(SoMFPlane* theWrappedObject, int  index, SbPlane  newValue);
   void setValue(SoMFPlane* theWrappedObject, SbPlane  newValue);
   void setValues(SoMFPlane* theWrappedObject, int  start, int  num, const SbPlane*  newValues);
};





class PythonQtWrapper_SoMFPlaned : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFPlaned* new_SoMFPlaned();
void delete_SoMFPlaned(SoMFPlaned* obj) { delete obj; }
   void*  static_SoMFPlaned_createInstance();
   int  find(SoMFPlaned* theWrappedObject, SbPlaned  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFPlaned* theWrappedObject);
   SoType  static_SoMFPlaned_getClassTypeId();
   bool  __ne__(SoMFPlaned* theWrappedObject, const SoMFPlaned&  f) const;
   SbPlaned  operator_assign(SoMFPlaned* theWrappedObject, SbPlaned  newValue);
   const SoMFPlaned*  operator_assign(SoMFPlaned* theWrappedObject, const SoMFPlaned&  f);
   bool  __eq__(SoMFPlaned* theWrappedObject, const SoMFPlaned&  f) const;
   SbPlaned  operator_subscript(SoMFPlaned* theWrappedObject, int  i) const;
   void set1Value(SoMFPlaned* theWrappedObject, int  index, SbPlaned  newValue);
   void setValue(SoMFPlaned* theWrappedObject, SbPlaned  newValue);
   void setValues(SoMFPlaned* theWrappedObject, int  start, int  num, const SbPlaned*  newValues);
};





class PythonQtWrapper_SoMFRotation : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFRotation* new_SoMFRotation();
void delete_SoMFRotation(SoMFRotation* obj) { delete obj; }
   void*  static_SoMFRotation_createInstance();
   int  find(SoMFRotation* theWrappedObject, const SbRotation&  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFRotation* theWrappedObject);
   SoType  static_SoMFRotation_getClassTypeId();
   bool  __ne__(SoMFRotation* theWrappedObject, const SoMFRotation&  f) const;
   const SbRotation*  operator_assign(SoMFRotation* theWrappedObject, const SbRotation&  newValue);
   const SoMFRotation*  operator_assign(SoMFRotation* theWrappedObject, const SoMFRotation&  f);
   bool  __eq__(SoMFRotation* theWrappedObject, const SoMFRotation&  f) const;
   const SbRotation*  operator_subscript(SoMFRotation* theWrappedObject, int  i) const;
   void set1Value(SoMFRotation* theWrappedObject, int  index, const SbRotation&  newValue);
   void set1Value(SoMFRotation* theWrappedObject, int  index, const SbVec3f&  axis, float  angle);
   void set1Value(SoMFRotation* theWrappedObject, int  index, float  q0, float  q1, float  q2, float  q3);
   void setValue(SoMFRotation* theWrappedObject, const SbRotation&  newValue);
   void setValue(SoMFRotation* theWrappedObject, const SbVec3f&  axis, float  angle);
   void setValue(SoMFRotation* theWrappedObject, float  q0, float  q1, float  q2, float  q3);
   void setValues(SoMFRotation* theWrappedObject, int  start, int  num, const SbRotation*  newValues);
};





class PythonQtWrapper_SoMFRotationd : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFRotationd* new_SoMFRotationd();
void delete_SoMFRotationd(SoMFRotationd* obj) { delete obj; }
   void*  static_SoMFRotationd_createInstance();
   int  find(SoMFRotationd* theWrappedObject, const SbRotationd&  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFRotationd* theWrappedObject);
   SoType  static_SoMFRotationd_getClassTypeId();
   bool  __ne__(SoMFRotationd* theWrappedObject, const SoMFRotationd&  f) const;
   const SbRotationd*  operator_assign(SoMFRotationd* theWrappedObject, const SbRotationd&  newValue);
   const SoMFRotationd*  operator_assign(SoMFRotationd* theWrappedObject, const SoMFRotationd&  f);
   bool  __eq__(SoMFRotationd* theWrappedObject, const SoMFRotationd&  f) const;
   const SbRotationd*  operator_subscript(SoMFRotationd* theWrappedObject, int  i) const;
   void set1Value(SoMFRotationd* theWrappedObject, int  index, const SbRotationd&  newValue);
   void set1Value(SoMFRotationd* theWrappedObject, int  index, const SbVec3d&  axis, double  angle);
   void set1Value(SoMFRotationd* theWrappedObject, int  index, double  q0, double  q1, double  q2, double  q3);
   void setValue(SoMFRotationd* theWrappedObject, const SbRotationd&  newValue);
   void setValue(SoMFRotationd* theWrappedObject, const SbVec3d&  axis, double  angle);
   void setValue(SoMFRotationd* theWrappedObject, double  q0, double  q1, double  q2, double  q3);
   void setValues(SoMFRotationd* theWrappedObject, int  start, int  num, const SbRotationd*  newValues);
};





class PythonQtWrapper_SoMFShort : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFShort* new_SoMFShort();
void delete_SoMFShort(SoMFShort* obj) { delete obj; }
   void*  static_SoMFShort_createInstance();
   int  find(SoMFShort* theWrappedObject, short  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFShort* theWrappedObject);
   SoType  static_SoMFShort_getClassTypeId();
   bool  __ne__(SoMFShort* theWrappedObject, const SoMFShort&  f) const;
   const SoMFShort*  operator_assign(SoMFShort* theWrappedObject, const SoMFShort&  f);
   short  operator_assign(SoMFShort* theWrappedObject, short  newValue);
   bool  __eq__(SoMFShort* theWrappedObject, const SoMFShort&  f) const;
   short  operator_subscript(SoMFShort* theWrappedObject, int  i) const;
   void set1Value(SoMFShort* theWrappedObject, int  index, short  newValue);
   void setValue(SoMFShort* theWrappedObject, short  newValue);
   void setValues(SoMFShort* theWrappedObject, int  start, int  num, const short*  newValues);
};





class PythonQtWrapper_SoMFString : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFString* new_SoMFString();
void delete_SoMFString(SoMFString* obj) { delete obj; }
   void*  static_SoMFString_createInstance();
   void deleteText(SoMFString* theWrappedObject, int  fromLine, int  fromChar, int  toLine, int  toChar);
   int  find(SoMFString* theWrappedObject, const SbString&  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFString* theWrappedObject);
   SoType  static_SoMFString_getClassTypeId();
   bool  __ne__(SoMFString* theWrappedObject, const SoMFString&  f) const;
   const SbString*  operator_assign(SoMFString* theWrappedObject, const SbString&  newValue);
   const SoMFString*  operator_assign(SoMFString* theWrappedObject, const SoMFString&  f);
   bool  __eq__(SoMFString* theWrappedObject, const SoMFString&  f) const;
   const SbString*  operator_subscript(SoMFString* theWrappedObject, int  i) const;
   void set1Value(SoMFString* theWrappedObject, int  index, const SbString&  newValue);
   void setValue(SoMFString* theWrappedObject, const SbString&  newValue);
   void setValue(SoMFString* theWrappedObject, const char*  string);
   void setValues(SoMFString* theWrappedObject, int  start, int  num, const SbString*  newValues);
   void setValues(SoMFString* theWrappedObject, int  start, int  num, const char**  strings);
};





class PythonQtWrapper_SoMFTime : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFTime* new_SoMFTime();
void delete_SoMFTime(SoMFTime* obj) { delete obj; }
   void*  static_SoMFTime_createInstance();
   int  find(SoMFTime* theWrappedObject, const SbTime&  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFTime* theWrappedObject);
   SoType  static_SoMFTime_getClassTypeId();
   bool  __ne__(SoMFTime* theWrappedObject, const SoMFTime&  f) const;
   const SbTime*  operator_assign(SoMFTime* theWrappedObject, const SbTime&  newValue);
   const SoMFTime*  operator_assign(SoMFTime* theWrappedObject, const SoMFTime&  f);
   bool  __eq__(SoMFTime* theWrappedObject, const SoMFTime&  f) const;
   const SbTime*  operator_subscript(SoMFTime* theWrappedObject, int  i) const;
   void set1Value(SoMFTime* theWrappedObject, int  index, const SbTime&  newValue);
   void setValue(SoMFTime* theWrappedObject, const SbTime&  newValue);
   void setValues(SoMFTime* theWrappedObject, int  start, int  num, const SbTime*  newValues);
};





class PythonQtWrapper_SoMFUInt32 : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFUInt32* new_SoMFUInt32();
void delete_SoMFUInt32(SoMFUInt32* obj) { delete obj; }
   void*  static_SoMFUInt32_createInstance();
   int  find(SoMFUInt32* theWrappedObject, unsigned int  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFUInt32* theWrappedObject);
   SoType  static_SoMFUInt32_getClassTypeId();
   bool  __ne__(SoMFUInt32* theWrappedObject, const SoMFUInt32&  f) const;
   const SoMFUInt32*  operator_assign(SoMFUInt32* theWrappedObject, const SoMFUInt32&  f);
   unsigned int  operator_assign(SoMFUInt32* theWrappedObject, unsigned int  newValue);
   bool  __eq__(SoMFUInt32* theWrappedObject, const SoMFUInt32&  f) const;
   unsigned int  operator_subscript(SoMFUInt32* theWrappedObject, int  i) const;
   void set1Value(SoMFUInt32* theWrappedObject, int  index, unsigned int  newValue);
   void setValue(SoMFUInt32* theWrappedObject, unsigned int  newValue);
   void setValues(SoMFUInt32* theWrappedObject, int  start, int  num, const unsigned int*  newValues);
};





class PythonQtWrapper_SoMFUShort : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFUShort* new_SoMFUShort();
void delete_SoMFUShort(SoMFUShort* obj) { delete obj; }
   void*  static_SoMFUShort_createInstance();
   int  find(SoMFUShort* theWrappedObject, unsigned short  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFUShort* theWrappedObject);
   SoType  static_SoMFUShort_getClassTypeId();
   bool  __ne__(SoMFUShort* theWrappedObject, const SoMFUShort&  f) const;
   const SoMFUShort*  operator_assign(SoMFUShort* theWrappedObject, const SoMFUShort&  f);
   unsigned short  operator_assign(SoMFUShort* theWrappedObject, unsigned short  newValue);
   bool  __eq__(SoMFUShort* theWrappedObject, const SoMFUShort&  f) const;
   unsigned short  operator_subscript(SoMFUShort* theWrappedObject, int  i) const;
   void set1Value(SoMFUShort* theWrappedObject, int  index, unsigned short  newValue);
   void setValue(SoMFUShort* theWrappedObject, unsigned short  newValue);
   void setValues(SoMFUShort* theWrappedObject, int  start, int  num, const unsigned short*  newValues);
};





class PythonQtWrapper_SoMFVec2d : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFVec2d* new_SoMFVec2d();
void delete_SoMFVec2d(SoMFVec2d* obj) { delete obj; }
   void*  static_SoMFVec2d_createInstance();
   int  find(SoMFVec2d* theWrappedObject, const SbVec2d&  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFVec2d* theWrappedObject);
   SoType  static_SoMFVec2d_getClassTypeId();
   bool  __ne__(SoMFVec2d* theWrappedObject, const SoMFVec2d&  f) const;
   const SbVec2d*  operator_assign(SoMFVec2d* theWrappedObject, const SbVec2d&  newValue);
   const SoMFVec2d*  operator_assign(SoMFVec2d* theWrappedObject, const SoMFVec2d&  f);
   bool  __eq__(SoMFVec2d* theWrappedObject, const SoMFVec2d&  f) const;
   const SbVec2d*  operator_subscript(SoMFVec2d* theWrappedObject, int  i) const;
   void set1Value(SoMFVec2d* theWrappedObject, int  index, const SbVec2d&  newValue);
   void set1Value(SoMFVec2d* theWrappedObject, int  index, double  x, double  y);
   void setValue(SoMFVec2d* theWrappedObject, const SbVec2d&  newValue);
   void setValue(SoMFVec2d* theWrappedObject, double  x, double  y);
   void setValues(SoMFVec2d* theWrappedObject, int  start, int  num, const SbVec2d*  newValues);
};





class PythonQtWrapper_SoMFVec2f : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFVec2f* new_SoMFVec2f();
void delete_SoMFVec2f(SoMFVec2f* obj) { delete obj; }
   void*  static_SoMFVec2f_createInstance();
   int  find(SoMFVec2f* theWrappedObject, const SbVec2f&  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFVec2f* theWrappedObject);
   SoType  static_SoMFVec2f_getClassTypeId();
   bool  __ne__(SoMFVec2f* theWrappedObject, const SoMFVec2f&  f) const;
   const SbVec2f*  operator_assign(SoMFVec2f* theWrappedObject, const SbVec2f&  newValue);
   const SoMFVec2f*  operator_assign(SoMFVec2f* theWrappedObject, const SoMFVec2f&  f);
   bool  __eq__(SoMFVec2f* theWrappedObject, const SoMFVec2f&  f) const;
   const SbVec2f*  operator_subscript(SoMFVec2f* theWrappedObject, int  i) const;
   void set1Value(SoMFVec2f* theWrappedObject, int  index, const SbVec2f&  newValue);
   void set1Value(SoMFVec2f* theWrappedObject, int  index, float  x, float  y);
   void setValue(SoMFVec2f* theWrappedObject, const SbVec2f&  newValue);
   void setValue(SoMFVec2f* theWrappedObject, float  x, float  y);
   void setValues(SoMFVec2f* theWrappedObject, int  start, int  num, const SbVec2f*  newValues);
};





class PythonQtWrapper_SoMFVec3d : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFVec3d* new_SoMFVec3d();
void delete_SoMFVec3d(SoMFVec3d* obj) { delete obj; }
   void*  static_SoMFVec3d_createInstance();
   int  find(SoMFVec3d* theWrappedObject, const SbVec3d&  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFVec3d* theWrappedObject);
   SoType  static_SoMFVec3d_getClassTypeId();
   bool  __ne__(SoMFVec3d* theWrappedObject, const SoMFVec3d&  f) const;
   const SbVec3d*  operator_assign(SoMFVec3d* theWrappedObject, const SbVec3d&  newValue);
   const SoMFVec3d*  operator_assign(SoMFVec3d* theWrappedObject, const SoMFVec3d&  f);
   bool  __eq__(SoMFVec3d* theWrappedObject, const SoMFVec3d&  f) const;
   const SbVec3d*  operator_subscript(SoMFVec3d* theWrappedObject, int  i) const;
   void set1Value(SoMFVec3d* theWrappedObject, int  index, const SbVec3d&  newValue);
   void set1Value(SoMFVec3d* theWrappedObject, int  index, double  x, double  y, double  z);
   void setValue(SoMFVec3d* theWrappedObject, const SbVec3d&  newValue);
   void setValue(SoMFVec3d* theWrappedObject, double  x, double  y, double  z);
   void setValues(SoMFVec3d* theWrappedObject, int  start, int  num, const SbVec3d*  newValues);
};





class PythonQtWrapper_SoMFVec3f : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFVec3f* new_SoMFVec3f();
void delete_SoMFVec3f(SoMFVec3f* obj) { delete obj; }
   void*  static_SoMFVec3f_createInstance();
   int  find(SoMFVec3f* theWrappedObject, const SbVec3f&  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFVec3f* theWrappedObject);
   SoType  static_SoMFVec3f_getClassTypeId();
   bool  __ne__(SoMFVec3f* theWrappedObject, const SoMFVec3f&  f) const;
   const SbVec3f*  operator_assign(SoMFVec3f* theWrappedObject, const SbVec3f&  newValue);
   const SoMFVec3f*  operator_assign(SoMFVec3f* theWrappedObject, const SoMFVec3f&  f);
   bool  __eq__(SoMFVec3f* theWrappedObject, const SoMFVec3f&  f) const;
   const SbVec3f*  operator_subscript(SoMFVec3f* theWrappedObject, int  i) const;
   void set1Value(SoMFVec3f* theWrappedObject, int  index, const SbVec3f&  newValue);
   void set1Value(SoMFVec3f* theWrappedObject, int  index, float  x, float  y, float  z);
   void setValue(SoMFVec3f* theWrappedObject, const SbVec3f&  newValue);
   void setValue(SoMFVec3f* theWrappedObject, float  x, float  y, float  z);
   void setValues(SoMFVec3f* theWrappedObject, int  start, int  num, const SbVec3f*  newValues);
};





class PythonQtWrapper_SoMFVec4d : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFVec4d* new_SoMFVec4d();
void delete_SoMFVec4d(SoMFVec4d* obj) { delete obj; }
   void*  static_SoMFVec4d_createInstance();
   int  find(SoMFVec4d* theWrappedObject, const SbVec4d&  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFVec4d* theWrappedObject);
   SoType  static_SoMFVec4d_getClassTypeId();
   bool  __ne__(SoMFVec4d* theWrappedObject, const SoMFVec4d&  f) const;
   const SbVec4d*  operator_assign(SoMFVec4d* theWrappedObject, const SbVec4d&  newValue);
   const SoMFVec4d*  operator_assign(SoMFVec4d* theWrappedObject, const SoMFVec4d&  f);
   bool  __eq__(SoMFVec4d* theWrappedObject, const SoMFVec4d&  f) const;
   const SbVec4d*  operator_subscript(SoMFVec4d* theWrappedObject, int  i) const;
   void set1Value(SoMFVec4d* theWrappedObject, int  index, const SbVec4d&  newValue);
   void set1Value(SoMFVec4d* theWrappedObject, int  index, double  x, double  y, double  z, double  w);
   void setValue(SoMFVec4d* theWrappedObject, const SbVec4d&  newValue);
   void setValue(SoMFVec4d* theWrappedObject, double  x, double  y, double  z, double  w);
   void setValues(SoMFVec4d* theWrappedObject, int  start, int  num, const SbVec4d*  newValues);
};





class PythonQtWrapper_SoMFVec4f : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMFVec4f* new_SoMFVec4f();
void delete_SoMFVec4f(SoMFVec4f* obj) { delete obj; }
   void*  static_SoMFVec4f_createInstance();
   int  find(SoMFVec4f* theWrappedObject, const SbVec4f&  targetValue, bool  addIfNotFound = 0);
   void finishEditing(SoMFVec4f* theWrappedObject);
   SoType  static_SoMFVec4f_getClassTypeId();
   bool  __ne__(SoMFVec4f* theWrappedObject, const SoMFVec4f&  f) const;
   const SbVec4f*  operator_assign(SoMFVec4f* theWrappedObject, const SbVec4f&  newValue);
   const SoMFVec4f*  operator_assign(SoMFVec4f* theWrappedObject, const SoMFVec4f&  f);
   bool  __eq__(SoMFVec4f* theWrappedObject, const SoMFVec4f&  f) const;
   const SbVec4f*  operator_subscript(SoMFVec4f* theWrappedObject, int  i) const;
   void set1Value(SoMFVec4f* theWrappedObject, int  index, const SbVec4f&  newValue);
   void set1Value(SoMFVec4f* theWrappedObject, int  index, float  x, float  y, float  z, float  w);
   void setValue(SoMFVec4f* theWrappedObject, const SbVec4f&  newValue);
   void setValue(SoMFVec4f* theWrappedObject, float  x, float  y, float  z, float  w);
   void setValues(SoMFVec4f* theWrappedObject, int  start, int  num, const SbVec4f*  newValues);
};


