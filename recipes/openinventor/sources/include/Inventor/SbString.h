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
 |      This file contains definitions of the SbString and SbName
 |      classes, which are useful variations on our friend, the
 |      character string.
 |
 |   Author(s)          : Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SB_STRING_
#define _SB_STRING_

#include <Inventor/system/SbSystem.h>
#include <Inventor/SbBasic.h>

#include <string.h>

#ifdef WIN32
#define oiv_strdup _strdup
#else
#define oiv_strdup strdup
#endif

////////////////////////////////////////////////////////////////////////////////
//! Class for smart character strings.
/*!
\class SbString
\ingroup Basics
Strings which have many convenience methods to make
string manipulation easier.

\par See Also
\par
SbName
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbString {
  public:

    //! \see SbString(int digitString)
    SbString()                          { string = staticStorage; 
                                          string[0] = '\0'; }

    //! \see SbString(int digitString)
    SbString(const char *str)           { string = staticStorage;
                                          *this = str; }

    //! \see SbString(int digitString)
    SbString(const char *str, int start, int end);

    //! \see SbString(int digitString)
    SbString(const SbString &str)       { string = staticStorage;
                                          *this = str.string; }

    //! Constructors and destructor. Constructors take a character string, the
    //! subset of a character string from start to end (inclusive), or an
    //! integer to be turned into a string.
    //! For example,
    //! <tt>SbString(1234)</tt>
    //! creates the string "1234".
    //! <tt>SbString("Testing",1,3)</tt>
    //! creates the string "est".
    SbString(int digitString);

    //! Destructor.
    ~SbString();

    //! Returns a reasonable hash key for string
    uint32_t            hash()          { return SbString::hash(string); }

    //! Returns length of string.
    int                 getLength() const       { return static_cast<int>(strlen(string)); }

    //! Sets string to be the empty string (""). If freeOld is TRUE
    //! (default), any old storage is freed up.
    void                makeEmpty(bool freeOld = TRUE);

    //! Returns pointer to the character string.
    const char *        getString() const       { return string; }

    //! Returns new string representing sub-string from \p startChar to
    //! \p endChar, inclusive. If \p endChar is -1 (the default), the
    //! sub-string from \p startChar until the end is returned.
    SbString            getSubString(int startChar, int endChar = -1) const;

    //! Deletes the characters from \p startChar to \p endChar, inclusive,
    //! from the string. If \p endChar is -1 (the default), all characters
    //! from \p startChar until the end are deleted.
    void                deleteSubString(int startChar, int endChar = -1);

    //! Assignment operators for character string, SbString.
    SbString &          operator =(const char *str);
    //! Assignment operators for character string, SbString.
    SbString &          operator =(const SbString &str)
        { return (*this = str.string); }

    //! Concatenation operators "+=" for string, SbString.
    SbString &          operator +=(const char *str);

    //! Concatenation operators "+=" for string, SbString.
    SbString &          operator +=(const SbString &str);

    //! Unary "not" operator; returns TRUE if string is empty ("").
    bool                   operator !() const { return (string[0] == '\0'); }

    //! Equality operator for SbString/char* and SbString/SbString comparison
    friend INVENTOR_API bool               operator ==(const SbString &str, const char *s);

    friend INVENTOR_API bool               operator ==(const char *s, const SbString &str)
        { return (str == s); }


    friend INVENTOR_API bool               operator ==(const SbString &str1, const SbString &str2)
        { return (str1 == str2.string); }

    //! Inequality operator for SbString/char* and SbString/SbString comparison
    friend INVENTOR_API bool               operator !=(const SbString &str, const char *s);

    friend INVENTOR_API bool               operator !=(const char *s, const SbString &str)
        { return (str != s); }

    friend INVENTOR_API bool               operator !=(const SbString &str1,
                                    const SbString &str2)
        { return (str1 != str2.string); }

    //! Lexically less than operator for SbString/char* and SbString/SbString comparison
    friend INVENTOR_API bool               operator <(const SbString &str, const char *s);

    friend INVENTOR_API bool               operator <(const char *s, const SbString &str)
        { return (str < s); }
    
    friend INVENTOR_API bool               operator <(const SbString &str1, const SbString &str2)
        { return (str1 < str2.string); }

  SoINTERNAL public:

    //! Returns a reasonable hash key for string.
    static uint32_t     hash(const char *s);    // Hash function

  private:
    char                *string;                //!< String pointer
    int                 storageSize;

    //! This is used if the string fits in a reasonably small space
#define SB_STRING_STATIC_STORAGE_SIZE           32
    char                staticStorage[SB_STRING_STATIC_STORAGE_SIZE];

    void                expand(int bySize);     //!< Makes more room
};

///////////////////////////////////////////////////////////////////////////////
///
////  \class SbNameEntry
///
///  This is used to make lists of SbName instances.
///
//////////////////////////////////////////////////////////////////////////////


SoINTERNAL class INVENTOR_API SbNameEntry {

  public:
    //! Returns TRUE if entry's string is empty ("")
    bool                isEmpty() const   { return (string[0] == '\0'); }

    //! Returns TRUE if entry's string is same as passed string
    bool                isEqual(const char *s) const
        { return (string[0] == s[0] && ! strcmp(string, s)); }

  private:
    static int          nameTableSize;  //!< Number of buckets in name table
    static SbNameEntry  **nameTable;    //!< Array of name entries
    static struct SbNameChunk *chunk;   //!< Chunk of memory for string storage

    const char          *string;        //!< String for this entry
    uint32_t            hashValue;      //!< Its hash value
    SbNameEntry         *next;          //!< Pointer to next entry

    //! Initializes SbNameEntry class - done only once
    static void         initClass();

    //! Constructor
    SbNameEntry(const char *s, uint32_t h, SbNameEntry *n)
        { string = s; hashValue = h; next = n; }

    //! Inserts string in table
    static const SbNameEntry *  insert(const char *s);

friend INVENTOR_API class SbName;
};



////////////////////////////////////////////////////////////////////////////////
//! Character string stored in a hash table.
/*!
\class SbName
\ingroup Basics
This class of strings stores the string in a hash table. It is
used by the Inventor toolkit for keywords and other unique names.
It is not recommended for general use (only in the context of Inventor
objects). When a string is stored in this table, a pointer to the
storage is returned. Two identical strings will return the same pointer.
This means that comparison of two SbNames
for equality can be accomplished by comparing their identifiers.
SbNames
are used for strings which are expected to show up frequently, such as
node names.

\par See Also
\par
SbString
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbName {
  public:

    //! Constructors and destructor.
    SbName();

    //! Constructor that initializes to given character string
    SbName(const char *s)               { entry = SbNameEntry::insert(s); }

    //! Constructor that initializes to given SbString
    SbName(const SbString &s)   { entry = SbNameEntry::insert(s.getString()); }

    //! Constructors and destructor.
    SbName(const SbName &n)                     { entry = n.entry; }

    //! Constructors and destructor.
    ~SbName()                                   {}

    //! Returns pointer to the character string.
    const char          *getString() const      { return entry->string; }

    //! Returns length of string.
    int                 getLength() const   { return static_cast<int>(strlen(entry->string)); }

    //! Returns TRUE if given character is a legal starting character
    //! for an identifier.
    static bool         isIdentStartChar(char c);

    //! Returns TRUE if given character is a legal nonstarting
    //! character for an identifier.
    static bool         isIdentChar(char c);

    //! Returns TRUE if given character is a legal starting character
    //! for an SoBase's name
    static bool         isBaseNameStartChar(char c);

    //! Returns TRUE if given character is a legal nonstarting
    //! character for an SoBase's name
    static bool         isBaseNameChar(char c);

    //! Unary "not" operator; returns TRUE if string is empty ("").
    bool                operator !() const   { return entry->isEmpty(); }

    //! Equality operator for SbName/char* and SbName/SbName comparison
    friend INVENTOR_API bool               operator ==(const SbName &n, const char *s)
        { return n.entry->isEqual(s); }

    friend INVENTOR_API bool               operator ==(const char *s, const SbName &n)
        { return n.entry->isEqual(s); }

    friend INVENTOR_API bool               operator ==(const SbName &n1, const SbName &n2)
        { return n1.entry == n2.entry; }

    //! Inequality operator for SbName/char* and SbName/SbName comparison
    friend INVENTOR_API bool               operator !=(const SbName &n, const char *s)
        { return ! n.entry->isEqual(s); }

    friend INVENTOR_API bool               operator !=(const char *s, const SbName &n)
        { return ! n.entry->isEqual(s); }

    friend INVENTOR_API bool               operator !=(const SbName &n1, const SbName &n2)
        { return n1.entry != n2.entry; }

  private:
    const SbNameEntry   *entry;         //!< Name string storage
};

#endif /* _SB_STRING_ */
