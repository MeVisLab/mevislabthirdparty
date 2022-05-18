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
 |      This file defines the SoAnnotation node class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_ANNOTATION_
#define  _SO_ANNOTATION_

#include <Inventor/system/SbSystem.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/fields/SoSFBool.h>

////////////////////////////////////////////////////////////////////////////////
//! Annotation group node.
/*!
\class SoAnnotation
\ingroup Nodes
This group node delays rendering its children until all other nodes
have been traversed, turning off depth buffer comparisons first. The
result is that the shapes under the annotation node are rendered on
top of the rest of the scene. This node is derived from
SoSeparator, so it saves and restores traversal state for all
actions.


Note that if more than one annotation node is present in a graph, the
order in which they are traversed determines the stacking order em
later nodes are rendered on top of earlier ones. Also note that since
depth buffer comparisons are disabled, complex 3D objects may not be
rendered correctly when used under annotation nodes.


Also note that the annotation node does nothing special when picking
along a ray. That is, it does not modify the sorting order of
intersected objects based on which ones are under annotation nodes. If
your application uses annotation nodes and you want to ensure that
objects under them are picked "in front of" other objects, you can
tell the pick action that you want to pick all objects along the ray
and then scan through the paths in the resulting picked point
instances to see if any of them passes through an annotation
node. Your program can then decide what to do in such a case.

\par File Format/Default
\par
\code
Annotation {
  renderCaching AUTO
  boundingBoxCaching AUTO
  renderCulling AUTO
  pickCulling AUTO
}
\endcode

\par Action Behavior
\par
SoGLRenderAction
<BR> Delays rendering its children until all other nodes have been traversed, turning off depth buffer comparisons first. 
\par
SoCallbackAction, SoGetBoundingBoxAction, SoGetMatrixAction, SoRayPickAction, SoSearchAction
<BR> Same as SoSeparator 

*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoAnnotation : public SoSeparator {

    SO_NODE_HEADER(SoAnnotation);

  public:

    //! Creates an annotation node with default settings.
    SoAnnotation();

    //@{! Fields

    //! If true, the depth buffer is cleared before rendering the children
    SoSFBool clearDepthBuffer;

    //! If true, the depth buffer is disabled during rendering of the children
    SoSFBool disableDepthBuffer;

    //@}

  SoEXTENDER public:
    //! Implement actions
    virtual void        GLRenderBelowPath(SoGLRenderAction *action);
    virtual void        GLRenderInPath(SoGLRenderAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    //! Destructor
    virtual ~SoAnnotation();
};

#endif /* _SO_ANNOTATION_ */
