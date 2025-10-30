#include "inventor_base0.h"
#include <Inventor/SbBox.h>
#include <Inventor/SbBoxd.h>
#include <Inventor/SbColor.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbLineard.h>
#include <Inventor/SbString.h>
#include <Inventor/SbTime.h>
#include <Inventor/SbViewportRegion.h>
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
#include <PythonQtConversion.h>
#include <PythonQtMethodInfo.h>
#include <PythonQtSignalReceiver.h>
#include <QVariant>

SbBox2f* PythonQtWrapper_SbBox2f::new_SbBox2f()
{ 
return new SbBox2f(); }

SbBox2f* PythonQtWrapper_SbBox2f::new_SbBox2f(const SbVec2f&  _min, const SbVec2f&  _max)
{ 
return new SbBox2f(_min, _max); }

SbBox2f* PythonQtWrapper_SbBox2f::new_SbBox2f(float  xmin, float  ymin, float  xmax, float  ymax)
{ 
return new SbBox2f(xmin, ymin, xmax, ymax); }

void PythonQtWrapper_SbBox2f::extendBy(SbBox2f* theWrappedObject, const SbBox2f&  r)
{
  ( theWrappedObject->extendBy(r));
}

void PythonQtWrapper_SbBox2f::extendBy(SbBox2f* theWrappedObject, const SbVec2f&  pt)
{
  ( theWrappedObject->extendBy(pt));
}

float  PythonQtWrapper_SbBox2f::getAspectRatio(SbBox2f* theWrappedObject) const
{
  return ( theWrappedObject->getAspectRatio());
}

SbVec2f  PythonQtWrapper_SbBox2f::getCenter(SbBox2f* theWrappedObject) const
{
  return ( theWrappedObject->getCenter());
}

SbVec2f  PythonQtWrapper_SbBox2f::getClosestPoint(SbBox2f* theWrappedObject, const SbVec2f&  point)
{
  return ( theWrappedObject->getClosestPoint(point));
}

const SbVec2f*  PythonQtWrapper_SbBox2f::getMax(SbBox2f* theWrappedObject) const
{
  return &( theWrappedObject->getMax());
}

const SbVec2f*  PythonQtWrapper_SbBox2f::getMin(SbBox2f* theWrappedObject) const
{
  return &( theWrappedObject->getMin());
}

bool  PythonQtWrapper_SbBox2f::hasArea(SbBox2f* theWrappedObject) const
{
  return ( theWrappedObject->hasArea());
}

bool  PythonQtWrapper_SbBox2f::intersect(SbBox2f* theWrappedObject, const SbBox2f&  bb) const
{
  return ( theWrappedObject->intersect(bb));
}

bool  PythonQtWrapper_SbBox2f::intersect(SbBox2f* theWrappedObject, const SbVec2f&  pt) const
{
  return ( theWrappedObject->intersect(pt));
}

bool  PythonQtWrapper_SbBox2f::isEmpty(SbBox2f* theWrappedObject) const
{
  return ( theWrappedObject->isEmpty());
}

void PythonQtWrapper_SbBox2f::makeEmpty(SbBox2f* theWrappedObject)
{
  ( theWrappedObject->makeEmpty());
}

bool  PythonQtWrapper_SbBox2f::__ne__(SbBox2f* theWrappedObject, const SbBox2f&  b2)
{
  return ( (*theWrappedObject)!= b2);
}

bool  PythonQtWrapper_SbBox2f::__eq__(SbBox2f* theWrappedObject, const SbBox2f&  b2)
{
  return ( (*theWrappedObject)== b2);
}

void PythonQtWrapper_SbBox2f::setBounds(SbBox2f* theWrappedObject, const SbVec2f&  _min, const SbVec2f&  _max)
{
  ( theWrappedObject->setBounds(_min, _max));
}

void PythonQtWrapper_SbBox2f::setBounds(SbBox2f* theWrappedObject, float  xmin, float  ymin, float  xmax, float  ymax)
{
  ( theWrappedObject->setBounds(xmin, ymin, xmax, ymax));
}



SbBox2s* PythonQtWrapper_SbBox2s::new_SbBox2s()
{ 
return new SbBox2s(); }

SbBox2s* PythonQtWrapper_SbBox2s::new_SbBox2s(const SbVec2s&  min, const SbVec2s&  max)
{ 
return new SbBox2s(min, max); }

SbBox2s* PythonQtWrapper_SbBox2s::new_SbBox2s(short  xmin, short  ymin, short  xmax, short  ymax)
{ 
return new SbBox2s(xmin, ymin, xmax, ymax); }

void PythonQtWrapper_SbBox2s::extendBy(SbBox2s* theWrappedObject, const SbBox2s&  r)
{
  ( theWrappedObject->extendBy(r));
}

void PythonQtWrapper_SbBox2s::extendBy(SbBox2s* theWrappedObject, const SbVec2s&  pt)
{
  ( theWrappedObject->extendBy(pt));
}

float  PythonQtWrapper_SbBox2s::getAspectRatio(SbBox2s* theWrappedObject) const
{
  return ( theWrappedObject->getAspectRatio());
}

const SbVec2s*  PythonQtWrapper_SbBox2s::getMax(SbBox2s* theWrappedObject) const
{
  return &( theWrappedObject->getMax());
}

const SbVec2s*  PythonQtWrapper_SbBox2s::getMin(SbBox2s* theWrappedObject) const
{
  return &( theWrappedObject->getMin());
}

bool  PythonQtWrapper_SbBox2s::intersect(SbBox2s* theWrappedObject, const SbBox2s&  bb) const
{
  return ( theWrappedObject->intersect(bb));
}

bool  PythonQtWrapper_SbBox2s::intersect(SbBox2s* theWrappedObject, const SbVec2s&  pt) const
{
  return ( theWrappedObject->intersect(pt));
}

void PythonQtWrapper_SbBox2s::makeEmpty(SbBox2s* theWrappedObject)
{
  ( theWrappedObject->makeEmpty());
}

bool  PythonQtWrapper_SbBox2s::__ne__(SbBox2s* theWrappedObject, const SbBox2s&  b2)
{
  return ( (*theWrappedObject)!= b2);
}

bool  PythonQtWrapper_SbBox2s::__eq__(SbBox2s* theWrappedObject, const SbBox2s&  b2)
{
  return ( (*theWrappedObject)== b2);
}

void PythonQtWrapper_SbBox2s::setBounds(SbBox2s* theWrappedObject, const SbVec2s&  _min, const SbVec2s&  _max)
{
  ( theWrappedObject->setBounds(_min, _max));
}

void PythonQtWrapper_SbBox2s::setBounds(SbBox2s* theWrappedObject, short  xmin, short  ymin, short  xmax, short  ymax)
{
  ( theWrappedObject->setBounds(xmin, ymin, xmax, ymax));
}



SbBox3d* PythonQtWrapper_SbBox3d::new_SbBox3d()
{ 
return new SbBox3d(); }

SbBox3d* PythonQtWrapper_SbBox3d::new_SbBox3d(const SbVec3d&  min, const SbVec3d&  max)
{ 
return new SbBox3d(min, max); }

SbBox3d* PythonQtWrapper_SbBox3d::new_SbBox3d(double  xmin, double  ymin, double  zmin, double  xmax, double  ymax, double  zmax)
{ 
return new SbBox3d(xmin, ymin, zmin, xmax, ymax, zmax); }

void PythonQtWrapper_SbBox3d::extendBy(SbBox3d* theWrappedObject, const SbBox3d&  bb)
{
  ( theWrappedObject->extendBy(bb));
}

void PythonQtWrapper_SbBox3d::extendBy(SbBox3d* theWrappedObject, const SbVec3d&  pt)
{
  ( theWrappedObject->extendBy(pt));
}

SbVec3d  PythonQtWrapper_SbBox3d::getCenter(SbBox3d* theWrappedObject) const
{
  return ( theWrappedObject->getCenter());
}

SbVec3d  PythonQtWrapper_SbBox3d::getClosestPoint(SbBox3d* theWrappedObject, const SbVec3d&  point)
{
  return ( theWrappedObject->getClosestPoint(point));
}

SbVec3d*  PythonQtWrapper_SbBox3d::getMax(SbBox3d* theWrappedObject)
{
  return &( theWrappedObject->getMax());
}

SbVec3d*  PythonQtWrapper_SbBox3d::getMin(SbBox3d* theWrappedObject)
{
  return &( theWrappedObject->getMin());
}

double  PythonQtWrapper_SbBox3d::getVolume(SbBox3d* theWrappedObject) const
{
  return ( theWrappedObject->getVolume());
}

bool  PythonQtWrapper_SbBox3d::hasVolume(SbBox3d* theWrappedObject) const
{
  return ( theWrappedObject->hasVolume());
}

bool  PythonQtWrapper_SbBox3d::intersect(SbBox3d* theWrappedObject, const SbBox3d&  bb) const
{
  return ( theWrappedObject->intersect(bb));
}

bool  PythonQtWrapper_SbBox3d::intersect(SbBox3d* theWrappedObject, const SbVec3d&  pt) const
{
  return ( theWrappedObject->intersect(pt));
}

bool  PythonQtWrapper_SbBox3d::isEmpty(SbBox3d* theWrappedObject) const
{
  return ( theWrappedObject->isEmpty());
}

void PythonQtWrapper_SbBox3d::makeEmpty(SbBox3d* theWrappedObject)
{
  ( theWrappedObject->makeEmpty());
}

bool  PythonQtWrapper_SbBox3d::__ne__(SbBox3d* theWrappedObject, const SbBox3d&  b2)
{
  return ( (*theWrappedObject)!= b2);
}

bool  PythonQtWrapper_SbBox3d::__eq__(SbBox3d* theWrappedObject, const SbBox3d&  b2)
{
  return ( (*theWrappedObject)== b2);
}

void PythonQtWrapper_SbBox3d::setBounds(SbBox3d* theWrappedObject, const SbVec3d&  _min, const SbVec3d&  _max)
{
  ( theWrappedObject->setBounds(_min, _max));
}

void PythonQtWrapper_SbBox3d::setBounds(SbBox3d* theWrappedObject, double  xmin, double  ymin, double  zmin, double  xmax, double  ymax, double  zmax)
{
  ( theWrappedObject->setBounds(xmin, ymin, zmin, xmax, ymax, zmax));
}

void PythonQtWrapper_SbBox3d::transform(SbBox3d* theWrappedObject, const SbMatrixd&  m)
{
  ( theWrappedObject->transform(m));
}



SbBox3f* PythonQtWrapper_SbBox3f::new_SbBox3f()
{ 
return new SbBox3f(); }

SbBox3f* PythonQtWrapper_SbBox3f::new_SbBox3f(const SbVec3f&  min, const SbVec3f&  max)
{ 
return new SbBox3f(min, max); }

SbBox3f* PythonQtWrapper_SbBox3f::new_SbBox3f(float  xmin, float  ymin, float  zmin, float  xmax, float  ymax, float  zmax)
{ 
return new SbBox3f(xmin, ymin, zmin, xmax, ymax, zmax); }

void PythonQtWrapper_SbBox3f::extendBy(SbBox3f* theWrappedObject, const SbBox3f&  bb)
{
  ( theWrappedObject->extendBy(bb));
}

void PythonQtWrapper_SbBox3f::extendBy(SbBox3f* theWrappedObject, const SbVec3f&  pt)
{
  ( theWrappedObject->extendBy(pt));
}

SbVec3f  PythonQtWrapper_SbBox3f::getCenter(SbBox3f* theWrappedObject) const
{
  return ( theWrappedObject->getCenter());
}

SbVec3f  PythonQtWrapper_SbBox3f::getClosestPoint(SbBox3f* theWrappedObject, const SbVec3f&  point)
{
  return ( theWrappedObject->getClosestPoint(point));
}

SbVec3f*  PythonQtWrapper_SbBox3f::getMax(SbBox3f* theWrappedObject)
{
  return &( theWrappedObject->getMax());
}

SbVec3f*  PythonQtWrapper_SbBox3f::getMin(SbBox3f* theWrappedObject)
{
  return &( theWrappedObject->getMin());
}

float  PythonQtWrapper_SbBox3f::getVolume(SbBox3f* theWrappedObject) const
{
  return ( theWrappedObject->getVolume());
}

bool  PythonQtWrapper_SbBox3f::hasVolume(SbBox3f* theWrappedObject) const
{
  return ( theWrappedObject->hasVolume());
}

bool  PythonQtWrapper_SbBox3f::intersect(SbBox3f* theWrappedObject, const SbBox3f&  bb) const
{
  return ( theWrappedObject->intersect(bb));
}

bool  PythonQtWrapper_SbBox3f::intersect(SbBox3f* theWrappedObject, const SbVec3f&  pt) const
{
  return ( theWrappedObject->intersect(pt));
}

bool  PythonQtWrapper_SbBox3f::isEmpty(SbBox3f* theWrappedObject) const
{
  return ( theWrappedObject->isEmpty());
}

void PythonQtWrapper_SbBox3f::makeEmpty(SbBox3f* theWrappedObject)
{
  ( theWrappedObject->makeEmpty());
}

bool  PythonQtWrapper_SbBox3f::__ne__(SbBox3f* theWrappedObject, const SbBox3f&  b2)
{
  return ( (*theWrappedObject)!= b2);
}

bool  PythonQtWrapper_SbBox3f::__eq__(SbBox3f* theWrappedObject, const SbBox3f&  b2)
{
  return ( (*theWrappedObject)== b2);
}

void PythonQtWrapper_SbBox3f::setBounds(SbBox3f* theWrappedObject, const SbVec3f&  _min, const SbVec3f&  _max)
{
  ( theWrappedObject->setBounds(_min, _max));
}

void PythonQtWrapper_SbBox3f::setBounds(SbBox3f* theWrappedObject, float  xmin, float  ymin, float  zmin, float  xmax, float  ymax, float  zmax)
{
  ( theWrappedObject->setBounds(xmin, ymin, zmin, xmax, ymax, zmax));
}

void PythonQtWrapper_SbBox3f::transform(SbBox3f* theWrappedObject, const SbMatrix&  m)
{
  ( theWrappedObject->transform(m));
}



SbColor* PythonQtWrapper_SbColor::new_SbColor()
{ 
return new SbColor(); }

SbColor* PythonQtWrapper_SbColor::new_SbColor(const SbVec3f  vec3f)
{ 
return new SbColor(vec3f); }

SbColor* PythonQtWrapper_SbColor::new_SbColor(float  r, float  g, float  b)
{ 
return new SbColor(r, g, b); }

unsigned int  PythonQtWrapper_SbColor::getPackedValue(SbColor* theWrappedObject, float  transparency) const
{
  return ( theWrappedObject->getPackedValue(transparency));
}

SbColor*  PythonQtWrapper_SbColor::setHSVValue(SbColor* theWrappedObject, float  h, float  s, float  v)
{
  return &( theWrappedObject->setHSVValue(h, s, v));
}



SbCylinder* PythonQtWrapper_SbCylinder::new_SbCylinder()
{ 
return new SbCylinder(); }

SbCylinder* PythonQtWrapper_SbCylinder::new_SbCylinder(const SbLine&  a, float  r)
{ 
return new SbCylinder(a, r); }

const SbLine*  PythonQtWrapper_SbCylinder::getAxis(SbCylinder* theWrappedObject) const
{
  return &( theWrappedObject->getAxis());
}

float  PythonQtWrapper_SbCylinder::getRadius(SbCylinder* theWrappedObject) const
{
  return ( theWrappedObject->getRadius());
}

void PythonQtWrapper_SbCylinder::setAxis(SbCylinder* theWrappedObject, const SbLine&  a)
{
  ( theWrappedObject->setAxis(a));
}

void PythonQtWrapper_SbCylinder::setRadius(SbCylinder* theWrappedObject, float  r)
{
  ( theWrappedObject->setRadius(r));
}

void PythonQtWrapper_SbCylinder::setValue(SbCylinder* theWrappedObject, const SbLine&  a, float  r)
{
  ( theWrappedObject->setValue(a, r));
}



SbCylinderd* PythonQtWrapper_SbCylinderd::new_SbCylinderd()
{ 
return new SbCylinderd(); }

SbCylinderd* PythonQtWrapper_SbCylinderd::new_SbCylinderd(const SbLined&  a, double  r)
{ 
return new SbCylinderd(a, r); }

const SbLined*  PythonQtWrapper_SbCylinderd::getAxis(SbCylinderd* theWrappedObject) const
{
  return &( theWrappedObject->getAxis());
}

double  PythonQtWrapper_SbCylinderd::getRadius(SbCylinderd* theWrappedObject) const
{
  return ( theWrappedObject->getRadius());
}

void PythonQtWrapper_SbCylinderd::setAxis(SbCylinderd* theWrappedObject, const SbLined&  a)
{
  ( theWrappedObject->setAxis(a));
}

void PythonQtWrapper_SbCylinderd::setRadius(SbCylinderd* theWrappedObject, double  r)
{
  ( theWrappedObject->setRadius(r));
}

void PythonQtWrapper_SbCylinderd::setValue(SbCylinderd* theWrappedObject, const SbLined&  a, double  r)
{
  ( theWrappedObject->setValue(a, r));
}



SbLine* PythonQtWrapper_SbLine::new_SbLine()
{ 
return new SbLine(); }

SbLine* PythonQtWrapper_SbLine::new_SbLine(const SbVec3f&  p0, const SbVec3f&  p1)
{ 
return new SbLine(p0, p1); }

SbVec3f  PythonQtWrapper_SbLine::getClosestPoint(SbLine* theWrappedObject, const SbVec3f&  point) const
{
  return ( theWrappedObject->getClosestPoint(point));
}

const SbVec3f*  PythonQtWrapper_SbLine::getDirection(SbLine* theWrappedObject) const
{
  return &( theWrappedObject->getDirection());
}

const SbVec3f*  PythonQtWrapper_SbLine::getPosition(SbLine* theWrappedObject) const
{
  return &( theWrappedObject->getPosition());
}

