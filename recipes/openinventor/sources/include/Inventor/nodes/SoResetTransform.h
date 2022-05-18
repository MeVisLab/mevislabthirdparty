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
 |      This file defines the SoResetTransform node class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_RESET_TRANSFORM_
#define  _SO_RESET_TRANSFORM_

#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/nodes/SoTransformation.h>


////////////////////////////////////////////////////////////////////////////////
//! Node that resets the current transformation to identity.
/*!
\class SoResetTransform
\ingroup Nodes
This node resets the current transformation to identity. It can be
used to apply an absolute world space transformation afterwards, such
as translating to a specific point from within a hierarchy.
An SoResetTransform node should probably be used under an
SoSeparator or SoTransformSeparator so it won't change
transformations for the rest of the scene graph.
An SoResetTransform node can also be used to reset the current
bounding box to empty during traversal of an
SoGetBoundingBoxAction, if the \b whatToReset  field has the
\b BBOX  bit set.

\par File Format/Default
\par
\code
ResetTransform {
  whatToReset TRANSFORM
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction, SoRayPickAction
<BR> If specified, resets current transformation matrix to identity. 
\par
SoGetBoundingBoxAction
<BR> If specified, resets current transformation matrix to identity and current computed bounding box to be empty. 
\par
SoGetMatrixAction
<BR> Returns identity matrix. 

\par See Also
\par
SoTransform
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoResetTransform : public SoTransformation {

    SO_NODE_HEADER(SoResetTransform);

  public:
    //! Which things get reset:
    enum ResetType {
        TRANSFORM       = 0x01,                 //!< Transformation
        BBOX            = 0x02                  //!< Bounding box
    };

    //! \name Fields
    //@{

    //! Specifies which items to reset when the node is traversed.
    SoSFBitMask         whatToReset;    

    //@}

    //! Creates a reset transformation node with default settings.
    SoResetTransform();

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
    virtual ~SoResetTransform();
};

#endif /* _SO_RESET_TRANSFORM_ */
