// **InsertLicense** code

//   Description:
//   This file contains a class to manage a buffer for a stack and a list
//   of string pointers for tracing debug and release code.


#include <string.h>
#include <Inventor/SoTrace.h>


SoTraceBuffer<SoGlobalTraceBufferType> SoGlobalTraceBuffer;


#if defined(__sgi)

// The #pragma instantiate directive causes a specific instance of a template declaration to be immediately instantiated.
#pragma instantiate SbString SoTraceBuffer<SoGlobalTraceBufferType>::getTraceDumpString() const

#else

// Dummy function not to be called. It is only used to force
// the instantiation of template functionality implemented in .cpp.
void
_dummyFunction_DO_NOT_CALL()
{
  SoGlobalTraceBuffer.getTraceDumpString();
}

#endif