void PythonQtWrapper_SbLine::setValue(SbLine* theWrappedObject, const SbVec3f&  p0, const SbVec3f&  p1)
{
  ( theWrappedObject->setValue(p0, p1));
}



SbLined* PythonQtWrapper_SbLined::new_SbLined()
{ 
return new SbLined(); }

SbLined* PythonQtWrapper_SbLined::new_SbLined(const SbVec3d&  p0, const SbVec3d&  p1)
{ 
return new SbLined(p0, p1); }

SbVec3d  PythonQtWrapper_SbLined::getClosestPoint(SbLined* theWrappedObject, const SbVec3d&  point) const
{
  return ( theWrappedObject->getClosestPoint(point));
}

const SbVec3d*  PythonQtWrapper_SbLined::getDirection(SbLined* theWrappedObject) const
{
  return &( theWrappedObject->getDirection());
}

const SbVec3d*  PythonQtWrapper_SbLined::getPosition(SbLined* theWrappedObject) const
{
  return &( theWrappedObject->getPosition());
}

void PythonQtWrapper_SbLined::setValue(SbLined* theWrappedObject, const SbVec3d&  p0, const SbVec3d&  p1)
{
  ( theWrappedObject->setValue(p0, p1));
}



SbMatrix* PythonQtWrapper_SbMatrix::new_SbMatrix()
{ 
return new SbMatrix(); }

SbMatrix* PythonQtWrapper_SbMatrix::new_SbMatrix(float  a11, float  a12, float  a13, float  a14, float  a21, float  a22, float  a23, float  a24, float  a31, float  a32, float  a33, float  a34, float  a41, float  a42, float  a43, float  a44)
{ 
return new SbMatrix(a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44); }

float  PythonQtWrapper_SbMatrix::det3(SbMatrix* theWrappedObject) const
{
  return ( theWrappedObject->det3());
}

float  PythonQtWrapper_SbMatrix::det3(SbMatrix* theWrappedObject, int  r1, int  r2, int  r3, int  c1, int  c2, int  c3) const
{
  return ( theWrappedObject->det3(r1, r2, r3, c1, c2, c3));
}

float  PythonQtWrapper_SbMatrix::det4(SbMatrix* theWrappedObject) const
{
  return ( theWrappedObject->det4());
}

bool  PythonQtWrapper_SbMatrix::equals(SbMatrix* theWrappedObject, const SbMatrix&  m, float  tolerance) const
{
  return ( theWrappedObject->equals(m, tolerance));
}

SbMatrix  PythonQtWrapper_SbMatrix::static_SbMatrix_identity()
{
  return (SbMatrix::identity());
}

SbMatrix  PythonQtWrapper_SbMatrix::inverse(SbMatrix* theWrappedObject) const
{
  return ( theWrappedObject->inverse());
}

void PythonQtWrapper_SbMatrix::makeIdentity(SbMatrix* theWrappedObject)
{
  ( theWrappedObject->makeIdentity());
}

SbMatrix*  PythonQtWrapper_SbMatrix::multLeft(SbMatrix* theWrappedObject, const SbMatrix&  m)
{
  return &( theWrappedObject->multLeft(m));
}

SbMatrix*  PythonQtWrapper_SbMatrix::multRight(SbMatrix* theWrappedObject, const SbMatrix&  m)
{
  return &( theWrappedObject->multRight(m));
}

bool  PythonQtWrapper_SbMatrix::__ne__(SbMatrix* theWrappedObject, const SbMatrix&  m2)
{
  return ( (*theWrappedObject)!= m2);
}

SbMatrix  PythonQtWrapper_SbMatrix::__mul__(SbMatrix* theWrappedObject, const SbMatrix&  m2)
{
  return ( (*theWrappedObject)* m2);
}

SbMatrix*  PythonQtWrapper_SbMatrix::__imul__(SbMatrix* theWrappedObject, const SbMatrix&  m)
{
  return &( (*theWrappedObject)*= m);
}

SbMatrix*  PythonQtWrapper_SbMatrix::operator_assign(SbMatrix* theWrappedObject, const SbMatrix&  m)
{
  return &( (*theWrappedObject)= m);
}

SbMatrix*  PythonQtWrapper_SbMatrix::operator_assign(SbMatrix* theWrappedObject, const SbRotation&  q)
{
  return &( (*theWrappedObject)= q);
}

bool  PythonQtWrapper_SbMatrix::__eq__(SbMatrix* theWrappedObject, const SbMatrix&  m2)
{
  return ( (*theWrappedObject)== m2);
}

void PythonQtWrapper_SbMatrix::setRotate(SbMatrix* theWrappedObject, const SbRotation&  q)
{
  ( theWrappedObject->setRotate(q));
}

void PythonQtWrapper_SbMatrix::setScale(SbMatrix* theWrappedObject, const SbVec3f&  s)
{
  ( theWrappedObject->setScale(s));
}

void PythonQtWrapper_SbMatrix::setScale(SbMatrix* theWrappedObject, float  s)
{
  ( theWrappedObject->setScale(s));
}

void PythonQtWrapper_SbMatrix::setTransform(SbMatrix* theWrappedObject, const SbVec3f&  t, const SbRotation&  r, const SbVec3f&  s)
{
  ( theWrappedObject->setTransform(t, r, s));
}

void PythonQtWrapper_SbMatrix::setTransform(SbMatrix* theWrappedObject, const SbVec3f&  t, const SbRotation&  r, const SbVec3f&  s, const SbRotation&  so)
{
  ( theWrappedObject->setTransform(t, r, s, so));
}

void PythonQtWrapper_SbMatrix::setTransform(SbMatrix* theWrappedObject, const SbVec3f&  translation, const SbRotation&  rotation, const SbVec3f&  scaleFactor, const SbRotation&  scaleOrientation, const SbVec3f&  center)
{
  ( theWrappedObject->setTransform(translation, rotation, scaleFactor, scaleOrientation, center));
}

void PythonQtWrapper_SbMatrix::setTranslate(SbMatrix* theWrappedObject, const SbVec3f&  t)
{
  ( theWrappedObject->setTranslate(t));
}

SbVec3f  PythonQtWrapper_SbMatrix::transformDirection(SbMatrix* theWrappedObject, const SbVec3f&  src) const
{
  return ( theWrappedObject->transformDirection(src));
}

SbLine  PythonQtWrapper_SbMatrix::transformLine(SbMatrix* theWrappedObject, const SbLine&  src) const
{
  return ( theWrappedObject->transformLine(src));
}

SbVec3f  PythonQtWrapper_SbMatrix::transformPoint(SbMatrix* theWrappedObject, const SbVec3f&  src) const
{
  return ( theWrappedObject->transformPoint(src));
}

SbVec4f  PythonQtWrapper_SbMatrix::transformPoint(SbMatrix* theWrappedObject, const SbVec4f&  src) const
{
  return ( theWrappedObject->transformPoint(src));
}

SbMatrix  PythonQtWrapper_SbMatrix::transpose(SbMatrix* theWrappedObject) const
{
  return ( theWrappedObject->transpose());
}



SbMatrixd* PythonQtWrapper_SbMatrixd::new_SbMatrixd()
{ 
return new SbMatrixd(); }

SbMatrixd* PythonQtWrapper_SbMatrixd::new_SbMatrixd(double  a11, double  a12, double  a13, double  a14, double  a21, double  a22, double  a23, double  a24, double  a31, double  a32, double  a33, double  a34, double  a41, double  a42, double  a43, double  a44)
{ 
return new SbMatrixd(a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44); }

double  PythonQtWrapper_SbMatrixd::det3(SbMatrixd* theWrappedObject) const
{
  return ( theWrappedObject->det3());
}

double  PythonQtWrapper_SbMatrixd::det3(SbMatrixd* theWrappedObject, int  r1, int  r2, int  r3, int  c1, int  c2, int  c3) const
{
  return ( theWrappedObject->det3(r1, r2, r3, c1, c2, c3));
}

double  PythonQtWrapper_SbMatrixd::det4(SbMatrixd* theWrappedObject) const
{
  return ( theWrappedObject->det4());
}

bool  PythonQtWrapper_SbMatrixd::equals(SbMatrixd* theWrappedObject, const SbMatrixd&  m, double  tolerance) const
{
  return ( theWrappedObject->equals(m, tolerance));
}

SbMatrixd  PythonQtWrapper_SbMatrixd::static_SbMatrixd_identity()
{
  return (SbMatrixd::identity());
}

SbMatrixd  PythonQtWrapper_SbMatrixd::inverse(SbMatrixd* theWrappedObject) const
{
  return ( theWrappedObject->inverse());
}

void PythonQtWrapper_SbMatrixd::makeIdentity(SbMatrixd* theWrappedObject)
{
  ( theWrappedObject->makeIdentity());
}

SbMatrixd*  PythonQtWrapper_SbMatrixd::multLeft(SbMatrixd* theWrappedObject, const SbMatrixd&  m)
{
  return &( theWrappedObject->multLeft(m));
}

SbMatrixd*  PythonQtWrapper_SbMatrixd::multRight(SbMatrixd* theWrappedObject, const SbMatrixd&  m)
{
  return &( theWrappedObject->multRight(m));
}

bool  PythonQtWrapper_SbMatrixd::__ne__(SbMatrixd* theWrappedObject, const SbMatrixd&  m2)
{
  return ( (*theWrappedObject)!= m2);
}

SbMatrixd  PythonQtWrapper_SbMatrixd::__mul__(SbMatrixd* theWrappedObject, const SbMatrixd&  m2)
{
  return ( (*theWrappedObject)* m2);
}

SbMatrixd*  PythonQtWrapper_SbMatrixd::__imul__(SbMatrixd* theWrappedObject, const SbMatrixd&  m)
{
  return &( (*theWrappedObject)*= m);
}

SbMatrixd*  PythonQtWrapper_SbMatrixd::operator_assign(SbMatrixd* theWrappedObject, const SbMatrixd&  m)
{
  return &( (*theWrappedObject)= m);
}

SbMatrixd*  PythonQtWrapper_SbMatrixd::operator_assign(SbMatrixd* theWrappedObject, const SbRotationd&  q)
{
  return &( (*theWrappedObject)= q);
}

bool  PythonQtWrapper_SbMatrixd::__eq__(SbMatrixd* theWrappedObject, const SbMatrixd&  m2)
{
  return ( (*theWrappedObject)== m2);
}

void PythonQtWrapper_SbMatrixd::setRotate(SbMatrixd* theWrappedObject, const SbRotationd&  q)
{
  ( theWrappedObject->setRotate(q));
}

void PythonQtWrapper_SbMatrixd::setScale(SbMatrixd* theWrappedObject, const SbVec3d&  s)
{
  ( theWrappedObject->setScale(s));
}

void PythonQtWrapper_SbMatrixd::setScale(SbMatrixd* theWrappedObject, double  s)
{
  ( theWrappedObject->setScale(s));
}

void PythonQtWrapper_SbMatrixd::setTransform(SbMatrixd* theWrappedObject, const SbVec3d&  t, const SbRotationd&  r, const SbVec3d&  s)
{
  ( theWrappedObject->setTransform(t, r, s));
}

void PythonQtWrapper_SbMatrixd::setTransform(SbMatrixd* theWrappedObject, const SbVec3d&  t, const SbRotationd&  r, const SbVec3d&  s, const SbRotationd&  so)
{
  ( theWrappedObject->setTransform(t, r, s, so));
}

void PythonQtWrapper_SbMatrixd::setTransform(SbMatrixd* theWrappedObject, const SbVec3d&  translation, const SbRotationd&  rotation, const SbVec3d&  scaleFactor, const SbRotationd&  scaleOrientation, const SbVec3d&  center)
{
  ( theWrappedObject->setTransform(translation, rotation, scaleFactor, scaleOrientation, center));
}

void PythonQtWrapper_SbMatrixd::setTranslate(SbMatrixd* theWrappedObject, const SbVec3d&  t)
{
  ( theWrappedObject->setTranslate(t));
}

SbVec3d  PythonQtWrapper_SbMatrixd::transformDirection(SbMatrixd* theWrappedObject, const SbVec3d&  src) const
{
  return ( theWrappedObject->transformDirection(src));
}

SbLined  PythonQtWrapper_SbMatrixd::transformLine(SbMatrixd* theWrappedObject, const SbLined&  src) const
{
  return ( theWrappedObject->transformLine(src));
}

SbVec3d  PythonQtWrapper_SbMatrixd::transformPoint(SbMatrixd* theWrappedObject, const SbVec3d&  src) const
{
  return ( theWrappedObject->transformPoint(src));
}

SbVec4d  PythonQtWrapper_SbMatrixd::transformPoint(SbMatrixd* theWrappedObject, const SbVec4d&  src) const
{
  return ( theWrappedObject->transformPoint(src));
}

SbMatrixd  PythonQtWrapper_SbMatrixd::transpose(SbMatrixd* theWrappedObject) const
{
  return ( theWrappedObject->transpose());
}



SbName* PythonQtWrapper_SbName::new_SbName()
{ 
return new SbName(); }

SbName* PythonQtWrapper_SbName::new_SbName(const SbName&  n)
{ 
return new SbName(n); }

SbName* PythonQtWrapper_SbName::new_SbName(const SbString&  s)
{ 
return new SbName(s); }

SbName* PythonQtWrapper_SbName::new_SbName(const char*  s)
{ 
return new SbName(s); }

int  PythonQtWrapper_SbName::getLength(SbName* theWrappedObject) const
{
  return ( theWrappedObject->getLength());
}

const char*  PythonQtWrapper_SbName::getString(SbName* theWrappedObject) const
{
  return ( theWrappedObject->getString());
}

bool  PythonQtWrapper_SbName::static_SbName_isBaseNameChar(char  c)
{
  return (SbName::isBaseNameChar(c));
}

bool  PythonQtWrapper_SbName::static_SbName_isBaseNameStartChar(char  c)
{
  return (SbName::isBaseNameStartChar(c));
}

bool  PythonQtWrapper_SbName::static_SbName_isIdentChar(char  c)
{
  return (SbName::isIdentChar(c));
}

bool  PythonQtWrapper_SbName::static_SbName_isIdentStartChar(char  c)
{
  return (SbName::isIdentStartChar(c));
}

bool  PythonQtWrapper_SbName::operator_not(SbName* theWrappedObject) const
{
  return (!  (*theWrappedObject));
}

bool  PythonQtWrapper_SbName::__ne__(SbName* theWrappedObject, const SbName&  n2)
{
  return ( (*theWrappedObject)!= n2);
}

bool  PythonQtWrapper_SbName::__eq__(SbName* theWrappedObject, const SbName&  n2)
{
  return ( (*theWrappedObject)== n2);
}



SbPlane* PythonQtWrapper_SbPlane::new_SbPlane()
{ 
return new SbPlane(); }

SbPlane* PythonQtWrapper_SbPlane::new_SbPlane(const SbVec3f&  n, const SbVec3f&  p)
{ 
return new SbPlane(n, p); }

SbPlane* PythonQtWrapper_SbPlane::new_SbPlane(const SbVec3f&  n, float  d)
{ 
return new SbPlane(n, d); }

SbPlane* PythonQtWrapper_SbPlane::new_SbPlane(const SbVec3f&  p0, const SbVec3f&  p1, const SbVec3f&  p2)
{ 
return new SbPlane(p0, p1, p2); }

float  PythonQtWrapper_SbPlane::getDistance(SbPlane* theWrappedObject, const SbVec3f&  point) const
{
  return ( theWrappedObject->getDistance(point));
}

float  PythonQtWrapper_SbPlane::getDistanceFromOrigin(SbPlane* theWrappedObject) const
{
  return ( theWrappedObject->getDistanceFromOrigin());
}

const SbVec3f*  PythonQtWrapper_SbPlane::getNormal(SbPlane* theWrappedObject) const
{
  return &( theWrappedObject->getNormal());
}

bool  PythonQtWrapper_SbPlane::isInHalfSpace(SbPlane* theWrappedObject, const SbVec3f&  point) const
{
  return ( theWrappedObject->isInHalfSpace(point));
}

void PythonQtWrapper_SbPlane::offset(SbPlane* theWrappedObject, float  d)
{
  ( theWrappedObject->offset(d));
}

bool  PythonQtWrapper_SbPlane::__ne__(SbPlane* theWrappedObject, const SbPlane&  p2)
{
  return ( (*theWrappedObject)!= p2);
}

bool  PythonQtWrapper_SbPlane::__eq__(SbPlane* theWrappedObject, const SbPlane&  p2)
{
  return ( (*theWrappedObject)== p2);
}

void PythonQtWrapper_SbPlane::transform(SbPlane* theWrappedObject, const SbMatrix&  matrix)
{
  ( theWrappedObject->transform(matrix));
}



SbPlaned* PythonQtWrapper_SbPlaned::new_SbPlaned()
{ 
return new SbPlaned(); }

SbPlaned* PythonQtWrapper_SbPlaned::new_SbPlaned(const SbVec3d&  n, const SbVec3d&  p)
{ 
return new SbPlaned(n, p); }

SbPlaned* PythonQtWrapper_SbPlaned::new_SbPlaned(const SbVec3d&  n, double  d)
{ 
return new SbPlaned(n, d); }

SbPlaned* PythonQtWrapper_SbPlaned::new_SbPlaned(const SbVec3d&  p0, const SbVec3d&  p1, const SbVec3d&  p2)
{ 
return new SbPlaned(p0, p1, p2); }

double  PythonQtWrapper_SbPlaned::getDistance(SbPlaned* theWrappedObject, const SbVec3d&  point) const
{
  return ( theWrappedObject->getDistance(point));
}

double  PythonQtWrapper_SbPlaned::getDistanceFromOrigin(SbPlaned* theWrappedObject) const
{
  return ( theWrappedObject->getDistanceFromOrigin());
}

const SbVec3d*  PythonQtWrapper_SbPlaned::getNormal(SbPlaned* theWrappedObject) const
{
  return &( theWrappedObject->getNormal());
}

bool  PythonQtWrapper_SbPlaned::isInHalfSpace(SbPlaned* theWrappedObject, const SbVec3d&  point) const
{
  return ( theWrappedObject->isInHalfSpace(point));
}

