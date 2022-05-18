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
 |      This file contains the declaration of the OneShot engine
 |
 |   Classes:
 |      SoOneShot
 |
 |   Author(s)          : Ronen Barzel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_ONE_SHOT_
#define  _SO_ONE_SHOT_

#include <Inventor/system/SbSystem.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/fields/SoSFBitMask.h>

////////////////////////////////////////////////////////////////////////////////
//! Timer that runs for a pre-set amount of time.
/*!
\class SoOneShot
\ingroup Engines
This engine is a timer that runs for a pre-set amount of time and then stops.
By default, the \b timeIn  input is connected to the \b realTime  global field.
It can, however, by connected to any other time source.


The timer is started when the \b trigger  input is touched.
It then runs for the specified \b duration , and updates the \b timeOut  
output with the time that has elapsed.
During that time, the \b ramp  output is also updated.  The \b ramp  output
starts at 0.0 at the beginning of the cycle, and linearly increases
until it reaches 1.0 at the end of the cycle.  


You can disable the timer by setting the \b disable  input to TRUE.
The output value remains 0.0 while the timer is disabled.
If the timer is disabled in the middle of a cycle the output values
will be set to 0.0.


The \b flags  input contains control flags. Using the flags
you can set the timer to be retriggerable in the middle of a cycle,
and set the output values to stay high after the cycle has 
been completed.  By default, these flags are not set.

\par File Format/Default
\par
\code
OneShot {
  duration 1
  flags ()
  disable FALSE
  timeIn 1316437066.408
}
\endcode

\par See Also
\par
SoElapsedTime, SoEngineOutput
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoOneShot : public SoEngine {

    SO_ENGINE_HEADER(SoOneShot);

  public:
    enum Flags  {
        RETRIGGERABLE   = (1<<0),       //!< can start over during cycle?
        HOLD_FINAL      = (1<<1)        //!< ramp & timeOut stay high after cycle?
    };

    //! \name Inputs
    //@{

    //! Duration of the active cycle.
    SoSFTime            duration;       

    //! Start the cycle. The trigger will be ignored if it 
    //! is touched in the middle of a cycle and the RETRIGGERABLE flag 
    //! is not set.
    SoSFTrigger         trigger;        

    //! Control flags.
    SoSFBitMask         flags;

    //! If TRUE, the timer is disabled.
    SoSFBool            disable;        

    //! Running time.
    SoSFTime            timeIn;

    //@}

    //! \name Outputs
    //@{

    //! Elapsed time from the start.
    SoEngineOutput      timeOut;        

    //! Is TRUE during the active cycle.
    SoEngineOutput      isActive;       

    //! Ramps linearly from 0.0 to 1.0.
    SoEngineOutput      ramp;           

    //@}

    //! Constructor
    SoOneShot();

  SoINTERNAL public:

    static void initClass();

  protected:
    virtual void        inputChanged(SoField *whichInput);

    //! Writes instance to SoOutput. Takes care of not writing out
    //! connection to realTime that is created in constructor.
    virtual void        writeInstance(SoOutput *out);

    //! Reads stuff into instance.  Works around a problem with old
    //! files that contain explicit references to the default
    //! connection to realTime.
    virtual bool        readInstance(SoInput *in, unsigned short flags);

  private:
    enum State {
        DISABLED,               //!< everything clamped at 0 (via disable input)
        OFF,                    //!< normal idle state
        TRIGGERED,              //!< has been triggered, need to start running
        ON,                     //!< running, watching the time
        PEAKED                  //!< have reached the end, need to reset
    }                   state;
    SbTime              baseTime;       //!< Starting time for elapsed time 
    SbTime              timeVal;        //!< holds output time value
    double              rampVal;        //!< holds ramp value
    bool                outputPending;  //!< keeps outputs enabled until data is read

    //! Destructor
    ~SoOneShot();

    //! Evaluation method
    virtual void        evaluate();
};

#endif  /* _SO_ONE_SHOT_ */
