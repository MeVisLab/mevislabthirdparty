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
 |      This file defines the SoIndexedTriangleSet node class.
 |
 |   Author(s)          : Paul S. Strauss, Gavin Bell, Florian Link
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_INDEXED_TRIANGLE_SET_
#define  _SO_INDEXED_TRIANGLE_SET_

#include <Inventor/system/SbSystem.h>
#include <Inventor/nodes/SoIndexedShape.h>
#include <Inventor/fields/SoSFBool.h>

class SoVertexArrayIndexer;

///////////////////////////////////////////////////////////////////////////////
///
///  \class SoIndexedTriangleSet
///  \ingroup Nodes
///
///  Indexed set of triangles. Each triangle consists of 3 vertices,
///  each of which is denoted by an integer index (from the coordIndex
///  field) into the current coordinates.
///  This is a specialized version of SoIndexedFaceSet, which offers
///  slightly faster updates/rendering, since it only renders triangles.
///  Unlike SoIndexedFaceSet, no -1 separators in the coordIndex field
///  are needed nor supported.
///  Depending on the current material and normal binding values, the materials and normals for
///  the faces or vertices may be accessed in order or indexed. If they
///  are indexed, the materialIndex and normalIndex fields are used.
///
///  (MeVis ONLY, VSG3D also has this node)
///
//////////////////////////////////////////////////////////////////////////////

class SoNormalBundle;
class SoCoordinateElement;
class SoShapeStyleElement;

class INVENTOR_API SoIndexedTriangleSet : public SoIndexedShape {

    SO_NODE_HEADER(SoIndexedTriangleSet);

  public:
    // \name Fields
    //@{
    //! flag that defines if the GL_TRIANGLES_ADJACENCY draw mode is used
    SoSFBool sendAdjacency;
    //@}

    //! Constructor
    SoIndexedTriangleSet();

  SoEXTENDER public:
    //! Implements actions
    virtual void        GLRender(SoGLRenderAction *action);

    //! Generates default normals using the given normal bundle. 
    //! Returns TRUE.
    virtual bool        generateDefaultNormals(SoState *state,
                                               SoNormalBundle *nb);

    //! Typedef of pointer to method on IndexedTriangleSet;
    //! This will be used to simplify declaration and initialization.
    typedef void (SoIndexedTriangleSet::*PMFS)(SoGLRenderAction *);
                                                  
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
    ~SoIndexedTriangleSet();

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

    //! invalidate cache when notified
    virtual void        notify(SoNotList *list);

    //! Set number of triangles.
    void setupNumTrisQuadsFaces();

    //! Number of triangles
    int     numTris;

    SoVertexArrayIndexer* _triangleIndexer;

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

    //! Array of function pointers to render functions:
    static PMFS TriRenderFunc[32];
};

#endif /* _SO_INDEXED_TRIANGLE_SET_ */
