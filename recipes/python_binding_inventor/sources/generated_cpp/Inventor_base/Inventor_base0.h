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
#include <stdexcept>



class PythonQtWrapper_SbBox2f : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbBox2f* new_SbBox2f();
SbBox2f* new_SbBox2f(const SbVec2f&  _min, const SbVec2f&  _max);
SbBox2f* new_SbBox2f(float  xmin, float  ymin, float  xmax, float  ymax);
SbBox2f* new_SbBox2f(const SbBox2f& other) {
SbBox2f* a = new SbBox2f();
*((SbBox2f*)a) = other;
return a; }
void delete_SbBox2f(SbBox2f* obj) { delete obj; }
   void extendBy(SbBox2f* theWrappedObject, const SbBox2f&  r);
   void extendBy(SbBox2f* theWrappedObject, const SbVec2f&  pt);
   float  getAspectRatio(SbBox2f* theWrappedObject) const;
   SbVec2f  getCenter(SbBox2f* theWrappedObject) const;
   SbVec2f  getClosestPoint(SbBox2f* theWrappedObject, const SbVec2f&  point);
   const SbVec2f*  getMax(SbBox2f* theWrappedObject) const;
   const SbVec2f*  getMin(SbBox2f* theWrappedObject) const;
   bool  hasArea(SbBox2f* theWrappedObject) const;
   bool  intersect(SbBox2f* theWrappedObject, const SbBox2f&  bb) const;
   bool  intersect(SbBox2f* theWrappedObject, const SbVec2f&  pt) const;
   bool  isEmpty(SbBox2f* theWrappedObject) const;
   void makeEmpty(SbBox2f* theWrappedObject);
   bool  __ne__(SbBox2f* theWrappedObject, const SbBox2f&  b2);
   bool  __eq__(SbBox2f* theWrappedObject, const SbBox2f&  b2);
   void setBounds(SbBox2f* theWrappedObject, const SbVec2f&  _min, const SbVec2f&  _max);
   void setBounds(SbBox2f* theWrappedObject, float  xmin, float  ymin, float  xmax, float  ymax);
    bool __nonzero__(SbBox2f* obj) { return !obj->isEmpty(); }
};





class PythonQtWrapper_SbBox2s : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbBox2s* new_SbBox2s();
SbBox2s* new_SbBox2s(const SbVec2s&  min, const SbVec2s&  max);
SbBox2s* new_SbBox2s(short  xmin, short  ymin, short  xmax, short  ymax);
SbBox2s* new_SbBox2s(const SbBox2s& other) {
SbBox2s* a = new SbBox2s();
*((SbBox2s*)a) = other;
return a; }
void delete_SbBox2s(SbBox2s* obj) { delete obj; }
   void extendBy(SbBox2s* theWrappedObject, const SbBox2s&  r);
   void extendBy(SbBox2s* theWrappedObject, const SbVec2s&  pt);
   float  getAspectRatio(SbBox2s* theWrappedObject) const;
   const SbVec2s*  getMax(SbBox2s* theWrappedObject) const;
   const SbVec2s*  getMin(SbBox2s* theWrappedObject) const;
   bool  intersect(SbBox2s* theWrappedObject, const SbBox2s&  bb) const;
   bool  intersect(SbBox2s* theWrappedObject, const SbVec2s&  pt) const;
   void makeEmpty(SbBox2s* theWrappedObject);
   bool  __ne__(SbBox2s* theWrappedObject, const SbBox2s&  b2);
   bool  __eq__(SbBox2s* theWrappedObject, const SbBox2s&  b2);
   void setBounds(SbBox2s* theWrappedObject, const SbVec2s&  _min, const SbVec2s&  _max);
   void setBounds(SbBox2s* theWrappedObject, short  xmin, short  ymin, short  xmax, short  ymax);
};





class PythonQtWrapper_SbBox3d : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbBox3d* new_SbBox3d();
SbBox3d* new_SbBox3d(const SbVec3d&  min, const SbVec3d&  max);
SbBox3d* new_SbBox3d(double  xmin, double  ymin, double  zmin, double  xmax, double  ymax, double  zmax);
SbBox3d* new_SbBox3d(const SbBox3d& other) {
SbBox3d* a = new SbBox3d();
*((SbBox3d*)a) = other;
return a; }
void delete_SbBox3d(SbBox3d* obj) { delete obj; }
   void extendBy(SbBox3d* theWrappedObject, const SbBox3d&  bb);
   void extendBy(SbBox3d* theWrappedObject, const SbVec3d&  pt);
   SbVec3d  getCenter(SbBox3d* theWrappedObject) const;
   SbVec3d  getClosestPoint(SbBox3d* theWrappedObject, const SbVec3d&  point);
   SbVec3d*  getMax(SbBox3d* theWrappedObject);
   SbVec3d*  getMin(SbBox3d* theWrappedObject);
   double  getVolume(SbBox3d* theWrappedObject) const;
   bool  hasVolume(SbBox3d* theWrappedObject) const;
   bool  intersect(SbBox3d* theWrappedObject, const SbBox3d&  bb) const;
   bool  intersect(SbBox3d* theWrappedObject, const SbVec3d&  pt) const;
   bool  isEmpty(SbBox3d* theWrappedObject) const;
   void makeEmpty(SbBox3d* theWrappedObject);
   bool  __ne__(SbBox3d* theWrappedObject, const SbBox3d&  b2);
   bool  __eq__(SbBox3d* theWrappedObject, const SbBox3d&  b2);
   void setBounds(SbBox3d* theWrappedObject, const SbVec3d&  _min, const SbVec3d&  _max);
   void setBounds(SbBox3d* theWrappedObject, double  xmin, double  ymin, double  zmin, double  xmax, double  ymax, double  zmax);
   void transform(SbBox3d* theWrappedObject, const SbMatrixd&  m);
    bool __nonzero__(SbBox3d* obj) { return !obj->isEmpty(); }
};





class PythonQtWrapper_SbBox3f : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbBox3f* new_SbBox3f();
SbBox3f* new_SbBox3f(const SbVec3f&  min, const SbVec3f&  max);
SbBox3f* new_SbBox3f(float  xmin, float  ymin, float  zmin, float  xmax, float  ymax, float  zmax);
SbBox3f* new_SbBox3f(const SbBox3f& other) {
SbBox3f* a = new SbBox3f();
*((SbBox3f*)a) = other;
return a; }
void delete_SbBox3f(SbBox3f* obj) { delete obj; }
   void extendBy(SbBox3f* theWrappedObject, const SbBox3f&  bb);
   void extendBy(SbBox3f* theWrappedObject, const SbVec3f&  pt);
   SbVec3f  getCenter(SbBox3f* theWrappedObject) const;
   SbVec3f  getClosestPoint(SbBox3f* theWrappedObject, const SbVec3f&  point);
   SbVec3f*  getMax(SbBox3f* theWrappedObject);
   SbVec3f*  getMin(SbBox3f* theWrappedObject);
   float  getVolume(SbBox3f* theWrappedObject) const;
   bool  hasVolume(SbBox3f* theWrappedObject) const;
   bool  intersect(SbBox3f* theWrappedObject, const SbBox3f&  bb) const;
   bool  intersect(SbBox3f* theWrappedObject, const SbVec3f&  pt) const;
   bool  isEmpty(SbBox3f* theWrappedObject) const;
   void makeEmpty(SbBox3f* theWrappedObject);
   bool  __ne__(SbBox3f* theWrappedObject, const SbBox3f&  b2);
   bool  __eq__(SbBox3f* theWrappedObject, const SbBox3f&  b2);
   void setBounds(SbBox3f* theWrappedObject, const SbVec3f&  _min, const SbVec3f&  _max);
   void setBounds(SbBox3f* theWrappedObject, float  xmin, float  ymin, float  zmin, float  xmax, float  ymax, float  zmax);
   void transform(SbBox3f* theWrappedObject, const SbMatrix&  m);
    bool __nonzero__(SbBox3f* obj) { return !obj->isEmpty(); }
};





class PythonQtWrapper_SbColor : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbColor* new_SbColor();
SbColor* new_SbColor(const SbVec3f  vec3f);
SbColor* new_SbColor(float  r, float  g, float  b);
SbColor* new_SbColor(const SbColor& other) {
SbColor* a = new SbColor();
*((SbColor*)a) = other;
return a; }
void delete_SbColor(SbColor* obj) { delete obj; }
   unsigned int  getPackedValue(SbColor* theWrappedObject, float  transparency = 0.0) const;
   SbColor*  setHSVValue(SbColor* theWrappedObject, float  h, float  s, float  v);
};





