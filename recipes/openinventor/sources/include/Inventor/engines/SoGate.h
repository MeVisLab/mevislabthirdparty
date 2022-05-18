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
 |      This file defines the SoGate class.
 |
 |   Author(s)          : Ronen Barzel, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_GATE_
#define  _SO_GATE_

#include <Inventor/system/SbSystem.h>
#include <Inventor/SoDB.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFName.h>
#include <Inventor/fields/SoSFTrigger.h>



////////////////////////////////////////////////////////////////////////////////
//! Selectively copies its input to its output.
/*!
\class SoGate
\ingroup Engines
This engine selectively copies its input to its output.
The type of the input field can be any subclass of SoMField.
The type is specified when an instance of the class is created.
For example,
SoGate(SoMFFloat::getClassTypeId())
creates an engine that copies floating-point values.


The \b enable  input controls continous flow-through of values.
While \b enable  is TRUE, the input will be copied to the output. 
Alternatively, by touching the \b trigger  input, you can 
copy a single value from the input to the output.

 
Note that unlike most other engine fields, \b input  and
\b output  are pointers.
Note also that by default \b input  does not contain any values.

\par See Also
\par
SoEngineOutput, SoConcatenate, SoSelectOne
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoGate : public SoEngine {

    SO_ENGINE_HEADER(SoGate);

  public:

    //! Constructor.  The argument specifies the type of the input field.
    SoGate(SoType mfInputType);

    SoSFBool            enable;         //!< enable continuous flow-through
    SoSFTrigger         trigger;        //!< copy a single value

    //! Note that unlike most engines the input field is a pointer.
    //! The default value for this field is no values.
    SoMField            *input;

    //! Note that unlike most engines the output is a pointer.  The
    //! type of the output is the same as the input.
    SoEngineOutput      *output;

  SoINTERNAL public:
    static void         initClass();

  protected:

    virtual void        inputChanged(SoField *whichInput);

    virtual SoFieldContainer *  copyThroughConnection() const;
  
  private:
    SoGate();
    ~SoGate();

    //! gate engines must write out their input type before writing
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

#endif /* _SO_GATE_ */
