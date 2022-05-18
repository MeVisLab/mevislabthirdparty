//! The JPEG loader has been moved to readJPEG.h/.cpp because OpenInventor
//! includes "windows.h" in SbSystem and that defines a "boolean" type, which
//! is incompatible with the JPEG "boolean" type. Thus the JPEG code needed
//! to be in an extra source file that has no dependencies on OpenInventor at all.

#include <stdio.h>
#include <stdlib.h>

//! read the JPEG image from given file, returns TRUE on success
int ReadJPEGImage(FILE* infile, int &w, int &h, int &nc, unsigned char *&bytes);