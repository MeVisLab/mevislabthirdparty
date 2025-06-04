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
#include <Inventor/SbString.h>
#include <Inventor/SoInput.h>
#include <Inventor/SoOutput.h>
#include <Inventor/SoType.h>
#include <Inventor/engines/SoEngine.h>
#include <Inventor/engines/SoTransformVec3f.h>
#include <Inventor/engines/SoTriggerAny.h>
#include <Inventor/fields/SoField.h>
#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/fields/SoFieldData.h>
#include <Inventor/misc/SoBase.h>
#include <Inventor/sensors/SoSensor.h>



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


