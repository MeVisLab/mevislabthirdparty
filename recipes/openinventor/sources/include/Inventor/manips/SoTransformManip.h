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
 * Copyright (C) 1990,91,92   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.1.1.1 $
 |
 |   Description:
 |      This file defines manipulators for transform nodes.
 |      they are subclassed from SoTransform.
 |
 |   Author(s): Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TRANSFORM_MANIP_
#define  _SO_TRANSFORM_MANIP_

#include <Inventor/SbLinear.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/sensors/SoFieldSensor.h>

////////////////////////////////////////////////////////////////////////////////
//! Base class for all transform Nodes with built-in 3D user interfaces.
/*!
\class SoTransformManip
\ingroup Manips
SoTransformManip 
is the base class for all SoTransform nodes that have a built-in 
3D user interface.
Since it is derived from SoTransform, any changes to its
fields result in the rotation, scaling, and/or translation of nodes that
follow it in the scene graph.


Typically, you will want to replace a regular SoTransform with an
SoTransformManip (as when the user selects an object to be moved),
or vice versa (as when the object is deselected, and the motion interface
should go away).
Use the
replaceNode() method
to insert a manipulator into a scene graph, and the
replaceManip() method
to remove it when done.


Every subclass of SoTransformManip utilizes a dragger of some sort to 
provide a 3D interface. (This class does not have dragger; but all the 
subclasses do.)
However a manipulator differs from a dragger; it
influences other objects in the scene because, as an SoTransform,
it alters the state. 
The fields values and movement of a dragger, on the other hand, affect only 
the dragger itself.


Each SoTransformManip subclass utilizes its dragger by adding it
as a hidden child.  When an action is applied to the manipulator,
such as rendering or handling events, the manipulator first traverses the
dragger, and then the manipulator adds its transformation matrix to the state.
When you click-drag-release over the manipulator, it passes these events down
to the dragger, which moves as a result ("I can't <em>help</em> it, I'm a dragger!").


The manipulator maintains consistency between the fields
of the dragger and its own fields. Let's say you use the mouse to rotate
the <em>dragger</em>. Callbacks insure that the 
\b rotation  field of the <em>manipulator</em> will change by the same 
amount, resulting in the rotation of nodes which follow in the scene graph.
Similarly, if you set any of the SoTransformManip fields
the manipulator will
move the dragger accordingly. You can use this feature
to impose contraints on a manipulator:  If the user moves the manipulator so
that a field value becomes too large, you can set 
the field back to your desired maximum, and the whole thing will move back to 
where you specified.

 
Since each SoTransformManip uses a dragger to provide its interface,
you will generally be told to look at the dragger's reference page for 
details of how it moves and what the different parts are for.
The interface for the dragger and the manipulator will always be exactly the
same.
Usually, a SoTransformManip will surround the
objects that it influences (i.e., those that move along with it).  
This is because the manipulator 
turns on the <em>surroundScale</em> part of its dragger; so the 
dragger geometry expands to envelope the other objects (see the reference
page for SoSurroundScale).  


Because the dragger is a <em>hidden</em> child, you can see the dragger on screen
and interact with it, but the dragger 
does not show up when you write the manipulator to file. Also, any SoPath
will end at the manipulator. (See the Actions section of this reference page 
for a complete description of when the dragger is traversed).


If you want to get a pointer to the dragger
you can get it from the manipulator using the 
getDragger() method.  You will need to 
do this if you want to change the geometry of a manipulator, since the
geometry actually belongs to the dragger.

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction, SoGetBoundingBoxAction, SoGetMatrixAction, SoHandleEventAction, SoRayPickAction
<BR> First, traverses the dragger the way an SoGroup would. All draggers place themselves in space, but leave the current transformation unchanged when finished.  Then the SoTransformManip accumulates a transformation into the  current transformation just like its base class, SoTransform. 
\par
SoSearchAction
<BR> Searches just like an SoTransform.  Does not search the dragger, which is a hidden child. 
\par
SoWriteAction
<BR> Writes out just like an SoTransform. Does not write the dragger, which is a hidden child.   If you really need to write valuable information  about the dragger, such as customized geometry, you  can retrieve the dragger with the  getDragger() method and then write  it out separately. 

\par See Also
\par
SoDragger, SoTransform, SoCenterballManip, SoHandleBoxManip, SoJackManip, SoSurroundScale, SoTabBoxManip, SoTrackballManip, SoTransformBoxManip, SoTransformerManip
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoTransformManip : public SoTransform
{
    SO_NODE_HEADER(SoTransformManip);

  public:

    //! Constructor.
    SoTransformManip();

    //! Returns a pointer to the dragger being used by this manipulator.
    //! Given this pointer, you can customize the dragger just like you would
    //! any other dragger.  You can change geometry using 
    //! the setPart() method, or add callbacks using 
    //! the methods found in the SoDragger reference page.
    SoDragger *getDragger();

    //! Replaces the tail of the path with this manipulator.
    //! The tail of the path must be an SoTransform node (or subclass thereof).
    //! If the path has a nodekit, this will try to use
    //! setPart() to insert the manipulator.
    //! Otherwise, the manipulator requires that the
    //! next to last node in the path chain be a group.
    //! 
    //! 
    //! The field values from the transform node will be copied to
    //! this manipulator, and the transform will be replaced.
    //! 
    //! 
    //! The manipulator will not call
    //! ref()  on the node it is replacing.
    //! The old node will disappear if
    //! it has no references other than from the input path \p p and its parent,
    //! since this manipulator will be replacing it in both of those places.
    //! Nor will the manipulator make any
    //! changes to field connections of the old node.  
    //! The calling process is thus responsible for keeping
    //! track of its own nodes and field connections.
    bool replaceNode( SoPath *p );
    //! Replaces the tail of the path, which must be this manipulator,
    //! with the given SoTransform node.
    //! If the path has a nodekit, this will try to use
    //! setPart() to insert the new node.
    //! Otherwise, the manipulator requires that the
    //! next to last node in the path chain be a group.
    //! 
    //! 
    //! The field values from the manipulator will be copied
    //! to the transform node, and the manipulator will be replaced.
    //! 
    //! 
    //! The manipulator will not call
    //! ref() or unref()
    //! on the node which is replacing it, nor will it make any
    //! changes to field connections.
    //! The calling process is thus responsible for keeping
    //! track of its own nodes and field connections.
    bool replaceManip(SoPath *p, SoTransform *newOne ) const;

  SoEXTENDER public:

    //! These functions implement all actions for nodekits.
    //! They first traverse the children, then use the SoTransform
    //! version of the actions. They traverse first so that the transform
    //! will affect objects which follow it in the tree, but not the
    //! dragger-child.
    virtual void doAction( SoAction *action );
    virtual void callback( SoCallbackAction *action );
    virtual void GLRender( SoGLRenderAction *action );
    virtual void getBoundingBox( SoGetBoundingBoxAction *action );
    virtual void getMatrix(SoGetMatrixAction *action );
    virtual void handleEvent( SoHandleEventAction *action );
    virtual void pick( SoPickAction *action );
    virtual void search( SoSearchAction *action );

  SoINTERNAL public:
    static void initClass();  //!< initialize the class

    virtual SoChildList *getChildren() const;

  protected:

    //! Redefines this to also copy the dragger
    virtual void        copyContents(const SoFieldContainer *fromFC,
                                     bool copyConnections);

   static void transferFieldValues( const SoTransform *from, SoTransform *to);

   static void valueChangedCB(void *,SoDragger *);

   SoFieldSensor *rotateFieldSensor;
   SoFieldSensor *translFieldSensor;
   SoFieldSensor *scaleFieldSensor;
   SoFieldSensor *centerFieldSensor;
   SoFieldSensor *scaleOrientFieldSensor;
   static void fieldSensorCB(void *, SoSensor *);

   virtual void setDragger( SoDragger *newDragger );

   SoChildList *children;

   virtual ~SoTransformManip();

  private:
    int getNumChildren() const { return (children->getLength()); }
};    

#endif  /* _SO_TRANSFORM_MANIP_ */
