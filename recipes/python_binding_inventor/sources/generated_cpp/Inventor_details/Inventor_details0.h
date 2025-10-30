#include <Inventor/SoType.h>
#include <Inventor/details/SoConeDetail.h>
#include <Inventor/details/SoCubeDetail.h>
#include <Inventor/details/SoCylinderDetail.h>
#include <Inventor/details/SoDetail.h>
#include <Inventor/details/SoFaceDetail.h>
#include <Inventor/details/SoLineDetail.h>
#include <Inventor/details/SoPointDetail.h>
#include <Inventor/details/SoTextDetail.h>
#include <PythonQt.h>
#include <QObject>
#include <QVariant>



class PythonQtShell_SoConeDetail : public SoConeDetail
{
public:
    PythonQtShell_SoConeDetail():SoConeDetail(),_wrapper(nullptr) {};

   ~PythonQtShell_SoConeDetail() override;

SoDetail*  copy() const override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoConeDetail : public SoConeDetail
{ public:
inline SoDetail*  py_q_copy() const { return SoConeDetail::copy(); }
};

class PythonQtWrapper_SoConeDetail : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoConeDetail* new_SoConeDetail();
void delete_SoConeDetail(SoConeDetail* obj) { delete obj; }
   SoDetail*  py_q_copy(SoConeDetail* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoConeDetail*)theWrappedObject)->py_q_copy());}
   SoType  static_SoConeDetail_getClassTypeId();
   int  getPart(SoConeDetail* theWrappedObject) const;
   void setPart(SoConeDetail* theWrappedObject, int  _part);
};





class PythonQtShell_SoCubeDetail : public SoCubeDetail
{
public:
    PythonQtShell_SoCubeDetail():SoCubeDetail(),_wrapper(nullptr) {};

   ~PythonQtShell_SoCubeDetail() override;

SoDetail*  copy() const override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoCubeDetail : public SoCubeDetail
{ public:
inline SoDetail*  py_q_copy() const { return SoCubeDetail::copy(); }
};

class PythonQtWrapper_SoCubeDetail : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoCubeDetail* new_SoCubeDetail();
void delete_SoCubeDetail(SoCubeDetail* obj) { delete obj; }
   SoDetail*  py_q_copy(SoCubeDetail* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoCubeDetail*)theWrappedObject)->py_q_copy());}
   SoType  static_SoCubeDetail_getClassTypeId();
   int  getPart(SoCubeDetail* theWrappedObject) const;
   void setPart(SoCubeDetail* theWrappedObject, int  _part);
};





class PythonQtShell_SoCylinderDetail : public SoCylinderDetail
{
public:
    PythonQtShell_SoCylinderDetail():SoCylinderDetail(),_wrapper(nullptr) {};

   ~PythonQtShell_SoCylinderDetail() override;

SoDetail*  copy() const override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoCylinderDetail : public SoCylinderDetail
{ public:
inline SoDetail*  py_q_copy() const { return SoCylinderDetail::copy(); }
};

class PythonQtWrapper_SoCylinderDetail : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoCylinderDetail* new_SoCylinderDetail();
void delete_SoCylinderDetail(SoCylinderDetail* obj) { delete obj; }
   SoDetail*  py_q_copy(SoCylinderDetail* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoCylinderDetail*)theWrappedObject)->py_q_copy());}
   SoType  static_SoCylinderDetail_getClassTypeId();
   int  getPart(SoCylinderDetail* theWrappedObject) const;
   void setPart(SoCylinderDetail* theWrappedObject, int  _part);
};





class PythonQtPublicPromoter_SoDetail : public SoDetail
{ public:
inline SoDetail*  py_q_copy() const { return this->copy(); }
};

class PythonQtWrapper_SoDetail : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
void delete_SoDetail(SoDetail* obj) { delete obj; }
   SoDetail*  copy(SoDetail* theWrappedObject) const;
   SoDetail*  py_q_copy(SoDetail* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoDetail*)theWrappedObject)->py_q_copy());}
   SoType  static_SoDetail_getClassTypeId();
   bool  isOfType(SoDetail* theWrappedObject, SoType  type) const;
};





class PythonQtShell_SoFaceDetail : public SoFaceDetail
{
public:
    PythonQtShell_SoFaceDetail():SoFaceDetail(),_wrapper(nullptr) {};

