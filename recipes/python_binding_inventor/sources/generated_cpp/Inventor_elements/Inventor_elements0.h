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
#include <Inventor/SbString.h>
#include <Inventor/SoType.h>
#include <Inventor/elements/SoAccumulatedElement.h>
#include <Inventor/elements/SoBBoxModelMatrixElement.h>
#include <Inventor/elements/SoCacheElement.h>
#include <Inventor/elements/SoClipPlaneElement.h>
#include <Inventor/elements/SoComplexityElement.h>
#include <Inventor/elements/SoComplexityTypeElement.h>
#include <Inventor/elements/SoCoordinateElement.h>
#include <Inventor/elements/SoCreaseAngleElement.h>
#include <Inventor/elements/SoDrawStyleElement.h>
#include <Inventor/elements/SoElement.h>
#include <Inventor/elements/SoFloatElement.h>
#include <Inventor/elements/SoFocalDistanceElement.h>
#include <Inventor/elements/SoFontNameElement.h>
#include <Inventor/elements/SoFontSizeElement.h>
#include <Inventor/elements/SoGLCacheContextElement.h>
#include <Inventor/elements/SoGLClipPlaneElement.h>
#include <Inventor/elements/SoGLCoordinateElement.h>
#include <Inventor/elements/SoGLDrawStyleElement.h>
#include <Inventor/elements/SoGLLazyElement.h>
#include <Inventor/elements/SoGLLightIdElement.h>
#include <Inventor/elements/SoGLLinePatternElement.h>
#include <Inventor/elements/SoGLLineWidthElement.h>
#include <Inventor/elements/SoGLModelMatrixElement.h>
#include <Inventor/elements/SoGLNormalElement.h>
#include <Inventor/elements/SoGLPointSizeElement.h>
#include <Inventor/elements/SoGLProjectionMatrixElement.h>
#include <Inventor/elements/SoGLRenderPassElement.h>
#include <Inventor/elements/SoGLShapeHintsElement.h>
#include <Inventor/elements/SoGLTextureCoordinateElement.h>
#include <Inventor/elements/SoGLTextureEnabledElement.h>
#include <Inventor/elements/SoLazyElement.h>
#include <Inventor/elements/SoNormalElement.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/nodes/SoNode.h>
#include <stdexcept>



class PythonQtShell_SoAccumulatedElement : public SoAccumulatedElement
{
public:
    PythonQtShell_SoAccumulatedElement():SoAccumulatedElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoAccumulatedElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoAccumulatedElement : public SoAccumulatedElement
{ public:
inline void promoted_addNodeId(const SoNode*  node) { this->addNodeId(node); }
inline void promoted_captureThis(SoState*  state) const { this->captureThis(state); }
inline void promoted_clearNodeIds() { this->clearNodeIds(); }
inline SoElement*  promoted_copyMatchInfo() const { return this->copyMatchInfo(); }
inline void promoted_setNodeId(const SoNode*  node) { this->setNodeId(node); }
inline void py_q_captureThis(SoState*  state) const { SoAccumulatedElement::captureThis(state); }
inline SoElement*  py_q_copyMatchInfo() const { return SoAccumulatedElement::copyMatchInfo(); }
inline bool  py_q_matches(const SoElement*  elt) const { return SoAccumulatedElement::matches(elt); }
};

class PythonQtWrapper_SoAccumulatedElement : public QObject
{ Q_OBJECT
public:
public slots:
SoAccumulatedElement* new_SoAccumulatedElement();
   void addNodeId(SoAccumulatedElement* theWrappedObject, const SoNode*  node);
   void py_q_captureThis(SoAccumulatedElement* theWrappedObject, SoState*  state) const{  (((PythonQtPublicPromoter_SoAccumulatedElement*)theWrappedObject)->py_q_captureThis(state));}
   void clearNodeIds(SoAccumulatedElement* theWrappedObject);
   SoElement*  py_q_copyMatchInfo(SoAccumulatedElement* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoAccumulatedElement*)theWrappedObject)->py_q_copyMatchInfo());}
   int  static_SoAccumulatedElement_getClassStackIndex();
   SoType  static_SoAccumulatedElement_getClassTypeId();
   bool  py_q_matches(SoAccumulatedElement* theWrappedObject, const SoElement*  elt) const{  return (((PythonQtPublicPromoter_SoAccumulatedElement*)theWrappedObject)->py_q_matches(elt));}
   void setNodeId(SoAccumulatedElement* theWrappedObject, const SoNode*  node);
};





class PythonQtShell_SoBBoxModelMatrixElement : public SoBBoxModelMatrixElement
{
public:
    PythonQtShell_SoBBoxModelMatrixElement():SoBBoxModelMatrixElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoBBoxModelMatrixElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
void makeEltIdentity() override;
bool  matches(const SoElement*  elt) const override;
void multElt(const SbMatrix&  matrix) override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void popMatrixElt(const SbMatrix&  m) override;
void push(SoState*  state) override;
SbMatrix  pushMatrixElt() override;
void rotateEltBy(const SbRotation&  translation) override;
void scaleEltBy(const SbVec3f&  scaleFactor) override;
void setElt(const SbMatrix&  matrix) override;
void translateEltBy(const SbVec3f&  translation) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoBBoxModelMatrixElement : public SoBBoxModelMatrixElement
{ public:
inline void promoted_makeEltIdentity() { this->makeEltIdentity(); }
inline void promoted_multElt(const SbMatrix&  matrix) { this->multElt(matrix); }
inline void promoted_popMatrixElt(const SbMatrix&  m) { this->popMatrixElt(m); }
inline SbMatrix  promoted_pushMatrixElt() { return this->pushMatrixElt(); }
inline void promoted_rotateEltBy(const SbRotation&  translation) { this->rotateEltBy(translation); }
inline void promoted_scaleEltBy(const SbVec3f&  scaleFactor) { this->scaleEltBy(scaleFactor); }
inline void promoted_setElt(const SbMatrix&  matrix) { this->setElt(matrix); }
inline void promoted_translateEltBy(const SbVec3f&  translation) { this->translateEltBy(translation); }
inline void py_q_init(SoState*  state) { SoBBoxModelMatrixElement::init(state); }
inline void py_q_makeEltIdentity() { SoBBoxModelMatrixElement::makeEltIdentity(); }
inline void py_q_multElt(const SbMatrix&  matrix) { SoBBoxModelMatrixElement::multElt(matrix); }
inline void py_q_popMatrixElt(const SbMatrix&  m) { SoBBoxModelMatrixElement::popMatrixElt(m); }
inline void py_q_push(SoState*  state) { SoBBoxModelMatrixElement::push(state); }
inline SbMatrix  py_q_pushMatrixElt() { return SoBBoxModelMatrixElement::pushMatrixElt(); }
inline void py_q_rotateEltBy(const SbRotation&  translation) { SoBBoxModelMatrixElement::rotateEltBy(translation); }
inline void py_q_scaleEltBy(const SbVec3f&  scaleFactor) { SoBBoxModelMatrixElement::scaleEltBy(scaleFactor); }
inline void py_q_setElt(const SbMatrix&  matrix) { SoBBoxModelMatrixElement::setElt(matrix); }
inline void py_q_translateEltBy(const SbVec3f&  translation) { SoBBoxModelMatrixElement::translateEltBy(translation); }
};

class PythonQtWrapper_SoBBoxModelMatrixElement : public QObject
{ Q_OBJECT
public:
public slots:
SoBBoxModelMatrixElement* new_SoBBoxModelMatrixElement();
   int  static_SoBBoxModelMatrixElement_getClassStackIndex();
   SoType  static_SoBBoxModelMatrixElement_getClassTypeId();
   void py_q_init(SoBBoxModelMatrixElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoBBoxModelMatrixElement*)theWrappedObject)->py_q_init(state));}
   void py_q_makeEltIdentity(SoBBoxModelMatrixElement* theWrappedObject){  (((PythonQtPublicPromoter_SoBBoxModelMatrixElement*)theWrappedObject)->py_q_makeEltIdentity());}
   void py_q_multElt(SoBBoxModelMatrixElement* theWrappedObject, const SbMatrix&  matrix){  (((PythonQtPublicPromoter_SoBBoxModelMatrixElement*)theWrappedObject)->py_q_multElt(matrix));}
   void static_SoBBoxModelMatrixElement_popMatrix(SoState*  state, const SbMatrix&  matrix, const SbMatrix&  localmatrix);
   void py_q_popMatrixElt(SoBBoxModelMatrixElement* theWrappedObject, const SbMatrix&  m){  (((PythonQtPublicPromoter_SoBBoxModelMatrixElement*)theWrappedObject)->py_q_popMatrixElt(m));}
   void py_q_push(SoBBoxModelMatrixElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoBBoxModelMatrixElement*)theWrappedObject)->py_q_push(state));}
   void static_SoBBoxModelMatrixElement_pushMatrix(SoState*  state, SbMatrix&  matrix, SbMatrix&  localmatrix);
   SbMatrix  py_q_pushMatrixElt(SoBBoxModelMatrixElement* theWrappedObject){  return (((PythonQtPublicPromoter_SoBBoxModelMatrixElement*)theWrappedObject)->py_q_pushMatrixElt());}
   void static_SoBBoxModelMatrixElement_reset(SoState*  state, SoNode*  node);
   void py_q_rotateEltBy(SoBBoxModelMatrixElement* theWrappedObject, const SbRotation&  translation){  (((PythonQtPublicPromoter_SoBBoxModelMatrixElement*)theWrappedObject)->py_q_rotateEltBy(translation));}
   void py_q_scaleEltBy(SoBBoxModelMatrixElement* theWrappedObject, const SbVec3f&  scaleFactor){  (((PythonQtPublicPromoter_SoBBoxModelMatrixElement*)theWrappedObject)->py_q_scaleEltBy(scaleFactor));}
   void py_q_setElt(SoBBoxModelMatrixElement* theWrappedObject, const SbMatrix&  matrix){  (((PythonQtPublicPromoter_SoBBoxModelMatrixElement*)theWrappedObject)->py_q_setElt(matrix));}
   void py_q_translateEltBy(SoBBoxModelMatrixElement* theWrappedObject, const SbVec3f&  translation){  (((PythonQtPublicPromoter_SoBBoxModelMatrixElement*)theWrappedObject)->py_q_translateEltBy(translation));}
};





