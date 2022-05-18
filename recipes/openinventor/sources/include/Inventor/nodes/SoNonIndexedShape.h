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
 |      This file defines the SoNonIndexedShape node class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_NON_INDEXED_SHAPE_
#define  _SO_NON_INDEXED_SHAPE_

#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/nodes/SoVertexShape.h>
#include <Inventor/nodes/SoVertexProperty.h>


////////////////////////////////////////////////////////////////////////////////
//! Abstract base class for all non-indexed vertex-based shapes.
/*!
\class SoNonIndexedShape
\ingroup Nodes
This node is the abstract base class for all vertex-based shapes that
are not constructed from indices, such as SoFaceSet,
SoLineSet, and SoQuadMesh.


All subclasses of SoNonIndexedShape construct objects by using the
coordinates specified in the \b vertexProperty  field (from
SoVertexShape), or the current inherited coordinates. 
The \b startIndex 
field defined by this class is now obsolete, and is provided
here only for compatibility with old files and programs.


The subclass decides what to do with this
and any subsequent coordinates. The shape is drawn with the current
lighting model and drawing style and is transformed by the current
transformation matrix.


Material, normal, and texture coordinate bindings for shapes derived
from this class ignore any index specifications. That is, a binding
value of <tt>PER_FACE_INDEXED</tt> is treated the same way as <tt>PER_FACE</tt>,
and so on.


If there aren't sufficient values in the current coordinates,
material, or texture coordinates, errors will occur.

\par See Also
\par
SoFaceSet, SoIndexedShape, SoLineSet, SoPointSet, SoQuadMesh, SoTriangleStripSet, SoVertexProperty
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoNonIndexedShape : public SoVertexShape {

    SO_NODE_ABSTRACT_HEADER(SoNonIndexedShape);

  public:
    //! \name Fields
    //@{

    //! Obsolete field, provided only for compatibility
    //! reasons.  Index of first coordinate of shape.
    SoSFInt32           startIndex;     

    //@}

  SoINTERNAL public:
    static void         initClass();

  protected:
    //! Constructor - makes this abstract
    SoNonIndexedShape();

    //! This is a convenience method to simplify the job of computing
    //! bounding boxes for subclasses; it can be called from a
    //! subclass's computeBBox() method. It sets the given bounding box
    //! to contain all vertices of the shape, assuming that the shape
    //! uses the numVertices coordinates beginning at the value in
    //! startIndex. (If numVertices is negative, it uses all
    //! coordinates from startIndex on.) It also sets the center to the
    //! average of the vertices' coordinates.
    void                computeCoordBBox(SoAction *action, int numVertices,
                                         SbBox3f &box, SbVec3f &center);

    virtual ~SoNonIndexedShape();
};

#endif /* _SO_NON_INDEXED_SHAPE_ */
