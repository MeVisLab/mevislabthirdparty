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
 |      SoSFPath
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SF_PATH_
#define  _SO_SF_PATH_

class SoPath;

#include <Inventor/fields/SoSubField.h>


////////////////////////////////////////////////////////////////////////////////
//! Field containing a pointer to an SoPath.
/*!
\class SoSFPath
\ingroup Fields
This field maintains a pointer to an SoPath instance,
correctly maintaining its reference count.


SoSFPaths are written to file as the path they point to.  See the
SoPath manual page for a description of the file format for a
path.

\par See Also
\par
SoField, SoSField, SoMFPath, SoPath
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoSFPath : public SoSField {

    //! Use standard field stuff
    SO_SFIELD_HEADER(SoSFPath, SoPath *, SoPath *);

  SoINTERNAL public:
    static void         initClass();

    //! Propagates notification through field
    virtual void        notify(SoNotList *list);

    //! Update a copied field to use node copies if the head node has
    //! been copied
    virtual void        fixCopy(SbBool copyConnections);

    //! Override this to also check the head of the stored path
    virtual bool        referencesCopy() const;

  private:
    SoNode              *head;          //!< Head node of path (needed
                                        //! to track notification)

    //! Override this to maintain write-references in path
    virtual void        countWriteRefs(SoOutput *out) const;

    //! Changes value in field without doing other notification stuff.
    //! Keeps track of references and auditors.
    void                setVal(SoPath *newValue);
};

#endif /* _SO_SF_PATH_ */
