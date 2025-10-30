#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SoInput.h>
#include <Inventor/SoOutput.h>
#include <Inventor/SoType.h>
#include <Inventor/engines/SoBoolOperation.h>
#include <Inventor/engines/SoCalculator.h>
#include <Inventor/engines/SoCompose.h>
#include <Inventor/engines/SoComputeBoundingBox.h>
#include <Inventor/engines/SoCounter.h>
#include <Inventor/engines/SoElapsedTime.h>
#include <Inventor/engines/SoEngine.h>
#include <Inventor/engines/SoFieldConverter.h>
#include <Inventor/engines/SoGate.h>
#include <Inventor/engines/SoInterpolate.h>
#include <Inventor/engines/SoOnOff.h>
#include <Inventor/engines/SoOneShot.h>
#include <Inventor/engines/SoSelectOne.h>
#include <Inventor/engines/SoTimeCounter.h>
#include <Inventor/engines/SoTransformVec3f.h>
#include <Inventor/engines/SoTriggerAny.h>
#include <Inventor/fields/SoField.h>
#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/fields/SoFieldData.h>
#include <Inventor/misc/SoBase.h>
#include <Inventor/sensors/SoSensor.h>
#include <PythonQt.h>
#include <QObject>
#include <QVariant>



class PythonQtWrapper_SoBoolOperation : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Operation )
enum Operation{
  CLEAR = SoBoolOperation::CLEAR,   SET = SoBoolOperation::SET,   A = SoBoolOperation::A,   NOT_A = SoBoolOperation::NOT_A,   B = SoBoolOperation::B,   NOT_B = SoBoolOperation::NOT_B,   A_OR_B = SoBoolOperation::A_OR_B,   NOT_A_OR_B = SoBoolOperation::NOT_A_OR_B,   A_OR_NOT_B = SoBoolOperation::A_OR_NOT_B,   NOT_A_OR_NOT_B = SoBoolOperation::NOT_A_OR_NOT_B,   A_AND_B = SoBoolOperation::A_AND_B,   NOT_A_AND_B = SoBoolOperation::NOT_A_AND_B,   A_AND_NOT_B = SoBoolOperation::A_AND_NOT_B,   NOT_A_AND_NOT_B = SoBoolOperation::NOT_A_AND_NOT_B,   A_EQUALS_B = SoBoolOperation::A_EQUALS_B,   A_NOT_EQUALS_B = SoBoolOperation::A_NOT_EQUALS_B};
public Q_SLOTS:
SoBoolOperation* new_SoBoolOperation();
   SoType  static_SoBoolOperation_getClassTypeId();
SoMFBool*  py_get_a(SoBoolOperation* theWrappedObject){ return &theWrappedObject->a; }
SoMFBool*  py_get_b(SoBoolOperation* theWrappedObject){ return &theWrappedObject->b; }
SoEngineOutput*  py_get_inverse(SoBoolOperation* theWrappedObject){ return &theWrappedObject->inverse; }
SoMFEnum*  py_get_operation(SoBoolOperation* theWrappedObject){ return &theWrappedObject->operation; }
SoEngineOutput*  py_get_output(SoBoolOperation* theWrappedObject){ return &theWrappedObject->output; }
};





class PythonQtWrapper_SoCalculator : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoCalculator* new_SoCalculator();
   SoType  static_SoCalculator_getClassTypeId();
