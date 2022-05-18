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
 |      This file defines the SoArray node class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_ARRAY_
#define  _SO_ARRAY_

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/nodes/SoGroup.h>


////////////////////////////////////////////////////////////////////////////////
//! Group node that creates a regular IxJxK array of copies of its children.
/*!
\class SoArray
\ingroup Nodes
This group node traverses its children, in order, several times,
creating a regular 3D array of copies of them. The number of copies
in each of the three directions is specified by fields, as are the
vectors used to separate the copies in each of the three dimensions.


For example, an SoArray node can be used to create a 2x3x4 array
of copies of its children, where the separation vectors between
adjacent copies in the three array dimensions are (1,2,3), (-4,-5,-6),
and (7,8,9), respectively. The base point of the array can be set to
one of several values, as described in the origin field.


Copies are traversed so that the first dimension cycles most quickly,
followed by the second, and then the third. This order is important
because SoArray sets the current switch value to N before
traversing the children for the Nth time (for use with inherited
switch values - see SoSwitch).

\par File Format/Default
\par
\code
Array {
  numElements1 1
  numElements2 1
  numElements3 1
  separation1 1 0 0
  separation2 0 1 0
  separation3 0 0 1
  origin FIRST
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction, SoGetBoundingBoxAction, SoRayPickAction
<BR> Traverses all children for each array element, saving and restoring state before and after each traversal. 
\par
SoSearchAction
<BR> Traverses all children once, setting the inherited switch value to SO_SWITCH_ALL first. 

\par See Also
\par
SoMultipleCopy, SoSwitch
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoArray : public SoGroup {

    SO_NODE_HEADER(SoArray);

  public:

    //! \name Fields
    //@{
    //! Number of elements in 1st direction
    SoSFShort           numElements1;   
    //! Number of elements in 2nd direction
    SoSFShort           numElements2;   
    //! Number of elements in 3rd direction
    SoSFShort           numElements3;   

    //@}

    SoSFVec3f           separation1;    //!< Separation vector in 1st direction
    SoSFVec3f           separation2;    //!< Separation vector in 2nd direction
    SoSFVec3f           separation3;    //!< Separation vector in 3rd direction

    //! Array origin:
    enum Origin {
        FIRST,                          //!< Origin at first element
        CENTER,                         //!< Origin at center of elements
        LAST                            //!< Origin at last element
    };

    SoSFEnum            origin;         //!< Base point

    //! Creates an array node with default settings.
    SoArray();

    //! Overrides default method on SoNode to return FALSE since arrays
    //! are effectively separators
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

  SoINTERNAL public:
    static void         initClass();

  protected:
    virtual ~SoArray();
};

#endif /* _SO_ARRAY_ */
