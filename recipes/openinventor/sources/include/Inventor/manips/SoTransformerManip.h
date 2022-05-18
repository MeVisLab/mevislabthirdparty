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
 * Copyright (C) 1994   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   Description:
 |      This file defines the SoTransformerManip class.
 |      It uses a SoTransformerDragger to edit the fields of a hideableTransformManip
 |
 |   Author(s): Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TRANSFORMER_MANIP_
#define  _SO_TRANSFORMER_MANIP_

#include <Inventor/manips/SoTransformManip.h>


////////////////////////////////////////////////////////////////////////////////
//! Transform node with 3D interface for changing scaling, rotation, and translation.
/*!
\class SoTransformerManip
\ingroup Manips
This is a new manipulator with some improvements over the older inventor
manips.  It has the following features:  [1] full interface for rotate, 
translate, and scale, [2] better feedback, [3] locate highlighting. 


SoTransformerManip 
is derived from SoTransform (by way of SoTransformManip).
When its fields 
change, nodes following it in the scene graph rotate, scale, and/or translate.


As a subclass of SoTransformManip, this manipulator
also has a 3D interface to edit some of its fields.
In this case, the interface edits the \b scaleFactor , \b rotation 
and \b translation  fields.


A manipulator differs from a dragger. When you move a dragger,
no other nodes are affected.  When you move an SoTransformManip,
other nodes move along with it.
(See the reference page for SoTransformManip).


The interface for an SoTransformerManip is exactly the same as that
of the SoTransformerDragger.  
To find out more about the interface, see the reference page 
for SoTransformerDragger.  To find out how the manipulator uses a 
dragger to provide its interface, see the reference page for 
SoTransformManip.


On screen, this manipulator will surround the objects influenced by its
motion.  This is because it turns on the <em>surroundScale</em> part of the
dragger (See the reference page for SoSurroundScale)

\par File Format/Default
\par
\code
TransformerManip {
  translation 0 0 0
  rotation 0 0 1 0
  scaleFactor 1 1 1
  scaleOrientation 0 0 1 0
  center 0 0 0
}
\endcode

\par See Also
\par
SoTransformerDragger, SoTransform, SoCenterballManip, SoHandleBoxManip, SoJackManip, SoTabBoxManip, SoTrackballManip, SoTransformBoxManip, SoTransformManip
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoTransformerManip : public SoTransformManip {

    SO_NODE_HEADER(SoTransformerManip);

  public:

    //! Constructor.
    SoTransformerManip();

    //! Tells the dragger inside this manip to unsquish its rotation and scale knobs 
    //! during the next traversal.
    //! Ordinarily, the knobs are only unsquished upon readin from file and when
    //! the mouse button is released at the end of a drag. If you want this to
    //! happen more often, then you should call this method.
    void unsquishKnobs();

    //! Controls whether or not the dragger inside this manip will perform locate 
    //! highlighting is used.  Default is TRUE.
    bool isLocateHighlighting();
    //! Controls whether or not the dragger inside this manip will perform locate 
    //! highlighting is used.  Default is TRUE.
    void setLocateHighlighting( bool onOff );

  SoINTERNAL public:
    static void         initClass();    //!< initialize the class

  protected:
    virtual ~SoTransformerManip();
};

#endif /* _SO_TRANSFORMER_MANIP_ */
