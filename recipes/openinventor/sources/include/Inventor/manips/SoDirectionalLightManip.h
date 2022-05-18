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
 |      This file defines a manipulator for a Point light nodes.
 |      It is subclassed from SoPointLight.
 |   Author(s): Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_DIRECTIONAL_LIGHT_MANIP_
#define  _SO_DIRECTIONAL_LIGHT_MANIP_

#include <Inventor/SbLinear.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/sensors/SoFieldSensor.h>



////////////////////////////////////////////////////////////////////////////////
//! Directional light node with 3D interface for editing direction.
/*!
\class SoDirectionalLightManip
\ingroup Manips
SoDirectionalLightManip 
is the base class for all SoDirectionalLight nodes that have a built-in 
3D user interface (this is the only such class provided with the 
Inventor toolkit).
Since it is derived from SoDirectionalLight, any changes to its
fields result in a change of lighting for nodes that
follow it in the scene graph.
In this case, the interface edits the \b direction  field.
Also, the color of the manipulator's geometry will reflect the color of the
light (but you cannot edit the color using this manipulator).


Typically, you will want to replace a regular SoDirectionalLight with an
SoDirectionalLightManip (as when the user selects a light to be edited),
or vice versa (as when the user is done moving the light and the interface
should go away).
Use the
replaceNode() method
to insert a manipulator into a scene graph, and the
replaceManip() method
to remove it when done.


The SoDirectionalLightManip 
utilizes an SoDirectionalLightDragger to provide a 3D interface. 
However, the manipulator differs from the dragger; it lights other objects
in the scene because, as an SoDirectionalLight,
it alters the state. 
The field values and movement of the dragger, on the other hand, affect only 
the dragger itself.
To find out more about how the interface works and what each part will do,
see the reference page for SoDirectionalLightDragger.  The interfaces of the
dragger and the manipulator are identical.


The SoDirectionalLightManip utilizes its dragger by adding it
as a hidden child.  When an action is applied to the manipulator,
such as rendering or handling events, the manipulator first traverses the
dragger, and then the manipulator adds its lighting parameters to the state.
When you click-drag-release over the manipulator, it passes these events down
to the dragger, which moves as a result ("I can't <em>help</em> it, I'm a dragger!").


The manipulator maintains consistency between the fields
of the dragger and its own fields. Let's say you use the mouse to rotate
the <em>dragger</em>. Callbacks ensure that the 
\b direction  field of the <em>manipulator</em> will change by the same 
amount, thus changing the lighting of nodes which follow 
in the scene graph.
Similarly, if you set the \b direction  field of the 
SoDirectionalLightManip, the manipulator will
orient the dragger accordingly. 

 
Because the dragger is a <em>hidden</em> child, you can see the dragger on screen
and interact with it, but the dragger 
does not show up when you write the manipulator to file. Also, any SoPath
will end at the manipulator. (See the Actions section of this reference page for
a complete description of when the dragger is traversed).


If you want to get a pointer to the dragger
you can get it from the manipulator using the 
getDragger() method.  You will need to 
do this if you want to change the geometry of a manipulator, since the
geometry actually belongs to the dragger.

\par File Format/Default
\par
\code
DirectionalLightManip {
  on TRUE
  intensity 1
  color 1 1 1
  direction 0 0 -1
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction, SoGetBoundingBoxAction, SoGetMatrixAction, SoHandleEventAction, SoRayPickAction
<BR> First, traverses the dragger the way an SoGroup would. All draggers place themselves in space, but leave the current transformation unchanged when finished.  Then the SoDirectionalLightManip adds a  directional light to the state  just like its base class, SoDirectionalLight. 
\par
SoSearchAction
<BR> Searches just like an SoDirectionalLight.  Does not search the dragger, which is a hidden child. 
\par
SoWriteAction
<BR> Writes out just like an SoDirectionalLight. Does not write the dragger, which is a hidden child.   If you really need to write valuable information  about the dragger, such as customized geometry, you  can retrieve the dragger with the  getDragger() method and then write  it out separately. 

\par See Also
\par
SoDragger, SoDirectionalLight, SoDirectionalLightDragger, SoPointLightManip, SoSpotLightManip
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoDirectionalLightManip : public SoDirectionalLight {

    SO_NODE_HEADER(SoDirectionalLightManip);

  public:
    //! Constructor.
    SoDirectionalLightManip();

    //! Returns a pointer to the dragger being used by this manipulator.
    //! Given this pointer, you can customize the dragger just like you would
    //! any other dragger.  You can change geometry using 
    //! the setPart() method, or add callbacks using 
    //! the methods found in the SoDragger reference page.
    SoDragger *getDragger();

    //! Replaces the tail of the path with this manipulator.
    //! The tail of the path must be an SoDirectionalLight 
    //! node (or subclass thereof).
    //! If the path has a nodekit, this will try to use
    //! setPart() to insert the manipulator.
    //! Otherwise, the manipulator requires that the
    //! next to last node in the path chain be a group.
    //! 
    //! 
    //! The field values from the directional light node will be copied to
    //! this manipulator, and the light node will be replaced.
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
    //! with the given SoDirectionalLight node.
    //! If the path has a nodekit, this will try to use
    //! setPart() to insert the new node.
    //! Otherwise, the manipulator requires that the
    //! next to last node in the path chain be a group.
    //! 
    //! 
    //! The field values from the manipulator will be copied
    //! to the directional light node, and the manipulator will be replaced.
    //! 
    //! 
    //! The manipulator will not call
    //! ref() or unref()
    //! on the node which is replacing it, nor will it make any
    //! changes to field connections.
    //! The calling process is thus responsible for keeping
    //! track of its own nodes and field connections.
    bool replaceManip(SoPath *p, SoDirectionalLight *newOne ) const;

  SoEXTENDER public:

    //! These functions implement all actions for nodekits.
    //! They first traverse the children, then use the SoDirectionalLight
    //! version of the actions. They traverse first so that the light
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
    static void         initClass();    //!< initialize the class

    virtual SoChildList *getChildren() const;

  protected:

   //! Redefines this to also copy the dragger
   virtual void copyContents(const SoFieldContainer *fromFC,
                             bool copyConnections);

   static void transferFieldValues( const SoDirectionalLight *from, 
                                    SoDirectionalLight *to);

   static void valueChangedCB(void *,SoDragger *);

   SoFieldSensor *directionFieldSensor;
   SoFieldSensor *colorFieldSensor;
   static void fieldSensorCB(void *, SoSensor *);

   void setDragger( SoDragger *newDragger );

   SoChildList *children;

   virtual ~SoDirectionalLightManip();

  private:
    int getNumChildren() const { return (children->getLength()); }
};

#endif /* _SO_DIRECTIONAL_LIGHT_MANIP_ */


