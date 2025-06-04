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
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFDouble.h>
#include <Inventor/fields/SoSFEngine.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFImage.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFMatrixd.h>
#include <Inventor/fields/SoSFName.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFPath.h>
#include <Inventor/fields/SoSFPlane.h>
#include <Inventor/fields/SoSFPlaned.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/fields/SoSFRotationd.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoSFUInt32.h>
#include <Inventor/fields/SoSFUShort.h>
#include <Inventor/fields/SoSFVec2d.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFVec2s.h>
#include <Inventor/fields/SoSFVec3d.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/nodes/SoNode.h>
#include <stdexcept>



class PythonQtWrapper_SoMField : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
void delete_SoMField(SoMField* obj) { delete obj; }
   void*  static_SoMField_createInstance();
   void deleteValues(SoMField* theWrappedObject, int  start, int  num = -1);
   SoType  static_SoMField_getClassTypeId();
   int  getNum(SoMField* theWrappedObject) const;
   void insertSpace(SoMField* theWrappedObject, int  start, int  num);
   bool  set1(SoMField* theWrappedObject, int  index, const char*  valueString);
   void setNum(SoMField* theWrappedObject, int  num);
};





class PythonQtWrapper_SoSFBitMask : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFBitMask* new_SoSFBitMask();
void delete_SoSFBitMask(SoSFBitMask* obj) { delete obj; }
   void*  static_SoSFBitMask_createInstance();
   SoType  static_SoSFBitMask_getClassTypeId();
   const SoSFBitMask*  operator_assign(SoSFBitMask* theWrappedObject, const SoSFBitMask&  f);
   int  operator_assign(SoSFBitMask* theWrappedObject, int  newValue);
};





class PythonQtWrapper_SoSFBool : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFBool* new_SoSFBool();
void delete_SoSFBool(SoSFBool* obj) { delete obj; }
   void*  static_SoSFBool_createInstance();
   SoType  static_SoSFBool_getClassTypeId();
   bool  getValue(SoSFBool* theWrappedObject) const;
   bool  __ne__(SoSFBool* theWrappedObject, const SoSFBool&  f) const;
   bool  operator_assign(SoSFBool* theWrappedObject, bool  newValue);
   const SoSFBool*  operator_assign(SoSFBool* theWrappedObject, const SoSFBool&  f);
   bool  __eq__(SoSFBool* theWrappedObject, const SoSFBool&  f) const;
   void setValue(SoSFBool* theWrappedObject, bool  newValue);
};





class PythonQtWrapper_SoSFColor : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFColor* new_SoSFColor();
void delete_SoSFColor(SoSFColor* obj) { delete obj; }
   void*  static_SoSFColor_createInstance();
   SoType  static_SoSFColor_getClassTypeId();
   const SbColor*  getValue(SoSFColor* theWrappedObject) const;
   bool  __ne__(SoSFColor* theWrappedObject, const SoSFColor&  f) const;
   const SbColor*  operator_assign(SoSFColor* theWrappedObject, const SbColor&  newValue);
   const SoSFColor*  operator_assign(SoSFColor* theWrappedObject, const SoSFColor&  f);
   bool  __eq__(SoSFColor* theWrappedObject, const SoSFColor&  f) const;
   void setHSVValue(SoSFColor* theWrappedObject, float  h, float  s, float  v);
   void setValue(SoSFColor* theWrappedObject, const SbColor&  newValue);
   void setValue(SoSFColor* theWrappedObject, const SbVec3f&  vec);
   void setValue(SoSFColor* theWrappedObject, float  r, float  g, float  b);
};





