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
 |      Defines the SoNodekitCatalog class. This class is used to 
 |      describe the subgraphs that make up different classes of 
 |      nodekit.        
 |
 |   Author(s)          : Paul Isaacs, Thad Beier
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
*/

#ifndef  _SO_NODEKIT_CATALOG
#define  _SO_NODEKIT_CATALOG

#include <Inventor/misc/SoBasic.h>
#include <Inventor/SbString.h>
#include <Inventor/SoLists.h>
#include <Inventor/SoType.h>

#define SO_CATALOG_NAME_NOT_FOUND -1
#define SO_CATALOG_THIS_PART_NUM   0

/////////////////////////////////////////////////////////////////////
///
////  \class SoNodekitCatalogEntry
///
///    an internal class that should be accessed only by an SoNodekitCatalog
///
///
////////////////////////////////////////////////////////////////////
SoINTERNAL class INVENTOR_API SoNodekitCatalogEntry {
    private:
        SbName     name;                //!< Reference name of this entry 
        SoType     type;                //!< Type of node allowable for setting
                                        //! this entry. 'type' may be an 
                                        //! abstract node type
        SoType     defaultType;         //!< Type of node to create if the nodekit
                                        //! is asked to build this part itself.
                                        //! May not be an abstract node type.
        bool       nullByDefault;       //!< If FALSE, then this part is 
                                        //! created within the constructor.
                                        //! Otherwise, it isn't.
        bool       leafPart;            //!< Is this entry a leaf node in the 
                                        //! nodekit's structure?
        SbName     parentName;          //!< Reference name of this entry's parent
        SbName     rightSiblingName;    //!< Name of right sibling of the entry
        bool       listPart;            //!< Is this entry a list of nodes?
        SoType     listContainerType;   //!< If so, what kind of container?
        SoTypeList listItemTypes;       //!< If so, what types of nodes may
                                        //! it contain?
        bool       publicPart;          //!< Can a user be given a pointer to
                                        //! this part?
    SoINTERNAL public:
        //! constructor
        SoNodekitCatalogEntry(const SbName &theName, 
                    SoType theType, SoType theDefaultType, 
                    bool theNullByDefault,
                    const SbName &theParentName, const SbName &theRightSiblingName, 
                    bool theListPart, SoType theListContainerType,
                    const SoTypeList &theListItemTypes,
                    bool thePublicPart);

        //! clone exactly, or make a clone with a given type...
        SoNodekitCatalogEntry *clone() const;           
        SoNodekitCatalogEntry *clone( SoType newType,
                                      SoType newDefaultType ) const; 

        //! inquiry functions:
        const SbName  &getName() const { return name; };
              SoType  getType() const { return type; };
              SoType  getDefaultType() const { return defaultType; };
              bool    isNullByDefault() const { return nullByDefault; };
              bool    isLeaf() const { return leafPart; };
        const SbName  &getParentName() const { return parentName; };
        const SbName  &getRightSiblingName() const { return rightSiblingName; };
              bool    isList() const { return listPart; };
              SoType  getListContainerType() const {return listContainerType;};
        const SoTypeList &getListItemTypes() const { return listItemTypes; };
              bool    isPublic() const { return publicPart; };

        //! For adding to the set of node types allowed beneath a list...
        void addListItemType( SoType typeToAdd );

        void setNullByDefault( bool newNullByDefault ) 
                { nullByDefault = newNullByDefault; }
        //! these should only by used by catalogs when an entry
        //! is given a new child or left sibling...
        void setPublic( bool newPublic ) { publicPart = newPublic; }
        void setLeaf( bool newLeafPart ) { leafPart = newLeafPart; }
        void setRightSiblingName( const SbName &newN ) { rightSiblingName = newN; }
        //! This should only by used by catalogs when an entry is changing
        //! type and/or defaultType
        void setTypes( SoType newType, SoType newDefaultType )
                            { type = newType; defaultType = newDefaultType; }

        //! recursively search this entry for 'name to find' in the 
        //! templates of this entry and its descendants
        bool recursiveSearch( const SbName &nameToFind, 
                                SoTypeList *typesChecked) const;

        void printCheck() const; //!< prints the contents of this entry
};