class PythonQtShell_SoCacheElement : public SoCacheElement
{
public:
    PythonQtShell_SoCacheElement():SoCacheElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoCacheElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoCacheElement : public SoCacheElement
{ public:
inline SoElement*  py_q_copyMatchInfo() const { return SoCacheElement::copyMatchInfo(); }
inline void py_q_init(SoState*  state) { SoCacheElement::init(state); }
inline bool  py_q_matches(const SoElement*  elt) const { return SoCacheElement::matches(elt); }
inline void py_q_pop(SoState*  state, const SoElement*  prevTopElement) { SoCacheElement::pop(state, prevTopElement); }
};

class PythonQtWrapper_SoCacheElement : public QObject
{ Q_OBJECT
public:
public slots:
SoCacheElement* new_SoCacheElement();
void delete_SoCacheElement(SoCacheElement* obj) { delete obj; }
   void static_SoCacheElement_addElement(SoState*  state, const SoElement*  elt);
   bool  static_SoCacheElement_anyOpen(SoState*  state);
   SoElement*  py_q_copyMatchInfo(SoCacheElement* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoCacheElement*)theWrappedObject)->py_q_copyMatchInfo());}
   int  static_SoCacheElement_getClassStackIndex();
   SoType  static_SoCacheElement_getClassTypeId();
   SoCacheElement*  getNextCacheElement(SoCacheElement* theWrappedObject) const;
   void py_q_init(SoCacheElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoCacheElement*)theWrappedObject)->py_q_init(state));}
   void static_SoCacheElement_invalidate(SoState*  state);
   bool  py_q_matches(SoCacheElement* theWrappedObject, const SoElement*  elt) const{  return (((PythonQtPublicPromoter_SoCacheElement*)theWrappedObject)->py_q_matches(elt));}
   void py_q_pop(SoCacheElement* theWrappedObject, SoState*  state, const SoElement*  prevTopElement){  (((PythonQtPublicPromoter_SoCacheElement*)theWrappedObject)->py_q_pop(state, prevTopElement));}
   bool  static_SoCacheElement_setInvalid(bool  newValue);
};





class PythonQtShell_SoClipPlaneElement : public SoClipPlaneElement
{
public:
    PythonQtShell_SoClipPlaneElement():SoClipPlaneElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoClipPlaneElement() override;

void addToElt(const SbPlane&  plane, const SbMatrix&  modelMatrix) override;
void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoClipPlaneElement : public SoClipPlaneElement
{ public:
inline void promoted_addToElt(const SbPlane&  plane, const SbMatrix&  modelMatrix) { this->addToElt(plane, modelMatrix); }
inline void py_q_addToElt(const SbPlane&  plane, const SbMatrix&  modelMatrix) { SoClipPlaneElement::addToElt(plane, modelMatrix); }
inline void py_q_init(SoState*  state) { SoClipPlaneElement::init(state); }
inline void py_q_pop(SoState*  state, const SoElement*  prevTopElement) { SoClipPlaneElement::pop(state, prevTopElement); }
inline void py_q_push(SoState*  state) { SoClipPlaneElement::push(state); }
};

class PythonQtWrapper_SoClipPlaneElement : public QObject
{ Q_OBJECT
public:
public slots:
SoClipPlaneElement* new_SoClipPlaneElement();
   void static_SoClipPlaneElement_add(SoState*  state, SoNode*  node, const SbPlane&  plane);
   void addToElt(SoClipPlaneElement* theWrappedObject, const SbPlane&  plane, const SbMatrix&  modelMatrix);
   void py_q_addToElt(SoClipPlaneElement* theWrappedObject, const SbPlane&  plane, const SbMatrix&  modelMatrix){  (((PythonQtPublicPromoter_SoClipPlaneElement*)theWrappedObject)->py_q_addToElt(plane, modelMatrix));}
   const SbPlane*  get(SoClipPlaneElement* theWrappedObject, int  index, bool  inWorldSpace = 1) const;
   int  static_SoClipPlaneElement_getClassStackIndex();
   SoType  static_SoClipPlaneElement_getClassTypeId();
   const SoClipPlaneElement*  static_SoClipPlaneElement_getInstance(SoState*  state);
   int  getNum(SoClipPlaneElement* theWrappedObject) const;
   void py_q_init(SoClipPlaneElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoClipPlaneElement*)theWrappedObject)->py_q_init(state));}
   void py_q_pop(SoClipPlaneElement* theWrappedObject, SoState*  state, const SoElement*  prevTopElement){  (((PythonQtPublicPromoter_SoClipPlaneElement*)theWrappedObject)->py_q_pop(state, prevTopElement));}
   void py_q_push(SoClipPlaneElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoClipPlaneElement*)theWrappedObject)->py_q_push(state));}
};





class PythonQtShell_SoComplexityElement : public SoComplexityElement
{
public:
    PythonQtShell_SoComplexityElement():SoComplexityElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoComplexityElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(float  value) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoComplexityElement : public SoComplexityElement
{ public:
inline void py_q_init(SoState*  state) { SoComplexityElement::init(state); }
};

class PythonQtWrapper_SoComplexityElement : public QObject
{ Q_OBJECT
public:
public slots:
SoComplexityElement* new_SoComplexityElement();
   float  static_SoComplexityElement_get(SoState*  state);
   int  static_SoComplexityElement_getClassStackIndex();
   SoType  static_SoComplexityElement_getClassTypeId();
   float  static_SoComplexityElement_getDefault();
   void py_q_init(SoComplexityElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoComplexityElement*)theWrappedObject)->py_q_init(state));}
   void static_SoComplexityElement_set(SoState*  state, float  comp);
};





