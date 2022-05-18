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
 |      This file defines the SoShapeHints node class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SHAPE_HINTS_
#define  _SO_SHAPE_HINTS_

#include <Inventor/elements/SoGLShapeHintsElement.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoSubNode.h>


////////////////////////////////////////////////////////////////////////////////
//! Node that provides hints about shapes.
/*!
\class SoShapeHints
\ingroup Nodes
By default, Inventor assumes very little about the shapes it renders.
You can use the SoShapeHints node to indicate that vertex-based
shapes (those derived from SoVertexShape) are solid, contain
ordered vertices, or contain convex faces.  For fastest rendering,
specify SOLID, COUNTERCLOCKWISE, CONVEX shapes.


These hints allow Inventor to optimize certain rendering features.
Optimizations that may be performed include enabling back-face culling
and disabling two-sided lighting. For example, if an object is solid
and has ordered vertices, Inventor turns on backface culling and turns
off two-sided lighting. If the object is not solid but has ordered
vertices, it turns off backface culling and turns on two-sided
lighting. In all other cases, both backface culling and two-sided
lighting are off.


The SoShapeHints node also affects how default normals are
generated.  When a node derived from SoVertexShape has to generate
default normals, it uses the \b creaseAngle  field to determine which
edges should be smooth-shaded and which ones should have a sharp
crease.  The crease angle is the angle between surface normals on
adjacent polygons. For example, a crease angle of .5 radians
means that an edge between two adjacent polygonal faces
will be smooth shaded if the normals to the two faces form an angle
that is less than .5 radians (about 30 degrees). Otherwise, it will
be faceted.  Normal generation is fastest when the creaseAngle is 0
(the default), producing one normal per facet.  A creaseAngle of pi
produces one averaged normal per vertex.

\par File Format/Default
\par
\code
ShapeHints {
  vertexOrdering UNKNOWN_ORDERING
  shapeType UNKNOWN_SHAPE_TYPE
  faceType CONVEX
  creaseAngle 0
  useVBO TRUE
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction, SoRayPickAction, SoGetBoundingBoxAction
<BR> Sets the state to contain the hints; sets up optimizations based on the hints. 

\par See Also
\par
SoVertexShape
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoShapeHints : public SoNode {

    SO_NODE_HEADER(SoShapeHints);

  public:
    //! Hints about ordering of face vertices: if ordering of all
    //! vertices of all faces is known to be consistent when viewed
    //! from "outside" shape or not.
    enum VertexOrdering {
        UNKNOWN_ORDERING = SoShapeHintsElement::UNKNOWN_ORDERING,
        CLOCKWISE        = SoShapeHintsElement::CLOCKWISE,
        COUNTERCLOCKWISE = SoShapeHintsElement::COUNTERCLOCKWISE
    };

    //! Hints about entire shape: if shape is known to be a solid
    //! object, as opposed to a surface.
    enum ShapeType {
        UNKNOWN_SHAPE_TYPE = SoShapeHintsElement::UNKNOWN_SHAPE_TYPE,
        SOLID              = SoShapeHintsElement::SOLID
    };

    //! Hints about faces of shape: if all faces are known to be convex
    //! or not.
    enum FaceType {
        UNKNOWN_FACE_TYPE = SoShapeHintsElement::UNKNOWN_FACE_TYPE,
        CONVEX            = SoShapeHintsElement::CONVEX
    };

    //! \name Fields
    //@{

    //! Indicates how the vertices of faces are ordered. <tt>CLOCKWISE</tt>
    //! ordering means that the vertices of each face form a clockwise loop
    //! around the face, when viewed from the outside (the side toward which
    //! the normal points).
    SoSFEnum            vertexOrdering; 

    //! Indicates whether the shape is known to enclose a volume (<tt>SOLID</tt>)
    //! or not. If the inside (the side away from the surface normal) of any
    //! part of the shape is visible, the shape is not solid.
    SoSFEnum            shapeType;      

    //! Indicates whether each face is convex. Because the penalty for
    //! non-convex faces is very steep (faces must be triangulated
    //! expensively), the default assumes all faces are convex. Therefore,
    //! shapes with concave faces may not be displayed correctly unless this
    //! hint is set to <tt>UNKNOWN_FACE_TYPE</tt>.
    SoSFEnum            faceType;       

    //! Indicates the minimum angle (in radians) between two adjacent face
    //! normals required to form a sharp crease at the edge when default
    //! normals are computed and used.
    SoSFFloat           creaseAngle;    
    //! Allows shapes to make use of vertex buffer objects if available
    SoSFBool            useVBO;         

    //@}

    //! Creates a shape hints node with default settings.
    SoShapeHints();

  SoEXTENDER public:
    virtual void        doAction(SoAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        callback(SoCallbackAction *action);
    virtual void        pick(SoPickAction *action);
    virtual void        getBoundingBox(SoGetBoundingBoxAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    virtual ~SoShapeHints();

  private:
    //! Does regular doAction stuff, also sets shapehints element
    void                doAction2(SoAction *action);
};

#endif /* _SO_SHAPE_HINTS_ */