class PythonQtWrapper_SbCylinder : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbCylinder* new_SbCylinder();
SbCylinder* new_SbCylinder(const SbLine&  a, float  r);
SbCylinder* new_SbCylinder(const SbCylinder& other) {
SbCylinder* a = new SbCylinder();
*((SbCylinder*)a) = other;
return a; }
void delete_SbCylinder(SbCylinder* obj) { delete obj; }
   const SbLine*  getAxis(SbCylinder* theWrappedObject) const;
   float  getRadius(SbCylinder* theWrappedObject) const;
   void setAxis(SbCylinder* theWrappedObject, const SbLine&  a);
   void setRadius(SbCylinder* theWrappedObject, float  r);
   void setValue(SbCylinder* theWrappedObject, const SbLine&  a, float  r);
};





class PythonQtWrapper_SbCylinderd : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbCylinderd* new_SbCylinderd();
SbCylinderd* new_SbCylinderd(const SbLined&  a, double  r);
SbCylinderd* new_SbCylinderd(const SbCylinderd& other) {
SbCylinderd* a = new SbCylinderd();
*((SbCylinderd*)a) = other;
return a; }
void delete_SbCylinderd(SbCylinderd* obj) { delete obj; }
   const SbLined*  getAxis(SbCylinderd* theWrappedObject) const;
   double  getRadius(SbCylinderd* theWrappedObject) const;
   void setAxis(SbCylinderd* theWrappedObject, const SbLined&  a);
   void setRadius(SbCylinderd* theWrappedObject, double  r);
   void setValue(SbCylinderd* theWrappedObject, const SbLined&  a, double  r);
};





class PythonQtWrapper_SbLine : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbLine* new_SbLine();
SbLine* new_SbLine(const SbVec3f&  p0, const SbVec3f&  p1);
SbLine* new_SbLine(const SbLine& other) {
SbLine* a = new SbLine();
*((SbLine*)a) = other;
return a; }
void delete_SbLine(SbLine* obj) { delete obj; }
   SbVec3f  getClosestPoint(SbLine* theWrappedObject, const SbVec3f&  point) const;
   const SbVec3f*  getDirection(SbLine* theWrappedObject) const;
   const SbVec3f*  getPosition(SbLine* theWrappedObject) const;
   void setValue(SbLine* theWrappedObject, const SbVec3f&  p0, const SbVec3f&  p1);
};





class PythonQtWrapper_SbLined : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbLined* new_SbLined();
SbLined* new_SbLined(const SbVec3d&  p0, const SbVec3d&  p1);
SbLined* new_SbLined(const SbLined& other) {
SbLined* a = new SbLined();
*((SbLined*)a) = other;
return a; }
void delete_SbLined(SbLined* obj) { delete obj; }
   SbVec3d  getClosestPoint(SbLined* theWrappedObject, const SbVec3d&  point) const;
   const SbVec3d*  getDirection(SbLined* theWrappedObject) const;
   const SbVec3d*  getPosition(SbLined* theWrappedObject) const;
   void setValue(SbLined* theWrappedObject, const SbVec3d&  p0, const SbVec3d&  p1);
};





class PythonQtWrapper_SbMatrix : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbMatrix* new_SbMatrix();
SbMatrix* new_SbMatrix(float  a11, float  a12, float  a13, float  a14, float  a21, float  a22, float  a23, float  a24, float  a31, float  a32, float  a33, float  a34, float  a41, float  a42, float  a43, float  a44);
SbMatrix* new_SbMatrix(const SbMatrix& other) {
SbMatrix* a = new SbMatrix();
*((SbMatrix*)a) = other;
return a; }
void delete_SbMatrix(SbMatrix* obj) { delete obj; }
   float  det3(SbMatrix* theWrappedObject) const;
   float  det3(SbMatrix* theWrappedObject, int  r1, int  r2, int  r3, int  c1, int  c2, int  c3) const;
   float  det4(SbMatrix* theWrappedObject) const;
   bool  equals(SbMatrix* theWrappedObject, const SbMatrix&  m, float  tolerance) const;
   SbMatrix  static_SbMatrix_identity();
   SbMatrix  inverse(SbMatrix* theWrappedObject) const;
   void makeIdentity(SbMatrix* theWrappedObject);
   SbMatrix*  multLeft(SbMatrix* theWrappedObject, const SbMatrix&  m);
   SbMatrix*  multRight(SbMatrix* theWrappedObject, const SbMatrix&  m);
   bool  __ne__(SbMatrix* theWrappedObject, const SbMatrix&  m2);
   SbMatrix  __mul__(SbMatrix* theWrappedObject, const SbMatrix&  m2);
   SbMatrix*  __imul__(SbMatrix* theWrappedObject, const SbMatrix&  m);
   SbMatrix*  operator_assign(SbMatrix* theWrappedObject, const SbMatrix&  m);
   SbMatrix*  operator_assign(SbMatrix* theWrappedObject, const SbRotation&  q);
   bool  __eq__(SbMatrix* theWrappedObject, const SbMatrix&  m2);
   void setRotate(SbMatrix* theWrappedObject, const SbRotation&  q);
   void setScale(SbMatrix* theWrappedObject, const SbVec3f&  s);
   void setScale(SbMatrix* theWrappedObject, float  s);
   void setTransform(SbMatrix* theWrappedObject, const SbVec3f&  t, const SbRotation&  r, const SbVec3f&  s);
   void setTransform(SbMatrix* theWrappedObject, const SbVec3f&  t, const SbRotation&  r, const SbVec3f&  s, const SbRotation&  so);
   void setTransform(SbMatrix* theWrappedObject, const SbVec3f&  translation, const SbRotation&  rotation, const SbVec3f&  scaleFactor, const SbRotation&  scaleOrientation, const SbVec3f&  center);
   void setTranslate(SbMatrix* theWrappedObject, const SbVec3f&  t);
   SbVec3f  transformDirection(SbMatrix* theWrappedObject, const SbVec3f&  src) const;
   SbLine  transformLine(SbMatrix* theWrappedObject, const SbLine&  src) const;
   SbVec3f  transformPoint(SbMatrix* theWrappedObject, const SbVec3f&  src) const;
   SbVec4f  transformPoint(SbMatrix* theWrappedObject, const SbVec4f&  src) const;
   SbMatrix  transpose(SbMatrix* theWrappedObject) const;
};





class PythonQtWrapper_SbMatrixd : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbMatrixd* new_SbMatrixd();
SbMatrixd* new_SbMatrixd(double  a11, double  a12, double  a13, double  a14, double  a21, double  a22, double  a23, double  a24, double  a31, double  a32, double  a33, double  a34, double  a41, double  a42, double  a43, double  a44);
SbMatrixd* new_SbMatrixd(const SbMatrixd& other) {
SbMatrixd* a = new SbMatrixd();
*((SbMatrixd*)a) = other;
return a; }
void delete_SbMatrixd(SbMatrixd* obj) { delete obj; }
   double  det3(SbMatrixd* theWrappedObject) const;
   double  det3(SbMatrixd* theWrappedObject, int  r1, int  r2, int  r3, int  c1, int  c2, int  c3) const;
   double  det4(SbMatrixd* theWrappedObject) const;
   bool  equals(SbMatrixd* theWrappedObject, const SbMatrixd&  m, double  tolerance) const;
   SbMatrixd  static_SbMatrixd_identity();
   SbMatrixd  inverse(SbMatrixd* theWrappedObject) const;
   void makeIdentity(SbMatrixd* theWrappedObject);
   SbMatrixd*  multLeft(SbMatrixd* theWrappedObject, const SbMatrixd&  m);
   SbMatrixd*  multRight(SbMatrixd* theWrappedObject, const SbMatrixd&  m);
   bool  __ne__(SbMatrixd* theWrappedObject, const SbMatrixd&  m2);
   SbMatrixd  __mul__(SbMatrixd* theWrappedObject, const SbMatrixd&  m2);
   SbMatrixd*  __imul__(SbMatrixd* theWrappedObject, const SbMatrixd&  m);
   SbMatrixd*  operator_assign(SbMatrixd* theWrappedObject, const SbMatrixd&  m);
   SbMatrixd*  operator_assign(SbMatrixd* theWrappedObject, const SbRotationd&  q);
   bool  __eq__(SbMatrixd* theWrappedObject, const SbMatrixd&  m2);
   void setRotate(SbMatrixd* theWrappedObject, const SbRotationd&  q);
   void setScale(SbMatrixd* theWrappedObject, const SbVec3d&  s);
   void setScale(SbMatrixd* theWrappedObject, double  s);
   void setTransform(SbMatrixd* theWrappedObject, const SbVec3d&  t, const SbRotationd&  r, const SbVec3d&  s);
   void setTransform(SbMatrixd* theWrappedObject, const SbVec3d&  t, const SbRotationd&  r, const SbVec3d&  s, const SbRotationd&  so);
   void setTransform(SbMatrixd* theWrappedObject, const SbVec3d&  translation, const SbRotationd&  rotation, const SbVec3d&  scaleFactor, const SbRotationd&  scaleOrientation, const SbVec3d&  center);
   void setTranslate(SbMatrixd* theWrappedObject, const SbVec3d&  t);
   SbVec3d  transformDirection(SbMatrixd* theWrappedObject, const SbVec3d&  src) const;
   SbLined  transformLine(SbMatrixd* theWrappedObject, const SbLined&  src) const;
   SbVec3d  transformPoint(SbMatrixd* theWrappedObject, const SbVec3d&  src) const;
   SbVec4d  transformPoint(SbMatrixd* theWrappedObject, const SbVec4d&  src) const;
   SbMatrixd  transpose(SbMatrixd* theWrappedObject) const;
};