class PythonQtWrapper_SoSFDouble : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFDouble* new_SoSFDouble();
void delete_SoSFDouble(SoSFDouble* obj) { delete obj; }
   void*  static_SoSFDouble_createInstance();
   SoType  static_SoSFDouble_getClassTypeId();
   double  getValue(SoSFDouble* theWrappedObject) const;
   bool  __ne__(SoSFDouble* theWrappedObject, const SoSFDouble&  f) const;
   const SoSFDouble*  operator_assign(SoSFDouble* theWrappedObject, const SoSFDouble&  f);
   double  operator_assign(SoSFDouble* theWrappedObject, double  newValue);
   bool  __eq__(SoSFDouble* theWrappedObject, const SoSFDouble&  f) const;
   void setValue(SoSFDouble* theWrappedObject, double  newValue);
};





class PythonQtWrapper_SoSFEngine : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFEngine* new_SoSFEngine();
void delete_SoSFEngine(SoSFEngine* obj) { delete obj; }
   void*  static_SoSFEngine_createInstance();
   SoType  static_SoSFEngine_getClassTypeId();
   SoEngine*  getValue(SoSFEngine* theWrappedObject) const;
   bool  __ne__(SoSFEngine* theWrappedObject, const SoSFEngine&  f) const;
   SoEngine*  operator_assign(SoSFEngine* theWrappedObject, SoEngine*  newValue);
   const SoSFEngine*  operator_assign(SoSFEngine* theWrappedObject, const SoSFEngine&  f);
   bool  __eq__(SoSFEngine* theWrappedObject, const SoSFEngine&  f) const;
   void setValue(SoSFEngine* theWrappedObject, SoEngine*  newValue);
};





class PythonQtWrapper_SoSFEnum : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFEnum* new_SoSFEnum();
void delete_SoSFEnum(SoSFEnum* obj) { delete obj; }
   void*  static_SoSFEnum_createInstance();
   SoType  static_SoSFEnum_getClassTypeId();
   int  getValue(SoSFEnum* theWrappedObject) const;
   bool  __ne__(SoSFEnum* theWrappedObject, const SoSFEnum&  f) const;
   const SoSFEnum*  operator_assign(SoSFEnum* theWrappedObject, const SoSFEnum&  f);
   int  operator_assign(SoSFEnum* theWrappedObject, int  newValue);
   bool  __eq__(SoSFEnum* theWrappedObject, const SoSFEnum&  f) const;
   void setEnums(SoSFEnum* theWrappedObject, int  num, int*  vals, SbName*  names);
   void setValue(SoSFEnum* theWrappedObject, const SbName&  name);
   void setValue(SoSFEnum* theWrappedObject, int  newValue);
};





class PythonQtWrapper_SoSFFloat : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFFloat* new_SoSFFloat();
void delete_SoSFFloat(SoSFFloat* obj) { delete obj; }
   void*  static_SoSFFloat_createInstance();
   SoType  static_SoSFFloat_getClassTypeId();
   float  getValue(SoSFFloat* theWrappedObject) const;
   bool  __ne__(SoSFFloat* theWrappedObject, const SoSFFloat&  f) const;
   const SoSFFloat*  operator_assign(SoSFFloat* theWrappedObject, const SoSFFloat&  f);
   float  operator_assign(SoSFFloat* theWrappedObject, float  newValue);
   bool  __eq__(SoSFFloat* theWrappedObject, const SoSFFloat&  f) const;
   void setValue(SoSFFloat* theWrappedObject, float  newValue);
};





class PythonQtWrapper_SoSFImage : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFImage* new_SoSFImage();
void delete_SoSFImage(SoSFImage* obj) { delete obj; }
   void*  static_SoSFImage_createInstance();
   void finishEditing(SoSFImage* theWrappedObject);
   SoType  static_SoSFImage_getClassTypeId();
   bool  __ne__(SoSFImage* theWrappedObject, const SoSFImage&  f) const;
   const SoSFImage*  operator_assign(SoSFImage* theWrappedObject, const SoSFImage&  f);
   bool  __eq__(SoSFImage* theWrappedObject, const SoSFImage&  f) const;
   void setValue(SoSFImage* theWrappedObject, const SbVec2s&  size, int  nc, const unsigned char*  bytes);
};





