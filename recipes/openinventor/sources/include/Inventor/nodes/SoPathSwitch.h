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
 |      This file defines the SoPathSwitch node class.
 |
 |   Author(s)          : Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_PATH_SWITCH_
#define  _SO_PATH_SWITCH_

#include <Inventor/fields/SoSFPath.h>
#include <Inventor/nodes/SoGroup.h>


////////////////////////////////////////////////////////////////////////////////
//! Group node that traverses only when traversed along a given path.
/*!
\class SoPathSwitch
\ingroup Nodes
SoPathSwitch is a group node that traverses its children only if
the current traversal path matches the SoPath in the \b path 
field. This can be used, for example, to affect only one instance of a
subgraph. The \b path  field contains the path up to (but not
including) the SoPathSwitch. The path need not go all the way back
to the root; if it does not, then only the number of ancestors that
are in the path are compared to see if the children should be
traversed. A NULL path means that the children are never traversed.

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction, SoGetBoundingBoxAction, SoRayPickAction, SoHandleEventAction
<BR> Traverses the children if the paths match. 

\par See Also
\par
SoPath, SoSwitch
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoPathSwitch : public SoGroup {

    SO_NODE_HEADER(SoPathSwitch);

  public:
    //! \name Fields
    //@{

    //! The path that must match the current traversal path.
    SoSFPath            path;           

    //@}

    //! Creates a path switch node with default settings.
    SoPathSwitch();

    //! Constructor that takes approximate number of children.
    SoPathSwitch(int nChildren);

  SoEXTENDER public:
    //! Implement actions
    virtual void        doAction(SoAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        pick(SoPickAction *action);
    virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void        handleEvent(SoHandleEventAction *action);
    virtual void        getMatrix(SoGetMatrixAction *action);
    virtual void        search(SoSearchAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    virtual ~SoPathSwitch();

  private:

    //! Checks for match of path with current path
    bool                matchesPath(const SoPath *switchPath,
                                    const SoPath *currentPath) const;
};

#endif /* _SO_PATH_SWITCH_ */
