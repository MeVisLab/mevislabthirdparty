// **InsertLicense** code

//   Description:
//   Macro file to implement exception handlers around some code to make
//   code safe. In the case of caught exception an error message is composed
//   and send to SoError.
//   The usage of the exception handler is optional and can be enabled/disabled
//   by the static class function SoCatch::enableExceptionHandling().
 
#include <Inventor/SoCatch.h>
#include <Inventor/SoTrace.h>


bool SoCatch::_isExceptionHandlingEnabled=false;


bool
SoCatch::isExceptionHandlingEnabled()
{
   return _isExceptionHandlingEnabled;
}

void
SoCatch::enableExceptionHandling(bool on)
{
   _isExceptionHandlingEnabled = on;
}

void
SoCatch::initClass()
{
   _isExceptionHandlingEnabled = false;
}

void
SoCatch::postExceptionMessage(SoType      ERR_OBJ_TYPE_ID,
                              const char *OP_DESCR_STR,
                              SoType      ACTION_TYPE_ID,
                              const char *END_STR)
{
   SbString objName = "<unknown object>";
   try {
      if(ERR_OBJ_TYPE_ID != SoType::badType()) {
         objName = ERR_OBJ_TYPE_ID.getName().getString();
      }
   }
   catch(...) {
      objName="<error getting objTypeName>";
   }

   SbString opString = "";
   try {
      if(OP_DESCR_STR) {
         opString = OP_DESCR_STR;
      }
   }
   catch(...) {
      opString = "<error getting description>";
   }

   SbString actionName = "";
   try {
      if(ACTION_TYPE_ID != SoType::badType()) {
         actionName = ACTION_TYPE_ID.getName().getString();
      }
   }
   catch(...) {
      actionName="<error getting action type name>";
   }

   SbString endString = "";
   try {
      if(END_STR) {
         endString = END_STR;
      }
   }
   catch(...) {
      endString = "<error getting endStr name>";
   }

   SbString traceInfos ="";
   try {
      traceInfos = SoGlobalTraceBuffer.getTraceDumpString();
   }
   catch(...) {
      traceInfos="<error getting traceInfos name>";
   }

   try {
      SoError::post("Crash in %s while %s %s %s %s",
                    objName   .getString(),
                    opString  .getString(),
                    actionName.getString(),
                    endString .getString(),
                    traceInfos.getString());
   }
   catch(...) {
      SoError::post("<Could not create error message after catching error>");
   }
}
