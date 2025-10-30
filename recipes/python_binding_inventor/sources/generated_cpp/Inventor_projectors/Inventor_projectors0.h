#include <Inventor/SbLinear.h>
#include <Inventor/projectors/SbCylinderPlaneProjector.h>
#include <Inventor/projectors/SbCylinderProjector.h>
#include <Inventor/projectors/SbCylinderSectionProjector.h>
#include <Inventor/projectors/SbCylinderSheetProjector.h>
#include <Inventor/projectors/SbLineProjector.h>
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/projectors/SbProjector.h>
#include <Inventor/projectors/SbSpherePlaneProjector.h>
#include <Inventor/projectors/SbSphereProjector.h>
#include <Inventor/projectors/SbSphereSectionProjector.h>
#include <Inventor/projectors/SbSphereSheetProjector.h>
#include <PythonQt.h>
#include <QObject>
#include <QVariant>



class PythonQtShell_SbCylinderPlaneProjector : public SbCylinderPlaneProjector
{
public:
    PythonQtShell_SbCylinderPlaneProjector(const SbCylinder&  cyl, float  edgeTol = .9, bool  orientToEye = 1):SbCylinderPlaneProjector(cyl, edgeTol, orientToEye),_wrapper(nullptr) {};
    PythonQtShell_SbCylinderPlaneProjector(float  edgeTol = .9, bool  orientToEye = 1):SbCylinderPlaneProjector(edgeTol, orientToEye),_wrapper(nullptr) {};

   ~PythonQtShell_SbCylinderPlaneProjector() override;

SbProjector*  copy() const override;
SbRotation  getRotation(const SbVec3f&  point1, const SbVec3f&  point2) override;
SbVec3f  project(const SbVec2f&  point) override;
void setViewVolume(const SbViewVolume&  vol) override;
void setWorkingSpace(const SbMatrix&  space) override;
void setupTolerance() override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SbCylinderPlaneProjector : public SbCylinderPlaneProjector
{ public:
inline SbRotation  promoted_getRotation(const SbVec3f&  point1, bool  tol1, const SbVec3f&  point2, bool  tol2) { return this->getRotation(point1, tol1, point2, tol2); }
inline SbProjector*  py_q_copy() const { return SbCylinderPlaneProjector::copy(); }
inline SbRotation  py_q_getRotation(const SbVec3f&  point1, const SbVec3f&  point2) { return SbCylinderPlaneProjector::getRotation(point1, point2); }
inline SbVec3f  py_q_project(const SbVec2f&  point) { return SbCylinderPlaneProjector::project(point); }
};

class PythonQtWrapper_SbCylinderPlaneProjector : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbCylinderPlaneProjector* new_SbCylinderPlaneProjector(const SbCylinder&  cyl, float  edgeTol = .9, bool  orientToEye = 1);
SbCylinderPlaneProjector* new_SbCylinderPlaneProjector(float  edgeTol = .9, bool  orientToEye = 1);
void delete_SbCylinderPlaneProjector(SbCylinderPlaneProjector* obj) { delete obj; }
   SbProjector*  py_q_copy(SbCylinderPlaneProjector* theWrappedObject) const{  return (((PythonQtPublicPromoter_SbCylinderPlaneProjector*)theWrappedObject)->py_q_copy());}
   SbRotation  getRotation(SbCylinderPlaneProjector* theWrappedObject, const SbVec3f&  point1, bool  tol1, const SbVec3f&  point2, bool  tol2);
   SbRotation  py_q_getRotation(SbCylinderPlaneProjector* theWrappedObject, const SbVec3f&  point1, const SbVec3f&  point2){  return (((PythonQtPublicPromoter_SbCylinderPlaneProjector*)theWrappedObject)->py_q_getRotation(point1, point2));}
   SbVec3f  py_q_project(SbCylinderPlaneProjector* theWrappedObject, const SbVec2f&  point){  return (((PythonQtPublicPromoter_SbCylinderPlaneProjector*)theWrappedObject)->py_q_project(point));}
};





class PythonQtShell_SbCylinderProjector : public SbCylinderProjector
{
public:
    PythonQtShell_SbCylinderProjector(bool  orientToEye):SbCylinderProjector(orientToEye),_wrapper(nullptr) {};
    PythonQtShell_SbCylinderProjector(const SbCylinder&  cyl, bool  orientToEye):SbCylinderProjector(cyl, orientToEye),_wrapper(nullptr) {};

