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
 * Copyright (C) 1990,91,92   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.1.1.1 $
 |
 |   Description:
 |      This file contains the implementation of the
 |      SoComputeBoundingBox engine
 |
 |   Classes:
 |      SoComputeBoundingBox
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_COMPUTE_BOUNDING_BOX_
#define  _SO_COMPUTE_BOUNDING_BOX_

#include <Inventor/system/SbSystem.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFPath.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFVec3f.h>

class SoGetBoundingBoxAction;


////////////////////////////////////////////////////////////////////////////////
//! Computes the bounding box and center of a scene graph.
/*!
\class SoComputeBoundingBox
\ingroup Engines
This engine computes the bounding box and center of a scene graph.
The scene graph can be defined by a path or by a root node.  


If the \b path  input is not NULL, the
bounding box of the graph defined by the path will be computed.
If \b path  is NULL, but the \b node  input is not NULL, the bounding
box is computed on the graph rooted by the node.
By default, the two inputs are NULL.  
If both the inputs are NULL, the outputs are disabled.


The engine uses a default viewport region.  If the graph includes
screen-based objects (such as SoText2) you can call setViewportRegion() 
on the engine instance to set up the correct viewport region to use.

\par File Format/Default
\par
\code
ComputeBoundingBox {
  path NULL
}
\endcode

\par See Also
\par
SoEngineOutput, SoGetBoundingBoxAction, SbBox3f
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoComputeBoundingBox : public SoEngine {

    SO_ENGINE_HEADER(SoComputeBoundingBox);

  public:
    //! Inputs:
    SoSFNode            node;           //!< Pointer to root node of graph
    SoSFPath            path;           //!< Pointer to path defining graph

    //! Outputs:
    SoEngineOutput      min;            //!< (SoSFVec3f) Minimum point of bbox
    SoEngineOutput      max;            //!< (SoSFVec3f) Maximum point of bbox
    SoEngineOutput      boxCenter;      //!< (SoSFVec3f) Center point of bbox
    SoEngineOutput      objectCenter;   //!< (SoSFVec3f) Center of object(s)

    //! Constructor
    SoComputeBoundingBox();

    //! Sets the viewport region to use for the bounding box computation.
    void                   setViewportRegion(const SbViewportRegion &vpReg);
    const SbViewportRegion &getViewportRegion() const;

  SoINTERNAL public:
    static void                 initClass();

  protected:
    //! Indicates that an input has changed - we use this to determine
    //! whether to use the node or path, or to disable output entirely
    virtual void                inputChanged(SoField *whichInput);

  private:
    //! Pointer to SoGetBoundingBoxAction
    SoGetBoundingBoxAction      *bba;

    //! Each of these is TRUE if the corresponding input pointer is non-NULL
    bool                        gotNode;
    bool                        gotPath;

    //! Destructor
    virtual ~SoComputeBoundingBox();

    //! Evaluation method
    virtual void        evaluate();
};

#endif  /* _SO_COMPUTE_BOUNDING_BOX_ */
