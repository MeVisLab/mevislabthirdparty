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
 |   Classes:
 |      SoV1CameraKit
 |
 |   Author(s)          : Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#include <Inventor/SoDB.h>
#include <Inventor/misc/upgraders/SoV1CameraKit.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/nodes/SoCallback.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodekits/SoAppearanceKit.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoPathSwitch.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodekits/SoSeparatorKit.h>

#include <Inventor/nodekits/SoCameraKit.h>

// Define the required type id and name inquiry methods
SO_NODE_SOURCE(SoV1CameraKit);

// Define the required catalog inquiry methods
SO_V1_SUBKIT_CATALOG_VARS(SoV1CameraKit);
SO_V1_SUBKIT_CATALOG_METHODS(SoV1CameraKit);

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Constructor
//
// Use: public

SoV1CameraKit::SoV1CameraKit()
//
////////////////////////////////////////////////////////////////////////
{
    SO_NODE_CONSTRUCTOR(SoV1CameraKit);

    if(SO_NODE_IS_FIRST_INSTANCE() ) {
    // Initialize children catalog and add entries to it
    // These are the macros you use to make a catalog.
    // Use ...INHERIT_CATALOG once, and put it first.
    // Then, use combinations of ...ADD_CATALOG_ENTRY 
    // and ...ADD_CATALOG_LIST_ENTRY.  See SoSubKit.h for more info
    // on syntax of these macros.
    SO_V1_SUBKIT_INHERIT_CATALOG(SoV1CameraKit, SoV1BaseKit );

    SO_V1_SUBKIT_ADD_CATALOG_LIST_ENTRY("callbackList", SoSeparator, "this", "",
                                        SoCallback, TRUE );
    SO_V1_SUBKIT_ADD_LIST_ITEM_TYPE("callbackList", SoEventCallback );
    SO_V1_SUBKIT_ADD_CATALOG_ENTRY("appearance", SoAppearanceKit, 
                                    "this", "", TRUE );
    SO_V1_SUBKIT_ADD_CATALOG_ENTRY("transform", SoTransform, 
                                    "this", "", TRUE );
    SO_V1_SUBKIT_ADD_CATALOG_ABSTRACT_ENTRY("camera", SoCamera, 
                                         SoPerspectiveCamera, "this", "", TRUE);
    SO_V1_SUBKIT_ADD_CATALOG_LIST_ENTRY("childList", SoSeparator, 
                                        "this", "", SoSeparatorKit, TRUE );

    }

    
    

    createNodekitPartsList();
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Destructor (necessary since inline destructor is too complex)
//
// Use: public

SoV1CameraKit::~SoV1CameraKit()
//
////////////////////////////////////////////////////////////////////////
{
}
SoNode *
SoV1CameraKit::createNewNode()
{
    return new SoCameraKit;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    A virtual function that allows classes to treat parts that fail the
//    tests of 'tryToSetPartInNewNode'
//
// If tryToSetPartInNewNode fails, then this routine is called.
// It will fail if the part read from file was called "texture2List"
// This part has been changed to a single noded part, "texture2"
// We will use just the first child of the list and set it as the "texture2"
// It will also print a warning.
//
// Use: public
//
bool 
SoV1CameraKit::dealWithUpgradedPart( SoBaseKit *newNode, SoNode *newPart, 
                                    const SbName &newPartName )
//
////////////////////////////////////////////////////////////////////////
{
    // First, try to let base class handle it...
    if ( SoV1BaseKit::dealWithUpgradedPart( newNode, newPart, newPartName ) )
        return TRUE;

    // If the part name is "appearance", or "childList", just print
    // a warning, don't set the part, and return TRUE.
    if ( newPartName == "appearance" || newPartName == "childList" ) {

        SoDebugError::postWarning("SoV1CameraKit::dealWithUpgradedPart",
            "the input file contained a part named %s. This part no longer exists, so you will unfortunately have to lose it.", newPartName.getString() );
        return TRUE;
    }

    return FALSE;   // don't know how to do anything yet...
}
