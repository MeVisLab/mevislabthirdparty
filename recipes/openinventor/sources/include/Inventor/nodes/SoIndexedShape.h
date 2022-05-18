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
 |      This file defines the SoIndexedShape node class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_INDEXED_SHAPE_
#define  _SO_INDEXED_SHAPE_

#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/nodes/SoVertexShape.h>


////////////////////////////////////////////////////////////////////////////////
//! Abstract base class for all indexed vertex-based shapes.
/*!
\class SoIndexedShape
\ingroup Nodes
This node is the abstract base class for all vertex-based shapes that
are constructed from indices, including SoIndexedFaceSet,
SoIndexedTriangleStripSet, and SoIndexedLineSet.
SoIndexedShape defines fields that are used in all of its
subclasses.


All subclasses of SoNonIndexedShape construct objects by using the
coordinates specified by the \b vertexProperty  field
(from SoVertexShape), or the current inherited coordinates. 
The \b coordIndex 
field defined by this class contains the indices into the current
coordinates of the vertices of the shape. These indices are also used
for materials, normals, or texture coordinates when the appropriate
binding is <tt>PER_VERTEX_INDEXED</tt>.


Material and normal bindings are interpreted as follows for each subclass:
\code
OVERALL		One material for the entire shape.
PER_PART		Specific to the subclass.
PER_PART_INDEXED	Same as PER_PART, using indices from the
			materialIndex or normalIndex field.
PER_FACE		Specific to the subclass.
PER_FACE_INDEXED	Same as PER_FACE, using indices from the
			materialIndex or normalIndex field.
PER_VERTEX		One material per vertex.
PER_VERTEX_INDEXED	One material per vertex, using indices from the
			materialIndex or normalIndex field.
\endcode


When any <tt>_INDEXED</tt> binding is used for materials or normals, the
\b materialIndex  or \b normalIndex  field is used to determine the
indices for the materials or normals. If this field contains a single
value of -1 (the default), the coordinate indices from the
\b coordIndex  field are used as well for materials or normals. When
the binding is <tt>PER_VERTEX_INDEXED</tt>, indices in these fields that
correspond to negative indices in \b coordIndex  are skipped; for
other index bindings all the values in the fields are used, in order.


Explicit texture coordinates (as defined by SoTextureCoordinate2)
may be bound to vertices of an indexed
shape consecutively (if the texture coordinate binding is
<tt>PER_VERTEX</tt>) or by using the indices in the \b textureCoordIndex 
field (if the binding is <tt>PER_VERTEX_INDEXED</tt>). As with all
vertex-based shapes, if there is a current texture but no texture
coordinates are specified, a default texture coordinate mapping is
calculated using the bounding box of the shape.


Be sure that the indices contained in the \b coordIndex ,
\b materialIndex , \b normalIndex , and \b textureCoordIndex  fields
are valid with respect to the current state, or errors will occur.

\par See Also
\par
SoIndexedFaceSet, SoIndexedTriangleSet, SoIndexedLineSet, SoIndexedTriangleStripSet, SoMaterialBinding, SoNonIndexedShape, SoNormalBinding, SoShapeHints, SoTextureCoordinateBinding
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoIndexedShape : public SoVertexShape {

    SO_NODE_ABSTRACT_HEADER(SoIndexedShape);

  public:
    //! \name Fields
    //@{

    //! The indices of the coordinates that the shape uses as its vertices.
    //! The coordinates connect to form faces, lines, or other shapes. Each
    //! subclass defines special negative indices to use to indicate
    //! separation between faces, lines, and so on.
    SoMFInt32           coordIndex;             
    //! Material indices
    SoMFInt32           materialIndex;          
    //! Surface normal indices
    SoMFInt32           normalIndex;            
    //! Texture Coordinate indices
    SoMFInt32           textureCoordIndex;      

    //@}

  SoINTERNAL public:
    static void         initClass();

  protected:
    //! Constructor - makes this abstract
    SoIndexedShape();

    //! This handles bounding box computation for all shapes derived
    //! from this class. It sets the bounding box to contain all
    //! vertices of the shape, assuming that the shape uses the
    //! coordinates indexed by all non-negative values in the
    //! coordIndex field. It also sets the center to the average of the
    //! vertices' coordinates.
    virtual void        computeBBox(SoAction *action, SbBox3f &box,
                                    SbVec3f &center);

    //! Returns TRUE if texture coordinates should be indexed
    static bool         areTexCoordsIndexed(SoAction *action);

    //! Starting at a given index in the coordIndex array, figure out
    //! how many vertices there are before either the end of the array
    //! or the next 'border' index
    int                 getNumVerts(int startCoord);

    //! Setup for fast rendering.  This should be called by subclasses,
    //! which can then use the textureI/colorI/normalI arrays (which
    //! will either point to one of the coordIndex arrays, or to a
    //! consective array of integers.  This must be called AFTER the
    //! vpCache has been filled in.
    void                setupIndices(int numParts, int numFaces,
                                bool needNormals, bool needTexCoords);

    //! These must not be called unless setupIndices has been called first:
    const int32_t *     getNormalIndices()
        { return (normalI ? normalI : consecutiveIndices); }
    const int32_t *     getColorIndices()
        { return (colorI ? colorI : consecutiveIndices); }
    const int32_t *     getTexCoordIndices()
        { return (texCoordI ? texCoordI : consecutiveIndices); }

    //! Keep indices up to date if things change
    virtual void        notify(SoNotList *list);

    virtual ~SoIndexedShape();

  private:
    //! Internal routines used to allocate sequential indices so the
    //! same rendering loops can be used for indexed or non-indexed
    //! cases:
    void        allocateSequential(int howMany);
    int32_t*    allocateSequentialWithHoles();

    //! These are filled in by the setupIndices routine:
    const int32_t       *texCoordI;
    const int32_t       *colorI;
    const int32_t       *normalI;
    static int32_t      *consecutiveIndices;
    static int  numConsecutiveIndicesAllocated;

    unsigned char materialBinding;
    unsigned char normalBinding;
    unsigned char texCoordBinding;
};

#endif /* _SO_INDEXED_SHAPE_ */