class PythonQtWrapper_SoSFInt32 : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFInt32* new_SoSFInt32();
void delete_SoSFInt32(SoSFInt32* obj) { delete obj; }
   void*  static_SoSFInt32_createInstance();
   SoType  static_SoSFInt32_getClassTypeId();
   int  getValue(SoSFInt32* theWrappedObject) const;
   bool  __ne__(SoSFInt32* theWrappedObject, const SoSFInt32&  f) const;
   const SoSFInt32*  operator_assign(SoSFInt32* theWrappedObject, const SoSFInt32&  f);
   int  operator_assign(SoSFInt32* theWrappedObject, int  newValue);
   bool  __eq__(SoSFInt32* theWrappedObject, const SoSFInt32&  f) const;
   void setValue(SoSFInt32* theWrappedObject, int  newValue);
};





class PythonQtWrapper_SoSFMatrix : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFMatrix* new_SoSFMatrix();
void delete_SoSFMatrix(SoSFMatrix* obj) { delete obj; }
   void*  static_SoSFMatrix_createInstance();
   SoType  static_SoSFMatrix_getClassTypeId();
   const SbMatrix*  getValue(SoSFMatrix* theWrappedObject) const;
   bool  __ne__(SoSFMatrix* theWrappedObject, const SoSFMatrix&  f) const;
   const SbMatrix*  operator_assign(SoSFMatrix* theWrappedObject, const SbMatrix&  newValue);
   const SoSFMatrix*  operator_assign(SoSFMatrix* theWrappedObject, const SoSFMatrix&  f);
   bool  __eq__(SoSFMatrix* theWrappedObject, const SoSFMatrix&  f) const;
   void setValue(SoSFMatrix* theWrappedObject, const SbMatrix&  newValue);
   void setValue(SoSFMatrix* theWrappedObject, float  a11, float  a12, float  a13, float  a14, float  a21, float  a22, float  a23, float  a24, float  a31, float  a32, float  a33, float  a34, float  a41, float  a42, float  a43, float  a44);
};





class PythonQtWrapper_SoSFMatrixd : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFMatrixd* new_SoSFMatrixd();
void delete_SoSFMatrixd(SoSFMatrixd* obj) { delete obj; }
   void*  static_SoSFMatrixd_createInstance();
   SoType  static_SoSFMatrixd_getClassTypeId();
   const SbMatrixd*  getValue(SoSFMatrixd* theWrappedObject) const;
   bool  __ne__(SoSFMatrixd* theWrappedObject, const SoSFMatrixd&  f) const;
   const SbMatrixd*  operator_assign(SoSFMatrixd* theWrappedObject, const SbMatrixd&  newValue);
   const SoSFMatrixd*  operator_assign(SoSFMatrixd* theWrappedObject, const SoSFMatrixd&  f);
   bool  __eq__(SoSFMatrixd* theWrappedObject, const SoSFMatrixd&  f) const;
   void setValue(SoSFMatrixd* theWrappedObject, const SbMatrixd&  newValue);
   void setValue(SoSFMatrixd* theWrappedObject, double  a11, double  a12, double  a13, double  a14, double  a21, double  a22, double  a23, double  a24, double  a31, double  a32, double  a33, double  a34, double  a41, double  a42, double  a43, double  a44);
};





class PythonQtWrapper_SoSFName : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFName* new_SoSFName();
void delete_SoSFName(SoSFName* obj) { delete obj; }
   void*  static_SoSFName_createInstance();
   SoType  static_SoSFName_getClassTypeId();
   const SbName*  getValue(SoSFName* theWrappedObject) const;
   bool  __ne__(SoSFName* theWrappedObject, const SoSFName&  f) const;
   const SbName*  operator_assign(SoSFName* theWrappedObject, const SbName&  newValue);
   const SoSFName*  operator_assign(SoSFName* theWrappedObject, const SoSFName&  f);
   bool  __eq__(SoSFName* theWrappedObject, const SoSFName&  f) const;
   void setValue(SoSFName* theWrappedObject, const SbName&  newValue);
   void setValue(SoSFName* theWrappedObject, const char*  string);
};





