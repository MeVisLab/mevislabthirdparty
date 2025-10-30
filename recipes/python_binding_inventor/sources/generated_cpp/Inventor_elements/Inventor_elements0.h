#include <Inventor/SbColor.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h>
#include <Inventor/SbViewportRegion.h>
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
#include <Inventor/elements/SoGLTextureImageElement.h>
#include <Inventor/elements/SoGLTextureMatrixElement.h>
#include <Inventor/elements/SoGLUpdateAreaElement.h>
#include <Inventor/elements/SoGLViewingMatrixElement.h>
#include <Inventor/elements/SoGLViewportRegionElement.h>
#include <Inventor/elements/SoInt32Element.h>
#include <Inventor/elements/SoLazyElement.h>
#include <Inventor/elements/SoLightAttenuationElement.h>
#include <Inventor/elements/SoLinePatternElement.h>
#include <Inventor/elements/SoLineWidthElement.h>
#include <Inventor/elements/SoLocalBBoxMatrixElement.h>
#include <Inventor/elements/SoMaterialBindingElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/elements/SoNormalBindingElement.h>
#include <Inventor/elements/SoNormalElement.h>
#include <Inventor/elements/SoOverrideElement.h>
#include <Inventor/elements/SoPickRayElement.h>
#include <Inventor/elements/SoPickStyleElement.h>
#include <Inventor/elements/SoPointSizeElement.h>
#include <Inventor/elements/SoProfileCoordinateElement.h>
#include <Inventor/elements/SoProfileElement.h>
#include <Inventor/elements/SoProjectionMatrixElement.h>
#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/elements/SoShapeHintsElement.h>
#include <Inventor/elements/SoShapeStyleElement.h>
#include <Inventor/elements/SoSwitchElement.h>
#include <Inventor/elements/SoTextureCoordinateBindingElement.h>
#include <Inventor/elements/SoTextureCoordinateElement.h>
#include <Inventor/elements/SoTextureImageElement.h>
#include <Inventor/elements/SoTextureMatrixElement.h>
#include <Inventor/elements/SoTextureQualityElement.h>
#include <Inventor/elements/SoUnitsElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoViewingMatrixElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoProfile.h>
#include <PythonQt.h>
#include <QObject>
#include <QVariant>



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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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
public Q_SLOTS:
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





class PythonQtShell_SoGLTextureImageElement : public SoGLTextureImageElement
{
public:
    PythonQtShell_SoGLTextureImageElement():SoGLTextureImageElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoGLTextureImageElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(const SbVec2s&  s, int  nc, const unsigned char*  bytes, int  wrapS, int  wrapT, int  model, const SbColor&  blendColor) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoGLTextureImageElement : public SoGLTextureImageElement
{ public:
inline void promoted_setElt(const SbVec2s&  s, int  nc, const unsigned char*  bytes, int  wrapS, int  wrapT, int  model, const SbColor&  blendColor) { this->setElt(s, nc, bytes, wrapS, wrapT, model, blendColor); }
inline void py_q_init(SoState*  state) { SoGLTextureImageElement::init(state); }
inline void py_q_pop(SoState*  state, const SoElement*  prevTopElement) { SoGLTextureImageElement::pop(state, prevTopElement); }
inline void py_q_setElt(const SbVec2s&  s, int  nc, const unsigned char*  bytes, int  wrapS, int  wrapT, int  model, const SbColor&  blendColor) { SoGLTextureImageElement::setElt(s, nc, bytes, wrapS, wrapT, model, blendColor); }
};

class PythonQtWrapper_SoGLTextureImageElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoGLTextureImageElement* new_SoGLTextureImageElement();
   int  static_SoGLTextureImageElement_getClassStackIndex();
   SoType  static_SoGLTextureImageElement_getClassTypeId();
   void py_q_init(SoGLTextureImageElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLTextureImageElement*)theWrappedObject)->py_q_init(state));}
   void py_q_pop(SoGLTextureImageElement* theWrappedObject, SoState*  state, const SoElement*  prevTopElement){  (((PythonQtPublicPromoter_SoGLTextureImageElement*)theWrappedObject)->py_q_pop(state, prevTopElement));}
   void py_q_setElt(SoGLTextureImageElement* theWrappedObject, const SbVec2s&  s, int  nc, const unsigned char*  bytes, int  wrapS, int  wrapT, int  model, const SbColor&  blendColor){  (((PythonQtPublicPromoter_SoGLTextureImageElement*)theWrappedObject)->py_q_setElt(s, nc, bytes, wrapS, wrapT, model, blendColor));}
};





class PythonQtShell_SoGLTextureMatrixElement : public SoGLTextureMatrixElement
{
public:
    PythonQtShell_SoGLTextureMatrixElement():SoGLTextureMatrixElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoGLTextureMatrixElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
void makeEltIdentity() override;
bool  matches(const SoElement*  elt) const override;
void multElt(const SbMatrix&  matrix) override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void rotateEltBy(const SbRotation&  translation) override;
void scaleEltBy(const SbVec3f&  scaleFactor) override;
void translateEltBy(const SbVec3f&  translation) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoGLTextureMatrixElement : public SoGLTextureMatrixElement
{ public:
inline void promoted_makeEltIdentity() { this->makeEltIdentity(); }
inline void promoted_multElt(const SbMatrix&  matrix) { this->multElt(matrix); }
inline void promoted_rotateEltBy(const SbRotation&  translation) { this->rotateEltBy(translation); }
inline void promoted_scaleEltBy(const SbVec3f&  scaleFactor) { this->scaleEltBy(scaleFactor); }
inline void promoted_translateEltBy(const SbVec3f&  translation) { this->translateEltBy(translation); }
inline void py_q_makeEltIdentity() { SoGLTextureMatrixElement::makeEltIdentity(); }
inline void py_q_multElt(const SbMatrix&  matrix) { SoGLTextureMatrixElement::multElt(matrix); }
inline void py_q_pop(SoState*  state, const SoElement*  prevTopElement) { SoGLTextureMatrixElement::pop(state, prevTopElement); }
inline void py_q_rotateEltBy(const SbRotation&  translation) { SoGLTextureMatrixElement::rotateEltBy(translation); }
inline void py_q_scaleEltBy(const SbVec3f&  scaleFactor) { SoGLTextureMatrixElement::scaleEltBy(scaleFactor); }
inline void py_q_translateEltBy(const SbVec3f&  translation) { SoGLTextureMatrixElement::translateEltBy(translation); }
};

class PythonQtWrapper_SoGLTextureMatrixElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoGLTextureMatrixElement* new_SoGLTextureMatrixElement();
   int  static_SoGLTextureMatrixElement_getClassStackIndex();
   SoType  static_SoGLTextureMatrixElement_getClassTypeId();
   void py_q_makeEltIdentity(SoGLTextureMatrixElement* theWrappedObject){  (((PythonQtPublicPromoter_SoGLTextureMatrixElement*)theWrappedObject)->py_q_makeEltIdentity());}
   void py_q_multElt(SoGLTextureMatrixElement* theWrappedObject, const SbMatrix&  matrix){  (((PythonQtPublicPromoter_SoGLTextureMatrixElement*)theWrappedObject)->py_q_multElt(matrix));}
   void py_q_pop(SoGLTextureMatrixElement* theWrappedObject, SoState*  state, const SoElement*  prevTopElement){  (((PythonQtPublicPromoter_SoGLTextureMatrixElement*)theWrappedObject)->py_q_pop(state, prevTopElement));}
   void py_q_rotateEltBy(SoGLTextureMatrixElement* theWrappedObject, const SbRotation&  translation){  (((PythonQtPublicPromoter_SoGLTextureMatrixElement*)theWrappedObject)->py_q_rotateEltBy(translation));}
   void py_q_scaleEltBy(SoGLTextureMatrixElement* theWrappedObject, const SbVec3f&  scaleFactor){  (((PythonQtPublicPromoter_SoGLTextureMatrixElement*)theWrappedObject)->py_q_scaleEltBy(scaleFactor));}
   void py_q_translateEltBy(SoGLTextureMatrixElement* theWrappedObject, const SbVec3f&  translation){  (((PythonQtPublicPromoter_SoGLTextureMatrixElement*)theWrappedObject)->py_q_translateEltBy(translation));}
};





class PythonQtShell_SoGLUpdateAreaElement : public SoGLUpdateAreaElement
{
public:
    PythonQtShell_SoGLUpdateAreaElement():SoGLUpdateAreaElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoGLUpdateAreaElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoGLUpdateAreaElement : public SoGLUpdateAreaElement
{ public:
inline SoElement*  py_q_copyMatchInfo() const { return SoGLUpdateAreaElement::copyMatchInfo(); }
inline void py_q_init(SoState*  state) { SoGLUpdateAreaElement::init(state); }
inline bool  py_q_matches(const SoElement*  elt) const { return SoGLUpdateAreaElement::matches(elt); }
inline void py_q_pop(SoState*  state, const SoElement*  prevTopElement) { SoGLUpdateAreaElement::pop(state, prevTopElement); }
inline void py_q_push(SoState*  state) { SoGLUpdateAreaElement::push(state); }
};

class PythonQtWrapper_SoGLUpdateAreaElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoGLUpdateAreaElement* new_SoGLUpdateAreaElement();
   SoElement*  py_q_copyMatchInfo(SoGLUpdateAreaElement* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoGLUpdateAreaElement*)theWrappedObject)->py_q_copyMatchInfo());}
   bool  static_SoGLUpdateAreaElement_get(SoState*  state, SbVec2f&  origin, SbVec2f&  size);
   int  static_SoGLUpdateAreaElement_getClassStackIndex();
   SoType  static_SoGLUpdateAreaElement_getClassTypeId();
   SbVec2f  static_SoGLUpdateAreaElement_getDefaultOrigin();
   SbVec2f  static_SoGLUpdateAreaElement_getDefaultSize();
   void py_q_init(SoGLUpdateAreaElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLUpdateAreaElement*)theWrappedObject)->py_q_init(state));}
   bool  py_q_matches(SoGLUpdateAreaElement* theWrappedObject, const SoElement*  elt) const{  return (((PythonQtPublicPromoter_SoGLUpdateAreaElement*)theWrappedObject)->py_q_matches(elt));}
   void py_q_pop(SoGLUpdateAreaElement* theWrappedObject, SoState*  state, const SoElement*  prevTopElement){  (((PythonQtPublicPromoter_SoGLUpdateAreaElement*)theWrappedObject)->py_q_pop(state, prevTopElement));}
   void py_q_push(SoGLUpdateAreaElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLUpdateAreaElement*)theWrappedObject)->py_q_push(state));}
   void static_SoGLUpdateAreaElement_set(SoState*  state, const SbVec2f&  origin, const SbVec2f&  size);
};