   ~PythonQtShell_SbCylinderProjector() override;

SbProjector*  copy() const override;
SbRotation  getRotation(const SbVec3f&  point1, const SbVec3f&  point2) override;
SbVec3f  project(const SbVec2f&  point) override;
void setViewVolume(const SbViewVolume&  vol) override;
void setWorkingSpace(const SbMatrix&  space) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SbCylinderProjector : public SbCylinderProjector
{ public:
inline SbRotation  py_q_getRotation(const SbVec3f&  point1, const SbVec3f&  point2) { return this->getRotation(point1, point2); }
inline SbVec3f  py_q_project(const SbVec2f&  point) { return this->project(point); }
inline void py_q_setWorkingSpace(const SbMatrix&  space) { SbCylinderProjector::setWorkingSpace(space); }
};

class PythonQtWrapper_SbCylinderProjector : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbCylinderProjector* new_SbCylinderProjector(bool  orientToEye);
SbCylinderProjector* new_SbCylinderProjector(const SbCylinder&  cyl, bool  orientToEye);
void delete_SbCylinderProjector(SbCylinderProjector* obj) { delete obj; }
   const SbCylinder*  getCylinder(SbCylinderProjector* theWrappedObject) const;
   SbRotation  getRotation(SbCylinderProjector* theWrappedObject, const SbVec3f&  point1, const SbVec3f&  point2);
   SbRotation  py_q_getRotation(SbCylinderProjector* theWrappedObject, const SbVec3f&  point1, const SbVec3f&  point2){  return (((PythonQtPublicPromoter_SbCylinderProjector*)theWrappedObject)->py_q_getRotation(point1, point2));}
   bool  isFront(SbCylinderProjector* theWrappedObject) const;
   bool  isOrientToEye(SbCylinderProjector* theWrappedObject) const;
   bool  isPointInFront(SbCylinderProjector* theWrappedObject, const SbVec3f&  point) const;
   SbVec3f  py_q_project(SbCylinderProjector* theWrappedObject, const SbVec2f&  point){  return (((PythonQtPublicPromoter_SbCylinderProjector*)theWrappedObject)->py_q_project(point));}
   void setCylinder(SbCylinderProjector* theWrappedObject, const SbCylinder&  cyl);
   void setFront(SbCylinderProjector* theWrappedObject, bool  isFront);
   void setOrientToEye(SbCylinderProjector* theWrappedObject, bool  orientToEye);
   void py_q_setWorkingSpace(SbCylinderProjector* theWrappedObject, const SbMatrix&  space){  (((PythonQtPublicPromoter_SbCylinderProjector*)theWrappedObject)->py_q_setWorkingSpace(space));}
};





class PythonQtShell_SbCylinderSectionProjector : public SbCylinderSectionProjector
{
public:
    PythonQtShell_SbCylinderSectionProjector(const SbCylinder&  cyl, float  edgeTol = .9, bool  orientToEye = 1):SbCylinderSectionProjector(cyl, edgeTol, orientToEye),_wrapper(nullptr) {};
    PythonQtShell_SbCylinderSectionProjector(float  edgeTol = .9, bool  orientToEye = 1):SbCylinderSectionProjector(edgeTol, orientToEye),_wrapper(nullptr) {};