class PythonQtWrapper_SoSFNode : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFNode* new_SoSFNode();
void delete_SoSFNode(SoSFNode* obj) { delete obj; }
   void*  static_SoSFNode_createInstance();
   SoType  static_SoSFNode_getClassTypeId();
   SoNode*  getValue(SoSFNode* theWrappedObject) const;
   bool  __ne__(SoSFNode* theWrappedObject, const SoSFNode&  f) const;
   SoNode*  operator_assign(SoSFNode* theWrappedObject, SoNode*  newValue);
   const SoSFNode*  operator_assign(SoSFNode* theWrappedObject, const SoSFNode&  f);
   bool  __eq__(SoSFNode* theWrappedObject, const SoSFNode&  f) const;
   void setValue(SoSFNode* theWrappedObject, SoNode*  newValue);
};





class PythonQtWrapper_SoSFPath : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFPath* new_SoSFPath();
void delete_SoSFPath(SoSFPath* obj) { delete obj; }
   void*  static_SoSFPath_createInstance();
   SoType  static_SoSFPath_getClassTypeId();
   SoPath*  getValue(SoSFPath* theWrappedObject) const;
   bool  __ne__(SoSFPath* theWrappedObject, const SoSFPath&  f) const;
   SoPath*  operator_assign(SoSFPath* theWrappedObject, SoPath*  newValue);
   const SoSFPath*  operator_assign(SoSFPath* theWrappedObject, const SoSFPath&  f);
   bool  __eq__(SoSFPath* theWrappedObject, const SoSFPath&  f) const;
   void setValue(SoSFPath* theWrappedObject, SoPath*  newValue);
};





class PythonQtWrapper_SoSFPlane : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFPlane* new_SoSFPlane();
void delete_SoSFPlane(SoSFPlane* obj) { delete obj; }
   void*  static_SoSFPlane_createInstance();
   SoType  static_SoSFPlane_getClassTypeId();
   const SbPlane*  getValue(SoSFPlane* theWrappedObject) const;
   bool  __ne__(SoSFPlane* theWrappedObject, const SoSFPlane&  f) const;
   const SbPlane*  operator_assign(SoSFPlane* theWrappedObject, const SbPlane&  newValue);
   const SoSFPlane*  operator_assign(SoSFPlane* theWrappedObject, const SoSFPlane&  f);
   bool  __eq__(SoSFPlane* theWrappedObject, const SoSFPlane&  f) const;
   void setValue(SoSFPlane* theWrappedObject, const SbPlane&  newValue);
};





class PythonQtWrapper_SoSFPlaned : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFPlaned* new_SoSFPlaned();
void delete_SoSFPlaned(SoSFPlaned* obj) { delete obj; }
   void*  static_SoSFPlaned_createInstance();
   SoType  static_SoSFPlaned_getClassTypeId();
   const SbPlaned*  getValue(SoSFPlaned* theWrappedObject) const;
   bool  __ne__(SoSFPlaned* theWrappedObject, const SoSFPlaned&  f) const;
   const SbPlaned*  operator_assign(SoSFPlaned* theWrappedObject, const SbPlaned&  newValue);
   const SoSFPlaned*  operator_assign(SoSFPlaned* theWrappedObject, const SoSFPlaned&  f);
   bool  __eq__(SoSFPlaned* theWrappedObject, const SoSFPlaned&  f) const;
   void setValue(SoSFPlaned* theWrappedObject, const SbPlaned&  newValue);
};