void PythonQtWrapper_SbPlaned::offset(SbPlaned* theWrappedObject, double  d)
{
  ( theWrappedObject->offset(d));
}

bool  PythonQtWrapper_SbPlaned::__ne__(SbPlaned* theWrappedObject, const SbPlaned&  p2)
{
  return ( (*theWrappedObject)!= p2);
}

bool  PythonQtWrapper_SbPlaned::__eq__(SbPlaned* theWrappedObject, const SbPlaned&  p2)
{
  return ( (*theWrappedObject)== p2);
}

void PythonQtWrapper_SbPlaned::transform(SbPlaned* theWrappedObject, const SbMatrixd&  matrix)
{
  ( theWrappedObject->transform(matrix));
}



SbRotation* PythonQtWrapper_SbRotation::new_SbRotation()
{ 
return new SbRotation(); }

SbRotation* PythonQtWrapper_SbRotation::new_SbRotation(const SbMatrix&  m)
{ 
return new SbRotation(m); }

SbRotation* PythonQtWrapper_SbRotation::new_SbRotation(const SbVec3f&  axis, float  radians)
{ 
return new SbRotation(axis, radians); }

SbRotation* PythonQtWrapper_SbRotation::new_SbRotation(const SbVec3f&  rotateFrom, const SbVec3f&  rotateTo)
{ 
return new SbRotation(rotateFrom, rotateTo); }

SbRotation* PythonQtWrapper_SbRotation::new_SbRotation(float  q0, float  q1, float  q2, float  q3)
{ 
return new SbRotation(q0, q1, q2, q3); }

bool  PythonQtWrapper_SbRotation::equals(SbRotation* theWrappedObject, const SbRotation&  r, float  tolerance) const
{
  return ( theWrappedObject->equals(r, tolerance));
}

float  PythonQtWrapper_SbRotation::getAngle(SbRotation* theWrappedObject) const
{
  return ( theWrappedObject->getAngle());
}

SbVec3f  PythonQtWrapper_SbRotation::getAxis(SbRotation* theWrappedObject) const
{
  return ( theWrappedObject->getAxis());
}

SbMatrix  PythonQtWrapper_SbRotation::getMatrix(SbRotation* theWrappedObject) const
{
  return ( theWrappedObject->getMatrix());
}

SbRotation  PythonQtWrapper_SbRotation::static_SbRotation_identity()
{
  return (SbRotation::identity());
}

SbRotation  PythonQtWrapper_SbRotation::inverse(SbRotation* theWrappedObject) const
{
  return ( theWrappedObject->inverse());
}

SbRotation*  PythonQtWrapper_SbRotation::invert(SbRotation* theWrappedObject)
{
  return &( theWrappedObject->invert());
}

bool  PythonQtWrapper_SbRotation::__ne__(SbRotation* theWrappedObject, const SbRotation&  q2)
{
  return ( (*theWrappedObject)!= q2);
}

SbRotation  PythonQtWrapper_SbRotation::__mul__(SbRotation* theWrappedObject, const SbRotation&  q2)
{
  return ( (*theWrappedObject)* q2);
}

SbRotation*  PythonQtWrapper_SbRotation::__imul__(SbRotation* theWrappedObject, const SbRotation&  q)
{
  return &( (*theWrappedObject)*= q);
}

bool  PythonQtWrapper_SbRotation::__eq__(SbRotation* theWrappedObject, const SbRotation&  q2)
{
  return ( (*theWrappedObject)== q2);
}

void PythonQtWrapper_SbRotation::scaleAngle(SbRotation* theWrappedObject, float  scaleFactor)
{
  ( theWrappedObject->scaleAngle(scaleFactor));
}

SbRotation*  PythonQtWrapper_SbRotation::setValue(SbRotation* theWrappedObject, const SbMatrix&  m)
{
  return &( theWrappedObject->setValue(m));
}

SbRotation*  PythonQtWrapper_SbRotation::setValue(SbRotation* theWrappedObject, const SbVec3f&  axis, float  radians)
{
  return &( theWrappedObject->setValue(axis, radians));
}

SbRotation*  PythonQtWrapper_SbRotation::setValue(SbRotation* theWrappedObject, const SbVec3f&  rotateFrom, const SbVec3f&  rotateTo)
{
  return &( theWrappedObject->setValue(rotateFrom, rotateTo));
}

SbRotation*  PythonQtWrapper_SbRotation::setValue(SbRotation* theWrappedObject, float  q0, float  q1, float  q2, float  q3)
{
  return &( theWrappedObject->setValue(q0, q1, q2, q3));
}

SbRotation  PythonQtWrapper_SbRotation::static_SbRotation_slerp(const SbRotation&  rot0, const SbRotation&  rot1, float  t)
{
  return (SbRotation::slerp(rot0, rot1, t));
}

SbVec3f  PythonQtWrapper_SbRotation::transformPoint(SbRotation* theWrappedObject, const SbVec3f&  src) const
{
  return ( theWrappedObject->transformPoint(src));
}



SbRotationd* PythonQtWrapper_SbRotationd::new_SbRotationd()
{ 
return new SbRotationd(); }

SbRotationd* PythonQtWrapper_SbRotationd::new_SbRotationd(const SbMatrixd&  m)
{ 
return new SbRotationd(m); }

SbRotationd* PythonQtWrapper_SbRotationd::new_SbRotationd(const SbVec3d&  axis, double  radians)
{ 
return new SbRotationd(axis, radians); }

SbRotationd* PythonQtWrapper_SbRotationd::new_SbRotationd(const SbVec3d&  rotateFrom, const SbVec3d&  rotateTo)
{ 
return new SbRotationd(rotateFrom, rotateTo); }

SbRotationd* PythonQtWrapper_SbRotationd::new_SbRotationd(double  q0, double  q1, double  q2, double  q3)
{ 
return new SbRotationd(q0, q1, q2, q3); }

bool  PythonQtWrapper_SbRotationd::equals(SbRotationd* theWrappedObject, const SbRotationd&  r, double  tolerance) const
{
  return ( theWrappedObject->equals(r, tolerance));
}

double  PythonQtWrapper_SbRotationd::getAngle(SbRotationd* theWrappedObject) const
{
  return ( theWrappedObject->getAngle());
}

SbVec3d  PythonQtWrapper_SbRotationd::getAxis(SbRotationd* theWrappedObject) const
{
  return ( theWrappedObject->getAxis());
}

SbMatrixd  PythonQtWrapper_SbRotationd::getMatrix(SbRotationd* theWrappedObject) const
{
  return ( theWrappedObject->getMatrix());
}

SbRotationd  PythonQtWrapper_SbRotationd::static_SbRotationd_identity()
{
  return (SbRotationd::identity());
}

SbRotationd  PythonQtWrapper_SbRotationd::inverse(SbRotationd* theWrappedObject) const
{
  return ( theWrappedObject->inverse());
}

SbRotationd*  PythonQtWrapper_SbRotationd::invert(SbRotationd* theWrappedObject)
{
  return &( theWrappedObject->invert());
}

bool  PythonQtWrapper_SbRotationd::__ne__(SbRotationd* theWrappedObject, const SbRotationd&  q2)
{
  return ( (*theWrappedObject)!= q2);
}

SbRotationd  PythonQtWrapper_SbRotationd::__mul__(SbRotationd* theWrappedObject, const SbRotationd&  q2)
{
  return ( (*theWrappedObject)* q2);
}

SbRotationd*  PythonQtWrapper_SbRotationd::__imul__(SbRotationd* theWrappedObject, const SbRotationd&  q)
{
  return &( (*theWrappedObject)*= q);
}

bool  PythonQtWrapper_SbRotationd::__eq__(SbRotationd* theWrappedObject, const SbRotationd&  q2)
{
  return ( (*theWrappedObject)== q2);
}

void PythonQtWrapper_SbRotationd::scaleAngle(SbRotationd* theWrappedObject, double  scaleFactor)
{
  ( theWrappedObject->scaleAngle(scaleFactor));
}

SbRotationd*  PythonQtWrapper_SbRotationd::setValue(SbRotationd* theWrappedObject, const SbMatrixd&  m)
{
  return &( theWrappedObject->setValue(m));
}

SbRotationd*  PythonQtWrapper_SbRotationd::setValue(SbRotationd* theWrappedObject, const SbVec3d&  axis, double  radians)
{
  return &( theWrappedObject->setValue(axis, radians));
}

SbRotationd*  PythonQtWrapper_SbRotationd::setValue(SbRotationd* theWrappedObject, const SbVec3d&  rotateFrom, const SbVec3d&  rotateTo)
{
  return &( theWrappedObject->setValue(rotateFrom, rotateTo));
}

SbRotationd*  PythonQtWrapper_SbRotationd::setValue(SbRotationd* theWrappedObject, double  q0, double  q1, double  q2, double  q3)
{
  return &( theWrappedObject->setValue(q0, q1, q2, q3));
}

SbRotationd  PythonQtWrapper_SbRotationd::static_SbRotationd_slerp(const SbRotationd&  rot0, const SbRotationd&  rot1, double  t)
{
  return (SbRotationd::slerp(rot0, rot1, t));
}

SbVec3d  PythonQtWrapper_SbRotationd::transformPoint(SbRotationd* theWrappedObject, const SbVec3d&  src) const
{
  return ( theWrappedObject->transformPoint(src));
}



SbSphere* PythonQtWrapper_SbSphere::new_SbSphere()
{ 
return new SbSphere(); }

SbSphere* PythonQtWrapper_SbSphere::new_SbSphere(const SbVec3f&  c, float  r)
{ 
return new SbSphere(c, r); }

void PythonQtWrapper_SbSphere::circumscribe(SbSphere* theWrappedObject, const SbBox3f&  box)
{
  ( theWrappedObject->circumscribe(box));
}

const SbVec3f*  PythonQtWrapper_SbSphere::getCenter(SbSphere* theWrappedObject) const
{
  return &( theWrappedObject->getCenter());
}

float  PythonQtWrapper_SbSphere::getRadius(SbSphere* theWrappedObject) const
{
  return ( theWrappedObject->getRadius());
}

void PythonQtWrapper_SbSphere::setCenter(SbSphere* theWrappedObject, const SbVec3f&  c)
{
  ( theWrappedObject->setCenter(c));
}

void PythonQtWrapper_SbSphere::setRadius(SbSphere* theWrappedObject, float  r)
{
  ( theWrappedObject->setRadius(r));
}

void PythonQtWrapper_SbSphere::setValue(SbSphere* theWrappedObject, const SbVec3f&  c, float  r)
{
  ( theWrappedObject->setValue(c, r));
}



SbSphered* PythonQtWrapper_SbSphered::new_SbSphered()
{ 
return new SbSphered(); }

SbSphered* PythonQtWrapper_SbSphered::new_SbSphered(const SbVec3d&  c, double  r)
{ 
return new SbSphered(c, r); }

void PythonQtWrapper_SbSphered::circumscribe(SbSphered* theWrappedObject, const SbBox3d&  box)
{
  ( theWrappedObject->circumscribe(box));
}

const SbVec3d*  PythonQtWrapper_SbSphered::getCenter(SbSphered* theWrappedObject) const
{
  return &( theWrappedObject->getCenter());
}

double  PythonQtWrapper_SbSphered::getRadius(SbSphered* theWrappedObject) const
{
  return ( theWrappedObject->getRadius());
}

void PythonQtWrapper_SbSphered::setCenter(SbSphered* theWrappedObject, const SbVec3d&  c)
{
  ( theWrappedObject->setCenter(c));
}

void PythonQtWrapper_SbSphered::setRadius(SbSphered* theWrappedObject, double  r)
{
  ( theWrappedObject->setRadius(r));
}

void PythonQtWrapper_SbSphered::setValue(SbSphered* theWrappedObject, const SbVec3d&  c, double  r)
{
  ( theWrappedObject->setValue(c, r));
}



SbString* PythonQtWrapper_SbString::new_SbString()
{ 
return new SbString(); }

SbString* PythonQtWrapper_SbString::new_SbString(const SbString&  str)
{ 
return new SbString(str); }

SbString* PythonQtWrapper_SbString::new_SbString(const char*  str)
{ 
return new SbString(str); }

SbString* PythonQtWrapper_SbString::new_SbString(const char*  str, int  start, int  end)
{ 
return new SbString(str, start, end); }

SbString* PythonQtWrapper_SbString::new_SbString(int  digitString)
{ 
return new SbString(digitString); }

void PythonQtWrapper_SbString::deleteSubString(SbString* theWrappedObject, int  startChar, int  endChar)
{
  ( theWrappedObject->deleteSubString(startChar, endChar));
}

int  PythonQtWrapper_SbString::getLength(SbString* theWrappedObject) const
{
  return ( theWrappedObject->getLength());
}

const char*  PythonQtWrapper_SbString::getString(SbString* theWrappedObject) const
{
  return ( theWrappedObject->getString());
}

SbString  PythonQtWrapper_SbString::getSubString(SbString* theWrappedObject, int  startChar, int  endChar) const
{
  return ( theWrappedObject->getSubString(startChar, endChar));
}

unsigned int  PythonQtWrapper_SbString::hash(SbString* theWrappedObject)
{
  return ( theWrappedObject->hash());
}

unsigned int  PythonQtWrapper_SbString::static_SbString_hash(const char*  s)
{
  return (SbString::hash(s));
}

void PythonQtWrapper_SbString::makeEmpty(SbString* theWrappedObject, bool  freeOld)
{
  ( theWrappedObject->makeEmpty(freeOld));
}

bool  PythonQtWrapper_SbString::operator_not(SbString* theWrappedObject) const
{
  return (!  (*theWrappedObject));
}

bool  PythonQtWrapper_SbString::__ne__(SbString* theWrappedObject, const SbString&  str2)
{
  return ( (*theWrappedObject)!= str2);
}

SbString*  PythonQtWrapper_SbString::__iadd__(SbString* theWrappedObject, const SbString&  str)
{
  return &( (*theWrappedObject)+= str);
}

SbString*  PythonQtWrapper_SbString::__iadd__(SbString* theWrappedObject, const char*  str)
{
  return &( (*theWrappedObject)+= str);
}

bool  PythonQtWrapper_SbString::__lt__(SbString* theWrappedObject, const SbString&  str2)
{
  return ( (*theWrappedObject)< str2);
}

SbString*  PythonQtWrapper_SbString::operator_assign(SbString* theWrappedObject, const SbString&  str)
{
  return &( (*theWrappedObject)= str);
}

SbString*  PythonQtWrapper_SbString::operator_assign(SbString* theWrappedObject, const char*  str)
{
  return &( (*theWrappedObject)= str);
}

bool  PythonQtWrapper_SbString::__eq__(SbString* theWrappedObject, const SbString&  str2)
{
  return ( (*theWrappedObject)== str2);
}



SbTime* PythonQtWrapper_SbTime::new_SbTime()
{ 
return new SbTime(); }

SbTime* PythonQtWrapper_SbTime::new_SbTime(double  sec)
{ 
return new SbTime(sec); }

SbString  PythonQtWrapper_SbTime::format(SbTime* theWrappedObject, const char*  fmt) const
{
  return ( theWrappedObject->format(fmt));
}

SbString  PythonQtWrapper_SbTime::formatDate(SbTime* theWrappedObject, const char*  fmt) const
{
  return ( theWrappedObject->formatDate(fmt));
}

unsigned long  PythonQtWrapper_SbTime::getMsecValue(SbTime* theWrappedObject) const
{
  return ( theWrappedObject->getMsecValue());
}

SbTime  PythonQtWrapper_SbTime::static_SbTime_getTimeOfDay()
{
  return (SbTime::getTimeOfDay());
}

double  PythonQtWrapper_SbTime::getValue(SbTime* theWrappedObject) const
{
  return ( theWrappedObject->getValue());
}

SbTime  PythonQtWrapper_SbTime::static_SbTime_max()
{
  return (SbTime::max());
}

bool  PythonQtWrapper_SbTime::__ne__(SbTime* theWrappedObject, const SbTime&  tm) const
{
  return ( (*theWrappedObject)!= tm);
}

SbTime  PythonQtWrapper_SbTime::__mod__(SbTime* theWrappedObject, const SbTime&  tm) const
{
  return ( (*theWrappedObject)% tm);
}

SbTime  PythonQtWrapper_SbTime::__mul__(SbTime* theWrappedObject, double  s)
{
  return ( (*theWrappedObject)* s);
}

SbTime*  PythonQtWrapper_SbTime::__imul__(SbTime* theWrappedObject, double  s)
{
  return &( (*theWrappedObject)*= s);
}

SbTime  PythonQtWrapper_SbTime::__add__(SbTime* theWrappedObject, const SbTime&  t1)
{
  return ( (*theWrappedObject)+ t1);
}

SbTime*  PythonQtWrapper_SbTime::__iadd__(SbTime* theWrappedObject, const SbTime&  tm)
{
  return &( (*theWrappedObject)+= tm);
}

SbTime  PythonQtWrapper_SbTime::__sub__(SbTime* theWrappedObject) const
{
  return (-  (*theWrappedObject));
}

SbTime  PythonQtWrapper_SbTime::__sub__(SbTime* theWrappedObject, const SbTime&  t1)
{
  return ( (*theWrappedObject)- t1);
}

SbTime*  PythonQtWrapper_SbTime::__isub__(SbTime* theWrappedObject, const SbTime&  tm)
{
  return &( (*theWrappedObject)-= tm);
}

double  PythonQtWrapper_SbTime::__div__(SbTime* theWrappedObject, const SbTime&  tm) const
{
  return ( (*theWrappedObject)/ tm);
}

SbTime  PythonQtWrapper_SbTime::__div__(SbTime* theWrappedObject, double  s)
{
  return ( (*theWrappedObject)/ s);
}

SbTime*  PythonQtWrapper_SbTime::__idiv__(SbTime* theWrappedObject, double  s)
{
  return &( (*theWrappedObject)/= s);
}

