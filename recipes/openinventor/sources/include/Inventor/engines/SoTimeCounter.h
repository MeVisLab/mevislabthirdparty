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
 |      This file contains the implementation of the TimeCounter engine
 |
 |   Classes:
 |      SoTimeCounter
 |
 |   Author(s)          : Ronen Barzel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TIME_COUNTER_
#define  _SO_TIME_COUNTER_

#include <Inventor/system/SbSystem.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFTrigger.h>

////////////////////////////////////////////////////////////////////////////////
//! Timed integer counter.
/*!
\class SoTimeCounter
\ingroup Engines
This engine is a counter that outputs numbers, starting
at a minimum value, increasing by a step value, and ending with
a number that does not exceed the maximum value.  When the 
maximum number is reached, it starts counting from the beginning again. 


The difference between this engine and the SoCounter engine, is
that this engine also has a \b timeIn  input, which allows the
counting cycles to be timed.  This engine counts automatically over time;
it does not need to be triggered to go to the next step.
By default, the \b timeIn  input is connected to the \b realTime  global field.  
It can, however, be connected to any time source. 


The \b frequency  input field controls how many min-to-max cycles
are performed per second.  For example, a \b frequency  value of 0.5 means
that it will take 2 seconds to complete a single min-to-max cycle.


The steps in the count cycle do not necessarily all have the same duration.
Using the \b duty  input field, you can arbitrarily split the time period
of the count cycle between the steps.
For example, if there are 5 steps in the cycle, a duty input of 
(1., 2., 2., 2., 1.) 
will make the second, third, and fourth steps take twice as long as the 
first and last steps.


At any time the counter can be reset to a specific value.  If you
set the \b reset  input field to a value, the engine will
continue counting from there.  Note that the counter will
always output numbers based on the \b min , \b max  and \b step  values, 
and setting the \b reset  value does not affect the those input fields.
If the reset value is not a legal counter value, the counter will still
behave as though it is:
\code
If reset is greater than max, the counter is set to max.
If reset is less than min, the counter is set to min.
If reset is between step values, the counter is set to the lower step.
\endcode
Each time a counting cycle is started, the \b syncOut  output is triggered.  
This output can be used to synchronize some other event with the 
counting cycle.
Other events can also synchronize the counter by triggering the 
\b syncIn  input.


You can pause the engine, by setting the \b on  input to FALSE, and
it will stop updating the output field. 
When you turn off the pause, by setting \b on  to TRUE, it 
will start counting again from where it left off.

\par File Format/Default
\par
\code
TimeCounter {
  min 0
  max 1
  step 1
  on TRUE
  frequency 1
  duty 1
  timeIn 1316437066.463
  reset 0
}
\endcode

\par See Also
\par
SoCounter, SoElapsedTime, SoEngineOutput
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoTimeCounter : public SoEngine {

    SO_ENGINE_HEADER(SoTimeCounter);

  public:
    //! \name Inputs
    //@{

    //! Minimum value for the counter.
    SoSFShort           min;            

    //! Maximum value for the counter.
    SoSFShort           max;            

    //! Counter step value.
    SoSFShort           step;           

    //! Counter pauses if this is set to FALSE.
    SoSFBool            on;             

    //! Number of \b min -to-\b max  cycles per second.
    SoSFFloat           frequency;      

    //! Duty cycle values.
    SoMFFloat           duty;           

    //! Running time.
    SoSFTime            timeIn;         

    //! Restart at the beginning of the cycle.
    SoSFTrigger         syncIn;         

    //! Reset the counter to the specified value.
    SoSFShort           reset;          

    //@}

    //! \name Outputs
    //@{

    //! Counts \b min -to-\b max , in \b step  increments.
    SoEngineOutput      output;         

    //! Triggers at cycle start.
    SoEngineOutput      syncOut;        

    //@}

    //! Constructor
    SoTimeCounter();

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
        ON,                     //!< counting
        PAUSED                  //!< holding
    }                   state;
    enum Todo {
        RECALC  = (1<<0),
        RESET   = (1<<1),
        SYNC    = (1<<2),
        PAUSE   = (1<<3),
        UNPAUSE = (1<<4)
    };
    unsigned int        todo;
    SbTime              period;         //!< total cycle time
    int                 nStages;
    int                 curStage;
    int                 prevStage;
    struct Stage {
        int     val;            //!< counter value for stage
        float   duty;           //!< normalized fraction of cycle
        SbTime  offset;         //!< time from start of cycle
    }                   *stages;
    SbTime              baseTime;       //!< Starting time for cycle
    SbTime              pauseOffset;    //!< Starting time for cycle

    //! Destructor
    ~SoTimeCounter();

    //! Evaluation method
    virtual void        evaluate();
};

#endif  /* _SO_TIME_COUNTER_ */
