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
 * Copyright (C) 1990,91,92,93   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.1.1.1 $
 |
 |   Description:
 |      This file defines the SoNurbsSurface node class.
 |
 |   Author(s)          : Dave Immel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_NURBS_SURFACE_
#define  _SO_NURBS_SURFACE_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/nodes/SoShape.h>


class SoState;
class SoPrimitiveVertex;
class _SoNurbsNurbsTessellator;

////////////////////////////////////////////////////////////////////////////////
//! NURBS surface shape node.
/*!
\class SoNurbsSurface
\ingroup Nodes
This shape node represents a NURBS surface based on the node's knot
vectors and on control points constructed from the current
coordinates. The current coordinates are used in row-major order (the
V direction corresponds to the rows). The number of coordinates used
is determined by the \b numUControlPoints  and \b numVControlPoints 
fields. The \b uKnotVector  and \b vKnotVector  fields contain
floating point arrays of non-decreasing values.


The order of the surface in the U and V directions is defined as the
number of knots minus the number of control points in the particular
direction. The largest order allowed for a NURBS surface is 8.


The control points of the NURBS surface are transformed by the current
cumulative transformation. The surface is drawn with the current light
model and drawing style. The coordinates, normals, and texture
coordinates of a surface are generated, so you cannot bind explicit
normals or texture coordinates to a NURBS surface. The first material
in the state is applied to the entire surface.


The surface is trimmed according to the currently defined profile's curves.


When default texture coordinates are applied to a NURBS surface, the
edges of the texture square are stretched to fit the surface. The axes
of the texture are called S and T; S is horizontal and T is vertical.
The axes of the NURBS surface are called U and V; U is horizontal and
V is vertical. You can also define texture coordinates explicitly with
the S,T location point, the knot vectors, and the current texture
coordinates.


The approximation of the surface by polygons is affected by the
current complexity value.

\par File Format/Default
\par
\code
NurbsSurface {
  numUControlPoints 0
  numVControlPoints 0
  numSControlPoints 0
  numTControlPoints 0
  uKnotVector 0
  vKnotVector 0
  sKnotVector 0
  tKnotVector 0
}
\endcode

\par Action Behavior
\par
SoGLRenderAction
<BR> Draws the surface based on the current coordinates, material, and so on. 
\par
SoRayPickAction
<BR> Picks the surface based on the current coordinates and transformation. 
\par
SoGetBoundingBoxAction
<BR> Computes the bounding box that encloses all control points of the surface with the current transformation applied to them. Sets the center to the average of the control points. 
\par
SoCallbackAction
<BR> If any triangle callbacks are registered with the action, they will be invoked for each successive triangle approximating the surface. 

\par See Also
\par
SoIndexedNurbsSurface, SoNurbsCurve, SoProfile
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoNurbsSurface : public SoShape {

    SO_NODE_HEADER(SoNurbsSurface);

  public:
    //! \name Fields
    //@{
    //! Number of control points in the U direction
    SoSFInt32           numUControlPoints; 
    //! Number of control points in the V direction
    SoSFInt32           numVControlPoints; 
    //! Number of control points in S direction
    SoSFInt32           numSControlPoints; 
    //! Number of control points in T direction
    SoSFInt32           numTControlPoints; 
    //! The knot vectors in the U direction
    SoMFFloat           uKnotVector;       
    //! The knot vectors in the V direction
    SoMFFloat           vKnotVector;       
    //! The knot vectors in the S direction
    SoMFFloat           sKnotVector;       
    //! The knot vectors in the T direction
    SoMFFloat           tKnotVector;       

    //@}

    //! Creates a NURBS surface node with default settings.
    SoNurbsSurface();

  SoEXTENDER public:
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        rayPick(SoRayPickAction *action);

  SoINTERNAL public:
    static void         initClass();

    void                sendPrimitive(SoAction *, SoPrimitiveVertex *);

  protected:
    //! Generates triangles representing a surface
    virtual void        generatePrimitives(SoAction *action);

    //! Computes bounding box of surface
    virtual void        computeBBox(SoAction *action, SbBox3f &box,
                                    SbVec3f &center);

    ~SoNurbsSurface();

  private:
    //! Renders the surface
    void                drawNURBS(_SoNurbsNurbsTessellator *render, SoState *state,
                                  bool doTextures);

    //! Matrix operations for level of detail and culling
    void                calcTotalMatrix( SoState *state, SbMatrix &totalMat );
    void                multMatrix4d( SbMatrix &n, SbMatrix left, 
                                      SbMatrix right );

    //! This callback gets details from the NURBS library
    static void         primCB(SoAction *, SoPrimitiveVertex *, void *);
};

#endif /* _SO_NURBS_SURFACE_ */
