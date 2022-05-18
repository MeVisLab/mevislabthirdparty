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
 |   Description:
 |      This file defines the SoSwitch node class.
 |
 |   Author(s)          : Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SWITCH_
#define  _SO_SWITCH_

#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/nodes/SoGroup.h>


#define SO_SWITCH_NONE          (-1)    /* Don't traverse any children  */
#define SO_SWITCH_INHERIT       (-2)    /* Inherit value from state     */
#define SO_SWITCH_ALL           (-3)    /* Traverse all children        */

////////////////////////////////////////////////////////////////////////////////
//! Group node that traverse one chosen child.
/*!
\class SoSwitch
\ingroup Nodes
This group node usually traverses only one or none of its children.
It implements an operation similar to the <tt>switch</tt> statement in C.
One can use this node to switch on and off the effects of some
properties or to switch between different properties.


The \b whichChild  field specifies the index of the child to traverse,
where the first child has index 0.


A value of <tt>SO_SWITCH_NONE</tt> (-1, the default) means do not traverse
any children. A value of <tt>SO_SWITCH_INHERIT</tt> (-2) allows the index
to be inherited from a previously-encountered SoSwitch node or
from certain other nodes (such as SoArray or SoMultipleCopy)
that set the switch value. A value of <tt>SO_SWITCH_ALL</tt> (-3) traverses
all children, making the switch behave exactly like a regular
SoGroup.

\par File Format/Default
\par
\code
Switch {
  whichChild -1
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction, SoGetBoundingBoxAction, SoGetMatrixAction, SoHandleEventAction, SoRayPickAction
<BR> Traverses the chosen child or children. 
\par
SoSearchAction
<BR> If the action's Searching-All flag is set, always traverses all children.  Otherwise, traverses just the chosen child or children. 

\par See Also
\par
SoArray, SoLevelOfDetail, SoMultipleCopy, SoPathSwitch
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoSwitch : public SoGroup {

    SO_NODE_HEADER(SoSwitch);

  public:
    //! \name Fields
    //@{

    //! Index of the child to traverse, or one of <tt>SO_SWITCH_NONE</tt>,
    //! <tt>SO_SWITCH_INHERIT</tt>, or <tt>SO_SWITCH_ALL</tt>.
    SoSFInt32           whichChild;     

    //@}

    //! Creates a switch node with default settings.
    SoSwitch();

    //! Constructor that takes approximate number of children.
    SoSwitch(int nChildren);

    //! Overrides method in SoNode to return FALSE if there is no
    //! selected child or the selected child does not affect the state.
    virtual bool        affectsState() const;

  SoEXTENDER public:
    //! Implement actions
    virtual void        doAction(SoAction *action);
    virtual void        callback(SoCallbackAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        pick(SoPickAction *action);
    virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void        handleEvent(SoHandleEventAction *action);
    virtual void        getMatrix(SoGetMatrixAction *action);
    virtual void        search(SoSearchAction *action);
    virtual void        write(SoWriteAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:

    virtual ~SoSwitch();

  private:
    //! Traverses correct child. If matchIndex >=0, child index must match
    void                doChild(SoAction *action, int matchIndex = -1);
};

#endif /* _SO_SWITCH_ */
