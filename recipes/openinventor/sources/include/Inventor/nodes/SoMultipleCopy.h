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
 |      This file defines the SoMultipleCopy node class.
 |
 |   Author(s)          : Thad Beier
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_MULTIPLE_COPY_
#define  _SO_MULTIPLE_COPY_

#include <Inventor/fields/SoMFMatrix.h>
#include <Inventor/nodes/SoGroup.h>


////////////////////////////////////////////////////////////////////////////////
//! Group node that traverses multiple times, applying matrices.
/*!
\class SoMultipleCopy
\ingroup Nodes
This group node traverses its children, in order, several times,
applying a different matrix each time. The matrices are stored in the
multiple-value \b matrix  field. Each matrix is concatenated to the
current transformation matrix, and all of the children are traversed.
This allows the user to put multiple copies of the same data in
different locations easily and efficiently.


Traversing the \p Nth child sets the current switch value to \p N, for use
with inherited switch values (see SoSwitch).

\par File Format/Default
\par
\code
MultipleCopy {
  matrix 1 0 0 0
	0 1 0 0
	0 0 1 0
	0 0 0 1
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction, SoGetBoundingBoxAction, SoRayPickAction
<BR> Traverses all children for each matrix, saving and restoring state before and after each traversal. 
\par
SoSearchAction
<BR> Traverses all children once, setting the inherited switch value to <tt>SO_SWITCH_ALL</tt> first. 

\par See Also
\par
SoArray, SoSwitch
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoMultipleCopy : public SoGroup {

    SO_NODE_HEADER(SoMultipleCopy);

  public:
    //! \name Fields
    //@{

    //! Set of matrices to apply to children.
    SoMFMatrix          matrix; 

    //@}

    //! Creates a multiple copy node with default settings.
    SoMultipleCopy();

    //! Overrides default method on SoNode to return FALSE since these
    //! nodes are effectively separators
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
    virtual ~SoMultipleCopy();
};

#endif /* _SO_MULTIPLE_COPY_ */
