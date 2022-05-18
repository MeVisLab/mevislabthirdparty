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
 |      This file defines the SoGroup node class.
 |
 |   Author(s)          : Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_GROUP_
#define  _SO_GROUP_

class SoChildList;
#include <Inventor/nodes/SoSubNode.h>


////////////////////////////////////////////////////////////////////////////////
//! Base class for all group nodes.
/*!
\class SoGroup
\ingroup Nodes
This node defines the base class for all group nodes. SoGroup is a
node that contains an ordered list of child nodes. The ordering of the
child nodes represents the traversal order for all operations (for
example, rendering, picking, and so on). This node is simply a
container for the child nodes and does not alter the traversal state
in any way. During traversal, state accumulated for a child is passed
on to each successive child and then to the parents of the group
(SoGroup does not push or pop traversal state as SoSeparator
does).

\par File Format/Default
\par
\code
Group {
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction, SoGetBoundingBoxAction, SoHandleEventAction, SoRayPickAction
<BR> Traverses each child in order. 
\par
SoGetMatrixAction
<BR> Does nothing unless the group is in the middle of the path chain the action is being applied to. If so, the children up to and including the next node in the chain are traversed. 
\par
SoSearchAction
<BR> If searching for group nodes, compares with this group. Otherwise, continues to search children. 
\par
SoWriteAction
<BR> Writes out the group node. This method also deals with any field data associated with the group node. As a result, this method is used for most subclasses of SoGroup as well. 

\par See Also
\par
SoArray, SoLevelOfDetail, SoMultipleCopy, SoPathSwitch, SoSeparator, SoSwitch
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoGroup : public SoNode {

    SO_NODE_HEADER(SoGroup);

  public:

    //! Creates an empty group node.
    SoGroup();

    //! Constructor that takes approximate number of children. Space is
    //! allocated for pointers to the children, but the group does not contain
    //! any actual child nodes.
    SoGroup(int nChildren);

    //! Adds a child as last one in group.
    void                addChild(SoNode *child);

    //! Adds a child so that it becomes the one with the given index.
    void                insertChild(SoNode *child, int newChildIndex);

    //! Returns pointer to child node with the given index.
    //! Does range checking an returns NULL if index is outside of [0,getNumChildren()-1]
    SoNode *            getChild(int index) const;

    //! Finds index of given child within group. Returns -1 if not found.
    int                 findChild(const SoNode *child) const;

    //! Returns number of children.
    int                 getNumChildren() const;

    //! Removes child with given index from group.
    void                removeChild(int index);

    //! Removes first instance of given child from group.
    void                removeChild(SoNode *child)
        { removeChild(findChild(child)); }

    //! Removes all children from group.
    void                removeAllChildren();

    //! Replaces child with given index with new child.
    void                replaceChild(int index, SoNode *newChild);

    //! Replaces first instance of given child with new child.
    void                replaceChild(SoNode *oldChild, SoNode *newChild)
        { replaceChild(findChild(oldChild), newChild); }

  SoEXTENDER public:
    //! Implement actions
    virtual void        doAction(SoAction *action);
    virtual void        callback(SoCallbackAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void        getMatrix(SoGetMatrixAction *action);
    virtual void        handleEvent(SoHandleEventAction *action);
    virtual void        pick(SoPickAction *action);
    virtual void        search(SoSearchAction *action);
    virtual void        write(SoWriteAction *action);

  SoINTERNAL public:
    static void         initClass();

    //! Returns pointer to children
    virtual SoChildList *getChildren() const;

  protected:
    SoChildList         *children;

    //! Reads stuff into instance of SoGroup. Returns FALSE on error
    virtual bool        readInstance(SoInput *in, unsigned short flags);

    //! Reads just the children into instance of SoGroup. Returns FALSE on error
    virtual bool        readChildren(SoInput *in);

    virtual ~SoGroup();

    //! Copies the contents of the given node into this instance
    virtual void        copyContents(const SoFieldContainer *fromFC,
                                     bool copyConnections);
};

#endif /* _SO_GROUP_ */
