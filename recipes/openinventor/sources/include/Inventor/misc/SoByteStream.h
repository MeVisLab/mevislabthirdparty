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
 |      This file defines the SoByteStream class.
 |
 |   Author(s): David Mott
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_BYTE_STREAM_
#define  _SO_BYTE_STREAM_

#include <Inventor/SbBasic.h>

class SoNode;
class SoPath;
class SoPathList;


////////////////////////////////////////////////////////////////////////////////
//! Converts scene graph objects to character byte streams.
/*!
\class SoByteStream
\ingroup General
This class creates a byte stream representation of a scene graph,
using an SoWriteAction to write path lists to an in-memory
buffer.  Byte streams are commonly used to transfer data in copy and
paste operations.

*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoByteStream {
  public:
    //! Constructor and destructor.
    SoByteStream();
   //! Constructor and destructor.
   ~SoByteStream();

    //! Convert the passed node, path, or path list into a byte stream.
    //! Caller may specify whether the byte stream is written in binary
    //! (TRUE) or ascii (FALSE) format. The converted data can be accessed
    //! through getData() and getNumBytes().
    
    //! \see convert(SoPathList *pathList, bool binaryFormat)
    void                convert(SoNode *node, bool binaryFormat = TRUE);
    
    //! \see convert(SoPathList *pathList, bool binaryFormat)
    void                convert(SoPath *path, bool binaryFormat = TRUE);
    
    //! These convert the passed scene graph object(s) into a byte stream.
    //! The caller may specify whether the byte stream is written in binary
    //! (TRUE) or ASCII (FALSE) format, and can pass the object(s) by node,
    //! path, or pathList.
    void                convert(SoPathList *pathList, bool binaryFormat = TRUE);

    //! Returns the data from the last convert()
    //! operation.  This byte stream format is well suited to data transfers,
    //! like copy and paste.
    void *              getData()       { return data; }
    //! Returns the number of bytes from the last convert()
    //! operation.
    uint32_t            getNumBytes()   { return numBytes; }
    
    //! Unconvert a byte stream back to a path list.
    //! This static routine performs an SoDB::read on the data,
    //! and returns a path list of the paths read in.
    
    //! These take byte stream data and unconvert it back to scene graph objects.
    //! The objects are returned in a path list.
    static SoPathList * unconvert(SoByteStream *byteStream);
    
    //! These take byte stream data and unconvert it back to scene graph objects.
    //! The objects are returned in a path list.
    static SoPathList * unconvert(void *data, uint32_t numBytes);
  
  SoEXTENDER public:
    //! This allows apps to store raw data here without converting 
    //! an Inventor node, path, or path list. This sets isRaw to TRUE,
    //! and that data cannot be unconverted.
    void                copy(void *d, size_t len);
    bool                isRawData() const { return isRaw; }
     
  private:
    void                *data;
    uint32_t            numBytes;
    bool                isRaw;
};

#endif // _SO_BYTE_STREAM_