   ~PythonQtShell_SbCylinderSectionProjector() override;

SbProjector*  copy() const override;
SbRotation  getRotation(const SbVec3f&  point1, const SbVec3f&  point2) override;
SbVec3f  project(const SbVec2f&  point) override;
void setViewVolume(const SbViewVolume&  vol) override;
void setWorkingSpace(const SbMatrix&  space) override;
void setupTolerance() override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SbCylinderSectionProjector : public SbCylinderSectionProjector
{ public:
inline void promoted_setupTolerance() { this->setupTolerance(); }
inline SbProjector*  py_q_copy() const { return SbCylinderSectionProjector::copy(); }
inline SbRotation  py_q_getRotation(const SbVec3f&  point1, const SbVec3f&  point2) { return SbCylinderSectionProjector::getRotation(point1, point2); }
inline SbVec3f  py_q_project(const SbVec2f&  point) { return SbCylinderSectionProjector::project(point); }
inline void py_q_setupTolerance() { SbCylinderSectionProjector::setupTolerance(); }
};

class PythonQtWrapper_SbCylinderSectionProjector : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbCylinderSectionProjector* new_SbCylinderSectionProjector(const SbCylinder&  cyl, float  edgeTol = .9, bool  orientToEye = 1);
SbCylinderSectionProjector* new_SbCylinderSectionProjector(float  edgeTol = .9, bool  orientToEye = 1);
void delete_SbCylinderSectionProjector(SbCylinderSectionProjector* obj) { delete obj; }
   SbProjector*  py_q_copy(SbCylinderSectionProjector* theWrappedObject) const{  return (((PythonQtPublicPromoter_SbCylinderSectionProjector*)theWrappedObject)->py_q_copy());}
   SbRotation  py_q_getRotation(SbCylinderSectionProjector* theWrappedObject, const SbVec3f&  point1, const SbVec3f&  point2){  return (((PythonQtPublicPromoter_SbCylinderSectionProjector*)theWrappedObject)->py_q_getRotation(point1, point2));}
   float  getTolerance(SbCylinderSectionProjector* theWrappedObject) const;
   bool  isWithinTolerance(SbCylinderSectionProjector* theWrappedObject, const SbVec3f&  point);
   SbVec3f  py_q_project(SbCylinderSectionProjector* theWrappedObject, const SbVec2f&  point){  return (((PythonQtPublicPromoter_SbCylinderSectionProjector*)theWrappedObject)->py_q_project(point));}
   void setTolerance(SbCylinderSectionProjector* theWrappedObject, float  edgeTol);
   void setupTolerance(SbCylinderSectionProjector* theWrappedObject);
   void py_q_setupTolerance(SbCylinderSectionProjector* theWrappedObject){  (((PythonQtPublicPromoter_SbCylinderSectionProjector*)theWrappedObject)->py_q_setupTolerance());}
};





class PythonQtShell_SbCylinderSheetProjector : public SbCylinderSheetProjector
{
public:
    PythonQtShell_SbCylinderSheetProjector(bool  orientToEye = 1):SbCylinderSheetProjector(orientToEye),_wrapper(nullptr) {};
    PythonQtShell_SbCylinderSheetProjector(const SbCylinder&  cyl, bool  orientToEye = 1):SbCylinderSheetProjector(cyl, orientToEye),_wrapper(nullptr) {};

   ~PythonQtShell_SbCylinderSheetProjector() override;

SbProjector*  copy() const override;
SbRotation  getRotation(const SbVec3f&  point1, const SbVec3f&  point2) override;
SbVec3f  project(const SbVec2f&  point) override;
void setViewVolume(const SbViewVolume&  vol) override;
void setWorkingSpace(const SbMatrix&  space) override;
void setupPlane() override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SbCylinderSheetProjector : public SbCylinderSheetProjector
{ public:
inline void promoted_setupPlane() { this->setupPlane(); }
inline SbProjector*  py_q_copy() const { return SbCylinderSheetProjector::copy(); }
inline SbRotation  py_q_getRotation(const SbVec3f&  point1, const SbVec3f&  point2) { return SbCylinderSheetProjector::getRotation(point1, point2); }
inline SbVec3f  py_q_project(const SbVec2f&  point) { return SbCylinderSheetProjector::project(point); }
inline void py_q_setupPlane() { SbCylinderSheetProjector::setupPlane(); }
};

class PythonQtWrapper_SbCylinderSheetProjector : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbCylinderSheetProjector* new_SbCylinderSheetProjector(bool  orientToEye = 1);
SbCylinderSheetProjector* new_SbCylinderSheetProjector(const SbCylinder&  cyl, bool  orientToEye = 1);
void delete_SbCylinderSheetProjector(SbCylinderSheetProjector* obj) { delete obj; }
   SbProjector*  py_q_copy(SbCylinderSheetProjector* theWrappedObject) const{  return (((PythonQtPublicPromoter_SbCylinderSheetProjector*)theWrappedObject)->py_q_copy());}
   SbRotation  py_q_getRotation(SbCylinderSheetProjector* theWrappedObject, const SbVec3f&  point1, const SbVec3f&  point2){  return (((PythonQtPublicPromoter_SbCylinderSheetProjector*)theWrappedObject)->py_q_getRotation(point1, point2));}
   SbVec3f  py_q_project(SbCylinderSheetProjector* theWrappedObject, const SbVec2f&  point){  return (((PythonQtPublicPromoter_SbCylinderSheetProjector*)theWrappedObject)->py_q_project(point));}
   void setupPlane(SbCylinderSheetProjector* theWrappedObject);
   void py_q_setupPlane(SbCylinderSheetProjector* theWrappedObject){  (((PythonQtPublicPromoter_SbCylinderSheetProjector*)theWrappedObject)->py_q_setupPlane());}
};





