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
 |      This file defines the SoCube node class.
 |
 |   Author(s)          : Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_CUBE_
#define  _SO_CUBE_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/misc/SoVBO.h>


////////////////////////////////////////////////////////////////////////////////
//! Cube shape node.
/*!
\class SoCube
\ingroup Nodes
This node represents a cuboid aligned with the coordinate axes. By
default, the cube is centered at (0,0,0) and measures 2 units in each
dimension, from -1 to +1. The cube is transformed by the current
cumulative transformation and is drawn with the current lighting
model, drawing style, material, and geometric complexity.


If the current material binding is <tt>PER_PART</tt>, <tt>PER_PART_INDEXED</tt>,
<tt>PER_FACE</tt>, or <tt>PER_FACE_INDEXED</tt>, materials will be bound to the
faces of the cube in this order: front, back, left, right, top, and
bottom.


Textures are applied individually to each face of the cube; the entire
texture goes on each face. On the front, back, right, and left sides
of the cube, the texture is applied right side up. On the top, the
texture appears right side up when the top of the cube is tilted
toward the camera. On the bottom, the texture appears right side up
when the top of the cube is tilted away from the camera.

\par File Format/Default
\par
\code
Cube {
  width 2
  height 2
  depth 2
}
\endcode

\par Action Behavior
\par
SoGLRenderAction
<BR> Draws cube based on the current coordinates, materials, drawing style, and so on. 
\par
SoRayPickAction
<BR> Intersects the ray with the cube. The face of the cube that was picked is available from the SoCubeDetail. 
\par
SoGetBoundingBoxAction
<BR> Computes the bounding box that encloses the cube. 
\par
SoCallbackAction
<BR> If any triangle callbacks are registered with the action, they will be invoked for each successive triangle that approximates the cube. 

\par See Also
\par
SoCone, SoCubeDetail, SoCylinder, SoSphere
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoCube : public SoShape {

    SO_NODE_HEADER(SoCube);

  public:
    //! \name Fields
    //@{
    //! Size in x dimension
    SoSFFloat           width;          
    //! Size in y dimension
    SoSFFloat           height;         
    //! Size in z dimension
    SoSFFloat           depth;          

    //@}

    //! Creates a cube node with default settings.
    SoCube();

  SoEXTENDER public:
    //! Implements actions
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        rayPick(SoRayPickAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    //! Generates triangles representing a cube
    virtual void        generatePrimitives(SoAction *action);

    //! Computes bounding box of cube
    virtual void        computeBBox(SoAction *action, SbBox3f &box,
                                    SbVec3f &center);

    //! Overrides standard method to create an SoCubeDetail instance
    virtual SoDetail *  createTriangleDetail(SoRayPickAction *action,
                                             const SoPrimitiveVertex *v1,
                                             const SoPrimitiveVertex *v2,
                                             const SoPrimitiveVertex *v3,
                                             SoPickedPoint *pp);

    virtual ~SoCube();

  private:
    static SbVec3f      coords[8];      //!< Corner coordinates
    static SbVec2f      texCoords[4];   //!< Face corner texture coordinates
    static SbVec3f      normals[6];     //!< Face normals
    static const SbVec3f *verts[6][4];  //!< Vertex references to coords

    //! The state of the last cone tessellation,
    //! so that the VBO can be reused if nothing changed.
    struct CacheState : public SimpleVertexArrayCache {
      CacheState() {
      }
    };

    CacheState _cache;

    //! This flag indicates whether picking is done on a real cube or a
    //! cube that is just a bounding box representing another shape. If
    //! this flag is TRUE, a pick on the cube should not generate a
    //! detail, since the bounding box is not really in the picked path.
    bool                pickingBoundingBox;

    //! Returns TRUE if per face materials are specified
    bool                isMaterialPerFace(SoAction *action) const;

    //! Computes number of divisions per side based on complexity
    int                 computeNumDivisions(SoAction *action) const;

    //! Computes real half-width, -height, -depth
    void                getSize(float &hWidth,
                                float &hHeight,
                                float &hDepth) const;

    //! These render the cube
    void                GLRenderGeneric(SoGLRenderAction *action,
                                        bool sendNormals, bool doTextures);
    void                GLRenderNvertTnone(SoGLRenderAction *action);

    //! Renders or picks cube representing given bounding box. These
    //! are used by SoShape to implement BOUNDING_BOX complexity.
    void                GLRenderBoundingBox(SoGLRenderAction *action,
                                            const SbBox3f &bbox);
    void                rayPickBoundingBox(SoRayPickAction *action,
                                           const SbBox3f &bbox);

    void GLRenderVertexArray(SoGLRenderAction *action,
                             bool sendNormals, bool doTextures);

    //! SoShape needs to get at the above methods
friend class SoShape; 
};

#endif /* _SO_CUBE_ */