SoMFVec3f*  py_get_A(SoCalculator* theWrappedObject){ return &theWrappedObject->A; }
SoMFVec3f*  py_get_B(SoCalculator* theWrappedObject){ return &theWrappedObject->B; }
SoMFVec3f*  py_get_C(SoCalculator* theWrappedObject){ return &theWrappedObject->C; }
SoMFVec3f*  py_get_D(SoCalculator* theWrappedObject){ return &theWrappedObject->D; }
SoMFVec3f*  py_get_E(SoCalculator* theWrappedObject){ return &theWrappedObject->E; }
SoMFVec3f*  py_get_F(SoCalculator* theWrappedObject){ return &theWrappedObject->F; }
SoMFVec3f*  py_get_G(SoCalculator* theWrappedObject){ return &theWrappedObject->G; }
SoMFVec3f*  py_get_H(SoCalculator* theWrappedObject){ return &theWrappedObject->H; }
SoMFFloat*  py_get_a(SoCalculator* theWrappedObject){ return &theWrappedObject->a; }
SoMFFloat*  py_get_b(SoCalculator* theWrappedObject){ return &theWrappedObject->b; }
SoMFFloat*  py_get_c(SoCalculator* theWrappedObject){ return &theWrappedObject->c; }
SoMFFloat*  py_get_d(SoCalculator* theWrappedObject){ return &theWrappedObject->d; }
SoMFFloat*  py_get_e(SoCalculator* theWrappedObject){ return &theWrappedObject->e; }
SoMFString*  py_get_expression(SoCalculator* theWrappedObject){ return &theWrappedObject->expression; }
SoMFFloat*  py_get_f(SoCalculator* theWrappedObject){ return &theWrappedObject->f; }
SoMFFloat*  py_get_g(SoCalculator* theWrappedObject){ return &theWrappedObject->g; }
SoMFFloat*  py_get_h(SoCalculator* theWrappedObject){ return &theWrappedObject->h; }
SoEngineOutput*  py_get_oA(SoCalculator* theWrappedObject){ return &theWrappedObject->oA; }
SoEngineOutput*  py_get_oB(SoCalculator* theWrappedObject){ return &theWrappedObject->oB; }
SoEngineOutput*  py_get_oC(SoCalculator* theWrappedObject){ return &theWrappedObject->oC; }
SoEngineOutput*  py_get_oD(SoCalculator* theWrappedObject){ return &theWrappedObject->oD; }
SoEngineOutput*  py_get_oa(SoCalculator* theWrappedObject){ return &theWrappedObject->oa; }
SoEngineOutput*  py_get_ob(SoCalculator* theWrappedObject){ return &theWrappedObject->ob; }
SoEngineOutput*  py_get_oc(SoCalculator* theWrappedObject){ return &theWrappedObject->oc; }
SoEngineOutput*  py_get_od(SoCalculator* theWrappedObject){ return &theWrappedObject->od; }
};





class PythonQtWrapper_SoComposeMatrix : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoComposeMatrix* new_SoComposeMatrix();
   SoType  static_SoComposeMatrix_getClassTypeId();
SoMFVec3f*  py_get_center(SoComposeMatrix* theWrappedObject){ return &theWrappedObject->center; }
SoEngineOutput*  py_get_matrix(SoComposeMatrix* theWrappedObject){ return &theWrappedObject->matrix; }
SoMFRotation*  py_get_rotation(SoComposeMatrix* theWrappedObject){ return &theWrappedObject->rotation; }
SoMFVec3f*  py_get_scaleFactor(SoComposeMatrix* theWrappedObject){ return &theWrappedObject->scaleFactor; }
SoMFRotation*  py_get_scaleOrientation(SoComposeMatrix* theWrappedObject){ return &theWrappedObject->scaleOrientation; }
SoMFVec3f*  py_get_translation(SoComposeMatrix* theWrappedObject){ return &theWrappedObject->translation; }
};





class PythonQtWrapper_SoComposeRotation : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoComposeRotation* new_SoComposeRotation();
   SoType  static_SoComposeRotation_getClassTypeId();
SoMFFloat*  py_get_angle(SoComposeRotation* theWrappedObject){ return &theWrappedObject->angle; }
SoMFVec3f*  py_get_axis(SoComposeRotation* theWrappedObject){ return &theWrappedObject->axis; }
SoEngineOutput*  py_get_rotation(SoComposeRotation* theWrappedObject){ return &theWrappedObject->rotation; }
};





class PythonQtWrapper_SoComposeRotationFromTo : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoComposeRotationFromTo* new_SoComposeRotationFromTo();
   SoType  static_SoComposeRotationFromTo_getClassTypeId();
SoMFVec3f*  py_get_from(SoComposeRotationFromTo* theWrappedObject){ return &theWrappedObject->from; }
SoEngineOutput*  py_get_rotation(SoComposeRotationFromTo* theWrappedObject){ return &theWrappedObject->rotation; }
SoMFVec3f*  py_get_to(SoComposeRotationFromTo* theWrappedObject){ return &theWrappedObject->to; }
};