class PythonQtShell_SbLineProjector : public SbLineProjector
{
public:
    PythonQtShell_SbLineProjector():SbLineProjector(),_wrapper(nullptr) {};

   ~PythonQtShell_SbLineProjector() override;

SbProjector*  copy() const override;
SbVec3f  getVector(const SbVec2f&  mousePosition) override;
SbVec3f  getVector(const SbVec2f&  mousePosition1, const SbVec2f&  mousePosition2) override;
SbVec3f  project(const SbVec2f&  point) override;
void setViewVolume(const SbViewVolume&  vol) override;
void setWorkingSpace(const SbMatrix&  space) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SbLineProjector : public SbLineProjector
{ public:
inline SbProjector*  py_q_copy() const { return SbLineProjector::copy(); }
inline SbVec3f  py_q_getVector(const SbVec2f&  mousePosition) { return SbLineProjector::getVector(mousePosition); }
inline SbVec3f  py_q_getVector(const SbVec2f&  mousePosition1, const SbVec2f&  mousePosition2) { return SbLineProjector::getVector(mousePosition1, mousePosition2); }
inline SbVec3f  py_q_project(const SbVec2f&  point) { return SbLineProjector::project(point); }
};

class PythonQtWrapper_SbLineProjector : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbLineProjector* new_SbLineProjector();
void delete_SbLineProjector(SbLineProjector* obj) { delete obj; }
   SbProjector*  py_q_copy(SbLineProjector* theWrappedObject) const{  return (((PythonQtPublicPromoter_SbLineProjector*)theWrappedObject)->py_q_copy());}
   const SbLine*  getLine(SbLineProjector* theWrappedObject) const;
   SbVec3f  getVector(SbLineProjector* theWrappedObject, const SbVec2f&  mousePosition);
   SbVec3f  py_q_getVector(SbLineProjector* theWrappedObject, const SbVec2f&  mousePosition){  return (((PythonQtPublicPromoter_SbLineProjector*)theWrappedObject)->py_q_getVector(mousePosition));}
   SbVec3f  getVector(SbLineProjector* theWrappedObject, const SbVec2f&  mousePosition1, const SbVec2f&  mousePosition2);
   SbVec3f  py_q_getVector(SbLineProjector* theWrappedObject, const SbVec2f&  mousePosition1, const SbVec2f&  mousePosition2){  return (((PythonQtPublicPromoter_SbLineProjector*)theWrappedObject)->py_q_getVector(mousePosition1, mousePosition2));}
   SbVec3f  py_q_project(SbLineProjector* theWrappedObject, const SbVec2f&  point){  return (((PythonQtPublicPromoter_SbLineProjector*)theWrappedObject)->py_q_project(point));}
   void setLine(SbLineProjector* theWrappedObject, const SbLine&  line);
   void setStartPosition(SbLineProjector* theWrappedObject, const SbVec2f&  mousePosition);
   void setStartPosition(SbLineProjector* theWrappedObject, const SbVec3f&  point);
};





class PythonQtShell_SbPlaneProjector : public SbPlaneProjector
{
public:
    PythonQtShell_SbPlaneProjector(bool  orient = 0):SbPlaneProjector(orient),_wrapper(nullptr) {};
    PythonQtShell_SbPlaneProjector(const SbPlane&  plane, bool  orient = 0):SbPlaneProjector(plane, orient),_wrapper(nullptr) {};

