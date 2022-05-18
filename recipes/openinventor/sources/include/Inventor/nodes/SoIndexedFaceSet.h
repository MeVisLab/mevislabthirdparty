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
 |      This file defines the SoIndexedFaceSet node class.
 |
 |   Author(s)          : Paul S. Strauss, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_INDEXED_FACE_SET_
#define  _SO_INDEXED_FACE_SET_

#include <Inventor/system/SbSystem.h>
#include <Inventor/nodes/SoIndexedShape.h>

class SoVertexArrayIndexer;


//! This coordinate index indicates that the current face ends and the
//! next face begins
#define SO_END_FACE_INDEX       (-1)

class SoNormalBundle;
class SoCoordinateElement;
class SoShapeStyleElement;

////////////////////////////////////////////////////////////////////////////////
//! Indexed polygonal face shape node.
/*!
\class SoIndexedFaceSet
\ingroup Nodes
This node represents a 3D shape formed by constructing faces
(polygons) from vertices located at the coordinates
specified in the \b vertexProperty  field (from SoVertexShape), 
or the current inherited state.
For optimal performance, the \b vertexProperty  field is recommended.


SoIndexedFaceSet uses the indices in the \b coordIndex  field
(from SoIndexedShape) to specify the polygonal faces. An index of
<tt>SO_END_FACE_INDEX</tt> (-1) indicates that the current face has ended
and the next one begins.
For improved performance, arrange all the faces with only 3 
vertices at beginning of the list, then all faces with 4 vertices,
and finally all other faces.


The vertices of the faces are transformed by the current
transformation matrix. The faces are drawn with the current light
model and drawing style.


Treatment of the current material and normal binding is as follows:
The <tt>PER_PART</tt> and <tt>PER_FACE</tt> bindings specify a material or
normal for each face. <tt>PER_VERTEX</tt> specifies a material or normal
for each vertex.  The corresponding <tt>_INDEXED</tt> bindings are the
same, but use the \b materialIndex  or \b normalIndex  indices (see
SoIndexedShape). The default material binding is 
<tt>OVERALL</tt>. The default normal binding is 
<tt>PER_VERTEX_INDEXED</tt>.


If any normals (or materials) are specified, Inventor assumes 
you provide the correct number of them, as indicated by the binding.
You will see unexpected results
if you specify fewer normals (or materials) than the shape requires.
If no normals are specified, they will be generated automatically.


Textures are applied
as described for the SoIndexedShape class.

\par File Format/Default
\par
\code
IndexedFaceSet {
  coordIndex 0
  materialIndex -1
  normalIndex -1
  textureCoordIndex -1
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
SoIndexedTriangleSet, SoCoordinate3, SoDrawStyle, SoFaceDetail, SoFaceSet, SoVertexProperty
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoIndexedFaceSet : public SoIndexedShape {

    SO_NODE_HEADER(SoIndexedFaceSet);

  public:

    //! Creates an indexed face set node with default settings.
    SoIndexedFaceSet();

  SoEXTENDER public:
    //! Implements actions
    virtual void        GLRender(SoGLRenderAction *action);

    //! Generates default normals using the given normal bundle. 
    //! Returns TRUE.
    virtual bool        generateDefaultNormals(SoState *state,
                                               SoNormalBundle *nb);

    //! Typedef of pointer to method on IndexedFaceSet;
    //! This will be used to simplify declaration and initialization.
    typedef void (SoIndexedFaceSet::*PMFS)(SoGLRenderAction *);
                                                  
  SoINTERNAL public:
    static void         initClass();

    //! This enum is used to indicate the current material or normal binding
    enum Binding {
        OVERALL, PER_FACE, PER_FACE_INDEXED, PER_VERTEX,
            PER_VERTEX_INDEXED
    };

  protected:
    //! Generates triangles representing faces
    virtual void        generatePrimitives(SoAction *action);

    //! Overrides standard method to create an SoFaceDetail instance
    virtual SoDetail *  createTriangleDetail(SoRayPickAction *action,
                                             const SoPrimitiveVertex *v1,
                                             const SoPrimitiveVertex *v2,
                                             const SoPrimitiveVertex *v3,
                                             SoPickedPoint *pp);
    ~SoIndexedFaceSet();

  private:
    //! internal GL rendering (MeVis ONLY)
    void GLRenderInternal( SoGLRenderAction * action, uint32_t useTexCoordsAnyway, const SoShapeStyleElement * shapeStyle);

    //! Saves normal binding when generating primitives for picking
    Binding             savedNormalBinding;

    //! Returns current material or normal binding from action's state
    Binding             getMaterialBinding(SoAction *action);
    Binding             getNormalBinding(SoAction *action,
                                         SoNormalBundle *nb);

    //! Figures out normals, if necessary. Returns TRUE if normals were
    //! generated
    bool                figureNormals(SoState *state, SoNormalBundle *nb);

    //! set numTris/Quads/Faces to -1 when notified
    virtual void        notify(SoNotList *list);
    
    //! Set number of triangles/quads/faces, based on coordIndex array.
    void setupNumTrisQuadsFaces();
    
    //! Number of triangles, quads, (n>4)-vertex faces
    int     numTris, numQuads, numFaces;

    SoVertexArrayIndexer* _triangleIndexer;
    SoVertexArrayIndexer* _quadIndexer;

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

#endif /* _SO_INDEXED_FACE_SET_ */
