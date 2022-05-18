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
 |      This file defines dictionaries. A dictionary maps some sort of
 |      unique key to a data pointer. Keys are size_t integers.
 |
 |   Classes:
 |      SbDictEntry, SbDict
 |
 |   Author(s)          : Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */


#ifndef _SB_DICT_
#define _SB_DICT_

#include <Inventor/system/SbSystem.h>

#include <Inventor/SbBasic.h>
#include <Inventor/SbString.h>
#include <Inventor/SbPList.h>

///////////////////////////////////////////////////////////////////////////////
///
////  \class SbDictEntry
///
///  A dictionary is stored as a collection of entries, each of which
///  is an SbDictEntry. It contains the key and value for the entry and
///  a link to create lists of entries.
///
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class SbDictEntry {
  private:
    size_t              key;
    void *              value;

    SbDictEntry *       next;

    //! Constructor
    SbDictEntry(size_t k, void *v)       { key = k; value = v; };

friend class SbDict;
};

///////////////////////////////////////////////////////////////////////////////
///
////  \class SbDict
///
///  This is a dictionary mapping (size_t) integer keys to (void *) data
///  pointers.
///
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SbDict {
  public:

    //! Constructor
    SbDict( int entries = 251 );

    //! Destructor
    ~SbDict();

    //! Calls given routine (passing value) for each entry in dictionary.
    //!  The order of entries is not guaranteed to mean anything.
    void        applyToAll(void (*rtn)(size_t key, void *value) );

    //! Calls given routine (passing value,data) for each entry in dictionary.
    //!  The order of entries is not guaranteed to mean anything.
    void        applyToAll(void (*rtn)(size_t key, void *value, void *data), 
                           void *data );

    //! Removes all entries from dictionary.
    void        clear();

    //! Enters a key,value pair into the dictionary. Overwrites entry and
    //!  returns FALSE if key already exists.
    bool        enter(size_t key, void *value);
    //! Convenience variant with pointer type as key:
    bool        enter(const void* key, void* value) { return enter((size_t)key, value); }

    //! Finds entry with given key, setting value to point to value.
    //!  Returns FALSE if no such entry.
    bool        find(size_t key, void *&value) const;
    //! Convenience variant with pointer type as key:
    bool        find(const void* key, void* &value) const { return find((size_t)key, value); }

    //! Makes two SbPLists, one for keys and the other for values.
    //!  The order of entries is not guaranteed to mean anything.
    void        makePList(SbPList &keys, SbPList &values);

    //! Removes the entry with the given key. Returns FALSE if no such entry.
    bool        remove(size_t key);
    //! Convenience variant with pointer type as key:
    bool        remove(const void* key) { return remove((size_t)key); }

  private:
    //! Entries are stored as an external hash table of SbDictEntry instances.
    int                 tableSize;                      //!< Entries in table
    SbDictEntry *       *buckets;                       //!< Hash table

    SbDictEntry *&      findEntry(size_t key) const;
    static void         addEntryToPLists(size_t key, void *value, void *data);
};

#endif /* _SB_DICT_ */
