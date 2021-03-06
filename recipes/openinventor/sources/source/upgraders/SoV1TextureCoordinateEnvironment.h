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
 |      Upgrade from 1.0 TextureCoordinateEnvironment to 2.0
 |
 |   Author(s)          : Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_V1TEXTURECOORDINATEENVIRONMENT_
#define  _SO_V1TEXTURECOORDINATEENVIRONMENT_

#include <Inventor/misc/upgraders/SoUpgrader.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/fields/SoSFVec3f.h>

///////////////////////////////////////////////////////////////////////////////
///
////  \class SoV1TextureCoordinateEnvironment
///
///  V1TextureCoordinateEnvironment for upgrading 1.0 TextureCoordinateEnvironments
///  to the 2.0 file format.
///
//////////////////////////////////////////////////////////////////////////////

class SoV1TextureCoordinateEnvironment : public SoUpgrader {

    SO_NODE_HEADER(SoV1TextureCoordinateEnvironment);

  public:
    //! Texture coordinate
    enum Coordinate {
        S,
        T,
        ALL
    };

    //! Fields.
    SoSFEnum            coord;          //!< Texture coords to affect

    //! Constructor
    SoV1TextureCoordinateEnvironment();

  SoINTERNAL public:
    static void         initClass();

    virtual SoNode      *createNewNode();

  protected:
    virtual ~SoV1TextureCoordinateEnvironment();
};

#endif /* _SO_V1TEXTURECOORDINATEENVIRONMENT_ */
