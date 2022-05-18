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
 |   $Revision: 1.2 $
 |
 |   Description:
 |      This file defines the SoSelectOne class, used to select one
 |      value out of an SoMF field and write it into the corresponding
 |      SoSF field.
 |
 |   Author(s)          : Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SELECTONE_
#define  _SO_SELECTONE_

#include <Inventor/system/SbSystem.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFName.h>



////////////////////////////////////////////////////////////////////////////////
//! Selects one value from a multiple-value field.
/*!
\class SoSelectOne
\ingroup Engines
This engine selects a single value from a multiple-value field,
based on the input field \b index .
The type of the input field can be any subclass of SoMField,
and the type of the output is the corresponding subclass of
SoSField. For example, if the input type is SoMFVec3f, the
output type will be SoSFVec3f.
The type is specified when an instance of the class is created.
For example,
SoSelectOne(SoMFFloat::getClassTypeId())
creates an engine that selects one floating-point value.


Note that unlike most other engine fields, the \b input  field and
\b output  are pointers.
Note also that by default \b input  does not contain any values,
and no value is output from the engine.

\par File Format/Default
\par
\code
SelectOne {
  index 0
}
\endcode

\par See Also
\par
SoEngineOutput, SoConcatenate, SoGate
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoSelectOne : public SoEngine {

    SO_ENGINE_HEADER(SoSelectOne);

  public:

    //! Constructor.  The argument specifies the type of the multiple-value
    //! input field.
    SoSelectOne(SoType mfInputType);

    //! Index is used to choose which value of the input is written to
    //! output.  Default is -1, meaning don't write anything.
    SoSFInt32           index;

    //! Note that unlike most engines the input field is a pointer.
    //! The default value for this field is no values.
    SoMField            *input;

    //! Note that unlike most engines the output is a pointer.  The
    //! type of the output is the single-value field corresponding to
    //! whatever type the input is.
    SoEngineOutput      *output;

  SoINTERNAL public:
    static void         initClass();

    virtual SoFieldContainer *  copyThroughConnection() const;
  
  private:
    SoSelectOne();
    ~SoSelectOne();

    //! SelectOne engines must write out their input type before writing
    //! their fields, so these are overridden:
    virtual bool        readInstance(SoInput *in, unsigned short flags);
    virtual void        writeInstance(SoOutput *out);

    void                setup(SoType);
    virtual void        evaluate();

    int conversionCase;

    SoFieldData *myInputData;
    SoEngineOutputData *myOutputData;

    SoSFName typeField; //!< Used when reading/writing
};

#endif /* _SO_SELECTONE_ */
