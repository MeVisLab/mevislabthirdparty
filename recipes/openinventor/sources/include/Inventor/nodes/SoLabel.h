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
 |   $Revision $
 |
 |   Description:
 |      This file defines the SoLabel node class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_LABEL_
#define  _SO_LABEL_

#include <Inventor/fields/SoSFName.h>
#include <Inventor/nodes/SoSubNode.h>


////////////////////////////////////////////////////////////////////////////////
//! Node containing label text string.
/*!
\class SoLabel
\ingroup Nodes
This class defines a label node in the scene graph. This node has no effect
during traversal. It is used to store text labels in the scene graph,
typically for application-specific identification of subgraphs when
node naming is not appropriate.

\par File Format/Default
\par
\code
Label {
  label "<Undefined label>"
}
\endcode

\par See Also
\par
SbName, SoInfo
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoLabel : public SoNode {

    SO_NODE_HEADER(SoLabel);

  public:
    //! \name Fields
    //@{

    //! Defines the label string value as an SbName.
    SoSFName            label;          

    //@}

    //! Creates a label node with default settings.
    SoLabel();

  SoINTERNAL public:
    static void         initClass();

  protected:
    virtual ~SoLabel();

    //! NOTE: No actions for this node. It's pretty passive.
};

#endif /* _SO_LABEL_ */
