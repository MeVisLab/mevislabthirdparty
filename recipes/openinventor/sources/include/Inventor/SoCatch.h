// **InsertLicense** code

#ifndef  _SO_CATCH_
#define  _SO_CATCH_

#include <Inventor/system/SbSystem.h>
#include <Inventor/misc/SoBasic.h>
#include <Inventor/SbString.h>
#include <Inventor/errors/SoError.h>

///////////////////////////////////////////////////////////////////////////////
///
///  Class containing static functions to control global
///  exception handling for OpenInventor.
///
//////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoCatch
{
   public:

      //! Function to query exception handling for all
      //! SO_CATCH* macros.
      static bool isExceptionHandlingEnabled();

      //! Function to enabled/disable exception handling for all
      //! SO_CATCH* macros when passing TRUE/FALSE.
      static void enableExceptionHandling(bool on);

      //! Initializes the SoCatch class.
      static void initClass();

      //! Posts composed error message. Used in catch branches on
      //! caught exceptions. All accesses on construction parts of
      //! message fragments are done as save as possible so that
      //! even crashes in type name accesses hopefully do not lead
      //! to further crashes but in a controlled error message.
      //!
      //! ERR_OBJ_TYPE_ID may be SoType::badType() which will be handled as
      //! no type (ignored). On all other type ids the id name will be used
      //! as string parameter for the error report. It typically should
      //! be the type id of the object which probably caused the crash.
      //!
      //! OP_DESCR_STR may be "" or another string describing
      //! the operation which were applied while the error occured, for
      //! example "delete" when the code between try / catch is for example
      //! "delete ERR_OBJ_PTR;".
      //!
      //! ACTION_TYPE_ID may be SoType::badType() which will be handled as
      //! no type (ignored). On all other type ids the name will be used
      //! as string parameter for error report. It should typically be
      //! the class type id of the class which was using the error
      //! causing object (for example an action traversing using a node).
      //!
      //! END_STR may be "" or any other terminating string to finish
      //! the error message.
      //!   "Crash in
      //!    <ERR_OBJ_TYPE_ID.getName()>
      //!    while
      //!    <OP_DESCR_STR>
      //!    <ACTION_TYPE_ID.getName()>
      //!    <END_STR>"
      static void postExceptionMessage(SoType      ERR_OBJ_TYPE_ID,
                                       const char *OP_DESCR_STR,
                                       SoType      ACTION_TYPE_ID,
                                       const char *END_STR);

   private:

      //! State member variable describing whether exceptions shall be catched
      //! or not.
      static bool _isExceptionHandlingEnabled;

};

#if !defined(DISABLE_ERRORTRACING)

//! See documentation of SO_CATCH_END.
#define SO_CATCH_START \
    if (!SoCatch::isExceptionHandlingEnabled()) {


//! See documentation of SO_CATCH_END.
//! CODE_BEFORE_TRY can be some initialization code or ";" done only in
//! case of enabled exception handling directly before calling
//! try; so some variables can be initialized from objects before
//! these object are changed due to the execution which could cause
//! the exception. For example a type could be read from an object
//! before it's deleted. The type then can be used in SO_CATCH_END.
//! See also SO_CATCH_END examples.
#define SO_CATCH_ELSE(CODE_BEFORE_TRY) \
    }                                  \
    else {                             \
      CODE_BEFORE_TRY                  \
      try {


//! Third macro used after SO_CATCH_START, SO_CATCH_ELSE and SO_CATCH_END.
//! Usage:
//! 1   SO_CATCH_START
//! 2     <user_code>
//! 3   SO_CATCH_ELSE(;)
//! 4     <user_code>
//! 5   SO_CATCH_END(ERR_OBJ_PTR, OP_DESCR_STR, ACTION_PTR, END_STR).
//!
//! It is strongly recommended that <user code> in line 2 and 4
//! is identical since only one of both will be executed dependent
//! on whether exception handling is enabled or not.
//!
//! Some code can be passed to SO_CATCH_ELSE in the case that
//! the stuff passed to SO_CATCH_ELSE requires some parameters
//! which need to be initialized outside the try body. If no code
//! needs to be passed a ; can be used instead.
//!
//! For a parameter description of this macro see
//! SoCatch::postExceptionMessage();
//!
//! Examples:
//! myNodePtr is a pointer to a node of class SoMyNode.
//! rednerActionPtr is a pointer to a SoGLRenderAction.
//!
//!  SO_CATCH_START
//!
//!    userCode
//!
//!  SO_CATCH_ELSE(;)
//!
//!    userCode
//!
//!  SO_CATCH_END(myNodePtr->getTypeId(), "applying",
//!               renderActionPtr->getTypeId(), "to it.")
//!
//! would result in
//!
//! "Crash in SoMyNode while applying SoGLRenderAction to it."
//!
//!
//! or
//!
//!
//! this is deleted and could cause an exception.
//!
//!  SO_CATCH_START
//!
//!    delete this;
//!
//!  SO_CATCH_ELSE(SoType myType=getTypeId();)
//!
//!    delete this;
//!
//!  SO_CATCH_END(myType, "deleting", SoType::badType(), "it.")
//!
//! would result in
//!
//! "Crash in SoMyType while deleting it."
//!
//! In both cases eventually a list of most recently called and
//! traced functions and/or the call stack of traced functions is
//! printed as specified in the settings of the SoGlobalTraceBuffer
//! instance.
#define SO_CATCH_END(ERR_OBJ_TYPE_ID, OP_DESCR_STR, ACTION_TYPE_ID, END_STR)    \
      }                                                       \
      catch(...) {                                            \
        /* Bad case, we caught a crash. Compose            */ \
        /* the error string and post it to SoError.        */ \
        try {                                                 \
          /* Do extra save message posting since we must   */ \
          /* assume that passed parameters (which could    */ \
          /* be expressions) also could be corrupt.        */ \
          SoCatch::postExceptionMessage(ERR_OBJ_TYPE_ID,      \
                                        OP_DESCR_STR,         \
                                        ACTION_TYPE_ID,       \
                                        END_STR);             \
        }                                                     \
        catch(...) {                                          \
          SoError::post("<Could not create error message "    \
                        "after catching fatal error>");       \
        }                                                     \
      } /* catch(...) */                                      \
    } /* else of SO_CATCH_ELSE */

#else  // DISABLE_ERRORTRACING

#define SO_CATCH_START \
    if(1) {
#define SO_CATCH_ELSE(CODE_BEFORE_TRY) \
    }                                  \
    else {
#define SO_CATCH_END(ERR_OBJ_TYPE_ID, OP_DESCR_STR, ACTION_TYPE_ID, END_STR) \
    }

#endif  // DISABLE_ERRORTRACING

#endif  // _SO_CATCH_
