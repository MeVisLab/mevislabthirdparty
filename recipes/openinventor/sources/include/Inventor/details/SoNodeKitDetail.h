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
 |      This file defines classes for describing or extracting
 |      detail information about a node kit.
 | 
 |
 |   The details contains a pointer to the node, a pointer to the 
 |   child part within the node, and the name of the child part.
 |   
 |   Classes:
 |      SoNodeKitDetail
 |
 |   Author(s)          : Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SO_NODE_KIT_DETAIL_
#define _SO_NODE_KIT_DETAIL_

#include <Inventor/system/SbSystem.h>
#include <Inventor/details/SoSubDetail.h>

class SoNode;
class SoBaseKit;


////////////////////////////////////////////////////////////////////////////////
//! Stores detail information about a nodekit.
/*!
\class SoNodeKitDetail
\ingroup Details
This class contains detail information about a nodekit.
This consists of a pointer to the nodekit, a pointer to the 
child part within the nodekit, and the name of the child part.


During a pick action, each nodekit along the picked path creates its own
SoNodeKitDetail.   Together, the full set of details gives you 
complete picture of the pickpath.  


Since nodekits have hidden children (See the reference page for 
SoBaseKit), a regular SoPath ends at the topmost nodekit in the 
path. If you cast the pickpath from an SoPath pointer to an 
SoNodeKitPath pointer, you can then retrieve all nodekits along the 
path and examine their corresponding details.

\par See Also
\par
SoBaseKit, SoNodeKitPath, SoDetail, SoPickedPoint
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoNodeKitDetail : public SoDetail {
    
    SO_DETAIL_HEADER(SoNodeKitDetail);

  public:

    //! Constructor and destructor.
    SoNodeKitDetail();
    //! Constructor and destructor.
    virtual ~SoNodeKitDetail();

    //! Returns a pointer to the nodekit that created this detail
    SoBaseKit *getNodeKit() const { return myNodeKit; }

    //! Returns a pointer to the part selected within the nodekit that 
    //! created this detail.
    SoNode *getPart() const { return myPart; }

    //! Returns the name of the part selected within the nodekit that created 
    //! this detail. (See SoRayPickAction  in the ACTIONS section of 
    //! the SoBaseKit reference page for more information).
    const SbName &getPartName() const { return myPartName; }

    //! Returns an instance that is a copy of this instance. The caller
    //! is responsible for deleting the copy when done.
    virtual SoDetail *  copy() const;

  SoEXTENDER public:

    void setNodeKit( SoBaseKit *theNodeKit );
    void setPart( SoNode *thePart );
    void setPartName( const SbName &theName )      { myPartName = theName; }

  SoINTERNAL public:
    static void         initClass();

  protected:
    SoBaseKit       *myNodeKit;
    SoNode          *myPart;
    SbName          myPartName;
};

#endif /* _SO_NODE_KIT_DETAIL_ */

