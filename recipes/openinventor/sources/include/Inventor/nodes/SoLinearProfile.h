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
 |      This file defines the SoLinearProfile node class.
 |
 |   Author(s)          : Thad Beier, Dave Immel, Paul Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_LINEAR_PROFILE_
#define  _SO_LINEAR_PROFILE_

#include <Inventor/system/SbSystem.h>
#include <Inventor/nodes/SoProfile.h>


//! This value, when used as the last value of the index field, 
//! the coordinates, starting from the last index+1 (zero if there is
//! only one value in the index field).
#define SO_LINEAR_PROFILE_USE_REST_OF_VERTICES  (-1)

////////////////////////////////////////////////////////////////////////////////
//! Piecewise-linear profile curve.
/*!
\class SoLinearProfile
\ingroup Nodes
This node specifies a piecewise-linear curve that is used as a profile
for either a trimming patch of a Nurbs surface or for the bevel of
SoText3.  The \b index  field indexes into the current profile
coordinates (specified in an SoProfileCoordinate2 or
SoProfileCoordinate3 node).
If the last value of the \b index  field is
<tt>SO_LINEAR_PROFILE_USE_REST_OF_VERTICES</tt> (-1), all remaining
coordinates in the current coordinates will be used, starting with
the coordinate after the previous index (all coordinates will be used
if <tt>SO_LINEAR_PROFILE_USE_REST_OF_VERTICES</tt> is the only value in the
\b index  field).  For example, if \b index  contains the values
<tt>[2,0,-1]</tt> and there are 4 profile coordinates (0-3), it is as if
the \b index  field contains <tt>[2,0,1,2,3]</tt>.

\par File Format/Default
\par
\code
LinearProfile {
  index 0
  linkage START_FIRST
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoRayPickAction, SoCallbackAction
<BR> Adds a profile to the current state. 

\par See Also
\par
SoNurbsProfile, SoProfileCoordinate2, SoProfileCoordinate3
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoLinearProfile : public SoProfile{

    SO_NODE_HEADER(SoLinearProfile);

  public:

    //! Creates a linear profile node with default settings.
    SoLinearProfile();

  SoEXTENDER public:
    //! Returns a profile as a trim curve.  numKnots will be zero.
    //! floatsPerVec will be either 2 or 3 depending on whether the
    //! curve is non-rational or rational.
    virtual void        getTrimCurve(SoState *state, int32_t &numPoints,
                                     float *&points, int &floatsPerVec,
                                     int32_t &numKnots, float *&knotVector);

    //! Returns vertices defining the profile
    virtual void        getVertices(SoState *state, int32_t &nVertices,
                                    SbVec2f *&vertices);

  SoINTERNAL public:
    static void         initClass();

  protected:
    virtual ~SoLinearProfile();
};

#endif /* _SO_LINEAR_PROFILE_ */
