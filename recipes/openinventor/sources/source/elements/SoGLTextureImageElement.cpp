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
 |   $Revision: 1.3 $
 |
 |   Classes:
 |      SoGLTextureImageElement
 |
 |   Author(s)          : Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#include <Inventor/elements/SoCacheElement.h>
#include <Inventor/elements/SoGLCacheContextElement.h>
#include <Inventor/elements/SoGLTextureImageElement.h>
#include <Inventor/elements/SoGLTextureEnabledElement.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/system/SbOpenGLU.h>
#include <Inventor/system/SbOpenGL.h>

#include <float.h>
#include <stdlib.h>

// Formats for 1-4 component textures
static GLenum formats[] = {
    GL_LUMINANCE,
    GL_LUMINANCE_ALPHA,
    GL_RGB,
    GL_RGBA
};

SO_ELEMENT_SOURCE(SoGLTextureImageElement);

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Destructor.
//
// Use: private

SoGLTextureImageElement::~SoGLTextureImageElement()
//
////////////////////////////////////////////////////////////////////////
{
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Initializes element.
//
// Use: public

void
SoGLTextureImageElement::init(SoState *state)
//
////////////////////////////////////////////////////////////////////////
{
    // Initialize base class stuff
    SoTextureImageElement::init(state);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Pops element, causing side effects in GL.
//
// Use: public

void
SoGLTextureImageElement::pop(SoState *state, const SoElement *)
//
////////////////////////////////////////////////////////////////////////
{
    // Empty texture, don't need to do anything-- the
    // GLTextureEnabledElement will turn off texturing.
    if (size[0] == 0 || size[1] == 0 || numComponents == 0) {
        return;
    }
    // Since popping this element has GL side effects, make sure any
    // open caches capture it
    capture(state);

    // Restore previous texture image (if any)
    sendTexEnv(state);
    sendTex(state);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets image.
//
// Use: protected, virtual

void
SoGLTextureImageElement::setElt(const SbVec2s &, int, const
                                unsigned char *, int, int, int,
                                const SbColor &)
//
////////////////////////////////////////////////////////////////////////
{
#ifdef DEBUG
    SoDebugError::post("SoGLTextureImageElement::setElt",
               "Nodes must call SoGLTextureImageElement::set"
               " for GLRender, not SoTextureImageElement::set");
#endif
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Does the right GL stuff.  This takes a GL display list that can
//    be used to render the texture; if -1 is passed in as the display
//    list, this will try to build a display list (if there are none
//    already open) and returns the display list, which must be freed
//    by the node that sets this element.
//
// Use: public, static

SoGLDisplayList *
SoGLTextureImageElement::set(SoState *state, SoNode *node,
                             const SbVec2s &_size, int _numComponents,
                             const unsigned char *_bytes,
                             float _quality, int _wrapS, int _wrapT,
                             int _model, const SbColor &_blendColor,
                             SoGLDisplayList *_list)
//
////////////////////////////////////////////////////////////////////////
{
    SoGLTextureImageElement     *elt;

    // Get an instance we can change (pushing if necessary)
    elt = (SoGLTextureImageElement *) getElement(state, classStackIndex, node);

    if (elt != NULL) {
        elt->SoTextureImageElement::setElt(_size, _numComponents,
                                           _bytes, _wrapS, _wrapT,
                                           _model, _blendColor);

        elt->list = _list;
        elt->quality = _quality;
        elt->sendTexEnv(state);
        elt->sendTex(state);
        return elt->list;
    }
    return NULL;
}

// Helper table; for integers 1-15, returns the high-bit (0-3):
static signed char powTable[0x10] = {
    -1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3 };

//
// Helper routine; given an integer, return next higher power of 2.
// This is convoluted, but pretty fast (about 1.6 times faster than
// a naive bit-shifting algorithm).
//
  static inline int nextPowerOf2(int num)
{
#ifdef DEBUG
    if (num <= 0) {
        SoDebugError::post("SoGLTextureImageElement::nextPowerOf2",
                           "size <= 0");
        return 0;
    }
#endif
    int t, bits = 0;
    int mask = 0xF;
    // Find closest to 4-bits:
    for (t = num-1; (t & (~mask)) != 0; bits += 4, t = t>>4) ;

    // Find high-bit:
    bits += powTable[t];
    return bits + 1;
}

//
// Helper routine stolen from the gluBuild2DMipMaps code:
//
// Compute the nearest power of 2 number.  This algorithm is a little 
// strange, but it works quite well.
//
  static int nearestPowerOf2(GLuint value)
{
    int i = 0;

#ifdef DEBUG
    if (value <= 0) {
        SoDebugError::post("SoGLTextureImageElement::nextPowerOf2",
                           "size <= 0");
        return 0;
    }
#endif

    for (;;) {
        if (value == 1) {
            return i;
        } else if (value == 3) {
            return i+2;
        }
        value = value >> 1;
        i++;
    }
}

//
// Helper table; mapping from textureQuality to OpenGL filter type:
//
struct qualityFilterTable {
    float quality;
    GLint filter;
    bool needMipMaps;
};

//
// Filter modes depending on quality settings:
//
static qualityFilterTable mipmap_minQFTable[] = {
    { 0.1f, GL_NEAREST, FALSE},
    { 0.5f, GL_LINEAR, FALSE},
    { 0.7f, GL_NEAREST_MIPMAP_NEAREST, TRUE},
    { 0.8f, GL_NEAREST_MIPMAP_LINEAR, TRUE},
    { 0.9f, GL_LINEAR_MIPMAP_NEAREST, TRUE},
    { FLT_MAX, GL_LINEAR_MIPMAP_LINEAR, TRUE},
};


////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sends texture environment.  This is separated from send()
//    because texture objects do NOT store the texture environment
//    state.
//
// Use: private

void
SoGLTextureImageElement::sendTexEnv(SoState *)
//
////////////////////////////////////////////////////////////////////////
{
    // This state isn't stored in a texture object:
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, model);
    if (model == GL_BLEND) {
        glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR,
                   blendColor.getValue());
    }
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sends down a 2D texture.  Builds or uses a display list, if it
//    can.
//
// Use: private

void
SoGLTextureImageElement::sendTex(SoState *state)
//
////////////////////////////////////////////////////////////////////////
{
    static bool useNonPowTwoTextures = (getenv("IV_NO_NPOT")==NULL) && 
                                       (GLEW_VERSION_2_0 || GLEW_ARB_texture_non_power_of_two) &&
                                       // only allow non-pow-two when glGenerateMipmap is available:
                                       (GLEW_VERSION_3_0 || GLEW_ARB_framebuffer_object);

    if (list) {
        // use display list
        list->call(state);
        return;
    }

    // Scale the image to closest power of 2 smaller than maximum
    // texture size:
    GLint maxsize = 0;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxsize);
    SbVec2s newSize;
    if (useNonPowTwoTextures) {
      // make sure to only use GL_MAX_TEXTURE_SIZE
      for (int i = 0; i < 2; i++) {
        if (size[i] > maxsize) {
          newSize[i] = maxsize;
        } else {
          newSize[i] = size[i];
        }
      }
    } else {
      // Use nearest power of 2 for big textures, use next higher
      // power of 2 for small textures:
      for (int i = 0; i < 2; i++) {
        if (size[i] > 8) {
          newSize[i] = size[i] > maxsize ?
                                 maxsize : 1 << nearestPowerOf2(size[i]);
        } else {
          newSize[i] = 1 << nextPowerOf2(size[i]);
        }
      }
    }


    int minFilter, magFilter;
    bool needMipMaps = FALSE;
    qualityFilterTable *tbl = mipmap_minQFTable;

    int i;
    for (i = 0; quality > tbl[i].quality; i++) /* Do nothing */;
    minFilter = tbl[i].filter;
    needMipMaps = tbl[i].needMipMaps;
    magFilter = (quality < 0.5 ? GL_NEAREST : GL_LINEAR);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // Not default
    
    // Format in memory
    int format = formats[numComponents-1];
    int internalFormat = formats[numComponents-1];
    
    bool buildList = !SoCacheElement::anyOpen(state);
    if (buildList) {
        list = new SoGLDisplayList(state,
                                   SoGLDisplayList::TEXTURE_OBJECT);
        list->open(state);
    }

    // If we aren't creating a texture object, then we need to 
    // unbind the current texture object so we don't overwrite it's state.
    if (!buildList) {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    // These need to go inside the display list or texture object
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    
    GLubyte *level0 = NULL;
    // scale the image if the new size is different from the original size:
    if (newSize != size) {
        level0 = (GLubyte *)
            malloc(newSize[0]*newSize[1]*numComponents*sizeof(GLubyte));

        // Use gluScaleImage (which does linear interpolation or box
        // filtering) if using a linear interpolation magnification
        // filter:
        gluScaleImage(
            (GLenum)format, size[0], size[1], GL_UNSIGNED_BYTE, bytes,
            newSize[0], newSize[1], GL_UNSIGNED_BYTE, level0);
    }
    
    // Send level-0 mipmap:
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, newSize[0], newSize[1],
                 0, (GLenum)format, GL_UNSIGNED_BYTE,
                 level0 == NULL ? bytes : level0);
    
    // If necessary, send other mipmaps:
    if (needMipMaps) {
      if (useNonPowTwoTextures) {
        // use the GL driver to generate the mip maps,
        // this supports non-power-of-two as well:
        glGenerateMipmap(GL_TEXTURE_2D);
      } else {
        // create mip maps manually, this code can only handle
        // power-of-two images:
        const GLubyte *prevLevel = NULL;
        if (level0 == NULL) {
          level0 = (GLubyte *)
            malloc(newSize[0]*newSize[1]*numComponents*sizeof(GLubyte));
          prevLevel = bytes;
        } else {
          prevLevel = level0;
        }

        int level = 0;
        SbVec2s curSize = newSize;
        while (curSize[0] > 1 || curSize[1] > 1) {
          ++level;
          SbVec2s prevSize = curSize;

          // When we're box-filtering, we average the 4 pixels
          // [(curSize),(curSize+deltas)].  If mipmaps have already
          // bottomed out for a dimension, the delta will be 0,
          // otherwise the delta will be 1.
          SbVec2s deltas;
          if (curSize[0] > 1) {
            curSize[0] = curSize[0] >> 1;
            deltas[0] = 1;
          } else {
            deltas[0] = 0;
          }
          if (curSize[1] > 1) {
            curSize[1] = curSize[1] >> 1;
            deltas[1] = 1;
          } else {
            deltas[1] = 0;
          }

          int byte = 0;
          for (int h = 0; h < prevSize[1]; h += (deltas[1]+1)) {
            for (int w = 0; w < prevSize[0]; w += (deltas[0]+1)) {
              for (int b = 0; b < numComponents; b++) {

                // Helper macro for indexing:
#define I(w,h,b) (b + (w + (h)*prevSize[0])*numComponents)

                level0[byte] =
                  (prevLevel[I(w,h,b)] +
                  prevLevel[I(w,h+deltas[1],b)] +
                  prevLevel[I(w+deltas[0],h,b)] +
                  prevLevel[I(w+deltas[0],h+deltas[1],b)]) / 4;
#undef I
                byte++;
              }
            }
          }
          // Send level-N mipmap:
          glTexImage2D(GL_TEXTURE_2D, level, internalFormat,
            curSize[0], curSize[1],
            0, (GLenum)format, GL_UNSIGNED_BYTE, level0);
          prevLevel = level0;
        }
      }
    }

    if (buildList) {
        list->close(state);
    }

    if (level0) {
      free(level0);
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);  // Reset to default
}