bool  PythonQtWrapper_SbTime::__lt__(SbTime* theWrappedObject, const SbTime&  tm) const
{
  return ( (*theWrappedObject)< tm);
}

bool  PythonQtWrapper_SbTime::__le__(SbTime* theWrappedObject, const SbTime&  tm) const
{
  return ( (*theWrappedObject)<= tm);
}

bool  PythonQtWrapper_SbTime::__eq__(SbTime* theWrappedObject, const SbTime&  tm) const
{
  return ( (*theWrappedObject)== tm);
}

bool  PythonQtWrapper_SbTime::__gt__(SbTime* theWrappedObject, const SbTime&  tm) const
{
  return ( (*theWrappedObject)> tm);
}

bool  PythonQtWrapper_SbTime::__ge__(SbTime* theWrappedObject, const SbTime&  tm) const
{
  return ( (*theWrappedObject)>= tm);
}

void PythonQtWrapper_SbTime::setMsecValue(SbTime* theWrappedObject, unsigned long  msec)
{
  ( theWrappedObject->setMsecValue(msec));
}

void PythonQtWrapper_SbTime::setToTimeOfDay(SbTime* theWrappedObject)
{
  ( theWrappedObject->setToTimeOfDay());
}

void PythonQtWrapper_SbTime::setValue(SbTime* theWrappedObject, double  sec)
{
  ( theWrappedObject->setValue(sec));
}

SbTime  PythonQtWrapper_SbTime::static_SbTime_zero()
{
  return (SbTime::zero());
}



PythonQtShell_SbVec2d::~PythonQtShell_SbVec2d() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SbVec2d* PythonQtWrapper_SbVec2d::new_SbVec2d()
{ 
return new PythonQtShell_SbVec2d(); }

SbVec2d* PythonQtWrapper_SbVec2d::new_SbVec2d(double  x, double  y)
{ 
return new PythonQtShell_SbVec2d(x, y); }

double  PythonQtWrapper_SbVec2d::dot(SbVec2d* theWrappedObject, const SbVec2d&  v) const
{
  return ( theWrappedObject->dot(v));
}

bool  PythonQtWrapper_SbVec2d::equals(SbVec2d* theWrappedObject, const SbVec2d  v, double  tolerance) const
{
  return ( theWrappedObject->equals(v, tolerance));
}

double  PythonQtWrapper_SbVec2d::length(SbVec2d* theWrappedObject) const
{
  return ( theWrappedObject->length());
}

void PythonQtWrapper_SbVec2d::negate(SbVec2d* theWrappedObject)
{
  ( theWrappedObject->negate());
}

double  PythonQtWrapper_SbVec2d::normalize(SbVec2d* theWrappedObject)
{
  return ( theWrappedObject->normalize());
}

bool  PythonQtWrapper_SbVec2d::__ne__(SbVec2d* theWrappedObject, const SbVec2d&  v2)
{
  return ( (*theWrappedObject)!= v2);
}

SbVec2d  PythonQtWrapper_SbVec2d::__mul__(SbVec2d* theWrappedObject, double  d)
{
  return ( (*theWrappedObject)* d);
}

SbVec2d*  PythonQtWrapper_SbVec2d::__imul__(SbVec2d* theWrappedObject, double  d)
{
  return &( (*theWrappedObject)*= d);
}

SbVec2d  PythonQtWrapper_SbVec2d::__add__(SbVec2d* theWrappedObject, const SbVec2d&  v2)
{
  return ( (*theWrappedObject)+ v2);
}

SbVec2d*  PythonQtWrapper_SbVec2d::__iadd__(SbVec2d* theWrappedObject, const SbVec2d&  u)
{
  return &( (*theWrappedObject)+= u);
}

SbVec2d  PythonQtWrapper_SbVec2d::__sub__(SbVec2d* theWrappedObject) const
{
  return (-  (*theWrappedObject));
}

SbVec2d  PythonQtWrapper_SbVec2d::__sub__(SbVec2d* theWrappedObject, const SbVec2d&  v2)
{
  return ( (*theWrappedObject)- v2);
}

SbVec2d*  PythonQtWrapper_SbVec2d::__isub__(SbVec2d* theWrappedObject, const SbVec2d&  u)
{
  return &( (*theWrappedObject)-= u);
}

SbVec2d  PythonQtWrapper_SbVec2d::__div__(SbVec2d* theWrappedObject, double  d)
{
  return ( (*theWrappedObject)/ d);
}

SbVec2d*  PythonQtWrapper_SbVec2d::__idiv__(SbVec2d* theWrappedObject, double  d)
{
  return &( (*theWrappedObject)/= d);
}

bool  PythonQtWrapper_SbVec2d::__eq__(SbVec2d* theWrappedObject, const SbVec2d&  v2)
{
  return ( (*theWrappedObject)== v2);
}

SbVec2d*  PythonQtWrapper_SbVec2d::setValue(SbVec2d* theWrappedObject, double  x, double  y)
{
  return &( theWrappedObject->setValue(x, y));
}



PythonQtShell_SbVec2f::~PythonQtShell_SbVec2f() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SbVec2f* PythonQtWrapper_SbVec2f::new_SbVec2f()
{ 
return new PythonQtShell_SbVec2f(); }

SbVec2f* PythonQtWrapper_SbVec2f::new_SbVec2f(float  x, float  y)
{ 
return new PythonQtShell_SbVec2f(x, y); }

float  PythonQtWrapper_SbVec2f::dot(SbVec2f* theWrappedObject, const SbVec2f&  v) const
{
  return ( theWrappedObject->dot(v));
}

bool  PythonQtWrapper_SbVec2f::equals(SbVec2f* theWrappedObject, const SbVec2f  v, float  tolerance) const
{
  return ( theWrappedObject->equals(v, tolerance));
}

float  PythonQtWrapper_SbVec2f::length(SbVec2f* theWrappedObject) const
{
  return ( theWrappedObject->length());
}

void PythonQtWrapper_SbVec2f::negate(SbVec2f* theWrappedObject)
{
  ( theWrappedObject->negate());
}

float  PythonQtWrapper_SbVec2f::normalize(SbVec2f* theWrappedObject)
{
  return ( theWrappedObject->normalize());
}

bool  PythonQtWrapper_SbVec2f::__ne__(SbVec2f* theWrappedObject, const SbVec2f&  v2)
{
  return ( (*theWrappedObject)!= v2);
}

SbVec2f  PythonQtWrapper_SbVec2f::__mul__(SbVec2f* theWrappedObject, float  d)
{
  return ( (*theWrappedObject)* d);
}

SbVec2f*  PythonQtWrapper_SbVec2f::__imul__(SbVec2f* theWrappedObject, float  d)
{
  return &( (*theWrappedObject)*= d);
}

SbVec2f  PythonQtWrapper_SbVec2f::__add__(SbVec2f* theWrappedObject, const SbVec2f&  v2)
{
  return ( (*theWrappedObject)+ v2);
}

SbVec2f*  PythonQtWrapper_SbVec2f::__iadd__(SbVec2f* theWrappedObject, const SbVec2f&  u)
{
  return &( (*theWrappedObject)+= u);
}

SbVec2f  PythonQtWrapper_SbVec2f::__sub__(SbVec2f* theWrappedObject) const
{
  return (-  (*theWrappedObject));
}

SbVec2f  PythonQtWrapper_SbVec2f::__sub__(SbVec2f* theWrappedObject, const SbVec2f&  v2)
{
  return ( (*theWrappedObject)- v2);
}

SbVec2f*  PythonQtWrapper_SbVec2f::__isub__(SbVec2f* theWrappedObject, const SbVec2f&  u)
{
  return &( (*theWrappedObject)-= u);
}

SbVec2f  PythonQtWrapper_SbVec2f::__div__(SbVec2f* theWrappedObject, float  d)
{
  return ( (*theWrappedObject)/ d);
}

SbVec2f*  PythonQtWrapper_SbVec2f::__idiv__(SbVec2f* theWrappedObject, float  d)
{
  return &( (*theWrappedObject)/= d);
}

bool  PythonQtWrapper_SbVec2f::__eq__(SbVec2f* theWrappedObject, const SbVec2f&  v2)
{
  return ( (*theWrappedObject)== v2);
}

SbVec2f*  PythonQtWrapper_SbVec2f::setValue(SbVec2f* theWrappedObject, float  x, float  y)
{
  return &( theWrappedObject->setValue(x, y));
}



PythonQtShell_SbVec2s::~PythonQtShell_SbVec2s() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SbVec2s* PythonQtWrapper_SbVec2s::new_SbVec2s()
{ 
return new PythonQtShell_SbVec2s(); }

SbVec2s* PythonQtWrapper_SbVec2s::new_SbVec2s(short  x, short  y)
{ 
return new PythonQtShell_SbVec2s(x, y); }

int  PythonQtWrapper_SbVec2s::dot(SbVec2s* theWrappedObject, const SbVec2s&  v) const
{
  return ( theWrappedObject->dot(v));
}

void PythonQtWrapper_SbVec2s::negate(SbVec2s* theWrappedObject)
{
  ( theWrappedObject->negate());
}

bool  PythonQtWrapper_SbVec2s::__ne__(SbVec2s* theWrappedObject, const SbVec2s&  v2)
{
  return ( (*theWrappedObject)!= v2);
}

SbVec2s  PythonQtWrapper_SbVec2s::__mul__(SbVec2s* theWrappedObject, double  d)
{
  return ( (*theWrappedObject)* d);
}

SbVec2s  PythonQtWrapper_SbVec2s::__mul__(SbVec2s* theWrappedObject, int  d)
{
  return ( (*theWrappedObject)* d);
}

SbVec2s*  PythonQtWrapper_SbVec2s::__imul__(SbVec2s* theWrappedObject, double  d)
{
  return &( (*theWrappedObject)*= d);
}

SbVec2s*  PythonQtWrapper_SbVec2s::__imul__(SbVec2s* theWrappedObject, int  d)
{
  return &( (*theWrappedObject)*= d);
}

SbVec2s  PythonQtWrapper_SbVec2s::__add__(SbVec2s* theWrappedObject, const SbVec2s&  v2)
{
  return ( (*theWrappedObject)+ v2);
}

SbVec2s*  PythonQtWrapper_SbVec2s::__iadd__(SbVec2s* theWrappedObject, const SbVec2s&  u)
{
  return &( (*theWrappedObject)+= u);
}

SbVec2s  PythonQtWrapper_SbVec2s::__sub__(SbVec2s* theWrappedObject) const
{
  return (-  (*theWrappedObject));
}

SbVec2s  PythonQtWrapper_SbVec2s::__sub__(SbVec2s* theWrappedObject, const SbVec2s&  v2)
{
  return ( (*theWrappedObject)- v2);
}

SbVec2s*  PythonQtWrapper_SbVec2s::__isub__(SbVec2s* theWrappedObject, const SbVec2s&  u)
{
  return &( (*theWrappedObject)-= u);
}

SbVec2s  PythonQtWrapper_SbVec2s::__div__(SbVec2s* theWrappedObject, double  d)
{
  return ( (*theWrappedObject)/ d);
}

SbVec2s  PythonQtWrapper_SbVec2s::__div__(SbVec2s* theWrappedObject, int  d)
{
  return ( (*theWrappedObject)/ d);
}

SbVec2s*  PythonQtWrapper_SbVec2s::__idiv__(SbVec2s* theWrappedObject, double  d)
{
  return &( (*theWrappedObject)/= d);
}

SbVec2s*  PythonQtWrapper_SbVec2s::__idiv__(SbVec2s* theWrappedObject, int  d)
{
  return &( (*theWrappedObject)/= d);
}

bool  PythonQtWrapper_SbVec2s::__eq__(SbVec2s* theWrappedObject, const SbVec2s&  v2)
{
  return ( (*theWrappedObject)== v2);
}

SbVec2s*  PythonQtWrapper_SbVec2s::setValue(SbVec2s* theWrappedObject, short  x, short  y)
{
  return &( theWrappedObject->setValue(x, y));
}



PythonQtShell_SbVec3d::~PythonQtShell_SbVec3d() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SbVec3d* PythonQtWrapper_SbVec3d::new_SbVec3d()
{ 
return new PythonQtShell_SbVec3d(); }

SbVec3d* PythonQtWrapper_SbVec3d::new_SbVec3d(SbPlaned&  p0, SbPlaned&  p1, SbPlaned&  p2)
{ 
return new PythonQtShell_SbVec3d(p0, p1, p2); }

SbVec3d* PythonQtWrapper_SbVec3d::new_SbVec3d(double  x, double  y, double  z)
{ 
return new PythonQtShell_SbVec3d(x, y, z); }

SbVec3d  PythonQtWrapper_SbVec3d::cross(SbVec3d* theWrappedObject, const SbVec3d&  v) const
{
  return ( theWrappedObject->cross(v));
}

double  PythonQtWrapper_SbVec3d::dot(SbVec3d* theWrappedObject, const SbVec3d&  v) const
{
  return ( theWrappedObject->dot(v));
}

bool  PythonQtWrapper_SbVec3d::equals(SbVec3d* theWrappedObject, const SbVec3d  v, double  tolerance) const
{
  return ( theWrappedObject->equals(v, tolerance));
}

SbVec3d  PythonQtWrapper_SbVec3d::getClosestAxis(SbVec3d* theWrappedObject) const
{
  return ( theWrappedObject->getClosestAxis());
}

double  PythonQtWrapper_SbVec3d::length(SbVec3d* theWrappedObject) const
{
  return ( theWrappedObject->length());
}

void PythonQtWrapper_SbVec3d::negate(SbVec3d* theWrappedObject)
{
  ( theWrappedObject->negate());
}

double  PythonQtWrapper_SbVec3d::normalize(SbVec3d* theWrappedObject)
{
  return ( theWrappedObject->normalize());
}

bool  PythonQtWrapper_SbVec3d::__ne__(SbVec3d* theWrappedObject, const SbVec3d&  v2)
{
  return ( (*theWrappedObject)!= v2);
}

SbVec3d  PythonQtWrapper_SbVec3d::__mul__(SbVec3d* theWrappedObject, double  d)
{
  return ( (*theWrappedObject)* d);
}

SbVec3d*  PythonQtWrapper_SbVec3d::__imul__(SbVec3d* theWrappedObject, double  d)
{
  return &( (*theWrappedObject)*= d);
}

SbVec3d  PythonQtWrapper_SbVec3d::__add__(SbVec3d* theWrappedObject, const SbVec3d&  v2)
{
  return ( (*theWrappedObject)+ v2);
}

SbVec3d*  PythonQtWrapper_SbVec3d::__iadd__(SbVec3d* theWrappedObject, SbVec3d  v)
{
  return &( (*theWrappedObject)+= v);
}

SbVec3d  PythonQtWrapper_SbVec3d::__sub__(SbVec3d* theWrappedObject) const
{
  return (-  (*theWrappedObject));
}

SbVec3d  PythonQtWrapper_SbVec3d::__sub__(SbVec3d* theWrappedObject, const SbVec3d&  v2)
{
  return ( (*theWrappedObject)- v2);
}

SbVec3d*  PythonQtWrapper_SbVec3d::__isub__(SbVec3d* theWrappedObject, SbVec3d  v)
{
  return &( (*theWrappedObject)-= v);
}

SbVec3d  PythonQtWrapper_SbVec3d::__div__(SbVec3d* theWrappedObject, double  d)
{
  return ( (*theWrappedObject)/ d);
}

SbVec3d*  PythonQtWrapper_SbVec3d::__idiv__(SbVec3d* theWrappedObject, double  d)
{
  return &( (*theWrappedObject)/= d);
}

bool  PythonQtWrapper_SbVec3d::__eq__(SbVec3d* theWrappedObject, const SbVec3d&  v2)
{
  return ( (*theWrappedObject)== v2);
}

SbVec3d*  PythonQtWrapper_SbVec3d::setValue(SbVec3d* theWrappedObject, const SbVec3d&  barycentic, const SbVec3d&  v0, const SbVec3d&  v1, const SbVec3d&  v2)
{
  return &( theWrappedObject->setValue(barycentic, v0, v1, v2));
}

SbVec3d*  PythonQtWrapper_SbVec3d::setValue(SbVec3d* theWrappedObject, double  x, double  y, double  z)
{
  return &( theWrappedObject->setValue(x, y, z));
}



PythonQtShell_SbVec3f::~PythonQtShell_SbVec3f() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SbVec3f* PythonQtWrapper_SbVec3f::new_SbVec3f()
{ 
return new PythonQtShell_SbVec3f(); }

SbVec3f* PythonQtWrapper_SbVec3f::new_SbVec3f(SbPlane&  p0, SbPlane&  p1, SbPlane&  p2)
{ 
return new PythonQtShell_SbVec3f(p0, p1, p2); }

SbVec3f* PythonQtWrapper_SbVec3f::new_SbVec3f(float  x, float  y, float  z)
{ 
return new PythonQtShell_SbVec3f(x, y, z); }

SbVec3f  PythonQtWrapper_SbVec3f::cross(SbVec3f* theWrappedObject, const SbVec3f&  v) const
{
  return ( theWrappedObject->cross(v));
}

float  PythonQtWrapper_SbVec3f::dot(SbVec3f* theWrappedObject, const SbVec3f&  v) const
{
  return ( theWrappedObject->dot(v));
}

bool  PythonQtWrapper_SbVec3f::equals(SbVec3f* theWrappedObject, const SbVec3f  v, float  tolerance) const
{
  return ( theWrappedObject->equals(v, tolerance));
}

SbVec3f  PythonQtWrapper_SbVec3f::getClosestAxis(SbVec3f* theWrappedObject) const
{
  return ( theWrappedObject->getClosestAxis());
}

float  PythonQtWrapper_SbVec3f::length(SbVec3f* theWrappedObject) const
{
  return ( theWrappedObject->length());
}

void PythonQtWrapper_SbVec3f::negate(SbVec3f* theWrappedObject)
{
  ( theWrappedObject->negate());
}

float  PythonQtWrapper_SbVec3f::normalize(SbVec3f* theWrappedObject)
{
  return ( theWrappedObject->normalize());
}