class PythonQtShell_SoComplexityTypeElement : public SoComplexityTypeElement
{
public:
    PythonQtShell_SoComplexityTypeElement():SoComplexityTypeElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoComplexityTypeElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(int  value) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoComplexityTypeElement : public SoComplexityTypeElement
{ public:
inline void py_q_init(SoState*  state) { SoComplexityTypeElement::init(state); }
};

class PythonQtWrapper_SoComplexityTypeElement : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Type )
enum Type{
  OBJECT_SPACE = SoComplexityTypeElement::OBJECT_SPACE,   SCREEN_SPACE = SoComplexityTypeElement::SCREEN_SPACE,   BOUNDING_BOX = SoComplexityTypeElement::BOUNDING_BOX};
public slots:
SoComplexityTypeElement* new_SoComplexityTypeElement();
   SoComplexityTypeElement::Type  static_SoComplexityTypeElement_get(SoState*  state);
   int  static_SoComplexityTypeElement_getClassStackIndex();
   SoType  static_SoComplexityTypeElement_getClassTypeId();
   SoComplexityTypeElement::Type  static_SoComplexityTypeElement_getDefault();
   void py_q_init(SoComplexityTypeElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoComplexityTypeElement*)theWrappedObject)->py_q_init(state));}
   void static_SoComplexityTypeElement_set(SoState*  state, SoComplexityTypeElement::Type  type);
};





class PythonQtShell_SoCoordinateElement : public SoCoordinateElement
{
public:
    PythonQtShell_SoCoordinateElement():SoCoordinateElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoCoordinateElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoCoordinateElement : public SoCoordinateElement
{ public:
inline void py_q_init(SoState*  state) { SoCoordinateElement::init(state); }
};

class PythonQtWrapper_SoCoordinateElement : public QObject
{ Q_OBJECT
public:
public slots:
SoCoordinateElement* new_SoCoordinateElement();
   const SbVec3f*  get3(SoCoordinateElement* theWrappedObject, int  index) const;
   const SbVec4f*  get4(SoCoordinateElement* theWrappedObject, int  index) const;
   int  static_SoCoordinateElement_getClassStackIndex();
   SoType  static_SoCoordinateElement_getClassTypeId();
   SbVec3f  static_SoCoordinateElement_getDefault3();
   SbVec4f  static_SoCoordinateElement_getDefault4();
   const SoCoordinateElement*  static_SoCoordinateElement_getInstance(SoState*  state);
   int  getNum(SoCoordinateElement* theWrappedObject) const;
   void py_q_init(SoCoordinateElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoCoordinateElement*)theWrappedObject)->py_q_init(state));}
   bool  is3D(SoCoordinateElement* theWrappedObject) const;
   void static_SoCoordinateElement_set3(SoState*  state, SoNode*  node, int  numCoords, const SbVec3f*  coords);
   void static_SoCoordinateElement_set4(SoState*  state, SoNode*  node, int  numCoords, const SbVec4f*  coords);
};





class PythonQtShell_SoCreaseAngleElement : public SoCreaseAngleElement
{
public:
    PythonQtShell_SoCreaseAngleElement():SoCreaseAngleElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoCreaseAngleElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(float  value) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoCreaseAngleElement : public SoCreaseAngleElement
{ public:
inline void py_q_init(SoState*  state) { SoCreaseAngleElement::init(state); }
};

class PythonQtWrapper_SoCreaseAngleElement : public QObject
{ Q_OBJECT
public:
public slots:
SoCreaseAngleElement* new_SoCreaseAngleElement();
   float  static_SoCreaseAngleElement_get(SoState*  state);
   int  static_SoCreaseAngleElement_getClassStackIndex();
   SoType  static_SoCreaseAngleElement_getClassTypeId();
   float  static_SoCreaseAngleElement_getDefault();
   void py_q_init(SoCreaseAngleElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoCreaseAngleElement*)theWrappedObject)->py_q_init(state));}
   void static_SoCreaseAngleElement_set(SoState*  state, float  angle);
};





class PythonQtShell_SoDrawStyleElement : public SoDrawStyleElement
{
public:
    PythonQtShell_SoDrawStyleElement():SoDrawStyleElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoDrawStyleElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(int  value) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoDrawStyleElement : public SoDrawStyleElement
{ public:
inline void py_q_init(SoState*  state) { SoDrawStyleElement::init(state); }
};

class PythonQtWrapper_SoDrawStyleElement : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Style )
enum Style{
  FILLED = SoDrawStyleElement::FILLED,   LINES = SoDrawStyleElement::LINES,   POINTS = SoDrawStyleElement::POINTS,   INVISIBLE = SoDrawStyleElement::INVISIBLE};
public slots:
SoDrawStyleElement* new_SoDrawStyleElement();
   SoDrawStyleElement::Style  static_SoDrawStyleElement_get(SoState*  state);
   int  static_SoDrawStyleElement_getClassStackIndex();
   SoType  static_SoDrawStyleElement_getClassTypeId();
   SoDrawStyleElement::Style  static_SoDrawStyleElement_getDefault();
   void py_q_init(SoDrawStyleElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoDrawStyleElement*)theWrappedObject)->py_q_init(state));}
   void static_SoDrawStyleElement_set(SoState*  state, SoDrawStyleElement::Style  style);
};





class PythonQtShell_SoElement : public SoElement
{
public:
    PythonQtShell_SoElement():SoElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoElement : public SoElement
{ public:
inline void promoted_capture(SoState*  state) const { this->capture(state); }
inline void promoted_captureThis(SoState*  state) const { this->captureThis(state); }
static inline int  promoted_createStackIndex(SoType  id) { return createStackIndex(id); }
static inline const SoElement*  promoted_getConstElement(SoState*  state, int  stackIndex) { return getConstElement(state, stackIndex); }
static inline SoElement*  promoted_getElement(SoState*  state, int  stackIndex) { return getElement(state, stackIndex); }
inline SoElement*  promoted_getNextFree() const { return this->getNextFree(); }
inline SoElement*  promoted_getNextInStack() const { return this->getNextInStack(); }
inline void promoted_setStackIndex(int  index) { this->setStackIndex(index); }
inline void promoted_setTypeId(SoType  id) { this->setTypeId(id); }
inline void py_q_captureThis(SoState*  state) const { SoElement::captureThis(state); }
inline SoElement*  py_q_copyMatchInfo() const { return this->copyMatchInfo(); }
inline void py_q_init(SoState*  state) { SoElement::init(state); }
inline bool  py_q_matches(const SoElement*  elt) const { return this->matches(elt); }
inline void py_q_pop(SoState*  state, const SoElement*  prevTopElement) { SoElement::pop(state, prevTopElement); }
inline void py_q_push(SoState*  state) { SoElement::push(state); }
};

class PythonQtWrapper_SoElement : public QObject
{ Q_OBJECT
public:
public slots:
SoElement* new_SoElement();
void delete_SoElement(SoElement* obj) { delete obj; }
   void capture(SoElement* theWrappedObject, SoState*  state) const;
   void captureThis(SoElement* theWrappedObject, SoState*  state) const;
   void py_q_captureThis(SoElement* theWrappedObject, SoState*  state) const{  (((PythonQtPublicPromoter_SoElement*)theWrappedObject)->py_q_captureThis(state));}
   SoElement*  copyMatchInfo(SoElement* theWrappedObject) const;
   SoElement*  py_q_copyMatchInfo(SoElement* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoElement*)theWrappedObject)->py_q_copyMatchInfo());}
   int  static_SoElement_createStackIndex(SoType  id);
   SoType  static_SoElement_getClassTypeId();
   const SoElement*  static_SoElement_getConstElement(SoState*  state, int  stackIndex);
   int  getDepth(SoElement* theWrappedObject) const;
   SoElement*  static_SoElement_getElement(SoState*  state, int  stackIndex);
   SoType  static_SoElement_getIdFromStackIndex(int  stackIndex);
   SoElement*  getNext(SoElement* theWrappedObject) const;
   SoElement*  getNextFree(SoElement* theWrappedObject) const;
   SoElement*  getNextInStack(SoElement* theWrappedObject) const;
   int  static_SoElement_getNumStackIndices();
   int  getStackIndex(SoElement* theWrappedObject) const;
   void init(SoElement* theWrappedObject, SoState*  state);
   void py_q_init(SoElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoElement*)theWrappedObject)->py_q_init(state));}
   void static_SoElement_initElements();
   bool  matches(SoElement* theWrappedObject, const SoElement*  elt) const;
   bool  py_q_matches(SoElement* theWrappedObject, const SoElement*  elt) const{  return (((PythonQtPublicPromoter_SoElement*)theWrappedObject)->py_q_matches(elt));}
   void pop(SoElement* theWrappedObject, SoState*  state, const SoElement*  prevTopElement);
   void py_q_pop(SoElement* theWrappedObject, SoState*  state, const SoElement*  prevTopElement){  (((PythonQtPublicPromoter_SoElement*)theWrappedObject)->py_q_pop(state, prevTopElement));}
   void push(SoElement* theWrappedObject, SoState*  state);
   void py_q_push(SoElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoElement*)theWrappedObject)->py_q_push(state));}
   void setDepth(SoElement* theWrappedObject, int  dpth);
   void setNext(SoElement* theWrappedObject, SoElement*  nxt);
   void setNextFree(SoElement* theWrappedObject, SoElement*  nxt);
   void setNextInStack(SoElement* theWrappedObject, SoElement*  nxt);
   void setStackIndex(SoElement* theWrappedObject, int  index);
   void setTypeId(SoElement* theWrappedObject, SoType  id);
};





