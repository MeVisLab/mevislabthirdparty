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
 |      This file defines the SoCylinder node class.
 |
 |   Author(s)          : Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_CYLINDER_
#define  _SO_CYLINDER_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/misc/SoVBO.h>


////////////////////////////////////////////////////////////////////////////////
//! Cylinder shape node.
/*!
\class SoCylinder
\ingroup Nodes
This node represents a simple capped cylinder centered around the
y-axis. By default, the cylinder is centered at (0,0,0) and has a
default size of -1 to +1 in all three dimensions.  You can use the
radius and height fields to create a cylinder with a different
size.


The cylinder is transformed by the current cumulative transformation
and is drawn with the current lighting model, drawing style, material,
and geometric complexity.


If the current material binding is <tt>PER_PART</tt> or
<tt>PER_PART_INDEXED</tt>, the first current material is used for the sides
of the cylinder, the second is used for the top, and the third is used
for the bottom. Otherwise, the first material is used for the entire
cylinder.


When a texture is applied to a cylinder, it is applied differently to
the sides, top, and bottom. On the sides, the texture wraps
counterclockwise (from above) starting at the back of the
cylinder. The texture has a vertical seam at the back, intersecting
the yz-plane. For the top and bottom, a circle is cut out of the
texture square and applied to the top or bottom circle. The top
texture appears right side up when the top of the cylinder is tilted
toward the camera, and the bottom texture appears right side up when
the top of the cylinder is tilted away from the camera.

\par File Format/Default
\par
\code
Cylinder {
  parts ALL
  radius 1
  height 2
}
\endcode

\par Action Behavior
\par
SoGLRenderAction
<BR> Draws cylinder based on the current coordinates, materials, drawing style, and so on. 
\par
SoRayPickAction
<BR> Intersects the ray with the cylinder. The part of the cylinder that was picked is available from the SoCylinderDetail. 
\par
SoGetBoundingBoxAction
<BR> Computes the bounding box that encloses the cylinder. 
\par
SoCallbackAction
<BR> If any triangle callbacks are registered with the action, they will be invoked for each successive triangle that approximates the cylinder. 

\par See Also
\par
SoCone, SoCube, SoCylinderDetail, SoSphere
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoCylinder : public SoShape {

    SO_NODE_HEADER(SoCylinder);

  public:

    //! Cylinder parts
    enum Part {
        SIDES   = 0x01,                 //!< The tubular part
        TOP     = 0x02,                 //!< The top circular face
        BOTTOM  = 0x04,                 //!< The bottom circular face
        ALL     = 0x07                  //!< All parts
    };

    //! \name Fields
    //@{

    //! Visible parts of cylinder.
    SoSFBitMask         parts;          
    //! Radius in x and z dimensions
    SoSFFloat           radius;         
    //! Size in y dimension
    SoSFFloat           height;         

    //! Defines how many sides are used for tessellation. If set to <= 0, the sides are
    //! calculated by the SoComplexityElement.
    SoSFInt32           sides;

    //! Defines how many sections are used for tessellation. If set to <= 0, the sections are
    //! calculated by the SoComplexityElement.
    SoSFInt32           sections;
    //@}

    //! Creates a cylinder node with default settings.
    SoCylinder();

    //! Turns on/off a part of the cylinder. (Convenience functions)
    void                addPart(SoCylinder::Part part);
    void                removePart(SoCylinder::Part part);

    //! Returns whether a given part is on or off. (Convenience function)
    bool                hasPart(SoCylinder::Part part) const;

  SoEXTENDER public:
    //! Implements actions
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        rayPick(SoRayPickAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    //! Generates triangles representing a cylinder
    virtual void        generatePrimitives(SoAction *action);

    //! Computes bounding box of cylinder
    virtual void        computeBBox(SoAction *action, SbBox3f &box,
                                    SbVec3f &center);

    virtual ~SoCylinder();

  private:
    static SbVec2f      *coordsArray;   //!< Storage for ring coords
    static int          maxCoords;      //!< Current max num of coords

    //! The state of the last cone tessellation,
    //! so that the VBO can be reused if nothing changed.
    struct CacheState : public SimpleVertexArrayCache {
      CacheState() {
        curParts = 0;
        numSides = 0;
        numSections = 0;
      }
      int curParts, numSides, numSections;
      SbVec3f scale;
    };

    CacheState _cache;

    //! Computes number of sides and sections to use to represent
    //! cylinder (based on complexity), then computes ring of x,z
    //! coordinates around cylinder and stores in ringCoords.
    void                computeRing(SoAction *action,
                                    int &numSides, int &numSections,
                                    SbVec2f *&ringCoords) const;

    //! Computes real radius and half-height
    void                getSize(float &rad, float &hHeight) const;

    //! These render the cylinder
    void                GLRenderGeneric(SoGLRenderAction *action,
                                        bool sendNormals, bool doTextures);
    void                GLRenderNvertTnone(SoGLRenderAction *action);
    
    void                GLRenderVertexArray(SoGLRenderAction *action,
                                        bool sendNormals, bool doTextures);
};

#endif /* _SO_CYLINDER_ */