bool  PythonQtWrapper_SbVec3f::__ne__(SbVec3f* theWrappedObject, const SbVec3f&  v2)
{
  return ( (*theWrappedObject)!= v2);
}

SbVec3f  PythonQtWrapper_SbVec3f::__mul__(SbVec3f* theWrappedObject, float  d)
{
  return ( (*theWrappedObject)* d);
}

SbVec3f*  PythonQtWrapper_SbVec3f::__imul__(SbVec3f* theWrappedObject, float  d)
{
  return &( (*theWrappedObject)*= d);
}

SbVec3f  PythonQtWrapper_SbVec3f::__add__(SbVec3f* theWrappedObject, const SbVec3f&  v2)
{
  return ( (*theWrappedObject)+ v2);
}

SbVec3f*  PythonQtWrapper_SbVec3f::__iadd__(SbVec3f* theWrappedObject, SbVec3f  v)
{
  return &( (*theWrappedObject)+= v);
}

SbVec3f  PythonQtWrapper_SbVec3f::__sub__(SbVec3f* theWrappedObject) const
{
  return (-  (*theWrappedObject));
}

SbVec3f  PythonQtWrapper_SbVec3f::__sub__(SbVec3f* theWrappedObject, const SbVec3f&  v2)
{
  return ( (*theWrappedObject)- v2);
}

SbVec3f*  PythonQtWrapper_SbVec3f::__isub__(SbVec3f* theWrappedObject, SbVec3f  v)
{
  return &( (*theWrappedObject)-= v);
}

SbVec3f  PythonQtWrapper_SbVec3f::__div__(SbVec3f* theWrappedObject, float  d)
{
  return ( (*theWrappedObject)/ d);
}

SbVec3f*  PythonQtWrapper_SbVec3f::__idiv__(SbVec3f* theWrappedObject, float  d)
{
  return &( (*theWrappedObject)/= d);
}

bool  PythonQtWrapper_SbVec3f::__eq__(SbVec3f* theWrappedObject, const SbVec3f&  v2)
{
  return ( (*theWrappedObject)== v2);
}

SbVec3f*  PythonQtWrapper_SbVec3f::setValue(SbVec3f* theWrappedObject, const SbVec3f&  barycentic, const SbVec3f&  v0, const SbVec3f&  v1, const SbVec3f&  v2)
{
  return &( theWrappedObject->setValue(barycentic, v0, v1, v2));
}

SbVec3f*  PythonQtWrapper_SbVec3f::setValue(SbVec3f* theWrappedObject, float  x, float  y, float  z)
{
  return &( theWrappedObject->setValue(x, y, z));
}



PythonQtShell_SbVec3s::~PythonQtShell_SbVec3s() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SbVec3s* PythonQtWrapper_SbVec3s::new_SbVec3s()
{ 
return new PythonQtShell_SbVec3s(); }

SbVec3s* PythonQtWrapper_SbVec3s::new_SbVec3s(short  x, short  y, short  z)
{ 
return new PythonQtShell_SbVec3s(x, y, z); }

int  PythonQtWrapper_SbVec3s::dot(SbVec3s* theWrappedObject, const SbVec3s&  v) const
{
  return ( theWrappedObject->dot(v));
}

void PythonQtWrapper_SbVec3s::negate(SbVec3s* theWrappedObject)
{
  ( theWrappedObject->negate());
}

bool  PythonQtWrapper_SbVec3s::__ne__(SbVec3s* theWrappedObject, const SbVec3s&  v2)
{
  return ( (*theWrappedObject)!= v2);
}

SbVec3s  PythonQtWrapper_SbVec3s::__mul__(SbVec3s* theWrappedObject, double  d)
{
  return ( (*theWrappedObject)* d);
}

SbVec3s  PythonQtWrapper_SbVec3s::__mul__(SbVec3s* theWrappedObject, int  d)
{
  return ( (*theWrappedObject)* d);
}

SbVec3s*  PythonQtWrapper_SbVec3s::__imul__(SbVec3s* theWrappedObject, double  d)
{
  return &( (*theWrappedObject)*= d);
}

SbVec3s*  PythonQtWrapper_SbVec3s::__imul__(SbVec3s* theWrappedObject, int  d)
{
  return &( (*theWrappedObject)*= d);
}

SbVec3s  PythonQtWrapper_SbVec3s::__add__(SbVec3s* theWrappedObject, const SbVec3s&  v2)
{
  return ( (*theWrappedObject)+ v2);
}

SbVec3s*  PythonQtWrapper_SbVec3s::__iadd__(SbVec3s* theWrappedObject, const SbVec3s&  u)
{
  return &( (*theWrappedObject)+= u);
}

SbVec3s  PythonQtWrapper_SbVec3s::__sub__(SbVec3s* theWrappedObject) const
{
  return (-  (*theWrappedObject));
}

SbVec3s  PythonQtWrapper_SbVec3s::__sub__(SbVec3s* theWrappedObject, const SbVec3s&  v2)
{
  return ( (*theWrappedObject)- v2);
}

SbVec3s*  PythonQtWrapper_SbVec3s::__isub__(SbVec3s* theWrappedObject, const SbVec3s&  u)
{
  return &( (*theWrappedObject)-= u);
}

SbVec3s  PythonQtWrapper_SbVec3s::__div__(SbVec3s* theWrappedObject, double  d)
{
  return ( (*theWrappedObject)/ d);
}

SbVec3s  PythonQtWrapper_SbVec3s::__div__(SbVec3s* theWrappedObject, int  d)
{
  return ( (*theWrappedObject)/ d);
}

SbVec3s*  PythonQtWrapper_SbVec3s::__idiv__(SbVec3s* theWrappedObject, double  d)
{
  return &( (*theWrappedObject)/= d);
}

SbVec3s*  PythonQtWrapper_SbVec3s::__idiv__(SbVec3s* theWrappedObject, int  d)
{
  return &( (*theWrappedObject)/= d);
}

bool  PythonQtWrapper_SbVec3s::__eq__(SbVec3s* theWrappedObject, const SbVec3s&  v2)
{
  return ( (*theWrappedObject)== v2);
}

SbVec3s*  PythonQtWrapper_SbVec3s::setValue(SbVec3s* theWrappedObject, short  x, short  y, short  z)
{
  return &( theWrappedObject->setValue(x, y, z));
}



PythonQtShell_SbVec4d::~PythonQtShell_SbVec4d() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SbVec4d* PythonQtWrapper_SbVec4d::new_SbVec4d()
{ 
return new PythonQtShell_SbVec4d(); }

SbVec4d* PythonQtWrapper_SbVec4d::new_SbVec4d(double  x, double  y, double  z, double  w)
{ 
return new PythonQtShell_SbVec4d(x, y, z, w); }

double  PythonQtWrapper_SbVec4d::dot(SbVec4d* theWrappedObject, const SbVec4d&  v) const
{
  return ( theWrappedObject->dot(v));
}

bool  PythonQtWrapper_SbVec4d::equals(SbVec4d* theWrappedObject, const SbVec4d  v, double  tolerance) const
{
  return ( theWrappedObject->equals(v, tolerance));
}

SbVec3d  PythonQtWrapper_SbVec4d::getReal(SbVec4d* theWrappedObject) const
{
  return ( theWrappedObject->getReal());
}

double  PythonQtWrapper_SbVec4d::length(SbVec4d* theWrappedObject) const
{
  return ( theWrappedObject->length());
}

void PythonQtWrapper_SbVec4d::negate(SbVec4d* theWrappedObject)
{
  ( theWrappedObject->negate());
}

double  PythonQtWrapper_SbVec4d::normalize(SbVec4d* theWrappedObject)
{
  return ( theWrappedObject->normalize());
}

bool  PythonQtWrapper_SbVec4d::__ne__(SbVec4d* theWrappedObject, const SbVec4d&  v2)
{
  return ( (*theWrappedObject)!= v2);
}

SbVec4d  PythonQtWrapper_SbVec4d::__mul__(SbVec4d* theWrappedObject, double  d)
{
  return ( (*theWrappedObject)* d);
}

SbVec4d*  PythonQtWrapper_SbVec4d::__imul__(SbVec4d* theWrappedObject, double  d)
{
  return &( (*theWrappedObject)*= d);
}

SbVec4d  PythonQtWrapper_SbVec4d::__add__(SbVec4d* theWrappedObject, const SbVec4d&  v2)
{
  return ( (*theWrappedObject)+ v2);
}

SbVec4d*  PythonQtWrapper_SbVec4d::__iadd__(SbVec4d* theWrappedObject, const SbVec4d&  u)
{
  return &( (*theWrappedObject)+= u);
}

SbVec4d  PythonQtWrapper_SbVec4d::__sub__(SbVec4d* theWrappedObject) const
{
  return (-  (*theWrappedObject));
}

SbVec4d  PythonQtWrapper_SbVec4d::__sub__(SbVec4d* theWrappedObject, const SbVec4d&  v2)
{
  return ( (*theWrappedObject)- v2);
}

SbVec4d*  PythonQtWrapper_SbVec4d::__isub__(SbVec4d* theWrappedObject, const SbVec4d&  u)
{
  return &( (*theWrappedObject)-= u);
}

SbVec4d  PythonQtWrapper_SbVec4d::__div__(SbVec4d* theWrappedObject, double  d)
{
  return ( (*theWrappedObject)/ d);
}

SbVec4d*  PythonQtWrapper_SbVec4d::__idiv__(SbVec4d* theWrappedObject, double  d)
{
  return &( (*theWrappedObject)/= d);
}

bool  PythonQtWrapper_SbVec4d::__eq__(SbVec4d* theWrappedObject, const SbVec4d&  v2)
{
  return ( (*theWrappedObject)== v2);
}

SbVec4d*  PythonQtWrapper_SbVec4d::setValue(SbVec4d* theWrappedObject, double  x, double  y, double  z, double  w)
{
  return &( theWrappedObject->setValue(x, y, z, w));
}



PythonQtShell_SbVec4f::~PythonQtShell_SbVec4f() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SbVec4f* PythonQtWrapper_SbVec4f::new_SbVec4f()
{ 
return new PythonQtShell_SbVec4f(); }

SbVec4f* PythonQtWrapper_SbVec4f::new_SbVec4f(float  x, float  y, float  z, float  w)
{ 
return new PythonQtShell_SbVec4f(x, y, z, w); }

float  PythonQtWrapper_SbVec4f::dot(SbVec4f* theWrappedObject, const SbVec4f&  v) const
{
  return ( theWrappedObject->dot(v));
}

bool  PythonQtWrapper_SbVec4f::equals(SbVec4f* theWrappedObject, const SbVec4f  v, float  tolerance) const
{
  return ( theWrappedObject->equals(v, tolerance));
}

SbVec3f  PythonQtWrapper_SbVec4f::getReal(SbVec4f* theWrappedObject) const
{
  return ( theWrappedObject->getReal());
}

float  PythonQtWrapper_SbVec4f::length(SbVec4f* theWrappedObject) const
{
  return ( theWrappedObject->length());
}

void PythonQtWrapper_SbVec4f::negate(SbVec4f* theWrappedObject)
{
  ( theWrappedObject->negate());
}

float  PythonQtWrapper_SbVec4f::normalize(SbVec4f* theWrappedObject)
{
  return ( theWrappedObject->normalize());
}

bool  PythonQtWrapper_SbVec4f::__ne__(SbVec4f* theWrappedObject, const SbVec4f&  v2)
{
  return ( (*theWrappedObject)!= v2);
}

SbVec4f  PythonQtWrapper_SbVec4f::__mul__(SbVec4f* theWrappedObject, float  d)
{
  return ( (*theWrappedObject)* d);
}

SbVec4f*  PythonQtWrapper_SbVec4f::__imul__(SbVec4f* theWrappedObject, float  d)
{
  return &( (*theWrappedObject)*= d);
}

SbVec4f  PythonQtWrapper_SbVec4f::__add__(SbVec4f* theWrappedObject, const SbVec4f&  v2)
{
  return ( (*theWrappedObject)+ v2);
}

SbVec4f*  PythonQtWrapper_SbVec4f::__iadd__(SbVec4f* theWrappedObject, const SbVec4f&  u)
{
  return &( (*theWrappedObject)+= u);
}

SbVec4f  PythonQtWrapper_SbVec4f::__sub__(SbVec4f* theWrappedObject) const
{
  return (-  (*theWrappedObject));
}

SbVec4f  PythonQtWrapper_SbVec4f::__sub__(SbVec4f* theWrappedObject, const SbVec4f&  v2)
{
  return ( (*theWrappedObject)- v2);
}

SbVec4f*  PythonQtWrapper_SbVec4f::__isub__(SbVec4f* theWrappedObject, const SbVec4f&  u)
{
  return &( (*theWrappedObject)-= u);
}

SbVec4f  PythonQtWrapper_SbVec4f::__div__(SbVec4f* theWrappedObject, float  d)
{
  return ( (*theWrappedObject)/ d);
}

SbVec4f*  PythonQtWrapper_SbVec4f::__idiv__(SbVec4f* theWrappedObject, float  d)
{
  return &( (*theWrappedObject)/= d);
}

bool  PythonQtWrapper_SbVec4f::__eq__(SbVec4f* theWrappedObject, const SbVec4f&  v2)
{
  return ( (*theWrappedObject)== v2);
}

SbVec4f*  PythonQtWrapper_SbVec4f::setValue(SbVec4f* theWrappedObject, float  x, float  y, float  z, float  w)
{
  return &( theWrappedObject->setValue(x, y, z, w));
}



PythonQtShell_SbViewVolume::~PythonQtShell_SbViewVolume() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SbViewVolume* PythonQtWrapper_SbViewVolume::new_SbViewVolume()
{ 
return new PythonQtShell_SbViewVolume(); }

SbRotation  PythonQtWrapper_SbViewVolume::getAlignRotation(SbViewVolume* theWrappedObject, bool  rightAngleOnly) const
{
  return ( theWrappedObject->getAlignRotation(rightAngleOnly));
}

SbMatrix  PythonQtWrapper_SbViewVolume::getCameraSpaceMatrix(SbViewVolume* theWrappedObject) const
{
  return ( theWrappedObject->getCameraSpaceMatrix());
}

float  PythonQtWrapper_SbViewVolume::getDepth(SbViewVolume* theWrappedObject) const
{
  return ( theWrappedObject->getDepth());
}

float  PythonQtWrapper_SbViewVolume::getFarDist(SbViewVolume* theWrappedObject) const
{
  return ( theWrappedObject->getFarDist());
}

float  PythonQtWrapper_SbViewVolume::getHeight(SbViewVolume* theWrappedObject) const
{
  return ( theWrappedObject->getHeight());
}

SbMatrix  PythonQtWrapper_SbViewVolume::getMatrix(SbViewVolume* theWrappedObject) const
{
  return ( theWrappedObject->getMatrix());
}

float  PythonQtWrapper_SbViewVolume::getNearDist(SbViewVolume* theWrappedObject) const
{
  return ( theWrappedObject->getNearDist());
}

SbPlane  PythonQtWrapper_SbViewVolume::getPlane(SbViewVolume* theWrappedObject, float  distFromEye) const
{
  return ( theWrappedObject->getPlane(distFromEye));
}

SbVec3f  PythonQtWrapper_SbViewVolume::getPlanePoint(SbViewVolume* theWrappedObject, float  distFromEye, const SbVec2f&  normPoint) const
{
  return ( theWrappedObject->getPlanePoint(distFromEye, normPoint));
}

const SbVec3f*  PythonQtWrapper_SbViewVolume::getProjectionDirection(SbViewVolume* theWrappedObject) const
{
  return &( theWrappedObject->getProjectionDirection());
}

SbMatrix  PythonQtWrapper_SbViewVolume::getProjectionMatrix(SbViewVolume* theWrappedObject) const
{
  return ( theWrappedObject->getProjectionMatrix());
}

const SbVec3f*  PythonQtWrapper_SbViewVolume::getProjectionPoint(SbViewVolume* theWrappedObject) const
{
  return &( theWrappedObject->getProjectionPoint());
}

SbViewVolume::ProjectionType  PythonQtWrapper_SbViewVolume::getProjectionType(SbViewVolume* theWrappedObject) const
{
  return ( theWrappedObject->getProjectionType());
}

SbVec3f  PythonQtWrapper_SbViewVolume::getSightPoint(SbViewVolume* theWrappedObject, float  distFromEye) const
{
  return ( theWrappedObject->getSightPoint(distFromEye));
}

SbMatrix  PythonQtWrapper_SbViewVolume::getViewingMatrix(SbViewVolume* theWrappedObject) const
{
  return ( theWrappedObject->getViewingMatrix());
}

float  PythonQtWrapper_SbViewVolume::getWidth(SbViewVolume* theWrappedObject) const
{
  return ( theWrappedObject->getWidth());
}

float  PythonQtWrapper_SbViewVolume::getWorldToScreenScale(SbViewVolume* theWrappedObject, const SbVec3f&  worldCenter, float  normRadius) const
{
  return ( theWrappedObject->getWorldToScreenScale(worldCenter, normRadius));
}

bool  PythonQtWrapper_SbViewVolume::intersect(SbViewVolume* theWrappedObject, const SbBox3f&  box) const
{
  return ( theWrappedObject->intersect(box));
}

bool  PythonQtWrapper_SbViewVolume::intersect(SbViewVolume* theWrappedObject, const SbVec3f&  point) const
{
  return ( theWrappedObject->intersect(point));
}

SbViewVolume  PythonQtWrapper_SbViewVolume::narrow(SbViewVolume* theWrappedObject, const SbBox3f&  box) const
{
  return ( theWrappedObject->narrow(box));
}

SbViewVolume  PythonQtWrapper_SbViewVolume::narrow(SbViewVolume* theWrappedObject, float  left, float  bottom, float  right, float  top) const
{
  return ( theWrappedObject->narrow(left, bottom, right, top));
}

void PythonQtWrapper_SbViewVolume::ortho(SbViewVolume* theWrappedObject, float  left, float  right, float  bottom, float  top, float  nearVal, float  farVal)
{
  ( theWrappedObject->ortho(left, right, bottom, top, nearVal, farVal));
}

