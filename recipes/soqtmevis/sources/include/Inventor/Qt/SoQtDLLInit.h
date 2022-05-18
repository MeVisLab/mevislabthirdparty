#ifndef SOQT_DLL_INIT
#define SOQT_DLL_INIT

// special include for the MeVis version of Open Inventor, to resolve some
// include order problems:
#include <Inventor/system/SbOpenGL.h>

#if defined(WIN32)
    #ifdef SOQT_MEVIS_EXPORTS
      #define SOQT_MEVIS_EXPORT __declspec(dllexport)
    #else
      #define SOQT_MEVIS_EXPORT __declspec(dllimport)
    #endif
#else
    #ifdef SOQT_MEVIS_EXPORTS
      #define SOQT_MEVIS_EXPORT __attribute__((__visibility__("default")))
    #else
      #define SOQT_MEVIS_EXPORT
    #endif
#endif


#endif