class PythonQtShell_SoFloatElement : public SoFloatElement
{
public:
    PythonQtShell_SoFloatElement():SoFloatElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoFloatElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(float  value) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoFloatElement : public SoFloatElement
{ public:
static inline float  promoted_get(int  stackIndex, SoState*  state) { return get(stackIndex, state); }
static inline void promoted_set(int  stackIndex, SoState*  state, float  value) { set(stackIndex, state, value); }
inline void promoted_setElt(float  value) { this->setElt(value); }
inline SoElement*  py_q_copyMatchInfo() const { return SoFloatElement::copyMatchInfo(); }
inline bool  py_q_matches(const SoElement*  elt) const { return SoFloatElement::matches(elt); }
inline void py_q_setElt(float  value) { SoFloatElement::setElt(value); }
};

class PythonQtWrapper_SoFloatElement : public QObject
{ Q_OBJECT
public:
public slots:
SoFloatElement* new_SoFloatElement();
   SoElement*  py_q_copyMatchInfo(SoFloatElement* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoFloatElement*)theWrappedObject)->py_q_copyMatchInfo());}
   float  static_SoFloatElement_get(int  stackIndex, SoState*  state);
   int  static_SoFloatElement_getClassStackIndex();
   SoType  static_SoFloatElement_getClassTypeId();
   bool  py_q_matches(SoFloatElement* theWrappedObject, const SoElement*  elt) const{  return (((PythonQtPublicPromoter_SoFloatElement*)theWrappedObject)->py_q_matches(elt));}
   void static_SoFloatElement_set(int  stackIndex, SoState*  state, float  value);
   void setElt(SoFloatElement* theWrappedObject, float  value);
   void py_q_setElt(SoFloatElement* theWrappedObject, float  value){  (((PythonQtPublicPromoter_SoFloatElement*)theWrappedObject)->py_q_setElt(value));}
};





class PythonQtShell_SoFocalDistanceElement : public SoFocalDistanceElement
{
public:
    PythonQtShell_SoFocalDistanceElement():SoFocalDistanceElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoFocalDistanceElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(float  value) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoFocalDistanceElement : public SoFocalDistanceElement
{ public:
inline void py_q_init(SoState*  state) { SoFocalDistanceElement::init(state); }
};

class PythonQtWrapper_SoFocalDistanceElement : public QObject
{ Q_OBJECT
public:
public slots:
SoFocalDistanceElement* new_SoFocalDistanceElement();
   float  static_SoFocalDistanceElement_get(SoState*  state);
   int  static_SoFocalDistanceElement_getClassStackIndex();
   SoType  static_SoFocalDistanceElement_getClassTypeId();
   float  static_SoFocalDistanceElement_getDefault();
   void py_q_init(SoFocalDistanceElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoFocalDistanceElement*)theWrappedObject)->py_q_init(state));}
   void static_SoFocalDistanceElement_set(SoState*  state, float  distance);
};





class PythonQtShell_SoFontNameElement : public SoFontNameElement
{
public:
    PythonQtShell_SoFontNameElement():SoFontNameElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoFontNameElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoFontNameElement : public SoFontNameElement
{ public:
inline SoElement*  py_q_copyMatchInfo() const { return SoFontNameElement::copyMatchInfo(); }
inline void py_q_init(SoState*  state) { SoFontNameElement::init(state); }
inline bool  py_q_matches(const SoElement*  elt) const { return SoFontNameElement::matches(elt); }
};

class PythonQtWrapper_SoFontNameElement : public QObject
{ Q_OBJECT
public:
public slots:
SoFontNameElement* new_SoFontNameElement();
   SoElement*  py_q_copyMatchInfo(SoFontNameElement* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoFontNameElement*)theWrappedObject)->py_q_copyMatchInfo());}
   const SbName*  static_SoFontNameElement_get(SoState*  state);
   int  static_SoFontNameElement_getClassStackIndex();
   SoType  static_SoFontNameElement_getClassTypeId();
   SbName  static_SoFontNameElement_getDefault();
   void py_q_init(SoFontNameElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoFontNameElement*)theWrappedObject)->py_q_init(state));}
   bool  py_q_matches(SoFontNameElement* theWrappedObject, const SoElement*  elt) const{  return (((PythonQtPublicPromoter_SoFontNameElement*)theWrappedObject)->py_q_matches(elt));}
   void static_SoFontNameElement_set(SoState*  state, SoNode*  node, const SbName&  fontName);
};





class PythonQtShell_SoFontSizeElement : public SoFontSizeElement
{
public:
    PythonQtShell_SoFontSizeElement():SoFontSizeElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoFontSizeElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(float  value) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoFontSizeElement : public SoFontSizeElement
{ public:
inline void py_q_init(SoState*  state) { SoFontSizeElement::init(state); }
};

class PythonQtWrapper_SoFontSizeElement : public QObject
{ Q_OBJECT
public:
public slots:
SoFontSizeElement* new_SoFontSizeElement();
   float  static_SoFontSizeElement_get(SoState*  state);
   int  static_SoFontSizeElement_getClassStackIndex();
   SoType  static_SoFontSizeElement_getClassTypeId();
   float  static_SoFontSizeElement_getDefault();
   void py_q_init(SoFontSizeElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoFontSizeElement*)theWrappedObject)->py_q_init(state));}
   void static_SoFontSizeElement_set(SoState*  state, float  size);
};





class PythonQtShell_SoGLCacheContextElement : public SoGLCacheContextElement
{
public:
    PythonQtShell_SoGLCacheContextElement():SoGLCacheContextElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoGLCacheContextElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoGLCacheContextElement : public SoGLCacheContextElement
{ public:
inline SoElement*  py_q_copyMatchInfo() const { return SoGLCacheContextElement::copyMatchInfo(); }
inline void py_q_init(SoState*  state) { SoGLCacheContextElement::init(state); }
inline bool  py_q_matches(const SoElement*  elt) const { return SoGLCacheContextElement::matches(elt); }
};

class PythonQtWrapper_SoGLCacheContextElement : public QObject
{ Q_OBJECT
public:
public slots:
SoGLCacheContextElement* new_SoGLCacheContextElement();
   bool  static_SoGLCacheContextElement_areMipMapsFast(SoState*  state);
   SoElement*  py_q_copyMatchInfo(SoGLCacheContextElement* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoGLCacheContextElement*)theWrappedObject)->py_q_copyMatchInfo());}
   int  static_SoGLCacheContextElement_get(SoState*  state);
   int  static_SoGLCacheContextElement_getClassStackIndex();
   SoType  static_SoGLCacheContextElement_getClassTypeId();
   void py_q_init(SoGLCacheContextElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLCacheContextElement*)theWrappedObject)->py_q_init(state));}
   bool  py_q_matches(SoGLCacheContextElement* theWrappedObject, const SoElement*  elt) const{  return (((PythonQtPublicPromoter_SoGLCacheContextElement*)theWrappedObject)->py_q_matches(elt));}
   int  static_SoGLCacheContextElement_resetAutoCacheBits(SoState*  state);
   void static_SoGLCacheContextElement_set(SoState*  state, int  context, bool  is2PassTransparency);
   void static_SoGLCacheContextElement_setAutoCacheBits(SoState*  state, int  bits);
   void static_SoGLCacheContextElement_shouldAutoCache(SoState*  state, int  bits);
};





