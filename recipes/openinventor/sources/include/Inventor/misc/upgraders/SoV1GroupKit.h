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
 |      Defines the SoV1GroupKit class. 
 |      Organizes an appearance, a transform, a local transform and a 
 |      group of child kits
 |
 |   Author(s)          : Paul Isaacs, Thad Beier
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
*/

#ifndef  _SO_V1_GROUP_KIT_
#define  _SO_V1_GROUP_KIT_

#include <Inventor/misc/upgraders/SoV1BaseKit.h>
#include <Inventor/misc/upgraders/SoV1AppearanceKit.h>

/////////////////////////////////////////////////////////////////////
////  \class SoV1GroupKit
///
///    New nodes in this subclass are:
///         callbackList, topSeparator, pickStyle, appearance,                 
///          transform, texture2Transform, 
///          childList
///
///      A parent node that manages a collection of child nodes 
///      into a unit with the following structure:
///
///                            this
///        |---------------------|
///     "label"     |      "topSeparator"
///            "callbackList"    |
///      ---------------------------------------------------------------
///      |       |           |     |                                   |
///  "pickStyle" |    "transform"  |                                   |
///     "appearance"  "texture2Transform"                              |
///                                                                    |
///                                                                    | 
///                                                              "childList"
///
////////////////////////////////////////////////////////////////////
SoEXTENDER class SoV1GroupKit : public SoV1BaseKit {

    //! Define typeId and name stuff
    SO_NODE_HEADER(SoV1GroupKit);

    //! Define catalog for children
    SO_V1_SUBKIT_CATALOG_HEADER(SoV1GroupKit);

  public:
    //! constructor
    SoV1GroupKit();

    virtual SoNode *createNewNode();

    //! Overload this function. After SoV1BaseKit is done, see if there
    //! is information we need in the nodelist:
    //! SoV1AppearanceKit::unusedTextureXfs.
    //! If so, move this into our "texture2Transform" part.
    //! Need to do this because Inventor 1.0 texture had fields for 
    //! texture transforms, but new one does not. So SoV1AppearanceKit just
    //! stores this info. We retrieve it and make use of it.
    virtual void setUpNewNode(SoNode *newNode);
    
    SoINTERNAL public:
    static void initClass();

  protected:
    virtual ~SoV1GroupKit();
};
#endif  /* _SO_V1_GROUP_KIT_ */
