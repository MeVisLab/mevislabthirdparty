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
 |   $Revision: 1.4 $
 |
 |   Classes:
 |      SoTexture2
 |
 |   Author(s)          : Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/elements/SoGLCacheContextElement.h>
#include <Inventor/elements/SoGLTextureEnabledElement.h>
#include <Inventor/elements/SoGLTextureImageElement.h>
#include <Inventor/elements/SoTextureQualityElement.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/errors/SoReadError.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/sensors/SoFieldSensor.h>

#include <stdio.h>
#include <stdlib.h>
#include "readJPEG.h"

SO_NODE_SOURCE(SoTexture2);

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Constructor
//
// Use: public

SoTexture2::SoTexture2()
//
////////////////////////////////////////////////////////////////////////
{
    SO_NODE_CONSTRUCTOR(SoTexture2);

    SO_NODE_ADD_FIELD(filename, (""));
    SO_NODE_ADD_FIELD(image, (SbVec2s(0, 0), 0, 0));
    SO_NODE_ADD_FIELD(wrapS, (REPEAT));
    SO_NODE_ADD_FIELD(wrapT, (REPEAT));
    SO_NODE_ADD_FIELD(model, (MODULATE));
    SO_NODE_ADD_FIELD(blendColor, (SbColor(0,0,0)));

    // Set up enumerations for texture model
    SO_NODE_DEFINE_ENUM_VALUE(Model, MODULATE);
    SO_NODE_DEFINE_ENUM_VALUE(Model, DECAL);
    SO_NODE_DEFINE_ENUM_VALUE(Model, BLEND);

    SO_NODE_DEFINE_ENUM_VALUE(Wrap, REPEAT);
    SO_NODE_DEFINE_ENUM_VALUE(Wrap, CLAMP);
    
    // Set up info in enumerated type field
    SO_NODE_SET_SF_ENUM_TYPE(model, Model);
    SO_NODE_SET_SF_ENUM_TYPE(wrapS, Wrap);
    SO_NODE_SET_SF_ENUM_TYPE(wrapT, Wrap);

    // Set up sensors to keep the image/filename fields agreeing.
    // Sensors are used instead of field to field connections or raw
    // notification so that the fields can still be attached to/from
    // other fields.
    imageSensor = new SoFieldSensor(imageChangedCB, this);
    imageSensor->setPriority(0);
    imageSensor->attach(&image);
    filenameSensor = new SoFieldSensor(filenameChangedCB, this);
    filenameSensor->setPriority(0);
    filenameSensor->attach(&filename);

    renderList = NULL;  // Display list used for rendering

    isBuiltIn = TRUE;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Destructor
//
// Use: private

SoTexture2::~SoTexture2()
//
////////////////////////////////////////////////////////////////////////
{
    if (renderList) {
        renderList->unref();
        renderList = NULL;
    }
    delete imageSensor;
    delete filenameSensor;
}


////////////////////////////////////////////////////////////////////////
//
// Description:
//    Reads into instance of SoTexture2. Returns FALSE on error.
//
// Use: protected

bool
SoTexture2::readInstance(SoInput *in, unsigned short flags)
//
////////////////////////////////////////////////////////////////////////
{
    // Detach filename sensor temporarily
    filenameSensor->detach();

    // Read field info as usual.
    bool readOK = SoNode::readInstance(in, flags);

    if (readOK && !filename.isDefault()) {
        // See the comment in SoFile::readInstance for why we do this
        // and don't just let the FieldSensor take care of reading in
        // the image.
        setReadStatus(readOK);
        (*(filenameSensor->getFunction()))(filenameSensor->getData(), NULL);

        // Don't set readOK, because not being able to read the image
        // isn't a fatal error.  But do issue a read error:
        if (getReadStatus() == FALSE)
            SoReadError::post(in, "Could not read texture file %s",
                              filename.getValue().getString());
    }

    // Reattach sensor
    filenameSensor->attach(&filename);

    return readOK;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Callback that sets the filename to "" whenever the image field
//    is changed.
//
// Use: static, internal

void
SoTexture2::imageChangedCB(void *data, SoSensor *)
//
////////////////////////////////////////////////////////////////////////
{
    SoTexture2 *tex = (SoTexture2 *)data;

    if (tex->image.isIgnored()) return;

    tex->filenameSensor->detach();
    tex->filename.setValue("");
    tex->filename.setDefault(TRUE);
    tex->filenameSensor->attach(&tex->filename);

    if (tex->renderList) {
        tex->renderList->unref();
        tex->renderList = NULL;
    }
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Callback that reads in the given file and stuffs it into the
//    image field whenever the filename field changes.
//
// Use: static, internal

void
SoTexture2::filenameChangedCB(void *data, SoSensor *)
//
////////////////////////////////////////////////////////////////////////
{
    SoTexture2 *tex = (SoTexture2 *)data;

    if (tex->filename.isIgnored()) {
        tex->setReadStatus(FALSE);
        return;
    }

    // Read in image file right away...
    int nx, ny, nc;
    unsigned char *bytes;
    bool result = readImage(tex->filename.getValue(), nx, ny, nc, bytes);
    if (!result) {
        // Read error is taken care of by readImage() call
        nx = ny = nc = 0;
        bytes = NULL;
    }
    // Detach the image sensor temporarily...
    tex->imageSensor->detach();

    // Set the image to the right value:
    tex->image.setValue(SbVec2s(nx, ny), nc, bytes);

    // And set its default bit so it isn't written out
    tex->image.setDefault(TRUE);

    if (bytes != NULL) delete [] bytes;

    if (tex->renderList) {
        tex->renderList->unref();
        tex->renderList = NULL;
    }
    tex->imageSensor->attach(&tex->image);

    tex->setReadStatus(result);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Performs typical action
//
// Use: extender

void
SoTexture2::doAction(SoAction *action)
//
////////////////////////////////////////////////////////////////////////
{
    SoState *   state = action->getState();

    if (image.isIgnored() ||
        SoTextureOverrideElement::getImageOverride(state))
        return; // Texture being overriden or this node ignored
    if (isOverride()) {
        SoTextureOverrideElement::setImageOverride(state, TRUE);
    }

    SbVec2s size;
    int nc;
    const unsigned char *bytes = image.getValue(size, nc);
    
    SoTextureImageElement::set(state, this, size, nc, bytes,
                               wrapS.getValue(), wrapT.getValue(),
                               model.getValue(), blendColor.getValue());
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Performs callback action
//
// Use: extender

void
SoTexture2::callback(SoCallbackAction *action)
//
////////////////////////////////////////////////////////////////////////
{
    SoTexture2::doAction(action);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Performs GL rendering on a texture node.
//
// Use: extender

void
SoTexture2::GLRender(SoGLRenderAction *action)
//
////////////////////////////////////////////////////////////////////////
{
    SoState *   state = action->getState();

    if (image.isIgnored() ||
        SoTextureOverrideElement::getImageOverride(state))
        return; // Texture being overriden or this node ignored
    if (isOverride()) {
        SoTextureOverrideElement::setImageOverride(state, TRUE);
    }

    SbVec2s size;
    int nc;
    const unsigned char *bytes = image.getValue(size, nc);
    int numBytes = size[0]*size[1]*nc;

    float texQuality = SoTextureQualityElement::get(state);
    if (texQuality == 0 || numBytes == 0 || image.isIgnored()) {
        SoGLTextureEnabledElement::set(state, FALSE);
        return;
    }
    else {
        SoGLTextureEnabledElement::set(state, TRUE);
    }   

    // Check for special cases of 1/2 component texture and model
    // DECAL or 3/4 component texture and model BLEND; print out
    // errors in these cases:
        
    int m = model.getValue();
    if (nc < 3 && m == DECAL) {
#ifdef DEBUG
        SoDebugError::post("SoTexture2::GLRender",
                           "Texture model is DECAL, but texture image"
                           " has only %d components (must be 3 or 4).  "
                           "Use imgcopy to convert the image.", nc);
#endif      
        SoGLTextureEnabledElement::set(state, FALSE);
    }
    else if (nc > 2 && m == BLEND) {
#ifdef DEBUG
        SoDebugError::post("SoTexture2::GLRender",
                           "Texture model is BLEND, but texture image"
                           " has %d components (must be 1 or 2).  "
                           "Use imgcopy to convert the image.", nc);
#endif      
        SoGLTextureEnabledElement::set(state, FALSE);
    } else {
        // This is kind of weird-- the element builds and uses the
        // display list (which is why we pass it in and assign
        // it) because it sends the GL calls, and needs to know
        // the list if the state is popped.  But this node must
        // manage storage and deletion of the display list, since
        // the list must go away if the node is deleted or the
        // image is changed.

        // See if renderList is valid (in the right context, with
        // the right texture quality):
        int context = SoGLCacheContextElement::get(state);
        if (renderList && renderList->getContext() == context &&
            texQuality == renderListQuality) {
            SoGLTextureImageElement::set(
                state, this, size, nc, bytes, texQuality,
                wrapS.getValue(), wrapT.getValue(),
                m, blendColor.getValue(), renderList);
        }  // Not valid, try to build
        else {
            // Free up old list, if necessary:
            if (renderList) {
                renderList->unref(state);
                renderList = NULL;
            }
            renderList = SoGLTextureImageElement::set(
                state, this, size, nc, bytes, texQuality,
                wrapS.getValue(), wrapT.getValue(),
                m, blendColor.getValue(), NULL);
            if (renderList)
                renderList->ref();
            renderListQuality = texQuality;
        }
    }
}

extern "C" {
#include "readGIF.h"
}

bool ReadGIFImage(const SoInput& in, int &w, int &h, int &nc,  
                                                unsigned char *&bytes) {

    int ncolors;
    int bgIndex;
    int errCode;
    GIF_Color *colors = (GIF_Color*) malloc(GIF_MAXCOLORMAPSIZE * sizeof(GIF_Color));
    FILE *fp = in.getCurFile();
    fseek(fp, 0, SEEK_SET);
    
    if (fp == NULL) return FALSE;
    
    unsigned char *array = readGIF(fp, 
                            &w, &h, colors, &ncolors, &bgIndex, &errCode);
    if (errCode != GIF_NO_ERROR) { 
        free(colors);
        return FALSE;
    }
    
    nc = 3;
    
    // convert color map image to rgb
    // gif files go top down and we need bottom up.  Switch it.
    bytes = new unsigned char[w*h*nc];
    
    int i, j;
    
    for (j = 0; j < h; ++j)
        for (i = 0; i < w; ++i) {
            int c = array[j*w+i];
            int index = ((h-j-1)*w+i)*nc;
            
            if (c < 0 || c >= ncolors)
                // store black if out of range
                bytes[index] = bytes[index+1] = bytes[index+2] = 0;
            else { 
                bytes[index] = colors[c].red / 256;
                bytes[index+1] = colors[c].green / 256;
                bytes[index+2] = colors[c].blue / 256;
            }
        }
        
    free(colors);
    free(array);
    
    return TRUE;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    read passed image file
//
// Use: static, protected

bool
SoTexture2::readImage(const SbString& fname, int &w, int &h, int &nc, 
                      unsigned char *&bytes)
//
////////////////////////////////////////////////////////////////////////
{
    w = h = nc = 0;
    bytes = NULL;
    
    // Empty file means an empty image...
    if (fname.getString()[0] == '\0')
        return TRUE;

    SoInput in;
    if (!in.openFile(fname.getString(), TRUE)) {
        return FALSE;
    }

#ifdef DEBUG
    SoDebugError::postInfo("SoTexture2::readImage",
                           "Reading texture image %s",
                           fname.getString());
#endif

/* Florian Link: Disabled RGB image loading, because the libimage uses close
   on the fileno of the fopen stream, which crashes in fclose of SoInput

    if (ReadSGIImage(in, w, h, nc, bytes))
        return TRUE;

    // fiopen() closes the file even if it can't read the data, so 
    // reopen it
    in.closeFile();
    if (!in.openFile(fname.getString(), TRUE))
        return FALSE;
*/
    if (ReadGIFImage(in, w, h, nc, bytes))
        return TRUE;

    if (ReadJPEGImage(in.getCurFile(), w, h, nc, bytes))
        return TRUE;

    return FALSE;
}
