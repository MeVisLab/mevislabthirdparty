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
 * Copyright (C) 1990-93   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |
 |   $Revision: 1.1.1.1 $
 |
 |   Description:
 |      This file defines the SoSelection node class.
 |
 |   Classes:   SoSelection
 |
 |   Author(s)  : David Mott, Thad Beier
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SELECTION_
#define  _SO_SELECTION_

#include <Inventor/SbColor.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/fields/SoSFBool.h>

class SoCallbackList;
class SoEvent;
class SoHandleEventAction;
class SoSearchAction;
class SoPickedPoint;
class SoPickedPointList;
class SoTypeList;
class SoSelection;
class SoPath;

//! callback function prototypes
typedef INVENTOR_API void SoSelectionPathCB(void *userData, SoPath *path);
typedef INVENTOR_API void SoSelectionClassCB(void *userData, SoSelection *sel);
typedef INVENTOR_API SoPath * SoSelectionPickCB(void *userData, const SoPickedPoint *pick);


////////////////////////////////////////////////////////////////////////////////
//! Manages a list of selected objects.
/*!
\class SoSelection
\ingroup General
SoSelection defines a node which can be inserted into a scene graph
and will generate and manage a selection list from picks on any node
in the subgraph below it. Nodes are selected based on a current
selection policy.
Callback functions report back to the application when a path has been
selected or deselected. The selection list can also be managed
programmatically.


When handling events, SoSelection makes sure that the mouse release
event was over the same object as the mouse press event before
changing the list of selected objects. This allows users to mouse
down on an object, change their mind and move the cursor off the object,
then release the mouse button without altering the selection.


The selection can be highlighted automatically through the SoQtRenderArea,
or the application can provide custom highlights. Please see the
chapter "Creating a Selection Highlight Style" in the
<em>Inventor Toolmaker</em>.

\par File Format/Default
\par
\code
Selection {
  renderCaching AUTO
  boundingBoxCaching AUTO
  renderCulling AUTO
  pickCulling AUTO
  policy SHIFT
}
\endcode

\par See Also
\par
SoEventCallback, SoQtRenderArea, SoBoxHighlightRenderAction, SoLineHighlightRenderAction
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoSelection : public SoSeparator {

    SO_NODE_HEADER(SoSelection);

  public:

    //! Creates a selection node with the default settings.
    SoSelection();
    //! Constructor that specifies the
    //! approximate number of children.
    SoSelection(int nChildren);
    
    //!
    //! Selection policy
    //! ----------------

    //! Default selection policy is SoSelection::SHIFT.
    enum Policy {
        //! left mouse pick on object clears selection, then selects object.
        //! left mouse pick on nothing clears selection.
        //! only one object may be selected at a time. 
        SINGLE,
        
        //! left mouse pick on object toggles its selection status.
        //! left mouse pick on nothing does nothing.
        //! multiple objects may be selected.
        TOGGLE,
        
        //! when shift key is down, selection policy is TOGGLE.
        //! when shift key is up, selection policy is SINGLE.
        //! multiple objects may be selected.
        SHIFT
    };

    //! \name Fields
    //@{

    //! Selection policy that is followed in response to user interaction.
    //! This can be set to <tt>SoSelection::SINGLE</tt>, <tt>SoSelection::TOGGLE</tt>, or
    //! <tt>SoSelection::SHIFT</tt>.
    SoSFEnum            policy; 

    //! If on, only perform selection on a single click, and not after the mouse has been
    //! dragged from the initial mouse down position. This serves a similar purpose as
    //! pickMatching, but mixes better with other interactions.
    SoSFBool            selectOnlyOnClick;

    //@}

    //! Select the passed path by adding it to the selection list.
    //! The selection node must lie in the path. The path is copied and
    //! truncated such that the selection node is the head of the path.
    //! If the selection node does not lie in the path, the selection list
    //! remains unchanged.
    //! This method ignores the current selection policy.
    void                select(const SoPath *path);    

    //! Select the passed node by creating a path to it, and adding
    //! the path to the selection list by calling
    //! select(path). If there is more than one
    //! instance of \p node beneath the selection node, the created
    //! path will be the first instance found.
    void                select(SoNode *node);

    //! Deselect the passed path by removing it from the selection list.
    void                deselect(const SoPath *path);
    //! Deselect a path by removing it from the selection list.
    //! The argument \p which specifies which path in the list to be removed.
    void                deselect(int which);

    //! Deselect the passed node by creating a path to it, and removing
    //! the node from the selection list by calling
    //! deselect(path). If there is more than one
    //! instance of \p node beneath the selection node, the created
    //! path will be the first instance found.
    void                deselect(SoNode *node);

    //! Toggle the selection status of the passed path em if the path is in
    //! the selection list, it is removed; if not in the list, it is added.
    void                toggle(const SoPath *path);

    //! Toggle the selection status of the passed node by creating a path to it,
    //! then calling toggle(path).
    //! If there is more than one
    //! instance of \p node beneath the selection node, the created
    //! path will be the first instance found.
    void                toggle(SoNode *node);

    //! returns TRUE if the path is selected
    bool                isSelected(const SoPath *path) const;
    //! This convenience version of deselect will search for the first instance
    //! of the passed node under this selection node, and return whether
    //! that path is selected.
    bool                isSelected(SoNode *node) const;

    //! Deselect all paths in the selection list, that is, clear the list.
    void                deselectAll();

    //! Return the number of paths in the selection list.
    int                 getNumSelected() const  { return selectionList.getLength(); }
    //! Return the list of selected paths.
    const SoPathList    *getList() const { return &selectionList; }
    //! Return the \p ith path in the selection list.
    SoPath              *getPath(int index) const;

    //! [] indexes into the selection list
    SoPath *            operator [](int i) const
                        { return getPath(i); }

    //! The selection callbacks are invoked every time an object is selected, whether
    //! it be from user interaction or from method call.
    //! The callbacks are invoked after the object has been added to the selection list.
    void    addSelectionCallback(SoSelectionPathCB *f, void *userData = NULL);
    //! Remove selection callback.
    void    removeSelectionCallback(SoSelectionPathCB *f, void *userData = NULL);

    //! The deselection callbacks are invoked every time an object is deselected, whether
    //! it be from user interaction or from method call.
    //! This is invoked after the object has been removed from the selection list.
    void    addDeselectionCallback(SoSelectionPathCB *f, void *userData = NULL);
    //! Remove deselection callback.
    void    removeDeselectionCallback(SoSelectionPathCB *f, void *userData = NULL);

    //! The start callbacks are invoked when the user has initiated an interactive
    //! change to the selection list (by picking objects). This will be followed by
    //! invocations of the
    //! select and/or deselect callbacks, finally followed by each finish callback.
    //! A start callback can be used, for instance, to save the current selection
    //! for later restoration (e.g. undo/redo). The start callbacks are not called
    //! when the selection list is changed programmatically.
    void    addStartCallback(SoSelectionClassCB *f, void *userData = NULL);
    //! Remove the start callback.
        void    removeStartCallback(SoSelectionClassCB *f, void *userData = NULL);

    //! The finish callbacks are invoked when the user has finished interactively
    //! changing the selection list (by picking objects).
    //! This was preceded by an invocation of each start
    //! callback, and invocations of the select and/or deselect callbacks.
    //! The finish callbacks are not called
    //! when the selection list is changed programmatically.
    void    addFinishCallback(SoSelectionClassCB *f, void *userData = NULL);
    //! Remove finish callback.
    void    removeFinishCallback(SoSelectionClassCB *f, void *userData = NULL);

    //! The pick filter callback is invoked when a pick has occurred
    //! and the selection node is about
    //! to change the selection list.
    //! The callback function returns the
    //! path that the selection node should use when selecting and deselecting.
    //! If no pick callback is registered (the default), the selection node
    //! will use the path returned by
    //! SoPickedPoint::getPath() on the picked
    //! point associated with the event being processed.
    //! The returned path should not be ref'd - selection will ref() and 
    //! unref() it.
    //! (See SoPath::unrefNoDelete().)
    //! 
    //! 
    //! Note that a picked object may or may not be a child of the selection
    //! node. A selection node will only select paths that pass through it.
    //! Possible return values from the callback:
    //! 
    //! 
    //! [a] NULL em selection behaves as if nothing was picked
    //! (i.e. for SINGLE and SHIFT policies, this clears
    //! the selection list). Handle event action traversal
    //! halts.
    //! 
    //! 
    //! [b] Path em this path will be selected/deselected according
    //! to the selection policy (it must lie under the
    //! selection node). Handle event action traversal halts.
    //! 
    //! 
    //! [c] Path containing <em>only</em> the selection node em apply the
    //! selection policy as if nothing was picked. Handle
    //! event action traversal continues.
    //! 
    //! 
    //! [d] Path not passing through the selection node em selection
    //! ignores this pick event and no change is made to the
    //! selection list. Handle event action traversal continues.
    //! 
    //! 
    //! A simple way to tell selection to ignore the pick is to return
    //! an SoPath with no nodes in it. (i.e. return new SoPath;)
    //! Selection will always ref the path returned by the callback, make a
    //! copy of the path, then unref the path.
    //! 
    //! 
    //! The \p callOnlyIfSelectable argument, when set to TRUE, means the pick
    //! callback function will only be invoked on picks which pass through
    //! the selection node. When FALSE, all picks will be passed to the callback
    //! whether they pass through the selection or not.
    void    setPickFilterCallback(
                SoSelectionPickCB *f,
                void *userData = NULL, 
                bool callOnlyIfSelectable = TRUE); 

    //! SoSelection will pick once on mouse down
    //! and once on mouse up, and make sure the picks match before changing
    //! the selection list. This allows the user to pick down on an object,
    //! change their mind and drag off the object, release the mouse button
    //! and not affect the selection. Pass TRUE to enable this behavior.
    //! Pass FALSE to disable this, meaning whatever is picked on a mouse
    //! release is added to/removed from the selection list.
    //! Default is pick-matching on.
    void    setPickMatching(bool pickTwice) { pickMatching = pickTwice; }
    //! Returns if pick matching is on.
    bool    isPickMatching() const { return pickMatching; }
    //! Returns if pick matching is on.
    bool    getPickMatching() const { return pickMatching; }
    
  SoINTERNAL public:
    //! Selection notify callbacks - invoked whenever the selection changes.
    //! Used by the render area to redraw for selection highlighting.
    void   addChangeCallback(SoSelectionClassCB *f, void *userData = NULL);
    void   removeChangeCallback(SoSelectionClassCB *f, void *userData = NULL);

  //! Internal:
    static void         initClass();

  protected:
    //! List of paths of selected objects
    SoPathList          selectionList;

    //! Selection callback lists
    SoCallbackList      *selCBList;
    SoCallbackList      *deselCBList;
    SoCallbackList      *startCBList;
    SoCallbackList      *finishCBList;
    
    //! Pick filter is a single callback function, not a list
    SoSelectionPickCB   *pickCBFunc;
    void                *pickCBData;
    bool                callPickCBOnlyIfSelectable;
    
    //! Change callbacks
    SoCallbackList      *changeCBList;
    
    //! Mouse down picked path
    SoPath              *mouseDownPickPath;
    bool                pickMatching;

    bool                abortSelection;

    SbVec2s             mouseDownPosition;

    //! Selection policies (shiftSelection is a combination of these)
    //! invokeSelectionPolicy() is called from handleEvent() - for a customized
    //! selection policy, either derive a class and write a new handleEvent()
    //! method, or use an SoEventCallback node placed such that it receives
    //! events before the selection node.
    void                invokeSelectionPolicy(SoPath *path, bool shiftDown);
    void                performSingleSelection(SoPath *path);
    void                performToggleSelection(SoPath *path);
    
    //! This copies the path so the copy is rooted by 'this'.
    //! Returns NULL if 'this' not found in the passed path.
    SoPath              *copyFromThis(const SoPath *path) const;

    //! Get path from picked point, calls callbacks
    SoPath              *getPickedPath(const SoPickedPoint* pickedPoint);
    
    //! addPath() assumes the path is rooted by 'this'
    void                addPath(SoPath *path);
    void                removePath(int which);
    
    //! This locates path in the selection list. The head of this path
    //! does not necessarily have to be 'this'.
    int                 findPath(const SoPath *path) const;

    //! Traversal routine for SoHandleEventAction - this will call
    //! action->setHandled() if the event is handled
    virtual void        handleEvent(SoHandleEventAction *action);
    
    //! Destructor removes everything from the list.
    ~SoSelection();

  private:

    //! This action is used to search for nodes.
    static SoSearchAction *searchAction;

    //! this is called from the two constructors.
    void                constructorCommon();  
};



#endif /* _SO_SELECTION_ */
