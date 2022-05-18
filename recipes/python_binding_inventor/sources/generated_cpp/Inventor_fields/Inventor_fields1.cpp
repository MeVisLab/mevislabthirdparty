/*************************************************************************************
**
** Copyright 2022, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/
#include "Inventor_fields1.h"
#include <PythonQtConversion.h>
#include <PythonQtMethodInfo.h>
#include <PythonQtSignalReceiver.h>
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

void*  PythonQtWrapper_SoMField::static_SoMField_createInstance()
{
  return (SoMField::createInstance());
}

void PythonQtWrapper_SoMField::deleteValues(SoMField* theWrappedObject, int  start, int  num)
{
  ( theWrappedObject->deleteValues(start, num));
}

SoType  PythonQtWrapper_SoMField::static_SoMField_getClassTypeId()
{
  return (SoMField::getClassTypeId());
}

int  PythonQtWrapper_SoMField::getNum(SoMField* theWrappedObject) const
{
  return ( theWrappedObject->getNum());
}

void PythonQtWrapper_SoMField::insertSpace(SoMField* theWrappedObject, int  start, int  num)
{
  ( theWrappedObject->insertSpace(start, num));
}

bool  PythonQtWrapper_SoMField::set1(SoMField* theWrappedObject, int  index, const char*  valueString)
{
  return ( theWrappedObject->set1(index, valueString));
}

void PythonQtWrapper_SoMField::setNum(SoMField* theWrappedObject, int  num)
{
  ( theWrappedObject->setNum(num));
}



SoSFBitMask* PythonQtWrapper_SoSFBitMask::new_SoSFBitMask()
{ 
return new SoSFBitMask(); }

void*  PythonQtWrapper_SoSFBitMask::static_SoSFBitMask_createInstance()
{
  return (SoSFBitMask::createInstance());
}

SoType  PythonQtWrapper_SoSFBitMask::static_SoSFBitMask_getClassTypeId()
{
  return (SoSFBitMask::getClassTypeId());
}

const SoSFBitMask*  PythonQtWrapper_SoSFBitMask::operator_assign(SoSFBitMask* theWrappedObject, const SoSFBitMask&  f)
{
  return &( (*theWrappedObject)= f);
}

int  PythonQtWrapper_SoSFBitMask::operator_assign(SoSFBitMask* theWrappedObject, int  newValue)
{
  return ( (*theWrappedObject)= newValue);
}



SoSFBool* PythonQtWrapper_SoSFBool::new_SoSFBool()
{ 
return new SoSFBool(); }

void*  PythonQtWrapper_SoSFBool::static_SoSFBool_createInstance()
{
  return (SoSFBool::createInstance());
}

SoType  PythonQtWrapper_SoSFBool::static_SoSFBool_getClassTypeId()
{
  return (SoSFBool::getClassTypeId());
}

bool  PythonQtWrapper_SoSFBool::getValue(SoSFBool* theWrappedObject) const
{
  return ( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFBool::__ne__(SoSFBool* theWrappedObject, const SoSFBool&  f) const
{
  return ( (*theWrappedObject)!= f);
}

bool  PythonQtWrapper_SoSFBool::operator_assign(SoSFBool* theWrappedObject, bool  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

const SoSFBool*  PythonQtWrapper_SoSFBool::operator_assign(SoSFBool* theWrappedObject, const SoSFBool&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFBool::__eq__(SoSFBool* theWrappedObject, const SoSFBool&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFBool::setValue(SoSFBool* theWrappedObject, bool  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFColor* PythonQtWrapper_SoSFColor::new_SoSFColor()
{ 
return new SoSFColor(); }

void*  PythonQtWrapper_SoSFColor::static_SoSFColor_createInstance()
{
  return (SoSFColor::createInstance());
}

SoType  PythonQtWrapper_SoSFColor::static_SoSFColor_getClassTypeId()
{
  return (SoSFColor::getClassTypeId());
}

const SbColor*  PythonQtWrapper_SoSFColor::getValue(SoSFColor* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFColor::__ne__(SoSFColor* theWrappedObject, const SoSFColor&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbColor*  PythonQtWrapper_SoSFColor::operator_assign(SoSFColor* theWrappedObject, const SbColor&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFColor*  PythonQtWrapper_SoSFColor::operator_assign(SoSFColor* theWrappedObject, const SoSFColor&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFColor::__eq__(SoSFColor* theWrappedObject, const SoSFColor&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFColor::setHSVValue(SoSFColor* theWrappedObject, float  h, float  s, float  v)
{
  ( theWrappedObject->setHSVValue(h, s, v));
}

void PythonQtWrapper_SoSFColor::setValue(SoSFColor* theWrappedObject, const SbColor&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFColor::setValue(SoSFColor* theWrappedObject, const SbVec3f&  vec)
{
  ( theWrappedObject->setValue(vec));
}

void PythonQtWrapper_SoSFColor::setValue(SoSFColor* theWrappedObject, float  r, float  g, float  b)
{
  ( theWrappedObject->setValue(r, g, b));
}



SoSFDouble* PythonQtWrapper_SoSFDouble::new_SoSFDouble()
{ 
return new SoSFDouble(); }

void*  PythonQtWrapper_SoSFDouble::static_SoSFDouble_createInstance()
{
  return (SoSFDouble::createInstance());
}

SoType  PythonQtWrapper_SoSFDouble::static_SoSFDouble_getClassTypeId()
{
  return (SoSFDouble::getClassTypeId());
}

double  PythonQtWrapper_SoSFDouble::getValue(SoSFDouble* theWrappedObject) const
{
  return ( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFDouble::__ne__(SoSFDouble* theWrappedObject, const SoSFDouble&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SoSFDouble*  PythonQtWrapper_SoSFDouble::operator_assign(SoSFDouble* theWrappedObject, const SoSFDouble&  f)
{
  return &( (*theWrappedObject)= f);
}

double  PythonQtWrapper_SoSFDouble::operator_assign(SoSFDouble* theWrappedObject, double  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

bool  PythonQtWrapper_SoSFDouble::__eq__(SoSFDouble* theWrappedObject, const SoSFDouble&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFDouble::setValue(SoSFDouble* theWrappedObject, double  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFEngine* PythonQtWrapper_SoSFEngine::new_SoSFEngine()
{ 
return new SoSFEngine(); }

void*  PythonQtWrapper_SoSFEngine::static_SoSFEngine_createInstance()
{
  return (SoSFEngine::createInstance());
}

SoType  PythonQtWrapper_SoSFEngine::static_SoSFEngine_getClassTypeId()
{
  return (SoSFEngine::getClassTypeId());
}

SoEngine*  PythonQtWrapper_SoSFEngine::getValue(SoSFEngine* theWrappedObject) const
{
  return ( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFEngine::__ne__(SoSFEngine* theWrappedObject, const SoSFEngine&  f) const
{
  return ( (*theWrappedObject)!= f);
}

SoEngine*  PythonQtWrapper_SoSFEngine::operator_assign(SoSFEngine* theWrappedObject, SoEngine*  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

const SoSFEngine*  PythonQtWrapper_SoSFEngine::operator_assign(SoSFEngine* theWrappedObject, const SoSFEngine&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFEngine::__eq__(SoSFEngine* theWrappedObject, const SoSFEngine&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFEngine::setValue(SoSFEngine* theWrappedObject, SoEngine*  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFEnum* PythonQtWrapper_SoSFEnum::new_SoSFEnum()
{ 
return new SoSFEnum(); }

void*  PythonQtWrapper_SoSFEnum::static_SoSFEnum_createInstance()
{
  return (SoSFEnum::createInstance());
}

SoType  PythonQtWrapper_SoSFEnum::static_SoSFEnum_getClassTypeId()
{
  return (SoSFEnum::getClassTypeId());
}

int  PythonQtWrapper_SoSFEnum::getValue(SoSFEnum* theWrappedObject) const
{
  return ( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFEnum::__ne__(SoSFEnum* theWrappedObject, const SoSFEnum&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SoSFEnum*  PythonQtWrapper_SoSFEnum::operator_assign(SoSFEnum* theWrappedObject, const SoSFEnum&  f)
{
  return &( (*theWrappedObject)= f);
}

int  PythonQtWrapper_SoSFEnum::operator_assign(SoSFEnum* theWrappedObject, int  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

bool  PythonQtWrapper_SoSFEnum::__eq__(SoSFEnum* theWrappedObject, const SoSFEnum&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFEnum::setEnums(SoSFEnum* theWrappedObject, int  num, int*  vals, SbName*  names)
{
  ( theWrappedObject->setEnums(num, vals, names));
}

void PythonQtWrapper_SoSFEnum::setValue(SoSFEnum* theWrappedObject, const SbName&  name)
{
  ( theWrappedObject->setValue(name));
}

void PythonQtWrapper_SoSFEnum::setValue(SoSFEnum* theWrappedObject, int  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFFloat* PythonQtWrapper_SoSFFloat::new_SoSFFloat()
{ 
return new SoSFFloat(); }

void*  PythonQtWrapper_SoSFFloat::static_SoSFFloat_createInstance()
{
  return (SoSFFloat::createInstance());
}

SoType  PythonQtWrapper_SoSFFloat::static_SoSFFloat_getClassTypeId()
{
  return (SoSFFloat::getClassTypeId());
}

float  PythonQtWrapper_SoSFFloat::getValue(SoSFFloat* theWrappedObject) const
{
  return ( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFFloat::__ne__(SoSFFloat* theWrappedObject, const SoSFFloat&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SoSFFloat*  PythonQtWrapper_SoSFFloat::operator_assign(SoSFFloat* theWrappedObject, const SoSFFloat&  f)
{
  return &( (*theWrappedObject)= f);
}

float  PythonQtWrapper_SoSFFloat::operator_assign(SoSFFloat* theWrappedObject, float  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

bool  PythonQtWrapper_SoSFFloat::__eq__(SoSFFloat* theWrappedObject, const SoSFFloat&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFFloat::setValue(SoSFFloat* theWrappedObject, float  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFImage* PythonQtWrapper_SoSFImage::new_SoSFImage()
{ 
return new SoSFImage(); }

void*  PythonQtWrapper_SoSFImage::static_SoSFImage_createInstance()
{
  return (SoSFImage::createInstance());
}

void PythonQtWrapper_SoSFImage::finishEditing(SoSFImage* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoSFImage::static_SoSFImage_getClassTypeId()
{
  return (SoSFImage::getClassTypeId());
}

bool  PythonQtWrapper_SoSFImage::__ne__(SoSFImage* theWrappedObject, const SoSFImage&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SoSFImage*  PythonQtWrapper_SoSFImage::operator_assign(SoSFImage* theWrappedObject, const SoSFImage&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFImage::__eq__(SoSFImage* theWrappedObject, const SoSFImage&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFImage::setValue(SoSFImage* theWrappedObject, const SbVec2s&  size, int  nc, const unsigned char*  bytes)
{
  ( theWrappedObject->setValue(size, nc, bytes));
}



SoSFInt32* PythonQtWrapper_SoSFInt32::new_SoSFInt32()
{ 
return new SoSFInt32(); }

void*  PythonQtWrapper_SoSFInt32::static_SoSFInt32_createInstance()
{
  return (SoSFInt32::createInstance());
}

SoType  PythonQtWrapper_SoSFInt32::static_SoSFInt32_getClassTypeId()
{
  return (SoSFInt32::getClassTypeId());
}

int  PythonQtWrapper_SoSFInt32::getValue(SoSFInt32* theWrappedObject) const
{
  return ( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFInt32::__ne__(SoSFInt32* theWrappedObject, const SoSFInt32&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SoSFInt32*  PythonQtWrapper_SoSFInt32::operator_assign(SoSFInt32* theWrappedObject, const SoSFInt32&  f)
{
  return &( (*theWrappedObject)= f);
}

int  PythonQtWrapper_SoSFInt32::operator_assign(SoSFInt32* theWrappedObject, int  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

bool  PythonQtWrapper_SoSFInt32::__eq__(SoSFInt32* theWrappedObject, const SoSFInt32&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFInt32::setValue(SoSFInt32* theWrappedObject, int  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFMatrix* PythonQtWrapper_SoSFMatrix::new_SoSFMatrix()
{ 
return new SoSFMatrix(); }

void*  PythonQtWrapper_SoSFMatrix::static_SoSFMatrix_createInstance()
{
  return (SoSFMatrix::createInstance());
}

SoType  PythonQtWrapper_SoSFMatrix::static_SoSFMatrix_getClassTypeId()
{
  return (SoSFMatrix::getClassTypeId());
}

const SbMatrix*  PythonQtWrapper_SoSFMatrix::getValue(SoSFMatrix* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFMatrix::__ne__(SoSFMatrix* theWrappedObject, const SoSFMatrix&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbMatrix*  PythonQtWrapper_SoSFMatrix::operator_assign(SoSFMatrix* theWrappedObject, const SbMatrix&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFMatrix*  PythonQtWrapper_SoSFMatrix::operator_assign(SoSFMatrix* theWrappedObject, const SoSFMatrix&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFMatrix::__eq__(SoSFMatrix* theWrappedObject, const SoSFMatrix&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFMatrix::setValue(SoSFMatrix* theWrappedObject, const SbMatrix&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFMatrix::setValue(SoSFMatrix* theWrappedObject, float  a11, float  a12, float  a13, float  a14, float  a21, float  a22, float  a23, float  a24, float  a31, float  a32, float  a33, float  a34, float  a41, float  a42, float  a43, float  a44)
{
  ( theWrappedObject->setValue(a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44));
}



SoSFMatrixd* PythonQtWrapper_SoSFMatrixd::new_SoSFMatrixd()
{ 
return new SoSFMatrixd(); }

void*  PythonQtWrapper_SoSFMatrixd::static_SoSFMatrixd_createInstance()
{
  return (SoSFMatrixd::createInstance());
}

SoType  PythonQtWrapper_SoSFMatrixd::static_SoSFMatrixd_getClassTypeId()
{
  return (SoSFMatrixd::getClassTypeId());
}

const SbMatrixd*  PythonQtWrapper_SoSFMatrixd::getValue(SoSFMatrixd* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFMatrixd::__ne__(SoSFMatrixd* theWrappedObject, const SoSFMatrixd&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbMatrixd*  PythonQtWrapper_SoSFMatrixd::operator_assign(SoSFMatrixd* theWrappedObject, const SbMatrixd&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFMatrixd*  PythonQtWrapper_SoSFMatrixd::operator_assign(SoSFMatrixd* theWrappedObject, const SoSFMatrixd&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFMatrixd::__eq__(SoSFMatrixd* theWrappedObject, const SoSFMatrixd&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFMatrixd::setValue(SoSFMatrixd* theWrappedObject, const SbMatrixd&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFMatrixd::setValue(SoSFMatrixd* theWrappedObject, double  a11, double  a12, double  a13, double  a14, double  a21, double  a22, double  a23, double  a24, double  a31, double  a32, double  a33, double  a34, double  a41, double  a42, double  a43, double  a44)
{
  ( theWrappedObject->setValue(a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44));
}



SoSFName* PythonQtWrapper_SoSFName::new_SoSFName()
{ 
return new SoSFName(); }

void*  PythonQtWrapper_SoSFName::static_SoSFName_createInstance()
{
  return (SoSFName::createInstance());
}

SoType  PythonQtWrapper_SoSFName::static_SoSFName_getClassTypeId()
{
  return (SoSFName::getClassTypeId());
}

const SbName*  PythonQtWrapper_SoSFName::getValue(SoSFName* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFName::__ne__(SoSFName* theWrappedObject, const SoSFName&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbName*  PythonQtWrapper_SoSFName::operator_assign(SoSFName* theWrappedObject, const SbName&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFName*  PythonQtWrapper_SoSFName::operator_assign(SoSFName* theWrappedObject, const SoSFName&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFName::__eq__(SoSFName* theWrappedObject, const SoSFName&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFName::setValue(SoSFName* theWrappedObject, const SbName&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFName::setValue(SoSFName* theWrappedObject, const char*  string)
{
  ( theWrappedObject->setValue(string));
}



SoSFNode* PythonQtWrapper_SoSFNode::new_SoSFNode()
{ 
return new SoSFNode(); }

void*  PythonQtWrapper_SoSFNode::static_SoSFNode_createInstance()
{
  return (SoSFNode::createInstance());
}

SoType  PythonQtWrapper_SoSFNode::static_SoSFNode_getClassTypeId()
{
  return (SoSFNode::getClassTypeId());
}

SoNode*  PythonQtWrapper_SoSFNode::getValue(SoSFNode* theWrappedObject) const
{
  return ( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFNode::__ne__(SoSFNode* theWrappedObject, const SoSFNode&  f) const
{
  return ( (*theWrappedObject)!= f);
}

SoNode*  PythonQtWrapper_SoSFNode::operator_assign(SoSFNode* theWrappedObject, SoNode*  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

const SoSFNode*  PythonQtWrapper_SoSFNode::operator_assign(SoSFNode* theWrappedObject, const SoSFNode&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFNode::__eq__(SoSFNode* theWrappedObject, const SoSFNode&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFNode::setValue(SoSFNode* theWrappedObject, SoNode*  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFPath* PythonQtWrapper_SoSFPath::new_SoSFPath()
{ 
return new SoSFPath(); }

void*  PythonQtWrapper_SoSFPath::static_SoSFPath_createInstance()
{
  return (SoSFPath::createInstance());
}

SoType  PythonQtWrapper_SoSFPath::static_SoSFPath_getClassTypeId()
{
  return (SoSFPath::getClassTypeId());
}

SoPath*  PythonQtWrapper_SoSFPath::getValue(SoSFPath* theWrappedObject) const
{
  return ( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFPath::__ne__(SoSFPath* theWrappedObject, const SoSFPath&  f) const
{
  return ( (*theWrappedObject)!= f);
}

SoPath*  PythonQtWrapper_SoSFPath::operator_assign(SoSFPath* theWrappedObject, SoPath*  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

const SoSFPath*  PythonQtWrapper_SoSFPath::operator_assign(SoSFPath* theWrappedObject, const SoSFPath&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFPath::__eq__(SoSFPath* theWrappedObject, const SoSFPath&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFPath::setValue(SoSFPath* theWrappedObject, SoPath*  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFPlane* PythonQtWrapper_SoSFPlane::new_SoSFPlane()
{ 
return new SoSFPlane(); }

void*  PythonQtWrapper_SoSFPlane::static_SoSFPlane_createInstance()
{
  return (SoSFPlane::createInstance());
}

SoType  PythonQtWrapper_SoSFPlane::static_SoSFPlane_getClassTypeId()
{
  return (SoSFPlane::getClassTypeId());
}

const SbPlane*  PythonQtWrapper_SoSFPlane::getValue(SoSFPlane* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFPlane::__ne__(SoSFPlane* theWrappedObject, const SoSFPlane&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbPlane*  PythonQtWrapper_SoSFPlane::operator_assign(SoSFPlane* theWrappedObject, const SbPlane&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFPlane*  PythonQtWrapper_SoSFPlane::operator_assign(SoSFPlane* theWrappedObject, const SoSFPlane&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFPlane::__eq__(SoSFPlane* theWrappedObject, const SoSFPlane&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFPlane::setValue(SoSFPlane* theWrappedObject, const SbPlane&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFPlaned* PythonQtWrapper_SoSFPlaned::new_SoSFPlaned()
{ 
return new SoSFPlaned(); }

void*  PythonQtWrapper_SoSFPlaned::static_SoSFPlaned_createInstance()
{
  return (SoSFPlaned::createInstance());
}

SoType  PythonQtWrapper_SoSFPlaned::static_SoSFPlaned_getClassTypeId()
{
  return (SoSFPlaned::getClassTypeId());
}

const SbPlaned*  PythonQtWrapper_SoSFPlaned::getValue(SoSFPlaned* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFPlaned::__ne__(SoSFPlaned* theWrappedObject, const SoSFPlaned&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbPlaned*  PythonQtWrapper_SoSFPlaned::operator_assign(SoSFPlaned* theWrappedObject, const SbPlaned&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFPlaned*  PythonQtWrapper_SoSFPlaned::operator_assign(SoSFPlaned* theWrappedObject, const SoSFPlaned&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFPlaned::__eq__(SoSFPlaned* theWrappedObject, const SoSFPlaned&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFPlaned::setValue(SoSFPlaned* theWrappedObject, const SbPlaned&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFRotation* PythonQtWrapper_SoSFRotation::new_SoSFRotation()
{ 
return new SoSFRotation(); }

void*  PythonQtWrapper_SoSFRotation::static_SoSFRotation_createInstance()
{
  return (SoSFRotation::createInstance());
}

SoType  PythonQtWrapper_SoSFRotation::static_SoSFRotation_getClassTypeId()
{
  return (SoSFRotation::getClassTypeId());
}

const SbRotation*  PythonQtWrapper_SoSFRotation::getValue(SoSFRotation* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFRotation::__ne__(SoSFRotation* theWrappedObject, const SoSFRotation&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbRotation*  PythonQtWrapper_SoSFRotation::operator_assign(SoSFRotation* theWrappedObject, const SbRotation&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFRotation*  PythonQtWrapper_SoSFRotation::operator_assign(SoSFRotation* theWrappedObject, const SoSFRotation&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFRotation::__eq__(SoSFRotation* theWrappedObject, const SoSFRotation&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFRotation::setValue(SoSFRotation* theWrappedObject, const SbRotation&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFRotation::setValue(SoSFRotation* theWrappedObject, const SbVec3f&  axis, float  angle)
{
  ( theWrappedObject->setValue(axis, angle));
}

void PythonQtWrapper_SoSFRotation::setValue(SoSFRotation* theWrappedObject, float  q0, float  q1, float  q2, float  q3)
{
  ( theWrappedObject->setValue(q0, q1, q2, q3));
}



SoSFRotationd* PythonQtWrapper_SoSFRotationd::new_SoSFRotationd()
{ 
return new SoSFRotationd(); }

void*  PythonQtWrapper_SoSFRotationd::static_SoSFRotationd_createInstance()
{
  return (SoSFRotationd::createInstance());
}

SoType  PythonQtWrapper_SoSFRotationd::static_SoSFRotationd_getClassTypeId()
{
  return (SoSFRotationd::getClassTypeId());
}

const SbRotationd*  PythonQtWrapper_SoSFRotationd::getValue(SoSFRotationd* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFRotationd::__ne__(SoSFRotationd* theWrappedObject, const SoSFRotationd&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbRotationd*  PythonQtWrapper_SoSFRotationd::operator_assign(SoSFRotationd* theWrappedObject, const SbRotationd&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFRotationd*  PythonQtWrapper_SoSFRotationd::operator_assign(SoSFRotationd* theWrappedObject, const SoSFRotationd&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFRotationd::__eq__(SoSFRotationd* theWrappedObject, const SoSFRotationd&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFRotationd::setValue(SoSFRotationd* theWrappedObject, const SbRotationd&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFRotationd::setValue(SoSFRotationd* theWrappedObject, const SbVec3d&  axis, double  angle)
{
  ( theWrappedObject->setValue(axis, angle));
}

void PythonQtWrapper_SoSFRotationd::setValue(SoSFRotationd* theWrappedObject, double  q0, double  q1, double  q2, double  q3)
{
  ( theWrappedObject->setValue(q0, q1, q2, q3));
}



SoSFShort* PythonQtWrapper_SoSFShort::new_SoSFShort()
{ 
return new SoSFShort(); }

void*  PythonQtWrapper_SoSFShort::static_SoSFShort_createInstance()
{
  return (SoSFShort::createInstance());
}

SoType  PythonQtWrapper_SoSFShort::static_SoSFShort_getClassTypeId()
{
  return (SoSFShort::getClassTypeId());
}

short  PythonQtWrapper_SoSFShort::getValue(SoSFShort* theWrappedObject) const
{
  return ( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFShort::__ne__(SoSFShort* theWrappedObject, const SoSFShort&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SoSFShort*  PythonQtWrapper_SoSFShort::operator_assign(SoSFShort* theWrappedObject, const SoSFShort&  f)
{
  return &( (*theWrappedObject)= f);
}

short  PythonQtWrapper_SoSFShort::operator_assign(SoSFShort* theWrappedObject, short  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

bool  PythonQtWrapper_SoSFShort::__eq__(SoSFShort* theWrappedObject, const SoSFShort&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFShort::setValue(SoSFShort* theWrappedObject, short  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFString* PythonQtWrapper_SoSFString::new_SoSFString()
{ 
return new SoSFString(); }

void*  PythonQtWrapper_SoSFString::static_SoSFString_createInstance()
{
  return (SoSFString::createInstance());
}

SoType  PythonQtWrapper_SoSFString::static_SoSFString_getClassTypeId()
{
  return (SoSFString::getClassTypeId());
}

const SbString*  PythonQtWrapper_SoSFString::getValue(SoSFString* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFString::__ne__(SoSFString* theWrappedObject, const SoSFString&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbString*  PythonQtWrapper_SoSFString::operator_assign(SoSFString* theWrappedObject, const SbString&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFString*  PythonQtWrapper_SoSFString::operator_assign(SoSFString* theWrappedObject, const SoSFString&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFString::__eq__(SoSFString* theWrappedObject, const SoSFString&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFString::setValue(SoSFString* theWrappedObject, const SbString&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFString::setValue(SoSFString* theWrappedObject, const char*  string)
{
  ( theWrappedObject->setValue(string));
}



SoSFTime* PythonQtWrapper_SoSFTime::new_SoSFTime()
{ 
return new SoSFTime(); }

void*  PythonQtWrapper_SoSFTime::static_SoSFTime_createInstance()
{
  return (SoSFTime::createInstance());
}

SoType  PythonQtWrapper_SoSFTime::static_SoSFTime_getClassTypeId()
{
  return (SoSFTime::getClassTypeId());
}

const SbTime*  PythonQtWrapper_SoSFTime::getValue(SoSFTime* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFTime::__ne__(SoSFTime* theWrappedObject, const SoSFTime&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbTime*  PythonQtWrapper_SoSFTime::operator_assign(SoSFTime* theWrappedObject, const SbTime&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFTime*  PythonQtWrapper_SoSFTime::operator_assign(SoSFTime* theWrappedObject, const SoSFTime&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFTime::__eq__(SoSFTime* theWrappedObject, const SoSFTime&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFTime::setValue(SoSFTime* theWrappedObject, const SbTime&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFTrigger* PythonQtWrapper_SoSFTrigger::new_SoSFTrigger()
{ 
return new SoSFTrigger(); }

void*  PythonQtWrapper_SoSFTrigger::static_SoSFTrigger_createInstance()
{
  return (SoSFTrigger::createInstance());
}

SoType  PythonQtWrapper_SoSFTrigger::static_SoSFTrigger_getClassTypeId()
{
  return (SoSFTrigger::getClassTypeId());
}

void PythonQtWrapper_SoSFTrigger::getValue(SoSFTrigger* theWrappedObject) const
{
  ( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFTrigger::__ne__(SoSFTrigger* theWrappedObject, const SoSFTrigger&  t) const
{
  return ( (*theWrappedObject)!= t);
}

const SoSFTrigger*  PythonQtWrapper_SoSFTrigger::operator_assign(SoSFTrigger* theWrappedObject, const SoSFTrigger&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFTrigger::__eq__(SoSFTrigger* theWrappedObject, const SoSFTrigger&  t) const
{
  return ( (*theWrappedObject)== t);
}

void PythonQtWrapper_SoSFTrigger::setValue(SoSFTrigger* theWrappedObject)
{
  ( theWrappedObject->setValue());
}



SoSFUInt32* PythonQtWrapper_SoSFUInt32::new_SoSFUInt32()
{ 
return new SoSFUInt32(); }

void*  PythonQtWrapper_SoSFUInt32::static_SoSFUInt32_createInstance()
{
  return (SoSFUInt32::createInstance());
}

SoType  PythonQtWrapper_SoSFUInt32::static_SoSFUInt32_getClassTypeId()
{
  return (SoSFUInt32::getClassTypeId());
}

unsigned int  PythonQtWrapper_SoSFUInt32::getValue(SoSFUInt32* theWrappedObject) const
{
  return ( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFUInt32::__ne__(SoSFUInt32* theWrappedObject, const SoSFUInt32&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SoSFUInt32*  PythonQtWrapper_SoSFUInt32::operator_assign(SoSFUInt32* theWrappedObject, const SoSFUInt32&  f)
{
  return &( (*theWrappedObject)= f);
}

unsigned int  PythonQtWrapper_SoSFUInt32::operator_assign(SoSFUInt32* theWrappedObject, unsigned int  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

bool  PythonQtWrapper_SoSFUInt32::__eq__(SoSFUInt32* theWrappedObject, const SoSFUInt32&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFUInt32::setValue(SoSFUInt32* theWrappedObject, unsigned int  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFUShort* PythonQtWrapper_SoSFUShort::new_SoSFUShort()
{ 
return new SoSFUShort(); }

void*  PythonQtWrapper_SoSFUShort::static_SoSFUShort_createInstance()
{
  return (SoSFUShort::createInstance());
}

SoType  PythonQtWrapper_SoSFUShort::static_SoSFUShort_getClassTypeId()
{
  return (SoSFUShort::getClassTypeId());
}

unsigned short  PythonQtWrapper_SoSFUShort::getValue(SoSFUShort* theWrappedObject) const
{
  return ( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFUShort::__ne__(SoSFUShort* theWrappedObject, const SoSFUShort&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SoSFUShort*  PythonQtWrapper_SoSFUShort::operator_assign(SoSFUShort* theWrappedObject, const SoSFUShort&  f)
{
  return &( (*theWrappedObject)= f);
}

unsigned short  PythonQtWrapper_SoSFUShort::operator_assign(SoSFUShort* theWrappedObject, unsigned short  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

bool  PythonQtWrapper_SoSFUShort::__eq__(SoSFUShort* theWrappedObject, const SoSFUShort&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFUShort::setValue(SoSFUShort* theWrappedObject, unsigned short  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFVec2d* PythonQtWrapper_SoSFVec2d::new_SoSFVec2d()
{ 
return new SoSFVec2d(); }

void*  PythonQtWrapper_SoSFVec2d::static_SoSFVec2d_createInstance()
{
  return (SoSFVec2d::createInstance());
}

SoType  PythonQtWrapper_SoSFVec2d::static_SoSFVec2d_getClassTypeId()
{
  return (SoSFVec2d::getClassTypeId());
}

const SbVec2d*  PythonQtWrapper_SoSFVec2d::getValue(SoSFVec2d* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFVec2d::__ne__(SoSFVec2d* theWrappedObject, const SoSFVec2d&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbVec2d*  PythonQtWrapper_SoSFVec2d::operator_assign(SoSFVec2d* theWrappedObject, const SbVec2d&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFVec2d*  PythonQtWrapper_SoSFVec2d::operator_assign(SoSFVec2d* theWrappedObject, const SoSFVec2d&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFVec2d::__eq__(SoSFVec2d* theWrappedObject, const SoSFVec2d&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFVec2d::setValue(SoSFVec2d* theWrappedObject, const SbVec2d&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFVec2d::setValue(SoSFVec2d* theWrappedObject, double  x, double  y)
{
  ( theWrappedObject->setValue(x, y));
}



SoSFVec2f* PythonQtWrapper_SoSFVec2f::new_SoSFVec2f()
{ 
return new SoSFVec2f(); }

void*  PythonQtWrapper_SoSFVec2f::static_SoSFVec2f_createInstance()
{
  return (SoSFVec2f::createInstance());
}

SoType  PythonQtWrapper_SoSFVec2f::static_SoSFVec2f_getClassTypeId()
{
  return (SoSFVec2f::getClassTypeId());
}

const SbVec2f*  PythonQtWrapper_SoSFVec2f::getValue(SoSFVec2f* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFVec2f::__ne__(SoSFVec2f* theWrappedObject, const SoSFVec2f&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbVec2f*  PythonQtWrapper_SoSFVec2f::operator_assign(SoSFVec2f* theWrappedObject, const SbVec2f&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFVec2f*  PythonQtWrapper_SoSFVec2f::operator_assign(SoSFVec2f* theWrappedObject, const SoSFVec2f&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFVec2f::__eq__(SoSFVec2f* theWrappedObject, const SoSFVec2f&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFVec2f::setValue(SoSFVec2f* theWrappedObject, const SbVec2f&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFVec2f::setValue(SoSFVec2f* theWrappedObject, float  x, float  y)
{
  ( theWrappedObject->setValue(x, y));
}



SoSFVec2s* PythonQtWrapper_SoSFVec2s::new_SoSFVec2s()
{ 
return new SoSFVec2s(); }

void*  PythonQtWrapper_SoSFVec2s::static_SoSFVec2s_createInstance()
{
  return (SoSFVec2s::createInstance());
}

SoType  PythonQtWrapper_SoSFVec2s::static_SoSFVec2s_getClassTypeId()
{
  return (SoSFVec2s::getClassTypeId());
}

const SbVec2s*  PythonQtWrapper_SoSFVec2s::getValue(SoSFVec2s* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFVec2s::__ne__(SoSFVec2s* theWrappedObject, const SoSFVec2s&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbVec2s*  PythonQtWrapper_SoSFVec2s::operator_assign(SoSFVec2s* theWrappedObject, const SbVec2s&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFVec2s*  PythonQtWrapper_SoSFVec2s::operator_assign(SoSFVec2s* theWrappedObject, const SoSFVec2s&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFVec2s::__eq__(SoSFVec2s* theWrappedObject, const SoSFVec2s&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFVec2s::setValue(SoSFVec2s* theWrappedObject, const SbVec2s&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFVec2s::setValue(SoSFVec2s* theWrappedObject, short  x, short  y)
{
  ( theWrappedObject->setValue(x, y));
}



SoSFVec3d* PythonQtWrapper_SoSFVec3d::new_SoSFVec3d()
{ 
return new SoSFVec3d(); }

void*  PythonQtWrapper_SoSFVec3d::static_SoSFVec3d_createInstance()
{
  return (SoSFVec3d::createInstance());
}

SoType  PythonQtWrapper_SoSFVec3d::static_SoSFVec3d_getClassTypeId()
{
  return (SoSFVec3d::getClassTypeId());
}

const SbVec3d*  PythonQtWrapper_SoSFVec3d::getValue(SoSFVec3d* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFVec3d::__ne__(SoSFVec3d* theWrappedObject, const SoSFVec3d&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbVec3d*  PythonQtWrapper_SoSFVec3d::operator_assign(SoSFVec3d* theWrappedObject, const SbVec3d&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFVec3d*  PythonQtWrapper_SoSFVec3d::operator_assign(SoSFVec3d* theWrappedObject, const SoSFVec3d&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFVec3d::__eq__(SoSFVec3d* theWrappedObject, const SoSFVec3d&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFVec3d::setValue(SoSFVec3d* theWrappedObject, const SbVec3d&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFVec3d::setValue(SoSFVec3d* theWrappedObject, double  x, double  y, double  z)
{
  ( theWrappedObject->setValue(x, y, z));
}



SoSFVec3f* PythonQtWrapper_SoSFVec3f::new_SoSFVec3f()
{ 
return new SoSFVec3f(); }

void*  PythonQtWrapper_SoSFVec3f::static_SoSFVec3f_createInstance()
{
  return (SoSFVec3f::createInstance());
}

SoType  PythonQtWrapper_SoSFVec3f::static_SoSFVec3f_getClassTypeId()
{
  return (SoSFVec3f::getClassTypeId());
}

const SbVec3f*  PythonQtWrapper_SoSFVec3f::getValue(SoSFVec3f* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFVec3f::__ne__(SoSFVec3f* theWrappedObject, const SoSFVec3f&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbVec3f*  PythonQtWrapper_SoSFVec3f::operator_assign(SoSFVec3f* theWrappedObject, const SbVec3f&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFVec3f*  PythonQtWrapper_SoSFVec3f::operator_assign(SoSFVec3f* theWrappedObject, const SoSFVec3f&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFVec3f::__eq__(SoSFVec3f* theWrappedObject, const SoSFVec3f&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFVec3f::setValue(SoSFVec3f* theWrappedObject, const SbVec3f&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFVec3f::setValue(SoSFVec3f* theWrappedObject, float  x, float  y, float  z)
{
  ( theWrappedObject->setValue(x, y, z));
}