class PythonQtWrapper_SoSFRotation : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFRotation* new_SoSFRotation();
void delete_SoSFRotation(SoSFRotation* obj) { delete obj; }
   void*  static_SoSFRotation_createInstance();
   SoType  static_SoSFRotation_getClassTypeId();
   const SbRotation*  getValue(SoSFRotation* theWrappedObject) const;
   bool  __ne__(SoSFRotation* theWrappedObject, const SoSFRotation&  f) const;
   const SbRotation*  operator_assign(SoSFRotation* theWrappedObject, const SbRotation&  newValue);
   const SoSFRotation*  operator_assign(SoSFRotation* theWrappedObject, const SoSFRotation&  f);
   bool  __eq__(SoSFRotation* theWrappedObject, const SoSFRotation&  f) const;
   void setValue(SoSFRotation* theWrappedObject, const SbRotation&  newValue);
   void setValue(SoSFRotation* theWrappedObject, const SbVec3f&  axis, float  angle);
   void setValue(SoSFRotation* theWrappedObject, float  q0, float  q1, float  q2, float  q3);
};





class PythonQtWrapper_SoSFRotationd : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFRotationd* new_SoSFRotationd();
void delete_SoSFRotationd(SoSFRotationd* obj) { delete obj; }
   void*  static_SoSFRotationd_createInstance();
   SoType  static_SoSFRotationd_getClassTypeId();
   const SbRotationd*  getValue(SoSFRotationd* theWrappedObject) const;
   bool  __ne__(SoSFRotationd* theWrappedObject, const SoSFRotationd&  f) const;
   const SbRotationd*  operator_assign(SoSFRotationd* theWrappedObject, const SbRotationd&  newValue);
   const SoSFRotationd*  operator_assign(SoSFRotationd* theWrappedObject, const SoSFRotationd&  f);
   bool  __eq__(SoSFRotationd* theWrappedObject, const SoSFRotationd&  f) const;
   void setValue(SoSFRotationd* theWrappedObject, const SbRotationd&  newValue);
   void setValue(SoSFRotationd* theWrappedObject, const SbVec3d&  axis, double  angle);
   void setValue(SoSFRotationd* theWrappedObject, double  q0, double  q1, double  q2, double  q3);
};





class PythonQtWrapper_SoSFShort : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFShort* new_SoSFShort();
void delete_SoSFShort(SoSFShort* obj) { delete obj; }
   void*  static_SoSFShort_createInstance();
   SoType  static_SoSFShort_getClassTypeId();
   short  getValue(SoSFShort* theWrappedObject) const;
   bool  __ne__(SoSFShort* theWrappedObject, const SoSFShort&  f) const;
   const SoSFShort*  operator_assign(SoSFShort* theWrappedObject, const SoSFShort&  f);
   short  operator_assign(SoSFShort* theWrappedObject, short  newValue);
   bool  __eq__(SoSFShort* theWrappedObject, const SoSFShort&  f) const;
   void setValue(SoSFShort* theWrappedObject, short  newValue);
};





class PythonQtWrapper_SoSFString : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFString* new_SoSFString();
void delete_SoSFString(SoSFString* obj) { delete obj; }
   void*  static_SoSFString_createInstance();
   SoType  static_SoSFString_getClassTypeId();
   const SbString*  getValue(SoSFString* theWrappedObject) const;
   bool  __ne__(SoSFString* theWrappedObject, const SoSFString&  f) const;
   const SbString*  operator_assign(SoSFString* theWrappedObject, const SbString&  newValue);
   const SoSFString*  operator_assign(SoSFString* theWrappedObject, const SoSFString&  f);
   bool  __eq__(SoSFString* theWrappedObject, const SoSFString&  f) const;
   void setValue(SoSFString* theWrappedObject, const SbString&  newValue);
   void setValue(SoSFString* theWrappedObject, const char*  string);
};





class PythonQtWrapper_SoSFTime : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFTime* new_SoSFTime();
void delete_SoSFTime(SoSFTime* obj) { delete obj; }
   void*  static_SoSFTime_createInstance();
   SoType  static_SoSFTime_getClassTypeId();
   const SbTime*  getValue(SoSFTime* theWrappedObject) const;
   bool  __ne__(SoSFTime* theWrappedObject, const SoSFTime&  f) const;
   const SbTime*  operator_assign(SoSFTime* theWrappedObject, const SbTime&  newValue);
   const SoSFTime*  operator_assign(SoSFTime* theWrappedObject, const SoSFTime&  f);
   bool  __eq__(SoSFTime* theWrappedObject, const SoSFTime&  f) const;
   void setValue(SoSFTime* theWrappedObject, const SbTime&  newValue);
};