////////////////////////////////////////////////////////////////////////////////
//! Nodekit catalog class.
/*!
\class SoNodekitCatalog
\ingroup Nodekits
This class describes the parts and structure of a nodekit.  Each class of
nodekit has one SoNodekitCatalog (a static variable for the class).
Internally, the catalog contains one entry for each "part" in the
nodekit's structure. Users can query the catalog for information about
each entry in the catalog. This information can be obtained either by
part name (an SbName unique for the part within the catalog) or by part
number (an index into an array of parts).


Note that, although the catalog for a nodekit class may contain many
entries, each instance of that class is not initially created with all of
these parts intact. Rather, each instance of the class has its own
parts list which keeps track of which parts the user has created. The
nodekit uses the catalog as a guide in creating new nodes as its
descendants; the standard addChild(), removeChild() and other 
SoGroup  methods are protected, so that users must create descendants 
indirectly by asking the nodekit to get and/or set the different "parts"
in the catalog.


The first entry in any SoNodekitCatalog corresponds to the nodekit
itself. Its \p partName is "this" and its \p partNumber is 0. All other 
parts in the catalog are described relative to "this."

\par See Also
\par
SoAppearanceKit, SoBaseKit, SoCameraKit, SoLightKit, SoNodeKit, SoNodeKitDetail, SoNodeKitListPart, SoNodeKitPath, SoSceneKit, SoSeparatorKit, SoShapeKit, SoWrapperKit
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoNodekitCatalog {

  public:

    //! Initializes this object.
    static void initClass();

    //! Returns number of entries in the catalog.
    int        getNumEntries() const { return numEntries; };

          //! Given the name of a part, returns its part number in the catalog.
          int        getPartNumber(      const SbName &theName ) const;
    //! Given the part number of a part, returns its name in the catalog.
    const SbName     &getName(                 int    thePartNumber ) const;
          SoType     getType(                  int    thePartNumber ) const;
          SoType     getType(            const SbName &theName ) const;
          SoType     getDefaultType(           int    thePartNumber ) const;
          SoType     getDefaultType(     const SbName &theName ) const;
          bool       isNullByDefault(          int    thePartNumber ) const;
          bool       isNullByDefault(            const SbName &theName ) const;
          bool       isLeaf(                   int    thePartNumber ) const;
          bool       isLeaf(             const SbName &theName ) const;
    const SbName     &getParentName(           int    thePartNumber ) const;
    const SbName     &getParentName(     const SbName &theName ) const;
          int        getParentPartNumber(      int    thePartNumber ) const;
          int        getParentPartNumber(const SbName &theName ) const;
    const SbName     &getRightSiblingName(      int    thePartNumber ) const;
    const SbName     &getRightSiblingName(const SbName &theName ) const;
          int        getRightSiblingPartNumber(      int thePartNumber ) const;
          int        getRightSiblingPartNumber(const SbName &theName ) const;
          bool       isList(                   int    thePartNumber ) const;
          bool       isList(             const SbName &theName ) const;
          SoType     getListContainerType(       int    thePartNumber ) const;
          SoType     getListContainerType( const SbName &theName ) const;
    const SoTypeList    &getListItemTypes(       int    thePartNumber ) const;
    const SoTypeList    &getListItemTypes( const SbName &theName ) const;
          bool       isPublic(                 int    thePartNumber ) const;
          bool       isPublic(           const SbName &theName ) const;

  SoEXTENDER public:
    //! Catalogs are only constructed, destructed, cloned or added to  
    //! by subclasses of SoBaseKit.
    //! This should be accomplished using the macros provided in SoSubKit.h

    //! Constructor
    SoNodekitCatalog();

    //! Destructor
    ~SoNodekitCatalog();

    //! Make a new identical copy, but you must give the node type for 'this' 
    //! (where 'this' is the top level node in the template )
    SoNodekitCatalog *clone( SoType typeOfThis ) const;

    //! Adding entries
    bool addEntry(const SbName &theName, 
                          SoType theType, SoType theDefaultType,
                          bool    theNullByDefault,
                    const SbName &theParentName, 
                    const SbName &theRightSiblingName, bool theListPart, 
                          SoType theListContainerType,
                          SoType theListItemType,
                          bool thePublicPart);

    //! For adding to the set of node types allowed beneath a list...
    void addListItemType(int thePartNumber, SoType typeToAdd);
    void addListItemType(const SbName &theName,   SoType typeToAdd);

    //! For changing the type and defaultType of an entry.
    //! The new types must be subclasses of the types already existing in the
    //! entry.  
    //! For example, in SoShapeKit, the part "shape" has type SoShape and
    //! default type SoSphere.  Any shape node is acceptable, but be default a 
    //! sphere will be built.
    //! Well, when creating the SoVertexShapeKit class, a call of:
    //!    narrowTypes( "shape", SoVertexShape::getClassTypeId(), 
    //!                          SoFaceSet::getClassTypeId())
    //! might be used.  This would reflect the fact that:
    //! Only vertext shapes may be put in the "shape"  part, not just any shape.
    //! And also, by default, a faceSet will be built, not a sphere.
    void narrowTypes( const SbName &theName, SoType newType, 
                      SoType newDefaultType );

    void setNullByDefault( const SbName &theName, bool newNullByDefault );

  SoINTERNAL public:
    //! used by SoNodekitParts to search through catalogs.
    //! recursively search a given part for 'name to find' in the 
    //! templates of that entry and its descendants
    bool recursiveSearch( int partNumber, const SbName &nameToFind, 
                            SoTypeList *typesChecked) const;

    void printCheck() const; //!< prints the contents of this catalog

  private:

    static const SbName  *emptyName;
    static const SoTypeList *emptyList;
    static SoType  *badType;

    int                   numEntries;   //!< how many entries?
    SoNodekitCatalogEntry **entries;    //!< the array of entries
    SbDict                partNameDict; //!< For fast lookup of part numbers

    //! Used for testing various aspects of new entries into a catalog
    bool      checkName( const SbName &theName );
    bool      checkNewName( const SbName &theName );
    bool      checkNewTypes( SoType theType, 
                             SoType theDefaultType );
    bool      checkAndGetParent(    const SbName &theName, 
                                    const SbName &theParentName, 
                                    SoNodekitCatalogEntry *& parentEntry );
    bool      checkAndGetSiblings(  const SbName &theParentName, 
                                    const SbName &theRightSiblingName, 
                                    SoNodekitCatalogEntry *& leftEntry,
                                    SoNodekitCatalogEntry *& rightEntry );
    bool      checkCanTypesBeList(  SoType theType,
                                    SoType theDefaultType,
                                    SoType theListContainerType );

};

#endif  /* _SO_NODEKIT_CATALOG */
