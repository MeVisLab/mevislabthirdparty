/*
 *
 *  Copyright (C) 2000 Silicon Graphics, Inc.  All Rights Reserved. 
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  Further, this software is distributed without any warranty that it is
 *  free of the rightful claim of any third person regarding infringement
 *  or the like.  Any license provided herein, whether implied or
 *  otherwise, applies only to this software file.  Patent licenses, if
 *  any, provided herein do not apply to combinations of this program with
 *  other software, or any other product whatsoever.
 * 
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,
 *  Mountain View, CA  94043, or:
 * 
 *  http://www.sgi.com 
 * 
 *  For further information regarding this notice, see: 
 * 
 *  http://oss.sgi.com/projects/GenInfo/NoticeExplan/
 *
 */

/*
 * Copyright (C) 1990,91   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.1.1.1 $
 |
 |   Classes:
 |      Field converter classes.
 |
 |   Author(s)          : Ronen Barzel, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#include <Inventor/engines/SoFieldConverter.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/fields/SoFields.h>
#include "SoFieldConverters.h"

//
// Maximum number of multi-valued field types, and maximum total
// number of field types:
//
#define MAXMFIELDS      1024
#define MAXFIELDS       MAXMFIELDS*2

// Constants for all the field types; used so we can quickly switch()
// on the field type at evaluate() time.
enum TypeConst 
{
    MFBitMask = 1,
    MFBool,
    MFColor,
    MFDouble,
    MFEnum,
    MFFloat,
    MFInt32,
    MFMatrix,
    MFMatrixd,
    MFName,
    MFNode,
    MFPath,
    MFPlane,
    MFPlaned,
    MFRotation,
    MFRotationd,
    MFShort,
    MFString,
    MFTime,
    MFUInt32,
    MFUShort,
    MFVec2d,
    MFVec2f,
    MFVec3d,
    MFVec3f,
    MFVec4d,
    MFVec4f,
    SFBitMask = MAXMFIELDS+1,
    SFBool,
    SFColor,
    SFDouble,
    SFEnum,
    SFFloat,
    SFInt32,
    SFMatrix,
    SFMatrixd,
    SFName,
    SFNode,
    SFPath,
    SFPlane,
    SFPlaned,
    SFRotation,
    SFRotationd,
    SFShort,
    SFString,
    SFTime,
    SFUInt32,
    SFUShort,
    SFVec2d,
    SFVec2f,
    SFVec3d,
    SFVec3f,
    SFVec4d,
    SFVec4f,
    BAD_TYPE
};

//
// Can't use regular SO_ENGINE_SOURCE macro because of the funky
// handling of getFieldData/getEngineOutputData:
//
SO__ENGINE_VARS(SoConvToTrigger);

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Constructor; takes type of input
//
// Use: public

SoConvToTrigger::SoConvToTrigger()
//
////////////////////////////////////////////////////////////////////////
{
    SO_ENGINE_CONSTRUCTOR(SoConvToTrigger);
    SO_ENGINE_ADD_OUTPUT(output, SoSFTrigger);
    myInputData = new SoFieldData(inputData);
    input = NULL;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Destructor; cleans up
//
// Use: public

SoConvToTrigger::~SoConvToTrigger()
//
////////////////////////////////////////////////////////////////////////
{
    delete myInputData;
    if (input != NULL) {
        delete input;
    }
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Database calls to get correct input field.  Creates field and
//    fieldData on the fly.
//
// Use: public

SoField *
SoConvToTrigger::getInput(SoType type)
//
////////////////////////////////////////////////////////////////////////
{
    input = (SoField *) type.createInstance();
    input->setContainer(this);
    myInputData->addField(this, "input", input);

    return input;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Database calls to get correct output.  Easy, because this always
//    outputs an SoSFTrigger.
//
// Use: public

SoEngineOutput *
SoConvToTrigger::getOutput(SoType)
//
////////////////////////////////////////////////////////////////////////
{
    return &output;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    inputChanged; needs to pull input value
//
// Use: public

void
SoConvToTrigger::inputChanged(SoField *whichInput)
//
////////////////////////////////////////////////////////////////////////
{
    whichInput->evaluate();
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Evaluate; just needs to evaluate input field.
//
// Use: public

void
SoConvToTrigger::evaluate()
//
////////////////////////////////////////////////////////////////////////
{
    input->evaluate();
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns type id.
//
// Use: public
//
SoType
SoConvToTrigger::getTypeId() const
//
////////////////////////////////////////////////////////////////////////
{
    return classTypeId;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns field data
//
// Use: internal
//
const SoFieldData *
SoConvToTrigger::getFieldData() const 
//
////////////////////////////////////////////////////////////////////////
{
    return myInputData;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns output data
//
// Use: internal
//
const SoEngineOutputData *
SoConvToTrigger::getOutputData() const
//
////////////////////////////////////////////////////////////////////////
{
    return outputData;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Create an instance of the class, using private constructor.
//    Used only by database when reading in from file.
//
// Use: internal
//
void *
SoConvToTrigger::createInstance()
//
////////////////////////////////////////////////////////////////////////
{
    return new SoConvToTrigger;
}

//
// Can't use regular SO_ENGINE_SOURCE macro because of the funky
// handling of getFieldData/getEngineOutputData:
//
SO__ENGINE_VARS(SoBuiltinFieldConverter);

////////////////////////////////////////////////////////////////////////
//
// Description:
//   
//
// Use:

SoBuiltinFieldConverter::SoBuiltinFieldConverter()
//
////////////////////////////////////////////////////////////////////////
{
    SO_ENGINE_CONSTRUCTOR(SoBuiltinFieldConverter);
    myInputData = new SoFieldData(inputData);
    myOutputData = new SoEngineOutputData(outputData);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//   
//
// Use:

SoBuiltinFieldConverter::~SoBuiltinFieldConverter()
//
////////////////////////////////////////////////////////////////////////
{
    delete myInputData;
    delete myOutputData;

    if (input != NULL) {
        delete input;
        delete output;
    }
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//   Called by database with the type we're converting to.  The engine
//   output is built on the fly, based on the type.  Also sets the
//   'outType' integer so we can quickly decide what conversion to do
//   at evaluate() time.
//
// Use: internal

SoEngineOutput *
SoBuiltinFieldConverter::getOutput(SoType type)
//
////////////////////////////////////////////////////////////////////////
{
    output = new SoEngineOutput;
    output->setContainer(this);
    myOutputData->addOutput(this, "output", output, type);
    
#define DECIDEOUT(class) \
    (type == SO__CONCAT(So,class)::getClassTypeId()) { \
        outType = class; \
    }
    
    if DECIDEOUT(MFBitMask)
    else if DECIDEOUT(MFBool)
    else if DECIDEOUT(MFColor)
    else if DECIDEOUT(MFDouble)
    else if DECIDEOUT(MFEnum)
    else if DECIDEOUT(MFFloat)
    else if DECIDEOUT(MFInt32)
    else if DECIDEOUT(MFMatrix)
    else if DECIDEOUT(MFMatrixd)
    else if DECIDEOUT(MFName)
    else if DECIDEOUT(MFNode)
    else if DECIDEOUT(MFPath)
    else if DECIDEOUT(MFPlane)
    else if DECIDEOUT(MFPlaned)
    else if DECIDEOUT(MFRotation)
    else if DECIDEOUT(MFRotationd)
    else if DECIDEOUT(MFShort)
    else if DECIDEOUT(MFString)
    else if DECIDEOUT(MFTime)
    else if DECIDEOUT(MFUInt32)
    else if DECIDEOUT(MFUShort)
    else if DECIDEOUT(MFVec2d)
    else if DECIDEOUT(MFVec2f)
    else if DECIDEOUT(MFVec3d)
    else if DECIDEOUT(MFVec3f)
    else if DECIDEOUT(MFVec4d)
    else if DECIDEOUT(MFVec4f)
    else if DECIDEOUT(SFBitMask)
    else if DECIDEOUT(SFBool)
    else if DECIDEOUT(SFColor)
    else if DECIDEOUT(SFDouble)
    else if DECIDEOUT(SFEnum)
    else if DECIDEOUT(SFFloat)
    else if DECIDEOUT(SFInt32)
    else if DECIDEOUT(SFMatrix)
    else if DECIDEOUT(SFMatrixd)
    else if DECIDEOUT(SFName)
    else if DECIDEOUT(SFNode)
    else if DECIDEOUT(SFPath)
    else if DECIDEOUT(SFPlane)
    else if DECIDEOUT(SFPlaned)
    else if DECIDEOUT(SFRotation)
    else if DECIDEOUT(SFRotationd)
    else if DECIDEOUT(SFShort)
    else if DECIDEOUT(SFString)
    else if DECIDEOUT(SFTime)
    else if DECIDEOUT(SFUInt32)
    else if DECIDEOUT(SFUShort)
    else if DECIDEOUT(SFVec2d)
    else if DECIDEOUT(SFVec2f)
    else if DECIDEOUT(SFVec3d)
    else if DECIDEOUT(SFVec3f)
    else if DECIDEOUT(SFVec4d)
    else if DECIDEOUT(SFVec4f)
#undef DECIDEOUT
#ifdef DEBUG    
    else {
        SoDebugError::post("(internal) SoBuiltinFieldConverter::getOutput"
                       "no output for type '%s'", type.getName().getString());
    }
#endif    
    return output;
}


////////////////////////////////////////////////////////////////////////
//
// Description:
//   Called by database with the type we're converting from.  The input
//   field is built on the fly, based on the type.  Also sets the
//   'inType' integer so we can quickly decide what conversion to do
//   at evaluate() time.
//
// Use: internal

SoField *
SoBuiltinFieldConverter::getInput(SoType type)
//
////////////////////////////////////////////////////////////////////////
{
    input = (SoField *)type.createInstance();
    
#define DECIDEIN(class,defaultValue) \
    (type == SO__CONCAT(So,class)::getClassTypeId()) { \
        inType = class; \
        ((SO__CONCAT(So,class) *)input)->setValue defaultValue ; \
    }
    
    if DECIDEIN(MFBitMask,(0))
    else if DECIDEIN(MFBool,(FALSE))
    else if DECIDEIN(MFColor,(0,0,0))
    else if DECIDEIN(MFDouble,(0))
    else if DECIDEIN(MFEnum,(0))
    else if DECIDEIN(MFFloat,(0))
    else if DECIDEIN(MFInt32,(0))
    else if DECIDEIN(MFMatrixd,(SbMatrixd::identity()))
    else if DECIDEIN(MFMatrix,(SbMatrix::identity()))
    else if DECIDEIN(MFName,(""))
    else if DECIDEIN(MFNode,(NULL))
    else if DECIDEIN(MFPath,(NULL))
    else if DECIDEIN(MFPlane,(SbPlane(SbVec3f(0,0,0),0)))
    else if DECIDEIN(MFPlaned,(SbPlaned(SbVec3d(0,0,0),0)))
    else if DECIDEIN(MFRotation,(SbRotation()))
    else if DECIDEIN(MFRotationd,(SbRotationd()))
    else if DECIDEIN(MFShort,(0))
    else if DECIDEIN(MFString,(""))
    else if DECIDEIN(MFTime,(SbTime::zero()))
    else if DECIDEIN(MFUInt32,(0))
    else if DECIDEIN(MFUShort,(0))
    else if DECIDEIN(MFVec2d,(0,0))
    else if DECIDEIN(MFVec2f,(0,0))
    else if DECIDEIN(MFVec3d,(0,0,0))
    else if DECIDEIN(MFVec3f,(0,0,0))
    else if DECIDEIN(MFVec4d,(0,0,0,0))
    else if DECIDEIN(MFVec4f,(0,0,0,0))
    else if DECIDEIN(SFBitMask,(0))
    else if DECIDEIN(SFBool,(FALSE))
    else if DECIDEIN(SFColor,(0,0,0))
    else if DECIDEIN(SFDouble,(0))
    else if DECIDEIN(SFEnum,(0))
    else if DECIDEIN(SFFloat,(0))
    else if DECIDEIN(SFInt32,(0))
    else if DECIDEIN(SFMatrix,(SbMatrix::identity()))
    else if DECIDEIN(SFMatrixd,(SbMatrixd::identity()))
    else if DECIDEIN(SFName,(""))
    else if DECIDEIN(SFNode,(NULL))
    else if DECIDEIN(SFPath,(NULL))
    else if DECIDEIN(SFPlane,(SbPlane(SbVec3f(0,0,0),0)))
    else if DECIDEIN(SFPlaned,(SbPlaned(SbVec3d(0,0,0),0)))
    else if DECIDEIN(SFRotation,(SbRotation()))
    else if DECIDEIN(SFRotationd,(SbRotationd()))
    else if DECIDEIN(SFShort,(0))
    else if DECIDEIN(SFString,(""))
    else if DECIDEIN(SFTime,(SbTime::zero()))
    else if DECIDEIN(SFUInt32,(0))
    else if DECIDEIN(SFUShort,(0))
    else if DECIDEIN(SFVec2d,(0,0))
    else if DECIDEIN(SFVec2f,(0,0))
    else if DECIDEIN(SFVec3d,(0,0,0))
    else if DECIDEIN(SFVec3f,(0,0,0))
    else if DECIDEIN(SFVec4d,(0,0,0,0))
    else if DECIDEIN(SFVec4f,(0,0,0,0))
#undef DECIDEIN
#ifdef DEBUG    
    else {
        SoDebugError::post("(internal) SoBuiltinFieldConverter::getInput",
                       "no input for type '%s'", type.getName().getString());
    }
#endif    

    input->setContainer(this);
    myInputData->addField(this, "input", input);

    return input;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Write input to output, with a conversion in between.
//
// Use: private
//

void
SoBuiltinFieldConverter::evaluate()
//
////////////////////////////////////////////////////////////////////////
{
    // For efficiency and to reduce bloat, we don't use the standard
    // SO_ENGINE_OUTPUT macro:

#ifdef DEBUG
    if (input == NULL) {
        SoDebugError::post("(internal) SoBuiltinFieldConverter::evaluate",
                           "NULL input field");
        return;
    }
#endif    

    // We know that our engineOutput cannot be disabled, since nobody
    // but us has access to it. If we are connected from an
    // engineOutput and that engineOutput is disabled, we still want
    // to convert that value - this will happen the first time this
    // engine is evaluated after the output is disabled. After the
    // first time, notification will be blocked, so we don't have to
    // check for a disabled output here.

    for (int i = 0; i < output->getNumConnections(); i++) {
        SoField *outField = (*output)[i];
        if (!outField->isReadOnly())
            doConversion(outField);
    }
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Create an SbRotationd from an SbRotation.
//
// Use: private

SbRotationd
static getSbRotationdFromSbRotation(const SbRotation &r)
//
////////////////////////////////////////////////////////////////////////
{
  float q0, q1, q2, q3;
  r.getValue(q0, q1, q2, q3);
  return SbRotationd(q0, q1, q2, q3);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Create an SbRotation from an SbRotationd.
//
// Use: private

SbRotation
static getSbRotationFromSbRotationd(const SbRotationd &r)
//
////////////////////////////////////////////////////////////////////////
{
  double q0, q1, q2, q3;
  r.getValue(q0, q1, q2, q3);
  return SbRotation(static_cast<float>(q0), 
                    static_cast<float>(q1), 
                    static_cast<float>(q2), 
                    static_cast<float>(q3));
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Create an SbMatrixd from an SbMatrix.
//
// Use: private

SbMatrixd
static getSbMatrixdFromSbMatrix(const SbMatrix &r)
//
////////////////////////////////////////////////////////////////////////
{
  SbMat matf;
  r.getValue(matf);
  SbMatd matd;
  for (int c=0; c < 4; ++c){
    for (int r=0; r < 4; ++r){
      matd[r][c] = matf[r][c];
    }
  }
  return SbMatrixd(matd);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Create an SbMatrix from an SbMatrixd.
//
// Use: private

SbMatrix
static getSbMatrixFromSbMatrixd(const SbMatrixd &r)
//
////////////////////////////////////////////////////////////////////////
{
  SbMatd matd;
  r.getValue(matd);
  SbMat matf;
  for (int c=0; c < 4; ++c){
    for (int r=0; r < 4; ++r){
      matf[r][c] = static_cast<float>(matd[r][c]);
    }
  }
  return SbMatrix(matf);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Actually do the conversion, writing to the given field.
//    A massive switch, which is the opposite of object-oriented but
//    which makes the library a lot smaller.
//
// Use: private

void
SoBuiltinFieldConverter::doConversion(SoField *outField)
//
////////////////////////////////////////////////////////////////////////
{
    // Various variables needed by the conversion cases:
    int i;
    SbMatrix matrix;
    SbMatrixd matrixd;
    SbString string;

    // Combine inType/outType into one integer.
    switch (inType*MAXFIELDS + outType) {

#define CASE(typeIn,typeOut) case typeIn*MAXFIELDS+typeOut

// This macro is for converting the single/multi fields into their
// corresponding multi/single value fields.
// In normal code, it looks like:
// Single to Multi:
//   SoMField->setValue(SoSField->getValue())
// Multi so Single:
//   if (MField->getNum() > 0) SoSField->setValue(SoMField[0])

#define CONV1(type)                                                         \
      CASE(SO__CONCAT(SF,type),SO__CONCAT(MF,type)):                \
        ((SO__CONCAT(SoMF,type) *)outField)->setValue(                      \
            ((SO__CONCAT(SoSF,type) *)input)->getValue());                  \
        break;                                                              \
      CASE(SO__CONCAT(MF,type),SO__CONCAT(SF,type)):                \
        if (((SoMField *)input)->getNum() > 0)                              \
            ((SO__CONCAT(SoSF,type) *)outField)->setValue(                  \
                (*(SO__CONCAT(SoMF,type) *)input)[0]);                      \
        break
        
// Cases for all the field types:
        CONV1(BitMask);
        CONV1(Bool);
        CONV1(Color);
        CONV1(Double);
        CONV1(Enum);
        CONV1(Float);
        CONV1(Int32);
        CONV1(Matrix);
        CONV1(Matrixd);
        CONV1(Name);
        CONV1(Node);
        CONV1(Path);
        CONV1(Plane);
        CONV1(Planed);
        CONV1(Rotation);
        CONV1(Rotationd);
        CONV1(Short);
        CONV1(String);
        CONV1(Time);
        CONV1(UInt32);
        CONV1(UShort);
        CONV1(Vec2d);
        CONV1(Vec2f);
        CONV1(Vec3d);
        CONV1(Vec3f);
        CONV1(Vec4d);
        CONV1(Vec4f);
#undef CONV1
        
//
// Conversions to/from a string for all field types.  The eight cases
// are:
// Single to/from Single string:
// Single to/from Multiple string:
// Multi to/from Single string:
//    input->get(string); outField->set(string);
// Multi to/from Multi string:
//    for (i = 0; i < ((SoMField *)input)->getNum(); i++) {
//       (SoMField *)input->get1(i, string);
//       (SoMField *)outField->set1(i, string);
//
// Note: we must use the SF/MFString->setValue() routines and not just
// plain set() in case there is whitespace in the string, since set()
// takes file format, and in the file format strings with whitespace
// must be quoted.
//
#define CONVSTR(type)                                                       \
      CASE(SO__CONCAT(SF,type),SFString):                                   \
      CASE(SO__CONCAT(MF,type),SFString):                                   \
        input->get(string);                                                 \
        ((SoSFString *)outField)->setValue(string);                         \
        break;                                                              \
      CASE(SO__CONCAT(SF,type),MFString):                                   \
        input->get(string);                                                 \
        ((SoMFString *)outField)->set1Value(0,string);                      \
        break;                                                              \
      CASE(SO__CONCAT(MF,type),MFString):                                   \
        for (i = 0; i < ((SoMField *)input)->getNum(); i++) {               \
            ((SoMField *)input)->get1(i, string);                           \
            ((SoMFString *)outField)->set1Value(i, string);                 \
        }                                                                   \
        break;                                                              \
      CASE(SFString,SO__CONCAT(SF,type)):                                   \
      CASE(MFString,SO__CONCAT(SF,type)):                                   \
      CASE(SFString,SO__CONCAT(MF,type)):                                   \
        input->get(string);                                                 \
        outField->set(string.getString());                                  \
        break;                                                              \
      CASE(MFString,SO__CONCAT(MF,type)):                                   \
        for (i = 0; i < ((SoMField *)input)->getNum(); i++) {               \
            ((SoMField *)input)->get1(i, string);                           \
            ((SoMField *)outField)->set1(i, string.getString());            \
        }                                                                   \
        break
        
// All types except string:
        CONVSTR(BitMask);
        CONVSTR(Bool);
        CONVSTR(Color);
        CONVSTR(Double);
        CONVSTR(Enum);
        CONVSTR(Float);
        CONVSTR(Int32);
        CONVSTR(Matrix);
        CONVSTR(Matrixd);
        CONVSTR(Name);
        CONVSTR(Node);
        CONVSTR(Path);
        CONVSTR(Plane);
        CONVSTR(Planed);
        CONVSTR(Rotation);
        CONVSTR(Rotationd);
        CONVSTR(Short);
        CONVSTR(UInt32);
        CONVSTR(UShort);
        CONVSTR(Vec2d);
        CONVSTR(Vec2f);
        CONVSTR(Vec3d);
        CONVSTR(Vec3f);
        CONVSTR(Vec4d);
        CONVSTR(Vec4f);
#undef CONVSTR

// Special case for time to string; if the time is great enough,
// format as a date:
      CASE(SFTime,SFString):
      {
          SbTime t = ((SoSFTime *)input)->getValue();
          if (t.getValue() > 3.15e7) string = t.formatDate();
          else string = t.format();
          ((SoSFString *)outField)->setValue(string);
      }
      break;
      CASE(SFTime,MFString):
      {
          SbTime t = ((SoSFTime *)input)->getValue();
          if (t.getValue() > 3.15e7) string = t.formatDate();
          else string = t.format();
          ((SoMFString *)outField)->set1Value(0, string);
      }
      break;
      CASE(MFTime,SFString):
      {
          SbTime t = (*((SoMFTime *)input))[0];
          if (t.getValue() > 3.15e7) string = t.formatDate();
          else string = t.format();
          ((SoSFString *)outField)->setValue(string);
      }
      break;
      CASE(MFTime,MFString):
      {
          for (i = 0; i < ((SoMField *)input)->getNum(); i++) {
              SbTime t = (*((SoMFTime *)input))[i];
              if (t.getValue() > 3.15e7) string = t.formatDate();
              else string = t.format();
              ((SoMFString *)outField)->set1Value(i, string);
          }
      }
      break;

      CASE(SFColor,     SFVec3d):
      CASE(SFVec3d,     SFColor):

      CASE(SFMatrix,    SFMatrixd):
      CASE(SFPlane,     SFPlaned):
      CASE(SFRotation,  SFRotationd):
      CASE(SFVec2f,     SFVec2d):
      CASE(SFVec3f,     SFVec3d):
      CASE(SFVec4f,     SFVec4d):

      CASE(SFMatrixd,   SFMatrix):
      CASE(SFPlaned,    SFPlane):
      CASE(SFRotationd, SFRotation):
      CASE(SFVec2d,     SFVec2f):
      CASE(SFVec3d,     SFVec3f):
      CASE(SFVec4d,     SFVec4f):

      CASE(SFString,SFTime):
      CASE(MFString,SFTime):
      CASE(SFString,MFTime):
        input->get(string);
        outField->set(string.getString());
        break;

      CASE(MFMatrix,    MFMatrixd):
      CASE(MFPlane,     MFPlaned):
      CASE(MFRotation,  MFRotationd):
      CASE(MFVec2f,     MFVec2d):
      CASE(MFVec3f,     MFVec3d):
      CASE(MFVec4f,     MFVec4d):

      CASE(MFMatrixd,   MFMatrix):
      CASE(MFPlaned,    MFPlane):
      CASE(MFRotationd, MFRotation):
      CASE(MFVec2d,     MFVec2f):
      CASE(MFVec3d,     MFVec3f):
      CASE(MFVec4d,     MFVec4f):

      CASE(MFString,MFTime):
        for (i = 0; i < ((SoMField *)input)->getNum(); i++) {
            ((SoMField *)input)->get1(i, string);
            ((SoMField *)outField)->set1(i, string.getString());
        }
      break;
      

// This macro will do most of the conversions, relying on the C++
// built-in type conversions.  It does all eight combinations of
// single/multi to single/multi conversions for two types that are
// different.  HALF_CONV does the conversions one-way, CONV does them
// both ways:
// Single to single: 
//   SoSField->setValue(SoSField->getValue());
// Multi to single:
//   if (SoMField->getNum() > 0) SoSField->setValue(SoMField[0])
// Single to multi:
//   SoMField->setValue(SoSField->getValue())
// Multi to multi:
//   for (i = 0; i < SoMField->getNum(); i++) {
//      SoMField->set1Value(i, SoMfield[i]);
//   }
//
#define HALF_CONV(typeIn,typeOut,valTypeOut)                                  \
      CASE(SO__CONCAT(SF,typeIn),SO__CONCAT(SF,typeOut)):                     \
        ((SO__CONCAT(SoSF,typeOut) *)outField)->setValue((valTypeOut)         \
            ((SO__CONCAT(SoSF,typeIn) *)input)->getValue());                  \
        break;                                                                \
      CASE(SO__CONCAT(MF,typeIn),SO__CONCAT(SF,typeOut)):                     \
        if (((SoMField *)input)->getNum() > 0)                                \
            ((SO__CONCAT(SoSF,typeOut) *)outField)->setValue((valTypeOut)     \
                (*(SO__CONCAT(SoMF,typeIn) *)input)[0]);                      \
        break;                                                                \
      CASE(SO__CONCAT(SF,typeIn),SO__CONCAT(MF,typeOut)):                     \
        ((SO__CONCAT(SoMF,typeOut) *)outField)->setValue((valTypeOut)         \
            ((SO__CONCAT(SoSF,typeIn) *)input)->getValue());                  \
        break;                                                                \
      CASE(SO__CONCAT(MF,typeIn),SO__CONCAT(MF,typeOut)):                     \
        for (i = 0; i < ((SoMField *)input)->getNum(); i++) {                 \
            ((SO__CONCAT(SoMF,typeOut) *)outField)->set1Value(i,              \
                (valTypeOut) (*(SO__CONCAT(SoMF,typeIn) *)input)[i]);         \
        }                                                                     \
        break

#define CONV(type1,valType1,type2,valType2)                                   \
    HALF_CONV(type1,type2,valType2);                                          \
    HALF_CONV(type2,type1,valType1)
        

// Simple conversions for most fields:
#ifdef WIN32
// these still cause warnings on MSVC, but I don't want to copy the macros to remove the warning.
#pragma warning( push ) 
#pragma warning( disable : 4800 )
#endif
        CONV(Bool,bool,Double,double);
        CONV(Bool,bool,Float,float);
        CONV(Bool,bool,Int32,int32_t);
        CONV(Bool,bool,Short,short);
        CONV(Bool,bool,UInt32,uint32_t);
        CONV(Bool,bool,UShort,unsigned short);

#ifdef WIN32
#pragma warning( pop )
#endif

        CONV(Color,const SbColor &,Vec3f,const SbVec3f &);

        CONV(Double,double,Int32,int32_t);
        CONV(Double,double,Short,short);
        CONV(Double,double,UInt32,uint32_t);
        CONV(Double,double,UShort,unsigned short);
        CONV(Double,double,Float,float);

        CONV(Float,float,Int32,int32_t);
        CONV(Float,float,Short,short);
        CONV(Float,float,UInt32,uint32_t);
        CONV(Float,float,UShort,unsigned short);

        CONV(Int32,int32_t,Short,short);
        CONV(Int32,int32_t,UInt32,uint32_t);
        CONV(Int32,int32_t,UShort,unsigned short);

        CONV(Short,short,UInt32,uint32_t);
        CONV(Short,short,UShort,unsigned short);

        CONV(UInt32,uint32_t,UShort,unsigned short);

// Some wacky oddball conversions that we have to special-case:

// Float to time can be handled by regular code because SbTime has a
// constructor that takes a float, but time to float needs to be
// special-cased:
      HALF_CONV(Float, Time, float);

      CASE(SFTime, SFFloat):
        ((SoSFFloat *)outField)->setValue(
            ((SoSFTime *)input)->getValue().getValue());
        break;
      CASE(SFTime, SFDouble):
        ((SoSFDouble *)outField)->setValue(
            ((SoSFTime *)input)->getValue().getValue());
        break;
      CASE(SFTime, MFFloat):
        ((SoMFFloat *)outField)->setValue(
            ((SoSFTime *)input)->getValue().getValue());
        break;
      CASE(SFTime, MFDouble):
        ((SoMFDouble *)outField)->setValue(
            ((SoSFTime *)input)->getValue().getValue());
        break;
      CASE(MFTime, SFFloat):
        ((SoSFFloat *)outField)->setValue(
            (*(SoMFTime *)input)[0].getValue());
        break;
      CASE(MFTime, SFDouble):
        ((SoSFDouble *)outField)->setValue(
            (*(SoMFTime *)input)[0].getValue());
        break;
      CASE(MFTime, MFFloat):
        for (i = 0; i < ((SoMFTime *)input)->getNum(); i++) {
            ((SoMFFloat *)outField)->set1Value(i,
                (*(SoMFTime *)input)[i].getValue());
        }
        break;
      CASE(MFTime, MFDouble):
        for (i = 0; i < ((SoMFTime *)input)->getNum(); i++) {
            ((SoMFDouble *)outField)->set1Value(i,
                (*(SoMFTime *)input)[i].getValue());
        }
        break;
      
      CASE(SFMatrix, SFRotation):
        ((SoSFRotation *) outField)->setValue(
            SbRotation(((SoSFMatrix *) input)->getValue()));
        break;
      CASE(SFMatrix, SFRotationd):
        ((SoSFRotationd *) outField)->setValue(
            SbRotationd(  getSbMatrixdFromSbMatrix(((SoSFMatrix *) input)->getValue())  ));
        break;
      CASE(SFMatrixd, SFRotation):
        ((SoSFRotation *) outField)->setValue(
            SbRotation(  getSbMatrixFromSbMatrixd(((SoSFMatrixd *) input)->getValue())  ));
        break;
      CASE(SFMatrixd, SFRotationd):
        ((SoSFRotationd *) outField)->setValue(
            SbRotationd(((SoSFMatrixd *) input)->getValue()));
        break;

      CASE(SFMatrix, MFRotation):
        ((SoMFRotation *) outField)->setValue(
            SbRotation(((SoSFMatrix *) input)->getValue()));
        break;
      CASE(SFMatrix, MFRotationd):
        ((SoMFRotationd *) outField)->setValue(
            SbRotationd(   getSbMatrixdFromSbMatrix(((SoSFMatrix *) input)->getValue())   ));
        break;
      CASE(SFMatrixd, MFRotation):
        ((SoMFRotation *) outField)->setValue(
            SbRotation(   getSbMatrixFromSbMatrixd(((SoSFMatrixd *) input)->getValue())   ));
        break;
      CASE(SFMatrixd, MFRotationd):
        ((SoMFRotationd *) outField)->setValue(
            SbRotationd(((SoSFMatrixd *) input)->getValue()));
        break;

      CASE(MFMatrix, SFRotation):
        ((SoSFRotation *) outField)->setValue(
            SbRotation((* (SoMFMatrix *) input)[0]));
        break;
      CASE(MFMatrix, SFRotationd):
        ((SoSFRotationd *) outField)->setValue(
            SbRotationd(   getSbMatrixdFromSbMatrix(  (* (SoMFMatrix *) input)[0]  ))   );
        break;
      CASE(MFMatrixd, SFRotation):
        ((SoSFRotation *) outField)->setValue(
            SbRotation(   getSbMatrixFromSbMatrixd(  (* (SoMFMatrixd *) input)[0]  ))   );
        break;
      CASE(MFMatrixd, SFRotationd):
        ((SoSFRotationd *) outField)->setValue(
            SbRotationd((* (SoMFMatrixd *) input)[0]));
        break;

      CASE(MFMatrix, MFRotation):
        for (i = 0; i < ((SoMFMatrix *)input)->getNum(); i++) {
            ((SoMFRotation *)outField)->set1Value(i,
                SbRotation((* (SoMFMatrix *) input)[i]));
        }
        break;
      CASE(MFMatrix, MFRotationd):
        for (i = 0; i < ((SoMFMatrix *)input)->getNum(); i++) {
            ((SoMFRotationd *)outField)->set1Value(i,
                SbRotationd(   getSbMatrixdFromSbMatrix(  (* (SoMFMatrix *) input)[i]  )   ));
        }
        break;
      CASE(MFMatrixd, MFRotation):
        for (i = 0; i < ((SoMFMatrixd *)input)->getNum(); i++) {
            ((SoMFRotation *)outField)->set1Value(i,
                SbRotation(   getSbMatrixFromSbMatrixd(  (* (SoMFMatrixd *) input)[i]  )   ));
        }
        break;
      CASE(MFMatrixd, MFRotationd):
        for (i = 0; i < ((SoMFMatrixd *)input)->getNum(); i++) {
            ((SoMFRotationd *)outField)->set1Value(i,
                SbRotationd((* (SoMFMatrixd *) input)[i]));
        }
        break;


      CASE(SFRotation, SFMatrix):
        matrix.setRotate(((SoSFRotation *)input)->getValue());
        ((SoSFMatrix *)outField)->setValue(matrix);
        break;
      CASE(SFRotation, SFMatrixd):
        matrixd.setRotate(   getSbRotationdFromSbRotation(  ((SoSFRotation *)input)->getValue()  )  );
        ((SoSFMatrixd *)outField)->setValue(matrixd);
        break;
      CASE(SFRotationd, SFMatrix):
        matrix.setRotate(   getSbRotationFromSbRotationd( ((SoSFRotationd *)input)->getValue()  )  );
        ((SoSFMatrix *)outField)->setValue(matrix);
        break;
      CASE(SFRotationd, SFMatrixd):
        matrixd.setRotate(((SoSFRotationd *)input)->getValue());
        ((SoSFMatrixd *)outField)->setValue(matrixd);
        break;

      CASE(SFRotation, MFMatrix):
        matrix.setRotate(((SoSFRotation *)input)->getValue());
        ((SoSFMatrix *)outField)->setValue(matrix);
        break;
      CASE(SFRotation, MFMatrixd):
        matrixd.setRotate(  getSbRotationdFromSbRotation(  ((SoSFRotation *)input)->getValue()  )  );
        ((SoSFMatrixd *)outField)->setValue(matrixd);
        break;
      CASE(SFRotationd, MFMatrix):
        matrix.setRotate(  getSbRotationFromSbRotationd(  ((SoSFRotationd *)input)->getValue()  )  );
        ((SoSFMatrix *)outField)->setValue(matrix);
        break;
      CASE(SFRotationd, MFMatrixd):
        matrixd.setRotate(((SoSFRotationd *)input)->getValue());
        ((SoSFMatrixd *)outField)->setValue(matrixd);
        break;

      CASE(MFRotation, SFMatrix):
        matrix.setRotate((*(SoMFRotation *)input)[0]);
        ((SoSFMatrix *)outField)->setValue(matrix);
        break;
      CASE(MFRotation, SFMatrixd):
        matrixd.setRotate(   getSbRotationdFromSbRotation(  (*(SoMFRotation *)input)[0]  )   );
        ((SoSFMatrixd *)outField)->setValue(matrixd);
        break;
      CASE(MFRotationd, SFMatrix):
        matrix.setRotate(   getSbRotationFromSbRotationd(  (*(SoMFRotationd *)input)[0]  )   );
        ((SoSFMatrix *)outField)->setValue(matrix);
        break;
      CASE(MFRotationd, SFMatrixd):
        matrixd.setRotate((*(SoMFRotationd *)input)[0]);
        ((SoSFMatrixd *)outField)->setValue(matrixd);
        break;

      CASE(MFRotation, MFMatrix):
        for (i = 0; i < ((SoMFRotation *)input)->getNum(); i++) {
            matrix.setRotate((*(SoMFRotation *)input)[i]);
            ((SoMFMatrix *)outField)->set1Value(i, matrix);
        }
        break;
      CASE(MFRotation, MFMatrixd):
        for (i = 0; i < ((SoMFRotation *)input)->getNum(); i++) {
            matrixd.setRotate(   getSbRotationdFromSbRotation(  (*(SoMFRotation *)input)[i]  )   );
            ((SoMFMatrixd *)outField)->set1Value(i, matrixd);
        }
        break;
      CASE(MFRotationd, MFMatrix):
        for (i = 0; i < ((SoMFRotationd *)input)->getNum(); i++) {
            matrix.setRotate(   getSbRotationFromSbRotationd(  (*(SoMFRotationd *)input)[i]  )   );
            ((SoMFMatrix *)outField)->set1Value(i, matrix);
        }
        break;
      CASE(MFRotationd, MFMatrixd):
        for (i = 0; i < ((SoMFRotationd *)input)->getNum(); i++) {
            matrixd.setRotate((*(SoMFRotationd *)input)[i]);
            ((SoMFMatrixd *)outField)->set1Value(i, matrixd);
        }
        break;

      default:
#ifdef DEBUG
        SoDebugError::post("SoBuiltinFieldConverter::doConversion",
                           "Can't convert type %d to type %d\n",
                           inType, outType);
#endif
        break;
    }
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns type id.
//
// Use: public
//
SoType
SoBuiltinFieldConverter::getTypeId() const
//
////////////////////////////////////////////////////////////////////////
{
    return classTypeId;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns field data
//
// Use: internal
//
const SoFieldData *
SoBuiltinFieldConverter::getFieldData() const 
//
////////////////////////////////////////////////////////////////////////
{
    return myInputData;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns output data
//
// Use: internal
//
const SoEngineOutputData *
SoBuiltinFieldConverter::getOutputData() const
//
////////////////////////////////////////////////////////////////////////
{
    return myOutputData;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Create an instance of the class, using private constructor.
//    Used only by database when reading in from file.
//
// Use: internal
//
void *
SoBuiltinFieldConverter::createInstance()
//
////////////////////////////////////////////////////////////////////////
{
    return new SoBuiltinFieldConverter;
}