class PythonQtWrapper_SbName : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbName* new_SbName();
SbName* new_SbName(const SbName&  n);
SbName* new_SbName(const SbString&  s);
SbName* new_SbName(const char*  s);
void delete_SbName(SbName* obj) { delete obj; }
   int  getLength(SbName* theWrappedObject) const;
   const char*  getString(SbName* theWrappedObject) const;
   bool  static_SbName_isBaseNameChar(char  c);
   bool  static_SbName_isBaseNameStartChar(char  c);
   bool  static_SbName_isIdentChar(char  c);
   bool  static_SbName_isIdentStartChar(char  c);
   bool  operator_not(SbName* theWrappedObject) const;
};





class PythonQtWrapper_SbPlane : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbPlane* new_SbPlane();
SbPlane* new_SbPlane(const SbVec3f&  n, const SbVec3f&  p);
SbPlane* new_SbPlane(const SbVec3f&  n, float  d);
SbPlane* new_SbPlane(const SbVec3f&  p0, const SbVec3f&  p1, const SbVec3f&  p2);
SbPlane* new_SbPlane(const SbPlane& other) {
SbPlane* a = new SbPlane();
*((SbPlane*)a) = other;
return a; }
void delete_SbPlane(SbPlane* obj) { delete obj; }
   float  getDistance(SbPlane* theWrappedObject, const SbVec3f&  point) const;
   float  getDistanceFromOrigin(SbPlane* theWrappedObject) const;
   const SbVec3f*  getNormal(SbPlane* theWrappedObject) const;
   bool  isInHalfSpace(SbPlane* theWrappedObject, const SbVec3f&  point) const;
   void offset(SbPlane* theWrappedObject, float  d);
   bool  __ne__(SbPlane* theWrappedObject, const SbPlane&  p2);
   bool  __eq__(SbPlane* theWrappedObject, const SbPlane&  p2);
   void transform(SbPlane* theWrappedObject, const SbMatrix&  matrix);
};





class PythonQtWrapper_SbPlaned : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbPlaned* new_SbPlaned();
SbPlaned* new_SbPlaned(const SbVec3d&  n, const SbVec3d&  p);
SbPlaned* new_SbPlaned(const SbVec3d&  n, double  d);
SbPlaned* new_SbPlaned(const SbVec3d&  p0, const SbVec3d&  p1, const SbVec3d&  p2);
SbPlaned* new_SbPlaned(const SbPlaned& other) {
SbPlaned* a = new SbPlaned();
*((SbPlaned*)a) = other;
return a; }
void delete_SbPlaned(SbPlaned* obj) { delete obj; }
   double  getDistance(SbPlaned* theWrappedObject, const SbVec3d&  point) const;
   double  getDistanceFromOrigin(SbPlaned* theWrappedObject) const;
   const SbVec3d*  getNormal(SbPlaned* theWrappedObject) const;
   bool  isInHalfSpace(SbPlaned* theWrappedObject, const SbVec3d&  point) const;
   void offset(SbPlaned* theWrappedObject, double  d);
   bool  __ne__(SbPlaned* theWrappedObject, const SbPlaned&  p2);
   bool  __eq__(SbPlaned* theWrappedObject, const SbPlaned&  p2);
   void transform(SbPlaned* theWrappedObject, const SbMatrixd&  matrix);
};





class PythonQtWrapper_SbRotation : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbRotation* new_SbRotation();
SbRotation* new_SbRotation(const SbMatrix&  m);
SbRotation* new_SbRotation(const SbVec3f&  axis, float  radians);
SbRotation* new_SbRotation(const SbVec3f&  rotateFrom, const SbVec3f&  rotateTo);
SbRotation* new_SbRotation(float  q0, float  q1, float  q2, float  q3);
SbRotation* new_SbRotation(const SbRotation& other) {
SbRotation* a = new SbRotation();
*((SbRotation*)a) = other;
return a; }
void delete_SbRotation(SbRotation* obj) { delete obj; }
   bool  equals(SbRotation* theWrappedObject, const SbRotation&  r, float  tolerance) const;
   float  getAngle(SbRotation* theWrappedObject) const;
   SbVec3f  getAxis(SbRotation* theWrappedObject) const;
   SbMatrix  getMatrix(SbRotation* theWrappedObject) const;
   SbRotation  static_SbRotation_identity();
   SbRotation  inverse(SbRotation* theWrappedObject) const;
   SbRotation*  invert(SbRotation* theWrappedObject);
   bool  __ne__(SbRotation* theWrappedObject, const SbRotation&  q2);
   SbRotation  __mul__(SbRotation* theWrappedObject, const SbRotation&  q2);
   SbRotation*  __imul__(SbRotation* theWrappedObject, const SbRotation&  q);
   bool  __eq__(SbRotation* theWrappedObject, const SbRotation&  q2);
   void scaleAngle(SbRotation* theWrappedObject, float  scaleFactor);
   SbRotation*  setValue(SbRotation* theWrappedObject, const SbMatrix&  m);
   SbRotation*  setValue(SbRotation* theWrappedObject, const SbVec3f&  axis, float  radians);
   SbRotation*  setValue(SbRotation* theWrappedObject, const SbVec3f&  rotateFrom, const SbVec3f&  rotateTo);
   SbRotation*  setValue(SbRotation* theWrappedObject, float  q0, float  q1, float  q2, float  q3);
   SbRotation  static_SbRotation_slerp(const SbRotation&  rot0, const SbRotation&  rot1, float  t);
   SbVec3f  transformPoint(SbRotation* theWrappedObject, const SbVec3f&  src) const;
};





class PythonQtWrapper_SbRotationd : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbRotationd* new_SbRotationd();
SbRotationd* new_SbRotationd(const SbMatrixd&  m);
SbRotationd* new_SbRotationd(const SbVec3d&  axis, double  radians);
SbRotationd* new_SbRotationd(const SbVec3d&  rotateFrom, const SbVec3d&  rotateTo);
SbRotationd* new_SbRotationd(double  q0, double  q1, double  q2, double  q3);
SbRotationd* new_SbRotationd(const SbRotationd& other) {
SbRotationd* a = new SbRotationd();
*((SbRotationd*)a) = other;
return a; }
void delete_SbRotationd(SbRotationd* obj) { delete obj; }
   bool  equals(SbRotationd* theWrappedObject, const SbRotationd&  r, double  tolerance) const;
   double  getAngle(SbRotationd* theWrappedObject) const;
   SbVec3d  getAxis(SbRotationd* theWrappedObject) const;
   SbMatrixd  getMatrix(SbRotationd* theWrappedObject) const;
   SbRotationd  static_SbRotationd_identity();
   SbRotationd  inverse(SbRotationd* theWrappedObject) const;
   SbRotationd*  invert(SbRotationd* theWrappedObject);
   bool  __ne__(SbRotationd* theWrappedObject, const SbRotationd&  q2);
   SbRotationd  __mul__(SbRotationd* theWrappedObject, const SbRotationd&  q2);
   SbRotationd*  __imul__(SbRotationd* theWrappedObject, const SbRotationd&  q);
   bool  __eq__(SbRotationd* theWrappedObject, const SbRotationd&  q2);
   void scaleAngle(SbRotationd* theWrappedObject, double  scaleFactor);
   SbRotationd*  setValue(SbRotationd* theWrappedObject, const SbMatrixd&  m);
   SbRotationd*  setValue(SbRotationd* theWrappedObject, const SbVec3d&  axis, double  radians);
   SbRotationd*  setValue(SbRotationd* theWrappedObject, const SbVec3d&  rotateFrom, const SbVec3d&  rotateTo);
   SbRotationd*  setValue(SbRotationd* theWrappedObject, double  q0, double  q1, double  q2, double  q3);
   SbRotationd  static_SbRotationd_slerp(const SbRotationd&  rot0, const SbRotationd&  rot1, double  t);
   SbVec3d  transformPoint(SbRotationd* theWrappedObject, const SbVec3d&  src) const;
};





