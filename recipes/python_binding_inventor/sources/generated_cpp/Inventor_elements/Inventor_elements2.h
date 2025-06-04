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
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SoType.h>
#include <Inventor/elements/SoElement.h>
#include <Inventor/elements/SoTextureQualityElement.h>
#include <Inventor/elements/SoUnitsElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoViewingMatrixElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/nodes/SoNode.h>



class PythonQtShell_SoTextureQualityElement : public SoTextureQualityElement
{
public:
    PythonQtShell_SoTextureQualityElement():SoTextureQualityElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoTextureQualityElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(float  value) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoTextureQualityElement : public SoTextureQualityElement
{ public:
inline void py_q_init(SoState*  state) { SoTextureQualityElement::init(state); }
};

class PythonQtWrapper_SoTextureQualityElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoTextureQualityElement* new_SoTextureQualityElement();
   float  static_SoTextureQualityElement_get(SoState*  state);
   int  static_SoTextureQualityElement_getClassStackIndex();
   SoType  static_SoTextureQualityElement_getClassTypeId();
   float  static_SoTextureQualityElement_getDefault();
   void py_q_init(SoTextureQualityElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoTextureQualityElement*)theWrappedObject)->py_q_init(state));}
   void static_SoTextureQualityElement_set(SoState*  state, float  qual);
};





class PythonQtShell_SoUnitsElement : public SoUnitsElement
{
public:
    PythonQtShell_SoUnitsElement():SoUnitsElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoUnitsElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(int  value) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoUnitsElement : public SoUnitsElement
{ public:
inline void py_q_init(SoState*  state) { SoUnitsElement::init(state); }
};

class PythonQtWrapper_SoUnitsElement : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Units )
enum Units{
  METERS = SoUnitsElement::METERS,   CENTIMETERS = SoUnitsElement::CENTIMETERS,   MILLIMETERS = SoUnitsElement::MILLIMETERS,   MICROMETERS = SoUnitsElement::MICROMETERS,   MICRONS = SoUnitsElement::MICRONS,   NANOMETERS = SoUnitsElement::NANOMETERS,   ANGSTROMS = SoUnitsElement::ANGSTROMS,   KILOMETERS = SoUnitsElement::KILOMETERS,   FEET = SoUnitsElement::FEET,   INCHES = SoUnitsElement::INCHES,   POINTS = SoUnitsElement::POINTS,   YARDS = SoUnitsElement::YARDS,   MILES = SoUnitsElement::MILES,   NAUTICAL_MILES = SoUnitsElement::NAUTICAL_MILES};
public Q_SLOTS:
SoUnitsElement* new_SoUnitsElement();
   SoUnitsElement::Units  static_SoUnitsElement_get(SoState*  state);
   int  static_SoUnitsElement_getClassStackIndex();
   SoType  static_SoUnitsElement_getClassTypeId();
   SoUnitsElement::Units  static_SoUnitsElement_getDefault();
   void py_q_init(SoUnitsElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoUnitsElement*)theWrappedObject)->py_q_init(state));}
   void static_SoUnitsElement_set(SoState*  state, SoUnitsElement::Units  units);
};





class PythonQtShell_SoViewVolumeElement : public SoViewVolumeElement
{
public:
    PythonQtShell_SoViewVolumeElement():SoViewVolumeElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoViewVolumeElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoViewVolumeElement : public SoViewVolumeElement
{ public:
inline void py_q_init(SoState*  state) { SoViewVolumeElement::init(state); }
};

class PythonQtWrapper_SoViewVolumeElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoViewVolumeElement* new_SoViewVolumeElement();
   const SbViewVolume*  static_SoViewVolumeElement_get(SoState*  state);
   int  static_SoViewVolumeElement_getClassStackIndex();
   SoType  static_SoViewVolumeElement_getClassTypeId();
   void py_q_init(SoViewVolumeElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoViewVolumeElement*)theWrappedObject)->py_q_init(state));}
   void static_SoViewVolumeElement_set(SoState*  state, SoNode*  node, const SbViewVolume&  viewVolume);
};





