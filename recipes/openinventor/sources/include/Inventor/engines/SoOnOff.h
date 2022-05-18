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
 |      This file contains the declaration of the OnOff engine
 |
 |   Classes:
 |      SoOnOff
 |
 |   Author(s)          : Ronen Barzel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_ON_OFF_
#define  _SO_ON_OFF_

#include <Inventor/system/SbSystem.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFTrigger.h>

////////////////////////////////////////////////////////////////////////////////
//! Engine that functions as an on/off switch.
/*!
\class SoOnOff
\ingroup Engines
This engine has three triggers as input and two Boolean values as output.  
The \b isOn  output is a switch that can be turned \b on  or \b off  by
triggering the corresponding input.
You can toggle the value by triggering the \b toggle  input.
By default \b isOn  is FALSE.
The \b isOff  output value is the inverse of \b isOn

\par File Format/Default
\par
\code
OnOff {
}
\endcode

\par See Also
\par
SoEngineOutput
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoOnOff : public SoEngine {

    SO_ENGINE_HEADER(SoOnOff);
    
  public:

    //! \name Inputs
    //@{

    //! Turn the \b isOn  switch on.
    SoSFTrigger on;     

    //! Turn the \b isOn  switch off.
    SoSFTrigger off;    

    //! Toggle the switch value.
    SoSFTrigger toggle; 

    //@}

    //! \name Outputs
    //@{

    //! Switch value.
    SoEngineOutput isOn;        

    //! The inverse of \b isOn .
    SoEngineOutput isOff;       

    //@}

    //! Constructor.
    SoOnOff();
    
  SoINTERNAL public:

    static void initClass();

  protected:
    virtual void        inputChanged(SoField *whichInput);

  private:

    //! Destructor
    ~SoOnOff();

    //! Evaluation method
    virtual void evaluate();

    bool        state;
};

#endif  /* _SO_ON_OFF_ */
