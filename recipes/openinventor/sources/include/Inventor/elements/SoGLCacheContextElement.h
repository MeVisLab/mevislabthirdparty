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
 |      This file defines the SoGLCacheContextElement class.
 |
 |   Author(s)          : Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_CACHE_CONTEXT_ELEMENT
#define  _SO_CACHE_CONTEXT_ELEMENT

#include <Inventor/system/SbOpenGL.h>
#include <Inventor/elements/SoSubElement.h>

//! the default maximum value for OpenInventor auto caching (it used to be 1000 in
//! the original SGI sources, but that is too low for todays GPUs!)
#define OIV_AUTO_CACHE_DEFAULT_MAX 100000

///////////////////////////////////////////////////////////////////////////////
///
///  \class SoCacheContextElement
///  \ingroup Elements
///
///  Element that stores the cache context.  There is a method on the
///  render action to set this; if you are not rendering onto multiple
///  displays, you will not need to set this (assuming that caches are
///  shareable between different windows on the same display, which is
///  true of GLX).
///
///  This element should be set before traversal starts, and must not
///  be changed during traversal (you'll get a debug error if a node
///  tries to set the cache context during traversal).
///
//////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
///
///  Class SoGLDisplayList:
///
///  A helper class used to store OpenGL display-list-like objects.
///  Currently, it can store either texture objects (which must be
///  treated like display lists; texture objects bound inside a display
///  list must be reference counted, etc) and display lists.
///
////////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SoGLDisplayList {

  public:
    //!
    //! Constructor.  Takes state, type, and number of lists to
    //! allocate.  Calls either glGenLists() or glGenTextures() to
    //! create empty objects/display lists. 
    //!
    enum Type {
        DISPLAY_LIST,
        TEXTURE_OBJECT,
        VERTEX_BUFFER_OBJECT //!< create a Vertex Buffer Object (MeVis ONLY)
        };
    SoGLDisplayList(SoState *state, Type type, int numToAllocate=1);

    //!
    //! Because display lists may contain textures objects or other
    //! display lists, they must be reference counted.
    //! You can pass a NULL state to unref(); deletion of the display
    //! list or texture object will then be delayed until a render
    //! action is applied in the correct context.
    void ref();
    void unref(SoState *state = NULL);

    //!
    //! Open/close a display list.  Display lists are done in
    //! COMPILE_AND_EXECUTE mode, so you don't need to call() the
    //! display list after close().
    //! Opening a texture object binds it; closing it does nothing.
    void open(SoState *state, int index = 0);
    void close(SoState *state);

    //!
    //! Call a display list, or bind a texture object.  This
    //! automatically sets up a dependency if there is another display
    //! list open in the state.
    //! You can also use the get() methods below and make the OpenGL
    //! calls yourself, in which case you should call the
    //! addDependency() method to do the correct reference counting...
    void call(SoState *state, int index = 0);
    void addDependency(SoState *state);

    //!
    //! Get methods
    //!
    Type getType() { return type; }
    int getNumAllocated() { return num; }
    GLuint getFirstIndex() { return startIndex; }
    int getContext() { return context; }

  private:
    ~SoGLDisplayList();

    Type type;
    GLuint startIndex;
    int num;
    int refCount;
    int context;
    
    friend class SoGLCacheContextElement;
};

class SbIntList;

SoEXTENDER class INVENTOR_API SoGLCacheContextElement : public SoElement {

    SO_ELEMENT_HEADER(SoGLCacheContextElement);

  public:
    //! Initializes element
    virtual void        init(SoState *state);

    //! Sets the current context.  This is done by the renderAction.
    // The third argument indicates whether 2-pass
    //! transparency is in effect (as for DELAYED or SORTED blending),
    //! which means that caches containing transparent objects may not
    //! be valid.
    static void         set(SoState *state, int context,
                            bool is2PassTransparency);

    //! Gets the current context
    static int          get(SoState *state);

    //! Methods to quickly figure out if an OpenGL extension is
    //! available at run-time.

    //! TRUE if mip-mapped textures are known to be fast
    //!(fli2011: always returns TRUE nowadays, only kept to keep legacy code working):
    static bool         areMipMapsFast(SoState *state);

    //! Methods used to improve auto-caching algorithm:

    //! Two bits are stored.  Nodes that should be cached will set the
    //! DO_AUTO_CACHE bit, nodes that should NOT be cached will set the
    //! DONT_AUTO_CACHE bit.  By default, DO_AUTO_CACHE is FALSE unless
    //! remote rendering is being done.  DONT_AUTO_CACHE is FALSE by
    //! default.  Separators will auto cache if DO_AUTO_CACHE is TRUE
    //! and DONT_AUTO_CACHE is FALSE, otherwise they won't auto-cache.
    enum {
        DO_AUTO_CACHE = 1,   //!< Hack warning: I rely on TRUE==DO_AUTO_CACHE
        DONT_AUTO_CACHE = 2
    };

    //! Called by nodes to say that they should/shouldn't be
    //! auto-cached (pass TRUE if should, FALSE if shouldn't, don't
    //! call this method at all if the node doesn't care):
    static void         shouldAutoCache(SoState *state, int bits)
    {
        SoGLCacheContextElement *elt = (SoGLCacheContextElement *)
            state->getElementNoPush(classStackIndex);
        elt->autoCacheBits |= bits;
    }

    //! Used by Separators to set/reset the auto-caching bits:
    static void         setAutoCacheBits(SoState *state, int bits)
        { ((SoGLCacheContextElement *)state->getElementNoPush(
            classStackIndex))->autoCacheBits = bits;
        }

    static int          resetAutoCacheBits(SoState *state)
        {
            SoGLCacheContextElement *elt = (SoGLCacheContextElement *)
                state->getElementNoPush(classStackIndex);
            int result = elt->autoCacheBits;
            elt->autoCacheBits = 0;
            
            return result;
        }

    //! Standard element stuff:

    //! Returns TRUE if the widths match in both elements
    virtual bool        matches(const SoElement *elt) const;

    //! Create and return a copy of this element
    virtual SoElement   *copyMatchInfo() const;

    //! Prints element (for debugging)
    virtual void        print(FILE *fp) const;

  SoINTERNAL public:
    static void         initClass();

  protected:
    int                 context;
    bool                is2PassTransp;
    int                 autoCacheBits;

    virtual ~SoGLCacheContextElement();

  private:
    //! Frees up the given display lists right away, if possible.  If
    //! not possible (because the state passed in is NULL or has a
    //! different cache context than the display lists' state), this
    //! adds the given display list/count to the list of display lists
    //! that need to be freed the next time the given context is valid.
    //! This method is necessary because nodes with caches can be
    //! deleted at any time, but we can't necessarily send GL commands
    //! to free up a display list at any time.
    static void         freeList(SoState *state,
                                 SoGLDisplayList *list);

    static SbPList *    waitingToBeFreed;       //!< Allocated in ::init

friend class SoGLDisplayList;
};

#endif /* _SO_CACHE_CONTEXT_ELEMENT */
