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
 |      This file defines the SoRotation node class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_ROTATION_
#define  _SO_ROTATION_

#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/nodes/SoTransformation.h>


////////////////////////////////////////////////////////////////////////////////
//! Node representing a 3D rotation about an arbitrary axis.
/*!
\class SoRotation
\ingroup Nodes
This node defines a 3D rotation about an arbitrary axis through the
origin. The rotation is accumulated into the current transformation,
which is applied to subsequent shapes.  The \b rotation  field
provides a variety of methods for specifying the rotation.

\par File Format/Default
\par
\code
Rotation {
  rotation 0 0 1 0
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
SoRotationXYZ, SoTransform
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoRotation : public SoTransformation {

    SO_NODE_HEADER(SoRotation);

  public:
    //! \name Fields
    //@{

    //! Rotation specification.
    SoSFRotation        rotation;       

    //@}

    //! Creates a rotation node with default settings.
    SoRotation();

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
    virtual ~SoRotation();
};

#endif /* _SO_ROTATION_ */