class PythonQtWrapper_SoComposeVec2f : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoComposeVec2f* new_SoComposeVec2f();
   SoType  static_SoComposeVec2f_getClassTypeId();
SoEngineOutput*  py_get_vector(SoComposeVec2f* theWrappedObject){ return &theWrappedObject->vector; }
SoMFFloat*  py_get_x(SoComposeVec2f* theWrappedObject){ return &theWrappedObject->x; }
SoMFFloat*  py_get_y(SoComposeVec2f* theWrappedObject){ return &theWrappedObject->y; }
};





class PythonQtWrapper_SoComposeVec3f : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoComposeVec3f* new_SoComposeVec3f();
   SoType  static_SoComposeVec3f_getClassTypeId();
SoEngineOutput*  py_get_vector(SoComposeVec3f* theWrappedObject){ return &theWrappedObject->vector; }
SoMFFloat*  py_get_x(SoComposeVec3f* theWrappedObject){ return &theWrappedObject->x; }
SoMFFloat*  py_get_y(SoComposeVec3f* theWrappedObject){ return &theWrappedObject->y; }
SoMFFloat*  py_get_z(SoComposeVec3f* theWrappedObject){ return &theWrappedObject->z; }
};





class PythonQtWrapper_SoComposeVec4f : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoComposeVec4f* new_SoComposeVec4f();
   SoType  static_SoComposeVec4f_getClassTypeId();
SoEngineOutput*  py_get_vector(SoComposeVec4f* theWrappedObject){ return &theWrappedObject->vector; }
SoMFFloat*  py_get_w(SoComposeVec4f* theWrappedObject){ return &theWrappedObject->w; }
SoMFFloat*  py_get_x(SoComposeVec4f* theWrappedObject){ return &theWrappedObject->x; }
SoMFFloat*  py_get_y(SoComposeVec4f* theWrappedObject){ return &theWrappedObject->y; }
SoMFFloat*  py_get_z(SoComposeVec4f* theWrappedObject){ return &theWrappedObject->z; }
};





class PythonQtWrapper_SoComputeBoundingBox : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoComputeBoundingBox* new_SoComputeBoundingBox();
   SoType  static_SoComputeBoundingBox_getClassTypeId();
   const SbViewportRegion*  getViewportRegion(SoComputeBoundingBox* theWrappedObject) const;
   void setViewportRegion(SoComputeBoundingBox* theWrappedObject, const SbViewportRegion&  vpReg);
SoEngineOutput*  py_get_boxCenter(SoComputeBoundingBox* theWrappedObject){ return &theWrappedObject->boxCenter; }
SoEngineOutput*  py_get_max(SoComputeBoundingBox* theWrappedObject){ return &theWrappedObject->max; }
SoEngineOutput*  py_get_min(SoComputeBoundingBox* theWrappedObject){ return &theWrappedObject->min; }
SoSFNode*  py_get_node(SoComputeBoundingBox* theWrappedObject){ return &theWrappedObject->node; }
SoEngineOutput*  py_get_objectCenter(SoComputeBoundingBox* theWrappedObject){ return &theWrappedObject->objectCenter; }
SoSFPath*  py_get_path(SoComputeBoundingBox* theWrappedObject){ return &theWrappedObject->path; }
};





class PythonQtWrapper_SoCounter : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoCounter* new_SoCounter();
   SoType  static_SoCounter_getClassTypeId();
SoSFShort*  py_get_max(SoCounter* theWrappedObject){ return &theWrappedObject->max; }
SoSFShort*  py_get_min(SoCounter* theWrappedObject){ return &theWrappedObject->min; }
SoEngineOutput*  py_get_output(SoCounter* theWrappedObject){ return &theWrappedObject->output; }
SoSFShort*  py_get_reset(SoCounter* theWrappedObject){ return &theWrappedObject->reset; }
SoSFShort*  py_get_step(SoCounter* theWrappedObject){ return &theWrappedObject->step; }
SoEngineOutput*  py_get_syncOut(SoCounter* theWrappedObject){ return &theWrappedObject->syncOut; }
SoSFTrigger*  py_get_trigger(SoCounter* theWrappedObject){ return &theWrappedObject->trigger; }
};





