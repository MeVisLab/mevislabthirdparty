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
 |      SoMFEngine
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_MF_ENGINE_
#define  _SO_MF_ENGINE_

class SoEngine;

#include <Inventor/fields/SoSubField.h>


////////////////////////////////////////////////////////////////////////////////
//! Multiple-value field containing any number of pointers to engines.
/*!
\class SoMFEngine
\ingroup Fields
This field maintains a set of pointers to SoEngine instances,
correctly maintaining their reference counts.


SoMFEngines are written to file as one or more engines.
When more than one value is present, all of the
values are enclosed in square brackets and separated by commas; for
example:
\code
[ ElapsedTime { }, OneShot { duration 2.0 }, USE myCalculator ]
\endcode

*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoMFEngine : public SoMField {

    //! Use standard field stuff
    SO_MFIELD_HEADER(SoMFEngine, SoEngine *, SoEngine *);

  SoINTERNAL public:
    static void         initClass();

    //! Update a copied field to use the copy of each engine if there is one
    virtual void        fixCopy(bool copyConnections);

    //! Override this to also check the stored engines
    virtual bool        referencesCopy() const;

  private:
    //! Override this to maintain write-references in engines
    virtual void        countWriteRefs(SoOutput *out) const;

    //! Changes value in field without doing other notification stuff.
    //! Keeps track of references and auditors.
    void                setVal(int index, SoEngine *newValue);
};

#endif /* _SO_MF_ENGINE_ */