class PythonQtWrapper_SbSphere : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbSphere* new_SbSphere();
SbSphere* new_SbSphere(const SbVec3f&  c, float  r);
SbSphere* new_SbSphere(const SbSphere& other) {
SbSphere* a = new SbSphere();
*((SbSphere*)a) = other;
return a; }
void delete_SbSphere(SbSphere* obj) { delete obj; }
   void circumscribe(SbSphere* theWrappedObject, const SbBox3f&  box);
   const SbVec3f*  getCenter(SbSphere* theWrappedObject) const;
   float  getRadius(SbSphere* theWrappedObject) const;
   void setCenter(SbSphere* theWrappedObject, const SbVec3f&  c);
   void setRadius(SbSphere* theWrappedObject, float  r);
   void setValue(SbSphere* theWrappedObject, const SbVec3f&  c, float  r);
};





class PythonQtWrapper_SbSphered : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbSphered* new_SbSphered();
SbSphered* new_SbSphered(const SbVec3d&  c, double  r);
SbSphered* new_SbSphered(const SbSphered& other) {
SbSphered* a = new SbSphered();
*((SbSphered*)a) = other;
return a; }
void delete_SbSphered(SbSphered* obj) { delete obj; }
   void circumscribe(SbSphered* theWrappedObject, const SbBox3d&  box);
   const SbVec3d*  getCenter(SbSphered* theWrappedObject) const;
   double  getRadius(SbSphered* theWrappedObject) const;
   void setCenter(SbSphered* theWrappedObject, const SbVec3d&  c);
   void setRadius(SbSphered* theWrappedObject, double  r);
   void setValue(SbSphered* theWrappedObject, const SbVec3d&  c, double  r);
};





class PythonQtWrapper_SbString : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbString* new_SbString();
SbString* new_SbString(const SbString&  str);
SbString* new_SbString(const char*  str);
SbString* new_SbString(const char*  str, int  start, int  end);
SbString* new_SbString(int  digitString);
void delete_SbString(SbString* obj) { delete obj; }
   void deleteSubString(SbString* theWrappedObject, int  startChar, int  endChar = -1);
   int  getLength(SbString* theWrappedObject) const;
   const char*  getString(SbString* theWrappedObject) const;
   SbString  getSubString(SbString* theWrappedObject, int  startChar, int  endChar = -1) const;
   unsigned int  hash(SbString* theWrappedObject);
   unsigned int  static_SbString_hash(const char*  s);
   void makeEmpty(SbString* theWrappedObject, bool  freeOld = 1);
   bool  operator_not(SbString* theWrappedObject) const;
   SbString*  __iadd__(SbString* theWrappedObject, const SbString&  str);
   SbString*  __iadd__(SbString* theWrappedObject, const char*  str);
   SbString*  operator_assign(SbString* theWrappedObject, const SbString&  str);
   SbString*  operator_assign(SbString* theWrappedObject, const char*  str);
};





class PythonQtWrapper_SbTime : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbTime* new_SbTime();
SbTime* new_SbTime(double  sec);
SbTime* new_SbTime(const SbTime& other) {
SbTime* a = new SbTime();
*((SbTime*)a) = other;
return a; }
void delete_SbTime(SbTime* obj) { delete obj; }
   SbString  format(SbTime* theWrappedObject, const char*  fmt = "%S.%i") const;
   SbString  formatDate(SbTime* theWrappedObject, const char*  fmt = "%A, %D %r") const;
   unsigned long  getMsecValue(SbTime* theWrappedObject) const;
   SbTime  static_SbTime_getTimeOfDay();
   double  getValue(SbTime* theWrappedObject) const;
   SbTime  static_SbTime_max();
   bool  __ne__(SbTime* theWrappedObject, const SbTime&  tm) const;
   SbTime  __mod__(SbTime* theWrappedObject, const SbTime&  tm) const;
   SbTime  __mul__(SbTime* theWrappedObject, double  s);
   SbTime*  __imul__(SbTime* theWrappedObject, double  s);
   SbTime  __add__(SbTime* theWrappedObject, const SbTime&  t1);
   SbTime*  __iadd__(SbTime* theWrappedObject, const SbTime&  tm);
   SbTime  __sub__(SbTime* theWrappedObject) const;
   SbTime  __sub__(SbTime* theWrappedObject, const SbTime&  t1);
   SbTime*  __isub__(SbTime* theWrappedObject, const SbTime&  tm);
   double  __div__(SbTime* theWrappedObject, const SbTime&  tm) const;
   SbTime  __div__(SbTime* theWrappedObject, double  s);
   SbTime*  __idiv__(SbTime* theWrappedObject, double  s);
   bool  __lt__(SbTime* theWrappedObject, const SbTime&  tm) const;
   bool  __le__(SbTime* theWrappedObject, const SbTime&  tm) const;
   bool  __eq__(SbTime* theWrappedObject, const SbTime&  tm) const;
   bool  __gt__(SbTime* theWrappedObject, const SbTime&  tm) const;
   bool  __ge__(SbTime* theWrappedObject, const SbTime&  tm) const;
   void setMsecValue(SbTime* theWrappedObject, unsigned long  msec);
   void setToTimeOfDay(SbTime* theWrappedObject);
   void setValue(SbTime* theWrappedObject, double  sec);
   SbTime  static_SbTime_zero();
};





class PythonQtShell_SbVec2d : public SbVec2d
{
public:
    PythonQtShell_SbVec2d():SbVec2d(),_wrapper(nullptr) {};
    PythonQtShell_SbVec2d(double  x, double  y):SbVec2d(x, y),_wrapper(nullptr) {};

   ~PythonQtShell_SbVec2d();


  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SbVec2d : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbVec2d* new_SbVec2d();
SbVec2d* new_SbVec2d(double  x, double  y);
SbVec2d* new_SbVec2d(const SbVec2d& other) {
PythonQtShell_SbVec2d* a = new PythonQtShell_SbVec2d();
*((SbVec2d*)a) = other;
return a; }
void delete_SbVec2d(SbVec2d* obj) { delete obj; }
   double  dot(SbVec2d* theWrappedObject, const SbVec2d&  v) const;
   bool  equals(SbVec2d* theWrappedObject, const SbVec2d  v, double  tolerance) const;
   double  length(SbVec2d* theWrappedObject) const;
   void negate(SbVec2d* theWrappedObject);
   double  normalize(SbVec2d* theWrappedObject);
   bool  __ne__(SbVec2d* theWrappedObject, const SbVec2d&  v2);
   SbVec2d  __mul__(SbVec2d* theWrappedObject, double  d);
   SbVec2d*  __imul__(SbVec2d* theWrappedObject, double  d);
   SbVec2d  __add__(SbVec2d* theWrappedObject, const SbVec2d&  v2);
   SbVec2d*  __iadd__(SbVec2d* theWrappedObject, const SbVec2d&  u);
   SbVec2d  __sub__(SbVec2d* theWrappedObject) const;
   SbVec2d  __sub__(SbVec2d* theWrappedObject, const SbVec2d&  v2);
   SbVec2d*  __isub__(SbVec2d* theWrappedObject, const SbVec2d&  u);
   SbVec2d  __div__(SbVec2d* theWrappedObject, double  d);
   SbVec2d*  __idiv__(SbVec2d* theWrappedObject, double  d);
   bool  __eq__(SbVec2d* theWrappedObject, const SbVec2d&  v2);
   SbVec2d*  setValue(SbVec2d* theWrappedObject, double  x, double  y);


  SbVec2f toVec2f( SbVec2d* vec )
  {
    const double* value = vec->getValue();
    return SbVec2f(value[0], value[1]);
  }

  QList<double> getValue(SbVec2d* vec)
  {
    QList<double> r;
    r << (*vec)[0];
    r << (*vec)[1];
    return r;
  }

  void         setValue(SbVec2d* vec, const QList<double>& values)
  {
    if (values.size() != 2) {
      throw std::range_error("SbVec2d::setValue expects 2 values.");
    }
    vec->setValue(values.at(0), values.at(1));
  }

