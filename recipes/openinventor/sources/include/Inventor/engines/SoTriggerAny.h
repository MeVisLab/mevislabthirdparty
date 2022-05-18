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
 |      This file contains the implementation of the trigger fan-in engine
 |
 |   Classes:
 |      SoTriggerAny
 |
 |   Author(s)          : Ronen Barzel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TRIGGER_ANY_
#define  _SO_TRIGGER_ANY_

#include <Inventor/system/SbSystem.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFTrigger.h>

////////////////////////////////////////////////////////////////////////////////
//! Provides fan-in for triggers.
/*!
\class SoTriggerAny
\ingroup Engines
This engine takes up to 10 input triggers, and produces one trigger
output.  The output is triggered whenever one of the inputs is touched.

\par File Format/Default
\par
\code
TriggerAny {
}
\endcode

\par See Also
\par
SoEngineOutput, SoSFTrigger
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoTriggerAny : public SoEngine {

    SO_ENGINE_HEADER(SoTriggerAny);

  public:
    SoSFTrigger                 input0;
    SoSFTrigger                 input1;
    SoSFTrigger                 input2;
    SoSFTrigger                 input3;
    SoSFTrigger                 input4;
    SoSFTrigger                 input5;
    SoSFTrigger                 input6;
    SoSFTrigger                 input7;
    SoSFTrigger                 input8;
    SoSFTrigger                 input9;
    SoEngineOutput              output;

    //! Constructor
    SoTriggerAny();

  SoINTERNAL public:
    static void                 initClass();

  private:
    ~SoTriggerAny();
    virtual void                evaluate();
};

#endif  /* _SO_TRIGGER_ANY_ */