   ~PythonQtShell_SbPlaneProjector() override;

SbProjector*  copy() const override;
SbVec3f  getVector(const SbVec2f&  mousePosition) override;
SbVec3f  getVector(const SbVec2f&  mousePosition1, const SbVec2f&  mousePosition2) override;
SbVec3f  project(const SbVec2f&  point) override;
void setViewVolume(const SbViewVolume&  vol) override;
void setWorkingSpace(const SbMatrix&  space) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SbPlaneProjector : public SbPlaneProjector
{ public:
inline void promoted_setupPlane() { this->setupPlane(); }
inline SbProjector*  py_q_copy() const { return SbPlaneProjector::copy(); }
inline SbVec3f  py_q_getVector(const SbVec2f&  mousePosition) { return SbPlaneProjector::getVector(mousePosition); }
inline SbVec3f  py_q_getVector(const SbVec2f&  mousePosition1, const SbVec2f&  mousePosition2) { return SbPlaneProjector::getVector(mousePosition1, mousePosition2); }
inline SbVec3f  py_q_project(const SbVec2f&  point) { return SbPlaneProjector::project(point); }
};

class PythonQtWrapper_SbPlaneProjector : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbPlaneProjector* new_SbPlaneProjector(bool  orient = 0);
SbPlaneProjector* new_SbPlaneProjector(const SbPlane&  plane, bool  orient = 0);
void delete_SbPlaneProjector(SbPlaneProjector* obj) { delete obj; }
   SbProjector*  py_q_copy(SbPlaneProjector* theWrappedObject) const{  return (((PythonQtPublicPromoter_SbPlaneProjector*)theWrappedObject)->py_q_copy());}
   const SbPlane*  getPlane(SbPlaneProjector* theWrappedObject) const;
   SbVec3f  getVector(SbPlaneProjector* theWrappedObject, const SbVec2f&  mousePosition);
   SbVec3f  py_q_getVector(SbPlaneProjector* theWrappedObject, const SbVec2f&  mousePosition){  return (((PythonQtPublicPromoter_SbPlaneProjector*)theWrappedObject)->py_q_getVector(mousePosition));}
   SbVec3f  getVector(SbPlaneProjector* theWrappedObject, const SbVec2f&  mousePosition1, const SbVec2f&  mousePosition2);
   SbVec3f  py_q_getVector(SbPlaneProjector* theWrappedObject, const SbVec2f&  mousePosition1, const SbVec2f&  mousePosition2){  return (((PythonQtPublicPromoter_SbPlaneProjector*)theWrappedObject)->py_q_getVector(mousePosition1, mousePosition2));}
   bool  isOrientToEye(SbPlaneProjector* theWrappedObject) const;
   SbVec3f  py_q_project(SbPlaneProjector* theWrappedObject, const SbVec2f&  point){  return (((PythonQtPublicPromoter_SbPlaneProjector*)theWrappedObject)->py_q_project(point));}
   void setOrientToEye(SbPlaneProjector* theWrappedObject, bool  orientToEye);
   void setPlane(SbPlaneProjector* theWrappedObject, const SbPlane&  plane);
   void setStartPosition(SbPlaneProjector* theWrappedObject, const SbVec2f&  mousePosition);
   void setStartPosition(SbPlaneProjector* theWrappedObject, const SbVec3f&  point);
   void setupPlane(SbPlaneProjector* theWrappedObject);
};





class PythonQtShell_SbProjector : public SbProjector
{
public:
    PythonQtShell_SbProjector():SbProjector(),_wrapper(nullptr) {};

   ~PythonQtShell_SbProjector() override;

SbProjector*  copy() const override;
SbVec3f  project(const SbVec2f&  point) override;
void setViewVolume(const SbViewVolume&  vol) override;
void setWorkingSpace(const SbMatrix&  space) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SbProjector : public SbProjector
{ public:
inline SbLine  promoted_getWorkingLine(const SbVec2f&  point) const { return this->getWorkingLine(point); }
inline SbProjector*  py_q_copy() const { return this->copy(); }
inline SbVec3f  py_q_project(const SbVec2f&  point) { return this->project(point); }
inline void py_q_setViewVolume(const SbViewVolume&  vol) { SbProjector::setViewVolume(vol); }
inline void py_q_setWorkingSpace(const SbMatrix&  space) { SbProjector::setWorkingSpace(space); }
};

class PythonQtWrapper_SbProjector : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbProjector* new_SbProjector();
   SbProjector*  copy(SbProjector* theWrappedObject) const;
   SbProjector*  py_q_copy(SbProjector* theWrappedObject) const{  return (((PythonQtPublicPromoter_SbProjector*)theWrappedObject)->py_q_copy());}
   const SbViewVolume*  getViewVolume(SbProjector* theWrappedObject) const;
   SbLine  getWorkingLine(SbProjector* theWrappedObject, const SbVec2f&  point) const;
   const SbMatrix*  getWorkingSpace(SbProjector* theWrappedObject) const;
   SbVec3f  project(SbProjector* theWrappedObject, const SbVec2f&  point);
   SbVec3f  py_q_project(SbProjector* theWrappedObject, const SbVec2f&  point){  return (((PythonQtPublicPromoter_SbProjector*)theWrappedObject)->py_q_project(point));}
   void setViewVolume(SbProjector* theWrappedObject, const SbViewVolume&  vol);
   void py_q_setViewVolume(SbProjector* theWrappedObject, const SbViewVolume&  vol){  (((PythonQtPublicPromoter_SbProjector*)theWrappedObject)->py_q_setViewVolume(vol));}
   void setWorkingSpace(SbProjector* theWrappedObject, const SbMatrix&  space);
   void py_q_setWorkingSpace(SbProjector* theWrappedObject, const SbMatrix&  space){  (((PythonQtPublicPromoter_SbProjector*)theWrappedObject)->py_q_setWorkingSpace(space));}
};