class PythonQtShell_SoGLViewingMatrixElement : public SoGLViewingMatrixElement
{
public:
    PythonQtShell_SoGLViewingMatrixElement():SoGLViewingMatrixElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoGLViewingMatrixElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(const SbMatrix&  matrix) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoGLViewingMatrixElement : public SoGLViewingMatrixElement
{ public:
inline void promoted_setElt(const SbMatrix&  matrix) { this->setElt(matrix); }
inline void py_q_init(SoState*  state) { SoGLViewingMatrixElement::init(state); }
inline void py_q_pop(SoState*  state, const SoElement*  prevTopElement) { SoGLViewingMatrixElement::pop(state, prevTopElement); }
inline void py_q_push(SoState*  state) { SoGLViewingMatrixElement::push(state); }
inline void py_q_setElt(const SbMatrix&  matrix) { SoGLViewingMatrixElement::setElt(matrix); }
};

class PythonQtWrapper_SoGLViewingMatrixElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoGLViewingMatrixElement* new_SoGLViewingMatrixElement();
   int  static_SoGLViewingMatrixElement_getClassStackIndex();
   SoType  static_SoGLViewingMatrixElement_getClassTypeId();
   void py_q_init(SoGLViewingMatrixElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLViewingMatrixElement*)theWrappedObject)->py_q_init(state));}
   void py_q_pop(SoGLViewingMatrixElement* theWrappedObject, SoState*  state, const SoElement*  prevTopElement){  (((PythonQtPublicPromoter_SoGLViewingMatrixElement*)theWrappedObject)->py_q_pop(state, prevTopElement));}
   void py_q_push(SoGLViewingMatrixElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLViewingMatrixElement*)theWrappedObject)->py_q_push(state));}
   void py_q_setElt(SoGLViewingMatrixElement* theWrappedObject, const SbMatrix&  matrix){  (((PythonQtPublicPromoter_SoGLViewingMatrixElement*)theWrappedObject)->py_q_setElt(matrix));}
};





class PythonQtShell_SoGLViewportRegionElement : public SoGLViewportRegionElement
{
public:
    PythonQtShell_SoGLViewportRegionElement():SoGLViewportRegionElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoGLViewportRegionElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(const SbViewportRegion&  vpReg) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoGLViewportRegionElement : public SoGLViewportRegionElement
{ public:
inline void promoted_setElt(const SbViewportRegion&  vpReg) { this->setElt(vpReg); }
inline void py_q_init(SoState*  state) { SoGLViewportRegionElement::init(state); }
inline void py_q_pop(SoState*  state, const SoElement*  prevTopElement) { SoGLViewportRegionElement::pop(state, prevTopElement); }
inline void py_q_push(SoState*  state) { SoGLViewportRegionElement::push(state); }
inline void py_q_setElt(const SbViewportRegion&  vpReg) { SoGLViewportRegionElement::setElt(vpReg); }
};

class PythonQtWrapper_SoGLViewportRegionElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoGLViewportRegionElement* new_SoGLViewportRegionElement();
   int  static_SoGLViewportRegionElement_getClassStackIndex();
   SoType  static_SoGLViewportRegionElement_getClassTypeId();
   void py_q_init(SoGLViewportRegionElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLViewportRegionElement*)theWrappedObject)->py_q_init(state));}
   void py_q_pop(SoGLViewportRegionElement* theWrappedObject, SoState*  state, const SoElement*  prevTopElement){  (((PythonQtPublicPromoter_SoGLViewportRegionElement*)theWrappedObject)->py_q_pop(state, prevTopElement));}
   void py_q_push(SoGLViewportRegionElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoGLViewportRegionElement*)theWrappedObject)->py_q_push(state));}
   void py_q_setElt(SoGLViewportRegionElement* theWrappedObject, const SbViewportRegion&  vpReg){  (((PythonQtPublicPromoter_SoGLViewportRegionElement*)theWrappedObject)->py_q_setElt(vpReg));}
};





class PythonQtShell_SoInt32Element : public SoInt32Element
{
public:
    PythonQtShell_SoInt32Element():SoInt32Element(),_wrapper(nullptr) {};

   ~PythonQtShell_SoInt32Element() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(int  value) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoInt32Element : public SoInt32Element
{ public:
inline SoElement*  py_q_copyMatchInfo() const { return SoInt32Element::copyMatchInfo(); }
inline bool  py_q_matches(const SoElement*  elt) const { return SoInt32Element::matches(elt); }
inline void py_q_setElt(int  value) { SoInt32Element::setElt(value); }
};

class PythonQtWrapper_SoInt32Element : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoInt32Element* new_SoInt32Element();
   SoElement*  py_q_copyMatchInfo(SoInt32Element* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoInt32Element*)theWrappedObject)->py_q_copyMatchInfo());}
   int  static_SoInt32Element_get(int  stackIndex, SoState*  state);
   int  static_SoInt32Element_getClassStackIndex();
   SoType  static_SoInt32Element_getClassTypeId();
   bool  py_q_matches(SoInt32Element* theWrappedObject, const SoElement*  elt) const{  return (((PythonQtPublicPromoter_SoInt32Element*)theWrappedObject)->py_q_matches(elt));}
   void static_SoInt32Element_set(int  stackIndex, SoState*  state, int  value);
   void setElt(SoInt32Element* theWrappedObject, int  value);
   void py_q_setElt(SoInt32Element* theWrappedObject, int  value){  (((PythonQtPublicPromoter_SoInt32Element*)theWrappedObject)->py_q_setElt(value));}
};





class PythonQtShell_SoLazyElement : public SoLazyElement
{
public:
    PythonQtShell_SoLazyElement():SoLazyElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoLazyElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  arg__1) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void registerGetDependence(SoState*  arg__1, unsigned int  arg__2) override;
void registerRedundantSet(SoState*  arg__1, unsigned int  arg__2) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoLazyElement : public SoLazyElement
{ public:
static inline int  promoted_getNumPatterns() { return getNumPatterns(); }
inline void promoted_registerGetDependence(SoState*  arg__1, unsigned int  arg__2) { this->registerGetDependence(arg__1, arg__2); }
inline void promoted_registerRedundantSet(SoState*  arg__1, unsigned int  arg__2) { this->registerRedundantSet(arg__1, arg__2); }
inline SoElement*  py_q_copyMatchInfo() const { return SoLazyElement::copyMatchInfo(); }
inline void py_q_init(SoState*  state) { SoLazyElement::init(state); }
inline bool  py_q_matches(const SoElement*  arg__1) const { return SoLazyElement::matches(arg__1); }
inline void py_q_push(SoState*  state) { SoLazyElement::push(state); }
inline void py_q_registerGetDependence(SoState*  arg__1, unsigned int  arg__2) { SoLazyElement::registerGetDependence(arg__1, arg__2); }
inline void py_q_registerRedundantSet(SoState*  arg__1, unsigned int  arg__2) { SoLazyElement::registerRedundantSet(arg__1, arg__2); }
};

