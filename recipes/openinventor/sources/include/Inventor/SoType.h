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
 |      Defines the SoType class.  The SoType class is used for
 |       run-time typing.  It is designed to be very small (it
 |       contains only two shorts) and to support comparison of types,
 |       single inheritence type hierarchies, and creation of a type
 |       from a name and create of a C++ instance from an SoType.
 |       No two types can share the same name, even if they are
 |       derived from different parents.
 |       SoTypes may also store an extra short with the type;
 |       this is used by nodes and actions to keep track of their
 |       place in the dispatch table.
 |
 |   Author(s)          : Nick Thompson, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TYPE_
#define  _SO_TYPE_

#include <Inventor/system/SbSystem.h>
#include <Inventor/misc/SoBasic.h>
#include <Inventor/SbString.h>
#include <Inventor/SbDict.h>

class SoTypeList;
struct SoTypeData;

//!
//! SoType has no virtual functions to keep it small...
//!
////////////////////////////////////////////////////////////////////////////////
//! Stores runtime type information.
/*!
\class SoType
\ingroup General
The SoType class keeps track of runtime type information in
Inventor. Each type is associated with a given name, so lookup is
possible in either direction.


Many Inventor classes request a unique SoType when they
are initialized.  This type can then be used to find out the actual
class of an instance when only its base class is known, or to obtain
an instance of a particular class given its type or name.


Note that the names associated with types of Inventor classes do not
contain the "So" prefix.

\par See Also
\par
SoAction, SoBase, SoDetail, SoError, SoEvent, SoField
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoType {
  public:

    //! Returns the type associated with the given name.
    static SoType       fromName(SbName name);

    //! Returns the name associated with a type.
    SbName              getName() const;

    //! Returns the type of the parent class.
    SoType              getParent() const;

    //! Returns an always-illegal type. Useful for returning errors.
    static SoType       badType();

    //! Returns TRUE if the type is a bad type.
    bool                isBad() const
        { return (storage.index == 0); }

    //! Returns TRUE if the type is derived from type \p t.
    bool                isDerivedFrom(SoType t) const;

    //! Adds all types derived from the given type to the given type list.
    //! Returns the number of types added.
    static int          getAllDerivedFrom(SoType type,
                                          SoTypeList &list);

    //! Some types are able to create instances; for example, most nodes and
    //! engines (those which are not abstract classes) can be created this
    //! way. This method returns TRUE if the type supports such creation.
    bool                canCreateInstance() const;

    //! Creates and returns a pointer to an instance of the type. Returns NULL
    //! if an instance could not be created for some reason. The pointer is
    //! returned as a generic pointer, but can be cast to the appropriate
    //! type. For example:
    //! \code
    //! SoCube *c = (SoCube *) SoCube::getClassTypeId().createInstance();
    //! \endcode
    //! is a convoluted way of creating a new instance of an SoCube.
    void *              createInstance() const;

    //! Returns TRUE if this type is the same as or not the same as the given type.
    bool                   operator ==(const SoType t) const
        { return (storage.index == t.storage.index);}
    //! Returns TRUE if this type is the same as or not the same as the given type.
    bool                   operator !=(const SoType t) const
        { return (storage.index != t.storage.index);}

    //! Less-than comparison operator that can be used to sort types. This is
    //! pretty useless otherwise.
    bool                   operator <(const SoType t) const
        { return (storage.index < t.storage.index); }

  SoEXTENDER public:

    //! Create a new type
    static SoType       createType(SoType parent, SbName name,
                                   void * (*createMethod)() = NULL,
                                   short data = 0);

    //! Make an new type act like an existing type.  The new type MUST
    //! be a C++ subclass of the original (e.g. MyCubeClass must be
    //! derived from SoCube), but there is no way for us to check that.
    //! This can be used to get the database to create a different
    //! subclass whenever it reads in a SoNode class from a file.
    static SoType       overrideType(SoType existingType,
                                     void * (*createMethod)() = NULL);

  SoINTERNAL public:
    //! Initialize the type system
    static void         init();

    //! Get data
    short               getData() const         { return storage.data; }

    //! Returns the type key as a short
    short               getKey() const          { return storage.index; }

    //! Mark this type as internal; if internal, getAllDerivedFrom and
    //! fromName will not return the type.
    void                makeInternal();

    //! Get the number of types currently registed in the types dictionary.
    //! This is used by SoAction when setting up the action method list.
    static int          getNumTypes()           { return nextIndex; }

  private:
    //! SoTypes are passed around on the stack a lot, and are cast to
    //! void *'s; they MUST fit into a single word.
    struct {
        unsigned int    data : 16;
        unsigned int    index : 15;  //!< Assumes we have fewer than
                                     //! 32,768 types
        unsigned int    isPublic :1; //!< 0 if is an internal class
    } storage;

    //! name->sotype dictionary
    static SbDict       *nameDict;

    //! array of SoTypeData
    static int          nextIndex;
    static int          arraySize;
    static SoTypeData   *typeData;

    static void         expandTypeData();
};

#endif /* _SO_TYPE_ */
