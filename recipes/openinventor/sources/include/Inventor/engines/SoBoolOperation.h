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
 * Copyright (C) 1990,91,92   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.1.1.1 $
 |
 |   Description:
 |      This file contains the declaration of the BoolOperation engine
 |
 |   Classes:
 |      SoBoolOperation
 |
 |   Author(s)          : Ronen Barzel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_BOOL_OPERATION_
#define  _SO_BOOL_OPERATION_

#include <Inventor/system/SbSystem.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoMFEnum.h>
#include <Inventor/fields/SoMFBool.h>

////////////////////////////////////////////////////////////////////////////////
//! Performs Boolean operations.
/*!
\class SoBoolOperation
\ingroup Engines
This engine performs a Boolean operation on two inputs,
and returns both the result of the operation and its inverse.


The input fields can have multiple values, allowing the engine to 
perform several Boolean operations in parallel. 
One input may have more values than the other.  In that case,
the last value of the shorter input will be repeated as necessary.

\par File Format/Default
\par
\code
BoolOperation {
  a FALSE
  b FALSE
  operation A
}
\endcode

\par See Also
\par
SoEngineOutput, SoCalculator
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoBoolOperation : public SoEngine {

    SO_ENGINE_HEADER(SoBoolOperation);
    
  public:

    enum Operation {
            CLEAR,
             SET,
            A,
        NOT_A,
                 B,
                 NOT_B,
            A_OR_B,
        NOT_A_OR_B,
            A_OR_NOT_B,
        NOT_A_OR_NOT_B,
            A_AND_B,
        NOT_A_AND_B,
            A_AND_NOT_B,
        NOT_A_AND_NOT_B,
            A_EQUALS_B,
            A_NOT_EQUALS_B
    };

    //! \name Inputs
    //@{

    //! First argument to the Boolean operation.
    SoMFBool    a;

    //! Second argument to the Boolean operation.
    SoMFBool    b;

    //! The Boolean operation.
    SoMFEnum    operation;

    //@}

    //! \name Outputs
    //@{

    //! Result of the Boolean operation applied to the inputs.
    SoEngineOutput output;      

    //! Inverse of \b output .
    SoEngineOutput inverse;     

    //@}

    //! Constructor.
    SoBoolOperation();
    
  SoINTERNAL public:

    static void initClass();

  private:

    //! Destructor
    ~SoBoolOperation();

    //! Evaluation method
    virtual void evaluate();
};

#endif  /* _SO_BOOL_OPERATION_ */