class PythonQtShell_SbSpherePlaneProjector : public SbSpherePlaneProjector
{
public:
    PythonQtShell_SbSpherePlaneProjector(const SbSphere&  sph, float  edgeTol = 0.9, bool  orientToEye = 1):SbSpherePlaneProjector(sph, edgeTol, orientToEye),_wrapper(nullptr) {};
    PythonQtShell_SbSpherePlaneProjector(float  edgeTol = 0.9, bool  orientToEye = 1):SbSpherePlaneProjector(edgeTol, orientToEye),_wrapper(nullptr) {};

   ~PythonQtShell_SbSpherePlaneProjector() override;

SbProjector*  copy() const override;
SbRotation  getRotation(const SbVec3f&  point1, const SbVec3f&  point2) override;
SbVec3f  project(const SbVec2f&  point) override;
void setViewVolume(const SbViewVolume&  vol) override;
void setWorkingSpace(const SbMatrix&  space) override;
void setupTolerance() override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SbSpherePlaneProjector : public SbSpherePlaneProjector
{ public:
inline SbRotation  promoted_getRotation(const SbVec3f&  point1, bool  tol1, const SbVec3f&  point2, bool  tol2) { return this->getRotation(point1, tol1, point2, tol2); }
inline SbProjector*  py_q_copy() const { return SbSpherePlaneProjector::copy(); }
inline SbRotation  py_q_getRotation(const SbVec3f&  point1, const SbVec3f&  point2) { return SbSpherePlaneProjector::getRotation(point1, point2); }
inline SbVec3f  py_q_project(const SbVec2f&  point) { return SbSpherePlaneProjector::project(point); }
};

class PythonQtWrapper_SbSpherePlaneProjector : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbSpherePlaneProjector* new_SbSpherePlaneProjector(const SbSphere&  sph, float  edgeTol = 0.9, bool  orientToEye = 1);
SbSpherePlaneProjector* new_SbSpherePlaneProjector(float  edgeTol = 0.9, bool  orientToEye = 1);
void delete_SbSpherePlaneProjector(SbSpherePlaneProjector* obj) { delete obj; }
   SbProjector*  py_q_copy(SbSpherePlaneProjector* theWrappedObject) const{  return (((PythonQtPublicPromoter_SbSpherePlaneProjector*)theWrappedObject)->py_q_copy());}
   SbRotation  getRotation(SbSpherePlaneProjector* theWrappedObject, const SbVec3f&  point1, bool  tol1, const SbVec3f&  point2, bool  tol2);
   SbRotation  py_q_getRotation(SbSpherePlaneProjector* theWrappedObject, const SbVec3f&  point1, const SbVec3f&  point2){  return (((PythonQtPublicPromoter_SbSpherePlaneProjector*)theWrappedObject)->py_q_getRotation(point1, point2));}
   SbVec3f  py_q_project(SbSpherePlaneProjector* theWrappedObject, const SbVec2f&  point){  return (((PythonQtPublicPromoter_SbSpherePlaneProjector*)theWrappedObject)->py_q_project(point));}
};





class PythonQtShell_SbSphereProjector : public SbSphereProjector
{
public:
    PythonQtShell_SbSphereProjector(bool  orientToEye):SbSphereProjector(orientToEye),_wrapper(nullptr) {};
    PythonQtShell_SbSphereProjector(const SbSphere&  s, bool  orientToEye):SbSphereProjector(s, orientToEye),_wrapper(nullptr) {};

