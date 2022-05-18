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
 |      Defines the SoWriteAction class
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_WRITE_ACTION_
#define  _SO_WRITE_ACTION_

#include <Inventor/system/SbSystem.h>
#include <Inventor/actions/SoAction.h>
#include <Inventor/actions/SoSubAction.h>
#include <Inventor/SoOutput.h>


////////////////////////////////////////////////////////////////////////////////
//! Writes a scene graph to a file.
/*!
\class SoWriteAction
\ingroup Actions
This class is used for writing scene graphs to files. It contains an
SoOutput instance that by default writes to the standard output.
Methods on the SoOutput can be called to specify what file or
memory buffer to write to.

\par See Also
\par
SoOutput
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoWriteAction : public SoAction {

    SO_ACTION_HEADER(SoWriteAction);

  public:

    //! Constructor.
    SoWriteAction();

    //! Constructor that takes an SoOutput to use for output.
    SoWriteAction(SoOutput *out);

    //! Destructor
    virtual ~SoWriteAction();

    //! Returns pointer to SoOutput instance in action.
    SoOutput *          getOutput() const               { return output; }

  SoINTERNAL public:
    static void         initClass();

    //! Continues write action on a graph or path
    void                continueToApply(SoNode *node);
    void                continueToApply(SoPath *path);

  protected:
    //! Initiates action on graph
    virtual void        beginTraversal(SoNode *node);

    //! Override method to return FALSE, since this action applies
    //! itself to each path separately, so it doesn't need the extra
    //! overhead of compacting the list.
    virtual bool        shouldCompactPathLists() const;

  private:
    SoOutput            *output;        //!< Output info
    bool                createdOutput;  //!< TRUE if output created by action
    bool                continuing;     //!< TRUE only if continueToApply()
                                        //! was used to apply action
    bool                doOneStage;     //!< TRUE if only supposed to do 1 stage
    SbPList             savedLists;     //!< Path lists saved for later apply

    //! Performs traversal on a path list, which is a little tricker
    void                traversePathList(SoNode *node);
};

#endif /* _SO_WRITE_ACTION_ */
