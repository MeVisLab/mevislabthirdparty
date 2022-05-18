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
 |      This file defines the SoVertexShape node class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_VERTEX_SHAPE_
#define  _SO_VERTEX_SHAPE_

#include <Inventor/nodes/SoShape.h>
#include <Inventor/nodes/SoVertexProperty.h>
#include <Inventor/fields/SoSFNode.h>


class SoNormalBundle;
class SoNormalCache;
class SoState;


////////////////////////////////////////////////////////////////////////////////
//! Abstract base class for all vertex-based shape nodes.
/*!
\class SoVertexShape
\ingroup Nodes
This node is the abstract base class for all vertex-based shape
(geometry) nodes. It is used as a
repository for convenience functions for subclasses and to provide a
type identifier to make it easy to determine whether a shape is
vertex-based.
It contains one public field, the SoVertexProperty
field. 


All subclasses of this node draw objects constructed from
vertices.  If the vertexProperty field is non-null and there are
coordinates in the associated vertex property node, then those
coordinates are used.  Otherwise the objects are drawn using the 
current coordinates in the state. The coordinates of the shape
are transformed by the current transformation matrix and are drawn
with the current light model and drawing style.


Subclasses that construct polygons from vertices may not render or
pick correctly if any of their polygons are self-intersecting or
non-planar.


All vertex shape subclasses use the bounding box of the shape to
determine default texture coordinates. The longest dimension of the
bounding box defines the S coordinates, and the next longest defines
the T coordinates. The value of the S coordinate ranges from 0 to 1,
from one end of the bounding box to the other. The T coordinate ranges
between 0 and the ratio of the second greatest dimension of the
bounding box to the greatest dimension.


When a vertex-based shape is picked with an SoRayPickAction, a
detail is always returned. If the shape is composed of faces (such as
SoFaceSet or SoTriangleStripSet), an SoFaceDetail is
returned. If the shape is composed of line segments (such as
SoLineSet), an SoLineDetail is returned. If the shape is
composed of points (such as SoPointSet), an SoPointDetail is
returned. Note that the type of detail returned is not affected by the
current drawing style.


Similarly, each class of vertex-based shape invokes appropriate
callbacks if those callbacks are registered with the
SoCallbackAction. Shapes made of faces invoke triangle callbacks
for each generated triangle. (Faces may be triangulated to create
these triangles.) Shapes made of line segments invoke line segment
callbacks for each segment, and shapes made of points invoke point
callbacks.


The subclass SoIndexedShape is a base class for vertex-based
shapes that index into the current set of coordinates.
The subclass SoNonIndexedShape is a base class for vertex-based
shapes that use the current coordinates in order.

\par See Also
\par
SoIndexedShape, SoNonIndexedShape, SoVertexProperty
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoVertexShape : public SoShape {

    SO_NODE_ABSTRACT_HEADER(SoVertexShape);
    
  public:
      SoSFNode          vertexProperty;

  SoEXTENDER public:
    //! Subclasses may define this method to generate normals to use
    //! when the normal binding is DEFAULT and there aren't enough
    //! normals in the state. This should use the given SoNormalBundle
    //! to generate the normals. Returns TRUE if normals were generated.
    virtual bool        generateDefaultNormals(SoState *state,
                                               SoNormalBundle *nb);

  SoINTERNAL public:
    static void         initClass();

    //! Redefines this to invalidate normal cache
    virtual void        notify(SoNotList *list);

  protected:
    //! Constructor - makes this abstract
    SoVertexShape();

    virtual ~SoVertexShape();

    //! Get the SoVertexProperty from the vertexProperty field, returning NULL if
    //! the contained node is not of type SoVertexProperty.
    SoVertexProperty* getVertexProperty();

    //! Returns TRUE if the shape should be rendered. 
    //! Checks for transparency in vertexProperty node before invoking
    //! render action.
    virtual bool        shouldGLRender(SoGLRenderAction *action);
    
    //! vpCache stores information from one render to the next about
    //! what information needs to be grabbed from the state, etc.
    SoVertexPropertyCache       vpCache;

    //! Sets up a cache to hold normals. This assumes the cache depends
    //! on only the current coordinates, shape hints, and crease angle.
    void                setNormalCache(SoState *state,
                                       int numNormals, const SbVec3f *normals);

    //! Returns the current normal cache, or NULL if there is none
    SoNormalCache       *getNormalCache() const { return normalCache; }

    //! enables vertex array rendering client state and VBO rendering (if supported),
    //! returns true if VBOs are used (MeVis ONLY)
    bool beginVertexArrayRendering(SoGLRenderAction* action);

    //! disables vertex array rendering and VBOs if vboWasUsed is passes as true (MeVis ONLY)
    void endVertexArrayRendering(SoGLRenderAction* action, bool vboWasUsed);

  private:
    //! This allows instances to cache normals that have been generated
    SoNormalCache       *normalCache;
};

#endif /* _SO_VERTEX_SHAPE_ */
