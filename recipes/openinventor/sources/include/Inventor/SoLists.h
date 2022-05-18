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
 |      This file contains the definitions of subclasses of SbPList for
 |      some of the specific Inventor pointer types so that lists of
 |      pointers can be created easily.
 |
 |   Classes:
 |      subclasses of SbPList:
 |              SoBaseList
 |              SoNodeList
 |              SoPathList
 |              SoEngineList
 |              SoTypeList
 |              SoDetailList
 |              SoPickedPointList
 |              SoFieldList
 |              SoEngineOutputList
 |
 |   Author(s)          : Paul S. Strauss, Nick Thompson, David Mott,
 |                        Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_LISTS_
#define  _SO_LISTS_

#include <Inventor/system/SbSystem.h>
#include <Inventor/SbPList.h>
#include <Inventor/SoType.h>

class SoBase;
class SoDetail;
class SoEngine;
class SoEngineOutput;
class SoField;
class SoNode;
class SoPath;
class SoPickedPoint;

///////////////////////////////////////////////////////////////////////////////
///
/// Subclasses of the SbPList class which hold lists of pointers of a
/// specific type.
///
/// Each contains:
///      A default constructor
///      A constructor taking an initial number of items in the list
///      An "append" function that adds a pointer to the end of the list
///      The index ([]) operator that returns the nth pointer in the list
///
//////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//! Maintains a list of pointers to instances of the SoBase classes.
/*!
\class SoBaseList
\ingroup General
This subclass of SbPList holds lists of pointers to
instances of classes derived from SoBase (an abstract class). A
flag indicates whether adding an instance pointer to the list should
add a reference to the instance. If this flag is TRUE, then adding and
removing pointers from the list updates reference counts in the
corresponding instances.

\par See Also
\par
SoBase, SoNodeList, SoPathList
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoBaseList : public SbPList {
  public:
    //! Constructor.
    SoBaseList();
    //! Constructor that pre-allocates storage for \p size pointers.
    SoBaseList(int size);
    //! Constructor that copies the contents of another list.
    SoBaseList(const SoBaseList &l);
    //! Destructor.
    ~SoBaseList()                       { truncate(0); }

    //! Adds a pointer to the end of the list.
    void                append(SoBase * ptr);

    //! Inserts given pointer in list before pointer with given index.
    void                insert(SoBase *ptr, int addBefore);

    //! Removes pointer with given index.
    void                remove(int which);

    //! Removes all pointers after one with given index, inclusive.
    void                truncate(int start);

    //! Copies a list, keeping all reference counts correct.
    void                copy(const SoBaseList &l);
    //! Copies a list, keeping all reference counts correct.
    SoBaseList &        operator =(const SoBaseList &l)
        { copy(l) ; return *this; }

    //! Access an element of a list
    SoBase *            operator [](int i) const
        { return ( (SoBase *) ( (*(const SbPList *) this) [i] ) ); }

    //! Sets an element of a list.
    void                set(int i, SoBase *ptr);

    //! Indicates whether to call ref() and unref() for bases in the
    //! list when adding/removing them. The default value is TRUE.
    void                addReferences(bool flag)      { addRefs = flag; }

  private:
    //! If TRUE (the default), this refs and unrefs things in the list
    bool                addRefs;
};

////////////////////////////////////////////////////////////////////////////////
//! Maintains a list of pointers to nodes.
/*!
\class SoNodeList
\ingroup General
This subclass of SoBaseList holds lists of pointers to
SoNodes.  It updates reference counts to nodes in the list
whenever adding or removing pointers.

\par See Also
\par
SoNode
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoNodeList : public SoBaseList {
  public:
    SoNodeList()                        : SoBaseList()  {}
    SoNodeList(int size)                : SoBaseList(size) {}
    SoNodeList(const SoNodeList &l)     : SoBaseList(l) {}
    //! Destructor.
    ~SoNodeList()                       { }

    //! Adds a pointer to the end of the list.
    void                append(SoNode * ptr)
        { ((SoBaseList *) this)->append((SoBase *) ptr); }

    //! Copies a list, keeping all reference counts correct.
    SoNodeList &        operator =(const SoNodeList &l)
        { SoBaseList::copy(l) ; return *this; }

    SoNode *            operator [](int i) const
        { return ( (SoNode *) ( (*(const SoBaseList *) this) [i] ) ); }
};

////////////////////////////////////////////////////////////////////////////////
//! Maintains a list of pointers to paths.
/*!
\class SoPathList
\ingroup General
This subclass of SoBaseList holds lists of pointers to
SoPaths.  It updates reference counts to paths in the list
whenever adding or removing pointers.

\par See Also
\par
SoPath
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoPathList : public SoBaseList {
  public:
    SoPathList()                        : SoBaseList()  {}
    SoPathList(int size)                : SoBaseList(size) {}
    SoPathList(const SoPathList &l)     : SoBaseList(l) {}
    //! Destructor.
    ~SoPathList()                       { }

    //! Adds a path to the end of the list.
    void                append(SoPath * ptr)
        { ((SoBaseList *) this)->append((SoBase *) ptr); }

    //! Copies a list, keeping all reference counts correct.
    SoPathList &        operator =(const SoPathList &l)
        { SoBaseList::copy(l) ; return *this; }

    SoPath *            operator [](int i) const
        { return ( (SoPath *) ( (*(const SoBaseList *) this) [i] ) ); }

    //! Returns the index of the matching path in the list, or -1 if not found.
    int                 findPath(const SoPath &path);

    //! Sorts list in place based on (1) increasing address of head node, then
    //! (2) increasing indices of children.
    void                sort();

    //! Given a sorted list, removes any path that (1) is a duplicate, or (2)
    //! goes through a node that is the tail of another path.
    void                uniquify();

  private:
    //! Comparison method for path list sorting.
    static int          comparePaths(const void *p1Ptr, const void *p2Ptr);
};

////////////////////////////////////////////////////////////////////////////////
//! Maintains a list of pointers to engines.
/*!
\class SoEngineList
\ingroup Engines
This subclass of SoBaseList holds lists of pointers to
SoEngines.  It updates reference counts to engines in the list
whenever adding or removing pointers.

\par See Also
\par
SoEngine
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoEngineList : public SoBaseList {
  public:
    SoEngineList()                      : SoBaseList()  {}
    SoEngineList(int size)              : SoBaseList(size) {}
    SoEngineList(const SoEngineList &l) : SoBaseList(l) {}
    //! Destructor.
    ~SoEngineList()                     { }

    //! Adds an engine to the end of the list.
    void                append(SoEngine * ptr)
        { ((SoBaseList *) this)->append((SoBase *) ptr); }

    //! Copies a list, keeping all reference counts correct.
    SoEngineList &      operator =(const SoEngineList &l)
        { SoBaseList::copy(l) ; return *this; }

    SoEngine *          operator [](int i) const
        { return ( (SoEngine *) ( (*(const SoBaseList *) this) [i] ) ); }
};

////////////////////////////////////////////////////////////////////////////////
//! Maintains a list of SoTypes.
/*!
\class SoTypeList
\ingroup General
This subclass of SbPList holds lists of SoType type identifiers.

\par See Also
\par
SoType
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoTypeList : public SbPList {
  public:
    SoTypeList()                        : SbPList()     {}
    SoTypeList(int size)                : SbPList(size) {}
    SoTypeList(const SoTypeList &l)     : SbPList(l)    {}
    //! Destructor.
    ~SoTypeList()                       { truncate(0); }

    //! Adds a type to the end of the list.
    void                append(SoType typeId);

    //! Returns index of given type in list, or -1 if not found.
    int                 find(SoType typeId) const;

    //! Inserts given type in list before type with given index.
    void                insert(SoType typeId, int addBefore);

    //! Access an element of a list
    SoType              operator [](int i) const;

    //! Sets an element of a list.
    void                set(int i, SoType typeId);
};

////////////////////////////////////////////////////////////////////////////////
//! Maintains a list of instances of details.
/*!
\class SoDetailList
\ingroup Details
This subclass of SbPList holds lists of instances of
classes derived from SoDetail.

\par See Also
\par
SoDetail
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoDetailList : public SbPList {
  public:
    SoDetailList()                      : SbPList()     {}
    SoDetailList(int size)              : SbPList(size) {}
    //! Constructor that copies the contents of another list.
    SoDetailList(const SoDetailList &l);
    //! Destructor.
    ~SoDetailList()                     { truncate(0); }

    //! Adds a detail to the end of the list.
    void                append(SoDetail *detail)
        { SbPList::append((void *) detail); }

    //! Inserts given detail in list before detail with given index.
    void                insert(SoDetail *detail, int addBefore)
        { SbPList::insert((void *) detail, addBefore); }

    //! Removes all details after one with given index, inclusive. Removed
    //! detail instances are deleted.
    void                truncate(int start);

    //! Copies a list, making a copy of each detail instance in the list.
    void                copy(const SoDetailList &l);
    //! Copies a list, making a copy of each detail instance in the list.
    SoDetailList &      operator =(const SoDetailList &l)
        { copy(l) ; return *this; }

    //! Access an element of a list
    SoDetail *          operator [](int i) const
        { return ( (SoDetail *) ( (* (const SbPList *) this) [i] ) ); }

    //! Sets an element of a list, deleting the old entry first.
    void                set(int i, SoDetail *detail);
};

////////////////////////////////////////////////////////////////////////////////
//! Maintains a list of pointers to SoPickedPoint instances.
/*!
\class SoPickedPointList
\ingroup General
This subclass of SbPList holds lists of pointers to
instances of classes derived from SoPickedPoint. It is used primarily
to return information from picking with the SoRayPickAction class.

\par See Also
\par
SoPickedPoint, SoRayPickAction
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoPickedPointList : public SbPList {
  public:
    SoPickedPointList()                 : SbPList()     {}
    SoPickedPointList(int size)         : SbPList(size) {}
    //! Constructor that copies the contents of another list.
    SoPickedPointList(const SoPickedPointList &l);
    //! Destructor.
    ~SoPickedPointList()                                { truncate(0); }

    //! Adds a pointer to the end of the list.
    void                append(SoPickedPoint *pickedPoint)
        { SbPList::append((void *) pickedPoint); }

    //! Inserts given pointer in list before pointer with given index.
    void                insert(SoPickedPoint *pickedPoint, int addBefore)
        { SbPList::insert((void *) pickedPoint, addBefore); }

    //! Removes all pointers after one with given index, inclusive, deleting all
    //! instances removed from the list.
    void                truncate(int start);

    //! Access an element of a list
    SoPickedPoint *     operator [](int i) const
        { return ( (SoPickedPoint *) ( (* (const SbPList *) this) [i] ) ); }

    //! Sets an element of a list.
    void                set(int i, SoPickedPoint *pickedPoint);
};

////////////////////////////////////////////////////////////////////////////////
//! Maintains a list of pointers to fields.
/*!
\class SoFieldList
\ingroup Fields
This subclass of SbPList holds lists of pointers to
instances of classes derived from SoField.

\par See Also
\par
SoField
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoFieldList : public SbPList {
  public:
    SoFieldList()                       : SbPList()     {}
    SoFieldList(int size)               : SbPList(size) {}
    SoFieldList(const SoFieldList &l)   : SbPList(l)    {}
    //! Destructor.
    ~SoFieldList()                      { truncate(0); }

    //! Adds a pointer to the end of the list.
    void                append(SoField *field)
        { SbPList::append((void *) field); }

    //! Inserts given pointer in list before pointer with given index.
    void                insert(SoField *field, int addBefore)
        { SbPList::insert((void *) field, addBefore); }

    //! Access an element of a list
    SoField *           operator [](int i) const
        { return ( (SoField *) ( (* (const SbPList *) this) [i] ) ); }

    //! Sets an element of a list.
    void                set(int i, SoField *Field)
        { (* (const SbPList *) this) [i] = (void *) Field; }

//! Internal versions of [] that do not check for bounds:
  SoINTERNAL public:
    SoField *           get(int i) const
        { return (SoField *)SbPList::get(i); }
};

////////////////////////////////////////////////////////////////////////////////
//! Maintains a list of pointers to engine outputs.
/*!
\class SoEngineOutputList
\ingroup Engines
This subclass of SbPlist holds lists of pointers to
SoEngineOutputs.  It updates reference counts to engine outputs in the list
whenever adding or removing pointers.

\par See Also
\par
SoEngineOutput
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoEngineOutputList : public SbPList {
  public:
    SoEngineOutputList()                        : SbPList()     {}
    SoEngineOutputList(int size)                : SbPList(size) {}
    SoEngineOutputList(const SoEngineOutputList &l)     : SbPList(l)    {}
    //! Destructor.
    ~SoEngineOutputList()                       { truncate(0); }

    //! Adds an engine output to the end of the list.
    void                append(SoEngineOutput *engineOutput)
        { SbPList::append((void *) engineOutput); }

    //! Inserts the given engine output in the list before the 
    //! element of the given index.
    void                insert(SoEngineOutput *engineOutput, int addBefore)
        { SbPList::insert((void *) engineOutput, addBefore); }

    //! Access an element of a list
    SoEngineOutput *            operator [](int i) const
        { return ( (SoEngineOutput *) ( (* (const SbPList *) this) [i] ) ); }

    //! Sets an element of a list.
    void                set(int i, SoEngineOutput *engineOutput)
        { (* (const SbPList *) this) [i] = (void *) engineOutput; }
};

///////////////////////////////////////////////////////////////////////////////

#endif /* _SO_LISTS_ */
