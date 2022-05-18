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
 |      Defines the SoSearchAction class
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SEARCH_ACTION_
#define  _SO_SEARCH_ACTION_

#include <Inventor/system/SbSystem.h>
#include <Inventor/actions/SoSubAction.h>


////////////////////////////////////////////////////////////////////////////////
//! Searches for nodes in a scene graph.
/*!
\class SoSearchAction
\ingroup Actions
This class is used to search scene graphs for specific nodes, nodes of
a specific type, nodes with a specific name, or any combination of
these. It can search for just the first or last node satisfying the
criteria or for all such nodes. The actions return paths to each node
found.


Note that by default nodekits do not search their children when a search 
action is applied.  The man page for SoBaseKit discusses the methods
SoBaseKit::isSearchingChildren() and
SoBaseKit::setSearchingChildren(),
which allow you to query and control this behavior.

\par See Also
\par
SoPath, SoBaseKit
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoSearchAction : public SoAction {

    SO_ACTION_HEADER(SoSearchAction);

  public:

    //! Enum that defines the search criterion:
    enum LookFor {
        NODE = 0x01,    //!< Looking for a particular node
        TYPE = 0x02,    //!< Looking for a particualr type of node
        NAME = 0x04     //!< Looking for a node with a particular name
    };

    //! Enum that defines which paths to return:
    enum Interest {
        FIRST,          //!< Return only the first path found
        LAST,           //!< Return only the last path found
        ALL             //!< Return all paths found
    };

    //! Constructor.
    SoSearchAction();

    //! Destructor
    virtual ~SoSearchAction();

    //! Resets options back to default values; clears list of returned paths.
    //! This can be used to apply the action again with a different set of
    //! search criteria.
    void                reset();

    //! Sets what to look for; \p what is a bitmask of <tt>LookFor</tt>
    //! enum values. Default is no flags at all. Note that setting a node,
    //! type, and/or name to search for activates the relevant flag, so you
    //! may never need to call this method directly.
    void                setFind(int what)       { lookingFor = what; }
    //! Returns what to look for.
    //! \see setFind
    int                 getFind()               { return lookingFor; }

    //! Returns the node to search for.
    SoNode *            getNode() const         { return node; }
    //! Sets the node to search for.
    void                setNode(SoNode *n);

    //! Gets the node type to search for. If \p derivedIsOk is TRUE,
    //! a node that is of a type that is derived from \p t will pass this
    //! search criterion.
    SoType              getType(bool &derivedIsOk) const
        { derivedIsOk = derivedOk; return type; }       
    //! Sets the node type to search for. If \p derivedIsOk is TRUE,
    //! a node that is of a type that is derived from \p t will pass this
    //! search criterion.
    void                setType(SoType t, bool derivedIsOk = TRUE);

    //! Sets/returns the name of the node to search for.
    const SbName &      getName() const { return name; }
    //! Sets/returns the name of the node to search for.
    void                setName(const SbName &n);

    //! Sets/returns which paths to return. Default is FIRST.
    Interest            getInterest() const     { return interest; }
    //! Sets/returns which paths to return. Default is FIRST.
    void                setInterest(Interest i) { interest = i;    }

    //! \see setSearchingAll
    bool                isSearchingAll() const  { return searchingAll; }
    //! Sets/returns whether searching uses regular traversal or whether it
    //! traverses every single node. For example, if this flag is FALSE, an
    //! SoSwitch node will traverse only the child or children it would
    //! normally traverse for an action. If the flag is TRUE, the switch would
    //! always traverse all of its children. The default is FALSE.
    void                setSearchingAll(bool flag) { searchingAll = flag; }

    //! Returns resulting path, or NULL if no path was found. This should be
    //! used if the interest is FIRST or LAST.
    SoPath *            getPath() const         { return retPath; }

    //! Returns resulting path list. This should be used if the interest is ALL.
    SoPathList &        getPaths()              { return retPaths; }

  SoEXTENDER public:
    //! Sets/returns whether action has found all desired nodes
    void                setFound()              { setTerminated(TRUE); }
    bool                isFound() const         { return hasTerminated(); }

    //! Sets found path or adds to list of found paths (depending on interest)
    void                addPath(SoPath *path);

  SoINTERNAL public:
    static void         initClass();

    //! This flag is used by the SoSwitch node, which must return a
    //! different result from its 'affectsState' method when called
    //! during a SearchAction that is searching all children.
    static bool         duringSearchAll;

  protected:
    //! Initiates action on graph
    virtual void        beginTraversal(SoNode *node);

  private:

    SoType              type;           //!< Node type id to search for
    bool                derivedOk;      //!< Exact match or derived ok
    SoNode              *node;          //!< Node to search for
    SbName              name;           //!< Name of node to search for   
    int                 lookingFor;     //!< What to search for
    Interest            interest;       //!< Which paths to return
    bool                searchingAll;   //!< Search all children or follow 
                                        //! normal traversal rules.
    SoPath              *retPath;       //!< Found node (if interest != ALL)
    SoPathList          retPaths;       //!< Found nodes (if interest == ALL)
};

#endif /* _SO_SEARCH_ACTION_ */