  QList<double> toTuple(SbVec2d* vec) { return getValue(vec); }

  void  __setitem__(SbVec2d* vec, int index, double value)
  {
    if (index<0 || index>=2) {
      throw std::range_error("SbVec2d::__setitem__ out of range!");
    }
    (*vec)[index] = value;
  }

  double __getitem__(SbVec2d* vec, int index)
  {
    if (index<0 || index>=2) {
      throw std::range_error("SbVec2d::__getitem__ out of range!");
    }
    return (*vec)[index];
  }

  int   __len__(SbVec2d* vec) { return 2; }

};





class PythonQtShell_SbVec2f : public SbVec2f
{
public:
    PythonQtShell_SbVec2f():SbVec2f(),_wrapper(nullptr) {};
    PythonQtShell_SbVec2f(float  x, float  y):SbVec2f(x, y),_wrapper(nullptr) {};

   ~PythonQtShell_SbVec2f();


  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SbVec2f : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbVec2f* new_SbVec2f();
SbVec2f* new_SbVec2f(float  x, float  y);
SbVec2f* new_SbVec2f(const SbVec2f& other) {
PythonQtShell_SbVec2f* a = new PythonQtShell_SbVec2f();
*((SbVec2f*)a) = other;
return a; }
void delete_SbVec2f(SbVec2f* obj) { delete obj; }
   float  dot(SbVec2f* theWrappedObject, const SbVec2f&  v) const;
   bool  equals(SbVec2f* theWrappedObject, const SbVec2f  v, float  tolerance) const;
   float  length(SbVec2f* theWrappedObject) const;
   void negate(SbVec2f* theWrappedObject);
   float  normalize(SbVec2f* theWrappedObject);
   bool  __ne__(SbVec2f* theWrappedObject, const SbVec2f&  v2);
   SbVec2f  __mul__(SbVec2f* theWrappedObject, float  d);
   SbVec2f*  __imul__(SbVec2f* theWrappedObject, float  d);
   SbVec2f  __add__(SbVec2f* theWrappedObject, const SbVec2f&  v2);
   SbVec2f*  __iadd__(SbVec2f* theWrappedObject, const SbVec2f&  u);
   SbVec2f  __sub__(SbVec2f* theWrappedObject) const;
   SbVec2f  __sub__(SbVec2f* theWrappedObject, const SbVec2f&  v2);
   SbVec2f*  __isub__(SbVec2f* theWrappedObject, const SbVec2f&  u);
   SbVec2f  __div__(SbVec2f* theWrappedObject, float  d);
   SbVec2f*  __idiv__(SbVec2f* theWrappedObject, float  d);
   bool  __eq__(SbVec2f* theWrappedObject, const SbVec2f&  v2);
   SbVec2f*  setValue(SbVec2f* theWrappedObject, float  x, float  y);

  SbVec2d toVec2d( SbVec2f* vec )
  {
    const float* value = vec->getValue();
    return SbVec2d(value[0], value[1]);
  }

  QList<float> getValue(SbVec2f* vec)
  {
    QList<float> r;
    r << (*vec)[0];
    r << (*vec)[1];
    return r;
  }

  void         setValue(SbVec2f* vec, const QList<float>& values)
  {
    if (values.size() != 2) {
      throw std::range_error("SbVec2f::setValue expects 2 values.");
    }
    vec->setValue(values.at(0), values.at(1));
  }

  QList<float> toTuple(SbVec2f* vec) { return getValue(vec); }

  void  __setitem__(SbVec2f* vec, int index, float value)
  {
    if (index<0 || index>=2) {
      throw std::range_error("SbVec2f::__setitem__ out of range!");
    }
    (*vec)[index] = value;
  }

  float __getitem__(SbVec2f* vec, int index)
  {
    if (index<0 || index>=2) {
      throw std::range_error("SbVec2f::__getitem__ out of range!");
    }
    return (*vec)[index];
  }

  int   __len__(SbVec2f* vec) { return 2; }

};





class PythonQtShell_SbVec2s : public SbVec2s
{
public:
    PythonQtShell_SbVec2s():SbVec2s(),_wrapper(nullptr) {};
    PythonQtShell_SbVec2s(short  x, short  y):SbVec2s(x, y),_wrapper(nullptr) {};

   ~PythonQtShell_SbVec2s();


  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SbVec2s : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbVec2s* new_SbVec2s();
SbVec2s* new_SbVec2s(short  x, short  y);
SbVec2s* new_SbVec2s(const SbVec2s& other) {
PythonQtShell_SbVec2s* a = new PythonQtShell_SbVec2s();
*((SbVec2s*)a) = other;
return a; }
void delete_SbVec2s(SbVec2s* obj) { delete obj; }
   int  dot(SbVec2s* theWrappedObject, const SbVec2s&  v) const;
   void negate(SbVec2s* theWrappedObject);
   bool  __ne__(SbVec2s* theWrappedObject, const SbVec2s&  v2);
   SbVec2s  __mul__(SbVec2s* theWrappedObject, double  d);
   SbVec2s  __mul__(SbVec2s* theWrappedObject, int  d);
   SbVec2s*  __imul__(SbVec2s* theWrappedObject, double  d);
   SbVec2s*  __imul__(SbVec2s* theWrappedObject, int  d);
   SbVec2s  __add__(SbVec2s* theWrappedObject, const SbVec2s&  v2);
   SbVec2s*  __iadd__(SbVec2s* theWrappedObject, const SbVec2s&  u);
   SbVec2s  __sub__(SbVec2s* theWrappedObject) const;
   SbVec2s  __sub__(SbVec2s* theWrappedObject, const SbVec2s&  v2);
   SbVec2s*  __isub__(SbVec2s* theWrappedObject, const SbVec2s&  u);
   SbVec2s  __div__(SbVec2s* theWrappedObject, double  d);
   SbVec2s  __div__(SbVec2s* theWrappedObject, int  d);
   SbVec2s*  __idiv__(SbVec2s* theWrappedObject, double  d);
   SbVec2s*  __idiv__(SbVec2s* theWrappedObject, int  d);
   bool  __eq__(SbVec2s* theWrappedObject, const SbVec2s&  v2);
   SbVec2s*  setValue(SbVec2s* theWrappedObject, short  x, short  y);

  QList<int> getValue(SbVec2s* vec)
  {
    QList<int> r;
    r << (*vec)[0];
    r << (*vec)[1];
    return r;
  }

  void         setValue(SbVec2s* vec, const QList<int>& values)
  {
    if (values.size() != 2) {
      throw std::range_error("SbVec2s::setValue expects 2 values.");
    }
    vec->setValue(values.at(0), values.at(1));
  }

  QList<int> toTuple(SbVec2s* vec) { return getValue(vec); }

  void  __setitem__(SbVec2s* vec, int index, short value)
  {
    if (index<0 || index>=2) {
      throw std::range_error("SbVec2s::__setitem__ out of range!");
    }
    (*vec)[index] = value;
  }

  short __getitem__(SbVec2s* vec, int index)
  {
    if (index<0 || index>=2) {
      throw std::range_error("SbVec2s::__getitem__ out of range!");
    }
    return (*vec)[index];
  }

  int   __len__(SbVec2s* vec) { return 2; }

};





class PythonQtShell_SbVec3d : public SbVec3d
{
public:
    PythonQtShell_SbVec3d():SbVec3d(),_wrapper(nullptr) {};
    PythonQtShell_SbVec3d(SbPlaned&  p0, SbPlaned&  p1, SbPlaned&  p2):SbVec3d(p0, p1, p2),_wrapper(nullptr) {};
    PythonQtShell_SbVec3d(double  x, double  y, double  z):SbVec3d(x, y, z),_wrapper(nullptr) {};

