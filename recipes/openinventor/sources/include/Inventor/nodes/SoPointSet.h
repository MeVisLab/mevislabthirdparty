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
 |      This file defines the SoPointSet node class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_POINT_SET_
#define  _SO_POINT_SET_

#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/nodes/SoNonIndexedShape.h>


//! This value, when used in the numPoints field, means use the rest of
//! the coordinates as points
#define SO_POINT_SET_USE_REST_OF_POINTS (-1)

////////////////////////////////////////////////////////////////////////////////
//! Point set shape node.
/*!
\class SoPointSet
\ingroup Nodes
This node represents a set of points located at the 
coordinates specified by the \b vertexProperty  field (from SoVertexShape)
or the current inherited coordinates. For optimal performance, 
the \b vertexProperty  field is recommended.


SoPointSet uses the coordinates in order,
starting with the first one. The
number of points in the set is specified by the \b numPoints  field.


The coordinates of the point set are transformed by the current
cumulative transformation. The points are drawn with the current light
model and drawing style (drawing styles <tt>FILLED</tt> and <tt>LINES</tt> are
treated as <tt>POINTS</tt>).


Treatment of the current material and normal binding is as follows:
<tt>PER_PART</tt>, <tt>PER_FACE</tt>, and <tt>PER_VERTEX</tt> bindings bind one
material or normal to each point. The default material binding is
 <tt>OVERALL</tt>. The default normal binding is 
<tt>PER_VERTEX</tt>.

\par File Format/Default
\par
\code
PointSet {
  startIndex 0
  numPoints -1
}
\endcode

\par Action Behavior
\par
SoGLRenderAction
<BR> Draws points based on the current coordinates, normals, materials, drawing style, and so on. 
\par
SoRayPickAction
<BR> Picks points based on the current coordinates and transformation. Details about the intersection are returned in an SoPointDetail. 
\par
SoGetBoundingBoxAction
<BR> Computes the bounding box that encloses all points in the set with the current transformation applied to them.  Sets the center to the average of the coordinates of all points. 
\par
SoCallbackAction
<BR> If any point callbacks are registered with the action, they will be invoked for each point in the set. 

\par See Also
\par
SoCoordinate3, SoDrawStyle, SoPointDetail, SoVertexProperty
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoPointSet : public SoNonIndexedShape {

    SO_NODE_HEADER(SoPointSet);

  public:
    //! \name Fields
    //@{

    //! Number of points.
    SoSFInt32           numPoints;      

    //@}

    //! Creates a point set node with default settings.
    SoPointSet();

  SoEXTENDER public:
    //! Implements actions
    virtual void        GLRender(SoGLRenderAction *action);

    //! Redefine this to tell open caches that they contain points
    virtual void        getBoundingBox(SoGetBoundingBoxAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    //! Generates points representing point set
    virtual void        generatePrimitives(SoAction *action);

    //! Computes bounding box of point set
    virtual void        computeBBox(SoAction *action, SbBox3f &box,
                                    SbVec3f &center);

    //! Overrides standard method to create an SoPointDetail instance
    virtual SoDetail *  createPointDetail(SoRayPickAction *action,
                                          const SoPrimitiveVertex *v,
                                          SoPickedPoint *pp);

  protected:
    virtual ~SoPointSet();

  private:
    //! Returns TRUE if materials/normals are bound to individual points
    bool                areMaterialsPerPoint(SoAction *action) const;
    bool                areNormalsPerPoint(SoAction *action) const;
};

#endif /* _SO_POINT_SET_ */