class PythonQtShell_SoGLClipPlaneElement : public SoGLClipPlaneElement
{
public:
    PythonQtShell_SoGLClipPlaneElement():SoGLClipPlaneElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoGLClipPlaneElement() override;

void addToElt(const SbPlane&  plane, const SbMatrix&  modelMatrix) override;
void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoGLClipPlaneElement : public SoGLClipPlaneElement
{ public:
inline void promoted_addToElt(const SbPlane&  plane, const SbMatrix&  modelMatrix) { this->addToElt(plane, modelMatrix); }
inline void py_q_addToElt(const SbPlane&  plane, const SbMatrix&  modelMatrix) { SoGLClipPlaneElement::addToElt(plane, modelMatrix); }
inline void py_q_pop(SoState*  state, const SoElement*  prevTopElement) { SoGLClipPlaneElement::pop(state, prevTopElement); }
};

class PythonQtWrapper_SoGLClipPlaneElement : public QObject
{ Q_OBJECT
public:
public slots:
SoGLClipPlaneElement* new_SoGLClipPlaneElement();
   void py_q_addToElt(SoGLClipPlaneElement* theWrappedObject, const SbPlane&  plane, const SbMatrix&  modelMatrix){  (((PythonQtPublicPromoter_SoGLClipPlaneElement*)theWrappedObject)->py_q_addToElt(plane, modelMatrix));}
   int  static_SoGLClipPlaneElement_getClassStackIndex();
   SoType  static_SoGLClipPlaneElement_getClassTypeId();
   int  static_SoGLClipPlaneElement_getMaxGLPlanes();
   void py_q_pop(SoGLClipPlaneElement* theWrappedObject, SoState*  state, const SoElement*  prevTopElement){  (((PythonQtPublicPromoter_SoGLClipPlaneElement*)theWrappedObject)->py_q_pop(state, prevTopElement));}
};





class PythonQtShell_SoGLCoordinateElement : public SoGLCoordinateElement
{
public:
    PythonQtShell_SoGLCoordinateElement():SoGLCoordinateElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoGLCoordinateElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoGLCoordinateElement : public QObject
{ Q_OBJECT
public:
public slots:
SoGLCoordinateElement* new_SoGLCoordinateElement();
   int  static_SoGLCoordinateElement_getClassStackIndex();
   SoType  static_SoGLCoordinateElement_getClassTypeId();
   void send(SoGLCoordinateElement* theWrappedObject, int  index) const;
};





class PythonQtShell_SoGLDrawStyleElement : public SoGLDrawStyleElement
{
public:
    PythonQtShell_SoGLDrawStyleElement():SoGLDrawStyleElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoGLDrawStyleElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(int  style) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoGLDrawStyleElement : public SoGLDrawStyleElement
{ public:
inline void promoted_setElt(int  style) { this->setElt(style); }
inline void py_q_init(SoState*  state) { SoGLDrawStyleElement::init(state); }
inline void py_q_pop(SoState*  state, const SoElement*  prevTopElement) { SoGLDrawStyleElement::pop(state, prevTopElement); }
inline void py_q_push(SoState*  state) { SoGLDrawStyleElement::push(state); }
inline void py_q_setElt(int  style) { SoGLDrawStyleElement::setElt(style); }
};

class PythonQtWrapper_SoGLDrawStyleElement : public QObject
{ Q_OBJECT
public:
public slots:
SoGLDrawStyleElement* new_SoGLDrawStyleElement();
   int  static_SoGLDrawStyleElement_getClassStackIndex();
   SoType  static_SoGLDrawStyleElement_getClassTypeId();
   void py_q_init(SoGLDrawStyleElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLDrawStyleElement*)theWrappedObject)->py_q_init(state));}
   void py_q_pop(SoGLDrawStyleElement* theWrappedObject, SoState*  state, const SoElement*  prevTopElement){  (((PythonQtPublicPromoter_SoGLDrawStyleElement*)theWrappedObject)->py_q_pop(state, prevTopElement));}
   void py_q_push(SoGLDrawStyleElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLDrawStyleElement*)theWrappedObject)->py_q_push(state));}
   void py_q_setElt(SoGLDrawStyleElement* theWrappedObject, int  style){  (((PythonQtPublicPromoter_SoGLDrawStyleElement*)theWrappedObject)->py_q_setElt(style));}
};





class PythonQtShell_SoGLLazyElement : public SoGLLazyElement
{
public:
    PythonQtShell_SoGLLazyElement():SoGLLazyElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoGLLazyElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  arg__1) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoGLLazyElement : public SoGLLazyElement
{ public:
inline SoElement*  py_q_copyMatchInfo() const { return SoGLLazyElement::copyMatchInfo(); }
inline void py_q_init(SoState*  state) { SoGLLazyElement::init(state); }
inline bool  py_q_matches(const SoElement*  arg__1) const { return SoGLLazyElement::matches(arg__1); }
inline void py_q_pop(SoState*  state, const SoElement*  prevTopElement) { SoGLLazyElement::pop(state, prevTopElement); }
inline void py_q_push(SoState*  state) { SoGLLazyElement::push(state); }
};

class PythonQtWrapper_SoGLLazyElement : public QObject
{ Q_OBJECT
public:
public slots:
SoGLLazyElement* new_SoGLLazyElement();
void delete_SoGLLazyElement(SoGLLazyElement* obj) { delete obj; }
   SoGLLazyElement*  copyLazyMatchInfo(SoGLLazyElement* theWrappedObject, SoState*  state);
   SoElement*  py_q_copyMatchInfo(SoGLLazyElement* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoGLLazyElement*)theWrappedObject)->py_q_copyMatchInfo());}
   int  static_SoGLLazyElement_getClassStackIndex();
   SoType  static_SoGLLazyElement_getClassTypeId();
   SoGLLazyElement*  static_SoGLLazyElement_getInstance(const SoState*  state);
   void py_q_init(SoGLLazyElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLLazyElement*)theWrappedObject)->py_q_init(state));}
   bool  lazyMatches(SoGLLazyElement* theWrappedObject, unsigned int  checkGLFlag, unsigned int  checkIVFlag, const SoGLLazyElement*  eltInState);
   bool  py_q_matches(SoGLLazyElement* theWrappedObject, const SoElement*  arg__1) const{  return (((PythonQtPublicPromoter_SoGLLazyElement*)theWrappedObject)->py_q_matches(arg__1));}
   void py_q_pop(SoGLLazyElement* theWrappedObject, SoState*  state, const SoElement*  prevTopElement){  (((PythonQtPublicPromoter_SoGLLazyElement*)theWrappedObject)->py_q_pop(state, prevTopElement));}
   void py_q_push(SoGLLazyElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLLazyElement*)theWrappedObject)->py_q_push(state));}
   void reset(SoGLLazyElement* theWrappedObject, SoState*  state, unsigned int  bitmask) const;
   void send(SoGLLazyElement* theWrappedObject, const SoState*  state, unsigned int  mask) const;
   void static_SoGLLazyElement_sendAllMaterial(SoState*  state);
   void sendDiffuseByIndex(SoGLLazyElement* theWrappedObject, int  index) const;
   void static_SoGLLazyElement_sendNoMaterial(SoState*  state);
   void static_SoGLLazyElement_sendOnlyDiffuseColor(SoState*  state);
   void sendVPPacked(SoGLLazyElement* theWrappedObject, SoState*  state, const unsigned char*  pcolor);
};





