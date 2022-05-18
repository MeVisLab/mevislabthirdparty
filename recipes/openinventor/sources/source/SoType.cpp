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
 |   $Revision: 1.6 $
 |
 |   Classes:
 |  SoType
 |
 |   Author(s)    : Nick Thompson, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#include <Inventor/system/SbSystem.h>
#include <Inventor/SoType.h>
#include <Inventor/SoLists.h>
#include <Inventor/errors/SoDebugError.h>
#ifndef WIN32
#include <dlfcn.h>
#endif
#include <stdlib.h>
#ifdef __sgi
#include <sgidefs.h>
#endif // __sgi
#include <sys/types.h>
#ifndef WIN32
#include <unistd.h>
#endif

SoINTERNAL struct SoTypeData {
    SoType    type;
    SoType    parent;
    SbName    name;
    void    *(*createMethod)();
};

int       SoType::nextIndex;
int       SoType::arraySize;
SoTypeData *      SoType::typeData;

// Dictionary mapping SbNames to pointers into indices in the typeData
// array (pointers into the array would be bad, since the array can
// move around as it gets expanded, but indices are OK):
SbDict *      SoType::nameDict;

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Initialize the type system.  Called by SoDB::init.
//
// Use: public, static

void
SoType::init()
//
////////////////////////////////////////////////////////////////////////
{
    nameDict = new SbDict;

    // This will change when expandTypeData() is called below
    arraySize = 0;
    typeData = NULL;

    // Initialize bad type at index 0. Make room first.
    expandTypeData();
    typeData->type.storage.index = 0;
    typeData->type.storage.isPublic = 1;
    typeData->type.storage.data  = 0;

    // The first real type will have index 1
    nextIndex = 1;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns the "bad type" - used for type errors
//    
//
// Use: public, static

SoType
SoType::badType()
//
////////////////////////////////////////////////////////////////////////
{
    SoType t;

    t.storage.index = 0;
    t.storage.isPublic = 1;
    t.storage.data = 0;

    return t;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns TRUE if this type is derived from the argument type
//
// Use: public

bool
SoType::isDerivedFrom(SoType t) const
//
////////////////////////////////////////////////////////////////////////
{
    SoType thisType = *this;

    while (! thisType.isBad())
  if (thisType == t)
      return TRUE;
  else
      thisType = thisType.getParent();

    return FALSE;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Add all types derived from the given type to the given type
//    list.  Returns the number of types added.
//
// Use: public, static

int
SoType::getAllDerivedFrom(SoType type, SoTypeList &typeList)
//
////////////////////////////////////////////////////////////////////////
{
    int   numAdded, i;
    SoType  curType;

    // Gather all valid types into array (skip index 0 - badType)
    numAdded = 0;
    for (i = 1; i < nextIndex; i++) {
  curType = typeData[i].type;

  // See if the type corresponds to a non-abstract node class 
  if (! curType.isBad() && curType.isDerivedFrom(type) &&
      (curType.storage.isPublic == 1)) {
      typeList.append(curType);
      ++numAdded;
  }
    }

    return numAdded;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Given a name, returns the appropriate SoType.
//
// Use: public, static

SoType
SoType::fromName(SbName name)
//
////////////////////////////////////////////////////////////////////////
{
    void *b = NULL;
    const char *nameChars = name.getString();
    SbString nameString(nameChars);  // For easier manipulation...

    // Look for an existing type; if the type begins with "So", then
    // look at a type matching the stuff after the "So", also.  If not
    // found, we'll try the DSO thing:
    bool notFound = !nameDict->find(nameChars, b);
    if (notFound && (name.getLength() > 2)  &&
        (nameString.getSubString(0,1) == "So"))
    {

        notFound = !nameDict->find(SbName(nameChars+2).getString(), b);
    }
    if (b == NULL) {
      return SoType::badType();
    }
    SoType result = typeData[(int) ((size_t) b)].type;

    if (result.storage.isPublic == 0) {
#ifdef DEBUG
      SoDebugError::post("SoType::fromName", "%s is internal",
        nameChars);
#endif
      return SoType::badType();
    }

    return result;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Create a new type, given it parent (badType if it has none), its
//    name, and, optionally, a method to create it and some data
//    associated with it.
//
// Use: extender, static

SoType
SoType::createType(SoType parent, SbName name,
       void * (*createMethod)(),
       short data)
//
////////////////////////////////////////////////////////////////////////
{
    SoType  t;  
    SoTypeData  *td;

    if (nextIndex >= arraySize)
  expandTypeData();

    t.storage.index = nextIndex++;
    t.storage.isPublic = 1;
    t.storage.data  = data;

    td = typeData + t.storage.index;

    td->type    = t;
    td->parent    = parent;
    td->name    = name;
    td->createMethod  = createMethod;

    nameDict->enter(name.getString(), (void *)(size_t)t.storage.index);

    return t;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Make a new type act like an existing type.  "new" in this case
//    means a different subclass of an existing type-- for examply, a
//    user can create an MyCube subclass derived from SoCube.  By
//    registering it with the type system using this method, whenever
//    the database uses SoType::fromName and then
//    SoType::createInstance, an instance of MyCube will be created
//    instead of an SoCube.  Since the pointer returned from
//    createInstance may be cast to an SoCube, the instance created
//    must be a subclass of SoCube.
//
// Use: extender, static

SoType
SoType::overrideType(SoType oldType, void * (*createMethod)())
//
////////////////////////////////////////////////////////////////////////
{
#ifdef DEBUG
    if (oldType.isBad() || ! oldType.canCreateInstance())
  SoDebugError::post("SoType::overrideType",
         "Type to override (%s) is bad: %s",
         oldType.getName().getString());
#endif

    SoTypeData *td = typeData + oldType.storage.index;

    td->createMethod  = createMethod;

    return oldType;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Mark this type as internal.  This MUST be done just after the
//    type is first created.
//
// Use: private, static

void
SoType::makeInternal()
//
////////////////////////////////////////////////////////////////////////
{
    // This is gross, but necessary.  After creation, copies of the
    // type exist in two places:  the classes' classTypeId member, and
    // in the typeData array.  So, we need to change them both:
    storage.isPublic = 0;
    typeData[storage.index].type.storage.isPublic = 0;
}

#define INITIAL_ARRAY_SIZE  64

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Make the table of type data bigger.
//
// Use: private, static

void
SoType::expandTypeData()
//
////////////////////////////////////////////////////////////////////////
{
    if (typeData == NULL) {
  arraySize = INITIAL_ARRAY_SIZE;
  typeData = new SoTypeData[arraySize];
    }
    else {
  SoTypeData *newTypeData = new SoTypeData[2 * arraySize];
  memcpy((void *) newTypeData, (void *) typeData,
        arraySize * sizeof(SoTypeData));
  delete[] typeData;
  typeData = newTypeData;
  arraySize *= 2;
    }
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Return the name of a given type.
//
// Use: public

SbName
SoType::getName() const
//
////////////////////////////////////////////////////////////////////////
{
    return typeData[storage.index].name;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Return the parent of a given type.
//
// Use: public

SoType
SoType::getParent() const
//
////////////////////////////////////////////////////////////////////////
{
    return typeData[storage.index].parent;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Test if we know how to create an instance
//
// Use: public

bool
SoType::canCreateInstance() const
//
////////////////////////////////////////////////////////////////////////
{
    SoTypeData  *data = &typeData[storage.index];

    return (data->createMethod != NULL);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Use the creation method to create an object of the appropriate
//    type.
//
// Use: public

void *
SoType::createInstance() const
//
////////////////////////////////////////////////////////////////////////
{
    SoTypeData  *data = &typeData[storage.index];

    if (data->createMethod != NULL)
   return (*data->createMethod)();

    return NULL;
}