   ~PythonQtShell_SbVec3d();


  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SbVec3d : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbVec3d* new_SbVec3d();
SbVec3d* new_SbVec3d(SbPlaned&  p0, SbPlaned&  p1, SbPlaned&  p2);
SbVec3d* new_SbVec3d(double  x, double  y, double  z);
SbVec3d* new_SbVec3d(const SbVec3d& other) {
PythonQtShell_SbVec3d* a = new PythonQtShell_SbVec3d();
*((SbVec3d*)a) = other;
return a; }
void delete_SbVec3d(SbVec3d* obj) { delete obj; }
   SbVec3d  cross(SbVec3d* theWrappedObject, const SbVec3d&  v) const;
   double  dot(SbVec3d* theWrappedObject, const SbVec3d&  v) const;
   bool  equals(SbVec3d* theWrappedObject, const SbVec3d  v, double  tolerance) const;
   SbVec3d  getClosestAxis(SbVec3d* theWrappedObject) const;
   double  length(SbVec3d* theWrappedObject) const;
   void negate(SbVec3d* theWrappedObject);
   double  normalize(SbVec3d* theWrappedObject);
   bool  __ne__(SbVec3d* theWrappedObject, const SbVec3d&  v2);
   SbVec3d  __mul__(SbVec3d* theWrappedObject, double  d);
   SbVec3d*  __imul__(SbVec3d* theWrappedObject, double  d);
   SbVec3d  __add__(SbVec3d* theWrappedObject, const SbVec3d&  v2);
   SbVec3d*  __iadd__(SbVec3d* theWrappedObject, SbVec3d  v);
   SbVec3d  __sub__(SbVec3d* theWrappedObject) const;
   SbVec3d  __sub__(SbVec3d* theWrappedObject, const SbVec3d&  v2);
   SbVec3d*  __isub__(SbVec3d* theWrappedObject, SbVec3d  v);
   SbVec3d  __div__(SbVec3d* theWrappedObject, double  d);
   SbVec3d*  __idiv__(SbVec3d* theWrappedObject, double  d);
   bool  __eq__(SbVec3d* theWrappedObject, const SbVec3d&  v2);
   SbVec3d*  setValue(SbVec3d* theWrappedObject, const SbVec3d&  barycentic, const SbVec3d&  v0, const SbVec3d&  v1, const SbVec3d&  v2);
   SbVec3d*  setValue(SbVec3d* theWrappedObject, double  x, double  y, double  z);

  SbVec3f toVec3f( SbVec3d* vec )
  {
    const double* value = vec->getValue();
    return SbVec3f(value[0], value[1], value[2]);
  }

  QList<double> getValue(SbVec3d* vec)
  {
    QList<double> r;
    r << (*vec)[0];
    r << (*vec)[1];
    r << (*vec)[2];
    return r;
  }

  void         setValue(SbVec3d* vec, const QList<double>& values)
  {
    if (values.size() != 3) {
      throw std::range_error("SbVec3d::setValue expects 3 values.");
    }
    vec->setValue(values.at(0), values.at(1), values.at(2));
  }

  QList<double> toTuple(SbVec3d* vec) { return getValue(vec); }

  void  __setitem__(SbVec3d* vec, int index, double value)
  {
    if (index<0 || index>=3) {
      throw std::range_error("SbVec3d::__setitem__ out of range!");
    }
    (*vec)[index] = value;
  }

  double __getitem__(SbVec3d* vec, int index)
  {
    if (index<0 || index>=3) {
      throw std::range_error("SbVec3d::__getitem__ out of range!");
    }
    return (*vec)[index];
  }

  int   __len__(SbVec3d* vec) { return 3; }

};





class PythonQtShell_SbVec3f : public SbVec3f
{
public:
    PythonQtShell_SbVec3f():SbVec3f(),_wrapper(nullptr) {};
    PythonQtShell_SbVec3f(SbPlane&  p0, SbPlane&  p1, SbPlane&  p2):SbVec3f(p0, p1, p2),_wrapper(nullptr) {};
    PythonQtShell_SbVec3f(float  x, float  y, float  z):SbVec3f(x, y, z),_wrapper(nullptr) {};

   ~PythonQtShell_SbVec3f();


  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SbVec3f : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbVec3f* new_SbVec3f();
SbVec3f* new_SbVec3f(SbPlane&  p0, SbPlane&  p1, SbPlane&  p2);
SbVec3f* new_SbVec3f(float  x, float  y, float  z);
SbVec3f* new_SbVec3f(const SbVec3f& other) {
PythonQtShell_SbVec3f* a = new PythonQtShell_SbVec3f();
*((SbVec3f*)a) = other;
return a; }
void delete_SbVec3f(SbVec3f* obj) { delete obj; }
   SbVec3f  cross(SbVec3f* theWrappedObject, const SbVec3f&  v) const;
   float  dot(SbVec3f* theWrappedObject, const SbVec3f&  v) const;
   bool  equals(SbVec3f* theWrappedObject, const SbVec3f  v, float  tolerance) const;
   SbVec3f  getClosestAxis(SbVec3f* theWrappedObject) const;
   float  length(SbVec3f* theWrappedObject) const;
   void negate(SbVec3f* theWrappedObject);
   float  normalize(SbVec3f* theWrappedObject);
   bool  __ne__(SbVec3f* theWrappedObject, const SbVec3f&  v2);
   SbVec3f  __mul__(SbVec3f* theWrappedObject, float  d);
   SbVec3f*  __imul__(SbVec3f* theWrappedObject, float  d);
   SbVec3f  __add__(SbVec3f* theWrappedObject, const SbVec3f&  v2);
   SbVec3f*  __iadd__(SbVec3f* theWrappedObject, SbVec3f  v);
   SbVec3f  __sub__(SbVec3f* theWrappedObject) const;
   SbVec3f  __sub__(SbVec3f* theWrappedObject, const SbVec3f&  v2);
   SbVec3f*  __isub__(SbVec3f* theWrappedObject, SbVec3f  v);
   SbVec3f  __div__(SbVec3f* theWrappedObject, float  d);
   SbVec3f*  __idiv__(SbVec3f* theWrappedObject, float  d);
   bool  __eq__(SbVec3f* theWrappedObject, const SbVec3f&  v2);
   SbVec3f*  setValue(SbVec3f* theWrappedObject, const SbVec3f&  barycentic, const SbVec3f&  v0, const SbVec3f&  v1, const SbVec3f&  v2);
   SbVec3f*  setValue(SbVec3f* theWrappedObject, float  x, float  y, float  z);

  SbVec3d toVec3d( SbVec3f* vec )
  {
    const float* value = vec->getValue();
    return SbVec3d(value[0], value[1], value[2]);
  }

  QList<float> getValue(SbVec3f* vec)
  {
    QList<float> r;
    r << (*vec)[0];
    r << (*vec)[1];
    r << (*vec)[2];
    return r;
  }

  void         setValue(SbVec3f* vec, const QList<float>& values)
  {
    if (values.size() != 3) {
      throw std::range_error("SbVec3f::setValue expects 3 values.");
    }
    vec->setValue(values.at(0), values.at(1), values.at(2));
  }

  QList<float> toTuple(SbVec3f* vec) { return getValue(vec); }

  void  __setitem__(SbVec3f* vec, int index, float value)
  {
    if (index<0 || index>=3) {
      throw std::range_error("SbVec3f::__setitem__ out of range!");
    }
    (*vec)[index] = value;
  }

  float __getitem__(SbVec3f* vec, int index)
  {
    if (index<0 || index>=3) {
      throw std::range_error("SbVec3f::__getitem__ out of range!");
    }
    return (*vec)[index];
  }

  int   __len__(SbVec3f* vec) { return 3; }

};





class PythonQtShell_SbVec3s : public SbVec3s
{
public:
    PythonQtShell_SbVec3s():SbVec3s(),_wrapper(nullptr) {};
    PythonQtShell_SbVec3s(short  x, short  y, short  z):SbVec3s(x, y, z),_wrapper(nullptr) {};

   ~PythonQtShell_SbVec3s();


  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SbVec3s : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbVec3s* new_SbVec3s();
SbVec3s* new_SbVec3s(short  x, short  y, short  z);
SbVec3s* new_SbVec3s(const SbVec3s& other) {
PythonQtShell_SbVec3s* a = new PythonQtShell_SbVec3s();
*((SbVec3s*)a) = other;
return a; }
void delete_SbVec3s(SbVec3s* obj) { delete obj; }
   int  dot(SbVec3s* theWrappedObject, const SbVec3s&  v) const;
   void negate(SbVec3s* theWrappedObject);
   bool  __ne__(SbVec3s* theWrappedObject, const SbVec3s&  v2);
   SbVec3s  __mul__(SbVec3s* theWrappedObject, double  d);
   SbVec3s  __mul__(SbVec3s* theWrappedObject, int  d);
   SbVec3s*  __imul__(SbVec3s* theWrappedObject, double  d);
   SbVec3s*  __imul__(SbVec3s* theWrappedObject, int  d);
   SbVec3s  __add__(SbVec3s* theWrappedObject, const SbVec3s&  v2);
   SbVec3s*  __iadd__(SbVec3s* theWrappedObject, const SbVec3s&  u);
   SbVec3s  __sub__(SbVec3s* theWrappedObject) const;
   SbVec3s  __sub__(SbVec3s* theWrappedObject, const SbVec3s&  v2);
   SbVec3s*  __isub__(SbVec3s* theWrappedObject, const SbVec3s&  u);
   SbVec3s  __div__(SbVec3s* theWrappedObject, double  d);
   SbVec3s  __div__(SbVec3s* theWrappedObject, int  d);
   SbVec3s*  __idiv__(SbVec3s* theWrappedObject, double  d);
   SbVec3s*  __idiv__(SbVec3s* theWrappedObject, int  d);
   bool  __eq__(SbVec3s* theWrappedObject, const SbVec3s&  v2);
   SbVec3s*  setValue(SbVec3s* theWrappedObject, short  x, short  y, short  z);