class PythonQtWrapper_SoDecomposeMatrix : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoDecomposeMatrix* new_SoDecomposeMatrix();
   SoType  static_SoDecomposeMatrix_getClassTypeId();
SoMFVec3f*  py_get_center(SoDecomposeMatrix* theWrappedObject){ return &theWrappedObject->center; }
SoMFMatrix*  py_get_matrix(SoDecomposeMatrix* theWrappedObject){ return &theWrappedObject->matrix; }
SoEngineOutput*  py_get_rotation(SoDecomposeMatrix* theWrappedObject){ return &theWrappedObject->rotation; }
SoEngineOutput*  py_get_scaleFactor(SoDecomposeMatrix* theWrappedObject){ return &theWrappedObject->scaleFactor; }
SoEngineOutput*  py_get_scaleOrientation(SoDecomposeMatrix* theWrappedObject){ return &theWrappedObject->scaleOrientation; }
SoEngineOutput*  py_get_translation(SoDecomposeMatrix* theWrappedObject){ return &theWrappedObject->translation; }
};





class PythonQtWrapper_SoDecomposeRotation : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoDecomposeRotation* new_SoDecomposeRotation();
   SoType  static_SoDecomposeRotation_getClassTypeId();
SoEngineOutput*  py_get_angle(SoDecomposeRotation* theWrappedObject){ return &theWrappedObject->angle; }
SoEngineOutput*  py_get_axis(SoDecomposeRotation* theWrappedObject){ return &theWrappedObject->axis; }
SoMFRotation*  py_get_rotation(SoDecomposeRotation* theWrappedObject){ return &theWrappedObject->rotation; }
};





class PythonQtWrapper_SoDecomposeVec2f : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoDecomposeVec2f* new_SoDecomposeVec2f();
   SoType  static_SoDecomposeVec2f_getClassTypeId();
SoMFVec2f*  py_get_vector(SoDecomposeVec2f* theWrappedObject){ return &theWrappedObject->vector; }
SoEngineOutput*  py_get_x(SoDecomposeVec2f* theWrappedObject){ return &theWrappedObject->x; }
SoEngineOutput*  py_get_y(SoDecomposeVec2f* theWrappedObject){ return &theWrappedObject->y; }
};





class PythonQtWrapper_SoDecomposeVec3f : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoDecomposeVec3f* new_SoDecomposeVec3f();
   SoType  static_SoDecomposeVec3f_getClassTypeId();
SoMFVec3f*  py_get_vector(SoDecomposeVec3f* theWrappedObject){ return &theWrappedObject->vector; }
SoEngineOutput*  py_get_x(SoDecomposeVec3f* theWrappedObject){ return &theWrappedObject->x; }
SoEngineOutput*  py_get_y(SoDecomposeVec3f* theWrappedObject){ return &theWrappedObject->y; }
SoEngineOutput*  py_get_z(SoDecomposeVec3f* theWrappedObject){ return &theWrappedObject->z; }
};





class PythonQtWrapper_SoDecomposeVec4f : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoDecomposeVec4f* new_SoDecomposeVec4f();
   SoType  static_SoDecomposeVec4f_getClassTypeId();
SoMFVec4f*  py_get_vector(SoDecomposeVec4f* theWrappedObject){ return &theWrappedObject->vector; }
SoEngineOutput*  py_get_w(SoDecomposeVec4f* theWrappedObject){ return &theWrappedObject->w; }
SoEngineOutput*  py_get_x(SoDecomposeVec4f* theWrappedObject){ return &theWrappedObject->x; }
SoEngineOutput*  py_get_y(SoDecomposeVec4f* theWrappedObject){ return &theWrappedObject->y; }
SoEngineOutput*  py_get_z(SoDecomposeVec4f* theWrappedObject){ return &theWrappedObject->z; }
};





class PythonQtWrapper_SoElapsedTime : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoElapsedTime* new_SoElapsedTime();
   SoType  static_SoElapsedTime_getClassTypeId();
