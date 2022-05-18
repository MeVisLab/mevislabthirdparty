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
 |      This file defines the (abstract) base SoDetail class.
 |
 |   Author(s)          : Dave Immel, Howard Look, Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SO_DETAIL_
#define _SO_DETAIL_

#include <Inventor/system/SbSystem.h>
#include <Inventor/SoType.h>


////////////////////////////////////////////////////////////////////////////////
//! Base class for describing detail information about a shape node.
/*!
\class SoDetail
\ingroup Details
SoDetail is the abstract base class for all detail classes. A
detail contains shape-specific information about a particular shape
during picking and primitive generation. Subclasses store information
based on the particular type of shape.

\par See Also
\par
SoConeDetail, SoCubeDetail, SoCylinderDetail, SoDetailList, SoFaceDetail, SoLineDetail, SoNodeKitDetail, SoPickedPoint, SoPointDetail, SoPrimitiveVertex, SoTextDetail
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoDetail {
  public:
    //! Destructor
    virtual ~SoDetail();

    //! Returns type identifier for this class.
    static SoType       getClassTypeId() { return classTypeId; }

    //! Returns the type identifier for a specific instance.
    virtual SoType      getTypeId() const = 0;

    //! Returns TRUE if this object is of the type specified in \p type or is
    //! derived from that type.  Otherwise, it returns FALSE.
    bool                isOfType(SoType type) const;

    //! Returns an instance that is a copy of this instance. The caller
    //! is responsible for deleting the copy when done.
    virtual SoDetail *  copy() const = 0;

  SoINTERNAL public:
    static void         initClass();

    //! Initialize ALL Inventor detail classes
    static void         initClasses();

  protected:
    //! Constructor is protected since this is an abstract class
    SoDetail();

  private:
    static SoType       classTypeId;            //!< Type identifier
};

#endif /* _SO_DETAIL_ */

