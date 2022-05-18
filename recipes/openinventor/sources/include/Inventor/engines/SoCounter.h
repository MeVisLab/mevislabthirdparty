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
 |      This file contains the implementation of the Counter engine
 |
 |   Classes:
 |      SoCounter
 |
 |   Author(s)          : Ronen Barzel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_COUNTER_
#define  _SO_COUNTER_

#include <Inventor/system/SbSystem.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFTrigger.h>

////////////////////////////////////////////////////////////////////////////////
//! Triggered integer counter.
/*!
\class SoCounter
\ingroup Engines
This engine is a counter that outputs numbers, starting at a
minimum value, increasing by a step value, and ending with a number
that does not exceed the maximum value.  It outputs the next
number whenever the \b trigger  input is touched. When the maximum number
is reached, it starts counting from the beginning again.  


At any time the counter can be reset to a specific value by setting
the \b reset  input field to that value.  The next time the counter
is triggered it will start counting from there.  Note that the counter will
always output numbers based on the min, max and step values, and
setting the reset value does not affect those input fields.
If the reset value is not a legal counter value, the counter will still
behave as though it is.
\code
If reset is greater than max, the counter is set to max.
If reset is less than min, the counter is set to min.
If reset is between steps, the counter is set to the lower step value.
\endcode


Each time a counting cycle is started, the \b syncOut  output is triggered.  
This output can be used to synchronize some other event with the 
counting cycle.

\par File Format/Default
\par
\code
Counter {
  min 0
  max 1
  step 1
  reset 0
}
\endcode

\par See Also
\par
SoTimeCounter, SoEngineOutput
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoCounter : public SoEngine {

    SO_ENGINE_HEADER(SoCounter);

  public:
    //! \name Inputs
    //@{

    //! Minimum value for the counter.
    SoSFShort           min;            

    //! Maximum value for the counter.
    SoSFShort           max;            

    //! Counter step value.
    SoSFShort           step;           

    //! Go to the next step.
    SoSFTrigger         trigger;        

    //! At the next trigger, reset the counter to the specified value.
    SoSFShort           reset;          

    //@}

    //! \name Outputs
    //@{

    //! Counts min-to-max in step increments.
    SoEngineOutput      output;         

    //! Triggers at cycle start.
    SoEngineOutput      syncOut;        

    //@}

    //! Constructor
    SoCounter();

  SoINTERNAL public:

    static void initClass();

  protected:
    virtual void        inputChanged(SoField *whichInput);

  private:
    enum Todo {
        RECALC  = (1<<0),
        RESET   = (1<<1),
        STEP    = (1<<2)
    };
    unsigned int        todo;
    int                 nStages;
    int                 curStage;
    struct Stage {
        int     val;            //!< counter value for stage
    }                   *stages;

    //! Destructor
    ~SoCounter();

    //! Evaluation method
    virtual void        evaluate();
};

#endif  /* _SO_COUNTER_ */