   ~PythonQtShell_SbSphereProjector() override;

SbProjector*  copy() const override;
SbRotation  getRotation(const SbVec3f&  point1, const SbVec3f&  point2) override;
SbVec3f  project(const SbVec2f&  point) override;
void setViewVolume(const SbViewVolume&  vol) override;
void setWorkingSpace(const SbMatrix&  space) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SbSphereProjector : public SbSphereProjector
{ public:
inline SbRotation  py_q_getRotation(const SbVec3f&  point1, const SbVec3f&  point2) { return this->getRotation(point1, point2); }
inline SbVec3f  py_q_project(const SbVec2f&  point) { return this->project(point); }
inline void py_q_setWorkingSpace(const SbMatrix&  space) { SbSphereProjector::setWorkingSpace(space); }
};

class PythonQtWrapper_SbSphereProjector : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbSphereProjector* new_SbSphereProjector(bool  orientToEye);
SbSphereProjector* new_SbSphereProjector(const SbSphere&  s, bool  orientToEye);
void delete_SbSphereProjector(SbSphereProjector* obj) { delete obj; }
   SbRotation  getRotation(SbSphereProjector* theWrappedObject, const SbVec3f&  point1, const SbVec3f&  point2);
   SbRotation  py_q_getRotation(SbSphereProjector* theWrappedObject, const SbVec3f&  point1, const SbVec3f&  point2){  return (((PythonQtPublicPromoter_SbSphereProjector*)theWrappedObject)->py_q_getRotation(point1, point2));}
   const SbSphere*  getSphere(SbSphereProjector* theWrappedObject) const;
   bool  isFront(SbSphereProjector* theWrappedObject) const;
   bool  isOrientToEye(SbSphereProjector* theWrappedObject) const;
   bool  isPointInFront(SbSphereProjector* theWrappedObject, const SbVec3f&  point) const;
   SbVec3f  py_q_project(SbSphereProjector* theWrappedObject, const SbVec2f&  point){  return (((PythonQtPublicPromoter_SbSphereProjector*)theWrappedObject)->py_q_project(point));}
   SbVec3f  projectAndGetRotation(SbSphereProjector* theWrappedObject, const SbVec2f&  point, SbRotation&  rot);
   void setFront(SbSphereProjector* theWrappedObject, bool  inFront);
   void setOrientToEye(SbSphereProjector* theWrappedObject, bool  orientToEye);
   void setSphere(SbSphereProjector* theWrappedObject, const SbSphere&  sph);
   void py_q_setWorkingSpace(SbSphereProjector* theWrappedObject, const SbMatrix&  space){  (((PythonQtPublicPromoter_SbSphereProjector*)theWrappedObject)->py_q_setWorkingSpace(space));}
};





class PythonQtShell_SbSphereSectionProjector : public SbSphereSectionProjector
{
public:
    PythonQtShell_SbSphereSectionProjector(const SbSphere&  sph, float  edgeTol = .9, bool  orientToEye = 1):SbSphereSectionProjector(sph, edgeTol, orientToEye),_wrapper(nullptr) {};
    PythonQtShell_SbSphereSectionProjector(float  edgeTol = .9, bool  orientToEye = 1):SbSphereSectionProjector(edgeTol, orientToEye),_wrapper(nullptr) {};

