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
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.1.1.1 $
 |
 |   Description:
 |      Defines the SoWWWInline class
 |
 |   Author(s): Gavin Bell, David Mott, Jim Kent
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_WWWINLINE_
#define  _SO_WWWINLINE_

#include <Inventor/misc/SoChildList.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFVec3f.h>

#include <Inventor/actions/SoCallbackAction.h>

class SoWWWInline;
class SoGroup;
class SoWriteAction;

//! This is the format for callbacks that will get URL data for us.
//! Once they get the data, they should call the setChildData() method.
typedef void INVENTOR_API SoWWWInlineFetchURLCB(
    const SbString &url, void *userData, SoWWWInline *node);
                


////////////////////////////////////////////////////////////////////////////////
//! Node that refers to children through a URL.
/*!
\class SoWWWInline
\ingroup Nodes
This node refers to children through a URL (Universal Resource Locator).
The application is responsible for actually fetching data from the URL
for an SoWWWInline node to display.

\par Action Behavior
\par
SoGLRenderAction
<BR> This renders the child data if it has been set by the application. It will render a wireframe bounding box as specified by the <tt>bboxCenter</tt> and <tt>bboxSize</tt> fields, and the setting passed to <tt>setBoundingBoxVisibility()</tt>. If no fetch URL callback is set and the <tt>alternateRep</tt> is not NULL, the <tt>alternateRep</tt> will be rendered until child data has been set. 

\par See Also
\par
SoWWWAnchor, SoFile
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoWWWInline : public SoNode {

    SO_NODE_HEADER(SoWWWInline);

  public:

    //! Creates an inline node with default settings.
    SoWWWInline();

    enum BboxVisibility {
        NEVER,             //!< Do not show bounding box
        UNTIL_LOADED,      //!< Show bounding box (if specified) until data is loaded
        ALWAYS            //!< Show bounding box along with data
    };

    SoSFVec3f   bboxCenter;     //!< Bounding box center
    SoSFVec3f   bboxSize;       //!< Bounding box size
    SoSFString  name;           //!< URL specifying children (might be relative)
    SoSFNode    alternateRep;   //!< Child data if app cannot fetch URL

    //! \see getFullURLName()
    void                setFullURLName(const SbString &url) { fullURL = url; }
    //! If the name field contains a relative URL (e.g. "foo.wrl" 
    //! instead of "http://bogus.com/foo.wrl"), the inline cannot 
    //! resolve the URL reference. This method allows the application 
    //! to tell the anchor what it's full URL should be. 
    //! getFullURLName() returns the fullURL set here, or if not set, returns 
    //! the contents of the name field.
    const SbString &    getFullURLName();

    //! Return (hidden) children as Group
    SoGroup             *copyChildren() const;

    //! Request that URL data be fetched. This will invoke the
    //! application callback to actually fetch the data and can be called
    //! before the inline does this for itself (see <tt>setFetchURLCallBack()</tt>).
    void                requestURLData() 
                            { if (! kidsRequested) requestChildrenFromURL(); }
    //! Return whether URL data has been requested and whether that data
    //! is here (i.e. whether <tt>setChildData()</tt> has been called.)
    bool                isURLDataRequested() const { return kidsRequested; }
    //! Return whether URL data has been requested and whether that data
    //! is here (i.e. whether <tt>setChildData()</tt> has been called.)
    bool                isURLDataHere() const { return kidsAreHere; }
    //! Cancel the active URL data fetch request.
    void                cancelURLDataRequest() 
                            { if (!kidsAreHere) kidsRequested = FALSE; }

    //! Set/get the child data the inline should display. The application should set
    //! child data after it has fetched data for an inline node.
    void                setChildData(SoNode *urlData);
    //! Set/get the child data the inline should display. The application should set
    //! child data after it has fetched data for an inline node.
    SoNode *            getChildData() const;

    //! Application callbacks invoked when the inline needs its URL data fetched.
    //! This happens the first time the inline is rendered, or if it needs to compute
    //! a bounding box and the bboxSize field is not set, or when <tt>requestURLData()</tt> is called.
    static void setFetchURLCallBack(SoWWWInlineFetchURLCB *f, void *userData);

    //! This allows the application to specify when bounding boxes are displayed.
    //! The bounding box can be rendered along with the
    //! children (<tt>ALWAYS</tt>), only until the child data is loaded (<tt>UNTIL_LOADED</tt>),
    //! or not at all (<tt>NEVER</tt>). Default is <tt>UNTIL_LOADED</tt>
    static void setBoundingBoxVisibility(BboxVisibility b) { bboxVisibility = b; } 
    //! Get the bounding boxes visibility.
    static BboxVisibility getBoundingBoxVisibility() { return bboxVisibility; }

    //! This allows the application to specify the color of bounding boxes displayed.
    static void setBoundingBoxColor(SbColor &c) { bboxColor = c; }
    //! This allows the application to specify the color of bounding boxes displayed.
    static const SbColor &getBoundingBoxColor() { return bboxColor; }


  SoEXTENDER public:
    //! Traversal methods for all the actions:
    virtual void        doAction(SoAction *action);
    virtual void        doActionOnKidsOrBox(SoAction *action);
    virtual void        callback(SoCallbackAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void        getMatrix(SoGetMatrixAction *action);
    virtual void        handleEvent(SoHandleEventAction *action);
    virtual void        search(SoSearchAction *action);
    virtual void        pick(SoPickAction *action);

  SoINTERNAL public:
    static void         initClass();

    //! Returns pointer to children, or NULL if none
    virtual SoChildList *getChildren() const;

  protected:
    virtual ~SoWWWInline();

    virtual void        addBoundingBoxChild(SbVec3f center, SbVec3f size);

    //! Reads into instance of SoWWWInline. Returns FALSE on error.
    virtual bool        readInstance(SoInput *in, unsigned short flags);

    //! Copies the child data as well as the rest of the node (if
    //! the child data has been set)
    virtual void        copyContents(const SoFieldContainer *fromFC,
                                     bool copyConnections);

  private:
    void                requestChildrenFromURL();

    SoChildList         *children;
    bool                kidsRequested;
    bool                kidsAreHere;
    SbString            fullURL;

    static SbColor            bboxColor;
    static BboxVisibility     bboxVisibility;

    //! Static methods
    static SoWWWInlineFetchURLCB        *fetchURLcb;
    static void                         *fetchURLdata;
};

#endif /* _SO_WWWINLINE_ */

