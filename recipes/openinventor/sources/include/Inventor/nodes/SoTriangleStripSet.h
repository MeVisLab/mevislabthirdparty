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
 |      This file defines the SoTriangleStripSet node class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TRIANGLE_STRIP_SET_
#define  _SO_TRIANGLE_STRIP_SET_

#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/nodes/SoNonIndexedShape.h>
#include <Inventor/nodes/SoVertexProperty.h>


class SoNormalGenerator;
class SoCoordinateElement;

#ifndef IV_STRICT
//! Deprecated feature; specifying USE_REST_OF_VERTICES as the last
//! value in the numVertices field will use all the points in the
//! coordinate array.
#define SO_TRI_STRIP_SET_USE_REST_OF_VERTICES   (-1)
#endif

////////////////////////////////////////////////////////////////////////////////
//! Triangle strip set shape node.
/*!
\class SoTriangleStripSet
\ingroup Nodes
This shape node constructs triangle strips out of vertices.
The vertices may be specified in
the \b vertexProperty  field (from SoVertexShape), 
or by the current inherited coordinates.
For optimal performance, the \b vertexProperty  field is recommended.


SoTriangleStripSet is one of the fastest ways of drawing
polygonal objects in Inventor. It uses the current
coordinates, in order, starting with the first one. 
The values in the \b numVertices  field indicate
the number of vertices to use for each triangle strip in the set. The
number of values in this field determines the number of strips.


For example, if 
\b numVertices  has the values [3,5], coordinates 1, 2, and 3 would be
used for the first triangle strip and coordinates 4, 5, 6, 7, and 8 
would be used for the second strip. This would result in 1 triangle in
the first strip and 3 in the second.


The coordinates of the strips are transformed by the current
cumulative transformation. The strips are drawn with the current light
model and drawing style.


Treatment of the current material and normal binding is as follows:
The <tt>PER_PART</tt> binding specifies a material or normal for each strip
of the set. The <tt>PER_FACE</tt> binding specifies a material or normal
for each triangle. The <tt>_INDEXED</tt> bindings are equivalent to
their non-indexed counterparts. The default normal binding is 
<tt>PER_VERTEX</tt>. The default material binding is 
<tt>OVERALL</tt>.


If any normals (or materials) are specified, Inventor assumes 
you provide the correct number of them, as indicated by the binding.
You will see unexpected results
if you specify fewer normals (or materials) than the shape requires.
If no normals are specified, they will be generated automatically.

\par File Format/Default
\par
\code
TriangleStripSet {
  startIndex 0
  numVertices -1
}
\endcode

\par Action Behavior
\par
SoGLRenderAction
<BR> Draws a strip set based on the current coordinates, normals, materials, drawing style, and so on. 
\par
SoRayPickAction
<BR> Picks on the strip set based on the current coordinates and transformation.  Details about the intersection are returned in an SoFaceDetail. 
\par
SoGetBoundingBoxAction
<BR> Computes the bounding box that encloses all vertices of the strip set with the current transformation applied to them. Sets the center to the average of the coordinates of all vertices. 
\par
SoCallbackAction
<BR> If any triangle callbacks are registered with the action, they will be invoked for each successive triangle forming the strips of the set. 

\par See Also
\par
SoCoordinate3, SoDrawStyle, SoFaceDetail, SoFaceSet, SoIndexedTriangleStripSet, SoQuadMesh, SoVertexProperty
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoTriangleStripSet : public SoNonIndexedShape {

    SO_NODE_HEADER(SoTriangleStripSet);

  public:
    //! \name Fields
    //@{

    //! Number of vertices in each triangle strip. The number of strips is
    //! equal to the number of values in this field.
    SoMFInt32   numVertices;    

    //@}

    //! Creates a triangle strip set node with default settings.
    SoTriangleStripSet();

  SoEXTENDER public:
    //! Implement actions
    virtual void        GLRender(SoGLRenderAction *action);

    //! Generates default normals using the given normal bundle. 
    //! Returns TRUE.
    virtual bool        generateDefaultNormals(SoState *state,
                                               SoNormalBundle *nb);

  SoINTERNAL public:
    static void         initClass();

    //!Typedef of pointer to method on TriangleStripSet;
    //!This will be used to simplify declaration and initialization.
    typedef void (SoTriangleStripSet::*PMTSS)(SoGLRenderAction *);

  protected:
    //! Generates triangles representing strips
    virtual void        generatePrimitives(SoAction *action);

    //! Computes bounding box of triangle strips
    virtual void        computeBBox(SoAction *action, SbBox3f &box,
                                    SbVec3f &center);
                                    
                            

    //! Overrides standard method to create an SoFaceDetail instance
    virtual SoDetail *  createTriangleDetail(SoRayPickAction *action,
                                             const SoPrimitiveVertex *v1,
                                             const SoPrimitiveVertex *v2,
                                             const SoPrimitiveVertex *v3,
                                             SoPickedPoint *pp);

    virtual ~SoTriangleStripSet();

  private:
    //! internal GL rendering (MeVis ONLY)
    void GLRenderInternal( SoGLRenderAction * action, uint32_t useTexCoordsAnyway, const SoShapeStyleElement * shapeStyle);

    //! Blow vpCache when vertexProperty field changes:
    virtual void        notify(SoNotList *list);


    //! This stores the total number of vertices; we use this
    //! information to influence Separator's auto-caching algorithm
    //! (shapes with very few triangles should be cached because
    //! traversing them can be expensive, shapes with lots of triangles
    //! shouldn't be cached because they'll take up too much memory).
    int                         totalNumVertices;

    //! 32 different render functions; names are formed like this:
    //! Om -- overall material  Pm -- per part material
    //! Fm -- per face material Vm -- per vertex material
    //! On -- overall normal    Pm -- per part normal
    //! Fn -- per face normal   Vm -- per vertex normal
    //! T  -- per vertex texture coordinates
    void OmOn(SoGLRenderAction *); void OmOnT(SoGLRenderAction *);
    void OmPn(SoGLRenderAction *); void OmPnT(SoGLRenderAction *);
    void OmFn(SoGLRenderAction *); void OmFnT(SoGLRenderAction *);
    void OmVn(SoGLRenderAction *); void OmVnT(SoGLRenderAction *);
    void PmOn(SoGLRenderAction *); void PmOnT(SoGLRenderAction *);
    void PmPn(SoGLRenderAction *); void PmPnT(SoGLRenderAction *);
    void PmFn(SoGLRenderAction *); void PmFnT(SoGLRenderAction *);
    void PmVn(SoGLRenderAction *); void PmVnT(SoGLRenderAction *);
    void FmOn(SoGLRenderAction *); void FmOnT(SoGLRenderAction *);
    void FmPn(SoGLRenderAction *); void FmPnT(SoGLRenderAction *);
    void FmFn(SoGLRenderAction *); void FmFnT(SoGLRenderAction *);
    void FmVn(SoGLRenderAction *); void FmVnT(SoGLRenderAction *);
    void VmOn(SoGLRenderAction *); void VmOnT(SoGLRenderAction *);
    void VmPn(SoGLRenderAction *); void VmPnT(SoGLRenderAction *);
    void VmFn(SoGLRenderAction *); void VmFnT(SoGLRenderAction *);
    void VmVn(SoGLRenderAction *); void VmVnT(SoGLRenderAction *);

    //! Array of function pointers to render functions:
    static PMTSS renderFunc[32];
};

#endif /* _SO_TRIANGLE_STRIP_SET_ */