bool  PythonQtWrapper_SbViewVolume::outsideTest(SbViewVolume* theWrappedObject, const SbPlane&  p, const SbVec3f&  min, const SbVec3f&  max) const
{
  return ( theWrappedObject->outsideTest(p, min, max));
}

void PythonQtWrapper_SbViewVolume::perspective(SbViewVolume* theWrappedObject, float  fovy, float  aspect, float  nearVal, float  farVal)
{
  ( theWrappedObject->perspective(fovy, aspect, nearVal, farVal));
}

SbVec2f  PythonQtWrapper_SbViewVolume::projectBox(SbViewVolume* theWrappedObject, const SbBox3f&  box) const
{
  return ( theWrappedObject->projectBox(box));
}

SbLine  PythonQtWrapper_SbViewVolume::projectPointToLine(SbViewVolume* theWrappedObject, const SbVec2f&  pt) const
{
  return ( theWrappedObject->projectPointToLine(pt));
}

SbVec3f  PythonQtWrapper_SbViewVolume::projectToScreen(SbViewVolume* theWrappedObject, const SbVec3f&  src) const
{
  return ( theWrappedObject->projectToScreen(src));
}

void PythonQtWrapper_SbViewVolume::rotateCamera(SbViewVolume* theWrappedObject, const SbRotation&  q)
{
  ( theWrappedObject->rotateCamera(q));
}

void PythonQtWrapper_SbViewVolume::scale(SbViewVolume* theWrappedObject, float  factor)
{
  ( theWrappedObject->scale(factor));
}

void PythonQtWrapper_SbViewVolume::scaleHeight(SbViewVolume* theWrappedObject, float  ratio)
{
  ( theWrappedObject->scaleHeight(ratio));
}

void PythonQtWrapper_SbViewVolume::scaleWidth(SbViewVolume* theWrappedObject, float  ratio)
{
  ( theWrappedObject->scaleWidth(ratio));
}

void PythonQtWrapper_SbViewVolume::transform(SbViewVolume* theWrappedObject, const SbMatrix&  matrix)
{
  ( theWrappedObject->transform(matrix));
}

void PythonQtWrapper_SbViewVolume::translateCamera(SbViewVolume* theWrappedObject, const SbVec3f&  v)
{
  ( theWrappedObject->translateCamera(v));
}

SbViewVolume  PythonQtWrapper_SbViewVolume::zNarrow(SbViewVolume* theWrappedObject, float  nearVal, float  farVal) const
{
  return ( theWrappedObject->zNarrow(nearVal, farVal));
}

SbVec3f  PythonQtWrapper_SbViewVolume::zVector(SbViewVolume* theWrappedObject) const
{
  return ( theWrappedObject->zVector());
}



SbViewportRegion* PythonQtWrapper_SbViewportRegion::new_SbViewportRegion()
{ 
return new SbViewportRegion(); }

SbViewportRegion* PythonQtWrapper_SbViewportRegion::new_SbViewportRegion(SbVec2s  winSize)
{ 
return new SbViewportRegion(winSize); }

SbViewportRegion* PythonQtWrapper_SbViewportRegion::new_SbViewportRegion(const SbViewportRegion&  vpReg)
{ 
return new SbViewportRegion(vpReg); }

SbViewportRegion* PythonQtWrapper_SbViewportRegion::new_SbViewportRegion(short  width, short  height)
{ 
return new SbViewportRegion(width, height); }

float  PythonQtWrapper_SbViewportRegion::getPixelsPerInch(SbViewportRegion* theWrappedObject) const
{
  return ( theWrappedObject->getPixelsPerInch());
}

float  PythonQtWrapper_SbViewportRegion::getPixelsPerPoint(SbViewportRegion* theWrappedObject) const
{
  return ( theWrappedObject->getPixelsPerPoint());
}

float  PythonQtWrapper_SbViewportRegion::getViewportAspectRatio(SbViewportRegion* theWrappedObject) const
{
  return ( theWrappedObject->getViewportAspectRatio());
}

const SbVec2f*  PythonQtWrapper_SbViewportRegion::getViewportOrigin(SbViewportRegion* theWrappedObject) const
{
  return &( theWrappedObject->getViewportOrigin());
}

const SbVec2s*  PythonQtWrapper_SbViewportRegion::getViewportOriginPixels(SbViewportRegion* theWrappedObject) const
{
  return &( theWrappedObject->getViewportOriginPixels());
}

const SbVec2f*  PythonQtWrapper_SbViewportRegion::getViewportSize(SbViewportRegion* theWrappedObject) const
{
  return &( theWrappedObject->getViewportSize());
}

const SbVec2s*  PythonQtWrapper_SbViewportRegion::getViewportSizePixels(SbViewportRegion* theWrappedObject) const
{
  return &( theWrappedObject->getViewportSizePixels());
}

const SbVec2s*  PythonQtWrapper_SbViewportRegion::getWindowSize(SbViewportRegion* theWrappedObject) const
{
  return &( theWrappedObject->getWindowSize());
}

bool  PythonQtWrapper_SbViewportRegion::__eq__(SbViewportRegion* theWrappedObject, const SbViewportRegion&  reg2)
{
  return ( (*theWrappedObject)== reg2);
}

void PythonQtWrapper_SbViewportRegion::scaleHeight(SbViewportRegion* theWrappedObject, float  ratio)
{
  ( theWrappedObject->scaleHeight(ratio));
}

void PythonQtWrapper_SbViewportRegion::scaleWidth(SbViewportRegion* theWrappedObject, float  ratio)
{
  ( theWrappedObject->scaleWidth(ratio));
}

void PythonQtWrapper_SbViewportRegion::setPixelsPerInch(SbViewportRegion* theWrappedObject, float  ppi)
{
  ( theWrappedObject->setPixelsPerInch(ppi));
}

void PythonQtWrapper_SbViewportRegion::setViewport(SbViewportRegion* theWrappedObject, SbVec2f  origin, SbVec2f  size)
{
  ( theWrappedObject->setViewport(origin, size));
}

void PythonQtWrapper_SbViewportRegion::setViewport(SbViewportRegion* theWrappedObject, float  left, float  bottom, float  width, float  height)
{
  ( theWrappedObject->setViewport(left, bottom, width, height));
}

void PythonQtWrapper_SbViewportRegion::setViewportPixels(SbViewportRegion* theWrappedObject, SbVec2s  origin, SbVec2s  size)
{
  ( theWrappedObject->setViewportPixels(origin, size));
}

void PythonQtWrapper_SbViewportRegion::setViewportPixels(SbViewportRegion* theWrappedObject, short  left, short  bottom, short  width, short  height)
{
  ( theWrappedObject->setViewportPixels(left, bottom, width, height));
}

void PythonQtWrapper_SbViewportRegion::setWindowSize(SbViewportRegion* theWrappedObject, SbVec2s  winSize)
{
  ( theWrappedObject->setWindowSize(winSize));
}

void PythonQtWrapper_SbViewportRegion::setWindowSize(SbViewportRegion* theWrappedObject, short  width, short  height)
{
  ( theWrappedObject->setWindowSize(width, height));
}



SbXfBox3d* PythonQtWrapper_SbXfBox3d::new_SbXfBox3d()
{ 
return new SbXfBox3d(); }

SbXfBox3d* PythonQtWrapper_SbXfBox3d::new_SbXfBox3d(const SbBox3d&  box)
{ 
return new SbXfBox3d(box); }

SbXfBox3d* PythonQtWrapper_SbXfBox3d::new_SbXfBox3d(const SbVec3d&  _min, const SbVec3d&  _max)
{ 
return new SbXfBox3d(_min, _max); }

void PythonQtWrapper_SbXfBox3d::extendBy(SbXfBox3d* theWrappedObject, const SbBox3d&  bb)
{
  ( theWrappedObject->extendBy(bb));
}

void PythonQtWrapper_SbXfBox3d::extendBy(SbXfBox3d* theWrappedObject, const SbVec3d&  pt)
{
  ( theWrappedObject->extendBy(pt));
}

void PythonQtWrapper_SbXfBox3d::extendBy(SbXfBox3d* theWrappedObject, const SbXfBox3d&  bb)
{
  ( theWrappedObject->extendBy(bb));
}

SbVec3d  PythonQtWrapper_SbXfBox3d::getCenter(SbXfBox3d* theWrappedObject) const
{
  return ( theWrappedObject->getCenter());
}

const SbMatrixd*  PythonQtWrapper_SbXfBox3d::getInverse(SbXfBox3d* theWrappedObject) const
{
  return &( theWrappedObject->getInverse());
}

const SbMatrixd*  PythonQtWrapper_SbXfBox3d::getTransform(SbXfBox3d* theWrappedObject) const
{
  return &( theWrappedObject->getTransform());
}

double  PythonQtWrapper_SbXfBox3d::getVolume(SbXfBox3d* theWrappedObject) const
{
  return ( theWrappedObject->getVolume());
}

bool  PythonQtWrapper_SbXfBox3d::hasVolume(SbXfBox3d* theWrappedObject) const
{
  return ( theWrappedObject->hasVolume());
}

bool  PythonQtWrapper_SbXfBox3d::intersect(SbXfBox3d* theWrappedObject, const SbBox3d&  bb) const
{
  return ( theWrappedObject->intersect(bb));
}

bool  PythonQtWrapper_SbXfBox3d::intersect(SbXfBox3d* theWrappedObject, const SbVec3d&  pt) const
{
  return ( theWrappedObject->intersect(pt));
}

bool  PythonQtWrapper_SbXfBox3d::isEmpty(SbXfBox3d* theWrappedObject) const
{
  return ( theWrappedObject->isEmpty());
}

void PythonQtWrapper_SbXfBox3d::makeEmpty(SbXfBox3d* theWrappedObject)
{
  ( theWrappedObject->makeEmpty());
}

bool  PythonQtWrapper_SbXfBox3d::__ne__(SbXfBox3d* theWrappedObject, const SbXfBox3d&  b2)
{
  return ( (*theWrappedObject)!= b2);
}

bool  PythonQtWrapper_SbXfBox3d::__eq__(SbXfBox3d* theWrappedObject, const SbXfBox3d&  b2)
{
  return ( (*theWrappedObject)== b2);
}

SbBox3d  PythonQtWrapper_SbXfBox3d::project(SbXfBox3d* theWrappedObject) const
{
  return ( theWrappedObject->project());
}

void PythonQtWrapper_SbXfBox3d::setBounds(SbXfBox3d* theWrappedObject, const SbVec3d&  _min, const SbVec3d&  _max)
{
  ( theWrappedObject->setBounds(_min, _max));
}

void PythonQtWrapper_SbXfBox3d::setBounds(SbXfBox3d* theWrappedObject, double  xmin, double  ymin, double  zmin, double  xmax, double  ymax, double  zmax)
{
  ( theWrappedObject->setBounds(xmin, ymin, zmin, xmax, ymax, zmax));
}

void PythonQtWrapper_SbXfBox3d::setTransform(SbXfBox3d* theWrappedObject, const SbMatrixd&  m)
{
  ( theWrappedObject->setTransform(m));
}

void PythonQtWrapper_SbXfBox3d::transform(SbXfBox3d* theWrappedObject, const SbMatrixd&  m)
{
  ( theWrappedObject->transform(m));
}



SbXfBox3f* PythonQtWrapper_SbXfBox3f::new_SbXfBox3f()
{ 
return new SbXfBox3f(); }

SbXfBox3f* PythonQtWrapper_SbXfBox3f::new_SbXfBox3f(const SbBox3f&  box)
{ 
return new SbXfBox3f(box); }

SbXfBox3f* PythonQtWrapper_SbXfBox3f::new_SbXfBox3f(const SbVec3f&  _min, const SbVec3f&  _max)
{ 
return new SbXfBox3f(_min, _max); }

void PythonQtWrapper_SbXfBox3f::extendBy(SbXfBox3f* theWrappedObject, const SbBox3f&  bb)
{
  ( theWrappedObject->extendBy(bb));
}

void PythonQtWrapper_SbXfBox3f::extendBy(SbXfBox3f* theWrappedObject, const SbVec3f&  pt)
{
  ( theWrappedObject->extendBy(pt));
}

void PythonQtWrapper_SbXfBox3f::extendBy(SbXfBox3f* theWrappedObject, const SbXfBox3f&  bb)
{
  ( theWrappedObject->extendBy(bb));
}

SbVec3f  PythonQtWrapper_SbXfBox3f::getCenter(SbXfBox3f* theWrappedObject) const
{
  return ( theWrappedObject->getCenter());
}

const SbMatrix*  PythonQtWrapper_SbXfBox3f::getInverse(SbXfBox3f* theWrappedObject) const
{
  return &( theWrappedObject->getInverse());
}

const SbMatrix*  PythonQtWrapper_SbXfBox3f::getTransform(SbXfBox3f* theWrappedObject) const
{
  return &( theWrappedObject->getTransform());
}

float  PythonQtWrapper_SbXfBox3f::getVolume(SbXfBox3f* theWrappedObject) const
{
  return ( theWrappedObject->getVolume());
}

bool  PythonQtWrapper_SbXfBox3f::hasVolume(SbXfBox3f* theWrappedObject) const
{
  return ( theWrappedObject->hasVolume());
}

bool  PythonQtWrapper_SbXfBox3f::intersect(SbXfBox3f* theWrappedObject, const SbBox3f&  bb) const
{
  return ( theWrappedObject->intersect(bb));
}

bool  PythonQtWrapper_SbXfBox3f::intersect(SbXfBox3f* theWrappedObject, const SbVec3f&  pt) const
{
  return ( theWrappedObject->intersect(pt));
}

bool  PythonQtWrapper_SbXfBox3f::isEmpty(SbXfBox3f* theWrappedObject) const
{
  return ( theWrappedObject->isEmpty());
}

void PythonQtWrapper_SbXfBox3f::makeEmpty(SbXfBox3f* theWrappedObject)
{
  ( theWrappedObject->makeEmpty());
}

bool  PythonQtWrapper_SbXfBox3f::__ne__(SbXfBox3f* theWrappedObject, const SbXfBox3f&  b2)
{
  return ( (*theWrappedObject)!= b2);
}

bool  PythonQtWrapper_SbXfBox3f::__eq__(SbXfBox3f* theWrappedObject, const SbXfBox3f&  b2)
{
  return ( (*theWrappedObject)== b2);
}

SbBox3f  PythonQtWrapper_SbXfBox3f::project(SbXfBox3f* theWrappedObject) const
{
  return ( theWrappedObject->project());
}

void PythonQtWrapper_SbXfBox3f::setBounds(SbXfBox3f* theWrappedObject, const SbVec3f&  _min, const SbVec3f&  _max)
{
  ( theWrappedObject->setBounds(_min, _max));
}

void PythonQtWrapper_SbXfBox3f::setBounds(SbXfBox3f* theWrappedObject, float  xmin, float  ymin, float  zmin, float  xmax, float  ymax, float  zmax)
{
  ( theWrappedObject->setBounds(xmin, ymin, zmin, xmax, ymax, zmax));
}

void PythonQtWrapper_SbXfBox3f::setTransform(SbXfBox3f* theWrappedObject, const SbMatrix&  m)
{
  ( theWrappedObject->setTransform(m));
}

void PythonQtWrapper_SbXfBox3f::transform(SbXfBox3f* theWrappedObject, const SbMatrix&  m)
{
  ( theWrappedObject->transform(m));
}



SoType  PythonQtWrapper_SoBase::static_SoBase_getClassTypeId()
{
  return (SoBase::getClassTypeId());
}

SbName  PythonQtWrapper_SoBase::getName(SoBase* theWrappedObject) const
{
  return ( theWrappedObject->getName());
}

int  PythonQtWrapper_SoBase::getRefCount(SoBase* theWrappedObject) const
{
  return ( theWrappedObject->getRefCount());
}

bool  PythonQtWrapper_SoBase::isOfType(SoBase* theWrappedObject, SoType  type) const
{
  return ( theWrappedObject->isOfType(type));
}

void PythonQtWrapper_SoBase::setName(SoBase* theWrappedObject, const SbName&  name)
{
  ( theWrappedObject->setName(name));
}

void PythonQtWrapper_SoBase::startNotify(SoBase* theWrappedObject)
{
  ( theWrappedObject->startNotify());
}

void PythonQtWrapper_SoBase::touch(SoBase* theWrappedObject)
{
  ( theWrappedObject->touch());
}



PythonQtShell_SoDB::~PythonQtShell_SoDB() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SoDB* PythonQtWrapper_SoDB::new_SoDB()
{ 
return new PythonQtShell_SoDB(); }

void PythonQtWrapper_SoDB::static_SoDB_addConverter(SoType  fromField, SoType  toField, SoType  converterEngine)
{
  (SoDB::addConverter(fromField, toField, converterEngine));
}

SoField*  PythonQtWrapper_SoDB::static_SoDB_createGlobalField(const SbName&  name, SoType  type)
{
  return (SoDB::createGlobalField(name, type));
}

void PythonQtWrapper_SoDB::static_SoDB_enableRealTimeSensor(bool  enable)
{
  (SoDB::enableRealTimeSensor(enable));
}

void PythonQtWrapper_SoDB::static_SoDB_endNotify()
{
  (SoDB::endNotify());
}

SoType  PythonQtWrapper_SoDB::static_SoDB_getConverter(SoType  fromField, SoType  toField)
{
  return (SoDB::getConverter(fromField, toField));
}

const SbTime*  PythonQtWrapper_SoDB::static_SoDB_getDelaySensorTimeout()
{
  return &(SoDB::getDelaySensorTimeout());
}

SoField*  PythonQtWrapper_SoDB::static_SoDB_getGlobalField(const SbName&  name)
{
  return (SoDB::getGlobalField(name));
}

SbString  PythonQtWrapper_SoDB::static_SoDB_getHeaderString(int  i)
{
  return (SoDB::getHeaderString(i));
}

int  PythonQtWrapper_SoDB::static_SoDB_getNumHeaders()
{
  return (SoDB::getNumHeaders());
}