class PythonQtWrapper_SoLazyElement : public QObject
{ Q_OBJECT
public:
Q_ENUMS(LightModel VertexAttribs cases internalMasks masks )
enum LightModel{
  BASE_COLOR = SoLazyElement::BASE_COLOR,   PHONG = SoLazyElement::PHONG};
enum VertexAttribs{
  ATTRIB_VERTEX = SoLazyElement::ATTRIB_VERTEX,   ATTRIB_NORMAL = SoLazyElement::ATTRIB_NORMAL,   ATTRIB_COLOR = SoLazyElement::ATTRIB_COLOR,   ATTRIB_TEXCOORD = SoLazyElement::ATTRIB_TEXCOORD};
enum cases{
  LIGHT_MODEL_CASE = SoLazyElement::LIGHT_MODEL_CASE,   COLOR_MATERIAL_CASE = SoLazyElement::COLOR_MATERIAL_CASE,   DIFFUSE_CASE = SoLazyElement::DIFFUSE_CASE,   AMBIENT_CASE = SoLazyElement::AMBIENT_CASE,   EMISSIVE_CASE = SoLazyElement::EMISSIVE_CASE,   SPECULAR_CASE = SoLazyElement::SPECULAR_CASE,   SHININESS_CASE = SoLazyElement::SHININESS_CASE,   BLENDING_CASE = SoLazyElement::BLENDING_CASE,   TRANSPARENCY_CASE = SoLazyElement::TRANSPARENCY_CASE};
enum internalMasks{
  OTHER_COLOR_MASK = SoLazyElement::OTHER_COLOR_MASK,   ALL_COLOR_MASK = SoLazyElement::ALL_COLOR_MASK,   NO_COLOR_MASK = SoLazyElement::NO_COLOR_MASK,   ALL_BUT_DIFFUSE_MASK = SoLazyElement::ALL_BUT_DIFFUSE_MASK,   DIFFUSE_ONLY_MASK = SoLazyElement::DIFFUSE_ONLY_MASK};
enum masks{
  LIGHT_MODEL_MASK = SoLazyElement::LIGHT_MODEL_MASK,   COLOR_MATERIAL_MASK = SoLazyElement::COLOR_MATERIAL_MASK,   DIFFUSE_MASK = SoLazyElement::DIFFUSE_MASK,   AMBIENT_MASK = SoLazyElement::AMBIENT_MASK,   EMISSIVE_MASK = SoLazyElement::EMISSIVE_MASK,   SPECULAR_MASK = SoLazyElement::SPECULAR_MASK,   SHININESS_MASK = SoLazyElement::SHININESS_MASK,   TRANSPARENCY_MASK = SoLazyElement::TRANSPARENCY_MASK,   BLENDING_MASK = SoLazyElement::BLENDING_MASK,   ALL_MASK = SoLazyElement::ALL_MASK};
public Q_SLOTS:
SoLazyElement* new_SoLazyElement();
   SoElement*  py_q_copyMatchInfo(SoLazyElement* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoLazyElement*)theWrappedObject)->py_q_copyMatchInfo());}
   void static_SoLazyElement_drawArrays(SoState*  state, GLenum  mode, GLint  first, GLsizei  count);
   void static_SoLazyElement_drawElements(SoState*  state, GLenum  mode, GLsizei  count, GLenum  type, const GLvoid*  indices);
   const SbColor*  static_SoLazyElement_getAmbient(SoState*  arg__1);
   bool  static_SoLazyElement_getBlending(SoState*  arg__1);
   int  static_SoLazyElement_getClassStackIndex();
   SoType  static_SoLazyElement_getClassTypeId();
   bool  static_SoLazyElement_getColorMaterial(SoState*  arg__1);
   SbColor  static_SoLazyElement_getDefaultAmbient();
   SbColor  static_SoLazyElement_getDefaultDiffuse();
   SbColor  static_SoLazyElement_getDefaultEmissive();
   int  static_SoLazyElement_getDefaultLightModel();
   unsigned int  static_SoLazyElement_getDefaultPacked();
   float  static_SoLazyElement_getDefaultShininess();
   SbColor  static_SoLazyElement_getDefaultSpecular();
   float  static_SoLazyElement_getDefaultTransparency();
   const SbColor*  static_SoLazyElement_getDiffuse(SoState*  state, int  index);
   const SbColor*  getDiffusePointer(SoLazyElement* theWrappedObject) const;
   const SbColor*  static_SoLazyElement_getEmissive(SoState*  arg__1);
   SoLazyElement*  static_SoLazyElement_getInstance(SoState*  state);
   int  static_SoLazyElement_getLightModel(SoState*  arg__1);
   int  getNumDiffuse(SoLazyElement* theWrappedObject) const;
   int  static_SoLazyElement_getNumPatterns();
   int  getNumTransparencies(SoLazyElement* theWrappedObject) const;
   const unsigned int*  static_SoLazyElement_getPackedColors(SoState*  arg__1);
   const unsigned int*  getPackedPointer(SoLazyElement* theWrappedObject) const;
   float  static_SoLazyElement_getShininess(SoState*  arg__1);
   const SbColor*  static_SoLazyElement_getSpecular(SoState*  arg__1);
   float  static_SoLazyElement_getTransparency(SoState*  arg__1, int  index);
   const float*  getTransparencyPointer(SoLazyElement* theWrappedObject) const;
   SoLazyElement*  static_SoLazyElement_getWInstance(SoState*  state);
   void py_q_init(SoLazyElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoLazyElement*)theWrappedObject)->py_q_init(state));}
   bool  isPacked(SoLazyElement* theWrappedObject) const;
   bool  isTransparent(SoLazyElement* theWrappedObject) const;
   bool  py_q_matches(SoLazyElement* theWrappedObject, const SoElement*  arg__1) const{  return (((PythonQtPublicPromoter_SoLazyElement*)theWrappedObject)->py_q_matches(arg__1));}
   void py_q_push(SoLazyElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoLazyElement*)theWrappedObject)->py_q_push(state));}
   void registerGetDependence(SoLazyElement* theWrappedObject, SoState*  arg__1, unsigned int  arg__2);
   void py_q_registerGetDependence(SoLazyElement* theWrappedObject, SoState*  arg__1, unsigned int  arg__2){  (((PythonQtPublicPromoter_SoLazyElement*)theWrappedObject)->py_q_registerGetDependence(arg__1, arg__2));}
   void registerRedundantSet(SoLazyElement* theWrappedObject, SoState*  arg__1, unsigned int  arg__2);
   void py_q_registerRedundantSet(SoLazyElement* theWrappedObject, SoState*  arg__1, unsigned int  arg__2){  (((PythonQtPublicPromoter_SoLazyElement*)theWrappedObject)->py_q_registerRedundantSet(arg__1, arg__2));}
   void static_SoLazyElement_setAmbient(SoState*  state, const SbColor*  color);
   void static_SoLazyElement_setBlending(SoState*  state, bool  value);
   void static_SoLazyElement_setColorMaterial(SoState*  state, bool  value);
   void static_SoLazyElement_setEmissive(SoState*  state, const SbColor*  color);
   void static_SoLazyElement_setLightModel(SoState*  state, const int  model);
   void static_SoLazyElement_setOverrideBlending(SoState*  state, bool  flag);
   void static_SoLazyElement_setPacked(SoState*  state, SoNode*  node, int  numColors, const unsigned int*  colors);
   void static_SoLazyElement_setShininess(SoState*  state, float  value);
   void static_SoLazyElement_setSpecular(SoState*  state, const SbColor*  color);
   void static_SoLazyElement_setTransparencyType(SoState*  state, int  type);
   void static_SoLazyElement_setUseVertexAttributes(SoState*  state, bool  flag);
   bool  static_SoLazyElement_shouldUseVertexAttributes(SoState*  state);
};





class PythonQtShell_SoLightAttenuationElement : public SoLightAttenuationElement
{
public:
    PythonQtShell_SoLightAttenuationElement():SoLightAttenuationElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoLightAttenuationElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoLightAttenuationElement : public SoLightAttenuationElement
{ public:
inline SoElement*  py_q_copyMatchInfo() const { return SoLightAttenuationElement::copyMatchInfo(); }
inline void py_q_init(SoState*  state) { SoLightAttenuationElement::init(state); }
inline bool  py_q_matches(const SoElement*  elt) const { return SoLightAttenuationElement::matches(elt); }
};

class PythonQtWrapper_SoLightAttenuationElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoLightAttenuationElement* new_SoLightAttenuationElement();
   SoElement*  py_q_copyMatchInfo(SoLightAttenuationElement* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoLightAttenuationElement*)theWrappedObject)->py_q_copyMatchInfo());}
   const SbVec3f*  static_SoLightAttenuationElement_get(SoState*  state);
   int  static_SoLightAttenuationElement_getClassStackIndex();
   SoType  static_SoLightAttenuationElement_getClassTypeId();
   SbVec3f  static_SoLightAttenuationElement_getDefault();
   void py_q_init(SoLightAttenuationElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoLightAttenuationElement*)theWrappedObject)->py_q_init(state));}
   bool  py_q_matches(SoLightAttenuationElement* theWrappedObject, const SoElement*  elt) const{  return (((PythonQtPublicPromoter_SoLightAttenuationElement*)theWrappedObject)->py_q_matches(elt));}
   void static_SoLightAttenuationElement_set(SoState*  state, SoNode*  node, const SbVec3f&  attenuation);
};





class PythonQtShell_SoLinePatternElement : public SoLinePatternElement
{
public:
    PythonQtShell_SoLinePatternElement():SoLinePatternElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoLinePatternElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(int  value) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoLinePatternElement : public SoLinePatternElement
{ public:
inline void py_q_init(SoState*  state) { SoLinePatternElement::init(state); }
};

class PythonQtWrapper_SoLinePatternElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoLinePatternElement* new_SoLinePatternElement();
   int  static_SoLinePatternElement_getClassStackIndex();
   SoType  static_SoLinePatternElement_getClassTypeId();
   void py_q_init(SoLinePatternElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoLinePatternElement*)theWrappedObject)->py_q_init(state));}
};





class PythonQtShell_SoLineWidthElement : public SoLineWidthElement
{
public:
    PythonQtShell_SoLineWidthElement():SoLineWidthElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoLineWidthElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(float  value) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoLineWidthElement : public SoLineWidthElement
{ public:
inline void py_q_init(SoState*  state) { SoLineWidthElement::init(state); }
};

class PythonQtWrapper_SoLineWidthElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoLineWidthElement* new_SoLineWidthElement();
   float  static_SoLineWidthElement_get(SoState*  state);
   int  static_SoLineWidthElement_getClassStackIndex();
   SoType  static_SoLineWidthElement_getClassTypeId();
   float  static_SoLineWidthElement_getDefault();
   void py_q_init(SoLineWidthElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoLineWidthElement*)theWrappedObject)->py_q_init(state));}
   void static_SoLineWidthElement_set(SoState*  state, float  width);
};





