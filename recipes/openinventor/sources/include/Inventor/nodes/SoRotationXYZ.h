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
 |      This file defines the SoRotationXYZ node class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_ROTATION_XYZ_
#define  _SO_ROTATION_XYZ_

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoTransformation.h>


////////////////////////////////////////////////////////////////////////////////
//! Node representing a 3D rotation about the x-, y-, or z-axis.
/*!
\class SoRotationXYZ
\ingroup Nodes
This node defines a 3D rotation about one of the three principal axes.
The rotation is accumulated into the current transformation, which is
applied to subsequent shapes.

\par File Format/Default
\par
\code
RotationXYZ {
  axis X
  angle 0
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction, SoGetBoundingBoxAction, SoRayPickAction
<BR> Accumulates rotation transformation into the current transformation. 
\par
SoGetMatrixAction
<BR> Returns the matrix corresponding to the rotation. 

\par See Also
\par
SoRotation, SoTransform
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoRotationXYZ : public SoTransformation {

    SO_NODE_HEADER(SoRotationXYZ);

  public:
    //! Rotation axis
    enum Axis {
        X,                                      //!< x-axis
        Y,                                      //!< y-axis
        Z                                       //!< z-axis
    };

    //! \name Fields
    //@{

    //! Rotation axis.
    SoSFEnum            axis;           

    //! Rotation angle (in radians), using the right-hand rule.
    SoSFFloat           angle;          

    //@}

    //! Creates a rotation node with default settings.
    SoRotationXYZ();

    //! Returns an SbRotation equivalent to the specified rotation.
    SbRotation          getRotation() const;

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
    virtual ~SoRotationXYZ();
};

#endif /* _SO_ROTATION_XYZ_ */