const SbTime*  PythonQtWrapper_SoDB::static_SoDB_getRealTimeInterval()
{
  return &(SoDB::getRealTimeInterval());
}

const char*  PythonQtWrapper_SoDB::static_SoDB_getVersion()
{
  return (SoDB::getVersion());
}

void PythonQtWrapper_SoDB::static_SoDB_init()
{
  (SoDB::init());
}

bool  PythonQtWrapper_SoDB::static_SoDB_isInitialized()
{
  return (SoDB::isInitialized());
}

bool  PythonQtWrapper_SoDB::static_SoDB_isNotifying()
{
  return (SoDB::isNotifying());
}

bool  PythonQtWrapper_SoDB::static_SoDB_isValidHeader(const char*  testString)
{
  return (SoDB::isValidHeader(testString));
}

SoSeparator*  PythonQtWrapper_SoDB::static_SoDB_readAll(SoInput*  in)
{
  return (SoDB::readAll(in));
}

void PythonQtWrapper_SoDB::static_SoDB_renameGlobalField(const SbName&  oldName, const SbName&  newName)
{
  (SoDB::renameGlobalField(oldName, newName));
}

void PythonQtWrapper_SoDB::static_SoDB_setDelaySensorTimeout(const SbTime&  t)
{
  (SoDB::setDelaySensorTimeout(t));
}

void PythonQtWrapper_SoDB::static_SoDB_setRealTimeInterval(const SbTime&  deltaT)
{
  (SoDB::setRealTimeInterval(deltaT));
}

void PythonQtWrapper_SoDB::static_SoDB_startNotify()
{
  (SoDB::startNotify());
}



SoInput* PythonQtWrapper_SoInput::new_SoInput()
{ 
return new SoInput(); }

SoInput* PythonQtWrapper_SoInput::new_SoInput(SoInput*  dictIn)
{ 
return new SoInput(dictIn); }

void PythonQtWrapper_SoInput::static_SoInput_addDirectoryFirst(const char*  dirName)
{
  (SoInput::addDirectoryFirst(dirName));
}

void PythonQtWrapper_SoInput::static_SoInput_addDirectoryLast(const char*  dirName)
{
  (SoInput::addDirectoryLast(dirName));
}

void PythonQtWrapper_SoInput::static_SoInput_addEnvDirectoriesFirst(const char*  envVarName)
{
  (SoInput::addEnvDirectoriesFirst(envVarName));
}

void PythonQtWrapper_SoInput::static_SoInput_addEnvDirectoriesLast(const char*  envVarName)
{
  (SoInput::addEnvDirectoriesLast(envVarName));
}

void PythonQtWrapper_SoInput::addReference(SoInput* theWrappedObject, const SbName&  name, SoBase*  base, bool  addToGlobalDict)
{
  ( theWrappedObject->addReference(name, base, addToGlobalDict));
}

void PythonQtWrapper_SoInput::static_SoInput_clearDirectories()
{
  (SoInput::clearDirectories());
}

void PythonQtWrapper_SoInput::closeFile(SoInput* theWrappedObject)
{
  ( theWrappedObject->closeFile());
}

bool  PythonQtWrapper_SoInput::eof(SoInput* theWrappedObject) const
{
  return ( theWrappedObject->eof());
}

SoBase*  PythonQtWrapper_SoInput::findReference(SoInput* theWrappedObject, const SbName&  name) const
{
  return ( theWrappedObject->findReference(name));
}

const char*  PythonQtWrapper_SoInput::getCurFileName(SoInput* theWrappedObject) const
{
  return ( theWrappedObject->getCurFileName());
}

SbString  PythonQtWrapper_SoInput::getHeader(SoInput* theWrappedObject)
{
  return ( theWrappedObject->getHeader());
}

float  PythonQtWrapper_SoInput::getIVVersion(SoInput* theWrappedObject)
{
  return ( theWrappedObject->getIVVersion());
}

size_t  PythonQtWrapper_SoInput::getNumBytesRead(SoInput* theWrappedObject) const
{
  return ( theWrappedObject->getNumBytesRead());
}

void PythonQtWrapper_SoInput::static_SoInput_init()
{
  (SoInput::init());
}

bool  PythonQtWrapper_SoInput::isBinary(SoInput* theWrappedObject)
{
  return ( theWrappedObject->isBinary());
}

bool  PythonQtWrapper_SoInput::isValidFile(SoInput* theWrappedObject)
{
  return ( theWrappedObject->isValidFile());
}

bool  PythonQtWrapper_SoInput::openFile(SoInput* theWrappedObject, const char*  fileName, bool  okIfNotFound)
{
  return ( theWrappedObject->openFile(fileName, okIfNotFound));
}

bool  PythonQtWrapper_SoInput::pushFile(SoInput* theWrappedObject, const char*  fileName)
{
  return ( theWrappedObject->pushFile(fileName));
}

void PythonQtWrapper_SoInput::putBack(SoInput* theWrappedObject, char  c)
{
  ( theWrappedObject->putBack(c));
}

void PythonQtWrapper_SoInput::putBack(SoInput* theWrappedObject, const char*  string)
{
  ( theWrappedObject->putBack(string));
}

bool  PythonQtWrapper_SoInput::readBinaryArray(SoInput* theWrappedObject, double*  d, int  length)
{
  return ( theWrappedObject->readBinaryArray(d, length));
}

bool  PythonQtWrapper_SoInput::readBinaryArray(SoInput* theWrappedObject, float*  f, int  length)
{
  return ( theWrappedObject->readBinaryArray(f, length));
}

bool  PythonQtWrapper_SoInput::readBinaryArray(SoInput* theWrappedObject, int*  l, int  length)
{
  return ( theWrappedObject->readBinaryArray(l, length));
}

bool  PythonQtWrapper_SoInput::readBinaryArray(SoInput* theWrappedObject, unsigned char*  c, int  length)
{
  return ( theWrappedObject->readBinaryArray(c, length));
}

void PythonQtWrapper_SoInput::static_SoInput_removeDirectory(const char*  dirName)
{
  (SoInput::removeDirectory(dirName));
}

void PythonQtWrapper_SoInput::removeReference(SoInput* theWrappedObject, const SbName&  name)
{
  ( theWrappedObject->removeReference(name));
}



SoOutput* PythonQtWrapper_SoOutput::new_SoOutput()
{ 
return new SoOutput(); }

SoOutput* PythonQtWrapper_SoOutput::new_SoOutput(SoOutput*  dictOut)
{ 
return new SoOutput(dictOut); }

void PythonQtWrapper_SoOutput::closeFile(SoOutput* theWrappedObject)
{
  ( theWrappedObject->closeFile());
}

void PythonQtWrapper_SoOutput::decrementIndent(SoOutput* theWrappedObject, int  amount)
{
  ( theWrappedObject->decrementIndent(amount));
}

unsigned int  PythonQtWrapper_SoOutput::getAnnotation(SoOutput* theWrappedObject)
{
  return ( theWrappedObject->getAnnotation());
}

size_t  PythonQtWrapper_SoOutput::getBufferSize(SoOutput* theWrappedObject) const
{
  return ( theWrappedObject->getBufferSize());
}

SbString  PythonQtWrapper_SoOutput::static_SoOutput_getDefaultASCIIHeader()
{
  return (SoOutput::getDefaultASCIIHeader());
}

SbString  PythonQtWrapper_SoOutput::static_SoOutput_getDefaultBinaryHeader()
{
  return (SoOutput::getDefaultBinaryHeader());
}

SoOutput::Stage  PythonQtWrapper_SoOutput::getStage(SoOutput* theWrappedObject) const
{
  return ( theWrappedObject->getStage());
}

void PythonQtWrapper_SoOutput::incrementIndent(SoOutput* theWrappedObject, int  amount)
{
  ( theWrappedObject->incrementIndent(amount));
}

void PythonQtWrapper_SoOutput::indent(SoOutput* theWrappedObject)
{
  ( theWrappedObject->indent());
}

bool  PythonQtWrapper_SoOutput::isBinary(SoOutput* theWrappedObject) const
{
  return ( theWrappedObject->isBinary());
}

bool  PythonQtWrapper_SoOutput::isCompact(SoOutput* theWrappedObject) const
{
  return ( theWrappedObject->isCompact());
}

bool  PythonQtWrapper_SoOutput::openFile(SoOutput* theWrappedObject, const char*  fileName)
{
  return ( theWrappedObject->openFile(fileName));
}

void PythonQtWrapper_SoOutput::reset(SoOutput* theWrappedObject)
{
  ( theWrappedObject->reset());
}

void PythonQtWrapper_SoOutput::resetBuffer(SoOutput* theWrappedObject)
{
  ( theWrappedObject->resetBuffer());
}

void PythonQtWrapper_SoOutput::resetHeaderString(SoOutput* theWrappedObject)
{
  ( theWrappedObject->resetHeaderString());
}

void PythonQtWrapper_SoOutput::setAnnotation(SoOutput* theWrappedObject, unsigned int  bits)
{
  ( theWrappedObject->setAnnotation(bits));
}

void PythonQtWrapper_SoOutput::setBinary(SoOutput* theWrappedObject, bool  flag)
{
  ( theWrappedObject->setBinary(flag));
}

void PythonQtWrapper_SoOutput::setCompact(SoOutput* theWrappedObject, bool  flag)
{
  ( theWrappedObject->setCompact(flag));
}

void PythonQtWrapper_SoOutput::setFloatPrecision(SoOutput* theWrappedObject, int  precision)
{
  ( theWrappedObject->setFloatPrecision(precision));
}

void PythonQtWrapper_SoOutput::setHeaderString(SoOutput* theWrappedObject, const SbString&  str)
{
  ( theWrappedObject->setHeaderString(str));
}

void PythonQtWrapper_SoOutput::setStage(SoOutput* theWrappedObject, SoOutput::Stage  stage)
{
  ( theWrappedObject->setStage(stage));
}

void PythonQtWrapper_SoOutput::write(SoOutput* theWrappedObject, char  c)
{
  ( theWrappedObject->write(c));
}

void PythonQtWrapper_SoOutput::write(SoOutput* theWrappedObject, const SbName&  n)
{
  ( theWrappedObject->write(n));
}

void PythonQtWrapper_SoOutput::write(SoOutput* theWrappedObject, const SbString&  s)
{
  ( theWrappedObject->write(s));
}

void PythonQtWrapper_SoOutput::write(SoOutput* theWrappedObject, const char*  s)
{
  ( theWrappedObject->write(s));
}

void PythonQtWrapper_SoOutput::write(SoOutput* theWrappedObject, double  d)
{
  ( theWrappedObject->write(d));
}

void PythonQtWrapper_SoOutput::write(SoOutput* theWrappedObject, float  f)
{
  ( theWrappedObject->write(f));
}

void PythonQtWrapper_SoOutput::write(SoOutput* theWrappedObject, int  i)
{
  ( theWrappedObject->write(i));
}

void PythonQtWrapper_SoOutput::write(SoOutput* theWrappedObject, short  s)
{
  ( theWrappedObject->write(s));
}

void PythonQtWrapper_SoOutput::write(SoOutput* theWrappedObject, unsigned int  i)
{
  ( theWrappedObject->write(i));
}

void PythonQtWrapper_SoOutput::write(SoOutput* theWrappedObject, unsigned short  s)
{
  ( theWrappedObject->write(s));
}

void PythonQtWrapper_SoOutput::writeBinaryArray(SoOutput* theWrappedObject, double*  d, int  length)
{
  ( theWrappedObject->writeBinaryArray(d, length));
}

void PythonQtWrapper_SoOutput::writeBinaryArray(SoOutput* theWrappedObject, float*  f, int  length)
{
  ( theWrappedObject->writeBinaryArray(f, length));
}

void PythonQtWrapper_SoOutput::writeBinaryArray(SoOutput* theWrappedObject, int*  l, int  length)
{
  ( theWrappedObject->writeBinaryArray(l, length));
}

void PythonQtWrapper_SoOutput::writeBinaryArray(SoOutput* theWrappedObject, unsigned char*  c, int  length)
{
  ( theWrappedObject->writeBinaryArray(c, length));
}



