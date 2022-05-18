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
 * Copyright (C) 1990,91,92  Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.1.1.1 $
 |
 |   Description:
 |      This file defines the SoProfileCoordinate3 node class.
 |
 |   Author(s)          : Thad Beier, Dave Immel, Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_PROFILE_COORDINATE_3_
#define  _SO_PROFILE_COORDINATE_3_

#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/nodes/SoSubNode.h>


////////////////////////////////////////////////////////////////////////////////
//! Rational profile coordinate node.
/*!
\class SoProfileCoordinate3
\ingroup Nodes
This node defines a set of rational 3D coordinates to be used by
subsequent SoProfile nodes. (These coordinates may be used for any
type of profile; they may be useful in some cases for specifying
control points for SoNurbsProfile nodes.) This node does not
produce a visible result during rendering; it simply replaces the
current profile coordinates in the traversal state for subsequent
nodes to use.

\par File Format/Default
\par
\code
ProfileCoordinate3 {
  point 0 0 1
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction, SoGetBoundingBoxAction, SoRayPickAction
<BR> Sets profile coordinates in current traversal state. 

\par See Also
\par
SoProfile, SoProfileCoordinate2
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoProfileCoordinate3 : public SoNode {

    SO_NODE_HEADER(SoProfileCoordinate3);

  public:
    //! \name Fields
    //@{

    //! Rational 3D profile coordinate points.
    SoMFVec3f           point;          

    //@}

    //! Creates a profile coordinate node with default settings.
    SoProfileCoordinate3();

  SoEXTENDER public:
    virtual void        doAction(SoAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        callback(SoCallbackAction *action);
    virtual void        pick(SoPickAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    virtual ~SoProfileCoordinate3();
};

#endif /* _SO_PROFILE_COORDINATE_3_ */