class PythonQtShell_SoLocalBBoxMatrixElement : public SoLocalBBoxMatrixElement
{
public:
    PythonQtShell_SoLocalBBoxMatrixElement():SoLocalBBoxMatrixElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoLocalBBoxMatrixElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoLocalBBoxMatrixElement : public SoLocalBBoxMatrixElement
{ public:
inline SoElement*  py_q_copyMatchInfo() const { return SoLocalBBoxMatrixElement::copyMatchInfo(); }
inline void py_q_init(SoState*  state) { SoLocalBBoxMatrixElement::init(state); }
inline bool  py_q_matches(const SoElement*  elt) const { return SoLocalBBoxMatrixElement::matches(elt); }
inline void py_q_push(SoState*  state) { SoLocalBBoxMatrixElement::push(state); }
};

class PythonQtWrapper_SoLocalBBoxMatrixElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoLocalBBoxMatrixElement* new_SoLocalBBoxMatrixElement();
   SoElement*  py_q_copyMatchInfo(SoLocalBBoxMatrixElement* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoLocalBBoxMatrixElement*)theWrappedObject)->py_q_copyMatchInfo());}
   const SbMatrix*  static_SoLocalBBoxMatrixElement_get(SoState*  state);
   int  static_SoLocalBBoxMatrixElement_getClassStackIndex();
   SoType  static_SoLocalBBoxMatrixElement_getClassTypeId();
   void py_q_init(SoLocalBBoxMatrixElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoLocalBBoxMatrixElement*)theWrappedObject)->py_q_init(state));}
   void static_SoLocalBBoxMatrixElement_makeIdentity(SoState*  state);
   bool  py_q_matches(SoLocalBBoxMatrixElement* theWrappedObject, const SoElement*  elt) const{  return (((PythonQtPublicPromoter_SoLocalBBoxMatrixElement*)theWrappedObject)->py_q_matches(elt));}
   void static_SoLocalBBoxMatrixElement_mult(SoState*  state, const SbMatrix&  matrix);
   void static_SoLocalBBoxMatrixElement_popMatrix(SoState*  state, const SbMatrix&  m);
   void py_q_push(SoLocalBBoxMatrixElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoLocalBBoxMatrixElement*)theWrappedObject)->py_q_push(state));}
   SbMatrix  static_SoLocalBBoxMatrixElement_pushMatrix(SoState*  state);
   void static_SoLocalBBoxMatrixElement_resetAll(SoState*  state);
   void static_SoLocalBBoxMatrixElement_rotateBy(SoState*  state, const SbRotation&  rotation);
   void static_SoLocalBBoxMatrixElement_scaleBy(SoState*  state, const SbVec3f&  scaleFactor);
   void static_SoLocalBBoxMatrixElement_set(SoState*  state, const SbMatrix&  matrix);
   void static_SoLocalBBoxMatrixElement_translateBy(SoState*  state, const SbVec3f&  translation);
};





class PythonQtShell_SoMaterialBindingElement : public SoMaterialBindingElement
{
public:
    PythonQtShell_SoMaterialBindingElement():SoMaterialBindingElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoMaterialBindingElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(int  value) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoMaterialBindingElement : public SoMaterialBindingElement
{ public:
inline void py_q_init(SoState*  state) { SoMaterialBindingElement::init(state); }
};

class PythonQtWrapper_SoMaterialBindingElement : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Binding )
enum Binding{
  OVERALL = SoMaterialBindingElement::OVERALL,   PER_PART = SoMaterialBindingElement::PER_PART,   PER_PART_INDEXED = SoMaterialBindingElement::PER_PART_INDEXED,   PER_FACE = SoMaterialBindingElement::PER_FACE,   PER_FACE_INDEXED = SoMaterialBindingElement::PER_FACE_INDEXED,   PER_VERTEX = SoMaterialBindingElement::PER_VERTEX,   PER_VERTEX_INDEXED = SoMaterialBindingElement::PER_VERTEX_INDEXED};
public Q_SLOTS:
SoMaterialBindingElement* new_SoMaterialBindingElement();
   SoMaterialBindingElement::Binding  static_SoMaterialBindingElement_get(SoState*  state);
   int  static_SoMaterialBindingElement_getClassStackIndex();
   SoType  static_SoMaterialBindingElement_getClassTypeId();
   SoMaterialBindingElement::Binding  static_SoMaterialBindingElement_getDefault();
   void py_q_init(SoMaterialBindingElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoMaterialBindingElement*)theWrappedObject)->py_q_init(state));}
   void static_SoMaterialBindingElement_set(SoState*  state, SoMaterialBindingElement::Binding  binding);
};





class PythonQtShell_SoModelMatrixElement : public SoModelMatrixElement
{
public:
    PythonQtShell_SoModelMatrixElement():SoModelMatrixElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoModelMatrixElement() override;

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

class PythonQtPublicPromoter_SoModelMatrixElement : public SoModelMatrixElement
{ public:
inline void promoted_makeEltIdentity() { this->makeEltIdentity(); }
inline void promoted_multElt(const SbMatrix&  matrix) { this->multElt(matrix); }
inline void promoted_popMatrixElt(const SbMatrix&  m) { this->popMatrixElt(m); }
inline SbMatrix  promoted_pushMatrixElt() { return this->pushMatrixElt(); }
inline void promoted_rotateEltBy(const SbRotation&  translation) { this->rotateEltBy(translation); }
inline void promoted_scaleEltBy(const SbVec3f&  scaleFactor) { this->scaleEltBy(scaleFactor); }
inline void promoted_setElt(const SbMatrix&  matrix) { this->setElt(matrix); }
inline void promoted_translateEltBy(const SbVec3f&  translation) { this->translateEltBy(translation); }
inline void py_q_init(SoState*  state) { SoModelMatrixElement::init(state); }
inline void py_q_makeEltIdentity() { SoModelMatrixElement::makeEltIdentity(); }
inline bool  py_q_matches(const SoElement*  elt) const { return SoModelMatrixElement::matches(elt); }
inline void py_q_multElt(const SbMatrix&  matrix) { SoModelMatrixElement::multElt(matrix); }
inline void py_q_popMatrixElt(const SbMatrix&  m) { SoModelMatrixElement::popMatrixElt(m); }
inline void py_q_push(SoState*  state) { SoModelMatrixElement::push(state); }
inline SbMatrix  py_q_pushMatrixElt() { return SoModelMatrixElement::pushMatrixElt(); }
inline void py_q_rotateEltBy(const SbRotation&  translation) { SoModelMatrixElement::rotateEltBy(translation); }
inline void py_q_scaleEltBy(const SbVec3f&  scaleFactor) { SoModelMatrixElement::scaleEltBy(scaleFactor); }
inline void py_q_setElt(const SbMatrix&  matrix) { SoModelMatrixElement::setElt(matrix); }
inline void py_q_translateEltBy(const SbVec3f&  translation) { SoModelMatrixElement::translateEltBy(translation); }
};

class PythonQtWrapper_SoModelMatrixElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoModelMatrixElement* new_SoModelMatrixElement();
   const SbMatrix*  static_SoModelMatrixElement_get(SoState*  state);
   const SbMatrix*  static_SoModelMatrixElement_get(SoState*  state, bool&  isIdent);
   int  static_SoModelMatrixElement_getClassStackIndex();
   SoType  static_SoModelMatrixElement_getClassTypeId();
   const SbMatrix*  static_SoModelMatrixElement_getCombinedCullMatrix(SoState*  state);
   void py_q_init(SoModelMatrixElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoModelMatrixElement*)theWrappedObject)->py_q_init(state));}
   void makeEltIdentity(SoModelMatrixElement* theWrappedObject);
   void py_q_makeEltIdentity(SoModelMatrixElement* theWrappedObject){  (((PythonQtPublicPromoter_SoModelMatrixElement*)theWrappedObject)->py_q_makeEltIdentity());}
   void static_SoModelMatrixElement_makeIdentity(SoState*  state, SoNode*  node);
   bool  py_q_matches(SoModelMatrixElement* theWrappedObject, const SoElement*  elt) const{  return (((PythonQtPublicPromoter_SoModelMatrixElement*)theWrappedObject)->py_q_matches(elt));}
   void static_SoModelMatrixElement_mult(SoState*  state, SoNode*  node, const SbMatrix&  matrix);
   void multElt(SoModelMatrixElement* theWrappedObject, const SbMatrix&  matrix);
   void py_q_multElt(SoModelMatrixElement* theWrappedObject, const SbMatrix&  matrix){  (((PythonQtPublicPromoter_SoModelMatrixElement*)theWrappedObject)->py_q_multElt(matrix));}
   void static_SoModelMatrixElement_popMatrix(SoState*  state, const SbMatrix&  m);
   void popMatrixElt(SoModelMatrixElement* theWrappedObject, const SbMatrix&  m);
   void py_q_popMatrixElt(SoModelMatrixElement* theWrappedObject, const SbMatrix&  m){  (((PythonQtPublicPromoter_SoModelMatrixElement*)theWrappedObject)->py_q_popMatrixElt(m));}
   void py_q_push(SoModelMatrixElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoModelMatrixElement*)theWrappedObject)->py_q_push(state));}
   SbMatrix  static_SoModelMatrixElement_pushMatrix(SoState*  state);
   SbMatrix  pushMatrixElt(SoModelMatrixElement* theWrappedObject);
   SbMatrix  py_q_pushMatrixElt(SoModelMatrixElement* theWrappedObject){  return (((PythonQtPublicPromoter_SoModelMatrixElement*)theWrappedObject)->py_q_pushMatrixElt());}
   void static_SoModelMatrixElement_rotateBy(SoState*  state, SoNode*  node, const SbRotation&  rotation);
   void rotateEltBy(SoModelMatrixElement* theWrappedObject, const SbRotation&  translation);
   void py_q_rotateEltBy(SoModelMatrixElement* theWrappedObject, const SbRotation&  translation){  (((PythonQtPublicPromoter_SoModelMatrixElement*)theWrappedObject)->py_q_rotateEltBy(translation));}
   void static_SoModelMatrixElement_scaleBy(SoState*  state, SoNode*  node, const SbVec3f&  scaleFactor);
   void scaleEltBy(SoModelMatrixElement* theWrappedObject, const SbVec3f&  scaleFactor);
   void py_q_scaleEltBy(SoModelMatrixElement* theWrappedObject, const SbVec3f&  scaleFactor){  (((PythonQtPublicPromoter_SoModelMatrixElement*)theWrappedObject)->py_q_scaleEltBy(scaleFactor));}
   void static_SoModelMatrixElement_set(SoState*  state, SoNode*  node, const SbMatrix&  matrix);
   void static_SoModelMatrixElement_setCullMatrix(SoState*  state, SoNode*  node, const SbMatrix&  matrix);
   void setElt(SoModelMatrixElement* theWrappedObject, const SbMatrix&  matrix);
   void py_q_setElt(SoModelMatrixElement* theWrappedObject, const SbMatrix&  matrix){  (((PythonQtPublicPromoter_SoModelMatrixElement*)theWrappedObject)->py_q_setElt(matrix));}
   void static_SoModelMatrixElement_translateBy(SoState*  state, SoNode*  node, const SbVec3f&  translation);
   void translateEltBy(SoModelMatrixElement* theWrappedObject, const SbVec3f&  translation);
   void py_q_translateEltBy(SoModelMatrixElement* theWrappedObject, const SbVec3f&  translation){  (((PythonQtPublicPromoter_SoModelMatrixElement*)theWrappedObject)->py_q_translateEltBy(translation));}
};