PythonQtShell_SoPath::~PythonQtShell_SoPath() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SbName  PythonQtShell_SoPath::getName() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("getName");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbName"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SbName returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getName", methodInfo, result);
          } else {
            returnValue = *((SbName*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SoPath::getName();
}
void PythonQtShell_SoPath::setName(const SbName&  name0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setName");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbName&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&name0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoPath::setName(name0);
}
void PythonQtShell_SoPath::startNotify()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("startNotify");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={""};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoPath::startNotify();
}
void PythonQtShell_SoPath::write(SoWriteAction*  writeAction0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("write");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoWriteAction*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&writeAction0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoPath::write(writeAction0);
}
SoPath* PythonQtWrapper_SoPath::new_SoPath()
{ 
return new PythonQtShell_SoPath(); }

SoPath* PythonQtWrapper_SoPath::new_SoPath(SoNode*  node)
{ 
return new PythonQtShell_SoPath(node); }

SoPath* PythonQtWrapper_SoPath::new_SoPath(int  approxLength)
{ 
return new PythonQtShell_SoPath(approxLength); }

void PythonQtWrapper_SoPath::append(SoPath* theWrappedObject, SoNode*  childNode)
{
  ( theWrappedObject->append(childNode));
}

void PythonQtWrapper_SoPath::append(SoPath* theWrappedObject, const SoPath*  fromPath)
{
  ( theWrappedObject->append(fromPath));
}

void PythonQtWrapper_SoPath::append(SoPath* theWrappedObject, int  childIndex)
{
  ( theWrappedObject->append(childIndex));
}

void PythonQtWrapper_SoPath::auditPath(SoPath* theWrappedObject, bool  flag)
{
  ( ((PythonQtPublicPromoter_SoPath*)theWrappedObject)->promoted_auditPath(flag));
}

bool  PythonQtWrapper_SoPath::containsNode(SoPath* theWrappedObject, const SoNode*  node) const
{
  return ( theWrappedObject->containsNode(node));
}

bool  PythonQtWrapper_SoPath::containsPath(SoPath* theWrappedObject, const SoPath*  path) const
{
  return ( theWrappedObject->containsPath(path));
}

SoPath*  PythonQtWrapper_SoPath::copy(SoPath* theWrappedObject, int  startFromNodeIndex, int  numNodes) const
{
  return ( theWrappedObject->copy(startFromNodeIndex, numNodes));
}

int  PythonQtWrapper_SoPath::findFork(SoPath* theWrappedObject, const SoPath*  path) const
{
  return ( theWrappedObject->findFork(path));
}

SoPath*  PythonQtWrapper_SoPath::static_SoPath_getByName(const SbName&  name)
{
  return (SoPath::getByName(name));
}

SoType  PythonQtWrapper_SoPath::static_SoPath_getClassTypeId()
{
  return (SoPath::getClassTypeId());
}

SoNode*  PythonQtWrapper_SoPath::getHead(SoPath* theWrappedObject) const
{
  return ( theWrappedObject->getHead());
}

int  PythonQtWrapper_SoPath::getIndex(SoPath* theWrappedObject, int  i) const
{
  return ( theWrappedObject->getIndex(i));
}

int  PythonQtWrapper_SoPath::getIndexFromTail(SoPath* theWrappedObject, int  i) const
{
  return ( theWrappedObject->getIndexFromTail(i));
}

int  PythonQtWrapper_SoPath::getLength(SoPath* theWrappedObject) const
{
  return ( theWrappedObject->getLength());
}

SoNode*  PythonQtWrapper_SoPath::getNode(SoPath* theWrappedObject, int  i) const
{
  return ( theWrappedObject->getNode(i));
}

SoNode*  PythonQtWrapper_SoPath::getNodeFromTail(SoPath* theWrappedObject, int  i) const
{
  return ( theWrappedObject->getNodeFromTail(i));
}

SoNode*  PythonQtWrapper_SoPath::getTail(SoPath* theWrappedObject) const
{
  return ( theWrappedObject->getTail());
}

void PythonQtWrapper_SoPath::insertIndex(SoPath* theWrappedObject, SoNode*  parent, int  newIndex)
{
  ( theWrappedObject->insertIndex(parent, newIndex));
}

bool  PythonQtWrapper_SoPath::__eq__(SoPath* theWrappedObject, const SoPath&  p2)
{
  return ( (*theWrappedObject)== p2);
}

void PythonQtWrapper_SoPath::pop(SoPath* theWrappedObject)
{
  ( theWrappedObject->pop());
}

void PythonQtWrapper_SoPath::push(SoPath* theWrappedObject, int  childIndex)
{
  ( theWrappedObject->push(childIndex));
}

void PythonQtWrapper_SoPath::removeIndex(SoPath* theWrappedObject, SoNode*  parent, int  oldIndex)
{
  ( theWrappedObject->removeIndex(parent, oldIndex));
}

void PythonQtWrapper_SoPath::replaceIndex(SoPath* theWrappedObject, SoNode*  parent, int  index, SoNode*  newChild)
{
  ( theWrappedObject->replaceIndex(parent, index, newChild));
}

void PythonQtWrapper_SoPath::setHead(SoPath* theWrappedObject, SoNode*  node)
{
  ( theWrappedObject->setHead(node));
}

void PythonQtWrapper_SoPath::truncate(SoPath* theWrappedObject, int  start)
{
  ( theWrappedObject->truncate(start));
}

void PythonQtWrapper_SoPath::write(SoPath* theWrappedObject, SoWriteAction*  writeAction) const
{
  ( theWrappedObject->write(writeAction));
}



SoPickedPoint* PythonQtWrapper_SoPickedPoint::new_SoPickedPoint(const SoPath*  path, SoState*  state, const SbVec3f&  objSpacePoint)
{ 
return new SoPickedPoint(path, state, objSpacePoint); }

SoPickedPoint* PythonQtWrapper_SoPickedPoint::new_SoPickedPoint(const SoPickedPoint&  pp)
{ 
return new SoPickedPoint(pp); }

SoPickedPoint*  PythonQtWrapper_SoPickedPoint::copy(SoPickedPoint* theWrappedObject) const
{
  return ( theWrappedObject->copy());
}

const SoDetail*  PythonQtWrapper_SoPickedPoint::getDetail(SoPickedPoint* theWrappedObject, const SoNode*  node) const
{
  return ( theWrappedObject->getDetail(node));
}

SbMatrix  PythonQtWrapper_SoPickedPoint::getImageToObject(SoPickedPoint* theWrappedObject, const SoNode*  node) const
{
  return ( theWrappedObject->getImageToObject(node));
}

int  PythonQtWrapper_SoPickedPoint::getMaterialIndex(SoPickedPoint* theWrappedObject) const
{
  return ( theWrappedObject->getMaterialIndex());
}

const SbVec3f*  PythonQtWrapper_SoPickedPoint::getNormal(SoPickedPoint* theWrappedObject) const
{
  return &( theWrappedObject->getNormal());
}

SbVec3f  PythonQtWrapper_SoPickedPoint::getObjectNormal(SoPickedPoint* theWrappedObject, const SoNode*  node) const
{
  return ( theWrappedObject->getObjectNormal(node));
}

SbVec3f  PythonQtWrapper_SoPickedPoint::getObjectPoint(SoPickedPoint* theWrappedObject, const SoNode*  node) const
{
  return ( theWrappedObject->getObjectPoint(node));
}

SbVec4f  PythonQtWrapper_SoPickedPoint::getObjectTextureCoords(SoPickedPoint* theWrappedObject, const SoNode*  node) const
{
  return ( theWrappedObject->getObjectTextureCoords(node));
}

SbMatrix  PythonQtWrapper_SoPickedPoint::getObjectToImage(SoPickedPoint* theWrappedObject, const SoNode*  node) const
{
  return ( theWrappedObject->getObjectToImage(node));
}

SbMatrix  PythonQtWrapper_SoPickedPoint::getObjectToWorld(SoPickedPoint* theWrappedObject, const SoNode*  node) const
{
  return ( theWrappedObject->getObjectToWorld(node));
}

SoPath*  PythonQtWrapper_SoPickedPoint::getPath(SoPickedPoint* theWrappedObject) const
{
  return ( theWrappedObject->getPath());
}

const SbVec3f*  PythonQtWrapper_SoPickedPoint::getPoint(SoPickedPoint* theWrappedObject) const
{
  return &( theWrappedObject->getPoint());
}

const SbVec4f*  PythonQtWrapper_SoPickedPoint::getTextureCoords(SoPickedPoint* theWrappedObject) const
{
  return &( theWrappedObject->getTextureCoords());
}

SbMatrix  PythonQtWrapper_SoPickedPoint::getWorldToObject(SoPickedPoint* theWrappedObject, const SoNode*  node) const
{
  return ( theWrappedObject->getWorldToObject(node));
}

bool  PythonQtWrapper_SoPickedPoint::isOnGeometry(SoPickedPoint* theWrappedObject) const
{
  return ( theWrappedObject->isOnGeometry());
}

void PythonQtWrapper_SoPickedPoint::setDetail(SoPickedPoint* theWrappedObject, SoDetail*  detail, SoNode*  node)
{
  ( theWrappedObject->setDetail(detail, node));
}

void PythonQtWrapper_SoPickedPoint::setMaterialIndex(SoPickedPoint* theWrappedObject, int  index)
{
  ( theWrappedObject->setMaterialIndex(index));
}

void PythonQtWrapper_SoPickedPoint::setObjectNormal(SoPickedPoint* theWrappedObject, const SbVec3f&  normal)
{
  ( theWrappedObject->setObjectNormal(normal));
}

void PythonQtWrapper_SoPickedPoint::setObjectTextureCoords(SoPickedPoint* theWrappedObject, const SbVec4f&  texCoords)
{
  ( theWrappedObject->setObjectTextureCoords(texCoords));
}



SoPrimitiveVertex* PythonQtWrapper_SoPrimitiveVertex::new_SoPrimitiveVertex()
{ 
return new SoPrimitiveVertex(); }

SoPrimitiveVertex* PythonQtWrapper_SoPrimitiveVertex::new_SoPrimitiveVertex(const SoPrimitiveVertex&  pv)
{ 
return new SoPrimitiveVertex(pv); }

const SoDetail*  PythonQtWrapper_SoPrimitiveVertex::getDetail(SoPrimitiveVertex* theWrappedObject) const
{
  return ( theWrappedObject->getDetail());
}

int  PythonQtWrapper_SoPrimitiveVertex::getMaterialIndex(SoPrimitiveVertex* theWrappedObject) const
{
  return ( theWrappedObject->getMaterialIndex());
}

const SbVec3f*  PythonQtWrapper_SoPrimitiveVertex::getNormal(SoPrimitiveVertex* theWrappedObject) const
{
  return &( theWrappedObject->getNormal());
}

const SbVec3f*  PythonQtWrapper_SoPrimitiveVertex::getPoint(SoPrimitiveVertex* theWrappedObject) const
{
  return &( theWrappedObject->getPoint());
}

const SbVec4f*  PythonQtWrapper_SoPrimitiveVertex::getTextureCoords(SoPrimitiveVertex* theWrappedObject) const
{
  return &( theWrappedObject->getTextureCoords());
}

SoPrimitiveVertex*  PythonQtWrapper_SoPrimitiveVertex::operator_assign(SoPrimitiveVertex* theWrappedObject, const SoPrimitiveVertex&  pv)
{
  return &( (*theWrappedObject)= pv);
}

void PythonQtWrapper_SoPrimitiveVertex::setDetail(SoPrimitiveVertex* theWrappedObject, SoDetail*  d)
{
  ( theWrappedObject->setDetail(d));
}

void PythonQtWrapper_SoPrimitiveVertex::setMaterialIndex(SoPrimitiveVertex* theWrappedObject, int  index)
{
  ( theWrappedObject->setMaterialIndex(index));
}

void PythonQtWrapper_SoPrimitiveVertex::setNormal(SoPrimitiveVertex* theWrappedObject, const SbVec3f&  norm)
{
  ( theWrappedObject->setNormal(norm));
}

void PythonQtWrapper_SoPrimitiveVertex::setPoint(SoPrimitiveVertex* theWrappedObject, const SbVec3f&  pt)
{
  ( theWrappedObject->setPoint(pt));
}

void PythonQtWrapper_SoPrimitiveVertex::setTextureCoords(SoPrimitiveVertex* theWrappedObject, const SbVec4f&  t)
{
  ( theWrappedObject->setTextureCoords(t));
}



PythonQtShell_SoSceneManager::~PythonQtShell_SoSceneManager() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoSceneManager::activate()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("activate");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={""};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoSceneManager::activate();
}
void PythonQtShell_SoSceneManager::deactivate()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("deactivate");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={""};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoSceneManager::deactivate();
}
SoNode*  PythonQtShell_SoSceneManager::getSceneGraph() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("getSceneGraph");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoNode* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getSceneGraph", methodInfo, result);
          } else {
            returnValue = *((SoNode**)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SoSceneManager::getSceneGraph();
}
bool  PythonQtShell_SoSceneManager::processEvent(const SoEvent*  event0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("processEvent");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoEvent*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&event0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("processEvent", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SoSceneManager::processEvent(event0);
}
void PythonQtShell_SoSceneManager::render(bool  clearWindow0, bool  clearZbuffer1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("render");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "bool" , "bool"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&clearWindow0, (void*)&clearZbuffer1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoSceneManager::render(clearWindow0, clearZbuffer1);
}
void PythonQtShell_SoSceneManager::setSceneGraph(SoNode*  newScene0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (Py_REFCNT((PyObject*)_wrapper) > 0) {
    static PyObject* name = PyString_FromString("setSceneGraph");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&newScene0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); }
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoSceneManager::setSceneGraph(newScene0);
}
SoSceneManager* PythonQtWrapper_SoSceneManager::new_SoSceneManager()
{ 
return new PythonQtShell_SoSceneManager(); }

void PythonQtWrapper_SoSceneManager::activate(SoSceneManager* theWrappedObject)
{
  ( theWrappedObject->activate());
}

void PythonQtWrapper_SoSceneManager::deactivate(SoSceneManager* theWrappedObject)
{
  ( theWrappedObject->deactivate());
}

void PythonQtWrapper_SoSceneManager::static_SoSceneManager_enableRealTimeUpdate(bool  flag)
{
  (SoSceneManager::enableRealTimeUpdate(flag));
}

void PythonQtWrapper_SoSceneManager::getAntialiasing(SoSceneManager* theWrappedObject, bool&  smoothing, int&  numPasses) const
{
  ( theWrappedObject->getAntialiasing(smoothing, numPasses));
}

const SbColor*  PythonQtWrapper_SoSceneManager::getBackgroundColor(SoSceneManager* theWrappedObject) const
{
  return &( theWrappedObject->getBackgroundColor());
}

unsigned int  PythonQtWrapper_SoSceneManager::static_SoSceneManager_getDefaultRedrawPriority()
{
  return (SoSceneManager::getDefaultRedrawPriority());
}

SoGLRenderAction*  PythonQtWrapper_SoSceneManager::getGLRenderAction(SoSceneManager* theWrappedObject) const
{
  return ( theWrappedObject->getGLRenderAction());
}

SoHandleEventAction*  PythonQtWrapper_SoSceneManager::getHandleEventAction(SoSceneManager* theWrappedObject) const
{
  return ( theWrappedObject->getHandleEventAction());
}

const SbVec2s*  PythonQtWrapper_SoSceneManager::getOrigin(SoSceneManager* theWrappedObject) const
{
  return &( theWrappedObject->getOrigin());
}

unsigned int  PythonQtWrapper_SoSceneManager::getRedrawPriority(SoSceneManager* theWrappedObject) const
{
  return ( theWrappedObject->getRedrawPriority());
}

SoNode*  PythonQtWrapper_SoSceneManager::getSceneGraph(SoSceneManager* theWrappedObject) const
{
  return ( theWrappedObject->getSceneGraph());
}

const SbVec2s*  PythonQtWrapper_SoSceneManager::getSize(SoSceneManager* theWrappedObject) const
{
  return &( theWrappedObject->getSize());
}

const SbViewportRegion*  PythonQtWrapper_SoSceneManager::getViewportRegion(SoSceneManager* theWrappedObject) const
{
  return &( theWrappedObject->getViewportRegion());
}

const SbVec2s*  PythonQtWrapper_SoSceneManager::getWindowSize(SoSceneManager* theWrappedObject) const
{
  return &( theWrappedObject->getWindowSize());
}

bool  PythonQtWrapper_SoSceneManager::isActive(SoSceneManager* theWrappedObject) const
{
  return ( ((PythonQtPublicPromoter_SoSceneManager*)theWrappedObject)->promoted_isActive());
}

bool  PythonQtWrapper_SoSceneManager::isAutoRedraw(SoSceneManager* theWrappedObject) const
{
  return ( theWrappedObject->isAutoRedraw());
}

bool  PythonQtWrapper_SoSceneManager::static_SoSceneManager_isRealTimeUpdateEnabled()
{
  return (SoSceneManager::isRealTimeUpdateEnabled());
}

bool  PythonQtWrapper_SoSceneManager::processEvent(SoSceneManager* theWrappedObject, const SoEvent*  event)
{
  return ( theWrappedObject->processEvent(event));
}

void PythonQtWrapper_SoSceneManager::redraw(SoSceneManager* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_SoSceneManager*)theWrappedObject)->promoted_redraw());
}

void PythonQtWrapper_SoSceneManager::reinitialize(SoSceneManager* theWrappedObject)
{
  ( theWrappedObject->reinitialize());
}

void PythonQtWrapper_SoSceneManager::render(SoSceneManager* theWrappedObject, bool  clearWindow, bool  clearZbuffer)
{
  ( theWrappedObject->render(clearWindow, clearZbuffer));
}

void PythonQtWrapper_SoSceneManager::scheduleRedraw(SoSceneManager* theWrappedObject)
{
  ( theWrappedObject->scheduleRedraw());
}

void PythonQtWrapper_SoSceneManager::setAntialiasing(SoSceneManager* theWrappedObject, bool  smoothing, int  numPasses)
{
  ( theWrappedObject->setAntialiasing(smoothing, numPasses));
}

void PythonQtWrapper_SoSceneManager::setBackgroundColor(SoSceneManager* theWrappedObject, const SbColor&  c)
{
  ( theWrappedObject->setBackgroundColor(c));
}

void PythonQtWrapper_SoSceneManager::setGLRenderAction(SoSceneManager* theWrappedObject, SoGLRenderAction*  ra)
{
  ( theWrappedObject->setGLRenderAction(ra));
}

void PythonQtWrapper_SoSceneManager::setHandleEventAction(SoSceneManager* theWrappedObject, SoHandleEventAction*  hea)
{
  ( theWrappedObject->setHandleEventAction(hea));
}

void PythonQtWrapper_SoSceneManager::setOrigin(SoSceneManager* theWrappedObject, const SbVec2s&  newOrigin)
{
  ( theWrappedObject->setOrigin(newOrigin));
}

void PythonQtWrapper_SoSceneManager::setRedrawPriority(SoSceneManager* theWrappedObject, unsigned int  priority)
{
  ( theWrappedObject->setRedrawPriority(priority));
}

void PythonQtWrapper_SoSceneManager::setSceneGraph(SoSceneManager* theWrappedObject, SoNode*  newScene)
{
  ( theWrappedObject->setSceneGraph(newScene));
}

void PythonQtWrapper_SoSceneManager::setSize(SoSceneManager* theWrappedObject, const SbVec2s&  newSize)
{
  ( theWrappedObject->setSize(newSize));
}

void PythonQtWrapper_SoSceneManager::setViewportRegion(SoSceneManager* theWrappedObject, const SbViewportRegion&  newRegion)
{
  ( theWrappedObject->setViewportRegion(newRegion));
}

void PythonQtWrapper_SoSceneManager::setWindowSize(SoSceneManager* theWrappedObject, const SbVec2s&  newSize)
{
  ( theWrappedObject->setWindowSize(newSize));
}



SoAction*  PythonQtWrapper_SoState::getAction(SoState* theWrappedObject) const
{
  return ( theWrappedObject->getAction());
}

const SoElement*  PythonQtWrapper_SoState::getConstElement(SoState* theWrappedObject, int  stackIndex) const
{
  return ( theWrappedObject->getConstElement(stackIndex));
}

int  PythonQtWrapper_SoState::getDepth(SoState* theWrappedObject) const
{
  return ( theWrappedObject->getDepth());
}

SoElement*  PythonQtWrapper_SoState::getElement(SoState* theWrappedObject, int  stackIndex)
{
  return ( theWrappedObject->getElement(stackIndex));
}

SoElement*  PythonQtWrapper_SoState::getElementNoPush(SoState* theWrappedObject, int  stackIndex) const
{
  return ( theWrappedObject->getElementNoPush(stackIndex));
}

bool  PythonQtWrapper_SoState::isCacheOpen(SoState* theWrappedObject) const
{
  return ( theWrappedObject->isCacheOpen());
}

bool  PythonQtWrapper_SoState::isElementEnabled(SoState* theWrappedObject, int  stackIndex) const
{
  return ( theWrappedObject->isElementEnabled(stackIndex));
}

void PythonQtWrapper_SoState::pop(SoState* theWrappedObject)
{
  ( theWrappedObject->pop());
}

void PythonQtWrapper_SoState::push(SoState* theWrappedObject)
{
  ( theWrappedObject->push());
}

void PythonQtWrapper_SoState::setCacheOpen(SoState* theWrappedObject, bool  flag)
{
  ( theWrappedObject->setCacheOpen(flag));
}



PythonQtShell_SoType::~PythonQtShell_SoType() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SoType* PythonQtWrapper_SoType::new_SoType()
{ 
return new PythonQtShell_SoType(); }

SoType  PythonQtWrapper_SoType::static_SoType_badType()
{
  return (SoType::badType());
}

bool  PythonQtWrapper_SoType::canCreateInstance(SoType* theWrappedObject) const
{
  return ( theWrappedObject->canCreateInstance());
}

void*  PythonQtWrapper_SoType::createInstance(SoType* theWrappedObject) const
{
  return ( theWrappedObject->createInstance());
}

SoType  PythonQtWrapper_SoType::static_SoType_fromName(SbName  name)
{
  return (SoType::fromName(name));
}

short  PythonQtWrapper_SoType::getData(SoType* theWrappedObject) const
{
  return ( theWrappedObject->getData());
}

short  PythonQtWrapper_SoType::getKey(SoType* theWrappedObject) const
{
  return ( theWrappedObject->getKey());
}

SbName  PythonQtWrapper_SoType::getName(SoType* theWrappedObject) const
{
  return ( theWrappedObject->getName());
}

int  PythonQtWrapper_SoType::static_SoType_getNumTypes()
{
  return (SoType::getNumTypes());
}

SoType  PythonQtWrapper_SoType::getParent(SoType* theWrappedObject) const
{
  return ( theWrappedObject->getParent());
}

void PythonQtWrapper_SoType::static_SoType_init()
{
  (SoType::init());
}

bool  PythonQtWrapper_SoType::isBad(SoType* theWrappedObject) const
{
  return ( theWrappedObject->isBad());
}

bool  PythonQtWrapper_SoType::isDerivedFrom(SoType* theWrappedObject, SoType  t) const
{
  return ( theWrappedObject->isDerivedFrom(t));
}

void PythonQtWrapper_SoType::makeInternal(SoType* theWrappedObject)
{
  ( theWrappedObject->makeInternal());
}

bool  PythonQtWrapper_SoType::__ne__(SoType* theWrappedObject, const SoType  t) const
{
  return ( (*theWrappedObject)!= t);
}

bool  PythonQtWrapper_SoType::__lt__(SoType* theWrappedObject, const SoType  t) const
{
  return ( (*theWrappedObject)< t);
}

bool  PythonQtWrapper_SoType::__eq__(SoType* theWrappedObject, const SoType  t) const
{
  return ( (*theWrappedObject)== t);
}


