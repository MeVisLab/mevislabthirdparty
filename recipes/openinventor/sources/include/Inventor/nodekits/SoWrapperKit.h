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
 |      Defines the SoWrapperKit class. 
 |      A group kit which has a place to attach any inventor subgraph
 |      of any unspecified structure.
 |
 |   Author(s)          : Paul Isaacs, Thad Beier
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
*/

#ifndef  _SO_WRAPPER_KIT_
#define  _SO_WRAPPER_KIT_

#include <Inventor/nodekits/SoSeparatorKit.h>


////////////////////////////////////////////////////////////////////////////////
//! Wrapper nodekit class.
/*!
\class SoWrapperKit
\ingroup Nodekits
SoWrapperKit is derived from SoSeparatorKit.
It adds the capability to wrap an arbitrary scene graph, (non-nodekit),
within an SoSeparatorKit, so that it may be used along with other
shape kits in a hierarchy. There are two additional parts
included in SoWrapperKit: <em>localTransform</em> and <em>contents</em>.


The part <em>contents</em> is an SoSeparator node beneath which
any arbitrary scene graph can be added. This is especially useful
for importing scene graphs of unknown structure (non-nodekits)
into nodekit format.


Since an SoWrapperKit is a class descended from SoSeparatorKit,
it may be put into another SoSeparatorKit's <em>childList</em>.

\par Parts
\par
\b localTransform
<BR> This part is an SoTransform node that is used to 	affect the scene graph defined in <em>contents</em> part. 	This part is <tt>NULL</tt> by default and is automatically 	created if requested. 
\par
\b contents
<BR> This part is an SoSeparator node that contains 	a user-supplied scene graph.  This scene graph can contain 	any nodes.  This part is <tt>NULL</tt> by default and an SoSeparator 	is automatically  	created if the user asks the nodekit to build the part.

\par See Also
\par
SoAppearanceKit, SoBaseKit, SoCameraKit, SoLightKit, SoNodeKit, SoNodeKitDetail, SoNodeKitListPart, SoNodeKitPath, SoNodekitCatalog, SoSceneKit, SoSeparatorKit, SoShapeKit
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoWrapperKit : public SoSeparatorKit {

    SO_KIT_HEADER(SoWrapperKit);

    //! defines fields for the new parts in the catalog
    SO_KIT_CATALOG_ENTRY_HEADER(localTransform);
    SO_KIT_CATALOG_ENTRY_HEADER(contents);

  public:

    //! Constructor.
    SoWrapperKit();

  SoINTERNAL public:
    static void initClass();

  protected:
    virtual ~SoWrapperKit();
};

#endif  /* _SO_WRAPPER_KIT_ */
