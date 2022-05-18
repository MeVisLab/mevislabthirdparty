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
 |      SoSFNode
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SF_NODE_
#define  _SO_SF_NODE_

class SoNode;

#include <Inventor/fields/SoSubField.h>


////////////////////////////////////////////////////////////////////////////////
//! Field containing a pointer to a node.
/*!
\class SoSFNode
\ingroup Fields
This field maintains a pointer to an SoNode instance,
correctly maintaining its reference count.


SoSFNodes are written to file as the node they are pointing to.
For example:
\code
mySoSFNodeField Cube {}
\endcode
is an SoSFNode field named 'mySoSFNodeField', pointing to an SoCube
node.  If the node is used elsewhere, the regular DEF/USE instancing
mechanism applies:
\code
anotherSoSFNodeField USE topSeparator
\endcode
is an SoSFNode field that points to a node named 'topSeparator' that
was DEF'ed earlier in the scene.

\par See Also
\par
SoField, SoSField, SoMFNode, SoNode
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoSFNode : public SoSField {

    //! Use standard field stuff
    SO_SFIELD_HEADER(SoSFNode, SoNode *, SoNode *);

  SoINTERNAL public:
    static void         initClass();

    //! Update a copied field to use the copy of the node if there is one
    virtual void        fixCopy(bool copyConnections);

    //! Override this to also check the stored node
    virtual bool        referencesCopy() const;

  private:
    //! Override this to maintain write-references in node
    virtual void        countWriteRefs(SoOutput *out) const;

    //! Changes value in field without doing other notification stuff.
    //! Keeps track of references and auditors.
    void                setVal(SoNode *newValue);
};

#endif /* _SO_SF_NODE_ */