class PythonQtShell_SoNormalBindingElement : public SoNormalBindingElement
{
public:
    PythonQtShell_SoNormalBindingElement():SoNormalBindingElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoNormalBindingElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(int  value) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoNormalBindingElement : public SoNormalBindingElement
{ public:
inline void py_q_init(SoState*  state) { SoNormalBindingElement::init(state); }
};

class PythonQtWrapper_SoNormalBindingElement : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Binding )
enum Binding{
  OVERALL = SoNormalBindingElement::OVERALL,   PER_PART = SoNormalBindingElement::PER_PART,   PER_PART_INDEXED = SoNormalBindingElement::PER_PART_INDEXED,   PER_FACE = SoNormalBindingElement::PER_FACE,   PER_FACE_INDEXED = SoNormalBindingElement::PER_FACE_INDEXED,   PER_VERTEX = SoNormalBindingElement::PER_VERTEX,   PER_VERTEX_INDEXED = SoNormalBindingElement::PER_VERTEX_INDEXED};
public Q_SLOTS:
SoNormalBindingElement* new_SoNormalBindingElement();
   SoNormalBindingElement::Binding  static_SoNormalBindingElement_get(SoState*  state);
   int  static_SoNormalBindingElement_getClassStackIndex();
   SoType  static_SoNormalBindingElement_getClassTypeId();
   SoNormalBindingElement::Binding  static_SoNormalBindingElement_getDefault();
   void py_q_init(SoNormalBindingElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoNormalBindingElement*)theWrappedObject)->py_q_init(state));}
   void static_SoNormalBindingElement_set(SoState*  state, SoNormalBindingElement::Binding  binding);
};





class PythonQtShell_SoNormalElement : public SoNormalElement
{
public:
    PythonQtShell_SoNormalElement():SoNormalElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoNormalElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoNormalElement : public SoNormalElement
{ public:
inline void py_q_init(SoState*  state) { SoNormalElement::init(state); }
};

class PythonQtWrapper_SoNormalElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoNormalElement* new_SoNormalElement();
   const SbVec3f*  get(SoNormalElement* theWrappedObject, int  index) const;
   int  static_SoNormalElement_getClassStackIndex();
   SoType  static_SoNormalElement_getClassTypeId();
   const SoNormalElement*  static_SoNormalElement_getInstance(SoState*  state);
   int  getNum(SoNormalElement* theWrappedObject) const;
   void py_q_init(SoNormalElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoNormalElement*)theWrappedObject)->py_q_init(state));}
   void static_SoNormalElement_set(SoState*  state, SoNode*  node, int  numNormals, const SbVec3f*  normals);
};





class PythonQtShell_SoOverrideElement : public SoOverrideElement
{
public:
    PythonQtShell_SoOverrideElement():SoOverrideElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoOverrideElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoOverrideElement : public SoOverrideElement
{ public:
inline SoElement*  py_q_copyMatchInfo() const { return SoOverrideElement::copyMatchInfo(); }
inline void py_q_init(SoState*  state) { SoOverrideElement::init(state); }
inline bool  py_q_matches(const SoElement*  elt) const { return SoOverrideElement::matches(elt); }
inline void py_q_push(SoState*  state) { SoOverrideElement::push(state); }
};

class PythonQtWrapper_SoOverrideElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoOverrideElement* new_SoOverrideElement();
void delete_SoOverrideElement(SoOverrideElement* obj) { delete obj; }
   SoElement*  py_q_copyMatchInfo(SoOverrideElement* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoOverrideElement*)theWrappedObject)->py_q_copyMatchInfo());}
   bool  static_SoOverrideElement_getAmbientColorOverride(SoState*  state);
   int  static_SoOverrideElement_getClassStackIndex();
   SoType  static_SoOverrideElement_getClassTypeId();
   bool  static_SoOverrideElement_getComplexityOverride(SoState*  state);
   bool  static_SoOverrideElement_getComplexityTypeOverride(SoState*  state);
   bool  static_SoOverrideElement_getCreaseAngleOverride(SoState*  state);
   bool  static_SoOverrideElement_getDiffuseColorOverride(SoState*  state);
   bool  static_SoOverrideElement_getDrawStyleOverride(SoState*  state);
   bool  static_SoOverrideElement_getEmissiveColorOverride(SoState*  state);
   bool  static_SoOverrideElement_getFontNameOverride(SoState*  state);
   bool  static_SoOverrideElement_getFontSizeOverride(SoState*  state);
   bool  static_SoOverrideElement_getLightModelOverride(SoState*  state);
   bool  static_SoOverrideElement_getLinePatternOverride(SoState*  state);
   bool  static_SoOverrideElement_getLineWidthOverride(SoState*  state);
   bool  static_SoOverrideElement_getMaterialBindingOverride(SoState*  state);
   bool  static_SoOverrideElement_getPickStyleOverride(SoState*  state);
   bool  static_SoOverrideElement_getPointSizeOverride(SoState*  state);
   bool  static_SoOverrideElement_getPolygonOffsetOverride(SoState*  state);
   bool  static_SoOverrideElement_getShapeHintsOverride(SoState*  state);
   bool  static_SoOverrideElement_getShininessOverride(SoState*  state);
   bool  static_SoOverrideElement_getSpecularColorOverride(SoState*  state);
   bool  static_SoOverrideElement_getTransparencyOverride(SoState*  state);
   void py_q_init(SoOverrideElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoOverrideElement*)theWrappedObject)->py_q_init(state));}
   bool  py_q_matches(SoOverrideElement* theWrappedObject, const SoElement*  elt) const{  return (((PythonQtPublicPromoter_SoOverrideElement*)theWrappedObject)->py_q_matches(elt));}
   void py_q_push(SoOverrideElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoOverrideElement*)theWrappedObject)->py_q_push(state));}
   void static_SoOverrideElement_setAmbientColorOverride(SoState*  state, SoNode*  arg__2, bool  override);
   void static_SoOverrideElement_setComplexityOverride(SoState*  state, SoNode*  arg__2, bool  override);
   void static_SoOverrideElement_setComplexityTypeOverride(SoState*  state, SoNode*  arg__2, bool  override);
   void static_SoOverrideElement_setCreaseAngleOverride(SoState*  state, SoNode*  arg__2, bool  override);
   void static_SoOverrideElement_setDiffuseColorOverride(SoState*  state, SoNode*  arg__2, bool  override);
   void static_SoOverrideElement_setDrawStyleOverride(SoState*  state, SoNode*  arg__2, bool  override);
   void static_SoOverrideElement_setEmissiveColorOverride(SoState*  state, SoNode*  arg__2, bool  override);
   void static_SoOverrideElement_setFontNameOverride(SoState*  state, SoNode*  arg__2, bool  override);
   void static_SoOverrideElement_setFontSizeOverride(SoState*  state, SoNode*  arg__2, bool  override);
   void static_SoOverrideElement_setLightModelOverride(SoState*  state, SoNode*  arg__2, bool  override);
   void static_SoOverrideElement_setLinePatternOverride(SoState*  state, SoNode*  arg__2, bool  override);
   void static_SoOverrideElement_setLineWidthOverride(SoState*  state, SoNode*  arg__2, bool  override);
   void static_SoOverrideElement_setMaterialBindingOverride(SoState*  state, SoNode*  arg__2, bool  override);
   void static_SoOverrideElement_setPickStyleOverride(SoState*  state, SoNode*  arg__2, bool  override);
   void static_SoOverrideElement_setPointSizeOverride(SoState*  state, SoNode*  arg__2, bool  override);
   void static_SoOverrideElement_setPolygonOffsetOverride(SoState*  state, SoNode*  arg__2, bool  override);
   void static_SoOverrideElement_setShapeHintsOverride(SoState*  state, SoNode*  arg__2, bool  override);
   void static_SoOverrideElement_setShininessOverride(SoState*  state, SoNode*  arg__2, bool  override);
   void static_SoOverrideElement_setSpecularColorOverride(SoState*  state, SoNode*  arg__2, bool  override);
   void static_SoOverrideElement_setTransparencyOverride(SoState*  state, SoNode*  arg__2, bool  override);
};





