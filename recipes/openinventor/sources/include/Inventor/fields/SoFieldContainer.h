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
 * Copyright (C) 1990,91,92   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.1.1.1 $
 |
 |   Description:
 |      Defines the SoFieldContainer class, which is the base class of
 |      all classes that contain fields (engines and nodes)
 |
 |   Classes:
 |      SoFieldContainer
 |
 |   Author(s)          : Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_FIELD_CONTAINER_
#define  _SO_FIELD_CONTAINER_

#include <Inventor/system/SbSystem.h>
#include <Inventor/misc/SoBase.h>


class SbDict;
class SoFieldData;
class SoFieldList;
class SoSensor;

////////////////////////////////////////////////////////////////////////////////
//! Abstract base class for objects that contain fields.
/*!
\class SoFieldContainer
\ingroup Fields
SoFieldContainer is the abstract base class for engines and nodes.
It contains methods for finding out what fields an object has,
controlling notification, and for dealing with all of the fields of an
object at once.


The fields of an engine are its inputs.  Note that even though an
engine's output corresponds to a specific type of field, an engine
output is not a field.

\par See Also
\par
SoSField, SoMField, SoNode, SoDB
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoFieldContainer : public SoBase {

  public:

    //! Returns the type of this class.
    static SoType       getClassTypeId()        { return classTypeId; }

    //! Sets all fields in this object to their default values.
    void                setToDefaults();

    //! Returns TRUE if all of the object's fields have their default values.
    //! This will return TRUE even if a field's isDefault() method returns 
    //! FALSE em for example, if a field's default value is 0.0 and you
    //! setValue(0.0)  that field, the default flag
    //! will be set to FALSE (because it would be too slow to compare the
    //! field against its default value every time setValue is called).
    //! However, hasDefaultValues() would return TRUE
    //! in this case.
    bool                hasDefaultValues() const;

    //! Returns TRUE if this object's fields are exactly equal to \p fc's fields.
    //! If \p fc is not exactly same type as this object, FALSE is returned.
    bool                fieldsAreEqual(const SoFieldContainer *fc) const;

    //! Copies the contents of \p fc's fields into this object's fields.  \p fc must
    //! be the same type as this object.  If \p copyConnections is TRUE, then if
    //! any of \p fc's fields are connected then this object's fields will also
    //! be connected to the same source.
    void                copyFieldValues(const SoFieldContainer *fc,
                                        bool copyConnections = FALSE);

    //! Sets one or more fields in this object to the values specified in the
    //! given string, which should be a string in the Inventor file format.
    //! TRUE is returned if the string was valid Inventor file format.  For
    //! example, you could set the fields of an SoCube by doing:
    //! \code
    //! SoCube *cube = ....
    //! cube->set("width 1.0 height 2.0 depth 3.2");
    //! \endcode
    bool                set(const char *fieldDataString)
        { return set(fieldDataString, NULL); }

    //! Returns the values of the fields of this object in the Inventor ASCII
    //! file format in the given string.  Fields whose
    //! isDefault() bit is set
    //! will not be part of the string.  You can use the
    //! field-&gt;get() method to get a field's value
    //! as a string even if has its default value.
    void                get(SbString &fieldDataString)
        { get(fieldDataString, NULL); }

    //! Appends pointers to all of this object's fields to resultList, and
    //! returns the number of fields appended.  The types of the fields can be
    //! determined using field-&gt;isOfType()
    //! and field-&gt;getTypeId(), and their
    //! names can be determined by passing the field pointers to the
    //! getFieldName() method (see below).
    virtual int         getFields(SoFieldList &list) const;

    //! Returns a pointer to the field with the given name. If no such
    //! field exists, NULL is returned.
    virtual SoField *   getField(const SbName &fieldName) const;

    //! Returns the name of the given field in the \p fieldName argument.
    //! Returns FALSE if field is not a member of this object.
    bool                getFieldName(const SoField *field,
                                     SbName &fieldName) const;

    //! Notification at this Field Container is enabled (if flag == TRUE) or 
    //! disabled (if flag == FALSE).  The returned boolean value indicates
    //! whether notification was enabled immediately prior to applying this method.
    bool                enableNotify(bool flag)       // returns old value
        { bool e = notifyEnabled; notifyEnabled = flag; return e; }
    //! Notification is the process of telling interested objects that this
    //! object has changed.  Notification is needed to make engines and
    //! sensors function, is used to keep SoPaths up to date when the
    //! scene graph's topology changes, and is also used to invalidate
    //! rendering or bounding box caches.
    //! 
    //! 
    //! Notification is normally enabled, but can be disabled on a node by
    //! node (or engine by engine) basis.  If you are making extensive changes
    //! to a large part of the scene graph then disabling notification can
    //! increase performance, at the expense of increased
    //! responsibility for making sure that any interested engines, sensors or
    //! paths are kept up to date.
    //! 
    //! 
    //! For example, if you will be making a lot of changes to a small part of
    //! your scene graph and you know that there are no engines or sensors
    //! attached to nodes in that part of the scene graph, you might disable
    //! notification on the nodes you are changing, modify them, re-enable
    //! notification, and then touch() one of the nodes to cause a redraw.
    //! 
    //! 
    //! However, you should profile your application and make sure that
    //! notification is taking a significant amount of time before going to
    //! the trouble of manually controlling notification.
    bool                isNotifyEnabled() const    { return notifyEnabled; }

  SoINTERNAL public:
    //! Setup type information
    static void         initClass();

    //! Sets one or more fields in this object to the values specified in the
    //! given string, which should be a string in the Inventor file format.
    //! TRUE is returned if the string was valid Inventor file format.  For
    //! example, you could set the fields of an SoCube by doing:
    //! \code
    //! SoCube *cube = ....
    //! cube->set("width 1.0 height 2.0 depth 3.2");
    //! \endcode
    bool                set(const char *fieldDataString, SoInput *dictIn);
    //! Returns the values of the fields of this object in the Inventor ASCII
    //! file format in the given string.  Fields whose
    //! isDefault() bit is set
    //! will not be part of the string.  You can use the
    //! field-&gt;get() method to get a field's value
    //! as a string even if has its default value.
    void                get(SbString &fieldDataString, SoOutput *dictOut);

    //! Propagates modification notification through an instance.
    virtual void        notify(SoNotList *);

    //! Adds a reference to the instance when writing. isFromField
    //! indicates whether the reference is from a field-to-field
    //! connection.
    virtual void        addWriteReference(SoOutput *out,
                                          bool isFromField = FALSE);

    //! Writes instance to SoOutput. (Used only for last stage of writing)
    virtual void        writeInstance(SoOutput *out);

    //! Returns whether or not instance is considered 'built-in' to the
    //! library.  Used during writing.
    bool                getIsBuiltIn() const { return isBuiltIn; }

    //! Returns an SoFieldData structure for the node. Objects with no
    //! fields should return NULL, which is what the default method does.
    virtual const SoFieldData * getFieldData() const;

    /////////////////////////////////////////////
    ///
    /// During a copy operation, copies of nodes and engines are
    /// stored in a dictionary, keyed by the original node or engine
    /// pointer, so that copies can be re-used. These methods
    /// operate on that dictionary.

    //! Initializes a new copy dictionary
    static void                 initCopyDict();

    //! Adds an instance to the dictionary
    static void                 addCopy(const SoFieldContainer *orig,
                                        const SoFieldContainer *copy);

    //! If a copy of the given instance is in the dictionary, this
    //! returns it. Otherwise, it returns NULL. The copy is not changed
    //! in any way.
    static SoFieldContainer *   checkCopy(const SoFieldContainer *orig);

    //! If a copy of the given instance is not in the dictionary, this
    //! returns NULL. Otherwise, this copies the contents of the
    //! original into the copy (if not already done) and returns a
    //! pointer to the copy.
    static SoFieldContainer *   findCopy(const SoFieldContainer *orig,
                                         bool copyConnections);

    //! Cleans up the dictionary when done. 
    static void                 copyDone();

    //!
    /////////////////////////////////////////////

    //! Copies the contents of the given node into this instance. The
    //! default implementation copies just field values and the name.
    virtual void                copyContents(const SoFieldContainer *fromFC,
                                             bool copyConnections);

    //! During a copy operation, this copies an instance that is
    //! encountered through a field connection. The default
    //! implementation just returns the original pointer - no copy is
    //! done. Subclasses such as nodes and engines handle this
    //! differently.
    virtual SoFieldContainer *  copyThroughConnection() const;

    //! Adds a sensor which is managed by the field container.
    //! It will be deleted when the container is deleted.
    void addManagedSensor(SoSensor* sensor);

  protected:

    //! Is the subclass a built-in Inventor subclass or an extender subclass?
    //! This is used to determine whether to read/write field type information.
    bool                isBuiltIn;

    SoFieldContainer();
    ~SoFieldContainer();

    //! Reads stuff into instance. Returns FALSE on error
    virtual bool        readInstance(SoInput *in, unsigned short flags);

  private:
    static SoType       classTypeId;
    bool                notifyEnabled;  //!< Whether notification is enabled

    //! a list of managed field sensors which are deleted when the instance is deleted
    SbPList*            _managedSensors;

    //! This holds a list of SbDict instances used during copy
    //! operations. It is a list to allow recursive copying.
    static SbPList      *copyDictList;

    //! And this callback is used to unref() all instances in the
    //! copyDict when copyDone() is called
    static void         unrefCopy(size_t key, void *instPtr);

    //! These are used by SoFieldContainer::get() to hold
    //! the returned field string
    static char         *fieldBuf;
    static size_t       fieldBufSize;

    //! This is used to reallocate the string buffer used by
    //! SoFieldContainer::get()
    static void *       reallocFieldBuf(void *ptr, size_t newSize);
};

#endif  /* _SO_FIELD_CONTAINER_ */
