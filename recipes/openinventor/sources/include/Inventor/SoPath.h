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
 |   $Revision: 1.2 $
 |
 |   Description:
 |      This file contains the definition of the SoPath and SoFullPath
 |      classes, and the related class SoLightweightPath
 |
 |   Author(s)          : Paul S. Strauss, Nick Thompson, Alan Norton
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_PATH_
#define  _SO_PATH_

#include <Inventor/system/SbSystem.h>
#include <Inventor/misc/SoBase.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/SoLists.h>


class SoPathList;
class SoWriteAction;
class SoTempPath;

////////////////////////////////////////////////////////////////////////////////
//! Path that points to a list of hierarchical nodes.
/*!
\class SoPath
\ingroup General
A path represents a scene graph or subgraph.  It contains a list of
pointers to nodes forming a chain from some root to some descendent.
Each node in the chain is a child of the previous node. Paths are used
to refer to some object in a scene graph precisely and unambiguously,
even if there are many instances of the object. Therefore, paths are
returned by both the SoRayPickAction and SoSearchAction.


When an action is applied to a path, only the nodes in the subgraph
defined by the path are traversed. These include: the nodes in the
path chain, all nodes (if any) below the last node in the path, and
all nodes whose effects are inherited by any of these nodes.


SoPath attempts to maintain consistency of paths even when the
structure of the scene graph changes. For example, removing a child
from its parent when both are in a path chain cuts the path chain at
that point, leaving the top part intact. Removing the node to the left
of a node in a path adjusts the index for that node. Replacing a child
of a node when both the parent and the child are in the chain replaces
the child in the chain with the new child, truncating the path below
the new child.


Note that only public children of nodes are accessible from an
SoPath. Nodes like node kits that limit access to their children
may provide other ways to get more information, such as by using the
SoNodeKitPath class.

\par See Also
\par
SoNode, SoRayPickAction, SoSearchAction, SoNodeKitPath
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoPath : public SoBase {

  public:

    //! Constructs an empty path.
    SoPath();

    //! Constructs a path with a hint to length (number of nodes in chain).
    SoPath(int approxLength);

    //! Constructs a path and sets the head node to the given node.
    SoPath(SoNode *node);

    //! Sets head node (first node in chain). The head node must be set before the
    //! append() or push() methods
    //! may be called.
    void                setHead(SoNode *node);

    //! Adds node to end of chain; the node is the \p childIndex'th child of
    //! the current tail node.
    void                append(int childIndex);

    //! Adds node to end of chain; uses the first occurrence of \p childNode
    //! as child of current tail node. If the path is empty, this is
    //! equivalent to
    //! setHead(childNode).
    void                append(SoNode *childNode);

    //! Adds all nodes in \p fromPath's chain to end of chain; the head node
    //! of \p fromPath must be the same as or a child of the current tail node.
    void                append(const SoPath *fromPath);

    //! These allow a path to be treated as a stack; they push a node at the
    //! end of the chain and pop the last node off.
    void                push(int childIndex) { append(childIndex); }
    //! These allow a path to be treated as a stack; they push a node at the
    //! end of the chain and pop the last node off.
    void                pop()                { truncate(getFullLength() - 1); }

    //! These return the first and last nodes in a path chain.
    SoNode *            getHead() const { return nodes[0]; }
    //! These return the first and last nodes in a path chain.
    SoNode *            getTail() const { return (nodes[getLength() - 1]); }

    //! Returns a pointer to the \p i'th node in the chain.
    //! Calling getNode(0) is equivalent to calling getHead().
    SoNode *            getNode(int i) const    { return (nodes[i]); }

    //! Returns a pointer to the \p i'th node.
    //! Passing 0 for \p i returns the tail node.
    SoNode *            getNodeFromTail(int i) const
        { return (nodes[getLength() - 1 - i]); }

    //! Return the index of the
    //! \p i'th node (within its parent) in the chain.
    int                 getIndex(int i) const   { return (indices[i]); }

    //! Return the index of the
    //! \p i'th node (within its parent) in the chain, counting backward from
    //! the tail node. Passing 0 for \p i returns the tail node's index.
    int                 getIndexFromTail(int i) const
        { return (indices[getLength() - 1 - i]); }

    //! Returns length of path chain (number of nodes).
    int                 getLength() const;

    //! Truncates the path chain, removing all nodes from index \p start on.
    //! Calling
    //! truncate(0)
    //! empties the path entirely.
    void                truncate(int start);

    //! Returns TRUE if the node is found anywhere in the path chain.
    bool                containsNode(const SoNode *node) const;

    //! Returns TRUE if the nodes in the chain in the passed path are
    //! contained (in consecutive order) in this path chain.
    bool                containsPath(const SoPath *path) const;

    //! If the two paths have different head nodes, this returns -1.
    //! Otherwise, it returns the path chain index of the last node (starting
    //! at the head) that is the same for both paths.
    int                 findFork(const SoPath *path) const;

    //! Creates and returns a new path that is a copy of some or all of this
    //! path. Copying starts at the given index (default is 0, which is the
    //! head node). A \p numNodes of 0 (the default) means copy all nodes
    //! from the starting index to the end. Returns NULL on error.
    SoPath *            copy(int startFromNodeIndex = 0,
                             int numNodes = 0) const;

    //! Comparison operator: returns TRUE if all nodes in paths are identical
    friend INVENTOR_API bool               operator ==(const SoPath &p1, const SoPath &p2);

    //! Returns type identifier for path instance
    virtual SoType      getTypeId() const;

    //! Returns type identifier for SoPath class
    static SoType       getClassTypeId()        { return classTypeId; }

    //! \see getByName(const SbName &name, SoPathList &list)
    static SoPath *     getByName(const SbName &name);
    //! These methods lookup and return paths with a given name.  Paths are
    //! named by calling their
    //! setName() method
    //! (defined by the SoBase class). The first form returns the last
    //! path that was given that name, either by
    //! setName()
    //! or by reading in a named path from a file. If there is no path with
    //! the given name, NULL will be returned.  The second form appends all
    //! paths with the given name to the given path list and returns the
    //! number of paths that were added. If there are no paths with the given
    //! name, zero will be returned and nothing will be added to the list.
    static int          getByName(const SbName &name, SoPathList &list);

  SoINTERNAL public:
    //! Initializes path class
    static void         initClass();

    //! This is called when a node in the path chain has a child added.
    //! The passed index is the index of the new child
    void                insertIndex(SoNode *parent, int newIndex);

    //! This is called when a node in the path chain has a child removed.
    //! The passed index is the index of the child to be removed
    void                removeIndex(SoNode *parent, int oldIndex);

    //! This is called when a node in the path chain replaces a child.
    //! The passed index is the index of the child to be removed
    void                replaceIndex(SoNode *parent, int index,
                                     SoNode *newChild);

    //! Writes path using given write action
    virtual void        write(SoWriteAction *writeAction) const;

    //! Returns TRUE if the given notification list involves a change
    //! to a node that affects the path. It is assumed that the last
    //! (most recent) node in the list is the head node of the path.
    bool                isRelevantNotification(SoNotList *list) const;

  protected:
    //! Allows internal SoTempPath subclass to forego auditor overhead
    void                auditPath(bool flag)  { doAuditors = flag; }

    ~SoPath();

  private:
    SoNodeList          nodes;          //!< Pointers to nodes
    SbIntList           indices;        //!< Child indices
    int                 numPublic;      //!< How many children are public
    int                 minNumPublic;   //!< Minimum we KNOW are public
    bool                doAuditors;     //!< TRUE if auditors to be maintained
    static SoType       classTypeId;    //!< TypeId of paths

    //! Returns real length of path, including hidden children
    int                 getFullLength() const   { return nodes.getLength(); }

    //! Appends the given node and index to the lists, updating
    //! numPublic as appropriate
    void                append(SoNode *node, int index);

    //! Returns new SoPath; called by SoType::createInstance()
    static void *       createInstance();

    //! Reads stuff into instance of SoPath. Returns FALSE on error.
    virtual bool        readInstance(SoInput *in, unsigned short flags);

    //! Really does a truncate. Flag indicates whether to notify.
    void                truncate(int start, bool doNotify);

friend class SoFullPath;
friend class SoTempPath;
friend class SoAction;
};

INVENTOR_API bool               operator ==(const SoPath &p1, const SoPath &p2);

///////////////////////////////////////////////////////////////////////////////
///
////  \class SoFullPath
///
///  This SoEXTENDER class allows expert users to examine "hidden"
///  children in paths. SoPath allows access from the head node down to
///  the first node with hidden children, but no further. Casting an
///  SoPath to an SoFullPath (which is always guaranteed to be safe)
///  allows you to get at hidden children. SoFullPath overrides some of
///  the methods defined on paths to make this possible.
///
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SoFullPath : public SoPath {

  public:
    //!
    //! Override methods that normally stop at last public child:
    //!

    //! These allow a path to be treated as a stack; they push a node at the
    //! end of the chain and pop the last node off.
    void                pop()           { truncate(getFullLength() - 1); }

    //! These return the first and last nodes in a path chain.
    SoNode *            getTail() const
        { return (nodes[getFullLength() - 1]); }

    //! Returns a pointer to the \p i'th node. Passing 0 for \p i returns the tail node.
    SoNode *            getNodeFromTail(int i) const
        { return (nodes[getFullLength() - 1 - i]); }

    //! Returns the index of the
    //! \p i'th node (within its parent) in the chain, counting backward from
    //! the tail node. Passing 0 for \p i returns the tail node's index.
    int                 getIndexFromTail(int i) const
        { return (indices[getFullLength() - 1 - i]); }

    //! Returns length of path chain (number of nodes).
    int                 getLength() const       { return getFullLength(); }

  private:
    SoFullPath(int approxLength) : SoPath(approxLength) {}
    virtual ~SoFullPath();

friend class SoTempPath;
};



///////////////////////////////////////////////////////////////////////////////
///
////  \class SoLightweightPath
///
///  A SoLightweightPath is a light-weight version of an SoTempPath, intended to
///  be used just to keep track of the current path during traversal.
///  Eventually it is intended to replace SoTempPath (when appropriate 
///  modifications are made to SoDraggers).
///  Unlike SoPath, it keeps only a chain of childIndices and a headnode.
///  The methods implemented are only those needed for traversal.
///
//////////////////////////////////////////////////////////////////////////////


class INVENTOR_API SoLightweightPath  {

  SoINTERNAL public:

    //! Constructor given approximate number of nodes in chain
    SoLightweightPath(int approxLength);
 

    //! Sets head node (first node in chain)
    //! Resulting path has only one node.
    void                setHead(SoNode *node);

    //! Adds node specified by childindex to end of chain. 
    void                append(int childIndex) 
        { indices.append(childIndex);}


    //! Allows path to be treated as a stack: push a node at the end of
    //! the chain and pop the last node off
    void                push(int childIndex)    { append(childIndex); }
    void                push()                  { append(-1);}
    void                pop()           { truncate(getFullLength() - 1); }
    void                setTail(int childIndex) 
                { indices.set(getFullLength()-1,(void *)(size_t)childIndex);}
    SoNode *            getTail()
                { return getNode(getFullLength()-1);}

    //! Returns the first node in a path chain.
    SoNode *            getHead() const { return headNode; }

    //! Returns pointer to ith node in chain
    SoNode *            getNode(int i) const;   

    //! Returns full length of path chain (number of nodes)
    //! note that public/private distinction is ignored.
    int                 getFullLength() const {return indices.getLength();}

    //! Removes all nodes from indexed node on
    void                truncate(int start) { indices.truncate(start);}

    
    //! fills in nodes for a TempPath that is represented by this 
    //! SoLightweightPath.  Called by SoAction::getCurPath(); 
    void                makeTempPath(SoTempPath *tmpPath) const;

    ~SoLightweightPath();

  private:

    SoNode *            headNode;       //!< Pointer to headnode
    SbIntList           indices;        //!< Child indices


  friend class SoAction;
};



#endif /* _SO_PATH_ */
