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
 |      Defines the SoSeparatorKit class. 
 |      Organizes an appearance, a transform, a local transform and a 
 |      group of child kits
 |
 |   Author(s)          : Paul Isaacs, Thad Beier
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
*/

#ifndef  _SO_SEPARATOR_KIT_
#define  _SO_SEPARATOR_KIT_

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/sensors/SoFieldSensor.h>


////////////////////////////////////////////////////////////////////////////////
//! Separator nodekit class.
/*!
\class SoSeparatorKit
\ingroup Nodekits
A nodekit that is used for creating nodekit hierarchies.
SoSeparatorKit contains a <em>transform</em> part, a <em>childList</em> part,
and a few others in its catalog.
The <em>transform</em> part (an SoTransform node) affects all of the
children in the <tt>childList</tt>. Each of these children must be an
SoSeparatorKit or from a class that is derived from SoSeparatorKit
(e.g., SoShapeKit and SoWrapperKit).
Since all members of the <em>childList</em> are in turn SoSeparatorKits,
and each contains a <em>transform</em>, these nested lists allow you to create
a hierarchy of motion, in which each <em>transform</em> affects an entire subgraph
of nodekits.


The other parts added to the catalog for the SoSeparatorKit are
<em>pickStyle</em>, <em>appearance</em>, <em>units</em> and <em>texture2Transform</em>.  
Furthermore,
since SoSeparator is derived from SoBaseKit, it inherits
the <em>callbackList</em> part. This is a list of SoCallback and/or
SoEventCallback nodes which enable the SoSeparatorKit to perform
special callbacks whenever an action is applied to it. 


By creating the <em>pickStyle</em> part, a user can alter the pick style
for the entire nodekit hierarchy. The <em>appearance</em> part is an
SoAppearanceKit nodekit. Note that all parts contained in the
SoAppearanceKit catalog can be accessed 
as if they were part of the SoSeparatorKit. For example:
\code
myMtl = mySepKit->getPart("material",TRUE)
\endcode
and 
\code
mySepKit->setPart("material",myMtl)
\endcode
See SoBaseKit for further explanation.

\par Parts
\par
\b pickStyle
<BR> An SoPickStyle property node that can be used to set the     picking style of its children. This part is <tt>NULL</tt> by default, 	but is created automatically if necessary. 
\par
\b appearance
<BR> An SoAppearanceKit nodekit which can be used 	to set the appearance properties of its children. 	This part is <tt>NULL</tt> by default, but is created automatically 	if necessary. 
\par
\b units
<BR> An SoUnits node which can be used 	to set the types of units, (e.g., feet), of its children. 	This part is <tt>NULL</tt> by default, but is created automatically 	if necessary. 
\par
\b transform
<BR> An SoTransform node which can be used 	to set the overall position, orientation, and scale 	of its children. This part is <tt>NULL</tt> by default, 	but is created automatically if necessary. 
\par
\b texture2Transform
<BR> An SoTexture2Transform node which can be used 	to apply a transformation to any textures used by its children. 	This part is <tt>NULL</tt> by default, but is created automatically 	if necessary. 
\par
\b childList
<BR> This part contains the children nodekits of this 	SoSeparatorKit.  This part is a <em>list part</em> and can 	have multiple children. This part is <tt>NULL</tt> by default, 	but is created automatically when the first child is added  	to the <em>childList</em>.  	Also, when asked to build a member of the <em>childList</em>,  	the separatorKit 	will build an SoShapeKit by default. 	So if the <em>childList</em> part is NULL, and you call: 	getPart("childList[0]", TRUE), 	the separator kit will create the <em>childList</em> and add  	an SoShapeKit as the new element in the list. 	

\par See Also
\par
SoAppearanceKit, SoBaseKit, SoCameraKit, SoLightKit, SoNodeKit, SoNodeKitDetail, SoNodeKitListPart, SoNodeKitPath, SoNodekitCatalog, SoSceneKit, SoShapeKit, SoWrapperKit
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoSeparatorKit : public SoBaseKit {

    SO_KIT_HEADER(SoSeparatorKit);

    //! defines fields for the new parts in the catalog
    SO_KIT_CATALOG_ENTRY_HEADER(topSeparator);
    SO_KIT_CATALOG_ENTRY_HEADER(pickStyle);
    SO_KIT_CATALOG_ENTRY_HEADER(appearance);
    SO_KIT_CATALOG_ENTRY_HEADER(units);
    SO_KIT_CATALOG_ENTRY_HEADER(transform);
    SO_KIT_CATALOG_ENTRY_HEADER(texture2Transform);
    SO_KIT_CATALOG_ENTRY_HEADER(childList);

  public:

    //! Possible values for caching
    enum CacheEnabled {
        OFF,                    //!< Never build or use a cache
        ON,                     //!< Always try to build a cache
        AUTO                    //!< Decide based on some heuristic
    };

    //! \name Fields
    //@{

    //! Set render caching mode.  Default is <tt>AUTO</tt>.
    SoSFEnum renderCaching;     

    //! Set bounding box caching mode.
    //! 	Default is <tt>ON</tt>.  Setting this value to <tt>AUTO</tt> is equivalent
    //! 	to <tt>ON</tt> (automatic culling is not implemented.)
    SoSFEnum boundingBoxCaching;

    //! Set render culling mode.  Default is <tt>OFF</tt>.
    //! 	Setting this value to <tt>AUTO</tt> is equivalent to <tt>ON</tt>
    //!     (automatic culling is not implemented.)
    SoSFEnum renderCulling;     

    //! Set pick culling mode.  Default is <tt>AUTO</tt>.
    SoSFEnum pickCulling;       

    //@}

    //! Constructor.
    SoSeparatorKit();

    //! Overrides default method on SoNode
    virtual bool affectsState() const;

  SoINTERNAL public:
    static void initClass();

  protected:

    //! detach/attach any sensors, callbacks, and/or field connections.
    //! Called by:            start/end of SoBaseKit::readInstance
    //! and on new copy by:   start/end of SoBaseKit::copy.
    //! Classes that redefine must call setUpConnections(TRUE,TRUE) 
    //! at end of constructor.
    //! Returns the state of the node when this was called.
    virtual bool setUpConnections( bool onOff, bool doItAlways = FALSE );

    //! Called by the SoBaseKit::write() method. Calls setDefault(TRUE)
    //! on the topSeparator. Note that this may be overriden later by basekit
    //! if, for example, topSeparator lies on a path that is being written out.
    virtual void setDefaultOnNonWritingFields();

    //! This sensor will watch the topSeparator part.  If the part changes to a 
    //! new node,  then the fields of the old part will be disconnected and
    //! the fields of the new part will be connected.
    //! Connections are made from/to the renderCaching, boundingBoxCaching,
    //! renderCulling and pickCulling fields. This way, the SoSeparatorKit
    //! can be treated from the outside just like a regular SoSeparator node.
    //! Setting the fields will affect caching and culling, even though the
    //! topSeparator takes care of it.
    //! oldTopSep keeps track of the part for comparison.
    SoFieldSensor *fieldSensor;
    static void fieldSensorCB( void *, SoSensor *);
    SoSeparator *oldTopSep;

    void connectSeparatorFields( SoSeparator *dest, bool onOff );

  protected:
    virtual ~SoSeparatorKit();

};
#endif  /* _SO_SEPARATOR_KIT_ */