class PythonQtShell_SoPickRayElement : public SoPickRayElement
{
public:
    PythonQtShell_SoPickRayElement():SoPickRayElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoPickRayElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoPickRayElement : public SoPickRayElement
{ public:
inline SoElement*  py_q_copyMatchInfo() const { return SoPickRayElement::copyMatchInfo(); }
inline void py_q_init(SoState*  state) { SoPickRayElement::init(state); }
inline bool  py_q_matches(const SoElement*  elt) const { return SoPickRayElement::matches(elt); }
};

class PythonQtWrapper_SoPickRayElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoPickRayElement* new_SoPickRayElement();
   SoElement*  py_q_copyMatchInfo(SoPickRayElement* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoPickRayElement*)theWrappedObject)->py_q_copyMatchInfo());}
   const SbViewVolume*  static_SoPickRayElement_get(SoState*  state);
   int  static_SoPickRayElement_getClassStackIndex();
   SoType  static_SoPickRayElement_getClassTypeId();
   void py_q_init(SoPickRayElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoPickRayElement*)theWrappedObject)->py_q_init(state));}
   bool  py_q_matches(SoPickRayElement* theWrappedObject, const SoElement*  elt) const{  return (((PythonQtPublicPromoter_SoPickRayElement*)theWrappedObject)->py_q_matches(elt));}
   void static_SoPickRayElement_set(SoState*  state, const SbViewVolume&  volume);
};





class PythonQtShell_SoPickStyleElement : public SoPickStyleElement
{
public:
    PythonQtShell_SoPickStyleElement():SoPickStyleElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoPickStyleElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(int  value) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoPickStyleElement : public SoPickStyleElement
{ public:
inline void py_q_init(SoState*  state) { SoPickStyleElement::init(state); }
};

class PythonQtWrapper_SoPickStyleElement : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Style )
enum Style{
  SHAPE = SoPickStyleElement::SHAPE,   BOUNDING_BOX = SoPickStyleElement::BOUNDING_BOX,   UNPICKABLE = SoPickStyleElement::UNPICKABLE};
public Q_SLOTS:
SoPickStyleElement* new_SoPickStyleElement();
   SoPickStyleElement::Style  static_SoPickStyleElement_get(SoState*  state);
   int  static_SoPickStyleElement_getClassStackIndex();
   SoType  static_SoPickStyleElement_getClassTypeId();
   SoPickStyleElement::Style  static_SoPickStyleElement_getDefault();
   void py_q_init(SoPickStyleElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoPickStyleElement*)theWrappedObject)->py_q_init(state));}
   void static_SoPickStyleElement_set(SoState*  state, SoPickStyleElement::Style  style);
};





class PythonQtShell_SoPointSizeElement : public SoPointSizeElement
{
public:
    PythonQtShell_SoPointSizeElement():SoPointSizeElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoPointSizeElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(float  value) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoPointSizeElement : public SoPointSizeElement
{ public:
inline void py_q_init(SoState*  state) { SoPointSizeElement::init(state); }
};

class PythonQtWrapper_SoPointSizeElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoPointSizeElement* new_SoPointSizeElement();
   float  static_SoPointSizeElement_get(SoState*  state);
   int  static_SoPointSizeElement_getClassStackIndex();
   SoType  static_SoPointSizeElement_getClassTypeId();
   float  static_SoPointSizeElement_getDefault();
   void py_q_init(SoPointSizeElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoPointSizeElement*)theWrappedObject)->py_q_init(state));}
   void static_SoPointSizeElement_set(SoState*  state, float  size);
};





class PythonQtShell_SoProfileCoordinateElement : public SoProfileCoordinateElement
{
public:
    PythonQtShell_SoProfileCoordinateElement():SoProfileCoordinateElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoProfileCoordinateElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoProfileCoordinateElement : public SoProfileCoordinateElement
{ public:
inline void py_q_init(SoState*  state) { SoProfileCoordinateElement::init(state); }
};

class PythonQtWrapper_SoProfileCoordinateElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoProfileCoordinateElement* new_SoProfileCoordinateElement();
   const SbVec2f*  get2(SoProfileCoordinateElement* theWrappedObject, int  index) const;
   const SbVec3f*  get3(SoProfileCoordinateElement* theWrappedObject, int  index) const;
   int  static_SoProfileCoordinateElement_getClassStackIndex();
   SoType  static_SoProfileCoordinateElement_getClassTypeId();
   SbVec2f  static_SoProfileCoordinateElement_getDefault2();
   SbVec3f  static_SoProfileCoordinateElement_getDefault3();
   const SoProfileCoordinateElement*  static_SoProfileCoordinateElement_getInstance(SoState*  state);
   int  getNum(SoProfileCoordinateElement* theWrappedObject) const;
   void py_q_init(SoProfileCoordinateElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoProfileCoordinateElement*)theWrappedObject)->py_q_init(state));}
   bool  is2D(SoProfileCoordinateElement* theWrappedObject) const;
   void static_SoProfileCoordinateElement_set2(SoState*  state, SoNode*  node, int  numCoords, const SbVec2f*  coords);
   void static_SoProfileCoordinateElement_set3(SoState*  state, SoNode*  node, int  numCoords, const SbVec3f*  coords);
};





class PythonQtShell_SoProfileElement : public SoProfileElement
{
public:
    PythonQtShell_SoProfileElement():SoProfileElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoProfileElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoProfileElement : public SoProfileElement
{ public:
inline void py_q_init(SoState*  state) { SoProfileElement::init(state); }
inline void py_q_push(SoState*  state) { SoProfileElement::push(state); }
};

class PythonQtWrapper_SoProfileElement : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Profile )
enum Profile{
  START_FIRST = SoProfileElement::START_FIRST,   START_NEW = SoProfileElement::START_NEW,   ADD_TO_CURRENT = SoProfileElement::ADD_TO_CURRENT};
public Q_SLOTS:
SoProfileElement* new_SoProfileElement();
   void static_SoProfileElement_add(SoState*  state, SoProfile*  profile);
   int  static_SoProfileElement_getClassStackIndex();
   SoType  static_SoProfileElement_getClassTypeId();
   void py_q_init(SoProfileElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoProfileElement*)theWrappedObject)->py_q_init(state));}
   void py_q_push(SoProfileElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoProfileElement*)theWrappedObject)->py_q_push(state));}
};





class PythonQtShell_SoProjectionMatrixElement : public SoProjectionMatrixElement
{
public:
    PythonQtShell_SoProjectionMatrixElement():SoProjectionMatrixElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoProjectionMatrixElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(const SbMatrix&  matrix) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoProjectionMatrixElement : public SoProjectionMatrixElement
{ public:
inline void promoted_setElt(const SbMatrix&  matrix) { this->setElt(matrix); }
inline void py_q_init(SoState*  state) { SoProjectionMatrixElement::init(state); }
inline void py_q_setElt(const SbMatrix&  matrix) { SoProjectionMatrixElement::setElt(matrix); }
};

class PythonQtWrapper_SoProjectionMatrixElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoProjectionMatrixElement* new_SoProjectionMatrixElement();
   const SbMatrix*  static_SoProjectionMatrixElement_get(SoState*  state);
   int  static_SoProjectionMatrixElement_getClassStackIndex();
   SoType  static_SoProjectionMatrixElement_getClassTypeId();
   void py_q_init(SoProjectionMatrixElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoProjectionMatrixElement*)theWrappedObject)->py_q_init(state));}
   void static_SoProjectionMatrixElement_set(SoState*  state, SoNode*  node, const SbMatrix&  matrix);
   void setElt(SoProjectionMatrixElement* theWrappedObject, const SbMatrix&  matrix);
   void py_q_setElt(SoProjectionMatrixElement* theWrappedObject, const SbMatrix&  matrix){  (((PythonQtPublicPromoter_SoProjectionMatrixElement*)theWrappedObject)->py_q_setElt(matrix));}
};





class PythonQtShell_SoReplacedElement : public SoReplacedElement
{
public:
    PythonQtShell_SoReplacedElement():SoReplacedElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoReplacedElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoReplacedElement : public SoReplacedElement
{ public:
static inline SoElement*  promoted_getElement(SoState*  state, int  stackIndex, SoNode*  node) { return getElement(state, stackIndex, node); }
inline SoElement*  py_q_copyMatchInfo() const { return SoReplacedElement::copyMatchInfo(); }
inline void py_q_init(SoState*  state) { SoReplacedElement::init(state); }
inline bool  py_q_matches(const SoElement*  elt) const { return SoReplacedElement::matches(elt); }
};

class PythonQtWrapper_SoReplacedElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoReplacedElement* new_SoReplacedElement();
   SoElement*  py_q_copyMatchInfo(SoReplacedElement* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoReplacedElement*)theWrappedObject)->py_q_copyMatchInfo());}
   int  static_SoReplacedElement_getClassStackIndex();
   SoType  static_SoReplacedElement_getClassTypeId();
   SoElement*  static_SoReplacedElement_getElement(SoState*  state, int  stackIndex, SoNode*  node);
   void py_q_init(SoReplacedElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoReplacedElement*)theWrappedObject)->py_q_init(state));}
   bool  py_q_matches(SoReplacedElement* theWrappedObject, const SoElement*  elt) const{  return (((PythonQtPublicPromoter_SoReplacedElement*)theWrappedObject)->py_q_matches(elt));}
};





