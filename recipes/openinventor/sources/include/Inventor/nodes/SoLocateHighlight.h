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
 * Copyright (C) 1995-96   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.1.1.1 $
 |
 |   Description:
 |      This file defines the SoLocateHighlight node class.
 |
 |   It has two fields, 
 |      color and style
 |
 |   When the cursor is over the stuff below this node,
 |   it will be redrawn (to the front buffer) with the color 
 |   emissive and/or diffuse in the state and the override flag ON.
 |
 |   Author(s)  : Alain Dumesny, Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_LOCATE_HIGHLIGHT_
#define  _SO_LOCATE_HIGHLIGHT_

#include <Inventor/system/SbSystem.h>
#include <Inventor/system/SbOpenGL.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoSeparator.h>

class SoAction;
class SoHandleEventAction;
class SoGLRenderAction;
class SoFullPath;
class SoColorPacker;



////////////////////////////////////////////////////////////////////////////////
//! Special separator that performs locate highlighting.
/*!
\class SoLocateHighlight
\ingroup Nodes
This is a subclass of SoSeparator that redraws itself in a different color
when the cursor is over the contents of the separator. 


The redraw happens for that separator only and not the entire window (redraw along 
the handle event pick path) and in the front buffer, to efficiently
track the mouse motion. The highlighted redraw overrides the emissive and/or diffuse
color of the subgraph based on the field values in this node.


NOTE: when using <tt>SoLightModel::BASE_COLOR</tt> (to turn lighting off) only the diffuse color
will be used to render objects, so <tt>EMISSIVE_DIFFUSE</tt> must be used for
this node to have any effect.

\par File Format/Default
\par
\code
LocateHighlight {
  renderCaching AUTO
  boundingBoxCaching AUTO
  renderCulling AUTO
  pickCulling AUTO
  mode AUTO
  style EMISSIVE
  color 0.300000011920929 0.300000011920929 0.300000011920929
}
\endcode

\par Action Behavior
\par
SoHandleEventAction
<BR> Checks to see if the cursor moves onto or off of the contents of the separator, and redraws appropriately (if \b mode  is <tt>AUTO</tt>), otherwise traverses  as a normal separator. 
\par
SoGLRenderAction
<BR> Redraws either highlighted (if cursor is over the contents of the separator when \b mode  == <tt>AUTO</tt> or always if \b mode  == <tt>ON</tt>), otherwise traverses  as a normal separator. 

\par See Also
\par
SoSeparator, SoSelection, SoMaterial
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoLocateHighlight : public SoSeparator {

    SO_NODE_HEADER(SoLocateHighlight);

  public:

    //! Possible values for draw style
    enum Styles {
        EMISSIVE,           //!< changes emissive color only (default)
        EMISSIVE_DIFFUSE    //!< changes emissive and diffuse colors
    };

    //! Possible values for the mode
    enum Modes {
        AUTO,               //!< highlight when mouse is over (default)
        ON,                 //!< always highlight
        OFF                 //!< never highlight
    };

    //! \name Fields
    //@{

    //! Highlighting color - default [.3, .3, .3]
    SoSFColor   color;  

    //! Highlighting draw style - default EMISSIVE
    SoSFEnum    style;  

    //! Whether to highlight or not - default AUTO
    SoSFEnum    mode;   

    //@}

    //! Creates a LocateHighlight node with default settings.
    SoLocateHighlight();

  SoEXTENDER public:
    //! Override handleEvent to look for mouse motion, to do a
    //! pick and highlight if mouse is over us. The GLRender methods
    //! are redefined to draw highlighted if needed.
    virtual void        handleEvent( SoHandleEventAction *action );
    virtual void        GLRenderBelowPath(SoGLRenderAction *action);
    virtual void        GLRenderInPath(SoGLRenderAction *action);

  SoINTERNAL public:
    static void         initClass();    //!< initialize the class

    //! This will de-highlight the currently highlighted node if any.
    //! this should be called when the cursor leaves a window or a mode
    //! changes happen which would prevent a highlighted node from receiving
    //! more mouse motion events. The GL render action used to render into
    //! that window needs to be passed to correctly un-highlight.
    static void         turnOffCurrentHighlight(SoGLRenderAction *action);

  protected:
    virtual ~SoLocateHighlight();
    
    //! This is called when this nodes needs to highlight or de-highlight. It
    //! can be used by subclasses to be told when the status change.
    virtual void        redrawHighlighted(SoAction *act, bool flag);
    
  private:
    //! highlighting stuff
    bool                highlightingPass;
    static SoFullPath   *currentHighlightPath;
    bool                isHighlighted(SoAction *action);
    bool                preRender(SoGLRenderAction *act, GLint &oldDepthFunc);
    SoColorPacker       *colorPacker;
};


#endif /* _SO_LOCATE_HIGHLIGHT_ */