class PythonQtShell_SoGLLightIdElement : public SoGLLightIdElement
{
public:
    PythonQtShell_SoGLLightIdElement():SoGLLightIdElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoGLLightIdElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(int  value) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoGLLightIdElement : public SoGLLightIdElement
{ public:
inline void py_q_init(SoState*  state) { SoGLLightIdElement::init(state); }
inline void py_q_pop(SoState*  state, const SoElement*  prevTopElement) { SoGLLightIdElement::pop(state, prevTopElement); }
inline void py_q_push(SoState*  state) { SoGLLightIdElement::push(state); }
};

class PythonQtWrapper_SoGLLightIdElement : public QObject
{ Q_OBJECT
public:
public slots:
SoGLLightIdElement* new_SoGLLightIdElement();
   int  static_SoGLLightIdElement_get(SoState*  state);
   int  static_SoGLLightIdElement_getClassStackIndex();
   SoType  static_SoGLLightIdElement_getClassTypeId();
   int  static_SoGLLightIdElement_getDefault();
   int  static_SoGLLightIdElement_getMaxGLSources();
   int  static_SoGLLightIdElement_increment(SoState*  state);
   void py_q_init(SoGLLightIdElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLLightIdElement*)theWrappedObject)->py_q_init(state));}
   void py_q_pop(SoGLLightIdElement* theWrappedObject, SoState*  state, const SoElement*  prevTopElement){  (((PythonQtPublicPromoter_SoGLLightIdElement*)theWrappedObject)->py_q_pop(state, prevTopElement));}
   void py_q_push(SoGLLightIdElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLLightIdElement*)theWrappedObject)->py_q_push(state));}
};





class PythonQtShell_SoGLLinePatternElement : public SoGLLinePatternElement
{
public:
    PythonQtShell_SoGLLinePatternElement():SoGLLinePatternElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoGLLinePatternElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(int  pattern) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoGLLinePatternElement : public SoGLLinePatternElement
{ public:
inline void promoted_setElt(int  pattern) { this->setElt(pattern); }
inline void py_q_init(SoState*  state) { SoGLLinePatternElement::init(state); }
inline void py_q_pop(SoState*  state, const SoElement*  prevTopElement) { SoGLLinePatternElement::pop(state, prevTopElement); }
inline void py_q_push(SoState*  state) { SoGLLinePatternElement::push(state); }
inline void py_q_setElt(int  pattern) { SoGLLinePatternElement::setElt(pattern); }
};

class PythonQtWrapper_SoGLLinePatternElement : public QObject
{ Q_OBJECT
public:
public slots:
SoGLLinePatternElement* new_SoGLLinePatternElement();
   int  static_SoGLLinePatternElement_getClassStackIndex();
   SoType  static_SoGLLinePatternElement_getClassTypeId();
   void py_q_init(SoGLLinePatternElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLLinePatternElement*)theWrappedObject)->py_q_init(state));}
   void py_q_pop(SoGLLinePatternElement* theWrappedObject, SoState*  state, const SoElement*  prevTopElement){  (((PythonQtPublicPromoter_SoGLLinePatternElement*)theWrappedObject)->py_q_pop(state, prevTopElement));}
   void py_q_push(SoGLLinePatternElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLLinePatternElement*)theWrappedObject)->py_q_push(state));}
   void py_q_setElt(SoGLLinePatternElement* theWrappedObject, int  pattern){  (((PythonQtPublicPromoter_SoGLLinePatternElement*)theWrappedObject)->py_q_setElt(pattern));}
};





class PythonQtShell_SoGLLineWidthElement : public SoGLLineWidthElement
{
public:
    PythonQtShell_SoGLLineWidthElement():SoGLLineWidthElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoGLLineWidthElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(float  width) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoGLLineWidthElement : public SoGLLineWidthElement
{ public:
inline void promoted_setElt(float  width) { this->setElt(width); }
inline void py_q_init(SoState*  state) { SoGLLineWidthElement::init(state); }
inline void py_q_pop(SoState*  state, const SoElement*  prevTopElement) { SoGLLineWidthElement::pop(state, prevTopElement); }
inline void py_q_push(SoState*  state) { SoGLLineWidthElement::push(state); }
inline void py_q_setElt(float  width) { SoGLLineWidthElement::setElt(width); }
};

class PythonQtWrapper_SoGLLineWidthElement : public QObject
{ Q_OBJECT
public:
public slots:
SoGLLineWidthElement* new_SoGLLineWidthElement();
   int  static_SoGLLineWidthElement_getClassStackIndex();
   SoType  static_SoGLLineWidthElement_getClassTypeId();
   void py_q_init(SoGLLineWidthElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLLineWidthElement*)theWrappedObject)->py_q_init(state));}
   void py_q_pop(SoGLLineWidthElement* theWrappedObject, SoState*  state, const SoElement*  prevTopElement){  (((PythonQtPublicPromoter_SoGLLineWidthElement*)theWrappedObject)->py_q_pop(state, prevTopElement));}
   void py_q_push(SoGLLineWidthElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLLineWidthElement*)theWrappedObject)->py_q_push(state));}
   void py_q_setElt(SoGLLineWidthElement* theWrappedObject, float  width){  (((PythonQtPublicPromoter_SoGLLineWidthElement*)theWrappedObject)->py_q_setElt(width));}
};





