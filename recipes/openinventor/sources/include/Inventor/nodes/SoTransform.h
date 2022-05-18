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
 |      This file defines the SoTransform node class.
 |
 |   Author(s)          : Paul S. Strauss, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TRANSFORM_
#define  _SO_TRANSFORM_

#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/nodes/SoTransformation.h>


////////////////////////////////////////////////////////////////////////////////
//! General 3D geometric transformation node.
/*!
\class SoTransform
\ingroup Nodes
This node defines a geometric 3D transformation consisting of (in
order) a (possibly) non-uniform scale about an arbitrary point, a
rotation about an arbitrary point and axis, and a translation. (While
the transformations can be thought of as being applied in that order,
matrices are actually premultiplied in the opposite order. Therefore,
the operations are listed in the reverse order throughout this reference
page.)

\par File Format/Default
\par
\code
Transform {
  translation 0 0 0
  rotation 0 0 1 0
  scaleFactor 1 1 1
  scaleOrientation 0 0 1 0
  center 0 0 0
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction, SoGetBoundingBoxAction, SoRayPickAction
<BR> Accumulates transformation into the current transformation. 
\par
SoGetMatrixAction
<BR> Returns the matrix corresponding to the total transformation. 

\par See Also
\par
SoMatrixTransform, SoResetTransform, SoRotation, SoRotationXYZ, SoScale, SoTransformManip, SoTransformSeparator, SoTranslation
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoTransform : public SoTransformation {

    SO_NODE_HEADER(SoTransform);

  public:
    //! \name Fields
    //@{

    //! Translation vector.
    SoSFVec3f           translation;     

    //! Rotation specification.
    SoSFRotation        rotation;        

    //! Scale factors.
    SoSFVec3f           scaleFactor;     

    //! Rotational orientation for scale.
    SoSFRotation        scaleOrientation;

    //! Origin for scale and rotation.
    SoSFVec3f           center;          

    //@}

    //! Creates a transformation node with default settings.
    SoTransform();

    //! Sets the node to translate the origin to the \b fromPoint  and rotate
    //! the negative z-axis (0,0,-1) to lie on the vector from \b fromPoint 
    //! to \b toPoint . This always tries to keep the "up" direction the
    //! positive y-axis, unless that is impossible.  All current field values
    //! in the node are replaced.
    void                pointAt(const SbVec3f &fromPoint,
                                const SbVec3f &toPoint);

    //! These return composite matrices that transform from object space to each
    //! of the spaces after the scale, rotation, or translation.
    void                getScaleSpaceMatrix(SbMatrix &mat, SbMatrix &inv) const;
    //! These return composite matrices that transform from object space to each
    //! of the spaces after the scale, rotation, or translation.
    void                getRotationSpaceMatrix(SbMatrix &mat,
                                               SbMatrix &inv) const;
    //! These return composite matrices that transform from object space to each
    //! of the spaces after the scale, rotation, or translation.
    void                getTranslationSpaceMatrix(SbMatrix &mat,
                                                  SbMatrix &inv) const;

    //! These are convenience functions that combine the effects of a matrix
    //! transformation into the current transformation stored in this node.
    //! This method premultiplies the transformation.
    void                multLeft(const SbMatrix &mat);
    //! These are convenience functions that combine the effects of a matrix
    //! transformation into the current transformation stored in this node.
    //! This method postmultiplies the transformation.
    void                multRight(const SbMatrix &mat);

    //! These are convenience functions that combine the effects of another
    //! transformation node into the current transformation stored in this
    //! node.
    //! This method premultiplies the transformation.
    void                combineLeft(SoTransformation *nodeOnLeft);
    //! These are convenience functions that combine the effects of another
    //! transformation node into the current transformation stored in this
    //! node.  The first method premultiplies the transformation and the
    //! This method postmultiplies the transformation.
    void                combineRight(SoTransformation *nodeOnRight);

    //! Sets the fields in the node to implement the transformation
    //! represented by the given matrix. Note that invalid matrices (such as
    //! singular ones) have undefined results.
    void                setMatrix(const SbMatrix &mat);

    //! Changes the center of the transformation to the given point without
    //! affecting the overall effect of the transformation.
    void                recenter(const SbVec3f &newCenter);

  SoEXTENDER public:
    virtual void        doAction(SoAction *action);
    virtual void        callback(SoCallbackAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void        getMatrix(SoGetMatrixAction *action);
    virtual void        pick(SoPickAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    virtual ~SoTransform();
};

#endif /* _SO_TRANSFORM_ */