class PythonQtShell_SoShapeHintsElement : public SoShapeHintsElement
{
public:
    PythonQtShell_SoShapeHintsElement():SoShapeHintsElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoShapeHintsElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(SoShapeHintsElement::VertexOrdering  vertexOrdering, SoShapeHintsElement::ShapeType  shapeType, SoShapeHintsElement::FaceType  faceType) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoShapeHintsElement : public SoShapeHintsElement
{ public:
inline void promoted_setElt(SoShapeHintsElement::VertexOrdering  vertexOrdering, SoShapeHintsElement::ShapeType  shapeType, SoShapeHintsElement::FaceType  faceType) { this->setElt(vertexOrdering, shapeType, faceType); }
inline SoElement*  py_q_copyMatchInfo() const { return SoShapeHintsElement::copyMatchInfo(); }
inline void py_q_init(SoState*  state) { SoShapeHintsElement::init(state); }
inline bool  py_q_matches(const SoElement*  elt) const { return SoShapeHintsElement::matches(elt); }
inline void py_q_push(SoState*  state) { SoShapeHintsElement::push(state); }
inline void py_q_setElt(SoShapeHintsElement::VertexOrdering  vertexOrdering, SoShapeHintsElement::ShapeType  shapeType, SoShapeHintsElement::FaceType  faceType) { SoShapeHintsElement::setElt(vertexOrdering, shapeType, faceType); }
};

class PythonQtWrapper_SoShapeHintsElement : public QObject
{ Q_OBJECT
public:
Q_ENUMS(FaceType ShapeType VertexOrdering )
enum FaceType{
  UNKNOWN_FACE_TYPE = SoShapeHintsElement::UNKNOWN_FACE_TYPE,   CONVEX = SoShapeHintsElement::CONVEX,   FACE_TYPE_AS_IS = SoShapeHintsElement::FACE_TYPE_AS_IS};
enum ShapeType{
  UNKNOWN_SHAPE_TYPE = SoShapeHintsElement::UNKNOWN_SHAPE_TYPE,   SOLID = SoShapeHintsElement::SOLID,   SHAPE_TYPE_AS_IS = SoShapeHintsElement::SHAPE_TYPE_AS_IS};
enum VertexOrdering{
  UNKNOWN_ORDERING = SoShapeHintsElement::UNKNOWN_ORDERING,   CLOCKWISE = SoShapeHintsElement::CLOCKWISE,   COUNTERCLOCKWISE = SoShapeHintsElement::COUNTERCLOCKWISE,   ORDERING_AS_IS = SoShapeHintsElement::ORDERING_AS_IS};
public Q_SLOTS:
SoShapeHintsElement* new_SoShapeHintsElement();
   SoElement*  py_q_copyMatchInfo(SoShapeHintsElement* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoShapeHintsElement*)theWrappedObject)->py_q_copyMatchInfo());}
   void static_SoShapeHintsElement_get(SoState*  state, SoShapeHintsElement::VertexOrdering&  vertexOrdering, SoShapeHintsElement::ShapeType&  shapeType, SoShapeHintsElement::FaceType&  faceType);
   int  static_SoShapeHintsElement_getClassStackIndex();
   SoType  static_SoShapeHintsElement_getClassTypeId();
   SoShapeHintsElement::FaceType  static_SoShapeHintsElement_getDefaultFaceType();
   SoShapeHintsElement::ShapeType  static_SoShapeHintsElement_getDefaultShapeType();
   bool  static_SoShapeHintsElement_getDefaultVBOUsage();
   SoShapeHintsElement::VertexOrdering  static_SoShapeHintsElement_getDefaultVertexOrdering();
   void py_q_init(SoShapeHintsElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoShapeHintsElement*)theWrappedObject)->py_q_init(state));}
   bool  static_SoShapeHintsElement_isVBOUsed(SoState*  state);
   bool  py_q_matches(SoShapeHintsElement* theWrappedObject, const SoElement*  elt) const{  return (((PythonQtPublicPromoter_SoShapeHintsElement*)theWrappedObject)->py_q_matches(elt));}
   void py_q_push(SoShapeHintsElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoShapeHintsElement*)theWrappedObject)->py_q_push(state));}
   void static_SoShapeHintsElement_set(SoState*  state, SoShapeHintsElement::VertexOrdering  vertexOrdering, SoShapeHintsElement::ShapeType  shapeType, SoShapeHintsElement::FaceType  faceType);
   void static_SoShapeHintsElement_set(SoState*  state, bool  useVBO);
   void setElt(SoShapeHintsElement* theWrappedObject, SoShapeHintsElement::VertexOrdering  vertexOrdering, SoShapeHintsElement::ShapeType  shapeType, SoShapeHintsElement::FaceType  faceType);
   void py_q_setElt(SoShapeHintsElement* theWrappedObject, SoShapeHintsElement::VertexOrdering  vertexOrdering, SoShapeHintsElement::ShapeType  shapeType, SoShapeHintsElement::FaceType  faceType){  (((PythonQtPublicPromoter_SoShapeHintsElement*)theWrappedObject)->py_q_setElt(vertexOrdering, shapeType, faceType));}
};





class PythonQtShell_SoShapeStyleElement : public SoShapeStyleElement
{
public:
    PythonQtShell_SoShapeStyleElement():SoShapeStyleElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoShapeStyleElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoShapeStyleElement : public SoShapeStyleElement
{ public:
inline SoElement*  py_q_copyMatchInfo() const { return SoShapeStyleElement::copyMatchInfo(); }
inline void py_q_init(SoState*  state) { SoShapeStyleElement::init(state); }
inline bool  py_q_matches(const SoElement*  elt) const { return SoShapeStyleElement::matches(elt); }
inline void py_q_push(SoState*  state) { SoShapeStyleElement::push(state); }
};

class PythonQtWrapper_SoShapeStyleElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoShapeStyleElement* new_SoShapeStyleElement();
   SoElement*  py_q_copyMatchInfo(SoShapeStyleElement* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoShapeStyleElement*)theWrappedObject)->py_q_copyMatchInfo());}
   const SoShapeStyleElement*  static_SoShapeStyleElement_get(SoState*  state);
   int  static_SoShapeStyleElement_getClassStackIndex();
   SoType  static_SoShapeStyleElement_getClassTypeId();
   int  getRenderCaseMask(SoShapeStyleElement* theWrappedObject) const;
   void py_q_init(SoShapeStyleElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoShapeStyleElement*)theWrappedObject)->py_q_init(state));}
   bool  static_SoShapeStyleElement_isScreenDoor(SoState*  state);
   bool  isTextureFunction(SoShapeStyleElement* theWrappedObject) const;
   bool  py_q_matches(SoShapeStyleElement* theWrappedObject, const SoElement*  elt) const{  return (((PythonQtPublicPromoter_SoShapeStyleElement*)theWrappedObject)->py_q_matches(elt));}
   bool  mightNotRender(SoShapeStyleElement* theWrappedObject) const;
   bool  needNormals(SoShapeStyleElement* theWrappedObject) const;
   bool  needTexCoords(SoShapeStyleElement* theWrappedObject) const;
   void py_q_push(SoShapeStyleElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoShapeStyleElement*)theWrappedObject)->py_q_push(state));}
   void static_SoShapeStyleElement_setComplexityType(SoState*  state, int  value);
   void static_SoShapeStyleElement_setDrawStyle(SoState*  state, int  value);
   void static_SoShapeStyleElement_setLightModel(SoState*  state, int  value);
   void static_SoShapeStyleElement_setOverrides(SoState*  state, bool  value);
   void static_SoShapeStyleElement_setTextureEnabled(SoState*  state, bool  value);
   void static_SoShapeStyleElement_setTextureFunction(SoState*  state, bool  value);
   void static_SoShapeStyleElement_setTransparencyType(SoState*  state, int  value);
};





class PythonQtShell_SoSwitchElement : public SoSwitchElement
{
public:
    PythonQtShell_SoSwitchElement():SoSwitchElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoSwitchElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(int  value) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoSwitchElement : public SoSwitchElement
{ public:
inline void py_q_init(SoState*  state) { SoSwitchElement::init(state); }
};

class PythonQtWrapper_SoSwitchElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSwitchElement* new_SoSwitchElement();
   int  static_SoSwitchElement_get(SoState*  state);
   int  static_SoSwitchElement_getClassStackIndex();
   SoType  static_SoSwitchElement_getClassTypeId();
   int  static_SoSwitchElement_getDefault();
   void py_q_init(SoSwitchElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoSwitchElement*)theWrappedObject)->py_q_init(state));}
   void static_SoSwitchElement_set(SoState*  state, int  index);
};





class PythonQtShell_SoTextureCoordinateBindingElement : public SoTextureCoordinateBindingElement
{
public:
    PythonQtShell_SoTextureCoordinateBindingElement():SoTextureCoordinateBindingElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoTextureCoordinateBindingElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(int  value) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoTextureCoordinateBindingElement : public SoTextureCoordinateBindingElement
{ public:
inline void py_q_init(SoState*  state) { SoTextureCoordinateBindingElement::init(state); }
};

class PythonQtWrapper_SoTextureCoordinateBindingElement : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Binding )
enum Binding{
  PER_VERTEX = SoTextureCoordinateBindingElement::PER_VERTEX,   PER_VERTEX_INDEXED = SoTextureCoordinateBindingElement::PER_VERTEX_INDEXED};
public Q_SLOTS:
SoTextureCoordinateBindingElement* new_SoTextureCoordinateBindingElement();
   SoTextureCoordinateBindingElement::Binding  static_SoTextureCoordinateBindingElement_get(SoState*  state);
   int  static_SoTextureCoordinateBindingElement_getClassStackIndex();
   SoType  static_SoTextureCoordinateBindingElement_getClassTypeId();
   SoTextureCoordinateBindingElement::Binding  static_SoTextureCoordinateBindingElement_getDefault();
   void py_q_init(SoTextureCoordinateBindingElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoTextureCoordinateBindingElement*)theWrappedObject)->py_q_init(state));}
   void static_SoTextureCoordinateBindingElement_set(SoState*  state, SoTextureCoordinateBindingElement::Binding  binding);
};