class PythonQtShell_SoGLModelMatrixElement : public SoGLModelMatrixElement
{
public:
    PythonQtShell_SoGLModelMatrixElement():SoGLModelMatrixElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoGLModelMatrixElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
void makeEltIdentity() override;
bool  matches(const SoElement*  elt) const override;
void multElt(const SbMatrix&  matrix) override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void popMatrixElt(const SbMatrix&  m) override;
void push(SoState*  state) override;
SbMatrix  pushMatrixElt() override;
void rotateEltBy(const SbRotation&  translation) override;
void scaleEltBy(const SbVec3f&  scaleFactor) override;
void setElt(const SbMatrix&  matrix) override;
void translateEltBy(const SbVec3f&  translation) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoGLModelMatrixElement : public SoGLModelMatrixElement
{ public:
inline void promoted_makeEltIdentity() { this->makeEltIdentity(); }
inline void promoted_multElt(const SbMatrix&  matrix) { this->multElt(matrix); }
inline void promoted_popMatrixElt(const SbMatrix&  m) { this->popMatrixElt(m); }
inline SbMatrix  promoted_pushMatrixElt() { return this->pushMatrixElt(); }
inline void promoted_rotateEltBy(const SbRotation&  translation) { this->rotateEltBy(translation); }
inline void promoted_scaleEltBy(const SbVec3f&  scaleFactor) { this->scaleEltBy(scaleFactor); }
inline void promoted_setElt(const SbMatrix&  matrix) { this->setElt(matrix); }
inline void promoted_translateEltBy(const SbVec3f&  translation) { this->translateEltBy(translation); }
inline void py_q_init(SoState*  state) { SoGLModelMatrixElement::init(state); }
inline void py_q_makeEltIdentity() { SoGLModelMatrixElement::makeEltIdentity(); }
inline void py_q_multElt(const SbMatrix&  matrix) { SoGLModelMatrixElement::multElt(matrix); }
inline void py_q_pop(SoState*  state, const SoElement*  prevTopElement) { SoGLModelMatrixElement::pop(state, prevTopElement); }
inline void py_q_popMatrixElt(const SbMatrix&  m) { SoGLModelMatrixElement::popMatrixElt(m); }
inline void py_q_push(SoState*  state) { SoGLModelMatrixElement::push(state); }
inline SbMatrix  py_q_pushMatrixElt() { return SoGLModelMatrixElement::pushMatrixElt(); }
inline void py_q_rotateEltBy(const SbRotation&  translation) { SoGLModelMatrixElement::rotateEltBy(translation); }
inline void py_q_scaleEltBy(const SbVec3f&  scaleFactor) { SoGLModelMatrixElement::scaleEltBy(scaleFactor); }
inline void py_q_setElt(const SbMatrix&  matrix) { SoGLModelMatrixElement::setElt(matrix); }
inline void py_q_translateEltBy(const SbVec3f&  translation) { SoGLModelMatrixElement::translateEltBy(translation); }
};

class PythonQtWrapper_SoGLModelMatrixElement : public QObject
{ Q_OBJECT
public:
public slots:
SoGLModelMatrixElement* new_SoGLModelMatrixElement();
   int  static_SoGLModelMatrixElement_getClassStackIndex();
   SoType  static_SoGLModelMatrixElement_getClassTypeId();
   void py_q_init(SoGLModelMatrixElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLModelMatrixElement*)theWrappedObject)->py_q_init(state));}
   void py_q_makeEltIdentity(SoGLModelMatrixElement* theWrappedObject){  (((PythonQtPublicPromoter_SoGLModelMatrixElement*)theWrappedObject)->py_q_makeEltIdentity());}
   void py_q_multElt(SoGLModelMatrixElement* theWrappedObject, const SbMatrix&  matrix){  (((PythonQtPublicPromoter_SoGLModelMatrixElement*)theWrappedObject)->py_q_multElt(matrix));}
   void py_q_pop(SoGLModelMatrixElement* theWrappedObject, SoState*  state, const SoElement*  prevTopElement){  (((PythonQtPublicPromoter_SoGLModelMatrixElement*)theWrappedObject)->py_q_pop(state, prevTopElement));}
   void py_q_popMatrixElt(SoGLModelMatrixElement* theWrappedObject, const SbMatrix&  m){  (((PythonQtPublicPromoter_SoGLModelMatrixElement*)theWrappedObject)->py_q_popMatrixElt(m));}
   void py_q_push(SoGLModelMatrixElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLModelMatrixElement*)theWrappedObject)->py_q_push(state));}
   SbMatrix  py_q_pushMatrixElt(SoGLModelMatrixElement* theWrappedObject){  return (((PythonQtPublicPromoter_SoGLModelMatrixElement*)theWrappedObject)->py_q_pushMatrixElt());}
   void py_q_rotateEltBy(SoGLModelMatrixElement* theWrappedObject, const SbRotation&  translation){  (((PythonQtPublicPromoter_SoGLModelMatrixElement*)theWrappedObject)->py_q_rotateEltBy(translation));}
   void py_q_scaleEltBy(SoGLModelMatrixElement* theWrappedObject, const SbVec3f&  scaleFactor){  (((PythonQtPublicPromoter_SoGLModelMatrixElement*)theWrappedObject)->py_q_scaleEltBy(scaleFactor));}
   void py_q_setElt(SoGLModelMatrixElement* theWrappedObject, const SbMatrix&  matrix){  (((PythonQtPublicPromoter_SoGLModelMatrixElement*)theWrappedObject)->py_q_setElt(matrix));}
   void py_q_translateEltBy(SoGLModelMatrixElement* theWrappedObject, const SbVec3f&  translation){  (((PythonQtPublicPromoter_SoGLModelMatrixElement*)theWrappedObject)->py_q_translateEltBy(translation));}
};





class PythonQtShell_SoGLNormalElement : public SoGLNormalElement
{
public:
    PythonQtShell_SoGLNormalElement():SoGLNormalElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoGLNormalElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoGLNormalElement : public SoGLNormalElement
{ public:
inline void py_q_init(SoState*  state) { SoGLNormalElement::init(state); }
};

class PythonQtWrapper_SoGLNormalElement : public QObject
{ Q_OBJECT
public:
public slots:
SoGLNormalElement* new_SoGLNormalElement();
   int  static_SoGLNormalElement_getClassStackIndex();
   SoType  static_SoGLNormalElement_getClassTypeId();
   void py_q_init(SoGLNormalElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLNormalElement*)theWrappedObject)->py_q_init(state));}
   void send(SoGLNormalElement* theWrappedObject, int  index) const;
};





class PythonQtShell_SoGLPointSizeElement : public SoGLPointSizeElement
{
public:
    PythonQtShell_SoGLPointSizeElement():SoGLPointSizeElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoGLPointSizeElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(float  size) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoGLPointSizeElement : public SoGLPointSizeElement
{ public:
inline void promoted_setElt(float  size) { this->setElt(size); }
inline void py_q_init(SoState*  state) { SoGLPointSizeElement::init(state); }
inline void py_q_pop(SoState*  state, const SoElement*  prevTopElement) { SoGLPointSizeElement::pop(state, prevTopElement); }
inline void py_q_push(SoState*  state) { SoGLPointSizeElement::push(state); }
inline void py_q_setElt(float  size) { SoGLPointSizeElement::setElt(size); }
};

class PythonQtWrapper_SoGLPointSizeElement : public QObject
{ Q_OBJECT
public:
public slots:
SoGLPointSizeElement* new_SoGLPointSizeElement();
   int  static_SoGLPointSizeElement_getClassStackIndex();
   SoType  static_SoGLPointSizeElement_getClassTypeId();
   void py_q_init(SoGLPointSizeElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLPointSizeElement*)theWrappedObject)->py_q_init(state));}
   void py_q_pop(SoGLPointSizeElement* theWrappedObject, SoState*  state, const SoElement*  prevTopElement){  (((PythonQtPublicPromoter_SoGLPointSizeElement*)theWrappedObject)->py_q_pop(state, prevTopElement));}
   void py_q_push(SoGLPointSizeElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLPointSizeElement*)theWrappedObject)->py_q_push(state));}
   void py_q_setElt(SoGLPointSizeElement* theWrappedObject, float  size){  (((PythonQtPublicPromoter_SoGLPointSizeElement*)theWrappedObject)->py_q_setElt(size));}
};





class PythonQtShell_SoGLProjectionMatrixElement : public SoGLProjectionMatrixElement
{
public:
    PythonQtShell_SoGLProjectionMatrixElement():SoGLProjectionMatrixElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoGLProjectionMatrixElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(const SbMatrix&  matrix) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoGLProjectionMatrixElement : public SoGLProjectionMatrixElement
{ public:
inline void promoted_setElt(const SbMatrix&  matrix) { this->setElt(matrix); }
inline void py_q_pop(SoState*  state, const SoElement*  prevTopElement) { SoGLProjectionMatrixElement::pop(state, prevTopElement); }
inline void py_q_setElt(const SbMatrix&  matrix) { SoGLProjectionMatrixElement::setElt(matrix); }
};

class PythonQtWrapper_SoGLProjectionMatrixElement : public QObject
{ Q_OBJECT
public:
public slots:
SoGLProjectionMatrixElement* new_SoGLProjectionMatrixElement();
   int  static_SoGLProjectionMatrixElement_getClassStackIndex();
   SoType  static_SoGLProjectionMatrixElement_getClassTypeId();
   void py_q_pop(SoGLProjectionMatrixElement* theWrappedObject, SoState*  state, const SoElement*  prevTopElement){  (((PythonQtPublicPromoter_SoGLProjectionMatrixElement*)theWrappedObject)->py_q_pop(state, prevTopElement));}
   void py_q_setElt(SoGLProjectionMatrixElement* theWrappedObject, const SbMatrix&  matrix){  (((PythonQtPublicPromoter_SoGLProjectionMatrixElement*)theWrappedObject)->py_q_setElt(matrix));}
};





class PythonQtShell_SoGLRenderPassElement : public SoGLRenderPassElement
{
public:
    PythonQtShell_SoGLRenderPassElement():SoGLRenderPassElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoGLRenderPassElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoGLRenderPassElement : public SoGLRenderPassElement
{ public:
inline SoElement*  py_q_copyMatchInfo() const { return SoGLRenderPassElement::copyMatchInfo(); }
inline void py_q_init(SoState*  state) { SoGLRenderPassElement::init(state); }
inline bool  py_q_matches(const SoElement*  elt) const { return SoGLRenderPassElement::matches(elt); }
};

class PythonQtWrapper_SoGLRenderPassElement : public QObject
{ Q_OBJECT
public:
public slots:
SoGLRenderPassElement* new_SoGLRenderPassElement();
   SoElement*  py_q_copyMatchInfo(SoGLRenderPassElement* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoGLRenderPassElement*)theWrappedObject)->py_q_copyMatchInfo());}
   int  static_SoGLRenderPassElement_get(SoState*  state);
   int  static_SoGLRenderPassElement_getClassStackIndex();
   SoType  static_SoGLRenderPassElement_getClassTypeId();
   void py_q_init(SoGLRenderPassElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLRenderPassElement*)theWrappedObject)->py_q_init(state));}
   bool  py_q_matches(SoGLRenderPassElement* theWrappedObject, const SoElement*  elt) const{  return (((PythonQtPublicPromoter_SoGLRenderPassElement*)theWrappedObject)->py_q_matches(elt));}
   void static_SoGLRenderPassElement_set(SoState*  state, int  pass);
};





