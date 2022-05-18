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
 |      This file contains the definition of the SoNodeKitPath class
 |
 |   Author(s)          : Paul Isaacs, Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_NODE_KIT_PATH_
#define  _SO_NODE_KIT_PATH_

#include <Inventor/SoPath.h>

class SoBaseKit;
class SoSearchAction;


////////////////////////////////////////////////////////////////////////////////
//! Path that points to a list of hierarchical nodekits.
/*!
\class SoNodeKitPath
\ingroup General
SoNodeKitPath is a subclass of SoPath that lets you 
look at nodekits below the top nodekit in the path. Since nodekits have 
hidden children, when you call getTail() on 
a regular path, it returns the top-most
nodekit on the path.  This occurs even though the path might contain extra
internal information leading to a node far deeper in the scene graph.
For example, when picking an object inside an SoSceneKit, the 
<em>regular</em> path would end at the scenekit. But a <em>nodekit</em> 
path would 
continue further down listing the other nodekits below it in the path.


Intermediary (private) nodes between nodekits are not included in the 
nodekit path.

 
Note that there is no constructor for an SoNodeKitPath,  so 
you can not create one. Rather, you cast an (SoPath *) into
an (SoNodeKitPath *),  which returns nodekit-style values from all
the same questions as SoPath.


Also, some methods of SoPath may not be called on an SoNodeKitPath.
Any methods which take a regular SoNode as an argument (except for
setHead()) are not accessible, and replaced by methods that take an 
SoBaseKit as an argument instead.  Methods which allow the programmer to 
refer to the child index of a node beneath its parent are also inaccessible; 
since a SoNodeKitPath only shows nodekits and hides any private parts,
successive nodekits in the path may not actually be parent and child.

\par See Also
\par
SoBaseKit, SoPath, SoRayPickAction, SoSearchAction
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoNodeKitPath : public SoPath {

  public:

    //! Returns length of path chain (number of nodekits).
    int                 getLength() const;

    //! Return the last nodekit in a path chain. Note that 
    //! getHead() is not redefined from SoPath,
    //! since an SoNodeKitPath need not begin with a nodekit; the restriction is
    //! placed only on successive nodes on the path.
    SoNode *            getTail() const;

    //! Returns a pointer to the \p i'th node in the nodekit path.
    SoNode *            getNode(int i) const;

    //! Returns a pointer to the \p i'th nodekit 
    //! in the chain, counting backward from
    //! the tail nodekit. Passing 0 for \p i returns the tail nodekit.
    SoNode *            getNodeFromTail(int i) const;

    //! Truncates the path chain, removing all nodes from index \p start on.
    //! Calling
    //! truncate(0)
    //! empties the path entirely.
    void                truncate(int start);

    //! Pops the last nodekit off the end of the path.
    void                pop();

    //! Adds \p childKit to end of chain; uses first occurrence of \p childKit
    //! as a part within current last nodekit. If the path is empty, this is
    //! equivalent to
    //! setHead(childKit).
    void                append(SoBaseKit *childKit);

    //! Adds all nodekits in \p fromPath's chain to end of chain; the head node
    //! of \p fromPath must be the same as or a child of the current tail node.
    void                append(const SoNodeKitPath *fromPath);

    //! Returns TRUE if the passed nodekit is found anywhere in the path chain.
    bool                containsNode(SoBaseKit *node) const;

    //! If the two paths have different head nodes, this returns -1.
    //! Otherwise, it returns the path chain index of the last nodekit (starting
    //! at the head) that is the same for both paths.
    int                 findFork(const SoNodeKitPath *path) const;

    //! Comparison operator: returns TRUE if all nodes on the nodekit path
    //! are equal
    friend bool operator ==(const SoNodeKitPath &p1, const SoNodeKitPath &p2);

  protected:
    //! Hide the constructor
    SoNodeKitPath(int approxLength) : SoPath(approxLength)      {}
    //! Destructor
    virtual ~SoNodeKitPath();

  private:
    //! This action is used to search for nodes.
    static SoSearchAction *searchAction;

    //! Hide these methods. They make no sense for a SoNodeKitPath.

    //! The methods that take an index or a node are replaced by
    //! methods that take a nodekit argument.
    void                append(int childIndex);
    void                append(SoNode *childNode);
    void                append(const SoPath *fromPath);
    void                push(int childIndex);
    int                 getIndex(int i) const;
    int                 getIndexFromTail(int i) const;
    void                insertIndex(SoNode *parent,int newIndex);
    void                removeIndex(SoNode *parent,int oldIndex);
    void                replaceIndex(SoNode *parent,int index,SoNode *newChild);
};

#endif /* _SO_NODE_KIT_PATH_ */