class PythonQtShell_SoTextureCoordinateElement : public SoTextureCoordinateElement
{
public:
    PythonQtShell_SoTextureCoordinateElement():SoTextureCoordinateElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoTextureCoordinateElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
SoTextureCoordinateElement::CoordType  getType() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoTextureCoordinateElement : public SoTextureCoordinateElement
{ public:
inline SoTextureCoordinateElement::CoordType  py_q_getType() const { return SoTextureCoordinateElement::getType(); }
inline void py_q_init(SoState*  state) { SoTextureCoordinateElement::init(state); }
};

class PythonQtWrapper_SoTextureCoordinateElement : public QObject
{ Q_OBJECT
public:
Q_ENUMS(CoordType )
enum CoordType{
  EXPLICIT = SoTextureCoordinateElement::EXPLICIT,   FUNCTION = SoTextureCoordinateElement::FUNCTION};
public Q_SLOTS:
SoTextureCoordinateElement* new_SoTextureCoordinateElement();
   const SbVec4f*  get(SoTextureCoordinateElement* theWrappedObject, const SbVec3f&  point, const SbVec3f&  normal) const;
   const SbVec2f*  get2(SoTextureCoordinateElement* theWrappedObject, int  index) const;
   const SbVec4f*  get4(SoTextureCoordinateElement* theWrappedObject, int  index) const;
   int  static_SoTextureCoordinateElement_getClassStackIndex();
   SoType  static_SoTextureCoordinateElement_getClassTypeId();
   const SoTextureCoordinateElement*  static_SoTextureCoordinateElement_getInstance(SoState*  state);
   int  getNum(SoTextureCoordinateElement* theWrappedObject) const;
   SoTextureCoordinateElement::CoordType  getType(SoTextureCoordinateElement* theWrappedObject) const;
   SoTextureCoordinateElement::CoordType  py_q_getType(SoTextureCoordinateElement* theWrappedObject) const{  return (((PythonQtPublicPromoter_SoTextureCoordinateElement*)theWrappedObject)->py_q_getType());}
   SoTextureCoordinateElement::CoordType  static_SoTextureCoordinateElement_getType(SoState*  state);
   void py_q_init(SoTextureCoordinateElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoTextureCoordinateElement*)theWrappedObject)->py_q_init(state));}
   bool  is2D(SoTextureCoordinateElement* theWrappedObject) const;
   void static_SoTextureCoordinateElement_set2(SoState*  state, SoNode*  node, int  numCoords, const SbVec2f*  coords);
   void static_SoTextureCoordinateElement_set4(SoState*  state, SoNode*  node, int  numCoords, const SbVec4f*  coords);
   void static_SoTextureCoordinateElement_setDefault(SoState*  state, SoNode*  node);
};





class PythonQtShell_SoTextureImageElement : public SoTextureImageElement
{
public:
    PythonQtShell_SoTextureImageElement():SoTextureImageElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoTextureImageElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
bool  matches(const SoElement*  elt) const override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void setElt(const SbVec2s&  s, int  nc, const unsigned char*  bytes, int  wrapS, int  wrapT, int  model, const SbColor&  blendColor) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoTextureImageElement : public SoTextureImageElement
{ public:
inline void promoted_setElt(const SbVec2s&  s, int  nc, const unsigned char*  bytes, int  wrapS, int  wrapT, int  model, const SbColor&  blendColor) { this->setElt(s, nc, bytes, wrapS, wrapT, model, blendColor); }
inline void py_q_init(SoState*  state) { SoTextureImageElement::init(state); }
inline void py_q_setElt(const SbVec2s&  s, int  nc, const unsigned char*  bytes, int  wrapS, int  wrapT, int  model, const SbColor&  blendColor) { SoTextureImageElement::setElt(s, nc, bytes, wrapS, wrapT, model, blendColor); }
};

class PythonQtWrapper_SoTextureImageElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoTextureImageElement* new_SoTextureImageElement();
   bool  static_SoTextureImageElement_containsTransparency(SoState*  state);
   const unsigned char*  static_SoTextureImageElement_get(SoState*  state, SbVec2s&  size, int&  numComponents, int&  wrapS, int&  wrapT, int&  model, SbColor&  blendColor);
   int  static_SoTextureImageElement_getClassStackIndex();
   SoType  static_SoTextureImageElement_getClassTypeId();
   const unsigned char*  static_SoTextureImageElement_getDefault(SbVec2s&  s, int&  nc);
   void py_q_init(SoTextureImageElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoTextureImageElement*)theWrappedObject)->py_q_init(state));}
   void static_SoTextureImageElement_set(SoState*  state, SoNode*  node, const SbVec2s&  size, int  numComponents, const unsigned char*  bytes, int  wrapS, int  wrapT, int  model, const SbColor&  blendColor);
   void setElt(SoTextureImageElement* theWrappedObject, const SbVec2s&  s, int  nc, const unsigned char*  bytes, int  wrapS, int  wrapT, int  model, const SbColor&  blendColor);
   void py_q_setElt(SoTextureImageElement* theWrappedObject, const SbVec2s&  s, int  nc, const unsigned char*  bytes, int  wrapS, int  wrapT, int  model, const SbColor&  blendColor){  (((PythonQtPublicPromoter_SoTextureImageElement*)theWrappedObject)->py_q_setElt(s, nc, bytes, wrapS, wrapT, model, blendColor));}
};





class PythonQtShell_SoTextureMatrixElement : public SoTextureMatrixElement
{
public:
    PythonQtShell_SoTextureMatrixElement():SoTextureMatrixElement(),_wrapper(nullptr) {};

   ~PythonQtShell_SoTextureMatrixElement() override;

void captureThis(SoState*  state) const override;
SoElement*  copyMatchInfo() const override;
void init(SoState*  state) override;
void makeEltIdentity() override;
bool  matches(const SoElement*  elt) const override;
void multElt(const SbMatrix&  matrix) override;
void pop(SoState*  state, const SoElement*  prevTopElement) override;
void push(SoState*  state) override;
void rotateEltBy(const SbRotation&  translation) override;
void scaleEltBy(const SbVec3f&  scaleFactor) override;
void translateEltBy(const SbVec3f&  translation) override;

  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtPublicPromoter_SoTextureMatrixElement : public SoTextureMatrixElement
{ public:
inline void promoted_makeEltIdentity() { this->makeEltIdentity(); }
inline void promoted_multElt(const SbMatrix&  matrix) { this->multElt(matrix); }
inline void promoted_rotateEltBy(const SbRotation&  translation) { this->rotateEltBy(translation); }
inline void promoted_scaleEltBy(const SbVec3f&  scaleFactor) { this->scaleEltBy(scaleFactor); }
inline void promoted_translateEltBy(const SbVec3f&  translation) { this->translateEltBy(translation); }
inline void py_q_init(SoState*  state) { SoTextureMatrixElement::init(state); }
inline void py_q_makeEltIdentity() { SoTextureMatrixElement::makeEltIdentity(); }
inline void py_q_multElt(const SbMatrix&  matrix) { SoTextureMatrixElement::multElt(matrix); }
inline void py_q_push(SoState*  state) { SoTextureMatrixElement::push(state); }
inline void py_q_rotateEltBy(const SbRotation&  translation) { SoTextureMatrixElement::rotateEltBy(translation); }
inline void py_q_scaleEltBy(const SbVec3f&  scaleFactor) { SoTextureMatrixElement::scaleEltBy(scaleFactor); }
inline void py_q_translateEltBy(const SbVec3f&  translation) { SoTextureMatrixElement::translateEltBy(translation); }
};

class PythonQtWrapper_SoTextureMatrixElement : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoTextureMatrixElement* new_SoTextureMatrixElement();
   const SbMatrix*  static_SoTextureMatrixElement_get(SoState*  state);
   int  static_SoTextureMatrixElement_getClassStackIndex();
   SoType  static_SoTextureMatrixElement_getClassTypeId();
   void py_q_init(SoTextureMatrixElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoTextureMatrixElement*)theWrappedObject)->py_q_init(state));}
   void makeEltIdentity(SoTextureMatrixElement* theWrappedObject);
   void py_q_makeEltIdentity(SoTextureMatrixElement* theWrappedObject){  (((PythonQtPublicPromoter_SoTextureMatrixElement*)theWrappedObject)->py_q_makeEltIdentity());}
   void static_SoTextureMatrixElement_makeIdentity(SoState*  state, SoNode*  node);
   void static_SoTextureMatrixElement_mult(SoState*  state, SoNode*  node, const SbMatrix&  matrix);
   void multElt(SoTextureMatrixElement* theWrappedObject, const SbMatrix&  matrix);
   void py_q_multElt(SoTextureMatrixElement* theWrappedObject, const SbMatrix&  matrix){  (((PythonQtPublicPromoter_SoTextureMatrixElement*)theWrappedObject)->py_q_multElt(matrix));}
   void py_q_push(SoTextureMatrixElement* theWrappedObject, SoState*  state){  (((PythonQtPublicPromoter_SoTextureMatrixElement*)theWrappedObject)->py_q_push(state));}
   void static_SoTextureMatrixElement_rotateBy(SoState*  state, SoNode*  node, const SbRotation&  rotation);
   void rotateEltBy(SoTextureMatrixElement* theWrappedObject, const SbRotation&  translation);
   void py_q_rotateEltBy(SoTextureMatrixElement* theWrappedObject, const SbRotation&  translation){  (((PythonQtPublicPromoter_SoTextureMatrixElement*)theWrappedObject)->py_q_rotateEltBy(translation));}
   void static_SoTextureMatrixElement_scaleBy(SoState*  state, SoNode*  node, const SbVec3f&  scaleFactor);
   void scaleEltBy(SoTextureMatrixElement* theWrappedObject, const SbVec3f&  scaleFactor);
   void py_q_scaleEltBy(SoTextureMatrixElement* theWrappedObject, const SbVec3f&  scaleFactor){  (((PythonQtPublicPromoter_SoTextureMatrixElement*)theWrappedObject)->py_q_scaleEltBy(scaleFactor));}
   void static_SoTextureMatrixElement_translateBy(SoState*  state, SoNode*  node, const SbVec3f&  translation);
   void translateEltBy(SoTextureMatrixElement* theWrappedObject, const SbVec3f&  translation);
   void py_q_translateEltBy(SoTextureMatrixElement* theWrappedObject, const SbVec3f&  translation){  (((PythonQtPublicPromoter_SoTextureMatrixElement*)theWrappedObject)->py_q_translateEltBy(translation));}
};





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


