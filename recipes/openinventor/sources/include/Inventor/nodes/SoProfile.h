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
 |   $Revision $
 |
 |   Description:
 |      This file defines the SoProfile node class.
 |
 |   Author(s)          : Thad Beier, Dave Immel, Paul Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_PROFILE_
#define  _SO_PROFILE_

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoProfileElement.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoSubNode.h>


////////////////////////////////////////////////////////////////////////////////
//! Abstract base class for all profile nodes.
/*!
\class SoProfile
\ingroup Nodes
This node is the abstract base class for all profile nodes, which
define 2D curves. A profile is not itself geometry, but is used to
change or delimit the geometry of something else. For an SoText3
node, the profile determines the cross-section of the side of each
text character. For an SoNurbsSurface node, the profile is used to
specify trim curves for the surface.


The current profile state can consist of one or more profiles, each of
which can be made up of one or more instances of SoProfile
subclass nodes. Each profile node specifies (in the \b index  field) a
set of indices that refer to the current set of profile coordinates,
specified using either an SoProfileCoordinate2 or an
SoProfileCoordinate3 node. No profile curve should intersect
itself or another profile curve.


Profiles are part of the state, just like all other properties. The
state contains a current list of profiles.  Depending on the
\b linkage  field, a profile can clear the list and begin a new
profile, begin a new profile at the end of those already in the list,
or append to the last profile in the current list. Note that when
appending profile B to the end of profile A, B must begin at the same
2D point at which A ends.

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction, SoGetBoundingBoxAction, SoRayPickAction
<BR> Adds profile to current traversal state. 

\par See Also
\par
SoLinearProfile, SoNurbsProfile, SoNurbsSurface, SoProfileCoordinate2, SoProfileCoordinate3, SoText3
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoProfile : public SoNode{

    SO_NODE_ABSTRACT_HEADER(SoProfile);

  public:
    enum Profile {
        START_FIRST    = SoProfileElement::START_FIRST,
        START_NEW      = SoProfileElement::START_NEW,
        ADD_TO_CURRENT = SoProfileElement::ADD_TO_CURRENT
    };

    //! \name Fields
    //@{

    //! Indices into profile coordinates.
    SoMFInt32           index;        

    //! Specifies connectivity of profile curve with respect to profiles in
    //! current list in state.
    SoSFEnum            linkage;      

    //@}

  SoEXTENDER public:
    //! These action methods are implemented for profiles. Each of them
    //! just adds the profile to the current state.
    virtual void        doAction(SoAction *action);
    virtual void        callback(SoCallbackAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void        pick(SoPickAction *action);

    //! Returns a profile as a trim curve.  numKnots is zero if the
    //! curve is linear. floatsPerVec will be either 2 or 3 depending
    //! on whether the curve is non-rational or rational.
    virtual void        getTrimCurve(SoState *state, int32_t &numPoints,
                                     float *&points, int &floatsPerVec,
                                     int32_t &numKnots, float *&knotVector) = 0;

    //! Returns vertices approximating the profile
    virtual void        getVertices(SoState *state, int32_t &nVertices,
                                    SbVec2f *&vertices) = 0;

  SoINTERNAL public:
    static void         initClass();

  protected:
    SoProfile();

    virtual ~SoProfile();
};

#endif /* _SO_PROFILE_ */
