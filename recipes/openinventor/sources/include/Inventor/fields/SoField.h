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
 |      Defines the SoField class, which is the base class for all fields.
 |
 |   Author(s)          : Paul S. Strauss, Nick Thompson, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_FIELD_
#define  _SO_FIELD_

#include <Inventor/SbString.h>
#include <Inventor/SoType.h>
#include <Inventor/misc/SoNotification.h>

class SoEngineOutput;
class SoFieldContainer;
struct SoFieldAuditorInfo;
class SoFieldConverter;
class SoFieldList;
class SoInput;
class SoNotList;
class SoOutput;


////////////////////////////////////////////////////////////////////////////////
//! Base class for all fields.
/*!
\class SoField
\ingroup Fields
SoField is the abstract base class for all fields. Fields
are the data elements contained within nodes and are the input values
for engines.
Each node or engine class specifies a set of fields and associates a
name with each.
These names define the semantics of the field (e.g., the SoCube
node contains three float fields named width, height, and depth).
Field classes provide the access methods that indirectly allow editing
and querying of data within nodes.


There are two abstract subclasses of SoField: SoSField
is the base class for all single-valued field classes and
SoMField is the base class for all multiple-valued fields, which
contain dynamic arrays of values. Subclasses of SoSField have an
SoSF prefix, and subclasses of SoMField have an SoMF
prefix.  See the reference pages for SoSField and SoMField for
additional methods.


Fields are typically constructed only within node or engine
instances; if you need a field that is not part of a node or engine,
you can create a GlobalField; see the methods on SoDB for
creating global fields.


Fields can be connected either directly to another field, or can be
connected to the output of an engine.  The value of a field with a
connection will change when the thing it is connected to changes.  For
example, consider a field "A" that is connected from "B" (by
A-&gt;connectFrom(B)).
When B's value is changed, A's value will also
change.  Note that A and B may have different values, even if they are
connected: if A's value is set after B's value, A's value will be
different from B's until B's value is set.


A field can be connected to several other fields, but can be connected
from only one source.


It is possible (and often useful) to create loops of field
connections (for example, A connected from B and B connected from A).
If there are loops, then the rule is that the last 
setValue() done
overrides any connections in to that value.  You can think of setting
the value of a field as immediately propagating that value forward
into all the fields it is connected to, with the propagation stopping
at the place where the original setValue() occurred if there is a
connection loop.  (Actually, a more efficient mechanism than this is
used, but the semantics are the same.)


If you try to connect two fields of differing types, Inventor will
automatically try to insert a field converter engine between them to
convert values from one type into the other.  Inventor has most
reasonable conversions built-in (multiple-valued field to single-valued 
and vice versa, anything to SoSFString, anything to
SoSFTrigger, float/short/unsigned short/int32_t/uint32_t/etc
numeric conversions, etc). You can add field converters using SoDB's
extender method addConverter(); see the SoDB.h header file for
details.  You can also find out if a converter is available with the
SoDB::getConverter() method.


Fields each define their own file format for reading and being written
to files, but all fields follow the same conventions:


Fields in a node or engine are written as the name of the field
followed by the field's value; fields are not written if they have not
been modified since they were created (if they have their default
value).


The ignored flag is written as a "~" character after the field's
value (if the field's value is its default value, just the "~" is
written).


Field connections are written as an "=" followed by the container of
the field or engine output that the field is connected to, followed by
a "." and the name of the field or engine output.  For example:
\code
DEF node1 Transform { translation 1 1 1 }
DEF node2 Scale { scaleFactor 1 1 1 = USE node1.translation }
\endcode


Global fields are written as part of an internal SoFieldContainer
class called GlobalField, which writes out an \b SoSFName  field named
\b type  whose value is the type of the global field, followed by
a field of that type whose name is the name of the global field.  For
example, a global uint32_t field called "FrameCounter" whose
value is 494 would be written as:
\code
GlobalField {
	type SoSFUInt32
	FrameCounter 494
}
\endcode

\par See Also
\par
SoSField, SoMField, SoNode, SoDB
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoField {
  public:
    //! Destructor
    virtual ~SoField();

    //! Sets the ignore flag for this field. When a field's ignore flag
    //! is set to TRUE, the field is not used during traversal for rendering
    //! and other actions. The default value for this flag is FALSE.
    void                setIgnored(bool ig);
    //! Gets the ignore flag for this field.
    //! \see setIgnored
    bool                isIgnored() const       { return flags.ignored; }

    //! Gets the state of default flag of the field. This flag will be TRUE
    //! for any field whose value is not modified after construction and will
    //! be FALSE for those that have changed (each node or engine determines
    //! what the default values for its fields are).  Note: the state of this
    //! flag should not be set explicitly from within applications.
    bool                isDefault() const       { return flags.hasDefault; }

    //! Return the type identifier for this field class.
    static SoType       getClassTypeId()        { return classTypeId; }

    //! Return the type identifier for this field instance (SoField *).
    virtual SoType      getTypeId() const = 0;

    //! Returns TRUE if this field is the given type or derived from that
    //! type. This is typically used
    //! with the getClassTypeId() method to determine the type of an SoField *
    //! at run-time:
    //! \code
    //! SoField *field = ....;
    //! if (field->isOfType(SoSFFloat::getClassTypeId())) {
    //!     SoSFFloat *floatField = (SoSFFloat *)field);
    //!     floatField->setValue(4.5);
    //! }
    //! {}
    //! \endcode
    bool                isOfType(SoType type) const;

    //! Field connections may be enabled and disabled.  Disabling a field's
    //! connection is almost exactly like disconnecting it; the only
    //! difference is that you can later re-enable the connection by calling
    //! enableConnection(TRUE).  Note that disconnecting an engine output can
    //! cause the engine's reference count to be decremented and the engine to
    //! be deleted, but disabling the connection does not decrement its
    //! reference count.
    //! 
    //! 
    //! Re-enabling a connection will cause the value of the field to be
    //! changed to the engine output or field to which it is connected.
    //! 
    //! 
    //! A field's connection-enabled status is maintained even if the field is
    //! disconnected or reconnected.  By default, connections are enabled.
    void                enableConnection(bool flag);
    //! Returns FALSE if connections to this field are disabled.  Note that this
    //! may return FALSE even if the field is not connected to anything.
    bool                isConnectionEnabled() const
        { return flags.connectionEnabled; }

    //! Connects the field to the given output of an engine or to
    //! another field. Returns FALSE if the connection could not be made.
    bool                connectFrom(SoEngineOutput *engineOutput);
    bool                connectFrom(SoField *field);

    //! Disconnect the field from whatever it was connected to.  This does
    //! nothing if the field was not connected.
    void                disconnect();

    //! Returns TRUE if the field is connected to anything.
    bool                isConnected() const     { return flags.connected; }
    //! Returns TRUE if the field is connected to an engine's output.
    bool                isConnectedFromEngine() const
        { return (flags.connected &&   flags.fromEngine); }
    //! Returns TRUE if the field is connected to another field.
    bool                isConnectedFromField() const
        { return (flags.connected && ! flags.fromEngine); }

    //! Returns TRUE if this field is being written into by an engine, and
    //! returns the engine output it is connected to in \p engineOutput.  Returns
    //! FALSE and does not modify \p engineOutput if it is not connected to an
    //! engine.
    bool                getConnectedEngine(SoEngineOutput *&engineOutput) const;
    //! Returns TRUE if this field is being written into by another field, and
    //! returns the field it is connected to in \p writingField.  Returns
    //! FALSE and does not modify \p writingField if it is not connected to a
    //! field.
    bool                getConnectedField(SoField *&field) const;

    //! Adds pointers to all of the fields that this field is writing into
    //! (either fields in nodes, global fields or engine inputs) to the given
    //! field list, and returns the number of forward connections.
    int                 getForwardConnections(SoFieldList &list) const;

    //! Returns the containing node or engine
    SoFieldContainer *  getContainer() const;

    //! Sets the field to the given value, which is an ASCII string in the
    //! Inventor file format.  Each field subclass defines its own file
    //! format; see their reference pages for information on their file format.
    //! The string should contain only the field's value, <em>not</em> the field's
    //! name (e.g., "1.0", <em>not</em> "width 1.0"). This method 
    //! returns TRUE if the string is valid, FALSE if it is not.
    bool                set(const char *valueString);

    //! Returns the value of the field in the Inventor file format, even if
    //! the field has its default value.
    void                get(SbString &valueString);

    //! Simulates a change to the field, causing attached sensors to fire,
    //! connected fields and engines to be marked as needing evaluation, and so
    //! forth. Calling touch() on an instance of a derived field class is
    //! equivalent to calling setValue(getValue()) using the derived class's
    //! methods, except that the field's isDefault() status remains
    //! unchanged.
    virtual void        touch();

    //! Return TRUE (FALSE) if this field is of the same type and has the same
    //! value as \p f.
    bool                   operator ==(const SoField &f) const
        { return isSame(f); }
    //! Return TRUE (FALSE) if this field is of the same type and has the same
    //! value as \p f.
    bool                   operator !=(const SoField &f) const
        { return ! isSame(f); }

  SoEXTENDER protected:
    //! Constuctor:
    SoField();

  SoINTERNAL public:
    static void         initClass();

    //! Initialize ALL Inventor node classes
    static void         initClasses();

    //! Sets default flag
    void                setDefault(bool def)  { flags.hasDefault = (def ? 1 : 0 ); }

    //! Initiates or propagates notification through container
    virtual void        startNotify();
    virtual void        notify(SoNotList *list);

    //! Sets the containing node.  This also calls enableNotify(TRUE)
    //! and setDefault(TRUE).
    void                setContainer(SoFieldContainer *cont);

    //! Returns TRUE if the field really needs to be written out.
    //! Fields with default values that aren't ignored and
    //! aren't connected to anything will return FALSE.
    bool                shouldWrite() const;

    //! Adds/removes an auditor to/from list
    void                addAuditor(void *auditor, SoNotRec::Type type);
    void                removeAuditor(void *auditor, SoNotRec::Type type);

    //! Indicates whether notification will propagate as the result of
    //! setting the field value. Engines turn this off when writing
    //! results into fields, since notification has already propagated.
    bool                enableNotify(bool flag);
    bool                isNotifyEnabled() const
        { return flags.notifyEnabled; }

    //! Indicates whether notification will propagate to the SoFieldContainer
    //! that owns the field. The default is TRUE, so that a field
    //! will notify its container. If disabled, only the direct
    //! auditors (connected fields and field sensors) will be notified
    //! and the field container does not get a notification.
    //! This will prevent unwanted scene repaints (for pure "output fields"
    //! that are changed while scene traversal) but has the side effect that
    //! the owning field container does not get a new node id and
    //! thus one can not detect the field change from the container
    //! except by attaching a SoFieldSensor directly to the field.
    //! If notification is disabled via enableNotify(FALSE), this flag has no effect.
    //! (MeVis Only)
    bool                enableContainerNotify(bool flag);
    bool                isContainerNotifyEnabled() const
    { return flags.notifyContainerEnabled; }

    //! Indicates to a field that a change has been made involving a
    //! connection from it (as source) to another field. Passed the
    //! number of things being connected to the field; the number will
    //! be negative when things are disconnected.
    //! The default method does nothing.
    virtual void        connectionStatusChanged(int numConnections);

    //! If this returns TRUE, it means we're in the middle of doing a
    //! setValue()+valueChanged() and values from an upstream
    //! connection shouldn't write into this field.
    bool                isReadOnly() const { return flags.readOnly; }

    //! Returns TRUE if the given field is of the same type and has the
    //! same value(s) as this. Subclasses must define this as well as
    //! an == operator.
    virtual bool        isSame(const SoField &f) const = 0;

    //! Copies the value from one field to another, assuming same subclass
    virtual void        copyFrom(const SoField &f) = 0;

    //! After a field value has been copied using copyFrom(),
    //! this is called to allow fields to update the copy. This is used
    //! by node, engine, and path fields to make sure instances are
    //! handled properly. The default implementation does nothing.
    virtual void        fixCopy(bool copyConnections);

    //! This returns TRUE if this field contains a reference to a node
    //! or engine that is copied during a copy operation (i.e., it is
    //! "inside"). The default method just checks if the field is
    //! connected to such a node or engine. Subclasses may contain
    //! other tests, such as those that contain pointers to nodes or
    //! engines.
    virtual bool        referencesCopy() const;

    //! Copies connection from one field to another. Assumes fields are
    //! the same subclass and that this field is connected.
    void                copyConnection(const SoField *fromField);

    //! Reads value of field (with given name) from file as defined by
    //! SoInput. This does the work common to all fields, then calls
    //! other read methods to do the rest.
    virtual bool        read(SoInput *in, const SbName &name);

    //! Writes field (with given name) to file as defined by SoOutput
    virtual void        write(SoOutput *out, const SbName &name) const;

    //! Counts write-references on field to prepare for writing
    virtual void        countWriteRefs(SoOutput *out) const;

    //! Evaluates the field from whatever it's connected to. If
    //! there's no connection or we don't need to evaluate, this does
    //! nothing. This has to be const because it's used by getValue
    //! methods.
    void                evaluate() const
        { if (flags.dirty) evaluateConnection(); }

  protected:
    //! Called by an instance to indicate that a value has changed. If
    //! resetDefault is TRUE, this turns off default flag. Initiates
    //! notification, if necessary.
    void                valueChanged(bool resetDefault = TRUE);

    //! Evaluates the field or engine the field is connected to,
    //! storing the result in the field. This is const because it is
    //! called by evaluate().
    virtual void        evaluateConnection() const;

    //! Reads value(s) of field
    virtual bool        readValue(SoInput *in) = 0;

    //! Reads connection.
    virtual bool        readConnection(SoInput *in);

    //! Writes value(s) of field
    virtual void        writeValue(SoOutput *out) const = 0;

    //! Writes field connection
    virtual void        writeConnection(SoOutput *out) const;

  private:
    static SoType       classTypeId;

    //! These are used by SoField::get() to hold the returned field string
    static char         *fieldBuf;
    static int          fieldBufSize;

    //! The "flags" field contains several bit flags:
    struct {
        unsigned int hasDefault         : 1; //!< Field is set to default value
        unsigned int ignored            : 1; //!< Field value is to be ignored
        unsigned int connected          : 1; //!< Field connected from something
        unsigned int converted          : 1; //!< Connection required converter
        unsigned int fromEngine         : 1; //!< Connection is from engine
        unsigned int connectionEnabled  : 1; //!< Connection is enabled
        unsigned int notifyEnabled      : 1; //!< Notification is enabled
        unsigned int hasAuditors        : 1; //!< Connected, or FieldSensor
        unsigned int isEngineModifying  : 1; //!< Engine evaluating
        unsigned int readOnly           : 1; //!< Must not write into
                                             //! this field
        unsigned int dirty              : 1; //!< Field was notified and
                                             //! needs evaluation
        unsigned int notifyContainerEnabled : 1; //!< If set to 0, the container is not notified on Field changed
    } flags;

    //! If no other auditors, the container for this field is stored
    //! directly here.  If the field has other auditors (flags.hasAuditors)
    //! then the connection information and the container are
    //! stored in an opaque SoFieldAuditorInfo structure.  This is
    //! done to save space in the common case.
    union {
        SoFieldContainer *container;
        SoFieldAuditorInfo *auditorInfo;
    };

    //! Creates auditorInfo strucuture, if necessary:
    void                createAuditorInfo();

    //! Creates a converter engine to convert from the given field
    //! type to the type of this field. Returns NULL on error.
    SoFieldConverter    *createConverter(const SoType &fromFieldType) const;

    //! Really disconnects field from whatever it's connected to
    void                reallyDisconnect();

    //! Returns pointer to field converter, if fields was connected
    //! through one
    SoFieldConverter *  getConverter() const;

    //! Looks up what field connection is from (container and field/output name)
    void                getConnectionInfo(SoFieldContainer *&, SbName&) const;

    //! This is used to reallocate the string buffer used by
    //! SoField::get()
    static void *       reallocFieldBuf(void *ptr, size_t newSize);

friend class SoEngineOutput;
};


////////////////////////////////////////////////////////////////////////////////
//! Abstract base class for all single-value fields.
/*!
\class SoSField
\ingroup Fields
Each class derived from SoSField begins with an 
SoSF prefix and contains one value of a particular type. Each has 
setValue() and getValue() methods
that are used to change or
access this value. In addition, some field classes have extra
convenience routines that allow values to be set or retrieved in other
related formats (see below).


In addition to setValue(), all single-value fields overload the "="
assignment operator to set the field value from the correct datatype
or from another field instance of the same type.


The value of a single-value field is written to file in a format
dependent on the field type; see the subclass man pages for details.


A field that is ignored has a tilde (~)
either in place of the value (if the actual value is the default)
or after it (otherwise).

\par See Also
\par
SoField, SoMField
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoSField : public SoField {
  public:
    //! Destructor
    virtual ~SoSField();

    //! Return the type identifier for this field class.
    static SoType       getClassTypeId()        { return classTypeId; }

  protected:
    //! Constructor
    SoSField();

  SoINTERNAL public:
    static void         initClass();

    static void *       createInstance();

  private:
    static SoType       classTypeId;

    //! Reads value of field
    virtual bool        readValue(SoInput *in) = 0;

    //! Writes value of field
    virtual void        writeValue(SoOutput *out) const = 0;
};


////////////////////////////////////////////////////////////////////////////////
//! Base class for all multiple-valued fields.
/*!
\class SoMField
\ingroup Fields
Each class derived from SoMField begins with an SoMF prefix
and contains a dynamic array of values of a particular type.  Each has a
setValues() method
that is passed a pointer to a const array of values of the correct
type; these values are copied into the array in the field, making
extra room in the array if necessary. The start and num parameters to
this method indicate the starting array index to copy into and the
number of values to copy.


The getValues() method
for a multiple-value field returns a const pointer to the array of
values in the field. (Because this pointer is const, it cannot be used
to change values in this array.)


In addition, the indexing operator "[]" is overloaded to return the
\p i'th value in the array; because it returns a const reference, it can
be used only to get values, not to set them.


Methods are provided for getting the number of values in the field,
inserting space for new values in the middle, and deleting values.


There are other methods that allow you to set only one value of
several in the field and to set the field to contain one and only one
value.


Two other methods can be used to make several changes to a
multiple-value field without the overhead of copying values into and
out of the fields. The startEditing() method
returns a non-const pointer to the array of values in the field; this
pointer can then be used to change (but not add or remove) any values
in the array. The finishEditing() method
indicates that the editing is done and notifies any sensors or engines
that may be connected to the field.


SoMFields are written to file as a series of values separated by
commas, all enclosed in square brackets.  If the field has no values
(getNum() returns zero), then only the square brackets ("[]") are
written.  The last value may optionally be followed by a comma.  Each
field subtype defines how the values are written; for example, a field
whose values are integers might be written as:
\code
[ 1, 2, 3, 4 ]
   or:
[ 1, 2, 3, 4, ]
\endcode

\par See Also
\par
SoNode, SoEngine
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoMField : public SoField {

  public:
    //! Destructor
    virtual ~SoMField();

    //! Returns the number of values currently in the field.
    int                 getNum() const { evaluate(); return num; }

    //! Forces this field to have exactly num values, inserting or deleting
    //! values as necessary.
    void                setNum(int num);

    //! Deletes \p num values beginning at index \p start (index \p start through
    //! \p start+\p num-1 will be deleted, and any leftover values will be moved
    //! down to fill in the gap created).  A \p num of -1 means delete all values
    //! from \p start to the last value in the field; getNum() will return 
    //! \p start  as the number of values in the field after this operation
    //! (deleteValues(0, -1) empties the field).
    virtual void        deleteValues(int start, int num = -1);

    //! Inserts space for \p num values at index \p start.  Index \p start through
    //! \p start+\p num-1 will be moved up to make room.  For example, to make room
    //! for 7 new values at the beginning of the field call
    //! insertSpace(0, 10).
    virtual void        insertSpace(int start, int num);

    //! This is equivalent to the set() 
    //! method of SoField, but operates on
    //! only one value.  See the SoField methods for details.
    bool                set1(int index, const char *valueString);
    //! This is equivalent to the 
    //! get() method of SoField, but operates on
    //! only one value.  See the SoField methods for details.
    void                get1(int index, SbString &valueString);

    //! Return the type identifier for this field class.
    static SoType       getClassTypeId()        { return classTypeId; }

  SoINTERNAL public:
    static void         initClass();

    static void *       createInstance();

  protected:
    int                 num;            //!< Number of values
    int                 maxNum;         //!< Number of values allocated

    //! Constructor
    SoMField();

    //! Make sure there is room for newNum vals
    virtual void        makeRoom(int newNum);

  private:
    static SoType       classTypeId;

    //! These are used by SoMField::get1() to hold the returned field string
    static char         *fieldBuf;
    static int          fieldBufSize;

    //! Allocates room for num values. Copies old values (if any) into
    //! new area. Deletes old area, if any.
    virtual void        allocValues(int num) = 0;

    //! Deletes all current values
    virtual void        deleteAllValues() = 0;

    //! Copies value indexed by "from" to value indexed by "to"
    virtual void        copyValue(int to, int from) = 0;

    //! Reads all values of field
    virtual bool        readValue(SoInput *in);

    //! Reads one indexed value of field from file
    virtual bool        read1Value(SoInput *in, int index) = 0;

    //! Writes all values of field
    virtual void        writeValue(SoOutput *out) const;

    //! Writes indexed value to file
    virtual void        write1Value(SoOutput *out, int index) const = 0;

    //! Reads array of binary values from file
    virtual bool        readBinaryValues(SoInput *in, int numToRead);

    //! Writes array of binary values to file
    virtual void        writeBinaryValues(SoOutput *out) const;

    //! Returns number of ASCII values to write per output line (default 1)
    virtual int         getNumValuesPerLine() const;

    //! This is used to reallocate the string buffer used by
    //! SoField::get()
    static void *       reallocFieldBuf(void *ptr, size_t newSize);
};

#endif /* _SO_FIELD_ */