  QList<int> getValue(SbVec3s* vec)
  {
    QList<int> r;
    r << (*vec)[0];
    r << (*vec)[1];
    r << (*vec)[2];
    return r;
  }

  void         setValue(SbVec3s* vec, const QList<int>& values)
  {
    if (values.size() != 3) {
      throw std::range_error("SbVec3s::setValue expects 3 values.");
    }
    vec->setValue(values.at(0), values.at(1), values.at(2));
  }

  QList<int> toTuple(SbVec3s* vec) { return getValue(vec); }

  void  __setitem__(SbVec3s* vec, int index, short value)
  {
    if (index<0 || index>=3) {
      throw std::range_error("SbVec3s::__setitem__ out of range!");
    }
    (*vec)[index] = value;
  }

  short __getitem__(SbVec3s* vec, int index)
  {
    if (index<0 || index>=3) {
      throw std::range_error("SbVec3s::__getitem__ out of range!");
    }
    return (*vec)[index];
  }

  int   __len__(SbVec3s* vec) { return 3; }

};





class PythonQtShell_SbVec4d : public SbVec4d
{
public:
    PythonQtShell_SbVec4d():SbVec4d(),_wrapper(nullptr) {};
    PythonQtShell_SbVec4d(double  x, double  y, double  z, double  w):SbVec4d(x, y, z, w),_wrapper(nullptr) {};

   ~PythonQtShell_SbVec4d();


  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SbVec4d : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbVec4d* new_SbVec4d();
SbVec4d* new_SbVec4d(double  x, double  y, double  z, double  w);
SbVec4d* new_SbVec4d(const SbVec4d& other) {
PythonQtShell_SbVec4d* a = new PythonQtShell_SbVec4d();
*((SbVec4d*)a) = other;
return a; }
void delete_SbVec4d(SbVec4d* obj) { delete obj; }
   double  dot(SbVec4d* theWrappedObject, const SbVec4d&  v) const;
   bool  equals(SbVec4d* theWrappedObject, const SbVec4d  v, double  tolerance) const;
   SbVec3d  getReal(SbVec4d* theWrappedObject) const;
   double  length(SbVec4d* theWrappedObject) const;
   void negate(SbVec4d* theWrappedObject);
   double  normalize(SbVec4d* theWrappedObject);
   bool  __ne__(SbVec4d* theWrappedObject, const SbVec4d&  v2);
   SbVec4d  __mul__(SbVec4d* theWrappedObject, double  d);
   SbVec4d*  __imul__(SbVec4d* theWrappedObject, double  d);
   SbVec4d  __add__(SbVec4d* theWrappedObject, const SbVec4d&  v2);
   SbVec4d*  __iadd__(SbVec4d* theWrappedObject, const SbVec4d&  u);
   SbVec4d  __sub__(SbVec4d* theWrappedObject) const;
   SbVec4d  __sub__(SbVec4d* theWrappedObject, const SbVec4d&  v2);
   SbVec4d*  __isub__(SbVec4d* theWrappedObject, const SbVec4d&  u);
   SbVec4d  __div__(SbVec4d* theWrappedObject, double  d);
   SbVec4d*  __idiv__(SbVec4d* theWrappedObject, double  d);
   bool  __eq__(SbVec4d* theWrappedObject, const SbVec4d&  v2);
   SbVec4d*  setValue(SbVec4d* theWrappedObject, double  x, double  y, double  z, double  w);

  SbVec4f toVec4f( SbVec4d* vec )
  {
    const double* value = vec->getValue();
    return SbVec4f(value[0], value[1], value[2], value[3]);
  }

  QList<double> getValue(SbVec4d* vec)
  {
    QList<double> r;
    r << (*vec)[0];
    r << (*vec)[1];
    r << (*vec)[2];
    r << (*vec)[3];
    return r;
  }

  void         setValue(SbVec4d* vec, const QList<double>& values)
  {
    if (values.size() != 4) {
      throw std::range_error("SbVec4d::setValue expects 4 values.");
    }
    vec->setValue(values.at(0), values.at(1), values.at(2), values.at(3));
  }

  QList<double> toTuple(SbVec4d* vec) { return getValue(vec); }

  void  __setitem__(SbVec4d* vec, int index, double value)
  {
    if (index<0 || index>=4) {
      throw std::range_error("SbVec4d::__setitem__ out of range!");
    }
    (*vec)[index] = value;
  }

  double __getitem__(SbVec4d* vec, int index)
  {
    if (index<0 || index>=4) {
      throw std::range_error("SbVec4d::__getitem__ out of range!");
    }
    return (*vec)[index];
  }

  int   __len__(SbVec4d* vec) { return 4; }

};





class PythonQtShell_SbVec4f : public SbVec4f
{
public:
    PythonQtShell_SbVec4f():SbVec4f(),_wrapper(nullptr) {};
    PythonQtShell_SbVec4f(float  x, float  y, float  z, float  w):SbVec4f(x, y, z, w),_wrapper(nullptr) {};

   ~PythonQtShell_SbVec4f();


  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SbVec4f : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbVec4f* new_SbVec4f();
SbVec4f* new_SbVec4f(float  x, float  y, float  z, float  w);
SbVec4f* new_SbVec4f(const SbVec4f& other) {
PythonQtShell_SbVec4f* a = new PythonQtShell_SbVec4f();
*((SbVec4f*)a) = other;
return a; }
void delete_SbVec4f(SbVec4f* obj) { delete obj; }
   float  dot(SbVec4f* theWrappedObject, const SbVec4f&  v) const;
   bool  equals(SbVec4f* theWrappedObject, const SbVec4f  v, float  tolerance) const;
   SbVec3f  getReal(SbVec4f* theWrappedObject) const;
   float  length(SbVec4f* theWrappedObject) const;
   void negate(SbVec4f* theWrappedObject);
   float  normalize(SbVec4f* theWrappedObject);
   bool  __ne__(SbVec4f* theWrappedObject, const SbVec4f&  v2);
   SbVec4f  __mul__(SbVec4f* theWrappedObject, float  d);
   SbVec4f*  __imul__(SbVec4f* theWrappedObject, float  d);
   SbVec4f  __add__(SbVec4f* theWrappedObject, const SbVec4f&  v2);
   SbVec4f*  __iadd__(SbVec4f* theWrappedObject, const SbVec4f&  u);
   SbVec4f  __sub__(SbVec4f* theWrappedObject) const;
   SbVec4f  __sub__(SbVec4f* theWrappedObject, const SbVec4f&  v2);
   SbVec4f*  __isub__(SbVec4f* theWrappedObject, const SbVec4f&  u);
   SbVec4f  __div__(SbVec4f* theWrappedObject, float  d);
   SbVec4f*  __idiv__(SbVec4f* theWrappedObject, float  d);
   bool  __eq__(SbVec4f* theWrappedObject, const SbVec4f&  v2);
   SbVec4f*  setValue(SbVec4f* theWrappedObject, float  x, float  y, float  z, float  w);

  SbVec4d toVec4d( SbVec4f* vec )
  {
    const float* value = vec->getValue();
    return SbVec4d(value[0], value[1], value[2], value[3]);
  }

  QList<float> getValue(SbVec4f* vec)
  {
    QList<float> r;
    r << (*vec)[0];
    r << (*vec)[1];
    r << (*vec)[2];
    r << (*vec)[3];
    return r;
  }

  void         setValue(SbVec4f* vec, const QList<float>& values)
  {
    if (values.size() != 4) {
      throw std::range_error("SbVec4f::setValue expects 4 values.");
    }
    vec->setValue(values.at(0), values.at(1), values.at(2), values.at(3));
  }

  QList<float> toTuple(SbVec4f* vec) { return getValue(vec); }

  void  __setitem__(SbVec4f* vec, int index, float value)
  {
    if (index<0 || index>=4) {
      throw std::range_error("SbVec4f::__setitem__ out of range!");
    }
    (*vec)[index] = value;
  }

  float __getitem__(SbVec4f* vec, int index)
  {
    if (index<0 || index>=4) {
      throw std::range_error("SbVec4f::__getitem__ out of range!");
    }
    return (*vec)[index];
  }