class PythonQtShell_SoViewingMatrixElement : public SoViewingMatrixElement
{
public:
    PythonQtShell_SoViewingMatrixElement():SoViewingMatrixElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoViewingMatrixElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(const SbMatrix&  matrix) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoViewingMatrixElement : public SoViewingMatrixElement
{ public:
inline void promoted_setElt(const SbMatrix&  matrix) { this->setElt(matrix); }
inline void py_q_init(SoState*  state) { SoViewingMatrixElement::init(state); }
inline void py_q_setElt(const SbMatrix&  matrix) { SoViewingMatrixElement::setElt(matrix); }
};

class PythonQtWrapper_SoViewingMatrixElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoViewingMatrixElement* new_SoViewingMatrixElement();
   const SbMatrix*  static_SoViewingMatrixElement_get(SoState*  state);
   int  static_SoViewingMatrixElement_getClassStackIndex();
   SoType  static_SoViewingMatrixElement_getClassTypeId();
   void py_q_init(SoViewingMatrixElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoViewingMatrixElement*)theWrappedObject)->py_q_init(state));}
   void static_SoViewingMatrixElement_set(SoState*  state, SoNode*  node, const SbMatrix&  matrix);
   void setElt(SoViewingMatrixElement* theWrappedObject, const SbMatrix&  matrix);
   void py_q_setElt(SoViewingMatrixElement* theWrappedObject, const SbMatrix&  matrix){  (((PythonQtPublicPromoter_SoViewingMatrixElement*)theWrappedObject)->py_q_setElt(matrix));}
};





class PythonQtShell_SoViewportRegionElement : public SoViewportRegionElement
{
public:
    PythonQtShell_SoViewportRegionElement():SoViewportRegionElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoViewportRegionElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(const SbViewportRegion&  vpReg) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoViewportRegionElement : public SoViewportRegionElement
{ public:
inline void promoted_setElt(const SbViewportRegion&  vpReg) { this->setElt(vpReg); }
inline SoElement*  py_q_copyMatchInfo() const { return SoViewportRegionElement::copyMatchInfo(); }
inline void py_q_init(SoState*  state) { SoViewportRegionElement::init(state); }
inline bool  py_q_matches(const SoElement*  elt) const { return SoViewportRegionElement::matches(elt); }
inline void py_q_setElt(const SbViewportRegion&  vpReg) { SoViewportRegionElement::setElt(vpReg); }
};

class PythonQtWrapper_SoViewportRegionElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoViewportRegionElement* new_SoViewportRegionElement();
   SoElement*  py_q_copyMatchInfo(SoViewportRegionElement* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoViewportRegionElement*)theWrappedObject)->py_q_copyMatchInfo());}
   const SbViewportRegion*  static_SoViewportRegionElement_get(SoState*  state);
   int  static_SoViewportRegionElement_getClassStackIndex();
   SoType  static_SoViewportRegionElement_getClassTypeId();
   void py_q_init(SoViewportRegionElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoViewportRegionElement*)theWrappedObject)->py_q_init(state));}
   bool  py_q_matches(SoViewportRegionElement* theWrappedObject, const SoElement*  elt) const{  return (((PythonQtPublicPromoter_SoViewportRegionElement*)theWrappedObject)->py_q_matches(elt));}
   void static_SoViewportRegionElement_set(SoState*  state, const SbViewportRegion&  vpReg);
   void setElt(SoViewportRegionElement* theWrappedObject, const SbViewportRegion&  vpReg);
   void py_q_setElt(SoViewportRegionElement* theWrappedObject, const SbViewportRegion&  vpReg){  (((PythonQtPublicPromoter_SoViewportRegionElement*)theWrappedObject)->py_q_setElt(vpReg));}
};