SoSFBool*  py_get_on(SoElapsedTime* theWrappedObject){ return &theWrappedObject->on; }
SoSFBool*  py_get_pause(SoElapsedTime* theWrappedObject){ return &theWrappedObject->pause; }
SoSFTrigger*  py_get_reset(SoElapsedTime* theWrappedObject){ return &theWrappedObject->reset; }
SoSFFloat*  py_get_speed(SoElapsedTime* theWrappedObject){ return &theWrappedObject->speed; }
SoSFTime*  py_get_timeIn(SoElapsedTime* theWrappedObject){ return &theWrappedObject->timeIn; }
SoEngineOutput*  py_get_timeOut(SoElapsedTime* theWrappedObject){ return &theWrappedObject->timeOut; }
};





class PythonQtWrapper_SoEngine : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
   SoEngine*  copy(SoEngine* theWrappedObject) const;
   void evaluateWrapper(SoEngine* theWrappedObject);
   SoEngine*  static_SoEngine_getByName(const SbName&  name);
   SoType  static_SoEngine_getClassTypeId();
   SoEngineOutput*  getOutput(SoEngine* theWrappedObject, const SbName&  outputName) const;
   bool  isNotifying(SoEngine* theWrappedObject) const;
   bool  shouldCopy(SoEngine* theWrappedObject) const;
};





class PythonQtWrapper_SoEngineOutput : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoEngineOutput* new_SoEngineOutput();
void delete_SoEngineOutput(SoEngineOutput* obj) { delete obj; }
   void addConnection(SoEngineOutput* theWrappedObject, SoField*  arg__1);
   void doneWriting(SoEngineOutput* theWrappedObject) const;
   void enable(SoEngineOutput* theWrappedObject, bool  flag);
   SoType  getConnectionType(SoEngineOutput* theWrappedObject) const;
   SoEngine*  getContainer(SoEngineOutput* theWrappedObject) const;
   int  getNumConnections(SoEngineOutput* theWrappedObject) const;
   bool  isEnabled(SoEngineOutput* theWrappedObject) const;
   SoField*  operator_subscript(SoEngineOutput* theWrappedObject, int  i) const;
   void prepareToWrite(SoEngineOutput* theWrappedObject) const;
   void removeConnection(SoEngineOutput* theWrappedObject, SoField*  arg__1);
   void setContainer(SoEngineOutput* theWrappedObject, SoEngine*  eng);
};





class PythonQtWrapper_SoFieldConverter : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
   SoType  static_SoFieldConverter_getClassTypeId();
   SoField*  getConnectedInput(SoFieldConverter* theWrappedObject);
   SoField*  getInput(SoFieldConverter* theWrappedObject, SoType  type);
   SoEngineOutput*  getOutput(SoFieldConverter* theWrappedObject, SoType  type);
};





class PythonQtWrapper_SoGate : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoGate* new_SoGate(SoType  mfInputType);
   SoType  static_SoGate_getClassTypeId();
SoSFBool*  py_get_enable(SoGate* theWrappedObject){ return &theWrappedObject->enable; }
SoMField*  py_get_input(SoGate* theWrappedObject){ return theWrappedObject->input; }
SoEngineOutput*  py_get_output(SoGate* theWrappedObject){ return theWrappedObject->output; }
SoSFTrigger*  py_get_trigger(SoGate* theWrappedObject){ return &theWrappedObject->trigger; }
};





class PythonQtWrapper_SoInterpolate : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
   SoType  static_SoInterpolate_getClassTypeId();
SoSFFloat*  py_get_alpha(SoInterpolate* theWrappedObject){ return &theWrappedObject->alpha; }
SoEngineOutput*  py_get_output(SoInterpolate* theWrappedObject){ return &theWrappedObject->output; }
};





class PythonQtWrapper_SoInterpolateFloat : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoInterpolateFloat* new_SoInterpolateFloat();
   SoType  static_SoInterpolateFloat_getClassTypeId();
SoMFFloat*  py_get_input0(SoInterpolateFloat* theWrappedObject){ return &theWrappedObject->input0; }
SoMFFloat*  py_get_input1(SoInterpolateFloat* theWrappedObject){ return &theWrappedObject->input1; }
};