  int   __len__(SbVec4f* vec) { return 4; }

};





class PythonQtShell_SbViewVolume : public SbViewVolume
{
public:
    PythonQtShell_SbViewVolume():SbViewVolume(),_wrapper(nullptr) {};

   ~PythonQtShell_SbViewVolume();


  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SbViewVolume : public QObject
{ Q_OBJECT
public:
Q_ENUMS(ProjectionType )
enum ProjectionType{
  ORTHOGRAPHIC = SbViewVolume::ORTHOGRAPHIC,   PERSPECTIVE = SbViewVolume::PERSPECTIVE};
public Q_SLOTS:
SbViewVolume* new_SbViewVolume();
SbViewVolume* new_SbViewVolume(const SbViewVolume& other) {
PythonQtShell_SbViewVolume* a = new PythonQtShell_SbViewVolume();
*((SbViewVolume*)a) = other;
return a; }
void delete_SbViewVolume(SbViewVolume* obj) { delete obj; }
   SbRotation  getAlignRotation(SbViewVolume* theWrappedObject, bool  rightAngleOnly = 0) const;
   SbMatrix  getCameraSpaceMatrix(SbViewVolume* theWrappedObject) const;
   float  getDepth(SbViewVolume* theWrappedObject) const;
   float  getFarDist(SbViewVolume* theWrappedObject) const;
   float  getHeight(SbViewVolume* theWrappedObject) const;
   SbMatrix  getMatrix(SbViewVolume* theWrappedObject) const;
   float  getNearDist(SbViewVolume* theWrappedObject) const;
   SbPlane  getPlane(SbViewVolume* theWrappedObject, float  distFromEye) const;
   SbVec3f  getPlanePoint(SbViewVolume* theWrappedObject, float  distFromEye, const SbVec2f&  normPoint) const;
   const SbVec3f*  getProjectionDirection(SbViewVolume* theWrappedObject) const;
   SbMatrix  getProjectionMatrix(SbViewVolume* theWrappedObject) const;
   const SbVec3f*  getProjectionPoint(SbViewVolume* theWrappedObject) const;
   SbViewVolume::ProjectionType  getProjectionType(SbViewVolume* theWrappedObject) const;
   SbVec3f  getSightPoint(SbViewVolume* theWrappedObject, float  distFromEye) const;
   SbMatrix  getViewingMatrix(SbViewVolume* theWrappedObject) const;
   float  getWidth(SbViewVolume* theWrappedObject) const;
   float  getWorldToScreenScale(SbViewVolume* theWrappedObject, const SbVec3f&  worldCenter, float  normRadius) const;
   bool  intersect(SbViewVolume* theWrappedObject, const SbBox3f&  box) const;
   bool  intersect(SbViewVolume* theWrappedObject, const SbVec3f&  point) const;
   SbViewVolume  narrow(SbViewVolume* theWrappedObject, const SbBox3f&  box) const;
   SbViewVolume  narrow(SbViewVolume* theWrappedObject, float  left, float  bottom, float  right, float  top) const;
   void ortho(SbViewVolume* theWrappedObject, float  left, float  right, float  bottom, float  top, float  nearVal, float  farVal);
   bool  outsideTest(SbViewVolume* theWrappedObject, const SbPlane&  p, const SbVec3f&  min, const SbVec3f&  max) const;
   void perspective(SbViewVolume* theWrappedObject, float  fovy, float  aspect, float  nearVal, float  farVal);
   SbVec2f  projectBox(SbViewVolume* theWrappedObject, const SbBox3f&  box) const;
   SbLine  projectPointToLine(SbViewVolume* theWrappedObject, const SbVec2f&  pt) const;
   SbVec3f  projectToScreen(SbViewVolume* theWrappedObject, const SbVec3f&  src) const;
   void rotateCamera(SbViewVolume* theWrappedObject, const SbRotation&  q);
   void scale(SbViewVolume* theWrappedObject, float  factor);
   void scaleHeight(SbViewVolume* theWrappedObject, float  ratio);
   void scaleWidth(SbViewVolume* theWrappedObject, float  ratio);
   void transform(SbViewVolume* theWrappedObject, const SbMatrix&  matrix);
   void translateCamera(SbViewVolume* theWrappedObject, const SbVec3f&  v);
   SbViewVolume  zNarrow(SbViewVolume* theWrappedObject, float  nearVal, float  farVal) const;
   SbVec3f  zVector(SbViewVolume* theWrappedObject) const;
void py_set_llf(SbViewVolume* theWrappedObject, SbVec3f  llf){ theWrappedObject->llf = llf; }
SbVec3f  py_get_llf(SbViewVolume* theWrappedObject){ return theWrappedObject->llf; }
void py_set_lrf(SbViewVolume* theWrappedObject, SbVec3f  lrf){ theWrappedObject->lrf = lrf; }
SbVec3f  py_get_lrf(SbViewVolume* theWrappedObject){ return theWrappedObject->lrf; }
void py_set_nearDist(SbViewVolume* theWrappedObject, float  nearDist){ theWrappedObject->nearDist = nearDist; }
float  py_get_nearDist(SbViewVolume* theWrappedObject){ return theWrappedObject->nearDist; }
void py_set_nearToFar(SbViewVolume* theWrappedObject, float  nearToFar){ theWrappedObject->nearToFar = nearToFar; }
float  py_get_nearToFar(SbViewVolume* theWrappedObject){ return theWrappedObject->nearToFar; }
void py_set_projDir(SbViewVolume* theWrappedObject, SbVec3f  projDir){ theWrappedObject->projDir = projDir; }
SbVec3f  py_get_projDir(SbViewVolume* theWrappedObject){ return theWrappedObject->projDir; }
void py_set_projPoint(SbViewVolume* theWrappedObject, SbVec3f  projPoint){ theWrappedObject->projPoint = projPoint; }
SbVec3f  py_get_projPoint(SbViewVolume* theWrappedObject){ return theWrappedObject->projPoint; }
void py_set_type(SbViewVolume* theWrappedObject, SbViewVolume::ProjectionType  type){ theWrappedObject->type = type; }
SbViewVolume::ProjectionType  py_get_type(SbViewVolume* theWrappedObject){ return theWrappedObject->type; }
void py_set_ulf(SbViewVolume* theWrappedObject, SbVec3f  ulf){ theWrappedObject->ulf = ulf; }
SbVec3f  py_get_ulf(SbViewVolume* theWrappedObject){ return theWrappedObject->ulf; }
};





class PythonQtWrapper_SbViewportRegion : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbViewportRegion* new_SbViewportRegion();
SbViewportRegion* new_SbViewportRegion(SbVec2s  winSize);
SbViewportRegion* new_SbViewportRegion(const SbViewportRegion&  vpReg);
SbViewportRegion* new_SbViewportRegion(short  width, short  height);
void delete_SbViewportRegion(SbViewportRegion* obj) { delete obj; }
   float  getPixelsPerInch(SbViewportRegion* theWrappedObject) const;
   float  getPixelsPerPoint(SbViewportRegion* theWrappedObject) const;
   float  getViewportAspectRatio(SbViewportRegion* theWrappedObject) const;
   const SbVec2f*  getViewportOrigin(SbViewportRegion* theWrappedObject) const;
   const SbVec2s*  getViewportOriginPixels(SbViewportRegion* theWrappedObject) const;
   const SbVec2f*  getViewportSize(SbViewportRegion* theWrappedObject) const;
   const SbVec2s*  getViewportSizePixels(SbViewportRegion* theWrappedObject) const;
   const SbVec2s*  getWindowSize(SbViewportRegion* theWrappedObject) const;
   void scaleHeight(SbViewportRegion* theWrappedObject, float  ratio);
   void scaleWidth(SbViewportRegion* theWrappedObject, float  ratio);
   void setPixelsPerInch(SbViewportRegion* theWrappedObject, float  ppi);
   void setViewport(SbViewportRegion* theWrappedObject, SbVec2f  origin, SbVec2f  size);
   void setViewport(SbViewportRegion* theWrappedObject, float  left, float  bottom, float  width, float  height);
   void setViewportPixels(SbViewportRegion* theWrappedObject, SbVec2s  origin, SbVec2s  size);
   void setViewportPixels(SbViewportRegion* theWrappedObject, short  left, short  bottom, short  width, short  height);
   void setWindowSize(SbViewportRegion* theWrappedObject, SbVec2s  winSize);
   void setWindowSize(SbViewportRegion* theWrappedObject, short  width, short  height);
};