class PythonQtShell_SoGLShapeHintsElement : public SoGLShapeHintsElement
{
public:
    PythonQtShell_SoGLShapeHintsElement():SoGLShapeHintsElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoGLShapeHintsElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(SoShapeHintsElement::VertexOrdering  vertexOrdering, SoShapeHintsElement::ShapeType  shapeType, SoShapeHintsElement::FaceType  faceType) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoGLShapeHintsElement : public SoGLShapeHintsElement
{ public:
inline void promoted_setElt(SoShapeHintsElement::VertexOrdering  vertexOrdering, SoShapeHintsElement::ShapeType  shapeType, SoShapeHintsElement::FaceType  faceType) { this->setElt(vertexOrdering, shapeType, faceType); }
inline void py_q_init(SoState*  state) { SoGLShapeHintsElement::init(state); }
inline void py_q_pop(SoState*  state, const SoElement*  prevTopElement) { SoGLShapeHintsElement::pop(state, prevTopElement); }
inline void py_q_push(SoState*  state) { SoGLShapeHintsElement::push(state); }
inline void py_q_setElt(SoShapeHintsElement::VertexOrdering  vertexOrdering, SoShapeHintsElement::ShapeType  shapeType, SoShapeHintsElement::FaceType  faceType) { SoGLShapeHintsElement::setElt(vertexOrdering, shapeType, faceType); }
};

class PythonQtWrapper_SoGLShapeHintsElement : public QObject
{ Q_OBJECT
public:
public slots:
SoGLShapeHintsElement* new_SoGLShapeHintsElement();
   int  static_SoGLShapeHintsElement_getClassStackIndex();
   SoType  static_SoGLShapeHintsElement_getClassTypeId();
   void py_q_init(SoGLShapeHintsElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLShapeHintsElement*)theWrappedObject)->py_q_init(state));}
   void py_q_pop(SoGLShapeHintsElement* theWrappedObject, SoState*  state, const SoElement*  prevTopElement){  (((PythonQtPublicPromoter_SoGLShapeHintsElement*)theWrappedObject)->py_q_pop(state, prevTopElement));}
   void py_q_push(SoGLShapeHintsElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLShapeHintsElement*)theWrappedObject)->py_q_push(state));}
   void py_q_setElt(SoGLShapeHintsElement* theWrappedObject, SoShapeHintsElement::VertexOrdering  vertexOrdering, SoShapeHintsElement::ShapeType  shapeType, SoShapeHintsElement::FaceType  faceType){  (((PythonQtPublicPromoter_SoGLShapeHintsElement*)theWrappedObject)->py_q_setElt(vertexOrdering, shapeType, faceType));}
};





class PythonQtShell_SoGLTextureCoordinateElement : public SoGLTextureCoordinateElement
{
public:
    PythonQtShell_SoGLTextureCoordinateElement():SoGLTextureCoordinateElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoGLTextureCoordinateElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
SoTextureCoordinateElement::CoordType  getType() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoGLTextureCoordinateElement : public SoGLTextureCoordinateElement
{ public:
inline SoTextureCoordinateElement::CoordType  py_q_getType() const { return SoGLTextureCoordinateElement::getType(); }
inline void py_q_init(SoState*  state) { SoGLTextureCoordinateElement::init(state); }
inline void py_q_pop(SoState*  state, const SoElement*  prevTopElement) { SoGLTextureCoordinateElement::pop(state, prevTopElement); }
inline void py_q_push(SoState*  state) { SoGLTextureCoordinateElement::push(state); }
};

class PythonQtWrapper_SoGLTextureCoordinateElement : public QObject
{ Q_OBJECT
public:
public slots:
SoGLTextureCoordinateElement* new_SoGLTextureCoordinateElement();
   int  static_SoGLTextureCoordinateElement_getClassStackIndex();
   SoType  static_SoGLTextureCoordinateElement_getClassTypeId();
   const SoGLTextureCoordinateElement*  static_SoGLTextureCoordinateElement_getInstance(SoState*  state);
   SoTextureCoordinateElement::CoordType  py_q_getType(SoGLTextureCoordinateElement* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoGLTextureCoordinateElement*)theWrappedObject)->py_q_getType());}
   void py_q_init(SoGLTextureCoordinateElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLTextureCoordinateElement*)theWrappedObject)->py_q_init(state));}
   void py_q_pop(SoGLTextureCoordinateElement* theWrappedObject, SoState*  state, const SoElement*  prevTopElement){  (((PythonQtPublicPromoter_SoGLTextureCoordinateElement*)theWrappedObject)->py_q_pop(state, prevTopElement));}
   void py_q_push(SoGLTextureCoordinateElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLTextureCoordinateElement*)theWrappedObject)->py_q_push(state));}
   void send(SoGLTextureCoordinateElement* theWrappedObject, int  index) const;
};





class PythonQtShell_SoGLTextureEnabledElement : public SoGLTextureEnabledElement
{
public:
    PythonQtShell_SoGLTextureEnabledElement():SoGLTextureEnabledElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoGLTextureEnabledElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(int  value) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoGLTextureEnabledElement : public SoGLTextureEnabledElement
{ public:
inline void py_q_init(SoState*  state) { SoGLTextureEnabledElement::init(state); }
inline void py_q_pop(SoState*  state, const SoElement*  prevTopElement) { SoGLTextureEnabledElement::pop(state, prevTopElement); }
inline void py_q_push(SoState*  state) { SoGLTextureEnabledElement::push(state); }
inline void py_q_setElt(int  value) { SoGLTextureEnabledElement::setElt(value); }
};

class PythonQtWrapper_SoGLTextureEnabledElement : public QObject
{ Q_OBJECT
public:
public slots:
SoGLTextureEnabledElement* new_SoGLTextureEnabledElement();
void delete_SoGLTextureEnabledElement(SoGLTextureEnabledElement* obj) { delete obj; }
   bool  static_SoGLTextureEnabledElement_get(SoState*  state);
   int  static_SoGLTextureEnabledElement_getClassStackIndex();
   SoType  static_SoGLTextureEnabledElement_getClassTypeId();
   bool  static_SoGLTextureEnabledElement_getDefault();
   void py_q_init(SoGLTextureEnabledElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLTextureEnabledElement*)theWrappedObject)->py_q_init(state));}
   void py_q_pop(SoGLTextureEnabledElement* theWrappedObject, SoState*  state, const SoElement*  prevTopElement){  (((PythonQtPublicPromoter_SoGLTextureEnabledElement*)theWrappedObject)->py_q_pop(state, prevTopElement));}
   void py_q_push(SoGLTextureEnabledElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLTextureEnabledElement*)theWrappedObject)->py_q_push(state));}
   void static_SoGLTextureEnabledElement_set(SoState*  state, bool  value);
   void py_q_setElt(SoGLTextureEnabledElement* theWrappedObject, int  value){  (((PythonQtPublicPromoter_SoGLTextureEnabledElement*)theWrappedObject)->py_q_setElt(value));}
};


