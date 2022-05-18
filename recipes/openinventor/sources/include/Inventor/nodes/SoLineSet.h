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
 |      This file defines the SoLineSet node class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_LINE_SET_
#define  _SO_LINE_SET_

#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNonIndexedShape.h>

class SoState;



#ifndef IV_STRICT
//! Deprecated feature; specifying USE_REST_OF_VERTICES as the last
//! value in the numVertices field will use all the points in the
//! coordinate array.
#define SO_LINE_SET_USE_REST_OF_VERTICES        (-1)
#endif


////////////////////////////////////////////////////////////////////////////////
//! Polyline shape node.
/*!
\class SoLineSet
\ingroup Nodes
This node represents a 3D shape formed by constructing polylines from
vertices located at the coordinates specified in the
\b vertexProperty  field (from SoVertexShape), 
or the current inherited coordinates. 
For optimal performance, the \b vertexProperty  field is recommended.


SoLineSet uses the
coordinates in order, starting with the first one. 
Each line has a number of vertices specified by
a value in the \b numVertices  field. For example, an SoLineSet
with a \b numVertices  of [3,4,2] would use
coordinates 1, 2, and 3 for the first line, coordinates 4, 5, 6, and 7
for the second line, and coordinates 8 and 9 for the third. 

The number of values in the \b numVertices  field indicates the
number of polylines in the set.


The coordinates of the line set are transformed by the current
cumulative transformation. The lines are drawn with the current light
model and drawing style (drawing style <tt>FILLED</tt> is treated as
<tt>LINES</tt>).


Treatment of the current material and normal binding is as follows:
The <tt>PER_PART</tt> binding specifies a material or normal for each
segment of the line. The <tt>PER_FACE</tt> binding specifies a material or
normal for each polyline. The <tt>_INDEXED</tt> bindings are equivalent to
their non-indexed counterparts. The default material binding is
<tt>OVERALL</tt>. The default normal binding is 
<tt>PER_VERTEX</tt>.


The current complexity value has no effect on the rendering of line
sets.

\par File Format/Default
\par
\code
LineSet {
  startIndex 0
  numVertices -1
}
\endcode

\par Action Behavior
\par
SoGLRenderAction
<BR> Draws lines based on the current coordinates, normals, materials, drawing style, and so on. 
\par
SoRayPickAction
<BR> Picks lines based on the current coordinates and transformation. Details about the intersection are returned in an SoLineDetail. 
\par
SoGetBoundingBoxAction
<BR> Computes the bounding box that encloses all vertices of the line set with the current transformation applied to them.  Sets the center to the average of the coordinates of all vertices. 
\par
SoCallbackAction
<BR> If any line segment callbacks are registered with the action, they will be invoked for each successive segment in the line set. 

\par See Also
\par
SoCoordinate3, SoDrawStyle, SoIndexedLineSet, SoLineDetail, SoVertexProperty
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoLineSet : public SoNonIndexedShape {

    SO_NODE_HEADER(SoLineSet);

  public:
    //! \name Fields
    //@{
    //! Number of vertices per polyline.
    SoMFInt32 numVertices;    

    //! flag that defines if the GL_LINE_STRIP_ADJACENCY draw mode is used (MeVis Only)
    SoSFBool sendAdjacency;

    //! If enabled, GL_LINES are drawn for all vertice pairs, independent of the numVertices field (MeVis Only)
    SoSFBool independentLines;

    //@}

    //! Creates a line set node with default settings.
    SoLineSet();

  SoEXTENDER public:
    //! Implements actions
    virtual void        GLRender(SoGLRenderAction *action);

    //! Redefine this to tell open caches that they contain lines
    virtual void        getBoundingBox(SoGetBoundingBoxAction *action);

  SoINTERNAL public:
    static void         initClass();

    //! This enum is used to indicate the current material or normal binding
    enum Binding {
        OVERALL, PER_LINE, PER_SEGMENT, PER_VERTEX
    };
    
    //!Typedef of pointer to method on IndexedLineSet;
    //!This will be used to simplify declaration and initialization.
    typedef void (SoLineSet::*PMLS)(SoGLRenderAction *);
    
  protected:
    //! Generates line segments representing line set
    virtual void        generatePrimitives(SoAction *action);

    //! Computes bounding box of line set
    virtual void        computeBBox(SoAction *action, SbBox3f &box,
                                    SbVec3f &center);

    //! Overrides standard method to create an SoLineDetail instance
    virtual SoDetail *  createLineSegmentDetail(SoRayPickAction *action,
                                                const SoPrimitiveVertex *v1,
                                                const SoPrimitiveVertex *v2,
                                                SoPickedPoint *pp);

    virtual ~SoLineSet();

  private:
    //! internal GL rendering (MeVis ONLY)
    void GLRenderInternal( SoGLRenderAction * action, uint32_t useTexCoordsAnyway, const SoShapeStyleElement * shapeStyle);

    //! Returns current material or normal binding from action's state
    static Binding      getMaterialBinding(SoAction *action);
    static Binding      getNormalBinding(SoAction *action);

    //! Returns TRUE if normal binding is AUTO and there aren't enough
    //! PER_VERTEX normals, in which case we turn off lighting and draw
    //! BASE_COLOR.
    bool        wouldGenerateNormals(SoState *state);

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
    static PMLS renderFunc[32];

};

#endif /* _SO_LINE_SET_ */