class PythonQtWrapper_SoSFTrigger : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFTrigger* new_SoSFTrigger();
void delete_SoSFTrigger(SoSFTrigger* obj) { delete obj; }
   void*  static_SoSFTrigger_createInstance();
   SoType  static_SoSFTrigger_getClassTypeId();
   void getValue(SoSFTrigger* theWrappedObject) const;
   bool  __ne__(SoSFTrigger* theWrappedObject, const SoSFTrigger&  t) const;
   const SoSFTrigger*  operator_assign(SoSFTrigger* theWrappedObject, const SoSFTrigger&  f);
   bool  __eq__(SoSFTrigger* theWrappedObject, const SoSFTrigger&  t) const;
   void setValue(SoSFTrigger* theWrappedObject);
};





class PythonQtWrapper_SoSFUInt32 : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFUInt32* new_SoSFUInt32();
void delete_SoSFUInt32(SoSFUInt32* obj) { delete obj; }
   void*  static_SoSFUInt32_createInstance();
   SoType  static_SoSFUInt32_getClassTypeId();
   unsigned int  getValue(SoSFUInt32* theWrappedObject) const;
   bool  __ne__(SoSFUInt32* theWrappedObject, const SoSFUInt32&  f) const;
   const SoSFUInt32*  operator_assign(SoSFUInt32* theWrappedObject, const SoSFUInt32&  f);
   unsigned int  operator_assign(SoSFUInt32* theWrappedObject, unsigned int  newValue);
   bool  __eq__(SoSFUInt32* theWrappedObject, const SoSFUInt32&  f) const;
   void setValue(SoSFUInt32* theWrappedObject, unsigned int  newValue);
};





class PythonQtWrapper_SoSFUShort : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFUShort* new_SoSFUShort();
void delete_SoSFUShort(SoSFUShort* obj) { delete obj; }
   void*  static_SoSFUShort_createInstance();
   SoType  static_SoSFUShort_getClassTypeId();
   unsigned short  getValue(SoSFUShort* theWrappedObject) const;
   bool  __ne__(SoSFUShort* theWrappedObject, const SoSFUShort&  f) const;
   const SoSFUShort*  operator_assign(SoSFUShort* theWrappedObject, const SoSFUShort&  f);
   unsigned short  operator_assign(SoSFUShort* theWrappedObject, unsigned short  newValue);
   bool  __eq__(SoSFUShort* theWrappedObject, const SoSFUShort&  f) const;
   void setValue(SoSFUShort* theWrappedObject, unsigned short  newValue);
};





class PythonQtWrapper_SoSFVec2d : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFVec2d* new_SoSFVec2d();
void delete_SoSFVec2d(SoSFVec2d* obj) { delete obj; }
   void*  static_SoSFVec2d_createInstance();
   SoType  static_SoSFVec2d_getClassTypeId();
   const SbVec2d*  getValue(SoSFVec2d* theWrappedObject) const;
   bool  __ne__(SoSFVec2d* theWrappedObject, const SoSFVec2d&  f) const;
   const SbVec2d*  operator_assign(SoSFVec2d* theWrappedObject, const SbVec2d&  newValue);
   const SoSFVec2d*  operator_assign(SoSFVec2d* theWrappedObject, const SoSFVec2d&  f);
   bool  __eq__(SoSFVec2d* theWrappedObject, const SoSFVec2d&  f) const;
   void setValue(SoSFVec2d* theWrappedObject, const SbVec2d&  newValue);
   void setValue(SoSFVec2d* theWrappedObject, double  x, double  y);
};





