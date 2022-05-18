/**************************************************************************
 *
 *                Copyright (c) 1994 David Koblas
 * Permission to use, copy, modify, and distribute this software   
 * and its documentation for any purpose and without fee is hereby 
 * granted, provided that the above copyright notice appear in all
 * copies and that both that copyright notice and this permission  
 * notice appear in supporting documentation.  This software is  
 * provided "as is" without express or implied warranty.       
 *
 **************************************************************************
 *
 * File: readGIF.h
 *
 * Description: Interface file for the GIF reader code.
 *
 **************************************************************************/


/* $Revision: 1.2 $ */


#ifndef _READGIF_H_INCLUDED
#define _READGIF_H_INCLUDED


#include <stdio.h>

/*
 * Data structure used by color operations
 */
typedef struct {
        unsigned long pixel;
        unsigned short red, green, blue;
        char flags;  /* do_red, do_green, do_blue */
        char pad;
} GIF_Color;


/* Public GIF information */

#define GIF_MAXCOLORMAPSIZE     256

/* Error codes */

#define GIF_NO_ERROR            0
#define GIF_BAD_HEADER          -1
#define GIF_BAD_MAGIC           -2
#define GIF_BAD_VERSION         -3
#define GIF_BAD_SCRNDESC        -4
#define GIF_BAD_GCOLORMAP       -5
#define GIF_SHORT_IMAGE         -6
#define GIF_NO_IMAGE            -7
#define GIF_SHORT_EXT           -8
#define GIF_BAD_CHARACTER       -9
#define GIF_SHORT_DIMS          -10
#define GIF_BAD_LCOLORMAP       -11


/* Public functions */

#ifdef __cplusplus
extern "C" {
#endif
extern unsigned char* readGIF(FILE *fd, int *w, int *h, GIF_Color *colors,
                                int *ncolors, int *bgIndex, int *errCode);
#ifdef __cplusplus
}
#endif


#endif  /* _READGIF_H_INCLUDED */