   ~PythonQtShell_SoFaceDetail() override;

SoDetail*  copy() const override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoFaceDetail : public SoFaceDetail
{ public:
inline SoDetail*  py_q_copy() const { return SoFaceDetail::copy(); }
};

class PythonQtWrapper_SoFaceDetail : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoFaceDetail* new_SoFaceDetail();
void delete_SoFaceDetail(SoFaceDetail* obj) { delete obj; }
   SoDetail*  py_q_copy(SoFaceDetail* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoFaceDetail*)theWrappedObject)->py_q_copy());}
   SoType  static_SoFaceDetail_getClassTypeId();
   int  getFaceIndex(SoFaceDetail* theWrappedObject) const;
   int  getNumPoints(SoFaceDetail* theWrappedObject) const;
   int  getPartIndex(SoFaceDetail* theWrappedObject) const;
   const SoPointDetail*  getPoint(SoFaceDetail* theWrappedObject, int  i) const;
   SoPointDetail*  getPoints(SoFaceDetail* theWrappedObject);
   void setFaceIndex(SoFaceDetail* theWrappedObject, int  i);
   void setNumPoints(SoFaceDetail* theWrappedObject, int  num);
   void setPartIndex(SoFaceDetail* theWrappedObject, int  i);
   void setPoint(SoFaceDetail* theWrappedObject, int  index, const SoPointDetail*  pd);
};





class PythonQtShell_SoLineDetail : public SoLineDetail
{
public:
    PythonQtShell_SoLineDetail():SoLineDetail(),_wrapper(nullptr) {};

   ~PythonQtShell_SoLineDetail() override;

SoDetail*  copy() const override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoLineDetail : public SoLineDetail
{ public:
inline SoDetail*  py_q_copy() const { return SoLineDetail::copy(); }
};

class PythonQtWrapper_SoLineDetail : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoLineDetail* new_SoLineDetail();
void delete_SoLineDetail(SoLineDetail* obj) { delete obj; }
   SoDetail*  py_q_copy(SoLineDetail* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoLineDetail*)theWrappedObject)->py_q_copy());}
   SoType  static_SoLineDetail_getClassTypeId();
   int  getLineIndex(SoLineDetail* theWrappedObject) const;
   int  getPartIndex(SoLineDetail* theWrappedObject) const;
   const SoPointDetail*  getPoint0(SoLineDetail* theWrappedObject) const;
   const SoPointDetail*  getPoint1(SoLineDetail* theWrappedObject) const;
   void setLineIndex(SoLineDetail* theWrappedObject, int  i);
   void setPartIndex(SoLineDetail* theWrappedObject, int  i);
   void setPoint0(SoLineDetail* theWrappedObject, const SoPointDetail*  pd);
   void setPoint1(SoLineDetail* theWrappedObject, const SoPointDetail*  pd);
};





class PythonQtShell_SoPointDetail : public SoPointDetail
{
public:
    PythonQtShell_SoPointDetail():SoPointDetail(),_wrapper(nullptr) {};

   ~PythonQtShell_SoPointDetail() override;

SoDetail*  copy() const override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoPointDetail : public SoPointDetail
{ public:
inline SoDetail*  py_q_copy() const { return SoPointDetail::copy(); }
};

class PythonQtWrapper_SoPointDetail : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoPointDetail* new_SoPointDetail();
void delete_SoPointDetail(SoPointDetail* obj) { delete obj; }
   SoDetail*  py_q_copy(SoPointDetail* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoPointDetail*)theWrappedObject)->py_q_copy());}
   SoType  static_SoPointDetail_getClassTypeId();
   int  getCoordinateIndex(SoPointDetail* theWrappedObject) const;
   int  getMaterialIndex(SoPointDetail* theWrappedObject) const;
   int  getNormalIndex(SoPointDetail* theWrappedObject) const;
   int  getTextureCoordIndex(SoPointDetail* theWrappedObject) const;
   void setCoordinateIndex(SoPointDetail* theWrappedObject, int  i);
   void setMaterialIndex(SoPointDetail* theWrappedObject, int  i);
   void setNormalIndex(SoPointDetail* theWrappedObject, int  i);
   void setTextureCoordIndex(SoPointDetail* theWrappedObject, int  i);
};





class PythonQtShell_SoTextDetail : public SoTextDetail
{
public:
    PythonQtShell_SoTextDetail():SoTextDetail(),_wrapper(nullptr) {};

   ~PythonQtShell_SoTextDetail() override;

SoDetail*  copy() const override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoTextDetail : public SoTextDetail
{ public:
inline SoDetail*  py_q_copy() const { return SoTextDetail::copy(); }
};

class PythonQtWrapper_SoTextDetail : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoTextDetail* new_SoTextDetail();
void delete_SoTextDetail(SoTextDetail* obj) { delete obj; }
   SoDetail*  py_q_copy(SoTextDetail* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoTextDetail*)theWrappedObject)->py_q_copy());}
   int  getCharacterIndex(SoTextDetail* theWrappedObject) const;
   SoType  static_SoTextDetail_getClassTypeId();
   SoText3::Part  getPart(SoTextDetail* theWrappedObject) const;
   int  getStringIndex(SoTextDetail* theWrappedObject) const;
   void setCharacterIndex(SoTextDetail* theWrappedObject, int  i);
   void setPart(SoTextDetail* theWrappedObject, SoText3::Part  p);
   void setStringIndex(SoTextDetail* theWrappedObject, int  i);
};


