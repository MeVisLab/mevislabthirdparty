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
 |      Defines the SoDB class
 |
 |   Author(s)          : Paul S. Strauss, Nick Thompson, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_DB_
#define  _SO_DB_

#include <Inventor/system/SbSystem.h>
#include <Inventor/sensors/SoSensorManager.h>
#include <Inventor/SoType.h>
#include <Inventor/SbPList.h>

class SoBase;
class SoSFRealTime;
class SoSeparator;
class SoInput;
class SoPath;
class SoNode;
class SoField;

typedef void SoDBHeaderCB(void *userData, SoInput *in);


////////////////////////////////////////////////////////////////////////////////
//! Scene graph database class.
/*!
\class SoDB
\ingroup General
The SoDB class holds all scene graphs, each representing a 3D
scene used by an application. A scene graph is a collection of SoNode
objects which come in several varieties (see SoNode).
Application programs must initialize the database by calling
SoDB::init()
before calling any other database routines and before constructing any
nodes, paths, functions, or actions. Note that 
SoDB::init() is called by 
SoInteraction::init(),
and SoNodeKit::init(), so if you are calling any of these
methods, you do not need to call 
SoDB::init() directly.
All methods on this class are static.


Typical program database initialization and scene reading is as follows:
<tt>\code
#include <Inventor/SoDB.h>
#include <Inventor/SoInput.h>
#include <Inventor/nodes/SoSeparator.h>
SoSeparator  *rootSep;
SoInput      in;
SoDB::init();
rootSep = SoDB::readAll(&in);
if (rootSep == NULL)
    printf("Error on read...\n");
 ...\
\endcode
</tt>

\par See Also
\par
SoBase, SoNode, SoEngine, SoField, SoInput, SoFile, SoPath, SoOneShotSensor, SoDataSensor
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoDB {

  public:

    //! Initializes the database.  This must be called before calling any
    //! other database routines, including the construction of any nodes,
    //! paths, engines, or actions.
    static void         init();

    //! Returns a character string identifying the version of the Inventor
    //! library in use.
    static const char   *getVersion();

    //! \see read(SoInput *in, SoPath *&path)
    static bool         read(SoInput *in, SoNode *&rootNode);

    //! Reads a graph from the file specified by the given SoInput,
    //! returning a pointer to the resulting root node in \p rootNode, or a
    //! pointer to the resulting path in \p path.  The programmer is
    //! responsible for determining which routine to use, based on the contents
    //! of the input. These routines return FALSE if any error occurred during
    //! reading.
    //! 
    //! 
    //! If the passed SoInput was used to open a file and the name of the
    //! file contains a directory, SoDB automatically adds the directory
    //! to the end of the current directory search path in the SoInput.
    //! This means that nested files named in SoFile nodes may be found
    //! relative to that directory.  The directory is removed from the search
    //! path when reading is complete.
    static bool         read(SoInput *in, SoPath *&path);

    //! Reads all graphs and paths from the file specified by the given SoInput.  If
    //! there is only one graph in the file and its root is an
    //! SoSeparator, a pointer to the root is returned. In all other
    //! cases, this creates an SoSeparator, adds the root nodes of all
    //! graphs read as children of it, and returns a pointer to it. This
    //! returns NULL on error. This processes directory paths in the same way
    //! as the other reading routines.
    static SoSeparator  *readAll(SoInput *in);

    //! Registers the given string as a valid header for input files.
    //! The string must be 80 characters or less, and start with the
    //! comment character <tt>'#'</tt>.
    //! If the passed isBinary flag is true, any file with this header
    //! will be read as a binary file.
    //! Usually, a user-defined header represents a file format that is
    //! a superset of the Inventor file format.
    //! The ivVersion number indicates which Inventor file version
    //! this header corresponds to.
    //! The user-defined callback functions preCB and postCB are 
    //! called before and after a file with this header is read.
    //! The userData is passed to both callback functions.
    //! The method returns TRUE if the header is successfully registered.
    //! Note, nothing prevents you from registering the
    //! same string multiple times.
    static bool         registerHeader(const SbString &headerString,
                                        bool isBinary, 
                                        float ivVersion, 
                                        SoDBHeaderCB *preCB,
                                        SoDBHeaderCB *postCB,
                                        void *userData = NULL);

    //! Passes back the data registered with the given header string,
    //! including the flag specifying whether the string is for a binary
    //! file, pointers to the callback functions invoked before and
    //! after reading the file, and a pointer to the user data passed
    //! to the callback functions.
    //! If the given header string does not match any of the registered
    //! headers, and the substringOK flag is TRUE, then the method
    //! will search for a registered header that is a substring of
    //! the given string.
    //! The method returns TRUE if a matching registered header, or
    //! subheader, was found.
    static bool         getHeaderData(const SbString &string,
                                        bool &isBinary,  
                                        float &ivVersion,
                                        SoDBHeaderCB *&preCB, 
                                        SoDBHeaderCB *&postCB, 
                                        void *&userData, 
                                        bool substringOK = FALSE);                                        
    //! Returns the number of valid headers, including standard Inventor
    //! headers, and user-registered headers.
    static int          getNumHeaders();
    //! Returns the i'th header.
    static SbString     getHeaderString(int i);

    //! This returns TRUE if the given character string is one of the valid 
    //! Inventor file headers, (e.g. <tt>"#Inventor V2.0 binary"</tt>), or if
    //! the string has been registered as a valid header through the 
    //! registerHeader method.
    static bool         isValidHeader(const char *testString);

    //! The database maintains a namespace for global fields, making sure that
    //! there is at most one instance of a global field with any given name in
    //! the database. This routine is used to create new global fields.  If
    //! there is no global field with the given name, it will create a new
    //! global field with the given name and type. If there is already a
    //! global field with the given name and type, it will return it. If there
    //! is already a global field with the given name but a different type,
    //! this returns NULL.
    //! 
    //! 
    //! All global fields must be derived from SoField; typically the result
    //! of this routine is cast into the appropriate type; for example:
    //! \code
    //! SoSFInt32 *longField =
    //!     (SoSFInt32 *) SoDB::createGlobalField("Frame",
    //!                                          SoSFInt32::getClassTypeId());
    //! \endcode
    static SoField *    createGlobalField(const SbName &name,
                                          SoType type);

    //! Returns the global field with the given name, or NULL if there is
    //! none. The type of the field may be checked using the
    //! SoField::isOfType(), SoField::getClassTypeId(),
    //! and SoField::getTypeId() 
    //! methods.
    static SoField *    getGlobalField(const SbName &name);

    //! Renames the global field named \p oldName.  Renaming a global field to
    //! an empty name ("") deletes it.  If there is already a global field
    //! with the new name, that field will be deleted (the
    //! getGlobalField method
    //! can be used to guard against this).
    static void         renameGlobalField(const SbName &oldName,
                                          const SbName &newName);

    //! The database automatically creates one global field when
    //! SoDB::init()
    //! is called.  The \b realTime  global field, which is of type
    //! SoSFTime, can be connected to engines and nodes for real-time
    //! animation.  The database will automatically update the \b realTime  global
    //! field 12 times per second, using a timer sensor.  Typically, there
    //! will be a node sensor on the root of the scene graph which schedules a
    //! redraw whenever the scene graph changes; by updating the \b realTime 
    //! global field periodically, scene graphs that are connected to
    //! \b realTime  (and are therefore animating) will be redrawn.  The rate
    //! at which the database updates \b realTime  can be controlled with this
    //! routine.  Passing in a zero time will disable automatic update of
    //! \b realTime . If there are no enabled connections from the
    //! \b realTime  field to any other field, the sensor is automatically
    //! disabled.
    //! .p
    //! Note that the SoSceneManager class automatically updates
    //! realTime immediately after redrawing, which will result in as high a
    //! frame rate as possible if the scene is continuously animating.  The
    //! SoDB::setRealTimeInterval method ensures that engines that do not
    //! continuously animate (such as SoTimeCounter) will eventually be
    //! scheduled.
    static void         setRealTimeInterval(const SbTime &deltaT);
    //! Returns how often the database is updating \b realTime .
    static const SbTime &getRealTimeInterval();

    //! This sets the timeout value for sensors that are delay queue sensors
    //! (one-shot sensors, data sensors). Delay queue sensors are
    //! triggered whenever there is idle time. If a long period of time
    //! elapses without any idle time (as when there are continuous events to
    //! process), these sensors may not be triggered. Setting this timeout
    //! value ensures that if the specified length of time elapses without any
    //! idle time, the delay queue sensors will be processed anyway.
    static void         setDelaySensorTimeout(const SbTime &t);
    //! Returns the current delay queue timeout value.
    static const SbTime &getDelaySensorTimeout();

    //! In order to keep timer and idle sensors running as expected, it is
    //! necessary that an Inventor application not block waiting for input. If
    //! the Inventor application uses the Xt utility library, this can be
    //! handled automatically.  However, if the application is using its own
    //! event loop, this function is provided as a wrapper around
    //! select(2) that will handle Inventor tasks if necessary instead of
    //! blocking.
    static int          doSelect(int nfds, fd_set *readfds, fd_set *writefds,
                                 fd_set *exceptfds,
                                 struct timeval *userTimeOut);

  SoEXTENDER public:
    //! Registers a field conversion engine that can be used to
    //! convert from one type of field to another. The type id's of the
    //! two fields are passed in, as is the type id of the field
    //! converter engine (derived from SoFieldConverter).
    static void         addConverter(SoType fromField, SoType toField,
                                     SoType converterEngine);

    //! Returns the field conversion engine registered for the two
    //! given field types. If no such engine exists,
    //! SoType::badType() is returned.
    static SoType       getConverter(SoType fromField, SoType toField);

  SoINTERNAL public:
    //! Accesses sensor manager
    static SoSensorManager *    getSensorManager();

    //! Returns TRUE if database is initialized (for error checking)
    static bool         isInitialized() { return (globalDB != NULL); }

    //! This is called when some instance begins or ends a notification
    //! process. It increments or decrements a counter of notifications
    //! in progress. When the counter reaches 0, all priority 0
    //! (immediate) delay queue sensors are triggered. By doing this,
    //! all notification has a chance to finish before any evaluation
    //! (due to data sensors, primarily) takes place.
    static void         startNotify()           { notifyCount++; }
    static bool         isNotifying()           { return (notifyCount > 0); }
    static void         endNotify()
        { if (--notifyCount == 0)
              globalDB->sensorManager.processImmediateQueue(); }

    //! Enables/disables realTime sensor processing
    static void         enableRealTimeSensor(bool enable);

    //! Reads a base of any type, returning a pointer to it. Returns
    //! FALSE on error.
    static bool         read(SoInput *in, SoBase *&base);
    
  private:
    static const char   *versionString; //!< Returned by getVersion()
    static SoDB         *globalDB;      //!< Pointer to the global database
    SoSensorManager     sensorManager;  //!< Its global sensor manager    

    static int          notifyCount;    //!< How many current notifications

    static SoTimerSensor *realTimeSensor;//!< touches realTime global field 
    static void         realTimeSensorCallback();
    static SoSFRealTime *realTime;
    
    //! List of valid header strings, and their corresponding callbacks
    static SbPList      *headerList;

    //! This dictionary stores field conversion engine types. The key
    //! is created by mangling the types of the two fields to convert
    //! from. The dictionary maps the key to the type of the conversion
    //! engine.
    static SbDict       *conversionDict;

    //! Returns a conversionDict key from the two given field type id's.
    static uint32_t     getConversionKey(SoType fromField, SoType toField)
        { return (fromField.getKey() << 16) | toField.getKey(); }

    static void         iv2_1PreCallback(void *userData, SoInput *in);
    static void         iv2_0PreCallback(void *userData, SoInput *in);
    static void         iv1_0PreCallback(void *userData, SoInput *in);
    static void         iv2_0PostCallback(void *userData, SoInput *in);
    static void         iv1_0PostCallback(void *userData, SoInput *in);
    
};

#endif /* _SO_DB_ */