   ~PythonQtShell_SbSphereSectionProjector() override;

SbProjector*  copy() const override;
SbRotation  getRotation(const SbVec3f&  point1, const SbVec3f&  point2) override;
SbVec3f  project(const SbVec2f&  point) override;
void setViewVolume(const SbViewVolume&  vol) override;
void setWorkingSpace(const SbMatrix&  space) override;
void setupTolerance() override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SbSphereSectionProjector : public SbSphereSectionProjector
{ public:
inline void promoted_setupTolerance() { this->setupTolerance(); }
inline SbProjector*  py_q_copy() const { return SbSphereSectionProjector::copy(); }
inline SbRotation  py_q_getRotation(const SbVec3f&  point1, const SbVec3f&  point2) { return SbSphereSectionProjector::getRotation(point1, point2); }
inline SbVec3f  py_q_project(const SbVec2f&  point) { return SbSphereSectionProjector::project(point); }
inline void py_q_setupTolerance() { SbSphereSectionProjector::setupTolerance(); }
};

class PythonQtWrapper_SbSphereSectionProjector : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbSphereSectionProjector* new_SbSphereSectionProjector(const SbSphere&  sph, float  edgeTol = .9, bool  orientToEye = 1);
SbSphereSectionProjector* new_SbSphereSectionProjector(float  edgeTol = .9, bool  orientToEye = 1);
void delete_SbSphereSectionProjector(SbSphereSectionProjector* obj) { delete obj; }
   SbProjector*  py_q_copy(SbSphereSectionProjector* theWrappedObject) const{  return (((PythonQtPublicPromoter_SbSphereSectionProjector*)theWrappedObject)->py_q_copy());}
   float  getRadialFactor(SbSphereSectionProjector* theWrappedObject) const;
   SbRotation  py_q_getRotation(SbSphereSectionProjector* theWrappedObject, const SbVec3f&  point1, const SbVec3f&  point2){  return (((PythonQtPublicPromoter_SbSphereSectionProjector*)theWrappedObject)->py_q_getRotation(point1, point2));}
   float  getTolerance(SbSphereSectionProjector* theWrappedObject) const;
   bool  isWithinTolerance(SbSphereSectionProjector* theWrappedObject, const SbVec3f&  point);
   SbVec3f  py_q_project(SbSphereSectionProjector* theWrappedObject, const SbVec2f&  point){  return (((PythonQtPublicPromoter_SbSphereSectionProjector*)theWrappedObject)->py_q_project(point));}
   void setRadialFactor(SbSphereSectionProjector* theWrappedObject, float  rad = 0.0);
   void setTolerance(SbSphereSectionProjector* theWrappedObject, float  edgeTol);
   void setupTolerance(SbSphereSectionProjector* theWrappedObject);
   void py_q_setupTolerance(SbSphereSectionProjector* theWrappedObject){  (((PythonQtPublicPromoter_SbSphereSectionProjector*)theWrappedObject)->py_q_setupTolerance());}
};





class PythonQtShell_SbSphereSheetProjector : public SbSphereSheetProjector
{
public:
    PythonQtShell_SbSphereSheetProjector(bool  orientToEye = 1):SbSphereSheetProjector(orientToEye),_wrapper(nullptr) {};
    PythonQtShell_SbSphereSheetProjector(const SbSphere&  sph, bool  orientToEye = 1):SbSphereSheetProjector(sph, orientToEye),_wrapper(nullptr) {};

   ~PythonQtShell_SbSphereSheetProjector() override;

SbProjector*  copy() const override;
SbRotation  getRotation(const SbVec3f&  point1, const SbVec3f&  point2) override;
SbVec3f  project(const SbVec2f&  point) override;
void setViewVolume(const SbViewVolume&  vol) override;
void setWorkingSpace(const SbMatrix&  space) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SbSphereSheetProjector : public SbSphereSheetProjector
{ public:
inline void promoted_setupPlane() { this->setupPlane(); }
inline SbProjector*  py_q_copy() const { return SbSphereSheetProjector::copy(); }
inline SbRotation  py_q_getRotation(const SbVec3f&  point1, const SbVec3f&  point2) { return SbSphereSheetProjector::getRotation(point1, point2); }
inline SbVec3f  py_q_project(const SbVec2f&  point) { return SbSphereSheetProjector::project(point); }
};

class PythonQtWrapper_SbSphereSheetProjector : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SbSphereSheetProjector* new_SbSphereSheetProjector(bool  orientToEye = 1);
SbSphereSheetProjector* new_SbSphereSheetProjector(const SbSphere&  sph, bool  orientToEye = 1);
void delete_SbSphereSheetProjector(SbSphereSheetProjector* obj) { delete obj; }
   SbProjector*  py_q_copy(SbSphereSheetProjector* theWrappedObject) const{  return (((PythonQtPublicPromoter_SbSphereSheetProjector*)theWrappedObject)->py_q_copy());}
   SbRotation  py_q_getRotation(SbSphereSheetProjector* theWrappedObject, const SbVec3f&  point1, const SbVec3f&  point2){  return (((PythonQtPublicPromoter_SbSphereSheetProjector*)theWrappedObject)->py_q_getRotation(point1, point2));}
   SbVec3f  py_q_project(SbSphereSheetProjector* theWrappedObject, const SbVec2f&  point){  return (((PythonQtPublicPromoter_SbSphereSheetProjector*)theWrappedObject)->py_q_project(point));}
   void setupPlane(SbSphereSheetProjector* theWrappedObject);
};