class PythonQtWrapper_SoInterpolateRotation : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoInterpolateRotation* new_SoInterpolateRotation();
   SoType  static_SoInterpolateRotation_getClassTypeId();
SoMFRotation*  py_get_input0(SoInterpolateRotation* theWrappedObject){ return &theWrappedObject->input0; }
SoMFRotation*  py_get_input1(SoInterpolateRotation* theWrappedObject){ return &theWrappedObject->input1; }
};





class PythonQtWrapper_SoInterpolateVec2f : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoInterpolateVec2f* new_SoInterpolateVec2f();
   SoType  static_SoInterpolateVec2f_getClassTypeId();
SoMFVec2f*  py_get_input0(SoInterpolateVec2f* theWrappedObject){ return &theWrappedObject->input0; }
SoMFVec2f*  py_get_input1(SoInterpolateVec2f* theWrappedObject){ return &theWrappedObject->input1; }
};





class PythonQtWrapper_SoInterpolateVec3f : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoInterpolateVec3f* new_SoInterpolateVec3f();
   SoType  static_SoInterpolateVec3f_getClassTypeId();
SoMFVec3f*  py_get_input0(SoInterpolateVec3f* theWrappedObject){ return &theWrappedObject->input0; }
SoMFVec3f*  py_get_input1(SoInterpolateVec3f* theWrappedObject){ return &theWrappedObject->input1; }
};





class PythonQtWrapper_SoInterpolateVec4f : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoInterpolateVec4f* new_SoInterpolateVec4f();
   SoType  static_SoInterpolateVec4f_getClassTypeId();
SoMFVec4f*  py_get_input0(SoInterpolateVec4f* theWrappedObject){ return &theWrappedObject->input0; }
SoMFVec4f*  py_get_input1(SoInterpolateVec4f* theWrappedObject){ return &theWrappedObject->input1; }
};





class PythonQtWrapper_SoOnOff : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoOnOff* new_SoOnOff();
   SoType  static_SoOnOff_getClassTypeId();
SoEngineOutput*  py_get_isOff(SoOnOff* theWrappedObject){ return &theWrappedObject->isOff; }
SoEngineOutput*  py_get_isOn(SoOnOff* theWrappedObject){ return &theWrappedObject->isOn; }
SoSFTrigger*  py_get_off(SoOnOff* theWrappedObject){ return &theWrappedObject->off; }
SoSFTrigger*  py_get_on(SoOnOff* theWrappedObject){ return &theWrappedObject->on; }
SoSFTrigger*  py_get_toggle(SoOnOff* theWrappedObject){ return &theWrappedObject->toggle; }
};





class PythonQtWrapper_SoOneShot : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Flags )
enum Flags{
  RETRIGGERABLE = SoOneShot::RETRIGGERABLE,   HOLD_FINAL = SoOneShot::HOLD_FINAL};
public Q_SLOTS:
SoOneShot* new_SoOneShot();
   SoType  static_SoOneShot_getClassTypeId();
SoSFBool*  py_get_disable(SoOneShot* theWrappedObject){ return &theWrappedObject->disable; }
SoSFTime*  py_get_duration(SoOneShot* theWrappedObject){ return &theWrappedObject->duration; }
SoSFBitMask*  py_get_flags(SoOneShot* theWrappedObject){ return &theWrappedObject->flags; }
SoEngineOutput*  py_get_isActive(SoOneShot* theWrappedObject){ return &theWrappedObject->isActive; }
SoEngineOutput*  py_get_ramp(SoOneShot* theWrappedObject){ return &theWrappedObject->ramp; }
SoSFTime*  py_get_timeIn(SoOneShot* theWrappedObject){ return &theWrappedObject->timeIn; }
SoEngineOutput*  py_get_timeOut(SoOneShot* theWrappedObject){ return &theWrappedObject->timeOut; }
SoSFTrigger*  py_get_trigger(SoOneShot* theWrappedObject){ return &theWrappedObject->trigger; }
};





class PythonQtWrapper_SoSelectOne : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSelectOne* new_SoSelectOne(SoType  mfInputType);
   SoType  static_SoSelectOne_getClassTypeId();
