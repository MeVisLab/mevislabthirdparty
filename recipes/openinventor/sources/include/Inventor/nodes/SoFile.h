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
 |   $Revision $
 |
 |   Description:
 |      This file defines the SoFile node class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_FILE_
#define  _SO_FILE_

#include <Inventor/misc/SoChildList.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFString.h>

class SoSensor;
class SoFieldSensor;


class SoGroup;

////////////////////////////////////////////////////////////////////////////////
//! Node that reads children from a named file.
/*!
\class SoFile
\ingroup Nodes
This node represents a subgraph that was read from a named input file.
When an SoFile node is written out, just the field containing the
name of the file is written; no children are written out. When an
SoFile is encountered during reading, reading continues from the
named file, and all nodes read from the file are added as hidden
children of the file node.


Whenever the \b name  field changes, any existing children are removed
and the contents of the new file is read in. The file node remembers
what directory the last file was read from and will read the new file
from the same directory after checking the standard list of
directories (see SoInput), assuming the field isn't set to an
absolute path name.


The children of an SoFile node are hidden; there is no way of
accessing or editing them. If you wish to edit the contents of an
SoFile node, you can modify the contents of the named file and
then "touch" the \b name  field (see SoField). Alternatively,
you can use the
copyChildren() method
to get a editable copy of the file node's children. Note that this
does not affect the original file on disk, however.

\par File Format/Default
\par
\code
File {
  name <Undefined file>
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction, SoGetBoundingBoxAction, SoGetMatrixAction, SoHandleEventAction
<BR> Traverses its children just as SoGroup does. 
\par
SoRayPickAction
<BR> Traverses its hidden children, but, if intersections are found, generates paths that end at the SoFile node. 
\par
SoWriteAction
<BR> Writes just the \b name  field and no children. 

\par See Also
\par
SoInput, SoPath
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoFile : public SoNode {

    SO_NODE_HEADER(SoFile);

  public:
    //! \name Fields
    //@{

    //! Name of file from which to read children.
    SoSFString          name;           

    //@}

    //! Creates a file node with default settings.
    SoFile();

    //! Method that returns a copy of the File node's children added to
    //! a group.
    SoGroup             *copyChildren() const;

  SoEXTENDER public:
    //! Traversal methods for all the actions:
    virtual void        doAction(SoAction *action);
    virtual void        callback(SoCallbackAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void        getMatrix(SoGetMatrixAction *action);
    virtual void        handleEvent(SoHandleEventAction *action);
    virtual void        pick(SoPickAction *action);

  SoINTERNAL public:
    static void         initClass();

    //! Returns pointer to children
    virtual SoChildList *getChildren() const;

    //! Copies the contents of the given node into this instance.
    //! This copies without re-reading the file.
    virtual void        copyContents(const SoFieldContainer *fromFC,
                                     bool copyConnections);

  protected:
    //! Reads stuff into instance of SoFile. Returns FALSE on error.
    virtual bool        readInstance(SoInput *in, unsigned short flags);

    virtual ~SoFile();

  private:
    SoChildList         children;

    //! These keep the image and filename fields in sync.
    SoFieldSensor *     nameChangedSensor;
    static void         nameChangedCB(void *, SoSensor *);

    bool                readOK;         //!< FALSE on read error.
};

#endif /* _SO_FILE_ */
