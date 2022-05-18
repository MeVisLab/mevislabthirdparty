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
 |      Defines the SoV1DirectionalLightKit class. 
 |      Subclassed off of SoV1LightKit, this class adds an SoDirectionalLight
 |      node to the catalog.
 |
 |   Author(s)          : Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
*/

#ifndef  _SO_V1_DIRECTIONAL_LIGHT_KIT_
#define  _SO_V1_DIRECTIONAL_LIGHT_KIT_

#include <Inventor/misc/upgraders/SoV1LightKit.h>

/////////////////////////////////////////////////////////////////////
////  \class SoV1DirectionalLightKit
///
///    New nodes in this subclass are:
///         directionalLight
///
///      A parent node that manages a collection of child nodes 
///      into a unit with the following structure:
///
///                            this
///     ------------------------------------------------------------------
///     |     |         |               |       |                       |
/// "label"   |     "appearance"   "transform"  |                       |
///      "callbackList"                         |                   "childList"
///                                          "light"
///                                           
////////////////////////////////////////////////////////////////////

SoEXTENDER class SoV1DirectionalLightKit : public SoV1LightKit {

    //! Define typeId and name stuff
    SO_NODE_HEADER(SoV1DirectionalLightKit);

    //! Define catalog for children
    SO_V1_SUBKIT_CATALOG_HEADER(SoV1DirectionalLightKit);

  public:
    //! constructor
    SoV1DirectionalLightKit();

    virtual SoNode *createNewNode();
    
    SoINTERNAL public:
    static void initClass();

  protected:
    virtual ~SoV1DirectionalLightKit();
};
#endif  /* _SO_V1_DIRECTIONAL_LIGHT_KIT_ */