SoSFInt32*  py_get_index(SoSelectOne* theWrappedObject){ return &theWrappedObject->index; }
SoMField*  py_get_input(SoSelectOne* theWrappedObject){ return theWrappedObject->input; }
SoEngineOutput*  py_get_output(SoSelectOne* theWrappedObject){ return theWrappedObject->output; }
};





class PythonQtWrapper_SoTimeCounter : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoTimeCounter* new_SoTimeCounter();
   SoType  static_SoTimeCounter_getClassTypeId();
SoMFFloat*  py_get_duty(SoTimeCounter* theWrappedObject){ return &theWrappedObject->duty; }
SoSFFloat*  py_get_frequency(SoTimeCounter* theWrappedObject){ return &theWrappedObject->frequency; }
SoSFShort*  py_get_max(SoTimeCounter* theWrappedObject){ return &theWrappedObject->max; }
SoSFShort*  py_get_min(SoTimeCounter* theWrappedObject){ return &theWrappedObject->min; }
SoSFBool*  py_get_on(SoTimeCounter* theWrappedObject){ return &theWrappedObject->on; }
SoEngineOutput*  py_get_output(SoTimeCounter* theWrappedObject){ return &theWrappedObject->output; }
SoSFShort*  py_get_reset(SoTimeCounter* theWrappedObject){ return &theWrappedObject->reset; }
SoSFShort*  py_get_step(SoTimeCounter* theWrappedObject){ return &theWrappedObject->step; }
SoSFTrigger*  py_get_syncIn(SoTimeCounter* theWrappedObject){ return &theWrappedObject->syncIn; }
SoEngineOutput*  py_get_syncOut(SoTimeCounter* theWrappedObject){ return &theWrappedObject->syncOut; }
SoSFTime*  py_get_timeIn(SoTimeCounter* theWrappedObject){ return &theWrappedObject->timeIn; }
};





class PythonQtWrapper_SoTransformVec3f : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoTransformVec3f* new_SoTransformVec3f();
   SoType  static_SoTransformVec3f_getClassTypeId();
SoEngineOutput*  py_get_direction(SoTransformVec3f* theWrappedObject){ return &theWrappedObject->direction; }
SoMFMatrix*  py_get_matrix(SoTransformVec3f* theWrappedObject){ return &theWrappedObject->matrix; }
SoEngineOutput*  py_get_normalDirection(SoTransformVec3f* theWrappedObject){ return &theWrappedObject->normalDirection; }
SoEngineOutput*  py_get_point(SoTransformVec3f* theWrappedObject){ return &theWrappedObject->point; }
SoMFVec3f*  py_get_vector(SoTransformVec3f* theWrappedObject){ return &theWrappedObject->vector; }
};





class PythonQtWrapper_SoTriggerAny : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoTriggerAny* new_SoTriggerAny();
   SoType  static_SoTriggerAny_getClassTypeId();
SoSFTrigger*  py_get_input0(SoTriggerAny* theWrappedObject){ return &theWrappedObject->input0; }
SoSFTrigger*  py_get_input1(SoTriggerAny* theWrappedObject){ return &theWrappedObject->input1; }
SoSFTrigger*  py_get_input2(SoTriggerAny* theWrappedObject){ return &theWrappedObject->input2; }
SoSFTrigger*  py_get_input3(SoTriggerAny* theWrappedObject){ return &theWrappedObject->input3; }
SoSFTrigger*  py_get_input4(SoTriggerAny* theWrappedObject){ return &theWrappedObject->input4; }
SoSFTrigger*  py_get_input5(SoTriggerAny* theWrappedObject){ return &theWrappedObject->input5; }
SoSFTrigger*  py_get_input6(SoTriggerAny* theWrappedObject){ return &theWrappedObject->input6; }
SoSFTrigger*  py_get_input7(SoTriggerAny* theWrappedObject){ return &theWrappedObject->input7; }
SoSFTrigger*  py_get_input8(SoTriggerAny* theWrappedObject){ return &theWrappedObject->input8; }
SoSFTrigger*  py_get_input9(SoTriggerAny* theWrappedObject){ return &theWrappedObject->input9; }
SoEngineOutput*  py_get_output(SoTriggerAny* theWrappedObject){ return &theWrappedObject->output; }
};