class PythonQtWrapper_SoSFVec2f : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFVec2f* new_SoSFVec2f();
void delete_SoSFVec2f(SoSFVec2f* obj) { delete obj; }
   void*  static_SoSFVec2f_createInstance();
   SoType  static_SoSFVec2f_getClassTypeId();
   const SbVec2f*  getValue(SoSFVec2f* theWrappedObject) const;
   bool  __ne__(SoSFVec2f* theWrappedObject, const SoSFVec2f&  f) const;
   const SbVec2f*  operator_assign(SoSFVec2f* theWrappedObject, const SbVec2f&  newValue);
   const SoSFVec2f*  operator_assign(SoSFVec2f* theWrappedObject, const SoSFVec2f&  f);
   bool  __eq__(SoSFVec2f* theWrappedObject, const SoSFVec2f&  f) const;
   void setValue(SoSFVec2f* theWrappedObject, const SbVec2f&  newValue);
   void setValue(SoSFVec2f* theWrappedObject, float  x, float  y);
};





class PythonQtWrapper_SoSFVec2s : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFVec2s* new_SoSFVec2s();
void delete_SoSFVec2s(SoSFVec2s* obj) { delete obj; }
   void*  static_SoSFVec2s_createInstance();
   SoType  static_SoSFVec2s_getClassTypeId();
   const SbVec2s*  getValue(SoSFVec2s* theWrappedObject) const;
   bool  __ne__(SoSFVec2s* theWrappedObject, const SoSFVec2s&  f) const;
   const SbVec2s*  operator_assign(SoSFVec2s* theWrappedObject, const SbVec2s&  newValue);
   const SoSFVec2s*  operator_assign(SoSFVec2s* theWrappedObject, const SoSFVec2s&  f);
   bool  __eq__(SoSFVec2s* theWrappedObject, const SoSFVec2s&  f) const;
   void setValue(SoSFVec2s* theWrappedObject, const SbVec2s&  newValue);
   void setValue(SoSFVec2s* theWrappedObject, short  x, short  y);
};





class PythonQtWrapper_SoSFVec3d : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFVec3d* new_SoSFVec3d();
void delete_SoSFVec3d(SoSFVec3d* obj) { delete obj; }
   void*  static_SoSFVec3d_createInstance();
   SoType  static_SoSFVec3d_getClassTypeId();
   const SbVec3d*  getValue(SoSFVec3d* theWrappedObject) const;
   bool  __ne__(SoSFVec3d* theWrappedObject, const SoSFVec3d&  f) const;
   const SbVec3d*  operator_assign(SoSFVec3d* theWrappedObject, const SbVec3d&  newValue);
   const SoSFVec3d*  operator_assign(SoSFVec3d* theWrappedObject, const SoSFVec3d&  f);
   bool  __eq__(SoSFVec3d* theWrappedObject, const SoSFVec3d&  f) const;
   void setValue(SoSFVec3d* theWrappedObject, const SbVec3d&  newValue);
   void setValue(SoSFVec3d* theWrappedObject, double  x, double  y, double  z);
};





class PythonQtWrapper_SoSFVec3f : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFVec3f* new_SoSFVec3f();
void delete_SoSFVec3f(SoSFVec3f* obj) { delete obj; }
   void*  static_SoSFVec3f_createInstance();
   SoType  static_SoSFVec3f_getClassTypeId();
   const SbVec3f*  getValue(SoSFVec3f* theWrappedObject) const;
   bool  __ne__(SoSFVec3f* theWrappedObject, const SoSFVec3f&  f) const;
   const SbVec3f*  operator_assign(SoSFVec3f* theWrappedObject, const SbVec3f&  newValue);
   const SoSFVec3f*  operator_assign(SoSFVec3f* theWrappedObject, const SoSFVec3f&  f);
   bool  __eq__(SoSFVec3f* theWrappedObject, const SoSFVec3f&  f) const;
   void setValue(SoSFVec3f* theWrappedObject, const SbVec3f&  newValue);
   void setValue(SoSFVec3f* theWrappedObject, float  x, float  y, float  z);
};


