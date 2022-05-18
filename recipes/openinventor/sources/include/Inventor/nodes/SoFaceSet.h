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
 |      This file defines the SoFaceSet node class.
 |
 |   Author(s)          : Paul S. Strauss, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_FACE_SET_
#define  _SO_FACE_SET_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNonIndexedShape.h>


//! This value, when used in the numVertices field, means that the
//! corresponding face should use the rest of the vertices
#define SO_FACE_SET_USE_REST_OF_VERTICES        (-1)

class SoCoordinateElement;
class SoNormalBundle;
class SoState;

////////////////////////////////////////////////////////////////////////////////
//! Polygonal face shape node.
/*!
\class SoFaceSet
\ingroup Nodes
This node represents a 3D shape formed by constructing faces
(polygons) from vertices located at the coordinates
specified in the \b vertexProperty  field (from SoVertexShape), 
or the current inherited state.
For optimal performance, the \b vertexProperty  field is recommended.


SoFaceSet uses the coordinates in order, starting with the
first one.
Each face has a number of
vertices specified by a value in the \b numVertices  field. For
example, an SoFaceSet  with 
\b numVertices  of [3,4,4] would use coordinates 1, 2, and 3 for the
first face, coordinates 4, 5, 6, and 7 for the second face, and
coordinates 8, 9, 10, and 11 for the third. 
For improved performance, arrange all the faces with only 3 
vertices at beginning of the list, then all faces with 4 vertices,
and finally all other faces.


The number of values in the \b numVertices  field indicates the
number of faces in the set.


The coordinates of the face set are transformed by the current
cumulative transformation. The faces are drawn with the current light
model and drawing style.


Treatment of the current material and normal binding is as follows:
The <tt>PER_PART</tt> and <tt>PER_FACE</tt> bindings specify a material or
normal for each face. The <tt>_INDEXED</tt> bindings are equivalent to
their non-indexed counterparts. The default material binding is 
<tt>OVERALL</tt>. The default normal binding is 
<tt>PER_VERTEX</tt>.


If any normals (or materials) are specified, Inventor assumes 
you provide the correct number of them, as indicated by the binding.
You will see unexpected results
if you specify fewer normals (or materials) than the shape requires.
If no normals are specified, they will be generated automatically.

\par File Format/Default
\par
\code
FaceSet {
  startIndex 0
  numVertices -1
}
\endcode

\par Action Behavior
\par
SoGLRenderAction
<BR> Draws faces based on the current coordinates, normals, materials, drawing style, and so on. 
\par
SoRayPickAction
<BR> Picks faces based on the current coordinates and transformation. Details about the intersection are returned in an SoFaceDetail. 
\par
SoGetBoundingBoxAction
<BR> Computes the bounding box that encloses all vertices of the face set with the current transformation applied to them.  Sets the center to the average of the coordinates of all vertices. 
\par
SoCallbackAction
<BR> If any triangle callbacks are registered with the action, they will be invoked for each successive triangle generated from each face in the set. 

\par See Also
\par
SoCoordinate3, SoDrawStyle, SoIndexedFaceSet, SoFaceDetail, SoVertexProperty
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoFaceSet : public SoNonIndexedShape {

    SO_NODE_HEADER(SoFaceSet);

  public:
    //! \name Fields
    //@{

    //! Number of vertices per face.
    SoMFInt32           numVertices;    

    //! flag that defines if the GL_TRIANGLES_ADJACENCY draw mode is used (MeVis Only)
    //! (this only applies to triangles, not to quads and other faces)
    SoSFBool sendAdjacency;

    //@}

    //! Creates a face set node with default settings.
    SoFaceSet();

  SoEXTENDER public:
    //! Implement actions
    virtual void        GLRender(SoGLRenderAction *action);

    //! Generates default normals using the given normal bundle. 
    //! Returns TRUE.
    virtual bool        generateDefaultNormals(SoState *state,
                                               SoNormalBundle *nb);

    //! Typedef of pointer to method on FaceSet;
    //! This will be used to simplify declaration and initialization.
    typedef void (SoFaceSet::*PMFS)(SoGLRenderAction *);
                                                  
  SoINTERNAL public:
    static void         initClass();

    //! This enum is used to indicate the current material or normal binding
    enum Binding {
        OVERALL, PER_FACE, PER_VERTEX
    };

  protected:
    //! Generates triangles representing faces
    virtual void        generatePrimitives(SoAction *action);

    //! Computes bounding box of face set
    virtual void        computeBBox(SoAction *action, SbBox3f &box,
                                    SbVec3f &center);

    //! Overrides standard method to create an SoFaceDetail instance
    virtual SoDetail *  createTriangleDetail(SoRayPickAction *action,
                                             const SoPrimitiveVertex *v1,
                                             const SoPrimitiveVertex *v2,
                                             const SoPrimitiveVertex *v3,
                                             SoPickedPoint *pp);

    ~SoFaceSet();

  private:
    //! internal GL rendering (MeVis ONLY)
    void GLRenderInternal( SoGLRenderAction * action, uint32_t useTexCoordsAnyway, const SoShapeStyleElement * shapeStyle);

    //! Returns current material or normal binding from action's state
    Binding             getMaterialBinding(SoAction *action);
    Binding             getNormalBinding(SoAction *action,
                                         SoNormalBundle *nb);

    //! Figures out normals, if necessary.
    bool                figureNormals(SoState *state, SoNormalBundle *nb);
    
    //! set numTris/Quads/Faces to -1, checks SO_USE_REST_OF_VERTICES
    //! when notified
    virtual void        notify(SoNotList *list);
    
    //! Set number of triangles/quads/faces, based on coordIndex array.
    void setupNumTrisQuadsFaces();
    
    //! Number of triangles, quads, (n>4)-vertex faces, total vertices
    int     numTris, numQuads, numFaces, totalNumVertices;
    
    //! keep track of whether we are using USE_REST_OF_VERTICES
    bool usingUSE_REST;
    bool nvNotifyEnabled;
    
    //! 18*3ferent render functions; names are formed like this:
    //! Om -- overall material
    //! Fm -- per face material Vm -- per vertex material
    //! On -- overall normal
    //! Fn -- per face normal   Vm -- per vertex normal
    //! T  -- per vertex texture coordinates
    void TriOmOn(SoGLRenderAction *); void TriOmOnT(SoGLRenderAction *);
    void TriOmFn(SoGLRenderAction *); void TriOmFnT(SoGLRenderAction *);
    void TriOmVn(SoGLRenderAction *); void TriOmVnT(SoGLRenderAction *);
    void TriFmOn(SoGLRenderAction *); void TriFmOnT(SoGLRenderAction *);
    void TriFmFn(SoGLRenderAction *); void TriFmFnT(SoGLRenderAction *);
    void TriFmVn(SoGLRenderAction *); void TriFmVnT(SoGLRenderAction *);
    void TriVmOn(SoGLRenderAction *); void TriVmOnT(SoGLRenderAction *);
    void TriVmFn(SoGLRenderAction *); void TriVmFnT(SoGLRenderAction *);
    void TriVmVn(SoGLRenderAction *); void TriVmVnT(SoGLRenderAction *);
    void QuadOmOn(SoGLRenderAction *); void QuadOmOnT(SoGLRenderAction *);
    void QuadOmFn(SoGLRenderAction *); void QuadOmFnT(SoGLRenderAction *);
    void QuadOmVn(SoGLRenderAction *); void QuadOmVnT(SoGLRenderAction *);
    void QuadFmOn(SoGLRenderAction *); void QuadFmOnT(SoGLRenderAction *);
    void QuadFmFn(SoGLRenderAction *); void QuadFmFnT(SoGLRenderAction *);
    void QuadFmVn(SoGLRenderAction *); void QuadFmVnT(SoGLRenderAction *);
    void QuadVmOn(SoGLRenderAction *); void QuadVmOnT(SoGLRenderAction *);
    void QuadVmFn(SoGLRenderAction *); void QuadVmFnT(SoGLRenderAction *);
    void QuadVmVn(SoGLRenderAction *); void QuadVmVnT(SoGLRenderAction *);
    void GenOmOn(SoGLRenderAction *); void GenOmOnT(SoGLRenderAction *);
    void GenOmFn(SoGLRenderAction *); void GenOmFnT(SoGLRenderAction *);
    void GenOmVn(SoGLRenderAction *); void GenOmVnT(SoGLRenderAction *);
    void GenFmOn(SoGLRenderAction *); void GenFmOnT(SoGLRenderAction *);
    void GenFmFn(SoGLRenderAction *); void GenFmFnT(SoGLRenderAction *);
    void GenFmVn(SoGLRenderAction *); void GenFmVnT(SoGLRenderAction *);
    void GenVmOn(SoGLRenderAction *); void GenVmOnT(SoGLRenderAction *);
    void GenVmFn(SoGLRenderAction *); void GenVmFnT(SoGLRenderAction *);
    void GenVmVn(SoGLRenderAction *); void GenVmVnT(SoGLRenderAction *);

    //! Array of function pointers to render functions:
    static PMFS TriRenderFunc[32];
    static PMFS QuadRenderFunc[32];
    static PMFS GenRenderFunc[32];
};

#endif /* _SO_FACE_SET_ */
